//
// Created by ivana.krumlova on 5.12.2023.
//

#ifndef AOC2023_DAY05_H
#define AOC2023_DAY05_H

#include <string>
#include <utility>
#include <vector>
#include <regex>
#include <iostream>
#include <set>
#include "../infra/Task.h"

using namespace std;

class ResourceMap {
public:
    ResourceMap() {};
    map<tuple<long long, long long>, long long> mapping{};
    string from;
    string to;
};

class Day05: public Task {
public:
    Day05(string name, const string& in_file) : Task(std::move(name), in_file) {
        string resource_regex_str;
        for (const string& res: resources) {
            resource_regex_str += res + "|";
        }
        resource_regex_str.pop_back();
        resource_regex = regex("(" + resource_regex_str + ")-to-(" + resource_regex_str + ") map:");
    };
    void run1(bool print_result) override {
        vector<long long> seeds = parse_seeds();
        string _;
        getline(_input, _);
        ResourceMap rm;
        map<tuple<string, string>, ResourceMap> resource_maps{};
        while(parse_map(rm)) {
            resource_maps[tuple<string, string>(rm.from, rm.to)] = rm;
        }
        vector<long long> locations;
        for (long long seed: seeds) {
            long long num = seed;
            for (int i = 0; i < resources.size() - 1; ++i) {
                ResourceMap &curr_map = resource_maps[tuple<string, string>(resources[i], resources[i + 1])];
                for (auto interval: curr_map.mapping) {
                    const auto [start, end] = interval.first;
                    long long maps_to = interval.second;
                    if(num >= start and num < end) {
                        num += maps_to;
                        break;
                    }
                }
            }
            locations.push_back(num);
        }
        long long minimum = *min_element(locations.begin(), locations.end());
        if(print_result) {
            cout << minimum << endl;
        }
    }

    void run2(bool print_result) override {
        vector<long long> seeds = parse_seeds();
        string _;
        getline(_input, _);
        ResourceMap rm;
        map<tuple<string, string>, ResourceMap> resource_maps{};
        while(parse_map(rm)) {
            resource_maps[tuple<string, string>(rm.from, rm.to)] = rm;
        }
        set<tuple<long long, long long>> intervals;
        for (int i = 0; i < seeds.size()/2; ++i) {
            intervals.emplace(seeds[2*i], seeds[2*i] + seeds[2*i+1]);
        }
        for (int i = 0; i < resources.size() - 1; ++i) {
            ResourceMap &curr_map = resource_maps[tuple<string, string>(resources[i], resources[i + 1])];
            set<tuple<long long, long long>> new_intervals;
            while(!intervals.empty()) {
                bool found_overlap = false;
                auto interval = *intervals.begin();
                intervals.erase(intervals.begin());
                const auto [i_start, i_end] = interval;
                for (auto map_interval: curr_map.mapping) {
                    const auto [m_start, m_end] = map_interval.first;
                    auto maps_to = map_interval.second;
                    if(m_end<=i_start or m_start >= i_end)
                        continue;
                    found_overlap = true;
                    if(i_start >= m_start and i_end <= m_end) {
                        new_intervals.emplace(i_start + maps_to, i_end + maps_to);
                        break;
                    }
                    if(i_start >= m_start) {
                        new_intervals.emplace(i_start + maps_to, m_end + maps_to);
                        intervals.emplace(m_end, i_end);
                        break;
                    }
                    if(i_end <= m_end){
                        new_intervals.emplace(m_start+maps_to, i_end+maps_to);
                        intervals.emplace(i_start, m_start);
                        break;
                    }
                }
                if(!found_overlap) {
                    new_intervals.insert(interval);
                }
            }
            intervals = new_intervals;
        }
        auto min_interval = *min_element(intervals.begin(), intervals.end());
        if(print_result) {
            cout << get<0>(min_interval) << endl;
        }
    }
private:
    vector<string> resources {"seed", "soil", "fertilizer", "water", "light", "temperature", "humidity", "location"};
    regex seed_regex{" (\\d+)"};
    regex resource_regex;

    vector<long long> parse_seeds() {
        string line;
        getline(_input, line);
        vector<long long> numbers;
        sregex_iterator iter(line.begin(), line.end(), seed_regex);
        sregex_iterator end;
        while(iter != end) {
            numbers.push_back(stoll((*iter)[1].str()));
            iter++;
        }
        return numbers;
    };

    bool parse_map(ResourceMap &rm) {
        rm.mapping.clear();
        string line;
        if(!getline(_input, line) or line.empty())
            return false;
        smatch sm;
        regex_search(line, sm, resource_regex);
        rm.from = sm[1].str();
        rm.to = sm[2].str();
        getline(_input, line);
        while(!line.empty()) {
            regex_search(line, sm, regex(R"((\d+) (\d+) (\d+))"));
            long long start = stoll(sm[2].str());
            rm.mapping[tuple<long long, long long>(start,
                                                   start + stoll(sm[3].str()))] = stoll(sm[1].str())-start;
            getline(_input, line);
        }
        return true;
    }
};


#endif //AOC2023_DAY05_H
