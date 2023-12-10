//
// Created by ivana.krumlova on 3.12.2023.
//

#ifndef AOC2023_DAY03_H
#define AOC2023_DAY03_H


#include <utility>

#include "../infra/Task.h"

class Day03: public Task {

public:
    Day03(string name, const string& in_file) : Task(std::move(name), in_file) {}
    void run1(bool print_result) override {
        vector<vector<int>> grid = create_grid();
        map<tuple<size_t, size_t>, vector<int>> star_map{};
        int sum{0};
        process_grid(grid, star_map, sum);
        if (print_result) {
            cout << sum << endl;
        }
    }
    void run2(bool print_result) override {
        vector<vector<int>> grid = create_grid();
        map<tuple<size_t, size_t>, vector<int>> star_map{};
        int sum_part_numbers{0};
        process_grid(grid, star_map, sum_part_numbers);
        int sum_gears = 0;
        for (auto star: star_map) {
            if(star.second.size() == 2) {
                sum_gears += star.second[0] * star.second[1];
            }
        }
        if (print_result) {
            cout << sum_gears << endl;
        }
    }

private:
    static vector<int> row_from_line(string &line) {
        vector<int> row(line.length() + 2, -1);
        int i = 0;
        for (char c:line) {
            i++;
            if(c == '.') {
                continue;
            }
            if (c >= '0' and c <= '9') {
                row[i] = c - '0';
            }
            else if (c == '*') {
                row[i] = STAR;
            }
            else {
                row[i] = SYMBOL;
            }
        }
        return row;
    }

    vector<vector<int>> create_grid() {
        string line;
        _input >> line;
        vector<vector<int>> grid;
        grid.emplace_back(line.length() + 2, -1);
        grid.push_back(row_from_line(line));
        while (_input >> line) {
            if (line.empty()) {
                continue;
            }
            grid.push_back(row_from_line(line));
        }
        grid.emplace_back(line.length() + 2, -1);
        return grid;
    }

    static void process_grid(vector<vector<int>> &grid, map<tuple<size_t, size_t>, vector<int>> &star_map,
                             int &sum_part_numbers) {
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
                    if (num_len > 0 and find_symbols(grid, j - num_len - 1, i - 1, j, i + 1,
                                                     star_map, num)) {
                        sum_part_numbers += num;
                    }
                    num = 0;
                    num_len = 0;
                }
            }
        }
    }

    static bool find_symbols(vector<vector<int>> &grid, size_t start_x, size_t start_y, size_t end_x, size_t end_y,
                             map<tuple<size_t, size_t>, vector<int>> &star_map, int num) {
        bool output = false;
        for (size_t i = start_y; i <= end_y; ++i) {
            for (size_t j = start_x; j <= end_x; ++j) {
                tuple<size_t, size_t> coords(i, j);
                switch (grid[i][j]) {
                    case STAR:
                        if (!star_map.contains(coords))
                            star_map[coords] = vector<int>{};
                        star_map[coords].push_back(num);
                    case SYMBOL:
                        output = true;
                }

            }
        }
        return output;
    }

    static const int EMPTY {-1};
    static const int STAR {-2};
    static const int SYMBOL {-3};
};


#endif //AOC2023_DAY03_H
