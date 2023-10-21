#include "shell.h"

/**
 * _set_memory - fills memory with a constant byte
 * @s: the pointer to the memory area
 * @byte: the byte to fill *s with
 * @size: the amount of bytes to be filled
 *
 * Return: (s) a pointer to the memory area s
 */
char *_set_memory(char *s, char byte, unsigned int size) {
    unsigned int i;

    for (i = 0; i < size; i++)
        s[i] = byte;
    return s;
}

/**
 * free_string_array - frees a string array
 * @str_array: string array to free
 */
void free_string_array(char **str_array) {
    char **array = str_array;

    if (!str_array)
        return;
    while (*str_array)
        free(*str_array++);
    free(array);
}

/**
 * custom_realloc - reallocates a block of memory
 * @ptr: pointer to the previous memory block
 * @old_size: byte size of the previous block
 * @new_size: byte size of the new block
 *
 * Return: pointer to the reallocated memory block
 */
void *custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size) {
    char *new_ptr;

    if (!ptr)
        return malloc(new_size);
    if (!new_size)
        return free(ptr), NULL;
    if (new_size == old_size)
        return ptr;

    new_ptr = malloc(new_size);
    if (!new_ptr)
        return NULL;

    old_size = old_size < new_size ? old_size : new_size;
    while (old_size--)
        new_ptr[old_size] = ((char *)ptr)[old_size];
    free(ptr);
    return new_ptr;
}

