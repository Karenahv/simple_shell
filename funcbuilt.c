#include "holberton.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#define MAX 500

/**
* _history - show history of commands.
* @h: node tha has the builtin command

* Return: no return
*/
int _history(command_t *h)
{
	(void)h;
	printf("función history\n");
	return (0);
}

/**
* _env - show all environment variables.
* @h: node tha has the builtin command
*
* Return: no return
*/
int _env(command_t *h)
{
	char **env = NULL, **args = NULL;
	int i = 0, l = 0;
	char sl = '\n';

	(void)h;
	args = h->args;
	if (args[1] != NULL)
	{
		search_file_env(h);
		return (0);
	}
	env = _setenv(NULL, NULL);
	while (env[i])
	{
		for (l = 0; env[i][l]; l++)
			;
		write(1, env[i], l);
		write(1, &sl, 1);
		i++;
	}
	return (0);
}
int _setenviron(command_t *h)
{
	char **args = NULL;
	int i = 0;
	args = h->args;
	for (; args[i]; i++)
		;
	if (i != 3)
	{
		printf("Error\n");
		return (-1);
	}
	_setenv(args[1], args[2]);
	return (0);
}
int _unsetenv(command_t *h)
{
	char **args = NULL;
	char *var = NULL;
	int i = 0;
	args = h->args;
	for (; args[i]; i++)
		;
	if (i != 2)
	{
		printf("Error\n");
		return (-1);
	}
	var = _getenvvar(args[1]);
	if (var)
	{
		_setenv(args[1], NULL);
		free(var);
		return (0);
	}
	else
	{
		printf("Error\n");
		return (-1);
	}
	return (-1);
}
/**
* _help - show help document of some functions.
* @h: node tha has the builtin command
*
* Return: no return
*/
int _help(command_t *h)
{
	char **argseach = NULL;
	int i = 0, j = 0, entero = 0, g, k;
	char *args[] = {"cd", "env", "history", "exit", "alias", NULL};
	char *filenames[] = {"h_cd.txt", "h_env.txt", "h_history.txt",
			     "h_exit.txt", "h_alias.txt", NULL};
	char *buffer = NULL;
	char *buf = NULL;
	ssize_t a = 0;
	ssize_t *p = &a;

	argseach = h->args;
	buffer = malloc(1024);
	if (buffer == NULL)
		return (0);
	if (argseach[1][0] == 0)
		return (0);
	while (args[i] != NULL)
	{
		for (j = 0; args[i][j] != '\0'; j++)
		{
			if (argseach[1][j] - args[i][j] != 0)
			{
				entero = argseach[1][j] - args[i][j];
				break;
			}
		}
		if (entero == 0)
		{
			for (j = 0; filenames[i][j] != 0; j++)
				;
			getcwd(buffer, 1024);
			for (g = 0; buffer[g]; g++)
				;
			buffer[g] = '/';
			g++;
			for (k = 0; k < j; k++)
			{
				buffer[g] = filenames[i][k];
				g++;
			}
			buf = _getline(p, buffer);
			printf("%s\n", buf);
		}
		i++;
	}
	free(buffer);
	return (0);
}

/**
* getvaderdir - get variable directory.
*
* Return: no return
*/
char  *getvaderdir(void)
{
	int l = 0, i = 0;
	char *pwd = NULL;
	char *newpwd = NULL;

	pwd = _getenvvar("PWD");
	for (; pwd[l]; l++)
		if (pwd[l] == '/')
			i = l;
	newpwd = _calloc(i + 2, sizeof(char));
	for (l = 0; pwd[l] && l < i; l++)
		newpwd[l] = pwd[l];
	free(pwd);
	return (newpwd);
}

/**
* chtopreviousdir - previous directory.
*
* Return: no return
*/
int chtopreviousdir(void)
{
	char *oldpwd = NULL;
	char *pwd = NULL;
	DIR *dir = NULL;
	int l = 0;
	char sl = '\n';

	oldpwd = _getenvvar("OLDPWD");
	pwd = _getenvvar("PWD");
	if (!oldpwd)
	{
		printf("OLDPWD not set error");
		free(pwd);
		return (-1);
	}
	else
	{
		dir = opendir(oldpwd);
		if (dir == NULL)
		{
			printf("ERROR\n");
			return (-1);
		}
		closedir(dir);
		chdir(oldpwd);
		_setenv("OLDPWD", pwd);
		for(; oldpwd[l]; l++)
			;
		write(1, oldpwd, l);
		write(1, &sl, 1);
		free(pwd);
		free(oldpwd);
		return (0);
	}
	return (-1);
}

/**
* darthCader - change directory father.
*
* Return: return 0
*/
int darthVader()
{
	char *newpwd = NULL;
	char *pwd = NULL;
	DIR *dir = NULL;
	pwd = _getenvvar("PWD");
	newpwd = getvaderdir();
	dir = opendir(newpwd);
	if (dir == NULL)
	{
		printf("Error :'v \n");
		free(pwd);
		free(newpwd);
		return(-1);
	}
	closedir(dir);
	chdir(newpwd);
	_setenv("PWD", newpwd);
	_setenv("OLDPWD", pwd);
	free(pwd);
	free(newpwd);
	return (0);
}
int lukeSkywalker(void)
{
	return (0);
}
int aredots(char *path, int pos, int size)
{
	if (path[pos] && path[pos + 1] && path[pos + 2])
	{
		if (path[pos] == '/' && path[pos + 1] == '.'
		    && path[pos + 2] == '.')
		{
			if ((pos + 3) <= size)
			{
				if ((path[pos + 3]) == 0 ||
				    (path[pos + 3]) == '/')
					return (1);
			}
		}
	}
	return (0);
}
int nextdir(char *filter, int i)
{
	if (!filter[i])
		return (-1);
	i++;
	for (; filter[i]; i++)
		if (filter[i] == '/')
			return(i);
	return (-1);
}
char *filtro1(char *path)
{
	char *filter = NULL;
	int j = 0, seek = 0, i = 0;
	for (; path[j]; j++)
		;
	filter = _calloc(j + 1, sizeof(char));
	for (; path[i]; i++)
	{
		if (path[i] == '/')
		{
			if (path[i + 1] == 0)
				break;
			if ((i + 1 <= j) && path[i + 1] == '/')
				continue;
			filter[seek] = path[i];
			seek++;
		}
		else
		{
			filter[seek] = path[i];
			seek++;
		}
	}
	return (filter);
}
char *filtro2(char *filter)
{
	char *cpypath = NULL;
	int j = 0, pos = 0, i = 0, cnt = 0;
	for (; filter[j]; j++)
		;
	cpypath = _calloc(j + 1, sizeof(char));

	for (i = 0; i <= j && filter[i]; i++)
	{
		if (i == 0 && aredots(filter, i, j))
		{
			i += 2;
			continue;
		}
		pos = nextdir(filter, i);
		if (pos == -1)
		{
			for (; filter[i]; i++, cnt++)
				cpypath[cnt] = filter[i];
			break;
		}
		if (aredots(filter, pos, j))
		{
			i = pos + 2;
			continue;
		}
		for (; i <= pos && filter[i]; i++, cnt++)
			cpypath[cnt] = filter[i];
		i--;
	}
	return (cpypath);
}
