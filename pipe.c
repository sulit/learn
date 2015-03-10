#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DATA_LEN 256
#define DELAY_TIME 1

int
main()
{
	pid_t pid;
	int pipe_fd[2];
	char buf[MAX_DATA_LEN];
	const char data[] = "Pipe Test Program";
	int real_read, real_write;

	memset((void *)buf, 0, sizeof(buf));
	if (pipe(pipe_fd) < 0)
	{
		printf("pipe create error\n");
		exit(1);
	}
	if ((pid = fork()) == 0)
	{
		close(pipe_fd[1]);
		sleep(DELAY_TIME * 3);

		if ((real_read = read(pipe_fd[0], buf, MAX_DATA_LEN)) > 0)
		{
			printf("%d bytes read from the pipe is '%s'\n", real_read, buf);
		}
		close(pipe_fd[0]);
		exit(0);
	}
	else if (pid > 0)
	{
		close(pipe_fd[0]);
		sleep(DELAY_TIME);
		if ((real_write = write(pipe_fd[1], data, strlen(data))) != -1)
		{
			printf("Parent wrote %d bytes : '%s'\n", real_write, data);
		}
		close(pipe_fd[1]);
		waitpid(pid, NULL, 0);
		exit(0);
	}
}
