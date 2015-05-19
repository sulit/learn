/*============================================
*   Copyright (C) 2015 All rights reserved.
*
*   filename : c_7_1.c
*   author : sulit - sulitsrc@163.com
*   last modified : 2015-05-19 21:47
*   description : argc[0] A.OUT -> a.out
*
**============================================*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int
main(int argc, char *argv[])
{
	while (*argv[0] != '\0')
		putchar(tolower(*argv[0]++));
	putchar('\0');
	putchar('\n');
	printf("%.*s\n", 6, "hello world");
	char *q = "hello%sworld";
	printf(q);

	exit(0);
}
