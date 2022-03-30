cmake_minimum_required(VERSION 3.17)
project(lab3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Werror -O2")

include_directories(.)

add_executable(n_gram
        main.cpp
        util.cpp
        grams.cpp)
        