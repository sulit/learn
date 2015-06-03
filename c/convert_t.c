/*============================================
 *   Copyright (C) 2015 All rights reserved.
 *
 *   filename : convert_t.c
 *   author : sulit - sulitsrc@163.com
 *   last modified : 2015-06-03 10:13
 *   description :
 *
 *============================================*/

#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
	unsigned int a = 6;
	int b = -20;
	(a + b > 6) ? puts(">6") : puts("<=6");

	exit(0);
}
