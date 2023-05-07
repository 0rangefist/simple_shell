#include "shell.h"
/**
 * get_alias_index - finds the index of an alias in the (program-wide)
 * shell state aliases array
 * @alias: the alias to search for in the aliases array
 * @shell_state: pointer to the shell state struct
 *
 * Return: the index of the alias in the aliases array, or -1 if the
 * alias is not found
 */
int get_alias_index(char *alias, shell_state_t *shell_state)
{
	int comp_result;
	int i = 0;

	if (shell_state->aliases == NULL) /* alias not found */
		return (-1);

	if (alias == NULL)
	{
		while (shell_state->aliases[i] != NULL) /* find NULL index */
			i++;

		return (i);
	}

	for (i = 0; shell_state->aliases[i] != NULL; i++)
	{
		comp_result = _strncmp(alias, shell_state->aliases[i], _strlen(alias));
		if (comp_result == 0 && shell_state->aliases[i][_strlen(alias)] == '=')
		{
			/* variable found */
			return (i); /*return the index*/
		}
	}
	/* variable not found */
	return (-1);
}

/**
 * get_alias_value - recursively retrieves the value of an alias,
 * accounting for nested aliases
 * @alias: the alias to retrieve the value of
 * @shell_state: pointer to the shell state struct
 *
 * Return: a pointer to the value of the alias, or NULL if the alias
 * is not found
 */
char *get_alias_value(char *alias, shell_state_t *shell_state)
{
	int	   i;
	size_t len;
	char **aliases = shell_state->aliases;
	char  *value   = NULL;
	char  *next_value;

	for (i = 0; aliases[i] != NULL; i++)
	{
		len = _strlen(alias);
		if (_strncmp(alias, aliases[i], len) == 0
			&& aliases[i][_strlen(alias)] == '=')
		{
			value = aliases[i] + len + 1;
			/* recursively check if the current alias value */
			/* is an alias itself & return its value */
			next_value = get_alias_value(value, shell_state);
			if (next_value != NULL) /* if value is found to be an alias */
				value = next_value; /* make it's return the value */
			break;
		}
	}
	return (value);
}

/**
 * get_alias_equal_sign_index - finds the index of the '=' character in
 * an alias string
 * @str: the alias string to search for the '=' character in
 *
 * Return: the index of the '=' character in the string, or -1 if the
 * '=' character is not found
 */
int get_alias_equal_sign_index(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '=') /* check if char is = */
			return (i);
	}
	return (-1); /* = not found, so not in alias=value format */
}

/**
 * set_alias - adds or updates an alias in the (program-wide)
 * shell state aliases array
 * @alias_and_value: the string containing the alias and its value in
 * the format 'alias=value'
 * @shell_state: pointer to the shell state struct
 */
void set_alias(char *alias_and_value, shell_state_t *shell_state)
{
	int	   i, num_of_aliases;
	char **aliases = shell_state->aliases; /* old aliases array  */
	char **new_aliases;					   /* updated aliases array*/
	int	   equal_sign_index = get_alias_equal_sign_index(alias_and_value);

	for (i = 0; aliases[i] != NULL; i++) /* if alias already exists */
	{ /* search through the program-wide aliases array for a match */
		if (_strncmp(aliases[i], alias_and_value, equal_sign_index) == 0)
		{														/*on match*/
			free(shell_state->aliases[i]);						/*free old one*/
			shell_state->aliases[i] = _strdup(alias_and_value); /*overwrite*/
			return;
		}
	}
	/* get the number of aliases in aliases array */
	num_of_aliases = get_alias_index(NULL, shell_state); /* index of NULL */
	/* allocate memory for new aliases array with room */
	/* for 1 more element & null byte */
	new_aliases = malloc((num_of_aliases + 2) * sizeof(char *));
	if (new_aliases == NULL) /*alloc fail*/
		return;
	/* copy old aliases into new array */
	for (i = 0; i < num_of_aliases; i++)
		new_aliases[i] = shell_state->aliases[i];
	/* append the new alias_and_value */
	new_aliases[num_of_aliases]		= _strdup(alias_and_value);
	new_aliases[num_of_aliases + 1] = NULL;
	/* free the memory of the old aliases array */
	free(shell_state->aliases);
	/* overwrite the old aliases array with the new updated one*/
	shell_state->aliases = new_aliases;
	/*alias  successfully added*/
	shell_state->exit_status = 0;
}
