#include "shell.h"

/**
 * string_to_int - Convert a string to an integer.
 * @s: The string to be converted.
 * 
 * Return: The converted number, 0 if no numbers in the string, -1 on error.
 */
int string_to_int(char *s) {
    int i = 0;
    unsigned long int result = 0;

    if (*s == '+') {
        s++;
    }

    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            result *= 10;
            result += (s[i] - '0');
            if (result > INT_MAX) {
                return -1;
            }
        } else {
            return -1;
        }
    }

    return result;
}

/**
 * print_error_message - Print an error message to stderr.
 * @estr: String containing the specified error type.
 *
 * Return: Nothing.
 */
void print_error_message(char *estr) {
    _eputs("Shell: ");
    _eputs(estr);
}

/**
 * print_integer - Print an integer to the specified file descriptor.
 * @input: The integer to print.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters printed.
 */
int print_integer(int input, int fd) {
    int (*print_char_func)(char) = _putchar;
    int i, count = 0;
    unsigned int absolute, current;

    if (fd == STDERR_FILENO) {
        print_char_func = _eputchar;
    }

    if (input < 0) {
        absolute = -input;
        print_char_func('-');
        count++;
    } else {
        absolute = input;
    }

    current = absolute;
    for (i = 1000000000; i > 1; i /= 10) {
        if (absolute / i) {
            print_char_func('0' + current / i);
            count++;
        }
        current %= i;
    }

    print_char_func('0' + current);
    count++;

    return count;
}

/**
 * integer_to_string - Convert a number to a string (itoa).
 * @num: The number.
 * @base: The base for conversion.
 * @flags: Argument flags.
 * 
 * Return: The converted string.
 */
char *integer_to_string(long int num, int base, int flags) {
    static char *char_array;
    static char buffer[50];
    char sign = 0;
    char *ptr;
    unsigned long n = num;

    if (!(flags & CONVERT_UNSIGNED) && num < 0) {
        n = -num;
        sign = '-';
    }

    char_array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
    ptr = &buffer[49];
    *ptr = '\0';

    do {
        *--ptr = char_array[n % base];
        n /= base;
    } while (n != 0);

    if (sign) {
        *--ptr = sign;
    }
    return ptr;
}

/**
 * remove_comments - Replace the first instance of '#' with '\0'.
 * @buf: Address of the string to modify.
 *
 * Return: Nothing.
 */
void remove_comments(char *buf) {
    int i;

    for (i = 0; buf[i] != '\0'; i++) {
        if (buf[i] == '#' && (!i || buf[i - 1] == ' ')) {
            buf[i] = '\0';
            break;
        }
    }
}

