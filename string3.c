#include "shell.h"

/**
 * **split_str - a function that splits a string into words
 * @st: a pointer to the string
 * @delim: a pointer to the delimeter
 * Return: returns a pointer to an array of strings, or NULL on failure
 */

char **split_str(char *st, char *delim)
{
	int i, j, k, m, wordnum = 0;
	char **s;

	if (st == NULL || st[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (i = 0; st[i] != '\0'; i++)
		if (!is_delimiter(st[i],
		 delim) && (is_delimiter(st[i + 1], delim) || !st[i + 1]))
			wordnum++;

	if (wordnum == 0)
		return (NULL);
	s = malloc((1 + wordnum) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < wordnum; j++)
	{
		while (is_delimiter(st[i], delim))
			i++;
		k = 0;
		while (!is_delimiter(st[i + k], delim) && st[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = st[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}


/**
 * **strtow2 - a function that splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: returns a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
