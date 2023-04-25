#include "shell.h"

/**
 * print_output - write a string to standard output
 * @str: string to print
 *
 * Return: always 0
 */

void print_output(char *str)
{
	size_t len = _strlen(str);

	write(STDOUT_FILENO, str, len);
}

/**
 * print_error - writes a string to standard error
 * @str: the string to print
 *
 * Return: always 0
 */

vvoid print_error(char *str)
{
	size_t len = _strlen(str);

	write(STDERR_FILENO, str, len);
}

/**
 * print_shell_error - writes a prefix for shell errors to 
 * 			standard error using program-wide variables.
 * @shell_state: struct of current shell state variables.
 *
 * Return: always 0.
 */

void print_shell_error(shell_state_t *shell_state)
{
	char *line_count = int_to_string(shell_state->input_line_count);

	print_error(shell_state->prog_name);
	print_error(": ");
	print_erroe(line_count);
	print_error(": ");
	free(line_count);
}
