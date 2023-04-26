#include "shell.h"

/**
 * construct_full_path - concatenates a path and a filename
 * @path: a pointer to a string representing the path
 * @file: a pointer to a string representing the filename
 *
 * Return: a pointer to a string representing the full path,
 * or NULL on failure
 */
char *construct_full_path(char *path, char *file)
{
	char *full_path;

	/* allocate memory for path, file, '/' and null byte */
	full_path = malloc(_strlen(path) + 1 + _strlen(file) + 1);
	_strncpy(full_path, path, _strlen(path) + 1);
	_strcat(full_path, "/");
	_strcat(full_path, file);

	return (full_path);
}

/**
 * get_path_to_command - gets the full path to a command
 * @command: a pointer to a string representing the command
 * @shell_state: current program-wide shell state variables
 *
 * Return: a pointer to a string representing the full path,
 * or NULL on failure
 */
char *get_path_to_command(char *command, shell_state_t *shell_state)
{
	char  *path_env_var = NULL, *full_path = NULL, *delim = ":";
	char **path_arr;
	int	   index;

	if (command[0] == '/') /*check if command is an absolute path */
	{
		full_path = _strdup(command);
		if (access(full_path, X_OK) == 0) /*file exists & executable*/
			return (full_path);
		free(full_path); /* free the allocated memory */
		return (NULL);	 /* file not found or isn't executable */
	}

	/* if command is not an absolute path */
	path_env_var = _strdup(_getenv("PATH", shell_state)); /*search env for PATH*/
	if (path_env_var == NULL) /* failed to find the PATH env variable */
		return (NULL);

	path_arr = tokenize(path_env_var, delim); /*tokenize PATH into arr*/

	free(path_env_var);

	for (index = 0; path_arr[index] != NULL; index++)
	{
		/* construct the full path ie. "path/command" */
		full_path = construct_full_path(path_arr[index], command);

		/* check if the full path exists & is executable */
		if (access(full_path, X_OK) == 0)
		{
			free_array(path_arr);
			return (full_path);
		}
		free(full_path); /* free the previously allocated memory */
	}
	/* file not found or isn't executable */
	free_array(path_arr);
	return (NULL);
}

/**
 * mount_image - Mounts and executes a replacement image
 * from a path onto the current child process using execve()
 *
 * @path: full path to image
 * @args: array of command & arguments
 * @shell_state: Struct of current shell state variables
 */
void mount_image(char *path, char **args, shell_state_t *shell_state)
{
	/* replace child process with new one from user's input */
	execve(path, args, shell_state->environ);

	/* execve returns if it failed to replace the child process */
	print_shell_error(shell_state);
	print_error(args[0]);
	print_error(": ");
	perror("");

	/* clean up resources */
	free_2d_array(shell_state->tokenized_commands);
	free(path);
	path = NULL;

	/* terminate child process with an error code */
	exit(EXIT_FAILURE);
}

/**
 * execute_command - Executes a command by creating a child process
 * and calling execve()
 *
 * @input_tokens: Token array (command & arguments) of the
 * original user input
 * @shell_state: Struct of current shell state variables
 */
void execute_command(char **input_tokens, shell_state_t *shell_state)
{
	pid_t child_pid;
	int	  status;
	char *path_to_command = NULL;

	if (input_tokens[0] == NULL) /* empty/null cmd after cmd sep ";" */
		return;

	/* get path to the command if it exists or is executable */
	path_to_command = get_path_to_command(input_tokens[0], shell_state);

	/* if NULL, command not found or not executable */
	if (path_to_command == NULL)
	{
		print_shell_error(shell_state);
		print_error(input_tokens[0]);
		print_error(": ");
		print_error("not found\n");
		return;
	}

	/* fork the parent process here */
	child_pid = fork();
	if (child_pid == -1) /* fork failed & child process creation failed */
	{
		perror("Fork Error");
		free(path_to_command);
		return;
	}
	if (child_pid == 0)
	{
		mount_image(path_to_command, input_tokens, shell_state);
	}
	/* the parent waits here till execution in the child */
	wait(&status); /* process is over & the status is stored */
	free(path_to_command);
	if (WIFEXITED(status)) /*save the child process exit status*/
		shell_state->child_exit_status = WEXITSTATUS(status);
}
