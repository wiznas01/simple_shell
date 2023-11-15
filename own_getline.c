#include "shell.h"
/**
 * own_getline - Custom getline function to read input from user.
 * @buffer: Pointer to the buffer where the line will be stored.
 * @size: Size of the buffer.
 * @stream: file.
 * Return: A pointer to the string read, returns NULL on fail.
 */

char *own_getline(char *buffer, size_t size)
{
	size_t i = 0;
	int c;

	while ((c = getchar()) != EOF)
	{
		if (c == '\n')
		{
			buffer[i] = '\0';
			break;
		}
		else if (c == '#')
		{
			while ((c = getchar()) != EOF && c != '\n')
			continue;
		}
		else
		{
			if (i < size - 1)
				buffer[i++] = c;
			else
				break;
		}
	}
	if (c == EOF && i == 0)
	{
		return (NULL);
	}
	return (buffer);
}

/**
 * main - Entry point for the custom shell program
 * Return: Always returns 0 on successful execution
 */
int main(void)
{
	char command[MAX_INPUT_SIZE];
	int exit_status;

	while (1)
	{
		own_getline(command, COMMAND_SIZE, stdin);
		if (strcmp(command, "exit\n") == 0 || strcmp(command, "quit\n") == 0)
		{
			printf("Exiting shell...\n");
			break;
		}
		exit_status = execute_command(command, envp);
		if (exit_status != 0)
			printf("Command exited with status %d\n", exit_status);
	}
	return (0);
}
