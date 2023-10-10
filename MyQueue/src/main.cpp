#include <iostream>
#include "../include/Queue.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Queue<int> queue(2);

    queue.Push(1);
//    this_thread::sleep_for(chrono::seconds(1));
    queue.Pop();
//    this_thread::sleep_for(chrono::seconds(1));
    queue.Push(2);
//    this_thread::sleep_for(chrono::seconds(1));
    queue.Push(3);
//    this_thread::sleep_for(chrono::seconds(1));
    queue.Push(4);
//    this_thread::sleep_for(chrono::seconds(1));
    queue.Pop();
//    this_thread::sleep_for(chrono::seconds(1));
    queue.Pop();
//    this_thread::sleep_for(chrono::seconds(1));
    queue.Pop();
//    this_thread::sleep_for(chrono::seconds(1));
    queue.Pop();
//    this_thread::sleep_for(chrono::seconds(1));
    queue.Push(5);
//    this_thread::sleep_for(chrono::seconds(1));

//    this_thread::sleep_for(chrono::seconds(2));

    return 0;
}
