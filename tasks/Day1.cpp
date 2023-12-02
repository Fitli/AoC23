//
// Created by ivana.krumlova on 2.12.2023.
//

#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>

#include "Day1.h"

map<string, int> Day1::num_chars()
{
    map<string, int> num_ch{};
    for (int i = 0; i < 10; i++) {
        num_ch.insert({ to_string(i), i });
    }
    return num_ch;
};

string Day1::min_map_element(map<string, int> m)
{
    auto a = *min_element(m.begin(), m.end(), [](std::pair<std::string, int> l, std::pair<std::string, int> r) -> bool { return l.second < r.second; });
    return a.first;
}

int Day1::get_occurence(string str, map<string, int>& to_search, bool first) {
    auto first_occs = map<string, int>{};
    for (const auto& kv : to_search) {
        size_t pos = first ? str.find(kv.first) : str.rfind(kv.first);
        if (pos != string::npos) {
            first_occs[kv.first] = first ? pos : str.length() - pos;
            str = first ? str.substr(0, pos + 2) : str.substr(pos, string::npos);
        }
    }
    return to_search[min_map_element(first_occs)];
}

int Day1::get_num(string& str, map<string, int>& to_search) {
    int first = get_occurence(str, to_search, true);
    int last = get_occurence(str, to_search, false);
    return 10 * first + last;
}

void Day1::run1(bool print_result) {
    std::string line = "";
    int suma = 0;
    map<string, int> to_search = num_chars();
    while (_in_file >> line) {
        suma += get_num(line, to_search);
    }
    if (print_result)
        std::cout << suma << std::endl;
}

void Day1::run2(bool print_result) {
    std::string line = "";
    map<string, int> to_search = num_chars();
    to_search.insert(num_strings.begin(), num_strings.end());

    int suma = 0;
    while (_in_file >> line) {
        suma += get_num(line, to_search);
    }
    if(print_result)
        std::cout << suma << std::endl;
}
