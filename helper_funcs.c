#include "shell.h"

/**
 * _getenv - searches for the environment string pointed to by env_name
 * @env_name: string representing the environment variable name
 * @shell_state: current program-wide shell state variables
 *
 * Return: On success, value of the environment variable, otherwise NULL.
 */
char *_getenv(char *env_name, shell_state_t *shell_state)
{
	char **envp = shell_state->environ;
	size_t len	= _strlen(env_name);

	for (; *envp != NULL; envp++)
	{
		/* search environment for env_name */
		if (_strncmp(*envp, env_name, len) == 0)
		{
			/*save only the env value without the VAR= */
			return (*envp + len + 1);
		}
	}
	/*return NULL if variable isn't found in the environment */
	return (NULL);
}

/**
 * int_to_string - convert an integer to a string dynamically
 * @num: the integer to convert
 *
 * Return: a dynamically allocated string containing the
 * integer's decimal representation, or NULL if an error
 * occurred during allocation.
 */
char *int_to_string(int num)
{
	char *str;
	int	  temp	 = num;
	int	  digits = 0;
	int	  i;

	if (num == 0) /*handle base case*/
		digits = 1;
	else
	{
		while (temp != 0)
		{
			temp /= 10;
			digits++;
		}
	}

	str = (char *) malloc(digits + 1);
	if (!str) /*alloc fail*/
		return (NULL);

	if (num == 0)
	{
		str[0] = '0';
		str[1] = '\0';
	}
	else
	{
		i = digits - 1;
		while (num != 0)
		{
			str[i--] = '0' + (num % 10);
			num /= 10;
		}
		str[digits] = '\0';
	}

	return (str);
}

/**
 * get_array_size - get size of null terminated array
 * @array: array to determin size of
 *
 * Return: int of array size
 */
int get_array_size(char **array)
{
	int i;
	int size = 0;

	for (i = 0; array[i] != NULL; i++)
	{
		size++;
	}
	return (size);
}

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
 * trim_lead_trail_spaces - Removes leading and trailing whitespace
 * characters from a string.
 * @str: The string to be trimmed.
 */
void trim_lead_trail_spaces(char *str)
{
	int start_index = 0;
	int end_index	= 0;
	int final_index = 0;

	if (str == NULL || str[0] == '\0') /*nothing to trim */
		return;

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
