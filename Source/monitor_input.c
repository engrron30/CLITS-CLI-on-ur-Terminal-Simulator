#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "process_commands.h"

#define CMDLINE_NAME            "type:ALU-7360>#"
#define CMDLINE_QUERY_CMD_CHAR  '?'
#define CMDLINE_INPUT_LEN       128
#define DIR_DATA                "Data/"

static char get_char_without_newline(void);
static bool monitor_newline_from_ch(char ch, char command[], int command_len);

/* Monitors user input by character by get_char_without_newline().
 * The character is checked whether it is:
 *       (1) newline    (proceed to process_command and clear input)
 *       (2) ?          (then will show suggestons),
 *       (3) BACKSPACE  (then remove last character typed by user) 
 * 
 * If none of them, keep of adding the character typed by user
 * in input string then monitor the characters if criteria
 * above are to be observed.
 *
 * Wait until the user hit newline to process_command.
 * */
void monitor_input(void)
{
    char input[CMDLINE_INPUT_LEN];
    int pos = 0;
    char ch;

    while (true) {
        printf("%s ", CMDLINE_NAME);
        fflush(stdout);
        pos = 0;

        while (true) {
            ch = get_char_without_newline();

            /*if (ch == '\n') {
                input[pos] = '\0';
                printf("\n");
                break;
            }*/

            if (monitor_newline_from_ch(ch, input, pos)) {
                break;
            }

            // Monitor ? CHAR from user
            if (ch == CMDLINE_QUERY_CMD_CHAR) {
                printf("\n[Help] You typed '?'. Displaying suggestions:\n");
                //system("cat Data/?");
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

            // Monitor other chaacters and append it to char input[]
            if (pos < CMDLINE_INPUT_LEN - 1) {
                input[pos++] = ch;
                putchar(ch);
                fflush(stdout);
            }
        }

        if (pos > 0) {
            process_command(input);
        }
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

/* Monitors if current character is newline.
 *
 * If newline is found, append NULL instead of newline
 * then return true.
 * */
static bool monitor_newline_from_ch(char ch, 
                                    char command[],
                                    int command_len)
{
    bool rv = false;

    if (ch == '\n')
    {
        command[command_len] = '\0';
        printf("\n");
        rv = true;
    }

    return rv;
}

