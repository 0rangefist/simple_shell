#include "shell.h"

/**
 * get_input - reads input from standard input
 * @shell_state: Struct of current shell state variables
 * Return: number input string or NULL otherwise
 */
char *get_input(shell_state_t *shell_state)
{
	char   *input			  = NULL;
	size_t	input_buffer_size = 0;
	ssize_t chars_read;

	chars_read = getline(&input, &input_buffer_size, stdin);
	(shell_state->input_line_count)++;

	if (input != NULL && chars_read > 1)
	{
		clearerr(stdin); /*clear err & eof flags on stdin*/
		return (input);
	}
	else /* if empty input or error */
	{
		free(input);
		/* if errno is 0 then we had an eof interrrupt */
		if (chars_read == -1 && errno == 0) /*handle eof interrupt*/
		{
			printf("\n");
			shell_state->is_alive	 = 0;
			shell_state->exit_status = 0;
		}

		/* if errno > 0 then we had an error */
		else if (chars_read == -1 && errno > 0) /*handle error*/
			perror("Error");

		/* return NULL on error or empty input */
		return (NULL);
	}
}
