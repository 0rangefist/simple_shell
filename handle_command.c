#include "shell.h"

/**
 * handle_command - Determines what type of command has
 * been entered & deploys the right function to handle it
 *
 * @command: Array of command and argument strings.
 * @shell_state: Struct of current shell state variables
 */
void handle_command(char **command, shell_state_t *shell_state)
{
	/* pointer to a function that executes a shell builtin command*/
	void (*execute_builtin)(char **, shell_state_t *);

	if (command[0] == NULL) /*check for empty commands*/
		return;				/*delim ; followed by nothing causes NULL cmd*/

	/* get appropriate execute_builtin function */
	execute_builtin = get_builtin_function(command);
	if (execute_builtin != NULL) /*we have a builtin*/
	{
		execute_builtin(command, shell_state);
		if (shell_state->is_alive == 0) /*occurs for valid execute_exit*/
			return;
	}
	else /* we have an external command*/
	{
		execute_command(command, shell_state);
	}
}
