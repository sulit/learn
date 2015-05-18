/*============================================
 *   Copyright (C) 2015 All rights reserved.
 *
 *   filename : sig_pend.c
 *   author : sulit - sulitsrc@163.com
 *   last modified : 2015-05-17 18:38
 *   description :
 *
 **============================================*/

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void printsigset(const sigset_t *set)
{
	int i;
	for (i = 1; i < 32; i++)
		if (sigismember(set, i) == 1)
			putchar('1');
		else
			putchar('0');
	puts("");
}

int main(void)
{
	sigset_t s, p;
	sigemptyset(&s);
	sigaddset(&s, SIGINT);
	sigprocmask(SIG_BLOCK, &s, NULL);
	while (1) {
		sigpending(&p);
		printsigset(&p);
		sleep(1);
	}
	return 0;
}
