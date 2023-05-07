#include "shell.h"

/**
 * handle_command - Processes a command from a string into
 * a token array, invokes the replacement of possible shell
 * variables in the token array, determines what type of command
 * has been entered & deploys the right function to execute it
 *
 * @cmd: command string possibly with its arguments.
 * @shell_state: Struct of current shell state variables
 */
void handle_command(char *cmd, shell_state_t *shell_state)
{
	char *delim	  = " \t\r\n\f\v";		  /* delimiFter for the tokenization */
	char **command = tokenize(cmd, delim); /* tokinized command array */
	/* pointer to a function that executes a shell builtin command*/
	void (*execute_builtin)(char **, shell_state_t *);

	replace_variables(command, shell_state); /* replace any shell variables */

	if (command[0] == NULL) /*check for empty commands*/
		return;				/*delim ; followed by nothing causes NULL cmd*/

	/* get appropriate execute_builtin function */
	execute_builtin = get_builtin_function(command);
	if (execute_builtin != NULL) /*we have a builtin*/
	{
		execute_builtin(command, shell_state);
		free_array(command);
		if (shell_state->is_alive == 0) /*occurs for valid execute_exit*/
			return;
	}
	else /* we have an external command*/
	{
		execute_command(command, shell_state);
		free_array(command);
	}
}
