#include "shell.h"

/**
 * execute_setenv - Implement the setenv builtin command
 * @var: Variable to set
 * @value: Value to assign to the variable
 * Return: 0 on success, -1 on failure
 */

int execute_setenv(char *var, char *value)
{
	if (setenv(var, value, 1) == -1)
	{
		perror("setenv");
		return (-1);
	}
	return (0);
}

/**
 * execute_unsetenv - Implement the unsetenv builtin command
 * @var: Variable to unset
 * Return: 0 on success, -1 on failure
 */

int execute_unsetenv(char *var)
{
	if (unsetenv(var) == -1)
	{
		perror("unsetenv");
		return (-1);
	}
	return (0);
}
