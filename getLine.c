#include "shell.h"

/**
 * buffer_input - Buffer chained commands.
 * @info: Parameter struct.
 * @buffer: Address of buffer.
 * @length: Address of length variable.
 *
 * Return: Bytes read.
 */
ssize_t buffer_input(info_t *info, char **buffer, size_t *length) {
    ssize_t bytes_read = 0;
    size_t length_p = 0;

    if (!*length) {
        free(*buffer);
        *buffer = NULL;
        signal(SIGINT, blockCtrlC);
#if USE_GETLINE
        bytes_read = getline(buffer, &length_p, stdin);
#else
        bytes_read = custom_getline(info, buffer, &length_p);
#endif

        if (bytes_read > 0) {
            if ((*buffer)[bytes_read - 1] == '\n') {
                (*buffer)[bytes_read - 1] = '\0';
                bytes_read--;
            }
            info->linecount_flag = 1;
            remove_comments(*buffer);
            build_history_list(info, *buffer, info->histcount++);
            *length = bytes_read;
            info->cmd_buffer = buffer;
        }
    }

    return bytes_read;
}

/**
 * read_input - Get a line without the newline character.
 * @info: Parameter struct.
 *
 * Return: Bytes read.
 */
ssize_t read_input(info_t *info) {
    static char *buffer;
    static size_t i, j, length;
    ssize_t bytes_read = 0;
    char **buffer_p = &(info->arg), *p;

    _putchar(BUF_FLUSH);
    bytes_read = buffer_input(info, &buffer, &length);

    if (bytes_read == -1) {
        return -1;
    }

    if (length) {
        j = i;
        p = buffer + i;

        check_chain(info, buffer, &j, i, length);
        while (j < length) {
            if (is_chain(info, buffer, &j)) {
                break;
            }
            j++;
        }

        i = j + 1;
        if (i >= length) {
            i = length = 0;
            info->cmd_buffer_type = CMD_NORMAL;
        }

        *buffer_p = p;
        return _strlen(p);
    }

    *buffer_p = buffer;
    return bytes_read;
}

/**
 * read_buffer - Read a buffer.
 * @info: Parameter struct.
 * @buffer: Buffer.
 * @i: Size.
 *
 * Return: Bytes read.
 */
ssize_t read_buffer(info_t *info, char *buffer, size_t *i) {
    ssize_t bytes_read = 0;

    if (*i) {
        return 0;
    }

    bytes_read = read(info->readfd, buffer, READ_BUF_SIZE);

    if (bytes_read >= 0) {
        *i = bytes_read;
    }

    return bytes_read;
}

/**
 * custom_getline - Get the next line of input from STDIN.
 * @info: Parameter struct.
 * @ptr: Address of pointer to buffer, preallocated or NULL.
 * @length: Size of preallocated ptr buffer if not NULL.
 *
 * Return: Bytes read.
 */
int custom_getline(info_t *info, char **ptr, size_t *length) {
    static char buf[READ_BUF_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t bytes_read = 0, bytes_written = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;
    if (p && length) {
        bytes_written = *length;
    }

    if (i == len) {
        i = len = 0;
    }

    bytes_read = read_buffer(info, buf, &len);

    if (bytes_read == -1 || (bytes_read == 0 && len == 0)) {
        return -1;
    }

    c = _strchr(buf + i, '\n');
    k = c ? 1 + (unsigned int)(c - buf) : len;
    new_p = _realloc(p, bytes_written, bytes_written ? bytes_written + k : k + 1);

    if (!new_p) {
        return (p ? free(p), -1 : -1);
    }

    if (bytes_written) {
        _strncat(new_p, buf + i, k - i);
    } else {
        _strncpy(new_p, buf + i, k - i + 1);
    }

    bytes_written += k - i;
    i = k;
    p = new_p;

    if (length) {
        *length = bytes_written;
    }

    *ptr = p;
    return bytes_written;
}

/**
 * blockCtrlC - Block Ctrl-C.
 * @signalNumber: The signal number.
 *
 * Return: void.
 */
void blockCtrlC(__attribute__((unused)) int signalNumber) {
    _puts("\n");
    _puts("$ ");
    _putchar(BUF_FLUSH);
}

