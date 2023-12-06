//
// Created by ivana.krumlova on 2.12.2023.
//

#ifndef AOC2023_DAY01_H
#define AOC2023_DAY01_H


#include <map>
#include <regex>
#include <utility>
#include <iostream>
#include "../infra/Task.h"
class Day01: public Task
{
public:
    Day01(string name, const string& in_file) : Task(std::move(name), in_file) {};
    void run1(bool print_result) override {
        std::string line;
        regex r("(\\d)");
        int suma = 0;
        while (_input >> line) {
            suma += get_num(r, r, line);
        }
        if (print_result)
            cout << suma << std::endl;
    }
    void run2(bool print_result) override {
        string num_str_regex_str;
        for (const auto& n:num_strings) {
            num_str_regex_str += "|" + n.first;
        }
        string reverse_regex_str{num_str_regex_str};
        reverse(reverse_regex_str.begin(), reverse_regex_str.end());

        regex front_r("\\d" + num_str_regex_str);
        regex back_r(reverse_regex_str + "\\d");

        std::string line;

        int suma = 0;
        while (_input >> line) {
            suma += get_num(front_r, back_r, line);
        }
        if(print_result)
            std::cout << suma << std::endl;
    }

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
    int get_num(regex &r_front, regex &r_back, string &line) {
        smatch sm;
        regex_search(line, sm, r_front);
        int first = str_to_num(sm.str());
        reverse(line.begin(), line.end());
        regex_search(line, sm, r_back);
        string found_str = sm.str();
        reverse(found_str.begin(), found_str.end());
        int last = str_to_num(found_str);
        return 10 * first + last;
    }
    int str_to_num(const string& str) {
        if (str.length() == 1) {
            return stoi(str);
        }
        return num_strings[str];
    }
};


#endif //AOC2023_DAY01_H
