//
// Created by ivana.krumlova on 13.12.2023.
//

#ifndef AOC2023_DAY13_H
#define AOC2023_DAY13_H

#include <algorithm>
#include "../infra/Task.h"

class Day13 : public Task{
public:
    Day13(string name, const string& in_file) : Task(std::move(name), in_file) {};
    void run1(bool print_result) override {
        vector<long long> row_vals;
        vector<long long> col_vals;
        long long max_row_val;
        long long max_col_val;
        int sum{};
        while(parse(row_vals, col_vals, max_row_val, max_col_val)){
            sum += 100*find_mirror(row_vals);
            sum += find_mirror(col_vals);
        }
        if(print_result) {
            cout << sum << endl;
        }
    }

    void run2(bool print_result) override {
        vector<long long> row_vals;
        vector<long long> col_vals;
        long long max_row_val;
        long long max_col_val;
        int sum{};
        while(parse(row_vals, col_vals, max_row_val, max_col_val)){
            sum += 100*find_mirror2(row_vals);
            sum += find_mirror2(col_vals);
        }
        if(print_result) {
            cout << sum << endl;
        }
    }
private:
    bool parse(vector<long long> &row_vals, vector<long long> &col_vals, long long &max_row_val, long long &max_col_val) {
        string line;
        row_vals = vector<long long>();
        col_vals = vector<long long>();
        max_row_val = 1;
        max_col_val = 1;
        while(getline(_input, line) and !line.empty()) {
            if(col_vals.empty()) {
                col_vals = vector<long long>(line.size(), 0);
                max_row_val = 1 << (line.size()+1);
            }
            max_col_val <<= 1;
            long long n = 0;
            for (int i = 0; i < line.size(); ++i) {
                col_vals[i] <<= 1;
                n <<= 1;
                if(line[i] == '#') {
                    col_vals[i]++;
                    n++;
                }
            }
            row_vals.push_back(n);
        }
        if(!row_vals.empty()) {
            return true;
        }
        return false;
    }
    static int find_mirror(const vector<long long>& values) {
        for (int i = 1; i < values.size(); ++i) {
            int width = min(i, (int)values.size()-i);
            bool is_mirror = true;
            for (int j = 0; j < width; ++j) {
                if(values[i-1-j] != values[i+j]) {
                    is_mirror = false;
                    break;
                }
            }
            if (is_mirror) {
                return i;
            }
        }
        return 0;
    }
    static int find_mirror2(const vector<long long>& values) {
        for (int i = 1; i < values.size(); ++i) {
            int width = min(i, (int)values.size()-i);
            int num_diffs = 0;
            for (int j = 0; j < width; ++j) {
                num_diffs += count_num_diffs(values[i-1-j], values[i+j]);
            }
            if (num_diffs == 1) {
                return i;
            }
        }
        return 0;
    }
    static int count_num_diffs(long long a, long long b) {
        if (a==b) {
            return 0;
        }
        long long diff = a xor b;
        while(diff % 2 == 0) {
            diff >>= 1;
        }
        if(diff >> 1 == 0) {
            return 1;
        }
        return 2; // more than 1 :D
    }
};


#endif //AOC2023_DAY13_H
