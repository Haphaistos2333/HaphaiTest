cmake_minimum_required(VERSION 3.15)
project(HaphaiTest)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(HaphaiTest
        HaphaiTest.h
        main.cpp
        test.cpp
        test.h)
