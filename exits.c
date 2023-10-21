#include "shell.h"

/**
 * copy_string - Copy a string.
 * @destination: The destination string to be copied to.
 * @source: The source string.
 * @n: The maximum number of characters to be copied.
 *
 * Return: The concatenated string.
 */
char *copy_string(char *destination, char *source, int n) {
    int i, j;
    char *result = destination;

    i = 0;
    while (source[i] != '\0' && i < n - 1) {
        destination[i] = source[i];
        i++;
    }

    if (i < n) {
        j = i;
        while (j < n) {
            destination[j] = '\0';
            j++;
        }
    }

    return result;
}

/**
 * concatenate_strings - Concatenate two strings.
 * @destination: The first string.
 * @source: The second string.
 * @n: The maximum number of bytes to be used.
 *
 * Return: The concatenated string.
 */
char *concatenate_strings(char *destination, char *source, int n) {
    int i, j;
    char *result = destination;

    i = 0;
    j = 0;

    while (destination[i] != '\0') {
        i++;
    }

    while (source[j] != '\0' && j < n) {
        destination[i] = source[j];
        i++;
        j++;
    }

    if (j < n) {
        destination[i] = '\0';
    }

    return result;
}

/**
 * find_character - Locate a character in a string.
 * @string: The string to be parsed.
 * @character: The character to look for.
 *
 * Return: A pointer to the memory area in the string.
 */
char *find_character(char *string, char character) {
    do {
        if (*string == character) {
            return string;
        }
    } while (*string++ != '\0');

    return NULL;
}

