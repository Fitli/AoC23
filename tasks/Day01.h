//
// Created by ivana.krumlova on 2.12.2023.
//

#ifndef AOC2023_DAY01_H
#define AOC2023_DAY01_H


#include <map>
#include "../infra/Task.h"
class Day01 :
        public Task
{
public:
    Day01(string name, string in_file) : Task(name, in_file) {};
    map<string, int> num_chars();
    string min_map_element(map<string, int> m);
    int get_occurence(string str, map<string, int>& to_search, bool first);
    int get_num(string & str, map<string, int>& to_search);
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


};


#endif //AOC2023_DAY01_H
