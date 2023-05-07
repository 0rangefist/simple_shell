#ifndef SHELL_H
#define SHELL_H

#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define LINE_FACTOR 2

extern char **environ;

/* Type Definitions*/

/**
 * struct shell_state - Holds state & info variables
 * of the shell program
 *
 * @prog_name: the name of the shell executable obtained from argv[0]
 * @input_line_count: number of input lines read by the shell so far
 * @is_alive: boolean to determine if the program should keep running
 * @commands: backup of array of command strings
 * @startup_errno: backup copy of errno at start of the shell program
 * @exit_status: 0 or positive number exit status of the shell program
 * @is_interactive: boolean to determine if shell is interactive terminal
 * @environ: the program-wide environment
 * @in_file_mode: boolean to know if input is from file instead of stdin
 * @fildes: file descriptor for reading from a file when in file mode
 * @aliases: program-wide array of alias strings with format: alias=path
 */

struct shell_state
{
	char   *prog_name;
	int		input_line_count;
	int		is_alive;
	char **commands;
	int		startup_errno;
	int		exit_status;
	int		is_interactive;
	char  **environ;
	int		in_file_mode;
	int		fildes;
	char  **aliases;
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
void	initialize_shell(shell_state_t *s, int argc, char *argv[]);
void	prompt_user(shell_state_t *s);
int		get_line(char **line, int fd);
char   *get_input(shell_state_t *s);
void	ignore_comment(char *input);
int		has_bad_syntax(char *input, shell_state_t *s);
char  **split_into_commands(char *input);
char ***tokenize_commands(char **commands);
void	replace_variables(char **cmd_toks, shell_state_t *s);
void	execute_commands(char **cmd_toks, shell_state_t *s);
void	logically_sequence_command(char *cmd, shell_state_t *s);
void	handle_command(char *cmd, shell_state_t *s);

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

/* alias builtin command functions */
int	  get_alias_equal_sign_index(char *str);
char *get_alias_value(char *alias, shell_state_t *s);
void  set_alias(char *alias_and_value, shell_state_t *s);

/* string manipulation functions */
char *_strdup(const char *str);
int	  _strlen(char *str);
char *_strncpy(char *dest, char *src, int n);
char *_strcat(char *dest, char *src);
int	  _strncmp(const char *str1, const char *str2, size_t n);
int	  _strcmp(const char *s1, const char *s2);

/* print functions */
void print_output(char *str);
void print_error(char *str);
void print_shell_error(shell_state_t *shell_state);

/* auxilliary functions */
char **tokenize(char *str, char *delim);
void   free_array(char **str_arr);
void   free_2d_array(char ***arr);
char  *int_to_string(int num);
int	   get_array_size(char **array);
int	   is_whitespace_string(char *str);
void   strip_lead_trail_whitespace(char *str);
void   strip_all_whitespace(char *str);
int	   strip_repeated_whitespace(char *buffer, int buff_len);

/* environment functions */
char  *_getenv(char *env_name, shell_state_t *s);
int	   get_env_index(char *env_name, shell_state_t *s);
void   delete_env_at_index(int index, shell_state_t *s);
int	   add_env(char *name, char *value, shell_state_t *s);
int	   environ_size(shell_state_t *s);
char **copy_environment(char **environ);
int	   add_env(char *name, char *value, shell_state_t *s);

#endif /*SHELL_H*/
