#include "shell.h"

/**
 * is_command_chain_delimiter - a function that test if current char in buffer
 * @data_list: astruct
 * @buf: a pointer
 * @ptr: address of current position in buf
 * Return: retuens 1 if chain delimeter, 0 otherwise
 */
int is_command_chain_delimiter(info_t *data_list, char *buf, size_t *ptr)
{
	size_t j = *ptr;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		data_list->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		data_list->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		data_list->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = j;
	return (1);
}

/**
 * handle_command_chain - a function that checks we should continue chaining
 * @data_list: struct
 * @str: the char buffer
 * @ptr: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 */
void handle_command_chain(info_t *data_list,
char *str, size_t *ptr, size_t i, size_t len)
{
	size_t j = *ptr;

	if (data_list->cmd_buf_type == CMD_AND)
	{
		if (data_list->status)
		{
			str[i] = 0;
			j = len;
		}
	}
	if (data_list->cmd_buf_type == CMD_OR)
	{
		if (!data_list->status)
		{
			str[i] = 0;
			j = len;
		}
	}

	*ptr = j;
}

/**
 * perform_alias_replacement - a function that replaces an aliases in the tokenized string
 * @data_list: the parameter struct
 * Return: returns 1 if replaced, 0 otherwise
 */
int perform_alias_replacement(info_t *data_list)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = find_matching_node(data_list->alias, data_list->argv[0], '=');
		if (!node)
			return (0);
		free(data_list->argv[0]);
		p = string_search(node->str, '=');
		if (!p)
			return (0);
		p = duplicate_string_memory(p + 1);
		if (!p)
			return (0);
		data_list->argv[0] = p;
	}
	return (1);
}

/**
 * perform_variable_replacement - replaces vars in the tokenized string
 * @data_list: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int perform_variable_replacement(info_t *data_list)
{
	int i = 0;
	list_t *node;

	for (i = 0; data_list->argv[i]; i++)
	{
		if (data_list->argv[i][0] != '$' || !data_list->argv[i][1])
			continue;

		if (!compare_strings(data_list->argv[i], "$?"))
		{
			replace_and_update_string(&(data_list->argv[i]),
				duplicate_string_memory(to_char_converted(data_list->status, 10, 0)));
			continue;
		}
		if (!compare_strings(data_list->argv[i], "$$"))
		{
			replace_and_update_string(&(data_list->argv[i]),
				duplicate_string_memory(to_char_converted(getpid(), 10, 0)));
			continue;
		}
		node = find_matching_node(data_list->env, &data_list->argv[i][1], '=');
		if (node)
		{
			replace_and_update_string(&(data_list->argv[i]),
				duplicate_string_memory(string_search(node->str, '=') + 1));
			continue;
		}
		replace_and_update_string(&data_list->argv[i], duplicate_string_memory(""));

	}
	return (0);
}

/**
 * replace_and_update_string - a function thatreplaces string
 * @old: address of old string
 * @newstr: new string
 * Return: returns 1 if replaced, 0 otherwise
 */
int replace_and_update_string(char **old, char *newstr)
{
	free(*old);
	*old = newstr;
	return (1);
}

