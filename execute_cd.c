#include "shell.h"
#include <limits.h>
/**
 * execute_cd - Change the current directory.
 * @dir: Directory to change to (NULL if not specified).
 * @envp: enviromental variables
 * Return: 0 on success, -1 on failure.
 */
int execute_cd(char *dir, char **envp)
{
	char *new_dir;
	char current_dir[PATH_MAX];

	(void)envp;

	if (dir == NULL || strcmp(dir, "-") == 0)
	{
		new_dir = getenv("OLDPWD");
		if (new_dir == NULL)
		{
			fprintf(stderr, "cd: OLDPWD not set\n");
			return (-1);
		}
	}
	else if (strcmp(dir, "~") == 0)
	{
		new_dir = getenv("HOME");
		if (new_dir == NULL)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return (-1);
		}
	}
	else
		new_dir = dir;

	if (!getcwd(current_dir, PATH_MAX) || chdir(new_dir) == -1)
	{
		perror("chdir");
		return (-1);
	}
	if (setenv("OLDPWD", current_dir, 1) == -1 || setenv("PWD", new_dir, 1) == -1)
	{
		perror("setenv");
		return (-1);
	}
	return (0);
}
