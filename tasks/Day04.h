//
// Created by ivana.krumlova on 4.12.2023.
//

#ifndef AOC2023_DAY04_H
#define AOC2023_DAY04_H

#include <cmath>
#include <set>
#include "../infra/Task.h"

class Card {
public:
    int num_matching{0};
    int num_cards{1};
};

class Day04: public Task {
public:
    Day04(string name, const string& in_file) : Task(std::move(name), in_file) { };
    void run1(bool print_result) override {
        int sum = 0;
        string line;
        while (getline(_input, line)) {
            int num_matching = parse_line(line).num_matching;
            if(num_matching > 0)
                sum += pow(2, num_matching-1);
        }
        if(print_result) {
            cout << sum << endl;
        }
    }
    void run2(bool print_result) override {
        string line;
        vector<Card> cards;
        while (getline(_input, line)) {
            cards.push_back(parse_line(line));
        }
        int total_sum = 0;
        for (int i = 0; i < cards.size(); ++i) {
            total_sum += cards[i].num_cards;
            for (int j = 1; j <= cards[i].num_matching and j <= cards.size(); ++j) {
                cards[i+j].num_cards += cards[i].num_cards;
            }
        }
        if(print_result) {
            cout << total_sum << endl;
        }
    }
private:
    Card parse_line(string &line) {
        sregex_iterator iter(line.begin(), line.end(), R);
        sregex_iterator end;
        Card card;
        iter++;
        set<int> winning{};
        while (iter->str() != "|") {
            winning.insert(stoi(iter->str()));
            iter++;
        }
        iter++;
        while(iter != end) {
            if(winning.contains(stoi(iter->str()))) {
                card.num_matching++;
            }
            iter++;
        }

        return card;
    }
    const regex R{"\\d+|\\|"};
};


#endif //AOC2023_DAY04_H
