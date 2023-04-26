#include "shell.h"

/**
 * tokenize_commands - Tokenizes an array of command strings into an
 * array of arrays of tokens using whitespace as the delimiter
 *
 * @commands: The array of command strings to be tokenized
 *
 * Return: An array of arrays of tokens or NULL otherwise
 */
char ***tokenize_commands(char **commands)
{
	int		i;
	char   *delim = " \t\r\n\f\v"; /* delimiter for the tokenization */
	char ***tokenized_commands = NULL;
	char  **tokenized_command  = NULL;
	int		num_of_commands	   = 0;

	/* iterate over the commands array to count */
	while (commands[num_of_commands] != NULL)
	{
		num_of_commands++;
	}

	/* allocate memory for an array of array of strings */
	tokenized_commands = malloc((num_of_commands + 1) * sizeof(char **));
	if (tokenized_commands == NULL)
	{
		return (NULL); /*alloc failed*/
	}

	/* iterate over the commands array */
	for (i = 0; commands[i] != NULL; i++)
	{
		/* tokenize each command string into */
		/* an array of command and arguments */
		tokenized_command = tokenize((commands[i]), delim);

		free(commands[i]);

		/* save a sanitized tokenized command in */
		/* the tokenized_commands array */
		tokenized_commands[i] = tokenized_command;
	}
	free(commands);

	tokenized_commands[i] = NULL; /* terminate with null byte */

	return (tokenized_commands);
}
