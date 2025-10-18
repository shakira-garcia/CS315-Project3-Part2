cmake_minimum_required(VERSION 4.0)
project(p3 CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(p3_part2
        main.cpp
        Scanner.cpp
        Scanner.hpp
        utils.cpp
        utils.hpp
        BST.cpp
        BST.hpp
        PriorityQueue.cpp
        PriorityQueue.hpp
)

