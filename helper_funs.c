#include "shell.h"
/**
 * inter_func - a function that returns true if shell is interactive mode
 * @data: struct address
 * Return: returns 1 or 0
 */
int inter_func(info_t *data)
{
	return (isatty(STDIN_FILENO) && data->readfd <= 2);
}

/**
 * is_delimiter - a function that checks if char is a delimeter
 * @s: char to check
 * @delimeter: the delimeter string
 * Return: returns 1 if true, 0 if false
 */
int is_delimiter(char s, char *delimeter)
{
	while (*delimeter)
		if (*delimeter++ == s)
			return (1);
	return (0);
}

/**
 *my_isalpha - a function that checks for alphabetic char
 *@c: The character to input
 *Return: returns 1 or 0.
 */

int my_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *my_atoi - a function that converts a string to an integer
 *@s: a string to be converted
 *Return: returns 0 or the coverted int
 */

int my_atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
