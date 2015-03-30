#include <stdio.h>
#include <stdlib.h>

#define MAXBUFFER 1024

void setp(char *p)
{
	char *a = "hello";

	*p = *a; //这时赋值的只有h，因为*a代表的是*(a+0)，即a[0]
}

int
main()
{
	char buf[MAXBUFFER]={0};
	char * p;
	p = buf;
	setp(p);
	printf("%s\n", p);

	exit(0);
}
