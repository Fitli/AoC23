//
// Created by ivana.krumlova on 11.12.2023.
//

#ifndef AOC2023_DAY11_H
#define AOC2023_DAY11_H


#include "../infra/Task.h"

class Day11: public Task {
public:
    Day11(string name, const string& in_file) : Task(std::move(name), in_file) {};
    void run1(bool print_result) override {
        run(print_result, 2);
    }
    void run2(bool print_result) override {
        run(print_result, 1000000);
    }
private:
    void parse_grid(vector<string> &grid) {
        string line;
        while (getline(_input, line)) {
            grid.push_back(line);
        }
    }
    static int count_galaxies(vector<string> &grid) {
        int count = 0;
        for (const string& l:grid) {
            count += count_galaxies_row(l);
        }
        return count;
    }
    static int count_galaxies_row(const string &row) {
        int count = 0;
        for (const char &c:row) {
            if(c == '#') {
                count++;
            }
        }
        return count;
    }
    static int count_galaxies_column(vector<string> &grid, int col_index) {
        int count = 0;
        for (const string &r:grid) {
            if(r[col_index] == '#') {
                count++;
            }
        }
        return count;
    }
    void run(bool print_result, long long growing_factor) {
        vector<string> universe{};
        parse_grid(universe);
        long long sum_lengths = 0;
        int num_galaxies = count_galaxies(universe);
        long long before = 0;
        long long after = num_galaxies;
        for(const string& r:universe) {
            int galaxies_in_row = count_galaxies_row(r);
            after -= galaxies_in_row;
            before += galaxies_in_row;
            if(galaxies_in_row == 0) {
                sum_lengths += before*after*growing_factor;
            }
            else {
                sum_lengths += before * after;
            }
        }
        before = 0;
        after = num_galaxies;
        for (int i = 0; i < universe[0].size(); ++i) {
            int galaxies_in_col = count_galaxies_column(universe, i);
            after -= galaxies_in_col;
            before += galaxies_in_col;
            if(galaxies_in_col == 0) {
                sum_lengths += before*after*growing_factor;
            }
            else {
                sum_lengths += before * after;
            }
        }
        if(print_result) {
            cout << sum_lengths << endl;
        }
    }
};


#endif //AOC2023_DAY11_H
