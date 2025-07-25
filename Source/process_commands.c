#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "process_commands.h"

#define COMMAND_LOGOUT        "logout"

static bool process_cmd_exit(const char *cmd, const char* ACTUAL_CMD);

command_handler_t command_handler[] = {
    { cmd_id_logout,     COMMAND_LOGOUT,    process_cmd_exit    },
    { cmd_id_max,        NULL,              NULL                }
};

void process_command(const char *cmd) 
{
    cmd_id_t cmd_id = 0;
    bool cmd_handled = false;

    for (int i = 0; command_handler[i].func != NULL; ++i) {
        const char* ACTUAL_CMD = command_handler[i].command_str;

        if (command_handler[i].func(cmd, ACTUAL_CMD)) {
            cmd_handled = true;
            goto EXIT;
        }
    }

EXIT:
    if (!cmd_handled)
        printf("Invalid token!\n");
}

void process_query(const char *cmd, int cmd_len)
{
    for (int i = 0; i < cmd_len; ++i) {
        printf("cmd[%d] = %c\n", cmd_len, cmd[cmd_len]);
    }
}

static bool process_cmd_exit(const char *cmd, const char *ACTUAL_CMD)
{
    bool rv = false;

    if (strcmp(cmd, ACTUAL_CMD) == 0) {
        exit(EXIT_SUCCESS);
        rv = true;
    }

    return rv;
}
