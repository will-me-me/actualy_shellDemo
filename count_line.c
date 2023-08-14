#include "shell.h"
#include "signal.h"

/**
 * buffer_of_inputs - buffers chained commands
 * @data_link: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t buffer_of_inputs(info_t *data_link, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)data_link->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USEget_line
		r = getline(buf, &len_p, stdin);
#else
		r = get_line(data_link, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			data_link->linecount_flag = 1;
			rmv_cmnt(*buf);
			list_of_history(data_link, *buf, data_link->histcount++);
			{
				*len = r;
				data_link->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_user_inputs - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_user_inputs(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = buffer_of_inputs(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		handle_command_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_command_chain_delimiter(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (get_string_length(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buffer - a function that reads a buffer
 * @data_list: struct
 * @buf: buffer
 * @i: size
 * Return: returns r
 */
ssize_t read_buffer(info_t *data_list, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(data_list->readfd, buf, read_buffer_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * get_line - a function thatgets the next line of input from STDIN
 * @data_link: struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 * Return: s
 */
int get_line(info_t *data_link, char **ptr, size_t *length)
{
	static char buf[read_buffer_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buffer(data_link, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = string_search(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = reallocate_memory_block(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		string_n_cat(new_p, buf + i, k - i);
	else
		string_n_cpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	string_puts("\n");
	string_puts("$ ");
	_putchar(BUF_FLUSH);
}
