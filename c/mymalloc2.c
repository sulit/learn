#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * getp()
{
	char *p = (char *)malloc(sizeof(char)*6);
	strcpy(p, "hello");

	return p;
}

int
main(int argc, char *argv[])
{
	char *p = getp();

	printf("%s\n", p);

	free(p);

	exit(0);
}
