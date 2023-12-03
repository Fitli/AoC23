//
// Created by ivana.krumlova on 3.12.2023.
//

#include <vector>
#include <iostream>
#include "Day03.h"

vector<int> Day03::row_from_line(string &line) {
    auto row = vector<int>(line.length() + 2, -1);
    int i = 0;
    for (char c:line) {
        i++;
        if(c == '.') {
            continue;
        }
        if (c >= '0' and c <= '9') {
            row[i] = c - '0';
        }
        else {
            row[i] = -2;
        }
    }
    return row;
}

vector<vector<int>> Day03::create_grid() {
    string line;
    _in_file >> line;
    vector<vector<int>> grid;
    grid.emplace_back(line.length() + 2, -1);
    grid.push_back(row_from_line(line));
    while (_in_file >> line) {
        if (line.empty()) {
            continue;
        }
        grid.push_back(row_from_line(line));
    }
    grid.emplace_back(line.length() + 2, -1);
    return grid;
}

bool Day03::has_symbol(vector<vector<int>> &grid, size_t start_x, size_t start_y, size_t end_x, size_t end_y) {
    for (size_t i = start_y; i <= end_y; ++i) {
        for (size_t j = start_x; j <= end_x; ++j) {
            if (grid[i][j] == -2) {
                return true;
            }
        }
    }
    return false;
}

int Day03::get_sum(vector<vector<int>> &grid) {
    int sum = 0;
    for (int i = 0; i < grid.size(); i++) {
        vector<int> &row = grid[i];
        int num = 0;
        size_t num_len = 0;
        for (int j = 0; j < row.size(); j++) {
            if(grid[i][j] >= 0) {
                num *= 10;
                num += grid[i][j];
                num_len++;
            }
            else {
                if (num_len > 0 and has_symbol(grid, j - num_len - 1, i-1, j, i+1)) {
                    sum += num;
                }
                num = 0;
                num_len = 0;
            }
        }
    }
    return sum;
}

void Day03::run1(bool print_result) {
    vector<vector<int>> grid = create_grid();
    int sum = get_sum(grid);
    if (print_result) {
        cout << sum << endl;
    }
}
