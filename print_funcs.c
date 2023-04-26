#include "shell.h"

/**
 * print_output - writes a string to standard output
 * @str: the string to print
 */
void print_output(char *str)
{
	size_t len = _strlen(str);

	write(STDOUT_FILENO, str, len);
}

/**
 * print_error - writes a string to standard error
 * @str: the string to print
 */
void print_error(char *str)
{
	size_t len = _strlen(str);

	write(STDERR_FILENO, str, len);
}

/**
 * print_shell_error - writes a prefix for shell errors
 * to stderr using program-wide variables.
 * @shell_state: Struct of current shell state variables.
 */
void print_shell_error(shell_state_t *shell_state)
{
	char *line_count = int_to_string(shell_state->input_line_count);

	print_error(shell_state->prog_name);
	print_error(": ");
	print_error(line_count);
	print_error(": ");
	free(line_count);
}
