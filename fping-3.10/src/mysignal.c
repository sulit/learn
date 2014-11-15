#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

#define true 1
#define false 0

void
sign_handler()
{
	printf("Capture sign\n"); 

	exit(0);
}

int
main(int argc, char *argv[])
{
	signal(SIGINT,sign_handler); 
	while(true)
	  sleep(1); 

	return 0; 
}
