#include <stdio.h>
#include "colors.h"

/* Reset colors and attributes */
void color_reset(void)
{
    /* ANSI reset */
    printf("\033[0m");
    fflush(stdout);
}

/* Set foreground (text) color */
void color_set_fg(int r, int g, int b)
{
    printf("\033[38;2;%d;%d;%dm", r, g, b);
    fflush(stdout);
}

/* Set background color */
void color_set_bg(int r, int g, int b)
{
    printf("\033[48;2;%d;%d;%dm", r, g, b);
    fflush(stdout);
}

/* Set foreground and background together */
void color_set_fg_bg(
    int fr, int fg, int fb,
    int br, int bg, int bb
)
{
    printf(
        "\033[38;2;%d;%d;%dm"
        "\033[48;2;%d;%d;%dm",
        fr, fg, fb,
        br, bg, bb
    );
    fflush(stdout);
}
