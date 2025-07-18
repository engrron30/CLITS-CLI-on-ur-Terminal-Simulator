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
    char input[CMDLINE_INPUT_LEN];
    int pos = 0;
    char ch;

    while (1) {
        printf("%s ", CMDLINE_NAME);
        fflush(stdout);
        pos = 0;

        while (1) {
            ch = get_char_without_newline();

            if (ch == '\n') {
                input[pos] = '\0';
                printf("\n");
                break;
            }

            // Monitor ? CHAR from user
            if (ch == CMDLINE_QUERY_CMD_CHAR) {
                printf("\n[Help] You typed '?'. Displaying suggestions:\n");
                //system("cat Data/?");  // Or use printf-based help
                printf("%s %.*s", CMDLINE_NAME, pos, input);
                fflush(stdout);
                continue;
            }

            // Monitor backspace CHAR from user
            if (ch == 127 || ch == '\b') {
                if (pos > 0) {
                    pos--;
                    printf("\b \b");
                    fflush(stdout);
                }
                continue;
            }

            // Monitor other commands input by user
            if (pos < CMDLINE_INPUT_LEN - 1) {
                input[pos++] = ch;
                putchar(ch);
                fflush(stdout);
            }
        }

<<<<<<< HEAD
        if (pos > 0) {
            process_command(input);
        }
=======
        // Command by User
        ungetc(input_ch, stdin);
        printf("%c", input_ch);
        fflush(stdout);
        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        input[strcspn(input, "\n")] = 0;
        process_command(input);
>>>>>>> 72208628b4df2c71d8a46949d34f310769c69762
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

