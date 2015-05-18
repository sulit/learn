#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int
main()
{
	int ret = alarm(5);
	pause();
	printf("I(%d) have been waken up.\n", ret);
}
