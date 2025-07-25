#ifndef PROCESS_COMMANDS_H
#define PROCESS_COMMANDS_H

typedef enum {
    command_id_exit = 0,
    cmd_id_show
} cmd_id_t;

void process_command(const char *cmd);
void process_query(const char *cmd, int cmd_len);

#endif
