#include <stdio.h>
#include <stdlib.h>

void setp(p)
{
	char a[] = "hello";

	p = a;
}

int
main()
{
	char * p;
	setp(p);
	printf("%s\n", p);

	exit(0);
}
