#include "shell.h"
/**
 * replace_variable - replaces shell variables with their
 * respective values
 * @token: pointer to string possibly containing a shell variable
 * @shell_state: struct of current shell state variables
 */
void replace_variable(char **token, shell_state_t *shell_state)
{
	char *env_name	= NULL; /* env var name eg. $PATH, $?, $$, etc */
	char *env_value = NULL; /* value held by the env var */

	if ((*token)[0] == '$')
	{
		if ((*token)[1] == '\0') /*if next char after $ is null byte */
			return;			   /* don't attempt a replacement */
		else if ((*token)[1] == '?')
		{
			/*save the last exit status returned by a child process */
			env_value = int_to_string(shell_state->exit_status);
		}
		else if ((*token)[1] == '$')
		{
			/* save the process ID of the shell program */
			env_value = int_to_string(getpid());
		}
		else
		{
			/* search the environment for the variable */
			env_name  = *token + 1;
			env_value = _strdup(_getenv(env_name, shell_state));
		}

		/* replace the variable with "" if not found */
		if (env_value == NULL)
		{
			env_value = _strdup("");
		}
		free(*token);
		*token = malloc(_strlen(env_value) + 1);
		_strncpy(*token, env_value, _strlen(env_value) + 1);
		free(env_value);
	}
}

/**
 * replace_variables - iterates through the commands array
 * and replaces shell variables with their respective values
 * @command_tokens: tokenized command array
 * @shell_state: struct of current shell state variables
 *
 * Return: No return value
 */
void replace_variables(char **command_tokens, shell_state_t *shell_state)
{
	int i;

	/* for each token of a command */
	for (i = 0; command_tokens[i] != NULL; i++)
	{
		/* Replace the shell variable with its value */
		replace_variable(&command_tokens[i], shell_state);
	}
}
