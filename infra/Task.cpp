//
// Created by ivana.krumlova on 2.12.2023.
//

#include <string>
#include <fstream>
#include <iostream>
#include <chrono>

#include "Task.h"

using namespace std;


Task::Task(string name, string in_file)
{
    _name = name;
    _in_file = ifstream(in_file);
}

void Task::run1(bool print_result) {
    if (print_result) {
        cout << "not implemented" << endl;
    }
}

void Task::run2(bool print_result) {
    if (print_result) {
        cout << "not implemented" << endl;
    }
}

void Task::print_results() {
    cout << _name << " - Task 1: ";
    run1(true);
    cout << flush;
    _in_file.clear();
    _in_file.seekg(0);
    cout << _name << " - Task 2: ";
    run2(true);
    cout << flush;
}

void Task::measure_time() {
    int repeats = 10;
    chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (size_t i = 0; i < 10; i++)
    {
        run1(false);
        _in_file.clear();
        _in_file.seekg(0);
    }
    chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << "1: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()/(1000.0*repeats) << endl;

    chrono::steady_clock::time_point begin2 = std::chrono::steady_clock::now();
    for (size_t i = 0; i < 10; i++)
    {
        run1(false);
        _in_file.clear();
        _in_file.seekg(0);
    }
    chrono::steady_clock::time_point end2 = std::chrono::steady_clock::now();
    cout << "2: " << std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2).count()/(1000.0*repeats) << endl;
}
