#include "shell.h"
/**
 * replace_variable - replaces shell variables with their
 * respective values
 * @tok: pointer to a string containing a shell variable
 * @shell_state: struct of current shell state variables
 */
void replace_variable(char **tok, shell_state_t *shell_state)
{
	char *env_name	= NULL; /* env var name eg. $PATH, $?, $$, etc */
	char *env_value = NULL; /* value held by the env var */

	if ((*tok)[0] == '$')
	{
		if ((*tok)[1] == '\0') /*if next char after $ is null byte */
			return;			   /* don't attempt a replacement */
		else if ((*tok)[1] == '?')
		{
			/*save the last exit status returned by a child process */
			env_value = int_to_string(shell_state->child_exit_status);
		}
		else if ((*tok)[1] == '$')
		{
			/* save the process ID of the shell program */
			env_value = int_to_string(getpid());
		}
		else
		{
			/* search the environment for the variable */
			env_name  = *tok + 1;
			env_value = _strdup(_getenv(env_name, shell_state));
		}

		/* replace the variable with value if it's found */
		if (env_value != NULL)
		{
			free(*tok);
			*tok = malloc(_strlen(env_value) + 1);
			_strncpy(*tok, env_value, _strlen(env_value) + 1);
		}
		free(env_value);
	}
}

/**
 * replace_variables - iterates through the tokenized commands
 * and replaces shell variables with their respective values
 * @tok_commands: pointer to a 2D array of tokenized commands
 * @shell_state: struct of current shell state variables
 *
 * Return: No return value
 */
void replace_variables(char ***tok_commands, shell_state_t *shell_state)
{
	int i, j;

	/* for each command */
	for (i = 0; tok_commands[i] != NULL; i++)
	{
		/* for each token of a command */
		for (j = 0; tok_commands[i][j] != NULL; j++)
		{
			/* Replace the env with its value */
			replace_variable(&tok_commands[i][j], shell_state);
		}
	}
}
