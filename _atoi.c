#include "shell.h"
#include <ctype.h>  // for isdigit and isalpha

int is_interactive(info_t *info) {
    return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

int is_delimiter(char c, char *delim) {
    for (int i = 0; delim[i] != '\0'; i++) {
        if (c == delim[i]) {
            return 1;
        }
    }
    return 0;
}

int is_alpha(int c) {
    return isalpha(c);  // Using standard library isalpha function
}

int custom_atoi(char *s) {
    int result = 0;
    int sign = 1;

    // Handle sign character
    if (*s == '-') {
        sign = -1;
        s++;
    }

    // Convert string to integer
    while (isdigit(*s)) {
        result = result * 10 + (*s - '0');
        s++;
    }

    return result * sign;
}

