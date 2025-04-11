cmake_minimum_required(VERSION 3.29)
project(TEP_Lab3)

set(CMAKE_CXX_STANDARD 98)

add_executable(TEP_Lab3
        main.cpp
        CTreeUI.cpp
        CTree.cpp
        CNode.cpp
        CTreeUI.h
        CTree.h
        CNode.h
        constants.h)
