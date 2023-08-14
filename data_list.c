#include "shell.h"

/**
 * information_clear - a function that initializes info_t struct
 * @data_list: struct address
 */
void information_clear(info_t *data_list)
{
	data_list->arg = NULL;
	data_list->argv = NULL;
	data_list->path = NULL;
	data_list->argc = 0;
}

/**
 * initialize_information - initializes info_t struct
 * @data_list: struct address
 * @av: argument vector
 */
void initialize_information(info_t *data_list, char **av)
{
	int i = 0;

	data_list->fname = av[0];
	if (data_list->arg)
	{
		data_list->argv = (char **)split_str(data_list->arg, " \t");
		if (!data_list->argv)
		{

			data_list->argv = malloc(sizeof(char *) * 2);
			if (data_list->argv)
			{
				data_list->argv[0] = duplicate_string_memory(data_list->arg);
				data_list->argv[1] = NULL;
			}
		}
		for (i = 0; data_list->argv && data_list->argv[i]; i++)
			;
		data_list->argc = i;

		perform_alias_replacement(data_list);
		perform_variable_replacement(data_list);
	}
}

/**
 * information_free - a function that frees info_t struct fields
 * @data_list: struct address
 * @all: true if freeing all fields
 */
void information_free(info_t *data_list, int all)
{
	free_pointer_and_contents(data_list->argv);
	data_list->argv = NULL;
	data_list->path = NULL;
	if (all)
	{
		if (!data_list->cmd_buf)
			free(data_list->arg);
		if (data_list->env)
			clear_linked_list(&(data_list->env));
		if (data_list->history)
			clear_linked_list(&(data_list->history));
		if (data_list->alias)
			clear_linked_list(&(data_list->alias));
		free_pointer_and_contents(data_list->environ);
			data_list->environ = NULL;
		free_and_null_pointer((void **)data_list->cmd_buf);
		if (data_list->readfd > 2)
			close(data_list->readfd);
		_putchar(BUF_FLUSH);
	}
}
