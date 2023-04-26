#include "shell.h"

/**
 * _atoi - converts a string to an integer
 * @str: the string to convert
 *
 * Return: the converted integer value
 */
int _atoi(const char *str)
{
	int result = 0;
	int sign   = 1;
	int i	   = 0;

	/* Skip leading whitespaces */
	while (str[i] == ' ')
	{
		i++;
	}

	/* Handle sign */
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
		{
			sign = -1;
		}
		i++;
	}

	/* Convert digits */
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}

	return (sign * result);
}

/**
 * is_positive_number - checks if string is a positive number
 * @str: the input string
 * Return: 1 if the string represents a positive number, 0 otherwise
 */
int is_positive_number(const char *str)
{
	int i = 0;

	/* Skip leading whitespaces */
	while (str[i] == ' ')
	{
		i++;
	}

	/* Check digits */
	while (str[i] >= '0' && str[i] <= '9')
	{
		i++;
	}

	/* Check end of string for null byte*/
	if (str[i] == '\0')
	{
		return (1);
	}

	return (0);
}

/**
 * execute_exit - Builtin command that exits the shell program
 *
 * @cmd: array of command and arguments
 * @shell_state: Struct of current shell state variables
 *
 * Return: void
 */
void execute_exit(char **cmd, shell_state_t *shell_state)
{
	int exit_status = 0;

	if (cmd[1] == NULL) /* if 2nd argument is absent*/
	{
		shell_state->is_alive = 0;
		return;
	}
	else /*else if 2nd argument is present*/
	{
		/* if string is a valid positive number */
		if (is_positive_number(cmd[1]) && cmd[2] == NULL)
		{
			/* convert it into an int */
			exit_status = _atoi(cmd[1]);
			shell_state->is_alive	 = 0;
			shell_state->exit_status = exit_status;
			return;
		}
		else /* illegal string (Not a number or is -ve)*/
		{
			print_shell_error(shell_state);
			print_error(cmd[0]);
			print_error(": ");
			print_error("Illegal number: ");
			print_error(cmd[1]);
			print_error("\n");
			return;
		}
	}
}
