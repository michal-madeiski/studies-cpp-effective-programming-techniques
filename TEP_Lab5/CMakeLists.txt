cmake_minimum_required(VERSION 3.30)
project(TEP_Lab5)

set(CMAKE_CXX_STANDARD 11)

add_executable(TEP_Lab5
        main.cpp
        SmartPointer.h
        RefCounter.h
        tree/CInfo.cpp
        tree/CInfo.h
        tree/CNode.cpp
        tree/CNode.h
        tree/constants.h
        tree/CTree.cpp
        tree/CTree.h
        tree/CTreeUI.cpp
        tree/CTreeUI.h)
