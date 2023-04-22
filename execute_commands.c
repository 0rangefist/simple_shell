#include "shell.h"
/**
 * execute_commands - Sequentially executes an array of tokenized commands.
 * @tok_commands: The array of tokenized commands to execute.
 * @shell_state: Struct of current shell state variables
 * Return: void.
 */
void execute_commands(char ***tok_commands, shell_state_t *shell_state)
{
	int	 i;
	/* pointer to a function that executes a shell builtin command*/
	void (*execute_builtin)(char **, shell_state_t *);

	/* iterate through the tokenized commands array */
	for (i = 0; tok_commands[i] != NULL; i++)
	{
		if (tok_commands[i][0] == NULL) /*check for empty commands*/
		{
			continue; /*delim ; followed by nothing causes NULL cmd*/
		}

		/* get appropriate execute_builtin function */
		execute_builtin = get_builtin_function(tok_commands[i]);

		if (execute_builtin != NULL) /*we have a builtin*/
		{
			execute_builtin(tok_commands[i], shell_state);
			if (shell_state->is_alive == 0) /*occurs for valid execute_exit*/
				return;
		}
		else /* we have an external command*/
		{
			execute_command(tok_commands[i], shell_state);
		}
	}
}
