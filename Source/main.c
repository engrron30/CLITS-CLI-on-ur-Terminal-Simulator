#include <stdio.h>

#include "monitor_input.h"
#include "process_commands.h"

static void welcome_notes(void);

int main()
{
    char user_cmd[COMMAND_LEN];
    int user_cmd_len = 0;

    welcome_notes();

    while (true) {
        monitor_input(user_cmd, &user_cmd_len);
        process_command(user_cmd);
    }

    return 0;
}


static void welcome_notes(void) {
    printf("Welcome to ISAM\n");
    printf("last login : <TO-DO>\n\n");
}
