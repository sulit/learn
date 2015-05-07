/*============================================
*   Copyright (C) 2015 All rights reserved.
*
*   filename : 16_11.c
*   author : sulit - sulitsrc@163.com
*   last modified : 2015-05-07 20:17
*   description :
*
**============================================*/

#include "apue.h"
#include <sys/socket.h>

#define MAXSLEEP 128

int connect_retry(int domain, int type, int protocol, const struct sockaddr *addr, socklen_t alen)
{
	int numsec, fd;

	for (numsec = 1; numsec <= MAXSLEEP; numsec <<= 1) {
		if ((fd = socket(domain, type, protocol)) < 0)
			return(-1);
		if (connect(fd, addr, alen) == 0) {
			return(fd);
		}
		close(fd);

		if (numsec <= MAXSLEEP/2)
			sleep(numsec);
	}
	return(-1);
}
