cmake_minimum_required(VERSION 3.12)
project(lab5)

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(standart_queue standart_queue.cpp)

set(PROJECT_HEADERS SafeQueue.h)
set(PROJECT_SOURCES safe_queue.cpp SafeQueue.cpp)
add_executable(safe_queue ${PROJECT_SOURCES} ${PROJECT_HEADERS})

add_executable(standart_queue_linear standart_queue_linear.cpp)