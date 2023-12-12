//
// Created by ivana.krumlova on 12.12.2023.
//

#ifndef AOC2023_DAY12_H
#define AOC2023_DAY12_H


#include <unordered_map>
#include "../infra/Task.h"

class Day12 : public Task {
public:
    Day12(string name, const string& in_file) : Task(std::move(name), in_file) {};
    void run1(bool print_result) override {
        string line;
        long long sum = 0;
        while (getline(_input, line)) {
            string streams;
            vector<int> lengths;
            parse_line(line, streams, lengths);
            unordered_map<int, unordered_map<int, long long>> cache;
            long long sols = possible_solutions(streams, lengths, 0, 0, cache);
            sum += sols;
        }
        if(print_result) {
            cout << sum << endl;
        }
    }
    void run2(bool print_result) override {
        string line;
        long long sum = 0;
        while (getline(_input, line)) {
            string streams;
            vector<int> lengths;
            parse_line2(line, streams, lengths);
            unordered_map<int, unordered_map<int, long long>> cache;
            long long sols = possible_solutions(streams, lengths, 0, 0, cache);
            sum += sols;
        }
        if(print_result) {
            cout << sum << endl;
        }
    }
private:
    static void parse_line(const string &line, string &streams, vector<int> &lengths) {
        stringstream line_stream(line);
        line_stream >> streams;
        string nums;
        line_stream>>nums;
        int n{};
        for (char c:nums) {
            if (c == ',') {
                lengths.push_back(n);
                n = 0;
            }
            else {
                n *= 10;
                n += c-'0';
            }
        }
        lengths.push_back(n);
    }
    static void parse_line2(const string &line, string &streams, vector<int> &lengths) {
        stringstream line_stream(line);
        string s;
        line_stream >> s;
        streams = s;
        for (int i = 0; i < 4; ++i) {
            streams += "?";
            streams += s;
        }
        string nums;
        vector<int> ns;
        line_stream>>nums;
        int n{};
        for (char c:nums) {
            if (c == ',') {
                ns.push_back(n);
                n = 0;
            }
            else {
                n *= 10;
                n += c-'0';
            }
        }
        ns.push_back(n);
        for (int i = 0; i < 5; ++i) {
            lengths.insert(lengths.end(), ns.begin(), ns.end());
        }
    }
    long long possible_solutions(string &streams, vector<int> &lengths, int streams_start, int lengths_start,
                                 unordered_map<int, unordered_map<int, long long>> &cache) {
        if(cache.contains(streams_start) and cache[streams_start].contains(lengths_start)) {
            return cache[streams_start][lengths_start];
        }
        if(!cache.contains(streams_start)) {
            cache[streams_start] = unordered_map<int, long long>{};
        }
        if (streams_start >= streams.length()) {
            if(lengths_start == lengths.size() and streams_start == streams.size()) {
                cache[streams_start][lengths_start] = 1;
                return 1;
            }
            else {
                cache[streams_start][lengths_start] = 0;
                return 0;
            }
        }
        if(lengths_start >= lengths.size() and streams[streams_start] == '#') {
            cache[streams_start][lengths_start] = 0;
            return 0;
        }
        long long count = 0;
        if (streams[streams_start] != '#') {
            count += possible_solutions(streams, lengths, streams_start+1, lengths_start, cache);
        }
        if (streams[streams_start] != '.' and streams_start + lengths[lengths_start] <= streams.size()) {
            bool can_start = true;
            for (int i = 0; i < lengths[lengths_start]; ++i) {
                if(streams[streams_start + i] == '.')
                    can_start = false;
            }
            if (streams_start + lengths[lengths_start] < streams.size() and streams[streams_start + lengths[lengths_start]] == '#') {
                can_start = false;
            }
            if (can_start) {
                if(streams_start + lengths[lengths_start] == streams.size() and lengths_start+1 == lengths.size()) {
                    count += 1;
                }
                else {
                    count += possible_solutions(streams, lengths,
                                                streams_start + lengths[lengths_start] + 1,
                                                lengths_start + 1, cache);
                }
            }
        }
        cache[streams_start][lengths_start] = count;
        return count;
    }

};


#endif //AOC2023_DAY12_H
