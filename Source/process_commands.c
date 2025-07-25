#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "process_commands.h"

#define COMMAND_EXIT        "exit"

static bool process_cmd_exit(const char *cmd);

command_handler_t command_handler[] = {
    { cmd_id_exit,       process_cmd_exit    },
    { cmd_id_max,        NULL                }
};

void process_command(const char *cmd) 
{
    /*if (strcmp(cmd, "hello") == 0) {
        printf("Hello there!\n");
    } else if (strcmp(cmd, "exit") == 0) {
        process_cmd_exit();
    } else {
        printf("Unknown command: %s\n", cmd);
    }*/
    cmd_id_t cmd_id = cmd_id_exit;
    bool cmd_handled = false;
    for (int i = 0; command_handler[i].func != NULL; ++i) {
        if (command_handler[i].func(cmd)) {
            cmd_handled = true;
            break;
        }
    }
}

void process_query(const char *cmd, int cmd_len)
{
    for (int i = 0; i < cmd_len; ++i) {
        printf("cmd[%d] = %c\n", cmd_len, cmd[cmd_len]);
    }
}

static bool process_cmd_exit(const char *cmd)
{
    bool rv = false;

    if (strcmp(cmd, COMMAND_EXIT) == 0) {
        exit(EXIT_SUCCESS);
        rv = true;
    }

    return rv;
}
