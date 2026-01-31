#include "platform.h"

#include <sys/ioctl.h>
#include <unistd.h>

int platform_get_terminal_width(void)
{
    struct winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
        return -1;

    if (ws.ws_col == 0)
        return -1;

    return ws.ws_col;
}
