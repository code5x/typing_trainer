#ifndef LINE_SPLIT_H
#define LINE_SPLIT_H

#include <stddef.h>

/*
  Split a line into multiple lines based on max_width.

  Parameters:
  - line: input string (null terminated)
  - max_width: terminal width (>0)
  - out_lines: output array of strings (allocated)
  - out_count: number of output lines
*/
int split_line_by_width(
    const char *line,
    size_t max_width,
    char ***out_lines,
    size_t *out_count
);

/* Free result from split_line_by_width */
void free_split_lines(char **lines, size_t count);

#endif
