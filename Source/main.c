#include <stdio.h>

#include "monitor_input.h"

static void welcome_notes(void);


int main()
{
    welcome_notes();
    test_func();
    return 0;
}


static void welcome_notes(void) {
    printf("Welcome to ISAM\n");
    printf("last login : <TO-DO>\n\n");
}
