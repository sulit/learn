#include <unistd.h>
#include <stdio.h>

int
main(void)
{
	pid_t pid;

	if ((pid = fork()) < 0)
	{
		printf("error");
		return 1;
	}
	else if (pid == 0)
		printf("child\n");
	else
		printf("parent\n");

	return 0;
}
