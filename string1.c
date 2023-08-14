#include "shell.h"

/**
 * copy_string_to_destination - a function that copies a string
 * @str_dest: a pointer to the str_destination
 * @str_src: a pointer to the source string
 * Return: returns a pointer to str_destination
 */
char *copy_string_to_destination(char *str_dest, char *str_src)
{
	int n = 0;

	if (str_dest == str_src || str_src == 0)
		return (str_dest);
	while (str_src[n])
	{
		str_dest[n] = str_src[n];
		n++;
	}
	str_dest[n] = 0;
	return (str_dest);
}

/**
 * duplicate_string_memory - a function that duplicates a string
 * @str: a pointer to the string to duplicate
 * Return: returns a pointer to string
 */
char *duplicate_string_memory(const char *str)
{
	int len = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	for (len++; len--;)
		ret[len] = *--str;
	return (ret);
}

/**
 *string_puts - a function that prints an input string
 *@st: a pointer the string to be printed
 */
void string_puts(char *st)
{
	int n = 0;

	if (!st)
		return;
	while (st[n] != '\0')
	{
		_putchar(st[n]);
		n++;
	}
}


/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

