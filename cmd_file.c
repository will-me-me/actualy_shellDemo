#include "shell.h"
#include <sys/types.h>

/**
 * my_cmd_determiner -a function that determines if a file is an executable command
 * @data_list: struct fata
 * @path: path to the file
 * Return: returns 1
 */
int my_cmd_determiner(info_t *data_list, char *path)
{
	struct stat st;

	(void)data_list;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & __S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * character_duplicator - a function that duplicates characters
 * @str: the PATH string
 * @start: starting index
 * @stop: stopping index
 * Return: pointer to new buffer
 */
char *character_duplicator(char *str, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (str[i] != ':')
			buf[k++] = str[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - a function that finds this cmd in the PATH string
 * @data_list: struct
 * @str: string Path
 * @cmd: the cmd to find
 * Return: returns full path of cmd if found or NULL
 */
char *find_path(info_t *data_list, char *str, char *cmd)
{
	int i = 0, current = 0;
	char *path;

	if (!str)
		return (NULL);
	if ((get_string_length(cmd) > 2) && find_prefix_in_string(cmd, "./"))
	{
		if (my_cmd_determiner(data_list, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!str[i] || str[i] == ':')
		{
			path = character_duplicator(str, current, i);
			if (!*path)
				concatenate_strings(path, cmd);
			else
			{
				concatenate_strings(path, "/");
				concatenate_strings(path, cmd);
			}
			if (my_cmd_determiner(data_list, path))
				return (path);
			if (!str[i])
				break;
			current = i;
		}
		i++;
	}
	return (NULL);
}
