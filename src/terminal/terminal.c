#include "terminal.h"

#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>

static struct termios original_termios;
static int raw_mode_enabled = 0;

int terminal_enable_raw_mode(void)
{
    struct termios raw;

    if (tcgetattr(STDIN_FILENO, &original_termios) == -1)
        return -1;

    raw = original_termios;

    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        return -1;

    raw_mode_enabled = 1;
    return 0;
}

void terminal_disable_raw_mode(void)
{
    if (!raw_mode_enabled)
        return;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);
    raw_mode_enabled = 0;
}

void terminal_clear_screen(void)
{
    /* ANSI clear screen + move cursor home */
    write(STDOUT_FILENO, "\033[2J\033[3J\033[H", 11);
}

void terminal_flush_input(void)
{
    tcflush(STDIN_FILENO, TCIFLUSH);
}

int terminal_get_width(void)
{
    struct winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
        return -1;

    if (ws.ws_col == 0)
        return -1;

    return ws.ws_col;
}
