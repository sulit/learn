/*============================================
 *   Copyright (C) 2015 All rights reserved.
 *
 *   filename : daytimetcpcli.c
 *   author : sulit - sulitsrc@163.com
 *   last modified : 2015-05-23 00:03
 *   description :
 *
 *============================================*/

#include "unp.h"

int
main(int argc, char *argv[])
{
	int sockfd;
	int n;
	char recvline[MAXLINE + 1];
	struct sockaddr_in servaddr;

	if (argc != 2)
		err_quit("usage: a.out <IPaddress>");

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	//bzero(&servaddr, sizeof(servaddr));弃用
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		err_sys("lnet_pton error for %s", argv[1]);

	if (connect(sockfd, (SA *) &servaddr, MAXLINE) > 0)
		err_sys("connect error");

	while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;
		if (fputs(recvline, stdout) == EOF)
			err_sys("fputs error");
	}
	if (n < 0)
		err_sys("read error");

	exit(0);
}
