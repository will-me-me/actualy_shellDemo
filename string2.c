#include "shell.h"

/**
 **string_n_cpy - a function that copies n number of string
 *@dest: a pointer tothe dest string
 *@src: a pointer to the source string
 *@n: an int represents the number of chars to be copied
 *Return: returns a pointer to the concat string
 */
char *string_n_cpy(char *dest, char *src, int n)
{
	int m;

	for (m = 0; m < n && src[m] != '\0'; m++)
	{
		dest[m] = src[m];
	}
	for (; m < n; m++)
	{
		dest[m] = '\0';
	}

	return (dest);
}

/**
 **string_n_cat - a function that concatenates two strings
 *@dest: a pointer to the first string
 *@src: a pointer to the second string
 *@n: the number of bytesto be concated
 *Return: returns a pointer to string
 */
char *string_n_cat(char *dest, char *src, int n)
{
	int i;
	int dest_len;

	dest_len = get_string_length(dest);
	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[dest_len + 1] = src[i];
	}

	dest[dest_len + i] = '\0';
	return (dest);
}

/**
 **string_search - a function that locates a charc in a string
 *@str: a pointer to the string to be parsed
 *@c: the character search
 *Return: returns NULL or a pointer to a string
 */
char *string_search(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}

