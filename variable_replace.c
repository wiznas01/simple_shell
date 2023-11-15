#include "shell.h"

/**
 * main - Entry point for the variable replacement example.
 * Return: Always returns 0 on successful execution.
 */
int main(void)
{
	char command[COMMAND_SIZE];
	char *result;

	own_getline(command, COMMAND_SIZE);

	result = replace_variables(command, 0);

	printf("Original command: %s\n", command);
	printf("Modified command: %s\n", result);
	free(result);
	return (0);
}

/**
 * replace_variables - Replaces special variables in the command string.
 * @command: The input command string.
 * @last_status: The exit status of the last command.
 * Return: A dynamically allocated string with replaced variables
 */
char *replace_variables(char *command, int last_status)
{
	char *result = malloc(strlen(command) + 1);
	char *src = command;
	char *dest = result;

	if (result == NULL)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	while (*src != '\0')
	{
		if (*src == '$')
		{
			src++;
			if (*src == '?')
			{
				dest += sprintf(dest, "%d", last_status);
			}
			else if (*src == '$')
				dest += sprintf(dest, "%d", getpid());
			else
			{
				*dest++ = '$';
				*dest++ = *src;
			}
		}
		else
		{
			*dest++ = *src;
		}
		src++;
	}
	*dest = '\0';
	return (result);
}
