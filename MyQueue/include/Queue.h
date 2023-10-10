//
// Created by Leonardo on 09/10/2023.
//
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>

#pragma once

using namespace std;

template<class T>
class Queue {
private:

    int size;
    queue<T> m_queue;
    mutex m_mutex;
    condition_variable can_push;
    condition_variable can_pop;
    vector<thread> threads;

    /**
     * Internal function responsible for add elements into queue.
     * @param element to be added.
     */
    void p_push(T element) {
        // A mutex was used to avoid race condition into queue, Once we have multiple threads trying to use this
        // critical area.
        // I have used a unique_lock to integrate with a condition variable avoiding use of a while or sleep when an
        // operation cannot be done.
        // This class wraps my mutex and automatically locks and unlock when this function is out of scope.
        unique_lock<mutex> push_lock(m_mutex);
        // Here a wait_for was used to finish threads in starvation avoiding deadlocks.
        // The predicate of my condition variable only allow this push operation if the number of elements in my queue
        // is less than size defined in constructor.
        if (can_push.wait_for(push_lock, std::chrono::seconds(2), [this] { return m_queue.size() < size; })) {
            m_queue.push(element);
            // Auxiliary function to follow execution.
            print_queue();
            // Now I notify and awake the next thread waiting to do a pop
            can_pop.notify_one();
        } else {
            cout << "Timeout occurred. Ignoring Push()" << endl;
        }
    }

    /**
     * Internal function responsible for remove an elements from begin of queue.
     */
    void p_pop() {
        // This lock has exactly the same comportment as described above in the p_push method.
        unique_lock<mutex> pop_lock(m_mutex);
        // For this case my condition variable will allow a pop operation only if the queue has at least one element.
        if (can_pop.wait_for(pop_lock, std::chrono::seconds(2), [this] { return m_queue.size() > 0; })) {
            m_queue.pop();
            print_queue();
            // Now I notify and awake the next thread waiting to do a push
            can_push.notify_one();
        } else {
            std::cout << "Timeout occurred. Ignoring Pop()" << std::endl;
        }
    }

    /**
     * Auxiliary method to print the queue state and its elements.
     */
    void print_queue() {

        queue<T> tempQueue = m_queue; // Create a copy of the queue
        cout << "Queue: {";
        while (!tempQueue.empty()) {
            cout << tempQueue.front() << ", ";
            tempQueue.pop();
        }
        cout << "}" << endl;
    }


public:
    /**
     * Method responsible to create a writer thread and run p_push on it.
     * @param element to be added.
     */
    void Push(T element) {
        // This threads vector was added to grant a control of all threads waiting and running.
        // This will be used into destructor to release resources allocated by threads.
        threads.emplace_back([this, element]() {
            this->p_push(element);
        });
    }

    void Pop() {
        // Similar behaviour as described above.
        threads.emplace_back([this]() {
            this->p_pop();
        });

    }

    /**
     * Will return the number of elements into queue.
     * @return elements count.
     */
    int Count() {
        return this->m_queue.size();
    }

    /**
     * Will return the maximum number of elements that can be added into queue.
     * @return maximum number of elements.
     */
    int Size() {
        return this->size;
    }

    /**
     * Class constructor.
     * @param size maximum number of elements into queue.
     */
    Queue(int size) {
        this->size = size;
    }

    /**
     * Class destructor
     */
    ~Queue() {
        for (auto &thread: threads) {
            thread.join();
        }
    }

};
