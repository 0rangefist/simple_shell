#include "shell.h"
/**
 * execute_commands - Sequentially executes an array of tokenized commands.
 * @tok_commands: The array of tokenized commands to execute.
 * @shell_state: Struct of current shell state variables
 * Return: void.
 */
void execute_commands(char ***tok_commands, shell_state_t *shell_state)
{
	int i;

	/* save program-wide copy of tok_commands to free deeper in prog */
	shell_state->tokenized_commands = tok_commands;

	/* iterate through the tokenized commands array */
	for (i = 0; tok_commands[i] != NULL; i++)
	{
		logically_sequence_command(tok_commands[i], shell_state);
	}
}
