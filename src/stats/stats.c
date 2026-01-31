#include "stats.h"

void stats_init(Stats *s)
{
    s->total_words = 0;
    s->total_chars = 0;
    s->correct_words = 0;
    s->correct_chars = 0;
    s->elapsed_seconds = 0.0;
}

void stats_set_time(Stats *s, double seconds)
{
    s->elapsed_seconds = seconds;
}

double stats_wpm(const Stats *s)
{
    if (s->elapsed_seconds <= 0.0)
        return 0.0;

    double minutes = s->elapsed_seconds / 60.0;
    return (double)s->total_words / minutes;
}

double stats_char_accuracy(const Stats *s)
{
    if (s->total_chars <= 0)
        return 0.0;

    return ((double)s->correct_chars / (double)s->total_chars) * 100.0;
}

double stats_word_accuracy(const Stats *s)
{
    if (s->total_words <= 0)
        return 0.0;

    return ((double)s->correct_words / (double)s->total_words) * 100.0;
}
