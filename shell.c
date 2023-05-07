#include "shell.h"

/**
 * main - The entry point of the program
 *
 * @argc: The number of command line arguments passed to the program
 * @argv: An array of strings containing the command line arguments
 * passed to the program
 *
 * Return: 0 on success, or an error code on failure
 */
int main(int argc, char *argv[])
{
	char   *input;	  /*unmodified input string entered by user */
	char  **commands; /*array of commands created using ; as delimiter*/
	shell_state_t shell_state = {0}; /*program-wide shell state variables*/

	initialize_shell(&shell_state, argc, argv);
	while (shell_state.is_alive)
	{
		/* prompt user to enter commands */
		prompt_user(&shell_state);

		/* get the user input & save num of chars read */
		input = get_input(&shell_state);
		if (input == NULL) /* if empty input or error */
			continue;	   /*restart loop*/

		ignore_comment(input); /* ignore comment (#...) in input */
		if (has_bad_syntax(input, &shell_state)) /* if input has bad syntax */
		{
			free(input);
			continue; /* restart loop */
		}

		/* tokenize input into array of commands delimited by ";" */
		commands = split_into_commands(input);

		/* execute each command in the array sequentially */
		execute_commands(commands, &shell_state);

		free_array(commands);
		errno = shell_state.startup_errno; /*reset errno*/
	}
	free_array(shell_state.environ);
	free_array(shell_state.aliases);
	if (shell_state.in_file_mode) /*close file*/
		close(shell_state.fildes);
	return (shell_state.exit_status);
}
