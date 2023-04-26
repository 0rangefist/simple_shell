#include "shell.h"
/**
 * update_pwd - Update PWD environment variable
 * @shell_state: Struct of current shell state variables
 */
void update_pwd(shell_state_t *shell_state)
{
	/* Get the current working directory */
	char cwd[1024];

	if (getcwd(cwd, 1024) == NULL)
	{
		print_shell_error(shell_state);
		perror("getcwd");
	}
	else
	{
		/* Update PWD */
		add_env("PWD", cwd, shell_state);
	}
}

/**
 * execute_cd - Builtin command that changes the directory
 * @cmd: array of command and arguments
 * @shell_state: Struct of current shell state variables
 */
void execute_cd(char **cmd, shell_state_t *shell_state)
{
	char cwd[1024];

	if (cmd[1] == NULL) /* No argument, change to home dir */
	{					/* save current directory as prev_dir */
		getcwd(shell_state->prev_dir, 1024);
		if (chdir(_getenv("HOME", shell_state)) == -1)
		{
			print_shell_error(shell_state);
			print_error("cd: home not found\n");
		}
		else /*update PWD env*/
			update_pwd(shell_state);
	}
	else if (_strcmp(cmd[1], "-") == 0)
	{ /* Change to previous directory */
		if (_strlen(shell_state->prev_dir) == 0) /* prev_dir empty */
			return;								/* can't change to it */
		getcwd(cwd, 1024); /* save current directory */
		if (chdir(shell_state->prev_dir) == -1)
		{
			print_shell_error(shell_state);
			perror("cd");
		}
		else
		{ /* set prev_dir to current directory */
			_strncpy(shell_state->prev_dir, cwd, _strlen(cwd));
			update_pwd(shell_state);
		}
	}
	else /* Change to specified directory */
	{	 /* save current directory as prev_dir */
		getcwd(shell_state->prev_dir, 1024);
		if (chdir(cmd[1]) == -1)
		{
			print_shell_error(shell_state);
			perror("cd");
		}
		else /*update PWD env*/
			update_pwd(shell_state);
	}
}
