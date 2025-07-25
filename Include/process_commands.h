#ifndef PROCESS_COMMANDS_H
#define PROCESS_COMMANDS_H

typedef enum {
    cmd_id_logout = 0,
    cmd_id_max
} cmd_id_t;

typedef bool (*CommandHandler_t)(const char *cmd, const char *ACTUAL_CMD);

typedef struct {
    cmd_id_t command_id;
    char* command_str;
    char* command_def_str;
    CommandHandler_t func;
} command_handler_t;

void process_command(const char *cmd);
void process_query(const char *cmd, int cmd_len);

#endif
