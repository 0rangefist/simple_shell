#include "shell.h"

/**
 * detect_bad_semicolons - Detects invalid semicolon syntax in a string.
 * @str: The input string to analyze.
 *
 * Return: 0 if valid, 1 if single semicolon error, 2 if multiple semicolon
 * error.
 */
int detect_bad_semicolons(char *str)
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
 * has_bad_syntax - Checks if a string contains invalid syntax.
 * @input: The input string to analyze.
 * @shell_state: Struct of current shell state variables
 * Return: 1 if bad syntax present and 0 otherwise.
 */
int has_bad_syntax(char *input, shell_state_t *shell_state)
{
	char  *delim			 = " \t\r\n\f\v"; /* whitespace delimiter */
	char **input_tokens		 = NULL;		  /* tokenized input */
	int	   num_of_semicolons = 0; /*number of bad semicolons detected*/
	char   semicolons[5];		  /*semicolon string for error message*/
	int	   i;
	char *input_cpy = _strdup(input);

	input_tokens = tokenize(input_cpy, delim);
	for (i = 0; input_tokens[i] != NULL; i++)
	{
		num_of_semicolons = detect_bad_semicolons(input_tokens[i]);
		if (num_of_semicolons == 1) /*single bad semicolon error*/
		{
			semicolons[0] = '"';
			semicolons[1] = ';';
			semicolons[2] = '"';
			semicolons[3] = '\0';
		}
		if (num_of_semicolons == 2) /*multiple bad semicolon error*/
		{
			semicolons[0] = '"';
			semicolons[1] = ';';
			semicolons[2] = ';';
			semicolons[3] = '"';
			semicolons[4] = '\0';
		}
		if (num_of_semicolons > 0)
		{ /* print error for either single or multiple bad semicolon*/
			fprintf(stderr, "%s: ", shell_state->prog_name);
			fprintf(stderr, "%d: ", shell_state->input_line_count);
			fprintf(stderr, "Syntax error: ");
			fprintf(stderr, "%s unexpected\n", semicolons);
			free_array(input_tokens);
			free(input_cpy);
			return (1);
		}
	} /* no syntax error */
	free_array(input_tokens);
	free(input_cpy);
	return (0);
}
