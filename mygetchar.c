#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>

int getchar(void);

int
main(int argc, char *argv[])
{
	printf("%d\n",getchar());

	return 0;
}

int getchar(void)
{
	char c;

	return (read(0, &c, 1) == 1) ? (unsigned char) c : EOF;
}
