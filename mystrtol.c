/*============================================
*   Copyright (C) 2015 All rights reserved.
*
*   filename : mystrtol.c
*   author : sulit - sulitsrc@163.com
*   last modified : 2015-05-10 11:02
*   description :
*
**============================================*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	long int key = strtol(argv[1], NULL, 0);

	printf("strtol argv[1] is %ld\n", key);

	exit(0);
}
