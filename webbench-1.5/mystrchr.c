#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char *p = strchr(argv[1],':');
	printf("the str is %s\n", p+1);
	char *q = strrchr(argv[1],':');
	printf("the str is %s\n", q+1);

	exit(0);
}
