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
static char get_char_without_newline(void);

void monitor_input(void)
{
    char input[CMDLINE_INPUT_LEN], input_ch;

    while (1) {
        printf("%s ", CMDLINE_NAME);
        fflush(stdout);

        // Monitor '?' character
        input_ch = get_char_without_newline();
        if (input_ch == CMDLINE_QUERY_CMD_CHAR) {
            system("cat Data/?");
            continue;
        }

        // Command by User
        ungetc(input_ch, stdin);
        printf("%c", input_ch);
        fflush(stdout);
        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        input[strcspn(input, "\n")] = 0;
        process_command(input);
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

/* Waits for user to input a character and saves it to ch
 * without waiting for the user to hit newline
 * */
static char get_char_without_newline(void)
{
    struct termios oldt, newt;
    char ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}

