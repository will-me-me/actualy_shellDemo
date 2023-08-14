#include "shell.h"

/**
 * initialize_env - a function that prints the curr env
 * @data_list: struct containing arguments.
 * Return: returns 0
 */
int initialize_env(info_t *data_list)
{
	print_string_elements(data_list->env);
	return (0);
}

/**
 * retrive_env - a funcrion that gets the value of an env var
 * @data_list: struct containing potential arguments
 * @str: env var string
 * Return: returns the value
 */
char *retrive_env(info_t *data_list, const char *str)
{
	list_t *node = data_list->env;
	char *ptr;

	while (node)
	{
		ptr = find_prefix_in_string(node->str, str);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * set_env - a function that initialize a new environment variable
 * @data_list: a struct containing potential arguments
 *  Return: returns 0
 */
int set_env(info_t *data_list)
{
	if (data_list->argc != 3)
	{
		print_error_string("Incorrect number of arguements\n");
		return (1);
	}
	if (_env_init(data_list, data_list->argv[1], data_list->argv[2]))
		return (0);
	return (1);
}

/**
 * unitialize_env - a function that removes an env var
 * @data_list: a struct containing potential arguments
 *  Return: returns 0
 */
int unitialize_env(info_t *data_list)
{
	int n;

	if (data_list->argc == 1)
	{
		print_error_string("Too few arguements.\n");
		return (1);
	}
	for (n = 1; n <= data_list->argc; n++)
		_uninitialize_env(data_list, data_list->argv[n]);

	return (0);
}

/**
 * env_populate - a function that populates env linked list
 * @data_list: a struct containing arguments
 * Return: returns 0 - success
 */
int env_populate(info_t *data_list)
{
	list_t *knot = NULL;
	size_t n;

	for (n = 0; environ[n]; n++)
		append_list_node(&knot, environ[n], 0);
	data_list->env = knot;
	return (0);
}

