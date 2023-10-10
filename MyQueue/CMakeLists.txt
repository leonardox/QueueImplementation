cmake_minimum_required(VERSION 3.24)
project(MyQueue)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

enable_testing()

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/googletest)

#add_executable(Queue src/main.cpp test/QueueTest.cpp)
