//
// Created by ivana.krumlova on 2.12.2023.
//

#ifndef AOC2023_DAY02_H
#define AOC2023_DAY02_H

#include <vector>
#include <regex>

#include "../infra/Task.h"

class Day02: public Task {
public:
    Day02(string name, string in_file) : Task(std::move(name), std::move(in_file)) {
        for (const string& color:_colors) {
            _color_regexes[color] = regex("(\\d+) " + color);
        }
    };
    void run1(bool print_result) override;
    void run2(bool print_result) override;
private:
    int evaluate_game(string& line);
    vector<string> _colors{"red", "blue", "green"};
    map<string, regex> _color_regexes{};
    regex _game_num_regex = regex("Game (\\d+):");

    map<string, int> get_max_seen(string &line);

    int get_power(string &line);
};


#endif //AOC2023_DAY02_H
