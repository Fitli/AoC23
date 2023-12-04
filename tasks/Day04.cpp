//
// Created by ivana.krumlova on 4.12.2023.
//

#include <iostream>
#include <regex>
#include <set>
#include <cmath>
#include "Day04.h"

Card Day04::parse_line(string &line) {
    sregex_iterator iter(line.begin(), line.end(), R);
    sregex_iterator end;
    Card card(stoi(iter->str()));
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

void Day04::run1(bool print_result) {
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

void Day04::run2(bool print_result) {
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
