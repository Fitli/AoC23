//
// Created by ivana.krumlova on 2.12.2023.
//

#ifndef AOC2023_TASK_H
#define AOC2023_TASK_H


#include <string>
#include <fstream>

using namespace std;

class Task
{
public:
    Task(string name, string in_file);

    virtual void run1(bool print_result);
    virtual void run2(bool print_result);
    void print_results();

    void measure_time();

    string _name;
    ifstream _in_file;
};


#endif //AOC2023_TASK_H
