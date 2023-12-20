//
// Created by ivana.krumlova on 19.12.2023.
//

#ifndef AOC2023_DAY19_H
#define AOC2023_DAY19_H


#include <functional>
#include <regex>
#include <utility>
#include "../infra/Task.h"

class Day19: public Task{
public:
    Day19(string name, const string& in_file) : Task(std::move(name), in_file) {};
    void run1(bool print_result) override {
        unordered_map<string, Workflow> workflows{};
        vector<Part> parts{};
        parse_workflows(workflows);
        parse_parts(parts);

        long long sum_accepted{0};
        for (Part p:parts) {
            string curr_workflow = "in";
            int curr_pos = 0;
            while(curr_workflow != "A" and curr_workflow != "R") {
                if (workflows[curr_workflow][curr_pos](p)) {
                    curr_workflow = workflows[curr_workflow][curr_pos].direction;
                    curr_pos = 0;
                } else {
                    curr_pos++;
                }
            }
            if(curr_workflow == "A") {
                sum_accepted += p.rating();
            }
        }
        if(print_result) {
            cout << sum_accepted;
        }
    }
    void run2(bool print_result) override {
        unordered_map<string, Workflow> workflows{};
        parse_workflows(workflows);

        Part min_part(1, 1, 1, 1);
        Part max_part(4000, 4000, 4000, 4000);

        unsigned long long result = run_multipart(workflows, min_part, max_part, "in", 0);

        if(print_result) {
            cout << result;
        }
    }
private:
    struct Part {
        Part(int x, int m, int a, int s): p_ratings{{'x', x}, {'m', m}, {'a', a},{'s', s},} {};
        unordered_map<char, int> p_ratings{};
        int& operator[](char c) {
            return p_ratings[c];
        }
        int rating() {return p_ratings['x']+p_ratings['m']+p_ratings['a']+p_ratings['s'];}
    };
    struct Rule {
        Rule(char cmp, int bor, char qua, string dir): comparator{cmp}, border{bor}, quality{qua}, direction(std::move(dir)) {};
        char comparator; // '<' or '>' or 'N' for no comparison
        int border;
        char quality; // x m a s
        string direction;
        bool operator()(Part p ) const {
            if (comparator == '<') {
                return p[quality] < border;
            } else if (comparator == '>') {
                return p[quality] > border;
            }
            return true;
        }
    };
    typedef vector<Rule> Workflow;

    void parse_workflows(unordered_map<string, Workflow> &workflows) {
        smatch sm;
        string line;
        regex rule_regex{R"(([xmas])([<>])(\d+):(\w{1,3}))"};
        while (getline(_input, line) && !line.empty()) {
            string wf_name{};
            for (int i = 0; i < line.size() and line[i] != '{'; ++i) {
                wf_name += line[i];
            }
            Workflow wf{};
            sregex_iterator iter(line.begin(), line.end(), rule_regex);
            sregex_iterator end;
            while (iter != end) {
                wf.emplace_back((*iter)[2].str()[0], stoi((*iter)[3]),
                                (*iter)[1].str()[0], (*iter)[4].str());
                iter++;
            }
            string final_move{};
            for (int i = line.size()-2; i >0 and line[i] != ','; --i) {
                final_move = line[i] + final_move;
            }
            wf.emplace_back('N', 0, 'x', final_move);
            workflows[wf_name] = wf;
        }

    }
    void parse_parts(vector<Part> &parts) {
        smatch sm;
        string line;
        regex part_regex{R"(\{x=(\d+),m=(\d+),a=(\d+),s=(\d+)\})"};
        while (getline(_input, line)) {
            regex_match(line, sm, part_regex);
            parts.emplace_back(stoi(sm[1]), stoi(sm[2]), stoi(sm[3]), stoi(sm[4]));
        }
    }
    unsigned long long run_multipart(unordered_map<string, Workflow> &workflows, Part &min_part, Part &max_part,
                      string start_wf, int start_index) {
        for(char c:"xmas") {
            if(max_part[c] < min_part[c]) {
                return 0;
            }
        }
        if(start_wf == "A") {
            return ((unsigned long long) max_part['x']-min_part['x'] + 1) * (max_part['m']-min_part['m'] + 1) *
                    (max_part['a']-min_part['a'] + 1) * (max_part['s']-min_part['s'] + 1);
        }
        if(start_wf == "R") {
            return 0;
        }
        Rule curr_rule = workflows[start_wf][start_index];
        if(curr_rule(min_part) == curr_rule(max_part)) {
            if(curr_rule(min_part)) {
                return run_multipart(workflows, min_part, max_part, curr_rule.direction, 0);
            }
            return run_multipart(workflows, min_part, max_part, start_wf, start_index+1);
        }
        Part new_max = max_part;
        new_max[curr_rule.quality] = curr_rule.border-1;
        Part new_min = min_part;
        new_min[curr_rule.quality] = curr_rule.border+1;
        Part middle_max = max_part;
        middle_max[curr_rule.quality] = curr_rule.border;
        Part middle_min = min_part;
        middle_min[curr_rule.quality] = curr_rule.border;

        return run_multipart(workflows, min_part, new_max, start_wf, start_index) +
                run_multipart(workflows, new_min, max_part, start_wf, start_index) +
                run_multipart(workflows, middle_min, middle_max, start_wf, start_index);
    }
};


#endif //AOC2023_DAY19_H
