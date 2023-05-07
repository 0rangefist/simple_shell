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
	shell_state->prog_name		  = argv[0];
	shell_state->input_line_count = 0;
	shell_state->is_alive		  = 1;
	shell_state->exit_status	  = 0;
	shell_state->commands		  = NULL;
	shell_state->startup_errno	  = errno;
	shell_state->is_interactive	  = 1;
	shell_state->environ		  = copy_environment(environ);
	shell_state->in_file_mode	  = 0;
	shell_state->fildes			  = 99;
	shell_state->aliases		  = NULL;

	shell_state->aliases = malloc(sizeof(char *) * 1);
	if (shell_state->aliases == NULL) /* alloc fail */
	{
		shell_state->is_alive = 0; /*kill shell*/
		return;
	}
	shell_state->aliases[0] = NULL;
	if (argc == 2)
	{ /*file mode*/
		shell_state->fildes = open(argv[1], O_RDONLY);
		if (shell_state->fildes == -1) /* file read error */
		{
			print_shell_error(shell_state);
			print_error("Can't open ");
			print_error(argv[1]);
			print_error("\n");
			shell_state->is_alive	 = 0;	/*kill shell*/
			shell_state->exit_status = 127; /*not found exit status*/
		}
		else /* file read successful so flag file_mode */
			shell_state->in_file_mode = 1;
	}
}
