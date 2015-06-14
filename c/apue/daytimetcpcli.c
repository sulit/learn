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
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAXLINE 1024
#define SA struct sockaddr
#define FILEMODE S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

int
main(int argc, char *argv[])
{
	int sockfd;
	int n;
	char recvline[MAXLINE + 1];
	struct sockaddr_in servaddr;
	int fd;
	char buff[MAXLINE];

	if (argc != 2) {
		fprintf(stderr, "usage: a.out <IPaddress>");
		exit(errno);
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "socket error");
		exit(errno);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5555);
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
		fprintf(stderr, "lnet_pton error for %s", argv[1]);
		exit(errno);
	}

	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0) {
		fprintf(stderr, "connect error");
		exit(errno);
	}

	if ((fd = open("unp.h.bak", O_RDWR | O_APPEND | O_CREAT, FILEMODE)) < 0)
		return -1;
	while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
		/*
		recvline[n] = 0;
		if (fputs(recvline, stdout) == EOF) {
			fprintf(stderr, "fputs error");
		exit(errno);
		}
		*/
		if (write(fd, recvline, n) != n) {
			close(fd);
			return -1;
		}
	}
	if (n < 0) {
		fprintf(stderr, "read error%d\n", errno);
		exit(errno);
	}
	close(fd);
	close(sockfd);

	exit(0);
}
