#include "shell.h"

/**
 * get_string_length - a function tha counts the length of a string
 * @str: a pointer to string to count
 * Return: returns an the number of the string
 */
int get_string_length(char *str)
{
	int n = 0;

	if (!str)
		return (0);

	while (*str++)
		n++;
	return (n);
}

/**
 * compare_strings - a function that compares to string
 * @str1: first param string
 * @str2: second param string
 * Return: returns an int 1, -1 or 0
 */
int compare_strings(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * find_prefix_in_string - a function to check string
 * @str: a pointer to string to search
 * @prefixs: a pointer to the prfix to find
 *
 * Return: returns an address of next char of str or NULL
 */
char *find_prefix_in_string(const char *str, const char *prefixs)
{
	while (*prefixs)
		if (*prefixs++ != *str++)
			return (NULL);
	return ((char *)str);
}

/**
 * concatenate_strings - a function that concatenates two strings
 * @str_dest: a pointer to the destination buffer
 * @str_src: a pointer to the source buffer
 * Return: returns a pointer to destination buffer
 */
char *concatenate_strings(char *str_dest, char *str_src)
{
	char *ret = str_dest;

	while (*str_dest)
		str_dest++;
	while (*str_src)
		*str_dest++ = *str_src++;
	*str_dest = *str_src;
	return (ret);
}

