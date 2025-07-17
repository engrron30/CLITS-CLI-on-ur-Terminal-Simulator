#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMDLINE_DEFAULT_NAME        "type:ALU-7360>#"
#define CMDLINE_DEFAULT_INPUT_LEN   128

static void process_command(const char *cmd);

void monitor_input() {
    char input[CMDLINE_DEFAULT_INPUT_LEN], input_ch;

    while (1) {
        printf("%s ", CMDLINE_DEFAULT_NAME);
        if (fgets(input, sizeof(input), stdin) == NULL)
            break;
        input[strcspn(input, "\n")] = 0;
    }
}

static void process_command(const char *cmd) {
    if (strcmp(cmd, "hello") == 0) {
        printf("Hello there!\n");
    } else if (strcmp(cmd, "exit") == 0) {
        printf("Exiting CLI...\n");
        exit(0);
    } else {
        printf("Unknown command: %s\n", cmd);
    }
}
