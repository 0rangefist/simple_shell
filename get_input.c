#include "shell.h"

/**
 * get_input - reads input from standard input
 *
 * Return: number input string or NULL otherwise
 */
char *get_input(void)
{
	char   *input			  = NULL;
	size_t	input_buffer_size = 0;
	ssize_t chars_read;

	chars_read = getline(&input, &input_buffer_size, stdin);

	if (chars_read <= 1) /* if empty input or error */
	{
		free(input);

		/* if errno is 0 then we had an eof interrrupt */
		if (chars_read == -1 && errno == 0) /*handle eof interrupt*/
			exit(EXIT_FAILURE);

		/* if errno > 0 then we had an error */
		else if (chars_read == -1 && errno > 0) /*handle error*/
			perror("Input Error A");

		/* return NULL on error or empty input */
		return (NULL);
	}

	return (input);
}

