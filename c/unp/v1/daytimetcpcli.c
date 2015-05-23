/*============================================
 *   Copyright (C) 2015 All rights reserved.
 *
 *   filename : daytimetcpcli.c
 *   author : sulit - sulitsrc@163.com
 *   last modified : 2015-05-23 00:03
 *   description :
 *
 *============================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAXLINE 1024
#define SA struct sockaddr

int
main(int argc, char *argv[])
{
	int sockfd;
	int n;
	char recvline[MAXLINE + 1];
	struct sockaddr_in servaddr;

	if (argc != 2) {
		fprintf(stderr, "usage: a.out <IPaddress>");
		exit(errno);
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "socket error");
		exit(errno);
	}

	//bzero(&servaddr, sizeof(servaddr));弃用
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
		fprintf(stderr, "lnet_pton error for %s", argv[1]);
		exit(errno);
	}

	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0) {
		fprintf(stderr, "connect error");
		exit(errno);
	}

	while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;
		if (fputs(recvline, stdout) == EOF) {
			fprintf(stderr, "fputs error");
		exit(errno);
		}
	}
	if (n < 0) {
		fprintf(stderr, "read error%d\n", errno);
		exit(errno);
	}

	exit(0);
}
