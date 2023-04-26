#include "shell.h"

/**
 * remove_whitespace - Removes whitespace from a given string in place
 * @str: Pointer to the string to be trimmed
 */
void remove_whitespace(char *str)
{
	int i; /*index of full original string with whitespaces*/
	int j; /*index of modified shorter string without whitespaces*/

	/* copy non-whitespace characters to the start of the string */
	for (i = 0, j = 0; i < _strlen(str); i++)
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		{
			str[j] = str[i];
			j++;
		}
	}

	/* null terminate trimmed string*/
	str[j] = '\0';
}

/**
 * count_bad_semicolons - Detects invalid semicolon syntax in a string.
 * @str: The input string to analyze.
 *
 * Return: 0 if valid, 1 if single semicolon error, 2 if multiple semicolon
 * error.
 */
int count_bad_semicolons(char *str)
{
	int i;
	int semicolon_count = 0;

	/* check for leading semicolon */
	if (str[0] == ';')
	{
		/* check if next char is also semicolon */
		if (str[1] == ';') /* invalid multiple semicolon */
			return (2);

		else /* invalid single semicolon */
			return (1);
	}

	/*searches the string for repeated semi-colon*/
	for (i = 0; str[i + 1] != '\0'; i++)
	{
		if (str[i] == ';' && str[i + 1] == ';') /* if char is a semicolon */
		{
			semicolon_count = 2;
			break;
		}
	}

	if (semicolon_count == 2) /* invalid multiple semicolons */
		return (2);

	else /* valid single semicolon or none */
		return (0);
}

/**
 * print_semicolon_error - Prints a appropriate error message for
 * either single or multiple bad semicolon count
 *
 * @bad_semicolon_count: The number of semicolons detected in the token.
 * @shell_state: Struct of current shell state variables.
 */
void print_semicolon_error(int bad_semicolon_count, shell_state_t *shell_state)
{
	char semicolons[5]; /* semicolon string for error message */

	if (bad_semicolon_count == 1)
	{
		semicolons[0] = '"';
		semicolons[1] = ';';
		semicolons[2] = '"';
		semicolons[3] = '\0';
	}
	else /* bad_semicolon_count == 2 */
	{
		semicolons[0] = '"';
		semicolons[1] = ';';
		semicolons[2] = ';';
		semicolons[3] = '"';
		semicolons[4] = '\0';
	}

	/* print error for either single or multiple bad semicolon */
	print_shell_error(shell_state);
	print_error("Syntax error: ");
	print_error(semicolons);
	print_error(" unexpected\n");
}

/**
 * has_bad_syntax - Checks if a string contains invalid syntax.
 * @input: The input string to analyze.
 * @shell_state: Struct of current shell state variables
 * Return: 1 if bad syntax present and 0 otherwise.
 */
int has_bad_syntax(char *input, shell_state_t *shell_state)
{
	int	  bad_semicolon_count; /*num of bad syntax semicolons in string*/
	char *input_cpy = _strdup(input);

	/* trim input of all whitespace including inbetween words */
	remove_whitespace(input_cpy);

	/* get the count of bad semicolons - either 1 or 2 */
	/* 1 for single and 2 for multiple bad semicolons */
	bad_semicolon_count = count_bad_semicolons(input_cpy);
	free(input_cpy);

	/* if any bad semicolons are detected*/
	if (bad_semicolon_count > 0)
	{
		/*print custom error depending on if single or multi semicolon*/
		print_semicolon_error(bad_semicolon_count, shell_state);
		return (1);
	}

	/* no syntax error */
	return (0);
}
