#ifndef SHELL_H
#define SHELL_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

extern char **environ;

char  *_strdup(const char *str);
void   prompt_user(void);
char  *get_input(void);
char **tokenize(char *input, char *delim);
void   execute_command(char **input_tokens);
void   free_array(char **str_arr);

#endif /*SHELL_H*/
