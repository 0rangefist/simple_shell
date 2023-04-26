#include "shell.h"

/**
 * ignore_comment - Replaces a '#' character in a string with a null
 * terminator, effectively "ignoring" any characters that come after
 * the '#' character.
 *
 * @input: The input string to be processed.
 */
void ignore_comment(char *input)
{
	int i;

	for (i = 0; input[i] != '\0'; i++)
	{
		/* we have a comment if # is found & it is the 1st char OR*/
		/* if a subsequent # is found & is preceeded by whitespace */
		if ((input[i] == '#' && i == 0)
			|| (input[i] == '#'
				&& (input[i - 1] == ' ' || input[i - 1] == '\t')))
		{
			input[i] = '\0'; /* # is replaced by null byte */
			break;
		}
	}
}
