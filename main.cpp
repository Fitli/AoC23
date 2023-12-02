#include "cstdio"

#include "infra/Task.h"
#include "tasks/Day1.h"
#include "tasks/Day2.h"

int main()
{
    Day1 d1 = Day1("Day1", "../input/input01.txt");
    d1.print_results();
    d1.measure_time();

    Day2 d2 = Day2("Day2", "../input/input02.txt");
    d2.print_results();
    d2.measure_time();
    //getchar();
    return 0;
}