#include "shell.h"

/**
 * print_alias - prints the value of a given alias if it exists
 * @alias: the name of the alias to search for
 * @shell_state: a pointer to the current shell state
 */
void print_alias(char *alias, shell_state_t *shell_state)
{
	int	   i;
	char **aliases = shell_state->aliases;
	char   output[256]; /* maximum size of output string */

	if (aliases == NULL)
	{
		return; /* print nothing on NULL ptr */
	}

	for (i = 0; aliases[i] != NULL; i++)
	{
		if (_strncmp(alias, aliases[i], _strlen(alias)) == 0
			&& aliases[i][_strlen(alias)] == '=')
		{
			/* on match */

			_strncpy(output, alias, _strlen(alias) + 1);
			_strcat(output, "='");
			_strcat(output, aliases[i] + _strlen(alias) + 1);
			_strcat(output, "'\n");
			print_output(output);
			return;
		}
	}

	/* else print an error */
}

/**
 * print_aliases - prints all aliases currently defined in the
 * program-wide shell state aliases array.
 * @shell_state: A pointer to the current shell state.
 */
void print_aliases(shell_state_t *shell_state)
{
	int	   i;
	char   output[256]; /* maximum size of output string */
	char **aliases = shell_state->aliases;
	int	   equal_sign_index;

	if (shell_state->aliases == NULL) /* on NULL ptr */
		return;						  /* print nothing */

	for (i = 0; aliases[i] != NULL; i++)
	{
		equal_sign_index = get_alias_equal_sign_index(aliases[i]);
		_strncpy(output, aliases[i], equal_sign_index);
		/* replace non-printable character with null terminator */
		output[equal_sign_index] = '\0';
		_strcat(output, "='");
		_strcat(output, aliases[i] + equal_sign_index + 1);
		_strcat(output, "'\n");
		print_output(output);
	}
}

/**
 * execute_alias - creates, updates or prints aliases based on the
 * given alias command and its arguments
 * @cmd: array of strings containing the command and arguments
 * @shell_state: pointer to the current state of the shell
 *
 * This function creates or prints aliases based on the given command and
 * arguments. If the command is only "alias", all the currently defined
 * aliases are printed to standard output. If the arguments contain one or
 * more aliases (in the format "alias=value"), the aliases are created or
 * updated in the shell's state. If the arguments contain only alias names
 * (without values), the values of the aliases are printed to standard output.
 */
void execute_alias(char **cmd, shell_state_t *shell_state)
{
	int i;

	if (cmd[1] == NULL) /* only the cmd alias is given */
	{
		print_aliases(shell_state);
		return;
	}
	/* some aliases (and their values) may be present */
	for (i = 1; cmd[i] != NULL; i++)
	{ /*if in format: alias=value*/
		if (get_alias_equal_sign_index(cmd[i]) != -1 && cmd[i][0] != 0)
		{
			set_alias(cmd[i], shell_state);
		}
		else /* if just alias name: alias */
		{
			print_alias(cmd[i], shell_state);
		}
	}
}
