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
    Day02(string name, const string& in_file) : Task(std::move(name), in_file) {
        for (const string& color:_colors) {
            _color_regexes[color] = regex("(\\d+) " + color);
        }
    };
    void run1(bool print_result) override {
        string line;
        int suma = 0;
        while(getline(_input, line)) {
            suma += evaluate_game(line);
        }
        if(print_result) {
            cout << suma << endl;
        }
    }
    void run2(bool print_result) override {
        string line;
        int suma = 0;
        while(getline(_input, line)) {
            suma += get_power(line);
        }
        if(print_result) {
            cout << suma << endl;
        }
    }
private:
    int evaluate_game(string& line) {
        if (line.empty()) {
            return 0;
        }
        smatch sm;
        regex_search(line, sm, _game_num_regex);
        int game_round = stoi(sm[1]);

        auto max_seen = get_max_seen(line);
        if (max_seen["red"] <= 12 and max_seen["green"] <= 13 and max_seen["blue"] <= 14) {
            return game_round;
        }
        return 0;
    }

    map<string, int> get_max_seen(string &line) {
        map<string, int> max_seen;
        for (const string& color:_colors) {
            max_seen[color] = 0;
            sregex_iterator iter(line.begin(), line.end(), _color_regexes[color]);
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

    int get_power(string &line) {
        if (line.empty()) {
            return 0;
        }

        auto max_seen = get_max_seen(line);
        return max_seen["red"] * max_seen["green"] * max_seen["blue"];
    }


    vector<string> _colors{"red", "blue", "green"};
    map<string, regex> _color_regexes{};
    regex _game_num_regex = regex("Game (\\d+):");
};


#endif //AOC2023_DAY02_H
