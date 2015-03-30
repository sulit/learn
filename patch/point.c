#include <stdio.h>
#include <stdlib.h>

#define MAXBUFFER 1024

void setp(char *p)
{
	char *a = "hello";

	*p = *a;
}

int
main()
{
	char buf[MAXBUFFER];
	char * p;
	p = buf;
	setp(p);
	printf("%s\n", p);

	exit(0);
}
