#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define CMDLINE_NAME            "type:ALU-7360>#"
#define CMDLINE_QUERY_CMD_CHAR  '?'
#define CMDLINE_INPUT_LEN       128
#define DIR_DATA                "Data/"

static void process_command(const char *cmd);
static char getch(void);

void monitor_input(void) 
{
    char input[CMDLINE_INPUT_LEN], input_ch;

    while (1) {
        printf("%s ", CMDLINE_NAME);

        input_ch = getch();
        if (CMDLINE_QUERY_CMD_CHAR == input_ch) {
            system("cat Data/?");
        } else {
            if (fgets(input, sizeof(input), stdin) == NULL)
                break;

            input[strcspn(input, "\n")] = 0;
            printf("### DEBUG input = %s ###\n\n");
        }

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

static char getch(void)
{
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);           // get current terminal attributes
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);         // disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);  // set new attributes
    ch = getchar();                           // read character
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  // restore old attributes
    return ch;
}

