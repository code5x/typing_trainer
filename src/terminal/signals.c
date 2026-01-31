#include "signals.h"

#include <signal.h>
#include <stdatomic.h>

static atomic_int terminate_requested = 0;

static void handle_sigint(int sig)
{
    (void)sig;
    terminate_requested = 1;
}

void signals_init(void)
{
    struct sigaction sa;
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);
}

int signals_should_terminate(void)
{
    return terminate_requested != 0;
}
