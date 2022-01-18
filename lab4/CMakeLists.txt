cmake_minimum_required(VERSION 3.17)
project(lab4)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab4
        BaseExpr.h
        main.cpp
        UnaryOP.cpp
        UnaryOP.h BaseExpr.cpp BinaryOP.cpp BinaryOP.h Expression.cpp Expression.h)
