#include "temp_file.h"

#include "../text/line_split.h"
#include "../text/text_process.h"
#include "../utils/platform.h"
#include "../../include/config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *TEMP_FILE_NAME = ".temp_typing_file.txt";

/* Create temp file */
int temp_file_create(const char *source_path)
{
    FILE *in;
    FILE *out;
    char buffer[4096];
    int term_width;

    if (!source_path)
        return -1;

    in = fopen(source_path, "r");
    if (!in)
        return -1;

    out = fopen(TEMP_FILE_NAME, "w");
    if (!out) {
        fclose(in);
        return -1;
    }

    /* Determine terminal width */
    if (AUTO_DETECT_TERMINAL_WIDTH) {
        term_width = platform_get_terminal_width();
        if (term_width <= 0)
            term_width = 80;
    } else {
        term_width = TERMINAL_WIDTH;
        if (term_width <= 0) {
            fclose(in);
            fclose(out);
            return -1;
        }
    }

    /* Read source file line by line */
    while (fgets(buffer, sizeof(buffer), in)) {
        char **split_lines = NULL;
        size_t split_count = 0;
        size_t i;

        /* Remove newline */
        buffer[strcspn(buffer, "\n")] = '\0';

        /* Split line by terminal width */
        if (split_line_by_width(
                buffer,
                (size_t)term_width,
                &split_lines,
                &split_count) != 0) {
            fclose(in);
            fclose(out);
            return -1;
        }

        /* Process each split line */
        for (i = 0; i < split_count; i++) {
            process_line(split_lines[i]);

            /* Skip empty lines after processing */
            if (split_lines[i][0] != '\0') {
                fprintf(out, "%s\n", split_lines[i]);
            }
        }

        free_split_lines(split_lines, split_count);
    }

    fclose(in);
    fclose(out);
    return 0;
}

const char *temp_file_path(void)
{
    return TEMP_FILE_NAME;
}

void temp_file_cleanup(void)
{
    remove(TEMP_FILE_NAME);
}
