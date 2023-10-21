#include "shell.h"

/**
 * custom_free - Frees a pointer and sets the address to NULL
 * @ptr: Address of the pointer to be freed and set to NULL
 *
 * Return: 1 if freed, otherwise 0.
 */
int custom_free(void **ptr) {
    if (ptr && *ptr) {
        free(*ptr);
        *ptr = NULL;
        return 1;
    }
    return 0;
}

