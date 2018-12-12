cmake_minimum_required(VERSION 3.12)
project(lab6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")
set(SOURCE_FILES task6.cpp)

add_executable(lab6  ${SOURCE_FILES})