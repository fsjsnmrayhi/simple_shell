#include "shell.h"

/**
 * is_executable - checks if a file is an executable command
 * @info: the information structure
 * @path: the path to the file
 *
 * Return: 1 if it's an executable command, 0 otherwise
 */
int is_executable(info_t *info, char *path) {
    struct stat st;

    (void)info;
    if (!path || stat(path, &st))
        return 0;

    if (st.st_mode & S_IFREG) {
        return 1;
    }
    return 0;
}

/**
 * duplicate_chars - duplicates characters from a string
 * @source: the source string
 * @start: the starting index
 * @stop: the stopping index
 *
 * Return: a pointer to a new buffer
 */
char *duplicate_chars(char *source, int start, int stop) {
    static char buffer[1024];
    int i = 0, k = 0;

    for (k = 0, i = start; i < stop; i++)
        if (source[i] != ':')
            buffer[k++] = source[i];
    buffer[k] = 0;
    return buffer;
}

/**
 * find_command_in_path - finds a command in the PATH environment variable
 * @info: the information structure
 * @path_str: the PATH string
 * @command: the command to find
 *
 * Return: the full path of the command if found, or NULL if not found
 */
char *find_command_in_path(info_t *info, char *path_str, char *command) {
    int i = 0, curr_pos = 0;
    char *path;

    if (!path_str)
        return NULL;
    if ((_strlen(command) > 2) && starts_with(command, "./")) {
        if (is_executable(info, command))
            return command;
    }
    while (1) {
        if (!path_str[i] || path_str[i] == ':') {
            path = duplicate_chars(path_str, curr_pos, i);
            if (!*path)
                _strcat(path, command);
            else {
                _strcat(path, "/");
                _strcat(path, command);
            }
            if (is_executable(info, path))
                return path;
            if (!path_str[i])
                break;
            curr_pos = i;
        }
        i++;
    }
    return NULL;
}

