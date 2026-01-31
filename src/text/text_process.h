#ifndef TEXT_PROCESS_H
#define TEXT_PROCESS_H

/* Trim leading and trailing spaces (in-place) */
void trim_spaces(char *line);

/* Remove patterns like [123], [07], [9] */
void remove_bracket_numbers(char *line);

/* Replace smart punctuation with ASCII */
void replace_smart_chars(char *line);

/* Remove non-ASCII characters */
void strip_non_ascii(char *line);

/* Apply all text processing rules in correct order */
void process_line(char *line);

#endif
