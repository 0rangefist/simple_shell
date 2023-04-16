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
	full_path = malloc(strlen(path) + 1 + strlen(file) + 1);
	strcpy(full_path, path);
	strcat(full_path, "/");
	strcat(full_path, file);

	return (full_path);
}

/**
 * get_path_to_command - gets the full path to a command
 * @command: a pointer to a string representing the command
 *
 * Return: a pointer to a string representing the full path,
 * or NULL on failure
 */
char *get_path_to_command(char *command)
{
	char  *path_env_var = NULL, *full_path = NULL, *delim = ":";
	char **envp = environ, **path_arr;
	int	   index, errno_backup = errno;

	if (command[0] == '/') /*check if command is an absolute path */
	{
		full_path = _strdup(command);
		if (access(full_path, X_OK) == 0) /*file exists & executable*/
			return (full_path);
		return (NULL); /* file not found or isn't executable */
	}

	while (*envp != NULL) /* if command is not an absolute path */
	{
		if (strncmp(*envp, "PATH=", 5) == 0) /* search envp for PATH= */
		{
			path_env_var = *envp + 5; /*save PATH var minus (PATH=)*/
			break;
		}
		envp++;
	}
	if (path_env_var == NULL) /* failed to find the PATH env variable */
		return (NULL);
	path_arr = tokenize(path_env_var, delim); /*tokenize PATH into arr*/
	for (index = 0; path_arr[index] != NULL; index++)
	{
		/* construct the full path ie. "path/command" */
		full_path = construct_full_path(path_arr[index], command);
		if (access(full_path, X_OK) == 0)
		{ /* check if the full path exists & is executable */
			free_array(path_arr);
			errno = errno_backup; /* restore original errno */
			return (full_path);
		}
		free(full_path); /* free the previously allocated memory */
	}
	/* file not found or isn't executable */
	free_array(path_arr);
	errno = errno_backup; /* restore original errno */
	return (NULL);
}

/**
 * execute_command - Executes a command by creating a child process
 * and calling execve()
 *
 * @input_tokens: Token array (command & arguments) of the
 * original user input
 */
void execute_command(char **input_tokens)
{
	pid_t child_pid;
	int	  status;
	char *path_to_command = NULL;

	/* get path to the command if it exists or is executable */
	path_to_command = get_path_to_command(input_tokens[0]);

	/* if NULL, command not found or not executable */
	if (path_to_command == NULL)
	{
		printf("%s: command not found\n", input_tokens[0]);
		return;
	}

	/* fork the parent process here */
	child_pid = fork();
	if (child_pid == -1) /* fork failed & child process creation failed */
	{
		perror("Fork Error");
		return;
	}
	if (child_pid == 0)
	{
		/* replace child process with new one from user's input */
		execve(path_to_command, input_tokens, NULL);

		/* execve returns if it failed to replace the child process */
		perror("Child Process Exec Error");

		/* clean up resources */
		free_array(input_tokens);
		free(path_to_command);
		path_to_command = NULL;

		/* terminate child process with an error code */
		exit(EXIT_FAILURE);
	}
	/* the parent waits here till execution in the child */
	wait(&status); /* process is over & the status is stored */
	free(path_to_command);
}

