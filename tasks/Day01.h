//
// Created by ivana.krumlova on 2.12.2023.
//

#ifndef AOC2023_DAY01_H
#define AOC2023_DAY01_H


#include <map>
#include <regex>
#include <utility>
#include "../infra/Task.h"
class Day01 :
        public Task
{
public:
    Day01(string name, const string& in_file) : Task(std::move(name), in_file) {};
    int get_num(regex &r_front, regex &r_back, string &line);
    void run1(bool print_result) override;
    void run2(bool print_result) override;

private:
    map<string, int> num_strings{
            { "zero", 0 },
            { "one", 1 },
            { "two", 2 },
            { "three", 3 },
            { "four", 4 },
            { "five", 5 },
            { "six", 6 },
            { "seven", 7 },
            { "eight", 8 },
            { "nine", 9 },
    };


    int str_to_num(const string& str);
};


#endif //AOC2023_DAY01_H
