#ifndef CIRCUITROUTER_SHELL_H
#define CIRCUITROUTER_SHELL_H

#include "lib/vector.h"
#include "lib/timer.h"
#include <sys/types.h>

typedef struct {
    pid_t pid;
    int status;
    TIMER_T startTime, stopTime;
} child_t;

//void waitForChild(vector_t *children);
void printChildren(vector_t *children);
void signal_handler(int signal);

#endif /* CIRCUITROUTER_SHELL_H */
