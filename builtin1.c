#include "shell.h"

/**
 * my_history - Display the command history list with line numbers.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int my_history(info_t *info) {
    print_command_history(info->history);
    return 0;
}

/**
 * unset_shell_alias - Unset a shell alias.
 * @info: Parameter struct.
 * @alias_str: The alias string to unset.
 *
 * Return: 0 on success, 1 on error.
 */
int unset_shell_alias(info_t *info, char *alias_str) {
    char *equal_sign, temp;
    int ret;

    equal_sign = _strchr(alias_str, '=');
    if (!equal_sign) {
        return 1;
    }
    temp = *equal_sign;
    *equal_sign = '\0';
    ret = delete_node_at_index(&(info->alias), get_alias_index(info->alias, alias_str));
    *equal_sign = temp;
    return ret;
}

/**
 * set_shell_alias - Set a shell alias.
 * @info: Parameter struct.
 * @alias_str: The alias string to set.
 *
 * Return: 0 on success, 1 on error.
 */
int set_shell_alias(info_t *info, char *alias_str) {
    char *equal_sign;

    equal_sign = _strchr(alias_str, '=');
    if (!equal_sign) {
        return 1;
    }

    if (!*++equal_sign) {
        return unset_shell_alias(info, alias_str);
    }

    unset_shell_alias(info, alias_str);
    return (add_node_end(&(info->alias), alias_str, 0) == NULL);
}

/**
 * print_shell_alias - Print a shell alias.
 * @alias_node: The alias node.
 *
 * Return: 0 on success, 1 on error.
 */
int print_shell_alias(list_t *alias_node) {
    char *equal_sign = NULL, *alias = NULL;

    if (alias_node) {
        equal_sign = _strchr(alias_node->str, '=');
        for (alias = alias_node->str; alias <= equal_sign; alias++) {
            _putchar(*alias);
        }
        _putchar('\'');
        _puts(equal_sign + 1);
        _puts("'\n");
        return 0;
    }
    return 1;
}

/**
 * my_alias - Mimic the alias builtin (man alias).
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int my_alias(info_t *info) {
    int i = 0;
    char *equal_sign = NULL;
    list_t *alias_node = NULL;

    if (info->argc == 1) {
        alias_node = info->alias;
        while (alias_node) {
            print_shell_alias(alias_node);
            alias_node = alias_node->next;
        }
        return 0;
    }

    for (i = 1; info->argv[i]; i++) {
        equal_sign = _strchr(info->argv[i], '=');
        if (equal_sign) {
            set_shell_alias(info, info->argv[i]);
        } else {
            print_shell_alias(get_alias_starts_with(info->alias, info->argv[i], '='));
        }
    }

    return 0;
}

