//
// Created by Leonardo on 10/10/2023.
//

#include "Queue.h"
#include <gtest/gtest.h>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

/*
 * This test will check if Pop operation is ignored when the Queue is empty and none push was received.
 */
TEST(QueueTests, popFromEmptyQueueTest) {
    Queue<int> m_queue(1);
    ASSERT_EQ(m_queue.Count(), 0);
    m_queue.Pop();
    ASSERT_EQ(m_queue.Count(), 0);
}


/*
 * This test will check if Push operation is working as expected.
 */
TEST(QueueTests, pushFromEmptyQueueTest) {

    Queue<int> m_queue(1);
    ASSERT_EQ(m_queue.Count(), 0);
    m_queue.Push(1);
    std::this_thread::sleep_for(0.5s);
    ASSERT_EQ(m_queue.Count(), 1);
}


/*
 * This test will check if Push operation is ignored when the Queue is full other push was received and none Pop.
 */
TEST(QueueTests, pushBlockedQueueTest) {

    Queue<int> m_queue(1);
    ASSERT_EQ(m_queue.Count(), 0);
    m_queue.Push(1);
    std::this_thread::sleep_for(0.5s);
    m_queue.Push(2);
    std::this_thread::sleep_for(2s);
    ASSERT_EQ(m_queue.Count(), 1);
}


/*
 * This test will check if a blocked Push operation is released after a Pop free a space into queue.
 */
TEST(QueueTests, pushReleasePushQueueTest) {

    Queue<int> m_queue(1);
    ASSERT_EQ(m_queue.Count(), 0);
    m_queue.Push(10);
    std::this_thread::sleep_for(0.5s);
    ASSERT_EQ(m_queue.Count(), 1);
    m_queue.Push(20);
    std::this_thread::sleep_for(0.5s);
    ASSERT_EQ(m_queue.Count(), 1);
    m_queue.Pop();
    std::this_thread::sleep_for(0.5s);
    ASSERT_EQ(m_queue.Count(), 1);
    m_queue.Pop();
    std::this_thread::sleep_for(0.5s);
    ASSERT_EQ(m_queue.Count(), 0);
}


/*
 * This test will check if a blocked Pop operation is released after a Push add an element into queue.
 */
TEST(QueueTests, pushReleasePopQueueTest) {

    Queue<int> m_queue(1);
    ASSERT_EQ(m_queue.Count(), 0);
    m_queue.Pop();
    std::this_thread::sleep_for(0.5s);
    ASSERT_EQ(m_queue.Count(), 0);
    m_queue.Push(10);
    std::this_thread::sleep_for(0.5s);
    ASSERT_EQ(m_queue.Count(), 0);
}


/*
 * This test will check if the size of queue is equals to the value sent as param.
 */
TEST(QueueTests, SizeQueueTest) {

    Queue<int> m_queue(10);
    ASSERT_EQ(m_queue.Size(), 10);
    ASSERT_EQ(m_queue.Count(), 0);
}


/*
 * This test will check if the queue works as expected when Push operations are blocked and released and Pop operations
 * are blocked and released in sequence.
 */
TEST(QueueTests, BaseQueueTest) {

    Queue<int> m_queue(2);
    ASSERT_EQ(m_queue.Count(), 0);

    m_queue.Push(1);
    std::this_thread::sleep_for(0.5s);
    ASSERT_EQ(m_queue.Count(), 1);

    m_queue.Pop();
    std::this_thread::sleep_for(0.5s);
    ASSERT_EQ(m_queue.Count(), 0);

    m_queue.Push(2);
    std::this_thread::sleep_for(0.5s);
    ASSERT_EQ(m_queue.Count(), 1);

    m_queue.Push(3);
    std::this_thread::sleep_for(0.5s);
    ASSERT_EQ(m_queue.Count(), 2);

    m_queue.Push(4);
    std::this_thread::sleep_for(0.5s);
    ASSERT_EQ(m_queue.Count(), 2);

    m_queue.Pop();
    std::this_thread::sleep_for(0.5s);
    ASSERT_EQ(m_queue.Count(), 2);

    m_queue.Pop();
    std::this_thread::sleep_for(0.5s);
    ASSERT_EQ(m_queue.Count(), 1);

    m_queue.Pop();
    std::this_thread::sleep_for(0.5s);
    ASSERT_EQ(m_queue.Count(), 0);

    m_queue.Pop();
    std::this_thread::sleep_for(0.5s);
    ASSERT_EQ(m_queue.Count(), 0);

    m_queue.Push(5);
    std::this_thread::sleep_for(0.5s);
    ASSERT_EQ(m_queue.Count(), 0);
}

int main(int argc, char **argv){

    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();

}
