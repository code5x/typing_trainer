#ifndef TERMINAL_H
#define TERMINAL_H

#include <stddef.h>

/* Enable raw mode (no echo, no canonical input) */
int terminal_enable_raw_mode(void);

/* Disable raw mode and restore terminal */
void terminal_disable_raw_mode(void);

/* Clear screen */
void terminal_clear_screen(void);

/* Flush input buffer */
void terminal_flush_input(void);

/* Get terminal width
   Returns width (>0) on success
   Returns -1 on failure
*/
int terminal_get_width(void);

#endif
