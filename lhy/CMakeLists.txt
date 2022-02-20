cmake_minimum_required(VERSION 3.17)
project(lhy)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lhy
        dynamic_array.cpp
        dynamic_array.h
        dynamic_impl.h)
