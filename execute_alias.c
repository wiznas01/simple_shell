#include "shell.h"

/**
 * execute_alias - Implements the alias builtin command
 * @alias_command: Alias command to execute
 * @aliases: Array to store aliases
 * @alias_count: Pointer to the count of aliases
 * Return: 0 on success, -1 on failure
 */
int execute_alias(char *alias_command, char *aliases[], int *alias_count)
{
	char *equal_sign;
	char *alias_name;
	int i;
	size_t alias_name_length;

	if (alias_command == NULL || *alias_count >= MAX_ALIAS_COUNT)
	{
		fprintf(stderr, "Invalid alias command or maximum alias count reached\n");
		return (-1);
	}
	equal_sign = strchr(alias_command, '=');
	if (equal_sign == NULL)
	{
		fprintf(stderr, "Invalid alias command format\n");
		return (-1);
	}
	alias_name_length = equal_sign - alias_command;
	alias_name = malloc(alias_name_length + 1);
	if (alias_name == NULL)
	{
		perror("Memory allocation failed");
		return (-1);
	}
	strncpy(alias_name, alias_command, alias_name_length);
	alias_name[alias_name_length] = '\0';
	for (i = 0; i < *alias_count; ++i)
	{
		if (strcmp(aliases[i], alias_name) == 0)
		{
			free(aliases[i]);
			aliases[i] = strdup(alias_command);
			free(alias_name);
			return (0);
		}
	}
	aliases[*alias_count] = strdup(alias_command);
	if (aliases[*alias_count] == NULL)
	{
		perror("Memory allocation failed");
		free(alias_name);
		return (-1);
	}
	(*alias_count)++;
	free(alias_name);
	return (0);
}

/**
 * print_aliases - Prints the list of aliases
 * @aliases: Array of aliases
 * @alias_count: Number of aliases
 */
void print_aliases(char *aliases[], int alias_count)
{
	int i;

	if (alias_count == 0)
	{
		printf("No aliases defined.\n");
	}
	else
	{
		printf("List of aliases:\n");
		for (i = 0; i < alias_count; ++i)
		{
			printf("%s\n", aliases[i]);
		}
	}
}
