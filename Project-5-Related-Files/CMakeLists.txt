cmake_minimum_required(VERSION 3.17)
project(Project_5_Related_Files)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project_5_Related_Files
        dlist.h
        dlist_impl.h
        call.cpp)
