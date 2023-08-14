#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vars
 * Return: returns 0 on success and 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int filesesc = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (filesesc)
		: "r" (filesesc));

	if (ac == 2)
	{
		filesesc = open(av[1], O_RDONLY);
		if (filesesc == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				print_error_string(av[0]);
				print_error_string(": 0: Can't open ");
				print_error_string(av[1]);
				write_char_to_stderr('\n');
				write_char_to_stderr(-1);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = filesesc;
	}
	env_populate(info);
	review_history(info);
	run_shell_loop(info, av);
	return (EXIT_SUCCESS);
}

