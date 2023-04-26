#include "shell.h"

/**
 * construct_env - Constructs a string representing an
 * environment variable
 *
 * @name: The name of the environment variable
 * @value: The value of the environment variable
 *
 * Return: A pointer to the constructed string, or NULL on failure
 */
char *construct_env(char *name, char *value)
{
	size_t name_len	 = _strlen(name);
	size_t value_len = _strlen(value);
	char  *env		 = malloc(name_len + value_len + 2); /*+2 for '=' and '\0'*/

	if (env == NULL)
	{
		return (NULL); /* allocation failed */
	}
	_strncpy(env, name, name_len + 1);
	_strcat(env, "=");
	_strcat(env, value);
	return (env);
}

/**
 * create_new_environ - Creates a new environment array from on an old one
 * & appends a new env variable or overwrites if it exists already
 *
 * @overwrite_index: The index of an environment variable to overwrite, or
 * -1 if a new environment variable is being added
 * @env: A string representing the new environment variable to add or
 * overwrite, in the form "NAME=value"
 * @shell_state: Program-wide shell state variables
 *
 * Return: A pointer to the new environment array, or NULL if allocation fails
 */
char **create_new_environ(int overwrite_index, char *env,
						  shell_state_t *shell_state)
{
	int	   i, num_of_envs;
	char **new_environ;

	/* get the number of environment variables in environ */
	num_of_envs = environ_size(shell_state);

	if (overwrite_index == -1)
	{
		/* allocate memory for new environment array with room */
		/* for 1 morevariable & null byte */
		new_environ = malloc((num_of_envs + 2) * sizeof(char *));
		if (new_environ == NULL) /*alloc fail*/
			return (NULL);

		/* copy old environment variables into new array */
		for (i = 0; i < num_of_envs; i++)
			new_environ[i] = shell_state->environ[i];

		/* add new environment variable */
		new_environ[num_of_envs]	 = env;
		new_environ[num_of_envs + 1] = NULL;

		/* free the memory of the old environ array */
		free(shell_state->environ);
	}
	else
	{
		/* overwrite existing environment variable */
		free(shell_state->environ[overwrite_index]);
		shell_state->environ[overwrite_index] = env;
		new_environ							  = shell_state->environ;
	}

	return (new_environ);
}

/**
 * add_env - Adds a new or overwrites an existing environment variable
 *
 * @name: The name of the environment variable
 * @value: The value of the environment variable
 * @shell_state: Program-wide shell state variables
 *
 * Return: 0 if successful, or -1 if allocation fails
 */
int add_env(char *name, char *value, shell_state_t *shell_state)
{
	int	   overwrite_index; /* index of env if it already exists in environ */
	char  *env;				/* fully constructed enviroment variable string */
	char **new_environ;		/* var to store the new updated environment*/

	/* construct the full environment variable string (NAME=value) */
	env = construct_env(name, value);
	if (env == NULL) /* allocation failed */
		return (-1);

	/* find the index of the env in environ if it exists*/
	overwrite_index = get_env_index(name, shell_state);

	/* create a new environ array with the constructed env appended */
	new_environ = create_new_environ(overwrite_index, env, shell_state);
	if (new_environ == NULL)
	{
		free(env);
		return (-1); /* allocation failed */
	}

	/* overwrite the old environ with the new updated one*/
	shell_state->environ = new_environ;

	return (0); /*environment variable successfully added*/
}

/**
 * execute_setenv - Executes the "setenv" command, adding a new or
 * overwriting an existing environment variable
 *
 * @cmd: An array of strings containing the command and its arguments
 * @shell_state: Program-wide shell state variables
 */
void execute_setenv(char **cmd, shell_state_t *shell_state)
{
	/* if no argument for unsetenv command*/
	if (cmd[1] == NULL || cmd[2] == NULL)
	{
		print_shell_error(shell_state);
		print_error(
			"setenv: too few arguments: usage: setenv [VARIABLE] [value]\n");
		return;
	}

	/* add the variable to the environment */
	if (add_env(cmd[1], cmd[2], shell_state) == -1)
	{
		/* if the add failed */
		print_shell_error(shell_state);
		print_error("setenv: failed to add the variable\n");
	}
}
