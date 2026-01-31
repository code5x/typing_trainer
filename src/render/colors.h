#ifndef COLORS_H
#define COLORS_H

/* Reset all colors and attributes */
void color_reset(void);

/* Set text color using RGB */
void color_set_fg(int r, int g, int b);

/* Set background color using RGB */
void color_set_bg(int r, int g, int b);

/* Set foreground + background together */
void color_set_fg_bg(
    int fr, int fg, int fb,
    int br, int bg, int bb
);

#endif
