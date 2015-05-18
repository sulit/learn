#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void my_func(int sign_no)
{
	if (sign_no == SIGINT)
	{
		printf("I have get SIGINT\n");
	}
	else if (sign_no == SIGQUIT)
	{
		printf("I have get SIGQUIT\n");
	}
}

int
main()
{
	struct sigaction action;
	printf("Waiting for signal SIGINT or SIGQUIT...\n");

	action.sa_handler = my_func;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;

	sigaction(SIGINT, &action, 0);
	sigaction(SIGQUIT, &action, 0);

	pause();
	exit(0);
}
