#include "apue.h"

static void sig_quit(int);

int
main(void)
{
	sigset_t newmask, oldmask, pendmask;

	if (signal(SIGQUIT, sig_quit) == SIG_ERR)
		err_sys("can't catch SIGQUIT");
	
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask))
		err_sys("SIG_BLOCK error");

	sleep(5);
	
	if (sigpending(&pendmask) < 0)
		err_sys("sigpending error");
	if (sigismember(&pendmask, SIGQUIT))
		printf("\nSIGQUIT pending\n");

	/*
	pr_mask("in critical region: ");

	if (sigsuspend(&waitmask) != -1)
		err_sys("sigsuspend error");
	
	pr_mask("after return from sigsuspend:");
	*/

	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		err_sys("SIG_SETMASK error");
	
	printf("SIGQUIT unblocked\n");
	//pr_mask("program exit: ");

	sleep(5);
	exit(0);
}

static void
sig_quit(int signo)
{
	pr_mask("\nin sig_int");
}
