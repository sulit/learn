#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
	int i;
	for (i = 0; i < 10; i++)
	printf("%x\n", 1 << i);
	
	exit(0);
}
