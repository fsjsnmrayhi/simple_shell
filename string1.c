#include "my_shell.h"

/**
 * my_strcpy - copies a string
 * @destination: the destination
 * @source: the source
 *
 * Return: pointer to the destination
 */
char *my_strcpy(char *destination, char *source) {
    int i = 0;

    if (destination == source || source == NULL)
        return destination;

    while (source[i]) {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0';
    return destination;
}

/**
 * my_strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *my_strdup(const char *str) {
    int length = 0;
    char *result;

    if (str == NULL)
        return NULL;

    while (*str++)
        length++;

    result = malloc(sizeof(char) * (length + 1));
    if (!result)
        return NULL;

    for (length++; length > 0; length--)
        result[length - 1] = *--str;

    return result;
}

/**
 * my_puts - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void my_puts(char *str) {
    int i = 0;

    if (!str)
        return;

    while (str[i] != '\0') {
        my_putchar(str[i]);
        i++;
    }
}

/**
 * my_putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success, 1. On error, -1 is returned, and errno is set appropriately.
 */
int my_putchar(char c) {
    static int buf_index = 0;
    static char write_buffer[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || buf_index >= WRITE_BUF_SIZE) {
        write(1, write_buffer, buf_index);
        buf_index = 0;
    }

    if (c != BUF_FLUSH)
        write_buffer[buf_index++] = c;

    return 1;
}

