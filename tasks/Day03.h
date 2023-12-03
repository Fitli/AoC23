//
// Created by ivana.krumlova on 3.12.2023.
//

#ifndef AOC2023_DAY03_H
#define AOC2023_DAY03_H


#include <utility>

#include "../infra/Task.h"

class Day03: public Task {

public:
    Day03(string name, string in_file) : Task(std::move(name), std::move(in_file)) {}
    void run1(bool print_result) override;

private:
    static vector<int> row_from_line(string &line);

    vector<vector<int>> create_grid();

    static int get_sum(vector<vector<int>> &grid);

    static bool has_symbol(vector<vector<int>> &grid, size_t start_x, size_t start_y, size_t end_x, size_t end_y);
};


#endif //AOC2023_DAY03_H
