#include "shell.h"
/**
 * update_pwd - Update PWD environment variable
 * @shell_state: Struct of current shell state variables
 * @should_print: boolean to determine if to also print pwd to stdout
 */
void update_pwd(shell_state_t *shell_state, int should_print)
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
		if (should_print)
		{
			print_output(cwd);
			print_output("\n");
		}
	}
}

/**
 * execute_cd - Builtin command that changes the directory
 * @cmd: array of command and arguments
 * @shell_state: Struct of current shell state variables
 */
void execute_cd(char **cmd, shell_state_t *shell_state)
{
	char pwd[1024];
	int	 PRINT = 1, DONT_PRINT = 0;

	if (cmd[1] == NULL) /* No argument, change to home dir */
	{					/* save current directory as prev_dir */
		getcwd(pwd, 1024);
		add_env("OLDPWD", pwd, shell_state);
		/* change the directory*/
		if (get_env_index("HOME", shell_state) != -1) /*if HOME in environ*/
			chdir(_getenv("HOME", shell_state));
		/*update PWD*/
		update_pwd(shell_state, DONT_PRINT);
	}
	else if (_strcmp(cmd[1], "-") == 0)
	{
		/* save current dir backup */
		getcwd(pwd, 1024);
		/* change the directory*/
		if (get_env_index("OLDPWD", shell_state) != -1) /*if OLDPWD in environ*/
			chdir(_getenv("OLDPWD", shell_state));
		/*now change OLDPWD to the previous dir befor the change*/
		add_env("OLDPWD", pwd, shell_state);
		/*update PWD*/
		update_pwd(shell_state, PRINT);
	}
	else /* Change to specified directory */
	{	 /* save current dir backup */
		getcwd(pwd, 1024);
		if (chdir(cmd[1]) == -1) /* change the directory*/
		{
			print_shell_error(shell_state);
			print_error("cd: can't cd to ");
			print_error(cmd[1]);
			print_error("\n");
		}
		/*now change OLDPWD to the previous dir befor the change*/
		add_env("OLDPWD", pwd, shell_state);
		/*update PWD env*/
		update_pwd(shell_state, DONT_PRINT);
	}
}
