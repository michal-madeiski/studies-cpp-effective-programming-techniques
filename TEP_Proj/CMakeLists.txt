cmake_minimum_required(VERSION 3.30)
project(TEP_Proj)

set(CMAKE_CXX_STANDARD 11)

add_executable(TEP_Proj
        GeneticProject/GaussianGroupingEvaluatorFactory.cpp
        GeneticProject/GaussianGroupingEvaluatorFactory.h
        GroupingChallenge.cpp
        GeneticProject/GroupingEvaluator.cpp
        GeneticProject/GroupingEvaluator.h
        Optimizer.h
        GeneticProject/Point.cpp
        GeneticProject/Point.h
        Individual.cpp
        Individual.h
        GeneticAlgorithm.cpp
        GeneticAlgorithm.h)
