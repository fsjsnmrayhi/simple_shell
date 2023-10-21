#include "shell.h"

/**
 * my_exit - Exit the shell.
 * @info: Structure containing potential arguments.
 *
 * Return: Exits with a given exit status (0) if info->argv[0] is not "exit".
 */
int my_exit(info_t *info) {
	int exit_code;

	if (info->argv[1]) {
		exit_code = custom_str_to_int(info->argv[1]);
		if (exit_code == -1) {
			info->status = 2;
			print_error(info, "Invalid number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return 1;
		}
		info->err_num = exit_code;
		return -2;
	}

	info->err_num = -1;
	return -2;
}

/**
 * my_cd - Change the current directory of the process.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int my_cd(info_t *info) {
	char *current_dir, *new_dir, buffer[1024];
	int chdir_result;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		_puts("TODO: Handle getcwd failure\n");

	if (!info->argv[1]) {
		new_dir = _getenv(info, "HOME=");
		if (!new_dir)
			chdir_result = chdir((new_dir = _getenv(info, "PWD=")) ? new_dir : "/");
		else
			chdir_result = chdir(new_dir);
	} else if (_strcmp(info->argv[1], "-") == 0) {
		if (!_getenv(info, "OLDPWD=")) {
			_puts(current_dir);
			_putchar('\n');
			return 1;
		}

		_puts(_getenv(info, "OLDPWD="));
		_putchar('\n');
		chdir_result = chdir((new_dir = _getenv(info, "OLDPWD=")) ? new_dir : "/");
	} else {
		chdir_result = chdir(info->argv[1]);
	}

	if (chdir_result == -1) {
		print_error(info, "Cannot change directory to ");
		_eputs(info->argv[1]);
		_eputchar('\n');
	} else {
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}

	return 0;
}

/**
 * my_help - Display a help message.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int my_help(info_t *info) {
	char **arg_array = info->argv;

	_puts("Help message: Functionality not yet implemented.\n");
	if (0) {
		_puts(*arg_array); /* Temporary workaround to avoid "unused variable" warning. */
	}
	return 0;
}

