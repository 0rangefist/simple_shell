#include "shell.h"

/**
 * get_num_of_tokens - Counts the number of tokens in a string based
 * on a given delimiter
 *
 * @str: The string to tokenize
 * @delim: The delimiter to use for tokenizing the string
 *
 * Return: The number of tokens in the string
 */
int get_num_of_tokens(const char *str, char *delim)
{
	int	  count	  = 0;
	char *str_cpy = _strdup(str);
	char *token	  = strtok(str_cpy, delim);

	while (token != NULL)
	{
		count++;
		token = strtok(NULL, delim);
	}
	/*printf("token count: %d\n", count);*/
	free(str_cpy);
	return (count);
}

/**
 * tokenize - Tokenizes an input string into an array of strings
 * based on a given delimiter
 *
 * @str: The string to tokenize
 * @delim: The delimiter to use for tokenizing the string
 *
 * Return: Array of strings containing tokens from the input string
 * or NULL otherwise
 */
char **tokenize(char *str, char *delim)
{
	char **token_arr;
	char  *token;
	int	   num_of_tokens;
	int	   i = 0;

	num_of_tokens = get_num_of_tokens(str, delim);

	/* alloc space for tokens + 1 for the null byte */
	token_arr = (char **) malloc(sizeof(char *) * (num_of_tokens + 1));
	if (token_arr == NULL)
	{
		return (NULL); /*alloc failed*/
	}

	/* tokenize the str and add into an array */
	token = strtok(str, delim); /* call first token */
	while (token != NULL)
	{
		token_arr[i] = _strdup(token);
		token		 = strtok(NULL, delim); /* call next token */
		i++;
	}
	token_arr[i] = NULL; /* set the last string to NULL */

	/*free(str);*/
	return (token_arr);
}

/**
 * tokenize_input - Tokenizes an input string into an array of
 * commands using ";" as the delimiter
 *
 * @input: The string to tokenize
 *
 * Return: Array of command strings or NULL otherwise
 */
char **tokenize_input(char *input)
{
	char **commands = NULL;
	char  *delim	= ";"; /* delimiter for the tokenization */

	commands = tokenize(input, delim);

	/* free memory pointed to by input & reset it to NULL */
	free(input);
	input = NULL;

	return (commands);
}

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
