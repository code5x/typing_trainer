#include "time_utils.h"

#include <time.h>

void timer_start(Timer *t)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    t->start_sec = ts.tv_sec;
    t->start_nsec = ts.tv_nsec;
}

void timer_stop(Timer *t)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    t->end_sec = ts.tv_sec;
    t->end_nsec = ts.tv_nsec;
}

double timer_elapsed_seconds(const Timer *t)
{
    long sec = t->end_sec - t->start_sec;
    long nsec = t->end_nsec - t->start_nsec;

    return (double)sec + (double)nsec / 1000000000.0;
}
