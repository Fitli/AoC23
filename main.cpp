#include "infra/Task.h"
#include "tasks/Day01.h"
#include "tasks/Day02.h"
#include "tasks/Day03.h"
#include "tasks/Day04.h"
#include "tasks/Day05.h"
#include "tasks/Day06.h"
#include "tasks/Day07.h"

void generate_readme(string filename, vector<Task *> tasks) {
    ofstream readme(filename);
    readme << "|\t| Solution \t| Execution time part 1\t | Execution time part 2\t|" << endl;
    readme <<"|---------|---|---|---|" << endl;
    for(Task *task:tasks) {
        task->write_readme_line(readme);
    }
}

int main()
{
    Day01 d1 = Day01("Day01", "../input/input01.txt");
    Day02 d2 = Day02("Day02", "../input/input02.txt");
    Day03 d3 = Day03("Day03", "../input/input03.txt");
    Day04 d4 = Day04("Day04", "../input/input04.txt");
    Day05 d5 = Day05("Day05", "../input/input05.txt");
    Day06 d6 = Day06("Day06", "../input/input06.txt");
    Day07 d7 = Day07("Day07", "../input/input07.txt");

    vector<Task *> tasks{
        &d1, &d2, &d3, &d4, &d5, &d6, &d7
    };

    for (auto task: tasks) {
        task->run_benchmarks();
        task->print_results();
    }

    generate_readme("../readme.md", tasks);
    return 0;
}

