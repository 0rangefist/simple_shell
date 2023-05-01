#include "shell.h"

/**
 * is_whitespace_string - checks if a string is empty or contains only
 * whitespace characters
 * @str: pointer to the string to check
 *
 * Return: 1 if string is empty/contains only whitespace, 0 otherwise
 */
int is_whitespace_string(char *str)
{
	int i;

	for (i = 0; i < _strlen(str); i++)
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r')
		{
			return (0);
		}
	}
	return (1);
}

/**
 * strip_lead_trail_whitespace - Removes leading and trailing whitespace
 * characters from a string.
 * @str: The string to be trimmed.
 */
void strip_lead_trail_whitespace(char *str)
{
	int start_index = 0;
	int end_index	= 0;
	int final_index = 0;

	if (str == NULL || str[0] == '\0') /*nothing to trim */
		return;
	if (is_whitespace_string(str)) /*make whitespace string empty */
	{
		str[0] = '\0';
		return;
	}

	/* skip leading whitespaces */
	while (str[start_index] == ' ' || str[start_index] == '\t'
		   || str[start_index] == '\n' || str[start_index] == '\r')
	{
		start_index++;
	}

	/* determine the end index */
	end_index = _strlen(str) - 1;
	/* iterate backward from end to 1st non-whitespace */
	while (str[end_index] == ' ' || str[end_index] == '\t'
		   || str[end_index] == '\n' || str[end_index] == '\r')
	{
		end_index--;
	}

	/* +1 to end_index to update it to the new end*/
	/* & overwrite the value there to a null byte */
	str[end_index + 1] = '\0';

	/* now copy the contents str fom start_idex to null byte */
	/* to the start of the string array */
	while (str[start_index] != '\0')
	{
		str[final_index++] = str[start_index++];
	}
	/* null terminate the string */
	str[final_index] = '\0';
}

/**
 * strip_all_whitespace - Removes all whitespace from a given string in place,
 * effectively creating a continuous string of chars from index 0
 * @str: Pointer to the string to be trimmed
 */
void strip_all_whitespace(char *str)
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
 * strip_repeated_whitespace - Removes repeated whitespace characters from a
 * buffer
 * @buff: Pointer to the buffer to modify
 * @buff_len: Length of the buffer in characters
 *
 * Return: The new length of the modified buffer.
 */
int strip_repeated_whitespace(char *buff, int buff_len)
{
	int	 i;					  /* loop index */
	int	 new_buff_len = 0;	  /* new number of chars in buff */
	char prev_char	  = '\0'; /* holds a copy of the previous char */
	char curr_char	  = '\0'; /* holds a copy of the current char */

	for (i = 0; i < buff_len; i++) /* loop over the buff */
	{
		curr_char = buff[i];
		/* check if the current character is a whitespace character */
		if (curr_char == ' ' || curr_char == '\t' || curr_char == '\n'
			|| curr_char == '\r')
		{
			/* check if the prev char is the same whitespace char */
			if (prev_char == curr_char) /* dont copy this char */
				continue;				/* skip this iteration of the loop */
			else
			{
				buff[new_buff_len] = curr_char; /*copy curr_char to new pos*/
				prev_char		   = curr_char; /* save curr_char as prev */
				new_buff_len++;					/* increment the new_buff_len */
			}
		}
		else /* curr char isnt a whitespace, copy to new position in buff */
		{
			buff[new_buff_len] = curr_char; /*copy curr_char to new pos*/
			prev_char		   = curr_char; /* save curr_char as prev */
			new_buff_len++;					/* increment the new_buff_len */
		}
	}
	return (new_buff_len); /* return the adjusted buffer_len */
}
