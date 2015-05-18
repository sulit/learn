#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int
main()
{
	char resolved_path[80];
	realpath(".",resolved_path);
	printf("resolved_path: %s\n", resolved_path);

	return 0;
}
