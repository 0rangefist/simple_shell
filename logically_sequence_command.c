#include "shell.h"

/**
 * print_logic_error - Prints a syntax error message for unexpected
 * logical operator in the command.
 * @str: A string containing the unexpected logical operator.
 * @shell_state: A pointer to the current state of the shell.
 */
void print_logic_error(char *str, shell_state_t *shell_state)
{
	print_shell_error(shell_state);
	print_error("Syntax error: ");
	print_error("\"");
	print_error(str);
	print_error("\" unexpected\n");
}

/**
 * get_logic_op_index - Finds the index of the logical operator in the command.
 * @command: An array of strings containing the command and its arguments.
 *
 * Return: The index of the logical operator if found, otherwise -1.
 */
int get_logic_op_index(char **command)
{
	int i;
	/* Check for logical operators */
	for (i = 0; command[i] != NULL; i++)
	{
		if (_strcmp(command[i], "&&") == 0 || _strcmp(command[i], "||") == 0)
		{
			return (i); /*found*/
		}
	}
	return (-1); /*not found*/
}

/**
 * split_command - Splits a command array into two parts at the given logical
 * operator index.
 * @command: An array of strings containing the command and its arguments.
 * @logic_op_index: The index of the logical operator in the command.
 * @left_command: A pointer to a pointer that will be set to the left part of
 * the command.
 * @right_command: A pointer to a pointer that will be set to the right part of
 * the command.
 */
void split_command(char **command, int logic_op_index, char ***left_command,
				   char ***right_command)
{
	int i, j;

	/* Allocate memory for left_command */
	*left_command = malloc(sizeof(char *) * (logic_op_index + 1));
	for (i = 0; i < logic_op_index; i++)
	{
		/*copy content from orig command till logic_op_index*/
		(*left_command)[i] = command[i];
	}
	(*left_command)[logic_op_index] = NULL;

	/* Allocate memory for right_command */
	*right_command = malloc(
		sizeof(char *) * ((get_array_size(command) - logic_op_index - 1) + 1));
	j = 0;
	for (i = logic_op_index + 1; command[i] != NULL; i++)
	{
		/*copy content from logic_op_index+1 till end of orig command*/
		(*right_command)[j] = command[i];
		j++;
	}
	(*right_command)[j] = NULL;
}

/**
 * has_logic_err - Checks if the command has any syntax errors related to
 * logical operators.
 * @command: An array of strings containing the command and its arguments.
 * @shell_state: A pointer to the current state of the shell.
 *
 * Return: 1 if the command has a syntax error related to logical operators,
 * otherwise 0.
 */
int has_logic_err(char **command, shell_state_t *shell_state)
{
	int last_index = get_array_size(command) - 1;
	/*if first element is || or &&, bad syntax*/
	if (_strcmp(command[0], "||") == 0 || _strcmp(command[0], "&&") == 0)
	{
		print_logic_error(command[0], shell_state);
		return (1);
	}

	/*if last element is || or &&, bad syntax*/
	if (_strcmp(command[last_index], "||") == 0
		|| _strcmp(command[last_index], "&&") == 0)
	{
		print_logic_error(command[last_index], shell_state);
		return (1);
	}

	return (0); /*good syntax*/
}
/**
 * logically_sequence_command - Sequences a command which may
 * have && or || branches within it so it correctly executes
 * successive sub-commands based on the logical operator
 *
 * @command: Command arr which may include logical subsequences
 * @shell_state: Struct of current shell state variables
 */
void logically_sequence_command(char **command, shell_state_t *shell_state)
{
	int	   logic_op_index, is_OR; /*is a || logical operator*/
	char **left_command;		  /* true command to left of logic op*/
	char **right_command; /* possibly nested command to right of logic op*/

	if (has_logic_err(command, shell_state)) /*print err if bad syntax*/
		return;
	/* Get index of a logic op in command if it exists */
	logic_op_index = get_logic_op_index(command);
	if (logic_op_index == -1)
	{ /* if no logical operator found, execute command as is */
		handle_command(command, shell_state);
		return;
	}
	/* if logic operator exists - split command into two parts */
	split_command(command, logic_op_index, &left_command, &right_command);
	handle_command(left_command, shell_state); /* execute the left command */
	/* Check logical op to determine if to execute right command */
	is_OR = (_strcmp(command[logic_op_index], "||") == 0) ? 1 : 0;
	if (is_OR)
	{ /* if left command succeeded, dont execute right command */
		if (shell_state->child_exit_status == 0) /*last command succeeded*/
		{
			free(left_command);
			free(right_command);
			return;
		}
	}
	else /*if it is &&*/
	{	 /* if left command failed, dont execute right command */
		if (shell_state->child_exit_status != 0) /*last command failed */
		{
			free(left_command);
			free(right_command);
			return;
		}
	} /* otherwise we are good to recursively sequence right command*/
	logically_sequence_command(right_command, shell_state);
	/* free allocated memory */
	free(left_command);
	free(right_command);
}
