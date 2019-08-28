#define MAX 4096
#define READING 1
#include "holberton.h"
#include <stdio.h>
#include <signal.h>
/**
 * _getline - function that gets a line from the stdin.
 * @pos: pointer to the actual buffer position.
 * @pathname: path of the file to read.
 * Return: pointer to the buffer that stores the line.
 */
char *_getline(ssize_t *pos, char *pathname)
{
	int fd = 0, flag = 1, state = 0;
	ssize_t n = 0;
	char *cpy = NULL, *buf = NULL;
	size_t size = MAX;

	fd = open(pathname, O_RDONLY);
	buf = _calloc(size, 1);
	state = READING;
	while (state)
	{
		if (!buf)
			return (NULL);
		n = read(fd, buf, MAX);
		*pos += n;
		if (buf[0] == 0)
			break;
		if (n == -1)
		{
			free(buf);
			return (NULL);
		}
		if (n != MAX && buf[*pos - 1] == '\n')
			break;
	}
	*pos -= 1;
	if (buf[*pos] == '\n')
		*pos -= 1;
	if (flag)
		return (buf);
	return (cpy);
}
