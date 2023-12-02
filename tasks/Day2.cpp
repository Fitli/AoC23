//
// Created by ivana.krumlova on 2.12.2023.
//
#include <iostream>
#include <map>
#include <regex>
#include "Day2.h"

using namespace std;

map<string, int> Day2:: get_max_seen(string& line) {
    map<string, int> max_seen;
    for (const string& color:_colors) {
        max_seen[color] = 0;
        regex r("(\\d+) " + color);
        sregex_iterator iter(line.begin(), line.end(), r);
        sregex_iterator end;
        while (iter != end) {
            int seen = stoi((*iter)[1]);
            if (seen > max_seen[color]) {
                max_seen[color] = seen;
            }
            iter++;
        }
    }
    return max_seen;
}

int Day2::evaluate_game(string& line) {
    if (line.empty()) {
        return 0;
    }
    smatch sm;
    regex_search(line, sm, regex("Game (\\d+):"));
    int game_round = stoi(sm[1]);

    auto max_seen = get_max_seen(line);
    if (max_seen["red"] <= 12 and max_seen["green"] <= 13 and max_seen["blue"] <= 14) {
        return game_round;
    }
    return 0;
}

void Day2::run1(bool print_result) {
    string line;
    int suma = 0;
    while(getline(_in_file, line)) {
        suma += evaluate_game(line);
    }
    if(print_result) {
        cout << suma << endl;
    }
}

int Day2::get_power(string& line) {
    if (line.empty()) {
        return 0;
    }
    smatch sm;
    regex_search(line, sm, regex("Game (\\d+):"));
    int game_round = stoi(sm[1]);

    auto max_seen = get_max_seen(line);
    return max_seen["red"] * max_seen["green"] * max_seen["blue"];
}

void Day2::run2(bool print_result) {
    string line;
    int suma = 0;
    while(getline(_in_file, line)) {
        suma += get_power(line);
    }
    if(print_result) {
        cout << suma << endl;
    }
}
