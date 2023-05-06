#include "shell.h"
/**
 * get_input - reads input from standard input
 * @shell_state: Struct of current shell state variables
 * Return: number input string or NULL otherwise
 */
char *get_input(shell_state_t *shell_state)
{
	char *input = NULL;
	int	  chars_read;
	int	  fd = STDIN_FILENO;

	if (shell_state->in_file_mode) /* switch from stdin to file */
		fd = shell_state->fildes;

	chars_read = get_line(&input, fd);
	(shell_state->input_line_count)++;

	/* if shell is non-interactive & no more chars to read from stdin */
	if (!(shell_state->is_interactive) && chars_read == -1)
		shell_state->is_alive = 0; /* kill the shell */
	/* read returns non-empty string */
	if (input != NULL && chars_read >= 1)
		return (input);

	/* else if input == NULL || chars_read < 1  */
	free(input);
	/* if errno is 0 then we had an EOF interrrupt */
	if (chars_read == -1 && errno == 0)
	{
		print_output("\n"); /* newline needed if shell dies from EOF */
		shell_state->is_alive = 0;
	}
	/* err of ENOTTY is excluded so we don't see that error when */
	/* stdin is not from a terminal device (non-interactive mode)*/
	else if (chars_read == -1 && errno != ENOTTY) /*errno !=0 is err*/
		perror("Error");
	/* return NULL for NULL/empty input or on error  */
	return (NULL);
}
