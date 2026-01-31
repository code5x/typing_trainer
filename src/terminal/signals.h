#ifndef SIGNALS_H
#define SIGNALS_H

/* Initialize signal handlers */
void signals_init(void);

/* Check if termination was requested (Ctrl+C) */
int signals_should_terminate(void);

#endif
