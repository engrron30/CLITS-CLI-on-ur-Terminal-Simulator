#ifndef MONITOR_INPUT_H
#define MONITOR_INPUT_H

#include <stdbool.h>

#define COMMAND_LEN 128

typedef bool (*CharHandler)(char ch, char *command, int *command_len);

typedef enum {
    char_id_newline = 0,
    char_id_querychar,
    char_id_backspace,
    char_id_otherchar,
    char_id_max
} char_id_t;

typedef struct {
    char_id_t char_id;
    CharHandler func;
} HandlerEntry;

void monitor_input(char *command, int *command_len);

#endif
