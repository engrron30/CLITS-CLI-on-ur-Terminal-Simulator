#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void process_cmd_exit(void);

void process_command(const char *cmd) 
{
    if (strcmp(cmd, "hello") == 0) {
        printf("Hello there!\n");
    } else if (strcmp(cmd, "exit") == 0) {
        process_cmd_exit();
    } else {
        printf("Unknown command: %s\n", cmd);
    }
}

void process_query(const char *cmd, int cmd_len)
{
    for (int i = 0; i < cmd_len; ++i) {
        printf("cmd[%d] = %c\n", cmd_len, cmd[cmd_len]);
    }
}

static void process_cmd_exit(void)
{
    exit(EXIT_SUCCESS);
}
