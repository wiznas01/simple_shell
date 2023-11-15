#include "shell.h"
/**
 * tokenize_commands - Tokenize input into separate commands using semicolon
 * @input: Input string containing multiple commands.
 * @commands: Array to store pointers to individual commands.
 * Return: The number of commands found.
 */
#define MAX_COMMAND 100

int tokenize_commands(char *input, char *commands[])
{
	int cmd_count = 0;
	char *end;

	while (*input != '\0' && cmd_count < MAX_COMMAND)
	{
		end = strchr(input, ';');
		if (end == NULL)
		{
			commands[cmd_count++] = input;
			break;
		}
		*end = '\0';
		commands[cmd_count++] = input;
		input = end + 1;

		while (*input == ' ' || *input == '\t')
			input++;
	}
	return (cmd_count);
}
