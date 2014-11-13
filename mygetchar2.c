#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>

int mygetchar(void);

int
main(int argc, char *argv[])
{
	int value = 0;
	while(1)
	{
		if ((value = mygetchar()) == EOF) // EOF is Ctrl + d
		  break;
		if (value != 10)
		printf("%d\n",value);
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
