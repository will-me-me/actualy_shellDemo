#include "shell.h"

/**
 * recoverHistory - a function that gets the history file
 * @data_list: a struct
 * Return: returns an allocated string
 */

char *recoverHistory(info_t *data_list)
{
	char *buf, *dir;

	dir = retrive_env(data_list, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (get_string_length(dir) + get_string_length(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	copy_string_to_destination(buf, dir);
	concatenate_strings(buf, "/");
	concatenate_strings(buf, HIST_FILE);
	return (buf);
}

/**
 * compute_history - a function that creates a file
 * @data_list: a struct
 * Return: returns 1 or-1
 */
int compute_history(info_t *data_list)
{
	ssize_t filedesc;
	char *name_file = recoverHistory(data_list);
	list_t *node = NULL;

	if (!name_file)
		return (-1);

	filedesc = open(name_file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(name_file);
	if (filedesc == -1)
		return (-1);
	for (node = data_list->history; node; node = node->next)
	{
		_putsfd(node->str, filedesc);
		write_char_to_fd('\n', filedesc);
	}
	write_char_to_fd(BUF_FLUSH, filedesc);
	close(filedesc);
	return (1);
}

/**
 * review_history - a function that reads history from file
 * @data_list: a struct
 * Return: returns  histcount or 0
 */
int review_history(info_t *data_list)
{
	int i, last = 0, count = 0;
	ssize_t filedesc, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = recoverHistory(data_list);

	if (!filename)
		return (0);

	filedesc = open(filename, O_RDONLY);
	free(filename);
	if (filedesc == -1)
		return (0);
	if (!fstat(filedesc, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(filedesc, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(filedesc);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			list_of_history(data_list, buf + last, count++);
			last = i + 1;
		}
	if (last != i)
		list_of_history(data_list, buf + last, count++);
	free(buf);
	data_list->histcount = count;
	while (data_list->histcount-- >= HIST_MAX)
		remove_node_at_index(&(data_list->history), 0);
	count_of_history(data_list);
	return (data_list->histcount);
}

/**
 * list_of_history - a function that adds entry to a history linked list
 * @data_list: a strunct
 * @str: a pointer to string
 * @count: an int count
 * Return: returns 0
 */
int list_of_history(info_t *data_list, char *str, int count)
{
	list_t *node = NULL;

	if (data_list->history)
		node = data_list->history;
	append_list_node(&node, str, count);

	if (!data_list->history)
		data_list->history = node;
	return (0);
}

/**
 * count_of_history - a function that counts the history
 * @data_list: a struct  containing potential arguments
 * Return: returns the new histcount
 */
int count_of_history(info_t *data_list)
{
	list_t *node = data_list->history;
	int n = 0;

	while (node)
	{
		node->num = n++;
		node = node->next;
	}
	return (data_list->histcount = n);
}
