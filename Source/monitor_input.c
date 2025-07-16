#include <stdio.h>
#include <termios.h>
#include <unistd.h>

void test_func()
{
    printf("Test function working correctly!\n\n\n");
}

void monitor_input() {
    struct termios oldt, newt;
    int ch;

    // Save current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Set terminal to raw mode (non-canonical, no echo)
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while (1) {
        ch = getchar();
        if (ch == '?' || ch == '\n') {
            printf("type:ALU-7360>#\n");
        }
    }

    // Restore original terminal settings (unreachable here unless you break the loop)
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}
