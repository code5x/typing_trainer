#ifndef STATS_H
#define STATS_H

typedef struct {
    /* Totals */
    long total_words;
    long total_chars;

    /* Correct counts */
    long correct_words;
    long correct_chars;

    /* Time */
    double elapsed_seconds;
} Stats;

/* Initialize stats */
void stats_init(Stats *s);

/* Set elapsed time */
void stats_set_time(Stats *s, double seconds);

/* Calculate WPM (based on total words) */
double stats_wpm(const Stats *s);

/* Character accuracy percentage */
double stats_char_accuracy(const Stats *s);

/* Word accuracy percentage */
double stats_word_accuracy(const Stats *s);

#endif
