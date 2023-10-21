#include "shell.h"

/**
 * get_shell_history_file - Get the path to the shell history file.
 * @info: Pointer to the info_t struct.
 *
 * Return: Allocated string containing the path to the history file.
 */
char *get_shell_history_file(info_t *info) {
    char *history_file, *home_dir;

    home_dir = _getenv(info, "HOME=");
    if (!home_dir)
        return (NULL);

    history_file = malloc(sizeof(char) * (_strlen(home_dir) + _strlen(SHELL_HISTORY_FILE) + 2));
    if (!history_file)
        return (NULL);

    history_file[0] = '\0';
    _strcpy(history_file, home_dir);
    _strcat(history_file, "/");
    _strcat(history_file, SHELL_HISTORY_FILE);

    return history_file;
}

/**
 * write_shell_history - Write shell history to a file.
 * @info: Pointer to the info_t struct.
 *
 * Return: 1 on success, -1 on failure.
 */
int write_shell_history(info_t *info) {
    ssize_t fd;
    char *filename = get_shell_history_file(info);
    list_t *node = NULL;

    if (!filename)
        return (-1);

    fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);

    if (fd == -1)
        return (-1);

    for (node = info->shell_history; node; node = node->next) {
        _putsfd(node->str, fd);
        _putfd('\n', fd);
    }
    _putfd(BUF_FLUSH, fd);
    close(fd);

    return 1;
}

/**
 * read_shell_history - Read shell history from a file.
 * @info: Pointer to the info_t struct.
 *
 * Return: Total number of lines read, 0 on failure.
 */
int read_shell_history(info_t *info) {
    int i, last = 0, line_count = 0;
    ssize_t fd, read_length, file_size = 0;
    struct stat st;
    char *buf = NULL, *filename = get_shell_history_file(info);

    if (!filename)
        return 0;

    fd = open(filename, O_RDONLY);
    free(filename);

    if (fd == -1)
        return 0;

    if (!fstat(fd, &st))
        file_size = st.st_size;

    if (file_size < 2)
        return 0;

    buf = malloc(sizeof(char) * (file_size + 1));

    if (!buf)
        return 0;

    read_length = read(fd, buf, file_size);
    buf[file_size] = '\0';

    if (read_length <= 0)
        return free(buf), 0;

    close(fd);

    for (i = 0; i < file_size; i++) {
        if (buf[i] == '\n') {
            buf[i] = '\0';
            build_shell_history_list(info, buf + last, line_count++);
            last = i + 1;
        }
    }

    if (last != i)
        build_shell_history_list(info, buf + last, line_count++);

    free(buf);
    info->shell_history_count = line_count;

    while (info->shell_history_count-- >= SHELL_HISTORY_MAX)
        delete_node_at_index(&(info->shell_history), 0);

    renumber_shell_history(info);

    return info->shell_history_count;
}

/**
 * build_shell_history_list - Add an entry to the shell history linked list.
 * @info: Pointer to the info_t struct.
 * @line: The line to add to the history.
 * @line_count: The history line count.
 *
 * Return: 0.
 */
int build_shell_history_list(info_t *info, char *line, int line_count) {
    list_t *node = NULL;

    if (info->shell_history)
        node = info->shell_history;

    add_node_end(&node, line, line_count);

    if (!info->shell_history)
        info->shell_history = node;

    return 0;
}

/**
 * renumber_shell_history - Renumber the shell history linked list after changes.
 * @info: Pointer to the info_t struct.
 *
 * Return: The new line count of the shell history.
 */
int renumber_shell_history(info_t *info) {
    list_t *node = info->shell_history;
    int line_count = 0;

    while (node) {
        node->num = line_count++;
        node = node->next;
    }

    return info->shell_history_count = line_count;
}

