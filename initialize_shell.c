#include "shell.h"

/**
 * initialize_shell - Initializes the shell_state_t struct with
 * startup values for various program-wide variables
 *
 * @shell_state: Pointer to the shell_state_t struct to initialize
 * @argc: Number of command-line arguments
 * @argv: Array of strings containing command-line arguments
 */
void initialize_shell(shell_state_t *shell_state, int argc, char *argv[])
{
	shell_state->prog_name			= argv[0];
	shell_state->input_line_count	= 0;
	shell_state->is_alive			= 1;
	shell_state->exit_status		= 0;
	shell_state->tokenized_commands = NULL;
	shell_state->startup_errno		= errno;
	shell_state->is_interactive		= 1;
	shell_state->child_exit_status	= 0;
	shell_state->environ			= copy_environment(environ);
	shell_state->in_file_mode		= 0;
	shell_state->fildes				= 99;

	if (argc == 2)
	{
		/*file mode*/
		shell_state->fildes = open(argv[1], O_RDONLY);
		if (shell_state->fildes == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		shell_state->in_file_mode = 1;
		/* print_output("mode: file: "); */
		/* print_output(argv[1]); */
		/* print_output("\n"); */
	}
}
