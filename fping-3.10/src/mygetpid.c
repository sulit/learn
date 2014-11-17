#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
	printf("This program pid is %X\n",getpid());
	printf("This program pid is %X\n",(getpid() & 0xFFFF));
	
	return 0;
}
