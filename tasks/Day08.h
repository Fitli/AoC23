//
// Created by ivana.krumlova on 8.12.2023.
//

#ifndef AOC2023_DAY08_H
#define AOC2023_DAY08_H

#include <string>
#include <regex>
#include <numeric>
#include <utility>
#include "../infra/Task.h"

class Day08: public Task {
public:
    Day08(string name, const string& in_file) : Task(std::move(name), in_file) {};
    void run1(bool print_result) override {
        string directions;
        _input >> directions;
        map<string, pair<string, string>> graph;
        parse_graph(graph);
        int result = navigate(graph, directions, "AAA");
        if(print_result) {
            cout << result << endl;
        }
    }
    void run2(bool print_result) override {
        /**
         * To je ale dementní
         */
        string directions;
        _input >> directions;
        map<string, pair<string, string>> graph;
        parse_graph(graph);
        vector<int> distances{};
        for (const auto &v:graph) {
            if(v.first[2] == 'A') {
                distances.push_back(navigate(graph, directions, v.first));
            }
        }
        long long result = 1;
        for (int n:distances) {
            result = lcm(result, n);
        }
        if(print_result) {
            cout << result << endl;
        }
    }
private:
    void parse_graph(map<string, pair<string, string>> &graph) {
        string line;
        smatch sm;
        while(getline(_input, line)) {
            if(line.empty()) {
                continue;
            }
            regex_match(line, sm, line_regex);
            graph[sm[1]] = {sm[2], sm[3]};
        }
    }
    static int navigate(map<string, pair<string, string>> &graph, string &directions, string starting_position) {
        int steps = 0;
        string position = std::move(starting_position);
        while(position[2] != 'Z') {
            char d = directions[steps % directions.size()];
            if(d=='L')
                position = graph[position].first;
            else
                position = graph[position].second;
            steps++;
        }
        return steps;
    };

    // EXPLORE FUNCTIONS
    static int reachable_from(map<string, pair<string, string>> &graph, map<string, pair<string, string>> &sub_graph,
                              string start) {
        int steps = 0;
        vector<string> queue{start};
        while(!queue.empty()) {
            string position = queue.back();
            if(sub_graph.contains(position)) {
                queue.pop_back();
                continue;
            }
            string left = graph[position].first;
            string right = graph[position].second;
            sub_graph[position] = pair<string, string>(left, right);
            queue.pop_back();
            queue.push_back(right);
            queue.push_back(left);
        }
        return steps;

    };
    static void graph_to_dot(map<string, pair<string, string>> &graph, const string& ofname) {
        ofstream dot_file(ofname);
        for(const auto& e:graph) {
            dot_file << e.first << "->" << e.second.first << ";" << endl;
            dot_file << e.first << "->" << e.second.second << "[color=red];" << endl;
        }
    }
    regex line_regex{"([A-Z]{3}) = \\(([A-Z]{3}), ([A-Z]{3})\\)"};
};


#endif //AOC2023_DAY08_H
