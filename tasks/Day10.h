//
// Created by ivana.krumlova on 10.12.2023.
//

#ifndef AOC2023_DAY10_H
#define AOC2023_DAY10_H


#include "../infra/Task.h"

typedef tuple<int, int> shift2d;

class Day10: public Task {
public:
    Day10(string name, const string& in_file) : Task(std::move(name), in_file) {};
    void run1(bool print_result) override {
        vector<vector<char>> grid{};
        int S_x, S_y;
        parse_grid(grid, S_x, S_y);
        size_t height = grid.size();
        size_t width = grid[0].size();
        vector<shift2d> starting_dirs = {UP, DOWN, LEFT, RIGHT};
        for (shift2d dir:starting_dirs) {
            int count{};
            int x = S_x;
            int y = S_y;
            make_move(dir, x, y);
            count ++;
            while(true) {
                if (x < 0 or y < 0 or x >= width or y >= height) {
                    break;
                }
                if (grid[y][x] == 'S') {
                    if(print_result) {
                        cout << count/2 << endl;
                    }
                    return;
                }
                if (get_next_dir(grid[y][x], dir, dir)) {
                    make_move(dir, x, y);
                    count++;
                }
                else {
                    break;
                }
            }
        }
    }

    void run2(bool print_result) override {
        vector<vector<char>> grid{};
        int S_x, S_y;
        parse_grid(grid, S_x, S_y);
        size_t height = grid.size();
        size_t width = grid[0].size();
        vector<shift2d> starting_dirs = {UP, DOWN, LEFT, RIGHT};
        pair<shift2d, shift2d> right_dirs;
        for (shift2d dir:starting_dirs) {
            bool found_loop = false;
            right_dirs.first = dir;
            int count{};
            int x = S_x;
            int y = S_y;
            make_move(dir, x, y);
            count ++;
            while(true) {
                if (x < 0 or y < 0 or x >= width or y >= height) {
                    break;
                }
                if (grid[y][x] == 'S') {
                    right_dirs.second = {get<0>(dir)*-1, get<1>(dir)*-1};
                    found_loop = true;
                    break;
                }
                if (get_next_dir(grid[y][x], dir, dir)) {
                    make_move(dir, x, y);
                    count++;
                }
                else {
                    break;
                }
            }
            if(found_loop) {
                break;
            }
        }
        vector<vector<Type>> type_grid;
        for (int i = 0; i < 3*height; ++i) {
            type_grid.emplace_back(3*width, UNKNOWN);
        }
        type_grid[3*S_y+1][3*S_x+1] = LINE;
        type_grid[3*S_y+1 + get<1>(right_dirs.first)][3*S_x+1 + get<0>(right_dirs.first)] = LINE;
        type_grid[3*S_y+1 + get<1>(right_dirs.second)][3*S_x+1 + get<0>(right_dirs.second)] = LINE;
        shift2d dir = right_dirs.first;
        int x = S_x;
        int y = S_y;
        make_move(dir, x, y);
        while(grid[y][x] != 'S') {
            type_grid[3*y+1][3*x+1] = LINE;
            switch(grid[y][x]) {
                case 'L':
                    type_grid[3*y][3*x+1] = LINE;
                    type_grid[3*y+1][3*x+2] = LINE;
                    break;
                case 'J':
                    type_grid[3*y][3*x+1] = LINE;
                    type_grid[3*y+1][3*x] = LINE;
                    break;
                case '7':
                    type_grid[3*y+2][3*x+1] = LINE;
                    type_grid[3*y+1][3*x] = LINE;
                    break;
                case 'F':
                    type_grid[3*y+2][3*x+1] = LINE;
                    type_grid[3*y+1][3*x+2] = LINE;
                    break;
                case '-':
                    type_grid[3*y+1][3*x] = LINE;
                    type_grid[3*y+1][3*x+2] = LINE;
                    break;
                case '|':
                    type_grid[3*y][3*x+1] = LINE;
                    type_grid[3*y+2][3*x+1] = LINE;
                    break;
            }
            get_next_dir(grid[y][x], dir, dir);
            make_move(dir, x, y);
        }
        fill(type_grid, 0, 0, OUTSIDE);
        //print_type_grid(type_grid);
        int count{};
        for (y = 0; y < height; ++y) {
            for (x = 0; x < width; ++x) {
                if(type_grid[3*y+1][3*x+1] == UNKNOWN) {
                    count++;
                }
            }
        }
        if(print_result) {
            cout << count << endl;
        }
    }
private:
    void parse_grid(vector<vector<char>> &grid, int &S_x, int &S_y) {
        string line;
        int x{}, y{};
        while(getline(_input, line)) {
            vector<char> v{};
            for (char c:line) {
                if(c=='S') {
                    S_x = x;
                    S_y = y;
                }
                v.push_back(c);
                x++;
            }
            grid.push_back(v);
            y++;
            x=0;
        }
    }

