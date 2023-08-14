#include "shell.h"

/**
 * _exit_once - a function that exits the shell
 * @data_list: a struct
 *  Return: return 1 or -1
 */
int _exit_once(info_t *data_list)
{
	int check_exit;

	if (data_list->argv[1])
	{
		check_exit = String_to_Int_func(data_list->argv[1]);
		if (check_exit == -1)
		{
			data_list->status = 2;
			ThemessageErrorFunc(data_list, "Illegal number: ");
			print_error_string(data_list->argv[1]);
			write_char_to_stderr('\n');
			return (1);
		}
		data_list->err_num = String_to_Int_func(data_list->argv[1]);
		return (-2);
	}
	data_list->err_num = -1;
	return (-2);
}

/**
 * change_directory - a function that changes the current dir
 * @data_list: a struct
 *  Return: returns 0
 */
int change_directory(info_t *data_list)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		string_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!data_list->argv[1])
	{
		dir = retrive_env(data_list, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = retrive_env(data_list, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (compare_strings(data_list->argv[1], "-") == 0)
	{
		if (!retrive_env(data_list, "OLDPWD="))
		{
			string_puts(s);
			_putchar('\n');
			return (1);
		}
		string_puts(retrive_env(data_list, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((dir = retrive_env(data_list, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(data_list->argv[1]);
	if (chdir_ret == -1)
	{
		ThemessageErrorFunc(data_list, "can't cd to ");
		print_error_string(data_list->argv[1]), write_char_to_stderr('\n');
	}
	else
	{
		_env_init(data_list, "OLDPWD", retrive_env(data_list, "PWD="));
		_env_init(data_list, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * ask_help -a function that changes the current directory of the process
 * @data_list: a struct containing potential arguments
 *  Return: returns 0
 */
int ask_help(info_t *data_list)
{
	char **arg_array;

	arg_array = data_list->argv;
	string_puts("help call works. Function not yet implemented \n");
	if (0)
		string_puts(*arg_array);
	return (0);
}
