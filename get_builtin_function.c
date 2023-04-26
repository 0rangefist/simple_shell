#include "shell.h"

/**
 * get_builtin_function - Returns the function associated with a built-in
 * command
 *
 * @cmd: Command to retrieve function for
 *
 * Return: Pointer to the function if command is a built-in command, NULL
 * otherwise
 */
void (*get_builtin_function(char **cmd))(char **, shell_state_t *)
{
	builtin_t builtins[]
		= {{"exit", execute_exit},	   {"env", execute_env},
		   {"setenv", execute_setenv}, {"unsetenv", execute_unsetenv},
		   {"cd", execute_cd},		   {NULL, NULL}};

	/* {"alias", execute_alias}, */

	int i;

	/* check for the builtin name, cmd[0] in builtins[]*/
	for (i = 0; builtins[i].name != NULL; i++)
	{
		/*compare command to names of builtin commands*/
		if (_strcmp(cmd[0], builtins[i].name) == 0)
		{
			/* return the function whose name matches */
			return (builtins[i].func);
		}
	}

	/* return NULL if no match was made */
	return (NULL);
}
