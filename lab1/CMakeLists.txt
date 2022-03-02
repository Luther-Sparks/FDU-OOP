cmake_minimum_required(VERSION 3.17)
project(lab1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(endlessLoop
        endlessLoop.cpp)

add_executable(segmentationFault
        segmentFault.cpp)

add_executable(findKthStr
        findKthStr.cpp)