    bool get_next_dir(const char &pipe, shift2d curr_dir, shift2d &next_dir) {
        if (pipe == '.') {
            return false;
        }
        if (pipe == 'L') {
            if(curr_dir == DOWN) {
                next_dir = RIGHT;
                return true;
            }
            if(curr_dir == LEFT) {
                next_dir = UP;
                return true;
            }
            return false;
        }
        if (pipe == 'J') {
            if(curr_dir == DOWN) {
                next_dir = LEFT;
                return true;
            }
            if(curr_dir == RIGHT) {
                next_dir = UP;
                return true;
            }
            return false;
        }
        if (pipe == '7') {
            if(curr_dir == RIGHT) {
                next_dir = DOWN;
                return true;
            }
            if(curr_dir == UP) {
                next_dir = LEFT;
                return true;
            }
            return false;
        }
        if (pipe == 'F') {
            if(curr_dir == LEFT) {
                next_dir = DOWN;
                return true;
            }
            if(curr_dir == UP) {
                next_dir = RIGHT;
                return true;
            }
            return false;
        }
        if (pipe == '|') {
            if(curr_dir == DOWN or curr_dir == UP) {
                next_dir = curr_dir;
                return true;
            }
            return false;
        }
        if (pipe == '-') {
            if(curr_dir == LEFT or curr_dir == RIGHT) {
                next_dir = curr_dir;
                return true;
            }
            return false;
        }
    }

    static void make_move(const shift2d &shift, int &x, int &y) {
        x += get<0>(shift);
        y += get<1>(shift);
    }

    enum Type {LINE, OUTSIDE, UNKNOWN};

    void fill(vector<vector<Type>> &type_grid, int start_x, int start_y, Type val){
        vector<tuple<int, int>> to_fill{tuple<int, int>(start_x, start_y)};
        while (!to_fill.empty()) {
            auto coords = to_fill.back();
            to_fill.pop_back();
            const auto [x, y] = coords;
            if(x < 0 or y < 0 or y >= type_grid.size() or x >= type_grid[y].size() or
               type_grid[y][x] == LINE or type_grid[y][x] == val) {
                continue;
            }
            type_grid[y][x] = val;
            to_fill.emplace_back(x+1,y);
            to_fill.emplace_back(x-1,y);
            to_fill.emplace_back(x,y+1);
            to_fill.emplace_back(x,y-1);
        }
    }
    static void print_type_grid(vector<vector<Type>> &type_grid) {
        for (auto l:type_grid) {
            for (Type t:l) {
                if(t==UNKNOWN) {
                    cout << ".";
                }
                if(t==OUTSIDE) {
                    cout << "O";
                }
                if(t==LINE) {
                    cout << "x";
                }
            }
            cout <<endl;
        }
    }
    shift2d UP{0,-1};
    shift2d DOWN{0,1};
    shift2d LEFT{-1, 0};
    shift2d RIGHT{1,0};
};


#endif //AOC2023_DAY10_H
