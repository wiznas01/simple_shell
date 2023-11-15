#include "shell.h"

int execute_and_or(char **commands, int count, char **envp);

/**
 * execute_logical - Execute commands separated by logical operators && or ||
 * @command: Input string containing commands and logical operators
 * @envp: environmental variables
 * Return: Result of the logical operations, 0 on success, -1 on failure
 */

int execute_logical(char *command, char **envp)
{
	char *commands[MAX_ARGUMENTS];
	int count = 0;
	char *token;
	int last_index;
	size_t len;

	token = strtok(command, "&|");
	while (token != NULL)
	{
		commands[count++] = token;
		token = strtok(NULL, "&|");
	}
	commands[count] = NULL;


	last_index = count - 1;
	len = strlen(commands[last_index]);

	if (len >= 2 && (strcmp(commands[last_index] + len - 2, "&&") == 0 ||
			strcmp(commands[last_index] + len - 2, "||") == 0))
	{
		fprintf(stderr, "Missing command after logical operator\n");
		return (-1);
	}
	return (execute_and_or(commands, count, envp));
}

/**
 * execute_and_or - Execute commands based on logical operators && or ||
 * @commands: Array of commands to execute
 * @count: Number of commands in the array
 * @envp: enviromental variables
 * Return: Result of the logical operations, 0 on success, -1 on failure
 */
int execute_and_or(char **commands, int count, char **envp)
{
	int i;
	int result = 0;
	int status;

	for (i = 0; i < count; ++i)
	{
		status = execute_command(commands[i], envp);

		if (status == 0 && !strcmp(commands[i] + strlen(commands[i]) - 2, "||"))
		{
			i++;
		}
		else if (status != 0 && !strcmp(commands[i] + strlen(commands[i]) - 2, "&&"))
		{
			i++;
			result = status;
		}
		else
			result = status;
	}
	return (result);
}
