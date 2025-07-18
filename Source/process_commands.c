#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void process_command(const char *cmd) 
{
    if (strcmp(cmd, "hello") == 0) {
        printf("Hello there!\n");
    } else if (strcmp(cmd, "exit") == 0) {
        printf("Exiting CLI...\n");
        exit(0);
    } else {
        printf("Unknown command: %s\n", cmd);
    }
}

