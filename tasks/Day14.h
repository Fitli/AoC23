//
// Created by ivana.krumlova on 14.12.2023.
//

#ifndef AOC2023_DAY14_H
#define AOC2023_DAY14_H


#include <unordered_map>
#include "../infra/Task.h"

class Day14: public Task{
public:
    Day14(string name, const string& in_file) : Task(std::move(name), in_file) {};
    void run1(bool print_result) override {
        vector<vector<char>> grid;
        parse(grid);
        long long result{};
        /*for (int i = 1; i < grid[0].size()-1; ++i) {
            int carying = 0;
            for (int j = (int) grid.size()-2; j >= 0; --j) {
                switch (grid[j][i]) {
                    case 'O':
                        carying++;
                        break;
                    case '#':
                        result += carying*(carying+1)/2 + carying * ((int) grid.size() - j - carying - 2);
                        carying = 0;
                        break;
                }
            }
        }*/
        fall(grid, pair<int, int>(0, -1));
        result = north_weight(grid);
        if (print_result) {
            cout << result;
        }
    }
    void run2(bool print_result) override {
        vector<vector<char>> grid;
        parse(grid);
        vector<pair<int, int>> directions {{0, -1},
                                           {-1, 0},
                                           {0, 1},
                                           {1, 0}};
        unordered_map<string, int> memory{};
        for (int i = 0; i < 1000000000; ++i) {
            for (auto d:directions) {
                fall(grid, d);
            }
            string g = grid_to_string(grid);
            if(memory.contains(g)) {
                int cycle_len = i - memory[g];
                i += ((1000000000 - i) / cycle_len) * cycle_len;
            }
            memory[g] = i;
        }
        if (print_result) {
            cout << north_weight(grid);
        }
    }
private:
    void parse(vector<vector<char>> &grid) {
        string line;
        bool first = true;
        size_t l;
        while(getline(_input, line)) {
            if (first) {
                l = line.length() + 2;
                grid.emplace_back(l, '#');
                first = false;
            }
            vector<char> line_vec;
            line_vec.push_back('#');
            for (char &c:line) {
                line_vec.push_back(c);
            }
            line_vec.push_back('#');
            grid.push_back(line_vec);
        }
        grid.emplace_back(l, '#');
    }

    static int north_weight(vector<vector<char>> &grid) {
        int weight = 0;
        for (size_t i = 1; i < grid.size()-1; ++i) {
            for (char &c:grid[i]) {
                if(c == 'O') {
                    weight += (int) (grid.size() - i - 1);
                }
            }
        }
        return weight;
    }

    static void fall(vector<vector<char>> &grid, pair<int, int> direction) {
        auto [dir_x, dir_y] = direction;
        vector<pair<int, int>> starting_points{};
        if(dir_x == 0) {
            for (size_t i = 1; i < grid[0].size() - 1; ++i) {
                starting_points.emplace_back(i, dir_y==1?1:grid.size()-1);
            }
        }
        else {
            for (size_t i = 1; i < grid.size() - 1; ++i) {
                starting_points.emplace_back(dir_x==1?1:grid[0].size()-1, i);
            }
        }
        for (auto p: starting_points) {
            auto [x,y] = p;
            int carying{0};
            while(x >= 0 and y >= 0 and y < grid.size() and x < grid[0].size()) {
                if(grid[y][x] == 'O') {
                    carying += 1;
                    grid[y][x]='.';
                }
                if(grid[y][x] == '#') {
                    for (int i = 1; i <= carying; ++i) {
                        grid[y - i*dir_y][x - i*dir_x] = 'O';
                    }
                    carying = 0;
                }
                x += dir_x;
                y += dir_y;
            }
        }
    }
    static string grid_to_string(vector<vector<char>> &grid) {
        string res{};
        for (auto &l:grid) {
            for (char c:l) {
                res += c;
            }
        }
        return res;
    }
};


#endif //AOC2023_DAY14_H
