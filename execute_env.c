#include "shell.h"

/**
 * execute_env - Builtin command that prints env
 *
 * @cmd: array of command and arguments
 * @shell_state: Struct of current shell state variables
 *
 * Return: void
 */
void execute_env(char **cmd, shell_state_t *shell_state)
{
	char **env = environ;

	if (*env == NULL)
	{
		fprintf(stderr, "%s: ", shell_state->prog_name);
		fprintf(stderr, "%d: %s: ", shell_state->input_line_count, cmd[0]);
		perror("");
	}
	else
	{
		while (*env)
		{
			printf("%s\n", *env);
			env++;
		}
	}
}
