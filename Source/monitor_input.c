#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "monitor_input.h"

#define CMDLINE_NAME            "type:ALU-7360>#"
#define CMDLINE_QUERY_CMD_CHAR  '?'
#define DIR_DATA                "Data/"

static char get_char_without_newline(void);
static bool monitor_newlinech_from_ch(char ch, char *command, int *command_len);
static bool monitor_querychar_from_ch(char ch, char *command, int *command_len);
static bool monitor_backspace_from_ch(char ch, char *command, int *command_len);
static bool monitor_otherchar_from_ch(char ch, char *command, int *command_len);

HandlerEntry monitor_handlers[] = {
    { char_id_newline,    monitor_newlinech_from_ch },
    { char_id_querychar,  monitor_querychar_from_ch },
    { char_id_backspace,  monitor_backspace_from_ch },
    { char_id_otherchar,  monitor_otherchar_from_ch },
    { char_id_max,        NULL }
};

/* This function monitors user input by character by get_char_without_newline().
 *
 * The character is checked whether it is:
 *       (1) newline    (exits this function entirely with user_cmd populated
 *                      based on the user input)
 *       (2) ?          (then will show suggestons),
 *       (3) BACKSPACE  (then remove last character typed by user) 
 * 
 * If none of them, keep in adding the character typed by user in user_cmd string
 * then monitor the characters if criteria above are to be observed.
 *
 * Wait until the user hit newline before exiting this function.
 * */
void monitor_input(char *user_cmd, int *user_cmd_len)
{
    char ch;
    *user_cmd_len = 0;

    printf("%s ", CMDLINE_NAME);
    fflush(stdout);

    while (true) {
        ch = get_char_without_newline();
        bool handled = false;
        char_id_t char_id = char_id_newline;

        for (char_id; monitor_handlers[char_id].func != NULL; ++char_id) {
            if (monitor_handlers[char_id].func(ch, user_cmd, user_cmd_len)) {
                handled = true;
                break;
            }
        }

        if (handled && char_id_newline == char_id)
            break;
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

/* This function monitors if current character is newline.
 *
 * If detected, append NULL to command string instead of newline
 * to indicate last character of the command, then returns true.
 * */
static bool monitor_newlinech_from_ch(char ch, char *command, int *command_len)
{
    bool rv = false;
    if (ch == '\n')
    {
        command[*command_len] = '\0';
        printf("\n");
        rv = true;
    }

    return rv;
}

/* This function monitors if current character is the QUERY CHARACTER ('?').
 *
 * If detected, do sugggest commands then returns true.
 * */
static bool monitor_querychar_from_ch(char ch, char *command, int *command_len)
{
    bool rv = false;
    if (ch == CMDLINE_QUERY_CMD_CHAR)
    {
        printf("\n[Help] You typed '?'. Displaying suggestions:\n");
        // TO-DO: Add specific action for QUERY CHAR is entered
        printf("%s %.*s", CMDLINE_NAME, *command_len, command);
        fflush(stdout);

        rv = true;
    }

    return rv;
}

/* This function monitors if current character is the BACKPACE character
 *
 * If detected, remove the last character in the command string and 
 * decrement the length of command by 1, then returns true.
 * Otherwise, false.
 * */
static bool monitor_backspace_from_ch(char ch, char *command, int *command_len)
{
    bool rv = false;
    if (ch == 127 || ch == '\b') {
        if (*command_len > 0) {
            (*command_len)--;
            printf("\b \b");
            fflush(stdout);
        }

        rv = true;
    }

    return rv;
}

/* This function monitors if the current character is anything except QUERY CHAR, 
 * NEWLINE or BACKSPACE.
 *
 * If detected, increment the command_len by 1 and append the current character
 * in the command string.
 * */
static bool monitor_otherchar_from_ch(char ch, char *command, int *command_len)
{
    bool rv = false;
    if (*command_len < COMMAND_LEN - 1)
    {
        command[(*command_len)++] = ch;
        putchar(ch);
        fflush(stdout);

        rv = true;
    }

    return rv;
}
