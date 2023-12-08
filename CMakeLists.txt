cmake_minimum_required(VERSION 3.16)
project(aoc2023)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS -Ofast)

add_executable(aoc2023 main.cpp
        infra/Task.h
        tasks/Day01.h
        tasks/Day02.h
        tasks/Day03.h
        tasks/Day04.h
        tasks/Day05.h
        tasks/Day06.h
        tasks/Day07.h
        tasks/Day08.h)
