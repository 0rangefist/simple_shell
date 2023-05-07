#include "shell.h"
/**
 * execute_commands - Sequentially executes an array of commands.
 * @commands: The array of commands to execute.
 * @shell_state: Struct of current shell state variables
 * Return: void.
 */
void execute_commands(char **commands, shell_state_t *shell_state)
{
	int i;

	/* save program-wide copy of commands to free deeper in prog */
	shell_state->commands = commands;

	/* iterate through the tokenized commands array */
	for (i = 0; commands[i] != NULL; i++)
	{
		logically_sequence_command(commands[i], shell_state);
		if (shell_state->is_alive == 0) /*if shell is killed by exit command*/
			return;/* return to main to exit */
	}
}
