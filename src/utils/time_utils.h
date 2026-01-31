#ifndef TIME_UTILS_H
#define TIME_UTILS_H

/* Opaque timer structure */
typedef struct {
    long start_sec;
    long start_nsec;
    long end_sec;
    long end_nsec;
} Timer;

/* Start the timer */
void timer_start(Timer *t);

/* Stop the timer */
void timer_stop(Timer *t);

/* Get elapsed time in seconds (double) */
double timer_elapsed_seconds(const Timer *t);

#endif
