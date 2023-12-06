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
        Card card{};
        string _;
        _input >> _;
        while (parse_card(card)) {
            int num_matching = card.num_matching;
            if(num_matching > 0)
                sum += pow(2, num_matching-1);
        }
        if(print_result) {
            cout << sum << endl;
        }
    }
    void run2(bool print_result) override {
        string _;
        _input >> _;
        vector<Card> cards;
        Card card;
        int i = 0;
        do {
            cards.emplace_back();
            i++;
        } while (parse_card(cards[i-1]));
        cards.pop_back();
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
    bool parse_card(Card &card) {
        card.num_cards = 1;
        card.num_matching = 0;
        string token;
        if(!(_input >> token)) { //card number
            return false;
        }
        set<int> winning{};
        while (_input >> token and token != "|") {
            winning.insert(stoi(token));
        }
        while (_input >> token and token != "Card") {
            if (winning.contains(stoi(token))) {
                card.num_matching++;
            }
        }
        return true;
    }
    const regex R{"\\d+|\\|"};
};


#endif //AOC2023_DAY04_H
