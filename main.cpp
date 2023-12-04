#include "cstdio"

#include "infra/Task.h"
#include "tasks/Day01.h"
#include "tasks/Day02.h"
#include "tasks/Day03.h"
#include "tasks/Day04.h"

int main()
{
    Day01 d1 = Day01("Day01", "../input/input01.txt");
    Day02 d2 = Day02("Day02", "../input/input02.txt");
    Day03 d3 = Day03("Day03", "../input/input03.txt");
    Day04 d4 = Day04("Day04", "../input/input04.txt");

    vector<Task *> tasks{
        &d1, &d2, &d3, &d4
    };

    for (auto task: tasks) {
        task->print_results();
        task->measure_time();
    }
    return 0;
}