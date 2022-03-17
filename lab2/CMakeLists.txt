cmake_minimum_required(VERSION 3.0)
project(lab2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra")

add_executable(editor
        main.cpp
        util.cpp
        util.h
        editor.cpp 
        editor.h
        )
