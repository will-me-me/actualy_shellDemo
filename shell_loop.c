#include "shell.h"

/**
 * run_shell_loop - a function thatmain shell loop
 * @data_list: the parameter & return info struct
 * @av: the argument vector from main()
 * Return: return 0 or 1
 */
int run_shell_loop(info_t *data_list, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		information_clear(data_list);
		if (inter_func(data_list))
			string_puts("welcome to shell Will/Munene$ ");
		write_char_to_stderr(BUF_FLUSH);
		r = get_user_inputs(data_list);
		if (r != -1)
		{
			initialize_information(data_list, av);
			builtin_ret = find_and_execute_builtin_command(data_list);
			if (builtin_ret == -1)
				search_and_execute_command(data_list);
		}
		else if (inter_func(data_list))
			_putchar('\n');
		information_free(data_list, 0);
	}
	compute_history(data_list);
	information_free(data_list, 1);
	if (!inter_func(data_list) && data_list->status)
		exit(data_list->status);
	if (builtin_ret == -2)
	{
		if (data_list->err_num == -1)
			exit(data_list->status);
		exit(data_list->err_num);
	}
	return (builtin_ret);
}

/**
 * find_and_execute_builtin_command - finds a builtin command
 * @data_list: the parameter & return info struct
 * Return: -1 or 0 or 1 or 2
 */
int find_and_execute_builtin_command(info_t *data_list)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _exit_once},
		{"env", initialize_env},
		{"help", ask_help},
		{"history", _myhistory},
		{"setenv", set_env},
		{"unsetenv", unitialize_env},
		{"cd", change_directory},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (compare_strings(data_list->argv[0], builtintbl[i].type) == 0)
		{
			data_list->line_count++;
			built_in_ret = builtintbl[i].func(data_list);
			break;
		}
	return (built_in_ret);
}

/**
 * search_and_execute_command - afunction that finds a command in PATH
 * @data_list: the parameter & return info struct
 */
void search_and_execute_command(info_t *data_list)
{
	char *path = NULL;
	int i, k;

	data_list->path = data_list->argv[0];
	if (data_list->linecount_flag == 1)
	{
		data_list->line_count++;
		data_list->linecount_flag = 0;
	}
	for (i = 0, k = 0; data_list->arg[i]; i++)
		if (!is_delimiter(data_list->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(data_list, retrive_env(data_list, "PATH="), data_list->argv[0]);
	if (path)
	{
		data_list->path = path;
		fork_and_execute_command(data_list);
	}
	else
	{
		if ((inter_func(data_list) || retrive_env(data_list, "PATH=")
			|| data_list->argv[0][0] == '/') && my_cmd_determiner(data_list, data_list->argv[0]))
			fork_and_execute_command(data_list);
		else if (*(data_list->arg) != '\n')
		{
			data_list->status = 127;
			ThemessageErrorFunc(data_list, "not found\n");
		}
	}
}

/**
 * fork_and_execute_command - a function forks a an exec thread to run cmd
 * @data_list: the parameter & return info struct
 * Return: void
 */
void fork_and_execute_command(info_t *data_list)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(data_list->path, data_list->argv, environment_to_get(data_list)) == -1)
		{
			information_free(data_list, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(data_list->status));
		if (WIFEXITED(data_list->status))
		{
			data_list->status = WEXITSTATUS(data_list->status);
			if (data_list->status == 126)
				ThemessageErrorFunc(data_list, "Permission denied\n");
		}
	}
}

