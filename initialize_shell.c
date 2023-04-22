#include "shell.h"

/**
 * initialize_shell - Initializes the shell_state_t struct with
 * startup values for various program-wide variables
 *
 * @shell_state: Pointer to the shell_state_t struct to initialize
 * @argv: Array of strings containing command-line arguments
 */
void initialize_shell(shell_state_t *shell_state, char *argv[])
{
	shell_state->prog_name			= argv[0];
	shell_state->input_line_count	= 0;
	shell_state->is_alive			= 1;
	shell_state->exit_status		= 0;
	shell_state->tokenized_commands = NULL;
	shell_state->startup_errno		= errno;
}
