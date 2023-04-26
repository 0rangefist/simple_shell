#include "shell.h"

/**
 * prompt_user - prints a prompt to ask for user input
 * @shell_state: Struct of current shell state variables
 */
void prompt_user(shell_state_t *shell_state)
{
	/* shell is interactive if stdin is from a terminal */
	shell_state->is_interactive = isatty(STDIN_FILENO);
	if (shell_state->in_file_mode)
	{
		shell_state->is_interactive = 0;
	}

	/* print user prompt if shell is in interactive mode */
	if (shell_state->is_interactive)
	{
		print_output("$ ");
		fflush(stdout);
	}
}
