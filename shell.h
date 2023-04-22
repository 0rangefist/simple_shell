#ifndef SHELL_H
#define SHELL_H

#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/*#define BUFFER_SIZE 256*/

extern char **environ;

/* Type Definitions*/

/**
 * struct shell_state - Holds state & info variables
 * of the shell program
 *
 * @prog_name: the name of the shell executable obtained from argv[0]
 * @input_line_count: number of input lines read by the shell so far
 * @is_alive: boolean to determine if the program should keep running
 * @tokenized_commands: 2d arr of commands tokenized by whitespace
 * @startup_errno: backup copy of errno at start of the shell program
 * @exit_status: 0 or positive number exit status of the shell program
 */

struct shell_state
{
	char   *prog_name;
	int		input_line_count;
	int		is_alive;
	char ***tokenized_commands;
	int		startup_errno;
	int		exit_status;
};

/**
 * shell_state_t - typedef for struct shell_state
 */
typedef struct shell_state shell_state_t;

/**
 * struct builtin - Struct for a builtin function
 *
 * @name: The name of the builtin function
 * @func: The function associated with the builtin
 */
struct builtin
{
	char *name;
	void (*func)(char **cmd, shell_state_t *s);
};

/**
 * builtin_t - typedef for struct builtin
 */
typedef struct builtin builtin_t;

/* main program functions */
void	initialize_shell(shell_state_t *s, char *argv[]);
void	prompt_user(void);
char   *get_input(shell_state_t *s);
int		has_bad_syntax(char *input, shell_state_t *s);
char  **tokenize_input(char *input);
char ***tokenize_commands(char **commands);
void	execute_commands(char ***tok_cmds, shell_state_t *s);

/* external shell command*/
void execute_command(char **tok_cmd, shell_state_t *s);

/* builtin shell commands */
void (*get_builtin_function(char **cmd))(char **, shell_state_t *);
void execute_exit(char **cmd, shell_state_t *s);
void execute_env(char **cmd, shell_state_t *s);
void execute_setenv(char **cmd, shell_state_t *s);
void execute_unsetenv(char **cmd, shell_state_t *s);
void execute_cd(char **cmd, shell_state_t *s);
void execute_alias(char **cmd, shell_state_t *s);

/* string manipulation functions */
char *_strdup(const char *str);
int	  _strcmp(const char *s1, const char *s2);

/* auxilliary functions */
char **tokenize(char *str, char *delim);
void   free_array(char **str_arr);
void   free_2d_array(char ***arr);

#endif /*SHELL_H*/
