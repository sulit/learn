#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
	struct timeval *tv;
	struct timezone *tz;
	long int result;

	gettimeofday(tv,tz);
	srandom(tv->tv_sec * 1000000 + tv->tv_usec + getpid());
	result = random();

	printf("The result is %ld\n",result);

	exit(0);
}
