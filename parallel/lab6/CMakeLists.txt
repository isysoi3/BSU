cmake_minimum_required(VERSION 3.12)
project(lab6)

set(CMAKE_CXX_COMPILER /usr/local/bin/g++-8)
set(CMAKE_C_COMPILER /usr/local/bin/gcc-8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

set(SOURCE_FILE_TASK_6 task6.cpp)
set(SOURCE_FILE_TASK_7 task7.cpp)
set(SOURCE_FILE_TASK_10 task10.cpp)


add_executable(task6  ${SOURCE_FILE_TASK_6})
add_executable(task7  ${SOURCE_FILE_TASK_7})
add_executable(task10  ${SOURCE_FILE_TASK_10})