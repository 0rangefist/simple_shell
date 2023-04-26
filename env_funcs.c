#include "shell.h"
/**
 * environ_size - Gets the size of the environment variable array
 * @shell_state: Program-wide shell state variables
 *
 * Return: The size of the environment variable array
 */
int environ_size(shell_state_t *shell_state)
{
	char **environ = shell_state->environ;
	int	   count   = 0;

	while (environ[count] != NULL)
	{
		count++;
	}
	return (count);
}

/**
 * get_env_index - Gets the index of the specified environment variable
 * @env_name: The name of the environment variable to search for
 * @shell_state: Program-wide shell state variables
 *
 * Return: The index of the environment variable if found, otherwise -1
 */
int get_env_index(char *env_name, shell_state_t *shell_state)
{
	int	   i = 0;
	int	   stat;
	char **environ = shell_state->environ;

	while (environ[i] != NULL)
	{
		stat = _strncmp(env_name, environ[i], _strlen(env_name));
		if (stat == 0 && environ[i][_strlen(env_name)] == '=')
		{
			/* variable found */
			return (i); /*return the index*/
		}
		i++;
	}
	/* variable not found */
	return (-1);
}

/**
 * delete_env_at_index - Deletes the environment variable at the
 * specified index
 * @index: The index of the environment variable to delete
 * @shell_state: Program-wide shell state variables
 */
void delete_env_at_index(int index, shell_state_t *shell_state)
{
	int	   i;
	char **environ = shell_state->environ;

	free(environ[index]);
	/* Shift all pointers after the deleted index to the left */
	for (i = index; environ[i + 1] != NULL; i++)
	{
		environ[i] = environ[i + 1];
	}

	/* Update the last pointer to NULL */
	environ[environ_size(shell_state) - 1] = NULL;
}

/**
 * copy_environment - Creates a copy of the environment variable array
 * @environ: The environment variable array to copy
 *
 * Return: A copy of the environment variable array
 */
char **copy_environment(char **environ)
{
	char **new_environ = NULL;
	int i, j;

	/* Count the number of environment variables */
	int num_of_envs = 0;

	while (environ[num_of_envs])
	{
		num_of_envs++;
	}

	/* Allocate a new array to hold the environment variables */
	new_environ = malloc(sizeof(char *) * (num_of_envs + 1));
	if (!new_environ) /* alloc fail */
		return (NULL);

	/* Loop through environ array & copy each string to new array */
	i = 0;
	while (environ[i])
	{
		new_environ[i] = _strdup(environ[i]);
		if (!new_environ[i]) /*duplication fail*/
		{
			/* Free memory for any strings previously allocated */
			j = 0;
			while (j < i)
			{
				free(new_environ[j]);
				j++;
			}
			free(new_environ);
			return (NULL);
		}
		i++;
	}
	/* Terminate the new array with a null pointer */
	new_environ[i] = NULL;
	return (new_environ);
}
