/*============================================
*   Copyright (C) 2015 All rights reserved.
*
*   filename : 17_4.c
*   author : sulit - sulitsrc@163.com
*   last modified : 2015-05-10 00:38
*   description :
*
**============================================*/

#include "apue.h"
#include <sys/msg.h>

#define MAXMSZ 512

struct mymesg {
	long mtype;
	char mtext[MAXMSZ];
};

int main(int argc, char *argv[])
{
	key_t key;
	long qid;
	size_t nbytes;
	struct mymesg m;

	if (argc != 3) {
		fprintf(stderr, "usage: sending KEY message\n");
		exit(1);
	}

	key = strtol(argv[1], NULL, 0);
	if ((qid = msgget(key, 0)) < 0)
		err_sys("can't open queue key %s", argv[1]);
	memset(&m, 0, sizeof(m));
	strncpy(m.mtext, argv[2], MAXMSZ-1);
	nbytes = strlen(m.mtext);
	m.mtype = 1;
	if (msgsnd(qid, &m, nbytes, 0) < 0)
		err_sys("can't send message");
	exit(0);
}
