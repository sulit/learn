/*============================================
 *   Copyright (C) 2015 All rights reserved.
 *
 *   filename : stringreverse.c
 *   author : sulit - sulitsrc@163.com
 *   last modified : 2015-06-05 21:16
 *   description :
 *
 *============================================*/

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1024

int mygetline(char s[], int lim);
void reverse(char s[]);

int main()
{
	char line[MAXLINE];

	while (mygetline(line, MAXLINE) > 0) {
		reverse(line);
		printf("%s", line);
	}

	exit(0);
}

void reverse(char s[])
{
	int i, j;
	char temp;

	i = 0;
	while (s[i] != '\0')
		i++;

	--i;
	if (s[i] == '\n')
		--i;
	j = 0;
	while (j < i) {
		temp = s[j];
		s[j] = s[i];
		s[i] = temp;
		--i;
		++j;
	}
}

int mygetline(char s[], int lim)
{
	int c, i;

	for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
