#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char *p = strstr(argv[1], "://");
	printf("the str is %s\n", p);

	exit(0);
}
