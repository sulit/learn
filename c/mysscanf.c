/*============================================
*   Copyright (C) 2015 All rights reserved.
*
*   filename : mysscanf.c
*   author : sulit - sulitsrc@163.com
*   last modified : 2015-05-09 14:16
*   description :
*
**============================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, char *argv[])
{
	double d;
	char buf[2];
	memset(buf, 0, sizeof(buf));
	sscanf(argv[1], "%lf%ls", &d, buf);

	printf("d is %lf, buf is %ls\n", d, buf);

	exit(0);
}
