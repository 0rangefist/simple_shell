#include "shell.h"

/**
 * execute_unsetenv - Removes an environment variable from the shell's
 * environment.
 * @cmd: An array of strings containing the command and its arguments.
 * @shell_state: Program-wide shell state variables
 */
void execute_unsetenv(char **cmd, shell_state_t *shell_state)
{
	char *env_name = cmd[1];
	int	  env_index;

	/* if no argument for unsetenv command*/
	if (env_name == NULL)
	{
		print_shell_error(shell_state);
		print_error(
			"unsetenv: too few arguments: usage: unsetenv [VARIABLE]\n");
		return;
	}

	/* Search environment for variable*/
	env_index = get_env_index(env_name, shell_state);
	/* on failure, error variable already not in environment */
	if (env_index == -1)
	{
		print_shell_error(shell_state);
		print_error("unsetenv: variable already not in environment\n");
		return;
	}
	/* delete the env using the found index */
	delete_env_at_index(env_index, shell_state);
}
