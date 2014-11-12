#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>

int mygetchar(void);

int
main(int argc, char *argv[])
{
	while(mygetchar() != 'q')
	{
		printf("%d\n",mygetchar());
	}

	return 0;
}

int mygetchar(void)
{
	static char buf[BUFSIZ];
	static char *bufp = buf;
	static int n = 0;

	if(n == 0)
	{
		n = read(0, buf, sizeof buf);
		bufp =buf;
	}

	return (--n >= 0) ? (unsigned char) *bufp++ : EOF;
}
