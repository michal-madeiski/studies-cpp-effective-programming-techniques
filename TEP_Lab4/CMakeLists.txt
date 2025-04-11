cmake_minimum_required(VERSION 3.30)
project(TEP_Lab4)

set(CMAKE_CXX_STANDARD 98)

add_executable(TEP_Lab4
        main.cpp
        Result_T_E.h
        specializations/Result_void_E.h
        error/Error.cpp
        error/Error.h
        saver/Saver.h
        tree/CInfo.cpp
        tree/CInfo.h
        tree/CNode.cpp
        tree/CNode.h
        tree/constants.h
        tree/CTree.cpp
        tree/CTree.h
        tree/CTreeUI.cpp
        tree/CTreeUI.h)
