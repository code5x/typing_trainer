#include "typing.h"

#include "../render/renderer.h"
#include "../terminal/terminal.h"
#include "../terminal/signals.h"
#include "../../include/config.h"

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

static int chars_equal(char a, char b)
{
#if CASE_SENSITIVE
    return a == b;
#else
    return tolower((unsigned char)a) == tolower((unsigned char)b);
#endif
}

static int read_char_nonblocking(char *out)
{
    ssize_t n = read(STDIN_FILENO, out, 1);
    if (n == 1)
        return 1;
    return 0;
}

int typing_run(const char *temp_file_path, Stats *stats)
{
    FILE *file;
    char line[4096];
    int c;
    int terminated = 0;

    int in_word = 0;
    int current_word_correct = 1;

    if (!temp_file_path || !stats)
        return -1;

    file = fopen(temp_file_path, "r");
    if (!file)
        return -1;

    if (terminal_enable_raw_mode() != 0) {
        fclose(file);
        return -1;
    }

    terminal_flush_input();

    while (fgets(line, sizeof(line), file)) {

        if (signals_should_terminate()) {
            terminated = 1;
            break;
        }

        line[strcspn(line, "\n")] = '\0';

        /* Preview line */
        render_preview_text(line);
        putchar('\n');

        for (size_t i = 0; line[i] != '\0'; i++) {

            if (signals_should_terminate()) {
                terminated = 1;
                break;
            }

            char ch;
            while (!read_char_nonblocking(&ch)) {
                if (signals_should_terminate())
                return 1;
            }
            c = ch;

            if (c == EOF) {
                terminated = 1;
                break;
            }

            stats->total_chars++;

            int correct = chars_equal((char)c, line[i]);

            if (correct) {
                render_correct_char(line[i]);
                stats->correct_chars++;
            } else {
                render_wrong_char(line[i]);
            }

            /* Word tracking */
            if (!isspace((unsigned char)line[i])) {

                if (!in_word) {
                    in_word = 1;
                    current_word_correct = 1;
                    stats->total_words++;
                }

                if (!correct)
                    current_word_correct = 0;

            } else {
                /* Space ends word */
                if (in_word) {
                    if (current_word_correct)
                        stats->correct_words++;

                    in_word = 0;
                }
            }
        }

        if (terminated)
            break;

        /* End of line may end a word */
        if (in_word) {
            if (current_word_correct)
                stats->correct_words++;
            in_word = 0;
        }

        /* Wait for Enter */
        while (1) {
            char ch;
            while (!read_char_nonblocking(&ch)) {
                if (signals_should_terminate())
                return 1;
            }
            c = ch;
            if (c == '\n' || c == '\r')
                break;
        }

        putchar('\n');
    }

    terminal_disable_raw_mode();
    render_reset();
    putchar('\n');
    fclose(file);

    return terminated ? 1 : 0;
}
