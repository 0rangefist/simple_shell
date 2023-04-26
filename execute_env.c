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
	char **env = shell_state->environ;

	if (*env == NULL)
	{
		print_shell_error(shell_state);
		print_error(cmd[0]);
		print_error(": ");
		perror("");
	}
	else
	{
		while (*env)
		{
			print_output(*env);
			print_output("\n");
			env++;
		}
	}
}
