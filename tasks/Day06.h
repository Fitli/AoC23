//
// Created by ivana.krumlova on 6.12.2023.
//

#ifndef AOC2023_DAY06_H
#define AOC2023_DAY06_H


#include <vector>
#include <iostream>
#include "../infra/Task.h"

class Day06: public Task {
public:
    Day06(string name, const string& in_file) : Task(std::move(name), in_file) {};
    void run1(bool print_result) override {
        vector<long long> times;
        vector<long long> distances;
        parse1(times, distances);

        long long result = 1;
        for (int i = 0; i < times.size(); ++i) {
            result *= get_num_ways(times[i], distances[i]);
        }
        if(print_result) {
            cout << result << endl;
        }
    }

    void run2(bool print_result) override {
        long long time;
        long long distance;
        parse2(time, distance);

        long long result = get_num_ways(time, distance);
        if(print_result) {
            cout << result << endl;
        }
    }
private:
    void parse1(vector<long long> &times, vector<long long> &distances) {
        string token;
        _input >> token;
        _input >> token;
        while(token != "Distance:") {
            times.push_back(stoll(token));
            _input >> token;
        }
        while(_input >> token) {
            distances.push_back(stoll(token));
        }
    }


    void parse2(long long &time, long long &distance) {
        string token;
        string big_num;
        _input >> token;
        _input >> token;
        while (token != "Distance:") {
            big_num += token;
            _input >> token;
        }
        time = stoll(big_num);
        big_num = "";
        while (_input >> token) {
            big_num += token;
        }
        distance = stoll(big_num);
    }

    static long long get_num_ways(long long time, long long distance) {
        long long min = 0;
        long long max = time/2 + 1;
        long long i = (min + max)/2;
        while(beats(i, time, distance) or (!beats(i+1, time, distance))) {
            if(beats(i, time, distance)) {
                max = i-1;
            }
            else {
                min = i+1;
            }
            i = (min + max)/2;
        }
        i++;
        return time + 1 - 2*i;
    }

    static bool beats(long long press, long long time, long long distance) {
        return (press * (time-press) > distance);
    }
};


#endif //AOC2023_DAY06_H
