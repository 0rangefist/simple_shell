#include "shell.h"

/**
 * split_into_commands - Tokenizes an input string into an array of
 * commands using ";" as the delimiter
 *
 * @input: The string to tokenize
 *
 * Return: Array of command strings or NULL otherwise
 */
char **split_into_commands(char *input)
{
	char **commands = NULL;
	char  *delim	= ";"; /* delimiter for the tokenization */

	commands = tokenize(input, delim);

	/* free memory pointed to by input & reset it to NULL */
	free(input);
	input = NULL;

	return (commands);
}
