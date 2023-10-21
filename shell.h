#ifndef _MY_SHELL_H_
#define _MY_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

#define COMMAND_NORMAL 0
#define COMMAND_OR 1
#define COMMAND_AND 2
#define COMMAND_CHAIN 3

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define USE_CUSTOM_GETLINE 0
#define USE_CUSTOM_STRTOK 0

#define HISTORY_FILE ".my_shell_history"
#define HISTORY_MAX 4096

extern char **environ;

typedef struct liststr
{
    int num;
    char *str;
    struct liststr *next;
} list_t;

typedef struct passinfo
{
    char *arg;
    char **argv;
    char *path;
    int argc;
    unsigned int line_count;
    int err_num;
    int linecount_flag;
    char *fname;
    list_t *env;
    list_t *history;
    list_t *alias;
    char **environ;
    int env_changed;
    int status;
    char **cmd_buf;
    int cmd_buf_type;
    int readfd;
    int histcount;
} info_t;

#define INFO_INITIALIZER \
{ \
    NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0 \
}

typedef struct builtin
{
    char *type;
    int (*func)(info_t *);
} builtin_table;

int my_shell(info_t *, char **);
int find_builtin(info_t *);
void find_command(info_t *);
void execute_command(info_t *);

int custom_shell(char **);

void custom_shell_loop(info_t *);

void print_error_msg(char *);
int custom_putchar(char);
int custom_fd_putchar(char, int);
int custom_fd_puts(char *, int);

char *custom_strncpy(char *, char *, int);
char *custom_strncat(char *, char *, int);
char *custom_strchr(char *, char);

char *_memset(char *, char, unsigned int);
void free_string_array(char **);
void *custom_realloc(void *, unsigned int, unsigned int);

int free_buffer(void **);

int is_valid_command(info_t *, char *);
char *duplicate_string(char *, int, int);
char *find_command_path(info_t *, char *, char *);

int count_characters(char *, char *);
int is_alpha(int);
int custom_atoi(char *);

int is_chain_command(info_t *, char *, size_t *);
void process_chain_command(info_t *, char *, size_t *, size_t, size_t);
int substitute_alias(info_t *);
int substitute_variables(info_t *);
int substitute_string(char **, char *);

int custom_exit(info_t *);
int custom_cd(info_t *);
int custom_help(info_t *);

int custom_history(info_t *);
int custom_alias(info_t *);

ssize_t get_input_line(info_t *);
int custom_getline(info_t *, char **, size_t *);
void sigintHandler(int);

void clear_info(info_t *);
void initialize_info(info_t *, char **);
void free_info(info_t *, int);

char *get_history_filename(info_t *info);
int write_history_to_file(info_t *info);
int read_history_from_file(info_t *info);
int append_to_history_list(info_t *info, char *buffer, int linecount);
int renumber_history_list(info_t *info);

list_t *add_node_at_beginning(list_t **, const char *, int);
list_t *add_node_at_end(list_t **, const char *, int);
size_t print_list_strings(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_linked_list(list_t **);

size_t count_list_items(const list_t *);
char **list_to_string_array(list_t *);
size_t print_entire_list(const list_t *);
list_t *find_node_starting_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

char *_set_memory(char *s, char byte, unsigned int size);
void free_string_array(char **);
void *custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

int free_buffer(void **ptr);

int is_command(info_t *, char *path);
char *copy_string_chars(char *pathstr, int start, int stop);
char *find_command_in_path(info_t *, char *pathstr, char *command);

#endif

