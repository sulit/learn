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
	char a[] = "hello";
	p = a;
	//setp(p);
	printf("%s\n", p);

	exit(0);
}
