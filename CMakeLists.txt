cmake_minimum_required(VERSION 3.26)
project(aoc2023)

set(CMAKE_CXX_STANDARD 20)

add_executable(aoc2023 main.cpp
        infra/Task.cpp
        infra/Task.h
        tasks/Day1.cpp
        tasks/Day1.h
        tasks/Day2.cpp
        tasks/Day2.h
        tasks/Day03.cpp
        tasks/Day03.h)
