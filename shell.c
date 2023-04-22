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
	char ***tokenized_commands; /*2d arr of commands tokenized by whitespace*/
	shell_state_t shell_state = {0}; /*program-wide shell state variables*/

	(void) argc;
	initialize_shell(&shell_state, argv);
	while (shell_state.is_alive)
	{
		/* prompt user to enter commands */
		prompt_user();

		/* get the user input & save num of chars read */
		input = get_input(&shell_state);

		if (input == NULL) /* if empty input or error */
			continue;	   /*restart loop*/

		/* check if input has bad syntax */
		if (has_bad_syntax(input, &shell_state))
		{
			free(input); /* free input memory */
			continue;	 /* restart loop */
		}

		/* tokenize input into array of commands delimited by ";" */
		commands = tokenize_input(input);

		/* further tokenize the commands, delimited by whitespaces */
		tokenized_commands			   = tokenize_commands(commands);
		shell_state.tokenized_commands = tokenized_commands;

		/* execute each tokenized_command in the array sequentially */
		execute_commands(tokenized_commands, &shell_state);

		free_2d_array(tokenized_commands);

		errno = shell_state.startup_errno; /*reset errno*/
	}
	return (shell_state.exit_status);
}
