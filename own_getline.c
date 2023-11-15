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
