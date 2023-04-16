#include "shell.h"

/**
 * main - The entry point of the program
 *
 * @argc: The number of command line arguments passed to the program
 * @argv: An array of strings containing the command line arguments
 * passed to the program
 *
 * Return: 0 on success, or an error code on failure
 */
int main(int argc, char *argv[])
{
	char  *input;		 /* unmodified input string entered by user */
	char **input_tokens; /* input tokenized into arr of command & arguments */
	char  *delim = " \t\r\n\f\v"; /* delimiter for the tokenization */

	(void) argc;
	(void) argv;

	while (1)
	{
		/* prompt user to enter commands */
		prompt_user();

		/* get the user input & save num of chars read */
		input = get_input();

		if (input == NULL) /* if empty input or error */
			continue;	   /*restart loop*/

		/* tokenize input into array of command & arguments */
		input_tokens = tokenize(input, delim);

		/* free memory pointed to by input & reset it to NULL */
		free(input);
		input = NULL;

		/* execute the command */
		execute_command(input_tokens);

		/* free the memory allocated for tokens */
		free_array(input_tokens);
	}

	free(input);

	/* handle potential errors */
	if (errno > 0) /* if errno is not 0 (eof interrrupt)*/
		perror("Input Error");

	return (0);
}
