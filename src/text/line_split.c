#include "line_split.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char *strndup_safe(const char *src, size_t n)
{
    char *out = (char *)malloc(n + 1);
    if (!out)
        return NULL;

    memcpy(out, src, n);
    out[n] = '\0';
    return out;
}

int split_line_by_width(
    const char *line,
    size_t max_width,
    char ***out_lines,
    size_t *out_count
)
{
    char **lines = NULL;
    size_t lines_count = 0;
    size_t lines_capacity = 8;

    char current[4096];
    size_t current_len = 0;

    const char *p = line;

    if (!line || max_width == 0 || !out_lines || !out_count)
        return -1;

    lines = malloc(sizeof(char *) * lines_capacity);
    if (!lines)
        return -1;

    while (*p) {

        /* Skip leading spaces */
        while (*p && isspace((unsigned char)*p))
            p++;

        if (!*p)
            break;

        /* Get word start */
        const char *word_start = p;

        while (*p && !isspace((unsigned char)*p))
            p++;

        size_t word_len = p - word_start;

        /* Word longer than line width → forced split */
        if (word_len > max_width) {

            size_t offset = 0;

            while (offset < word_len) {
                size_t chunk = max_width;

                if (offset + chunk > word_len)
                    chunk = word_len - offset;

                char *part = strndup_safe(word_start + offset, chunk);
                if (!part)
                    goto error;

                if (lines_count == lines_capacity) {
                    lines_capacity *= 2;
                    char **tmp = realloc(lines, sizeof(char *) * lines_capacity);
                    if (!tmp)
                        goto error;
                    lines = tmp;
                }

                lines[lines_count++] = part;
                offset += chunk;
            }

            current_len = 0;
            continue;
        }

        /* If word does not fit current line, flush current line */
        if (current_len > 0 &&
            current_len + 1 + word_len > max_width) {

            char *out = strndup_safe(current, current_len);
            if (!out)
                goto error;

            if (lines_count == lines_capacity) {
                lines_capacity *= 2;
                char **tmp = realloc(lines, sizeof(char *) * lines_capacity);
                if (!tmp)
                    goto error;
                lines = tmp;
            }

            lines[lines_count++] = out;
            current_len = 0;
        }

        /* Add space if needed */
        if (current_len > 0) {
            current[current_len++] = ' ';
        }

        memcpy(current + current_len, word_start, word_len);
        current_len += word_len;
    }

    /* Flush last line */
    if (current_len > 0) {
        char *out = strndup_safe(current, current_len);
        if (!out)
            goto error;

        if (lines_count == lines_capacity) {
            lines_capacity *= 2;
            char **tmp = realloc(lines, sizeof(char *) * lines_capacity);
            if (!tmp)
                goto error;
            lines = tmp;
        }

        lines[lines_count++] = out;
    }

    *out_lines = lines;
    *out_count = lines_count;
    return 0;

error:
    free_split_lines(lines, lines_count);
    return -1;
}
void free_split_lines(char **lines, size_t count)
{
    size_t i;

    if (!lines)
        return;

    for (i = 0; i < count; i++) {
        free(lines[i]);
    }

    free(lines);
}
