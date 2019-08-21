#define MAX 1024
#include "holberton.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
int main (void)
{
    int status;
    ssize_t a = 89;
    ssize_t *p = &a;
    char *buf = NULL;
    command_t *h;
    getentorno();
    while (1)
    {
        status = 0;
        a = 0;
        prompt();
        buf = _getline(p, NULL);
        h = _getargs(buf, p);
        if (!h)
		return (0);
        while (h != NULL)
        {
            if (!h->args)
                return (0);
            if (fork() == 0)
            {
                status = execve(*h->args, h->args, NULL);
            }
            else
                wait(NULL);
            if (status == -1)
            {
                printf("Error.\n");
            }
            h = h->next;
        }
            free(buf);
    }
    return (0);
}
