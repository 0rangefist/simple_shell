#include "shell.h"

/**
 * execute_exit - Builtin command that exits the shell program
 *
 * @cmd: array of command and arguments
 * @shell_state: Struct of current shell state variables
 *
 * Return: void
 */
void execute_exit(char **cmd, shell_state_t *shell_state)
{
	int exit_status = 0;

	if (cmd[1] == NULL) /* if 2nd argument is absent*/
	{
		shell_state->is_alive	 = 0;
		shell_state->exit_status = exit_status;
		return;
	}
	else /*else if 2nd argument is present*/
	{
		/* convert it into an int */
		exit_status = atoi(cmd[1]);

		/* exit_status is illegal if value returned by conversion is*/
		/* negative int OR 0 while first char of argument isn't '0'*/
		if (exit_status < 0 || (exit_status == 0 && cmd[1][0] != '0'))
		{
			fprintf(stderr, "%s: ", shell_state->prog_name);
			fprintf(stderr, "%d: %s: ", shell_state->input_line_count, cmd[0]);
			fprintf(stderr, "Illegal number: ");
			fprintf(stderr, "%s\n", cmd[1]);
			return;
		}
		else /*valid (non-illegal) exit_status value*/
		{
			shell_state->is_alive	 = 0;
			shell_state->exit_status = exit_status;
			return;
		}
	}
}
