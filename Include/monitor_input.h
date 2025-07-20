#ifndef MONITOR_INPUT_H
#define MONITOR_INPUT_H

#include <stdbool.h>

typedef bool (*CharHandler)(char ch, char *command, int *command_len);

typedef struct {
    const char *name;
    CharHandler func;
} HandlerEntry;

void monitor_input(void);

#endif
