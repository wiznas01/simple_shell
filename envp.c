#include "shell.h"

/**
 * execute_cmd - Execute a given command with arguments
 * @command: String representing the command to execute
 * @envp: Pointer to an array of strings containing environment variables
 * Return: This function does not return a value.
 */

void execute_cmd(char *command, char **envp)
{
	char *args[MAX_ARGUMENTS];
	int arg_count = 0;

	command[strcspn(command, "\n")] = '\0';
	args[arg_count] = strtok(command, " ");

	while (args[arg_count] != NULL && arg_count < MAX_ARGUMENTS  - 1)
	{
		arg_count++;
		args[arg_count] = strtok(NULL, " ");
	}
	args[arg_count] = NULL;

	if (access(args[0], F_OK) == 0)
	{
		pid_t pid = fork();

		if (pid < 0)
		{
			perror("Fork failed");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (execve(args[0], args, envp) == -1)
			{
				perror("Error executing command");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(NULL);
		}
	}
	else
	{
		fprintf(stderr, "%s: command not found\n", args[0]);
	}
}
