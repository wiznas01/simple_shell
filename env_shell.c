#include "shell.h"

/**
 * env_shell - Prints the current environment variables.
 * @envp: Pointer to the environment variables array.
 */

void env_shell(char **envp)
{
	int i = 0;

	if (envp == NULL)
	{
		fprintf(stderr, "Environment variables array is empty\n");
		return;
	}
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
}
