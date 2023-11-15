#include "shell.h"
/**
 * execute_path_command - execute a given command with arguments
 * @command: string representing the command to execute
 * Return: this function does not return a value
 */
int execute_path_command(char *command, char **envp)
{
	char *args[MAX_ARGUMENTS];
	int arg_count = 0;

	command[strcspn(command, "\n")] = '\0';
	args[arg_count] = strtok(command, " ");

	while (args[arg_count] != NULL && arg_count < MAX_ARGUMENTS - 1)
	{
		arg_count++;
		args[arg_count] = strtok(NULL, " ");
	}
	args[arg_count] = NULL;

	path_execute(args[0], args);
	return (0);
}

/**
 * path_execute - execute a command searching through paths
 * @command: command to execute
 * @args: array of arguments
 * Return: this function does not return a value
 */
void path_execute(char *command, char **args)
{
	char *path = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
	char *path_args[MAX_ARGUMENTS];
	char cmd[MAX_PATH_LENGTH];
	char *token;
	char *path_copy;
	int i;
	int arg_count = 0;
	char *next;

	path_copy = strdup(path);
	if (path_copy == NULL)
	{
		perror("Memory allocation failed");
		return;
	}

	token = path_copy;
	while (*token != '\0' && arg_count < MAX_ARGUMENTS - 1)
	{
		if (next == NULL)
		{
			next = strchr(token, ':');

			path_args[arg_count++] = token;
			break;
		}
		*next = '\0';
		path_args[arg_count++] = token;
		token = next + 1;
	}
	path_args[arg_count] = NULL;
	free(path_copy);

	if (access(command, F_OK | X_OK) == 0 && execve(command, args, NULL) != -1)
		return;
	for (i = 0; path_args[i] != NULL; i++)
	{
		snprintf(cmd, sizeof(cmd), "%s/%s", path_args[i], command);
		if (access(cmd, X_OK) == 0 && execve(cmd, args, NULL) != -1)
			return;
	}
	fprintf(stderr, "%s: command not found\n", command);
	return;
}
