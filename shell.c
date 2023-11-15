#include "shell.h"
/**
 * get_max_argument - Determines the maximum number of arguments.
 * Return: Maximum number of arguments.
 */

int get_max_argument(void)
{
	return (10);
}

/**
 * split_command - function to split commands
 * @command: command to be split
 * @args: argument
 * Return: returns void
 */
void split_command(char *command, char *args[])
{
	int arg_count = 0;

	while (*command != '\0' && arg_count < MAX_ARGUMENTS - 1)
	{
		while (*command == ' ' || *command == '\t' || *command == '\n')
		{
			*command++ = '\0';
		}
		args[arg_count++] = command;
		while (*command != '\0' && *command != ' ' &&
			*command != '\t' && *command != '\n')
			command++;
	}
	args[arg_count] = NULL;
}

/**
 * execute_command - Execute a command with arguments.
 * @command: Input command to execute.
 * Return: 0 on success, -1 on failure.
 */
int execute_command(char *command, char *envp[])
{
	char *args[MAX_ARGUMENTS];

	split_command(command, args);
	if (args[0] != NULL)
	{
		if (access(args[0], X_OK) == 0)
		{
			if (execve(args[0], args, envp) == -1)
				perror("Error executing command");
		}
		else
		{
			fprintf(stderr, "%s: command not found\n", args[0]);
		}
	}
	return (0);
}

/**
 * main - Entry point for the custom shell program.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line argument strings.
 *
 * Return: 0
 */

int main(int argc, char *argv[], char *envp[])
{
	char command[COMMAND_SIZE];
	char *modified_command;
	FILE *file;

	if (argc == 2)
	{
		file = fopen(argv[1], "r");
		if (file == NULL)
		{
			perror("Error opening file");
			exit(EXIT_FAILURE);
		}
	}
	while (1)
	{
		printf("($) ");

		if (own_getline(command, sizeof(command)) == NULL)
		{
			if (argc == 2)
				break;
			else
				continue;
		}
		command[strcspn(command, "\n")] = '\0';

		modified_command = replace_variables(command, 0);
		execute_command(modified_command, envp);
		free(modified_command);
	}
	if (argc == 2)
		fclose(file);

	return (0);
}
