#ifndef _SHELL_H_
#define _SHELL_H_

#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>

/* for read/write buffers */
#define read_buffer_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USEget_line 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct data_list - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct data_list
{
	int num;
	char *str;
	struct data_list *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
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

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


int run_shell_loop(info_t *, char **);
int find_and_execute_builtin_command(info_t *);
void search_and_execute_command(info_t *);
void fork_and_execute_command(info_t *);

int my_cmd_determiner(info_t *, char *);
char *character_duplicator(char *, int, int);
char *find_path(info_t *, char *, char *);

/* looprun_shell_loop.c */
/*int looprun_shell_loop(char **);*/

void print_error_string(char *);
int write_char_to_stderr(char);
int write_char_to_fd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_string.c */
int get_string_length(char *);
int compare_strings(char *, char *);
char *find_prefix_in_string(const char *, const char *);
char *concatenate_strings(char *, char *);

char *copy_string_to_destination(char *, char *);
char *duplicate_string_memory(const char *);
void string_puts(char *);
int _putchar(char);

char *string_n_cpy(char *, char *, int);
char *string_n_cat(char *, char *, int);
char *string_search(char *, char);

char **split_str(char *, char *);
/*char **split_str2(char *, char);*/


/* toem_realloc.c */
char *fill_memory_with_char(char *, char, unsigned int);
void free_pointer_and_contents(char **);
void *reallocate_memory_block(void *, unsigned int, unsigned int);

/* toem_memory.c */
int free_and_null_pointer(void **);


int inter_func(info_t *);
int is_delimiter(char, char *);
int my_isalpha(int);
int my_atoi(char *);

/* toem_errors1.c */
int String_to_Int_func(char *);
void ThemessageErrorFunc(info_t *, char *);
int printdecimalfunction(int, int);
char *to_char_converted(long int, int, int);
void rmv_cmnt(char *);

/* toem_builtin.c */
int _exit_once(info_t *);
int change_directory(info_t *);
int ask_help(info_t *);

/* toem_builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/*toemget_line.c */
ssize_t get_user_inputs(info_t *);
int get_line(info_t *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void information_clear(info_t *);
void initialize_information(info_t *, char **);
void information_free(info_t *, int);

/* toem_environ.c */
char *retrive_env(info_t *, const char *);
int initialize_env(info_t *);
int set_env(info_t *);
int unitialize_env(info_t *);
int env_populate(info_t *);

/* toemretrive_env.c */
char **environment_to_get(info_t *);
int _uninitialize_env(info_t *, char *);
int _env_init(info_t *, char *, char *);

/* toem_history.c */
char *recoverHistory(info_t *info);
int compute_history(info_t *info);
int review_history(info_t *info);
int list_of_history(info_t *info, char *buf, int linecount);
int count_of_history(info_t *info);

/* toem_lists.c */
list_t *add_list_node(list_t **, const char *, int);
list_t *append_list_node(list_t **, const char *, int);
size_t print_string_elements(const list_t *);
int remove_node_at_index(list_t **, unsigned int);
void clear_linked_list(list_t **);

/* toem_lists1.c */
size_t get_linked_list_length(const list_t *);
char **convert_linked_list_to_string_array(list_t *);
size_t print_linked_list(const list_t *);
list_t *find_matching_node(list_t *, char *, char);
ssize_t find_node_index(list_t *, list_t *);

/* toem_vars.c */
int is_command_chain_delimiter(info_t *, char *, size_t *);
void handle_command_chain(info_t *, char *, size_t *, size_t, size_t);
int perform_alias_replacement(info_t *);
int perform_variable_replacement(info_t *);
int replace_and_update_string(char **, char *);

#endif

