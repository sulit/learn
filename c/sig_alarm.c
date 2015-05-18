/*============================================
*   Copyright (C) 2015 All rights reserved.
*
*   filename : sig_alarm.c
*   author : sulit - sulitsrc@163.com
*   last modified : 2015-05-17 18:26
*   description :
*
**============================================*/

#include <unistd.h>
#include <stdio.h>

int main(void)
{
	int counter;
	alarm(1);
	for (counter = 0; 1; counter++)
		printf("counter=%d ", counter);
	return 0;
}
