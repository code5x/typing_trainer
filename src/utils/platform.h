#ifndef PLATFORM_H
#define PLATFORM_H

/* Get terminal width
   Returns width (>0) on success
   Returns -1 on failure
*/
int platform_get_terminal_width(void);

#endif
