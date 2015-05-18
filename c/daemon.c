#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int
main()
{
	pid_t pid;
	int i, fd;
	char *buf = "This is a Daemon\n";

	pid = fork();
	if (pid < 0)
	{
		printf("Error fork\n");
		exit(1);
	}
	else if (pid > 0)
	{
		exit(0);
	}

	setsid();
	chdir("/");
	umask(0);
	for (i = 0; i < getdtablesize(); i++)
	{
		close(i);
	}

	while(1)
	{
		if ((fd = open("/tmp/daemon.log", O_CREAT | O_WRONLY | O_APPEND, 0600)) < 0)
		{
			printf("Open file error\n");
			exit(1);
		}
		write(fd, buf, strlen(buf) + 1);
		close(fd);
		sleep(10);
	}
	exit(0);
}
