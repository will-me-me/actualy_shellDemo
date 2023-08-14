#include "shell.h"

/**
 * environment_to_get - a function that returns the string array copy
 * @data_list: a struct of members
 * Return: returns 0
 */
char **environment_to_get(info_t *data_list)
{
	if (!data_list->environ || data_list->env_changed)
	{
		data_list->environ = convert_linked_list_to_string_array(data_list->env);
		data_list->env_changed = 0;
	}

	return (data_list->environ);
}

/**
 * _uninitialize_env - a function that remove an environment variable
 * @data_list: a struct data_list containing potential argument
 * @str: a pointer to string
 *  Return: returns 1 or
 */
int _uninitialize_env(info_t *data_list, char *str)
{
	list_t *node = data_list->env;
	size_t n = 0;
	char *ptr;

	if (!node || !str)
		return (0);

	while (node)
	{
		ptr = find_prefix_in_string(node->str, str);
		if (ptr && *ptr == '=')
		{
			data_list->env_changed = remove_node_at_index(&(data_list->env), n);
			n = 0;
			node = data_list->env;
			continue;
		}
		node = node->next;
		n++;
	}
	return (data_list->env_changed);
}

/**
 * _env_init - a function that initialize a new environment variable
 * @data_list: struct data_list
 * @str: a pointer to sytring
 * @value: a pointer to string
 *  Return: retruns 0
 */
int _env_init(info_t *data_list, char *str, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *ptr;

	if (!str || !value)
		return (0);

	buf = malloc(get_string_length(str) + get_string_length(value) + 2);
	if (!buf)
		return (1);
	copy_string_to_destination(buf, str);
	concatenate_strings(buf, "=");
	concatenate_strings(buf, value);
	node = data_list->env;
	while (node)
	{
		ptr = find_prefix_in_string(node->str, str);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buf;
			data_list->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	append_list_node(&(data_list->env), buf, 0);
	free(buf);
	data_list->env_changed = 1;
	return (0);
}
