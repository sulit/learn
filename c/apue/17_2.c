/*============================================
*   Copyright (C) 2015 All rights reserved.
*
*   filename : 17_2.c
*   author : sulit - sulitsrc@163.com
*   last modified : 2015-05-09 21:46
*   description :
*
**============================================*/

#include "apue.h"
#include <sys/socket.h>

int
fd_pipe(int fd[2])
{
	return(socketpair(AF_UNIX, SOCK_STREAM, 0, fd));
}
