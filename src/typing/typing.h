#ifndef TYPING_H
#define TYPING_H

#include "../stats/stats.h"

/*
  Run typing session.

  Parameters:
  - temp_file_path: processed text file
  - stats: stats structure to update

  Returns:
  - 0 = completed normally
  - 1 = terminated early (Ctrl+C)
  - -1 = error
*/
int typing_run(const char *temp_file_path, Stats *stats);

#endif
