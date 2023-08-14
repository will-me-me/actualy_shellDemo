#include "shell.h"

/**
 * _myhistory - a function that displays the history
 * @data_list: a struct
 *  Return: returns 0
 */
int _myhistory(info_t *data_list)
{
	print_linked_list(data_list->history);
	return (0);
}

/**
 * unset_alias - a fucntion that sets alias to string
 * @data_list:  struct
 * @str: the string alias
 * Return: returns 0 or 1
 */
int unset_alias(info_t *data_list, char *str)
{
	char *ptr, c;
	int ret;

	ptr = string_search(str, '=');
	if (!ptr)
		return (1);
	c = *ptr;
	*ptr = 0;
	ret =
	remove_node_at_index(&(data_list->alias),
		find_node_index(data_list->alias,
		find_matching_node(data_list->alias, str, -1)));
	*ptr = c;
	return (ret);
}

/**
 * set_alias - a function that sets alias to string
 * @data_list: struct
 * @str: a pointer to string
 * Return: returns 0
 */
int set_alias(info_t *data_list, char *str)
{
	char *ptr;

	ptr = string_search(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(data_list, str));

	unset_alias(data_list, str);
	return (append_list_node(&(data_list->alias), str, 0) == NULL);
}

/**
 * print_alias - a function that prints an alias string
 * @node: a struct
 * Return: returns a 0 or 1
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = string_search(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		string_puts(p + 1);
		string_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - a function that mimics the alias builtin
 * @data_list: struct
 *  Return: returns 0
 */

int _myalias(info_t *data_list)
{
	int i = 0;
	char *ptr = NULL;
	list_t *node = NULL;

	if (data_list->argc == 1)
	{
		node = data_list->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; data_list->argv[i]; i++)
	{
		ptr = string_search(data_list->argv[i], '=');
		if (ptr)
			set_alias(data_list, data_list->argv[i]);
		else
			print_alias(find_matching_node(data_list->alias, data_list->argv[i], '='));
	}

	return (0);
}
