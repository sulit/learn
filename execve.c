#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int
main()
{
	char *arg[] = {"env", NULL};
	char *envp[] = {"PATH=/tmp", "USER=sulit", NULL};

	if (fork() == 0)
	{
		if (execve("/usr/bin/env", arg, envp))
		{
			printf("Execvp error\n");
		}
	}

	return 0;
}
