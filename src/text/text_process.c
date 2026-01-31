#include "text_process.h"

#include <ctype.h>
#include <string.h>

/* Trim leading and trailing spaces */
void trim_spaces(char *line)
{
    char *start;
    char *end;
    size_t len;

    if (!line)
        return;

    /* Trim leading spaces */
    start = line;
    while (*start && isspace((unsigned char)*start))
        start++;

    if (start != line)
        memmove(line, start, strlen(start) + 1);

    /* Trim trailing spaces */
    len = strlen(line);
    if (len == 0)
        return;

    end = line + len - 1;
    while (end >= line && isspace((unsigned char)*end)) {
        *end = '\0';
        end--;
    }
}

/* Remove [digits] patterns */
void remove_bracket_numbers(char *line)
{
    char *src = line;
    char *dst = line;

    if (!line)
        return;

    while (*src) {
        if (*src == '[') {
            char *p = src + 1;

            while (*p && isdigit((unsigned char)*p))
                p++;

            if (*p == ']') {
                src = p + 1;
                continue;
            }
        }

        *dst++ = *src++;
    }

    *dst = '\0';
}

/* Replace smart punctuation */
void replace_smart_chars(char *line)
{
    char *src = line;
    char *dst = line;

    if (!line)
        return;

    while (*src) {
        if ((unsigned char)src[0] == 0xE2 &&
            (unsigned char)src[1] == 0x80) {

            switch ((unsigned char)src[2]) {

                case 0x94:  /* em dash — */
                case 0x93:  /* en dash – */
                    *dst++ = '-';
                    src += 3;
                    continue;

                case 0x9C:  /* left double quote “ */
                case 0x9D:  /* right double quote ” */
                    *dst++ = '"';
                    src += 3;
                    continue;

                case 0x98:  /* left single quote ‘ */
                case 0x99:  /* right single quote ’ */
                    *dst++ = '\'';
                    src += 3;
                    continue;

                case 0xA6:  /* ellipsis … */
                    *dst++ = '.';
                    *dst++ = '.';
                    *dst++ = '.';
                    src += 3;
                    continue;
            }
        }

        *dst++ = *src++;
    }

    *dst = '\0';
}

/* Remove non-ASCII characters */
void strip_non_ascii(char *line)
{
    char *src = line;
    char *dst = line;

    if (!line)
        return;

    while (*src) {
        if ((unsigned char)*src < 128) {
            *dst++ = *src;
        }
        src++;
    }

    *dst = '\0';
}

/* Apply all rules */
void process_line(char *line)
{
    if (!line)
        return;

    remove_bracket_numbers(line);
    replace_smart_chars(line);
    strip_non_ascii(line);
    trim_spaces(line);
}
