#include "shell.h"

/**
 * retrieve_environment - Get a copy of the environment strings.
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: String array of environment variables.
 */
char **retrieve_environment(info_t *info) {
    if (!info->environment || info->env_has_changed) {
        info->environment = list_to_strings(info->env);
        info->env_has_changed = 0;
    }

    return info->environment;
}

/**
 * custom_unsetenv - Remove an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * @variable: The environment variable to remove.
 *
 * Return: 1 if removed, 0 otherwise.
 */
int custom_unsetenv(info_t *info, char *variable) {
    list_t *node = info->env;
    size_t index = 0;
    char *p;

    if (!node || !variable) {
        return 0;
    }

    while (node) {
        p = starts_with(node->str, variable);
        if (p && *p == '=') {
            info->env_has_changed = delete_node_at_index(&(info->env), index);
            index = 0;
            node = info->env;
            continue;
        }
        node = node->next;
        index++;
    }

    return info->env_has_changed;
}

/**
 * custom_setenv - Initialize a new environment variable or modify an existing one.
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * @variable: The environment variable property.
 * @value: The environment variable value.
 *
 * Return: Always 0.
 */
int custom_setenv(info_t *info, char *variable, char *value) {
    char *buffer = NULL;
    list_t *node;
    char *p;

    if (!variable || !value) {
        return 0;
    }

    buffer = malloc(_strlen(variable) + _strlen(value) + 2);
    if (!buffer) {
        return 1;
    }

    _strcpy(buffer, variable);
    _strcat(buffer, "=");
    _strcat(buffer, value);
    node = info->env;

    while (node) {
        p = starts_with(node->str, variable);
        if (p && *p == '=') {
            free(node->str);
            node->str = buffer;
            info->env_has_changed = 1;
            return 0;
        }
        node = node->next;
    }

    add_node_end(&(info->env), buffer, 0);
    free(buffer);
    info->env_has_changed = 1;
    return 0;
}

