#include "renderer.h"

#include "colors.h"
#include "../../include/config.h"

#include <stdio.h>

/* Render correct character */
void render_correct_char(char expected)
{
    /* Green text with dark background */
    color_set_fg_bg(
        COLOR_GREEN_R,
        COLOR_GREEN_G,
        COLOR_GREEN_B,
        COLOR_BG_R,
        COLOR_BG_G,
        COLOR_BG_B
    );

    /* Print expected character */
    if (expected == ' ')
        putchar(' ');
    else
        putchar(expected);

    fflush(stdout);
}

/* Render wrong character */
void render_wrong_char(char expected)
{
    /* Red text with dark background */
    color_set_fg_bg(
        COLOR_RED_R,
        COLOR_RED_G,
        COLOR_RED_B,
        COLOR_BG_R,
        COLOR_BG_G,
        COLOR_BG_B
    );

    /* Special rule: space shows '_' */
    if (expected == ' ')
        putchar('_');
    else
        putchar(expected);

    fflush(stdout);
}

/* Render preview text (yellow, no background) */
void render_preview_text(const char *text)
{
    if (!text)
        return;

    /* Reset everything first */
    color_reset();

    /* Set yellow foreground only */
    color_set_fg(
        COLOR_YELLOW_R,
        COLOR_YELLOW_G,
        COLOR_YELLOW_B
    );

    printf("%s", text);
    fflush(stdout);
}

/* Reset colors */
void render_reset(void)
{
    color_reset();
}
