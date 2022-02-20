cmake_minimum_required(VERSION 3.17)
project(Project_2_Related_Files)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project_2_Related_Files
        p2.h
        recursive.cpp
        recursive.h
        p2.cpp
        simple_test.cpp)
