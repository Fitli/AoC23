//
// Created by ivana.krumlova on 7.12.2023.
//

#ifndef AOC2023_DAY07_H
#define AOC2023_DAY07_H

#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include "../infra/Task.h"

using namespace std;

class CamelCard {
public:
    CamelCard(const string& values, int bid_) {
        string_values = values;
        bid = bid_;
        type = get_type(values);
    }
    static int get_type(const string& values) {
        map<char, int> counts;
        for(const char &c:values) {
            if(counts.contains(c)) {
                counts[c]++;
            }
            else {
                counts[c] = 1;
            }
        }
        int max_count = 0;
        for(auto e:counts) {
            if(e.second > max_count)
                max_count = e.second;
        }
        switch (counts.size()) {
            case 5:
                if (counts.contains('1')) {
                    return 2;
                }
                return 1;
            case 4:
                if (counts.contains('1')) {
                    return 4;
                }
                return 2;
            case 3:
                if (counts.contains('1')) {
                    return (counts['1'] == 1 and max_count == 2)?5:6;
                }
                return (max_count == 2) ? 3 : 4;
            case 2:
                if (counts.contains('1')) {
                    return 7;
                }
                return (max_count == 3) ? 5 : 6;
            case 1:
                return 7;
        }
    }
    static int char_to_val(char c) {
        if('0' <= c and '9' >= c) {
            return c-'0';
        }
        switch(c) {
            case 'T':
                return 10;
            case 'J':
                return 11;
            case 'Q':
                return 12;
            case 'K':
                return 13;
            case 'A':
                return 14;
        }
    }

    int bid;
    string string_values;
    int type;
};


bool operator< (const CamelCard& c1, const CamelCard& c2)
{
    if(c1.type != c2.type) {
        return c1.type < c2.type;
    }
    for (int i = 0; i < 5; ++i) {
        if(c1.string_values[i] == c2.string_values[i]) {
            continue;
        }
        return CamelCard::char_to_val(c1.string_values[i]) < CamelCard::char_to_val(c2.string_values[i]);
    }
}

class Day07: public Task {
public:
    Day07(string name, const string& in_file) : Task(std::move(name), in_file) {};
    void run1(bool print_result) override {
        long long result = run(false);
        if(print_result) {
            cout << result << endl;
        }
    }

    void run2(bool print_result) override {
        long long result = run(true);
        if(print_result) {
            cout << result << endl;
        }
    }

private:
    long long run(bool task_2) {
        vector<CamelCard> cards;
        string values;
        string bid;
        while(_input >> values) {
            _input >> bid;
            if(task_2)
            {
                for (int i = 0; i < 5; ++i) {
                    if (values[i] == 'J') {
                        values[i] = '1';
                    }
                }
            }
            cards.emplace_back(values, stoi(bid));
        }
        sort(cards.begin(), cards.end());
        long long sum = 0;
        for (int i = 0; i < cards.size(); ++i) {
            sum += (i+1)*cards[i].bid;
        }
        return sum;
    }
};

#endif //AOC2023_DAY07_H
