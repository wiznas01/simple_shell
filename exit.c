#include "shell.h"
/**
 * exit_shell - exits the shell
 * @status: exit status
 */

void exit_shell(int status)
{
	printf("Exiting shell with status %d\n", status);
	exit(status);
}
