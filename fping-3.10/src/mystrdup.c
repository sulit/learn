#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int
main()
{
	char *s="hello strdup";
	char *d;

	d=strdup(s);

	printf("%s\n",d);
	free(d);

	exit(0);
}
