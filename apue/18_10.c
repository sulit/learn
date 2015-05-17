/*============================================
*   Copyright (C) 2015 All rights reserved.
*
*   filename : 18_10.c
*   author : sulit - sulitsrc@163.com
*   last modified : 2015-05-18 00:49
*   description :
*
**============================================*/

#include "apue.h"
#include <termios.h>

int
main(void)
{
	struct termios term;
	long	vdisable;

	if (isatty(STDIN_FILENO) == 0)
		err_sys("standard input is not a terminal device");

	if ((vdisable = fpathconf(STDIN_FILENO, _PC_VDISABLE)) < 0)
		err_sys("fpathconf error or _POSIX_VDISABLE not in effect");

	if (tcgetattr(STDIN_FILENO, &term) < 0)
		err_sys("tcgetattr error");

	term.c_cc[VINTR] = vdisable;
	term.c_cc[VEOF] = 2;

	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term) < 0)
		err_sys("tcsetattr error");

	exit(0);
}
