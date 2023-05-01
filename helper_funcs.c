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
