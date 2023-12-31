#include "my_shell.h"

int my_shell(info_t *info, char **av) {
    ssize_t read_result = 0;
    int builtin_ret = 0;

    while (read_result != -1 && builtin_ret != -2) {
        clear_info(info);
        if (interactive(info))
            _puts("$ ");
        _eputchar(BUF_FLUSH);
        read_result = get_input_line(info);
        if (read_result != -1) {
            set_info(info, av);
            builtin_ret = find_builtin(info);
            if (builtin_ret == -1)
                find_command(info);
        } else if (interactive(info))
            _putchar('\n');
        free_info(info, 0);
    }
    write_history_to_file(info);
    free_info(info, 1);
    if (!interactive(info) && info->status)
        exit(info->status);
    if (builtin_ret == -2) {
        if (info->err_num == -1)
            exit(info->status);
        exit(info->err_num);
    }
    return builtin_ret;
}

int find_builtin(info_t *info) {
    int i, builtin_ret = -1;
    builtin_table builtintbl[] = {
        {"exit", _myexit},
        {"env", _myenv},
        {"help", _myhelp},
        {"history", _myhistory},
        {"setenv", _mysetenv},
        {"unsetenv", _myunsetenv},
        {"cd", _mycd},
        {"alias", _myalias},
        {NULL, NULL}
    };

    for (i = 0; builtintbl[i].type; i++)
        if (_strcmp(info->argv[0], builtintbl[i].type) == 0) {
            info->line_count++;
            builtin_ret = builtintbl[i].func(info);
            break;
        }
    return builtin_ret;
}

void find_command(info_t *info) {
    char *path = NULL;
    int i, k;

    info->path = info->argv[0];
    if (info->linecount_flag == 1) {
        info->line_count++;
        info->linecount_flag = 0;
    }
    for (i = 0, k = 0; info->arg[i]; i++)
        if (!is_delim(info->arg[i], " \t\n"))
            k++;
    if (!k)
        return;

    path = find_command_path(info, _getenv(info, "PATH="), info->argv[0]);
    if (path) {
        info->path = path;
        fork_cmd(info);
    } else {
        if ((interactive(info) || _getenv(info, "PATH=") || info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
            fork_cmd(info);
        else if (*(info->arg) != '\n') {
            info->status = 127;
            print_error_msg(info, "not found\n");
        }
    }
}

void fork_cmd(info_t *info) {
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == -1) {
        perror("Fork Error:");
        return;
    }
    if (child_pid == 0) {
        if (execve(info->path, info->argv, get_environ(info)) == -1) {
            free_info(info, 1);
            if (errno == EACCES)
                exit(126);
            exit(1);
        }
    } else {
        wait(&(info->status));
        if (WIFEXITED(info->status)) {
            info->status = WEXITSTATUS(info->status);
            if (info->status == 126)
                print_error_msg(info, "Permission denied\n");
        }
    }
}

