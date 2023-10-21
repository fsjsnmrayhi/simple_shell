#include "shell.h"

/**
 * get_list_length - Determines the length of a linked list.
 * @h: Pointer to the first node.
 *
 * Return: The size of the list.
 */
size_t get_list_length(const list_t *h) {
    size_t size = 0;

    while (h) {
        h = h->next;
        size++;
    }

    return size;
}

/**
 * list_to_string_array - Returns an array of strings from the list->str field.
 * @head: Pointer to the first node.
 *
 * Return: An array of strings.
 */
char **list_to_string_array(list_t *head) {
    list_t *node = head;
    size_t i = get_list_length(head);
    size_t j;
    char **strings;
    char *str;

    if (!head || !i)
        return NULL;

    strings = malloc(sizeof(char *) * (i + 1));

    if (!strings)
        return NULL;

    for (i = 0; node; node = node->next, i++) {
        str = malloc(_strlen(node->str) + 1);

        if (!str) {
            for (j = 0; j < i; j++)
                free(strings[j]);
            free(strings);
            return NULL;
        }

        str = _strcpy(str, node->str);
        strings[i] = str;
    }

    strings[i] = NULL;
    return strings;
}

/**
 * print_list_nodes - Prints all elements of a list_t linked list.
 * @h: Pointer to the first node.
 *
 * Return: The size of the list.
 */
size_t print_list_nodes(const list_t *h) {
    size_t size = 0;

    while (h) {
        _puts(convert_number(h->num, 10, 0));
        _putchar(':');
        _putchar(' ');
        _puts(h->str ? h->str : "(nil)");
        _puts("\n");
        h = h->next;
        size++;
    }

    return size;
}

/**
 * find_node_with_prefix - Returns the node whose string starts with a prefix.
 * @node: Pointer to the list head.
 * @prefix: String to match at the beginning of the nodes.
 * @c: The next character after the prefix to match.
 *
 * Return: The matching node or NULL.
 */
list_t *find_node_with_prefix(list_t *node, char *prefix, char c) {
    char *p = NULL;

    while (node) {
        p = starts_with(node->str, prefix);
        if (p && ((c == -1) || (*p == c)))
            return node;
        node = node->next;
    }

    return NULL;
}

/**
 * get_node_index - Gets the index of a node within the linked list.
 * @head: Pointer to the list head.
 * @node: Pointer to the node to find.
 *
 * Return: The index of the node or -1 if not found.
 */
ssize_t get_node_index(list_t *head, list_t *node) {
    size_t index = 0;

    while (head) {
        if (head == node)
            return index;
        head = head->next;
        index++;
    }

    return -1;
}

