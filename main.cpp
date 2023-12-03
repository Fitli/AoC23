#include "cstdio"

#include "infra/Task.h"
#include "tasks/Day1.h"
#include "tasks/Day2.h"
#include "tasks/Day03.h"

int main()
{
    Day1 d1 = Day1("Day1", "../input/input01.txt");
    d1.print_results();
    d1.measure_time();

    Day2 d2 = Day2("Day2", "../input/input02.txt");
    d2.print_results();
    d2.measure_time();

    Day03 d3 = Day03("Day3", "../input/input03.txt");
    d3.print_results();
    d3.measure_time();
    return 0;
}