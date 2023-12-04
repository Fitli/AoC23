//
// Created by ivana.krumlova on 2.12.2023.
//

#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>
#include <regex>

#include "Day01.h"

int Day01::str_to_num(const string& str) {
    if (str.length() == 1) {
        return stoi(str);
    }
    return num_strings[str];
};

int Day01::get_num(regex &r_front, regex &r_back, string &line) {
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

void Day01::run1(bool print_result) {
    std::string line;
    regex r("(\\d)");
    int suma = 0;
    while (_input >> line) {
        suma += get_num(r, r, line);
    }
    if (print_result)
        std::cout << suma << std::endl;
}

void Day01::run2(bool print_result) {
    string num_str_regex_str = "";
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
