//
// Created by ivana.krumlova on 2.12.2023.
//

#ifndef AOC2023_DAY2_H
#define AOC2023_DAY2_H

#include <vector>

#include "../infra/Task.h"

class Day2: public Task {
public:
    Day2(string name, string in_file) : Task(std::move(name), std::move(in_file)) {};
    void run1(bool print_result) override;
    void run2(bool print_result) override;
private:
    int evaluate_game(string& line);
    vector<string> _colors{"red", "blue", "green"};

    map<string, int> get_max_seen(string &line);

    int get_power(string &line);
};


#endif //AOC2023_DAY2_H
