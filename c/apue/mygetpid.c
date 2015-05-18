#include "apue.h"

int
main(void)
{
	printf("hello world from process ID %ld\n", (long)getpid());
	sleep(1);

	exit(0);
}
