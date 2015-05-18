#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int
main()
{
	char *envp[] = {"PATH=/tmp", "USER=sulit", NULL};

	if (fork() == 0)
	{
		if (execle("/usr/bin/env", "env", NULL, envp) < 0)
		{
			printf("Execle error\n");
		}
	}
}
