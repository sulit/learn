#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

#define true 1
#define false 0

int main()
{
	signal(SIGINT,SIG_IGN); //Ctrl+\
	while(true)
	  sleep(1); 
	return 0; 
}
