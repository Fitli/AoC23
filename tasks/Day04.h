//
// Created by ivana.krumlova on 4.12.2023.
//

#ifndef AOC2023_DAY04_H
#define AOC2023_DAY04_H


#include "../infra/Task.h"

class Card {
public:
    Card(int number_) {
        number = number_;
    }
    int number;
    int num_matching{0};
    int num_cards{1};
};

class Day04: public Task {
public:
    Day04(string name, const string& in_file) : Task(std::move(name), in_file) { };
    void run1(bool print_result) override;
    void run2(bool print_result) override;
private:
    Card parse_line(string &line);
    const regex R{"\\d+|\\|"};
};


#endif //AOC2023_DAY04_H
