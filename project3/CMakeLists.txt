cmake_minimum_required(VERSION 3.17)
project(project_3)

set(CMAKE_CXX_STANDARD 14)

add_executable(p3
        world_type.h p3.cpp simulation.cpp simulation.h)