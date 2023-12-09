//
// Created by ivana.krumlova on 9.12.2023.
//

#ifndef AOC2023_DAY09_H
#define AOC2023_DAY09_H


#include <algorithm>
#include <numeric>
#include "../infra/Task.h"

class Day09: public Task {
public:
    Day09(string name, const string& in_file) : Task(std::move(name), in_file) {}
    void run1(bool print_result) override {
        run(print_result, false);
    }
    void run2(bool print_result) override {
        run(print_result, true);
    }
private:
    void run(bool print_result, bool rev) {
        string line;
        int sum{};
        while(getline(_input, line)) {
            int val = eval_line(line, rev);
            sum += val;
        }
        if(print_result) {
            cout << sum << endl;
        }
    }
    static int eval_line(string &line, bool rev=false) {
        vector<int> numbers;
        parse_line(line, numbers);
        if (rev) {
            reverse(numbers.begin(), numbers.end());
        }
        vector<int> last_elems;
        while(!all_of(numbers.begin(), numbers.end(), [](int i) { return i == 0; })) {
            last_elems.push_back(numbers.back());
            numbers = get_diffs(numbers);
        }
        return reduce(last_elems.begin(), last_elems.end());
    }

    static void parse_line(string &line, vector<int> &numbers) {
        stringstream line_stream(line);
        string tok;
        while(line_stream >> tok) {
            numbers.push_back(stoi(tok));
        }
    }

    static vector<int> get_diffs(vector<int> &numbers) {
        vector<int> diffs{};
        for(int i=1; i<numbers.size(); i++) {
            diffs.push_back(numbers[i]-numbers[i-1]);
        }
        return diffs;
    }
};


#endif //AOC2023_DAY09_H
