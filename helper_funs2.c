#include "shell.h"

/**
 * String_to_Int_func - a function that converts a string to an integer
 * @str: the string to be converted
 * Return: 0 or the converted int
 */
int String_to_Int_func(char *str)
{
	int i = 0;
	unsigned long int num = 0;

	if (*str == '+')
		str++;
	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			num *= 10;
			num += (str[i] - '0');
			if (num > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (num);
}

/**
 * ThemessageErrorFunc - a function that prints an error
 * @data: a pointer to info_t struct
 * @err: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void ThemessageErrorFunc(info_t *data, char *err)
{
	print_error_string(data->fname);
	print_error_string(": ");
	printdecimalfunction(data->line_count, STDERR_FILENO);
	print_error_string(": ");
	print_error_string(data->argv[0]);
	print_error_string(": ");
	print_error_string(err);
}

/**
 * printdecimalfunction - function that prints a number
 * @dt: an int param
 * @filedes: file descriptor to write to
 * Return: returns the number of chars printed
 */
int printdecimalfunction(int dt, int filedes)
{
	int (*__putchar)(char) = _putchar;
	int i, num = 0;
	unsigned int absolute_, curr;

	if (filedes == STDERR_FILENO)
		__putchar = write_char_to_stderr;
	if (dt < 0)
	{
		absolute_ = -dt;
		__putchar('-');
		num++;
	}
	else
		absolute_ = dt;
	curr = absolute_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absolute_ / i)
		{
			__putchar('0' + curr / i);
			num++;
		}
		curr %= i;
	}
	__putchar('0' + curr);
	num++;

	return (num);
}

/**
 * to_char_converted - a function that converta num to a string
 * @num: long int number
 * @base: int base
 * @flags: int argument flag
 * Return: returns a string
 */
char *to_char_converted(long int num, int base, int flags)
{
	static char *arr;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = arr[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * rmv_cmnt - a function that replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 * Return: returns 0;
 */
void rmv_cmnt(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
