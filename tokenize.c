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
