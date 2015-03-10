#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#define MYFIFO "/tmp/myfifo"
#define MAX_BUFFER_SIZE PIPE_BUF

int
main()
{
	int fd;
	char buff[MAX_BUFFER_SIZE];
	int nread;

	if (access(MYFIFO, F_OK) == -1)
	{
		if ((mkfifo(MYFIFO, 0666) < 0) && (errno != EEXIST))
		{
			printf("Cannot create fifo file\n");
			exit(1);
		}
	}

	fd = open(MYFIFO, O_RDONLY);
	if (fd == -1)
	{
		printf("Open fifo file error\n");
		exit(1);
	}

	while(1)
	{
		memset(buff, 0, sizeof(buff));
		if ((nread = read(fd, buff, MAX_BUFFER_SIZE)) > 0)
		{
			printf("Read '%s' from FIFO\n", buff);
		}
	}
	close(fd);
	exit(0);
}
