#include "cstdio"

#include "infra/Task.h"
#include "tasks/Day01.h"
#include "tasks/Day02.h"
#include "tasks/Day03.h"

int main()
{
    Day01 d1 = Day01("Day01", "../input/input01.txt");
    Day02 d2 = Day02("Day02", "../input/input02.txt");
    Day03 d3 = Day03("Day03", "../input/input03.txt");

    vector<Task *> tasks{
        &d1, &d2, &d3
    };

    for (auto task: tasks) {
        task->print_results();
        task->measure_time();
    }
    return 0;
}