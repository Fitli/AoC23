cmake_minimum_required(VERSION 3.26)
project(aoc2023)

set(CMAKE_CXX_STANDARD 20)

add_executable(aoc2023 main.cpp
        infra/Task.cpp
        infra/Task.h
        tasks/Day01.cpp
        tasks/Day01.h
        tasks/Day02.cpp
        tasks/Day02.h
        tasks/Day03.cpp
        tasks/Day03.h
        tasks/Day04.cpp
        tasks/Day04.h)
