#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_ARGUMENTS 10
#define MAX_INPUT_SIZE 1024
#define MAX_ALIAS_COUNT 50
#define COMMAND_SIZE 256
#define MAX_PATH_LENGTH 256

int get_max_argument(void);
int execute_command(char *command, char *envp[]);
void execute_cmd(char *command, char **envp);
void path_execute(char *command, char **args, char **envp);
void exit_shell(void);
void env_shell(char **envp);
char *own_getline(char *buffer, size_t size);
int execute_setenv(char *var, char *value);
int execute_unsetenv(char *var);
void split_command(char *command, char *args[]);
int execute_cd(char *dir, char **envp);
int tokenize_commands(char *input, char *commands[]);
int execute_logical(char *command, char **envp);
int execute_and_or(char **commands, int count, char **envp);
int execute_path_command(char *command, char **envp);
int execute_alias(char *alias_command, char *aliases[], int *alias_count);
void print_aliases(char *aliases[], int alias_count);
char *replace_variables(char *command, int last_status);

#endif
