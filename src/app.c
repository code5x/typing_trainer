#include "app.h"

#include "io/temp_file.h"
#include "typing/typing.h"
#include "stats/stats.h"
#include "utils/time_utils.h"
#include "terminal/terminal.h"
#include "terminal/signals.h"
#include "render/renderer.h"

#include <stdio.h>
#include <string.h>

/* Print final statistics */
static void print_stats(const Stats *s)
{
    double total_sec = s->elapsed_seconds;
    int minutes = (int)(total_sec / 60.0);
    int seconds = (int)total_sec - (minutes * 60);

    printf("\n\n\n    ===== Typing Statistics =====\n\n");
    printf("Time taken          : %d minutes, %d seconds\n", minutes, seconds);
    printf("Words Per Minute    : %.2f\n", stats_wpm(s));
    printf("Accuracy            : %.2f %%\n", stats_char_accuracy(s));
    printf("Correct words       : %ld / %ld (%.2f %%)\n",
           s->correct_words,
           s->total_words,
           stats_word_accuracy(s));
    printf("Correct characters  : %ld / %ld (%.2f %%)\n",
           s->correct_chars,
           s->total_chars,
           stats_char_accuracy(s));
}

/* Main application logic */
int app_run(void)
{
    char file_path[512];
    Stats stats;
    Timer timer;
    int typing_result;

    /* Prepare signal handling */
    signals_init();

    terminal_clear_screen();

    printf("Enter the text file name: ");
    fflush(stdout);

    if (!fgets(file_path, sizeof(file_path), stdin)) {
        printf("Input error.\n");
        return -1;
    }

    /* Remove newline */
    file_path[strcspn(file_path, "\n")] = '\0';

    if (temp_file_create(file_path) != 0) {
        printf("Error: Cannot open or process file.\n");
        return -1;
    }

    stats_init(&stats);

    timer_start(&timer);

    typing_result = typing_run(temp_file_path(), &stats);

    timer_stop(&timer);
    stats_set_time(&stats, timer_elapsed_seconds(&timer));

    terminal_disable_raw_mode();

    render_reset();

    print_stats(&stats);

    temp_file_cleanup();

    if (typing_result == 1) {
        printf("\nSession terminated (Ctrl+C).\n");
    }

    return 0;
}
