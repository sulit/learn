/*============================================
 *   Copyright (C) 2015 All rights reserved.
 *
 *   filename : daytimetcpsrv.c
 *   author : sulit - sulitsrc@163.com
 *   last modified : 2015-05-23 22:13
 *   description :
 *
 *============================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAXLINE 1024
#define SA struct sockaddr

int listfilenames(const int socket, const char *dirname);
int sendfile(const int socket, const char *dirname);

int
main(int argc, char *argv[])
{
	int listenfd;
	int connfd;
	struct sockaddr_in servaddr;
	//char buff[MAXLINE];
	//time_t ticks;

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "socket error\n");
		exit(errno);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(5555);
	if ((bind(listenfd, (SA *)&servaddr, sizeof(servaddr))) != 0) {
		fprintf(stderr, "bind error\n");
		exit(errno);
	}

	if ((listen(listenfd, 5)) != 0) {
		fprintf(stderr, "listen error\n");
		exit(errno);
	}

	for ( ; ; ) {
		connfd = accept(listenfd, (SA *)NULL, NULL);

		/*
		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		if ((write(connfd, buff, strlen(buff))) < 0) {
			fprintf(stderr, "write socket error\n");
			exit(errno);
		}
		*/
		//if (listfilenames(connfd, ".") < 0)
		//	fprintf(stderr, "write socket error\n");
		if (sendfile(connfd, "/home/sulit/src/ftp/myftp/test.txt") < 0)
			fprintf(stderr, "write socket error\n");

		if (close(connfd) < 0) {
			fprintf(stderr, "close socket error\n");
			exit(errno);
		}
	}

	exit(0);
}

int listfilenames(const int socket, const char *dirname)
{
	DIR	*dp;
	struct dirent *dirp;
	char buff[MAXLINE];

	assert(dirname != NULL);

	if ((dp = opendir(dirname)) == NULL)
		return -1;
	while ((dirp = readdir(dp)) != NULL) {
		if (strcmp(dirp->d_name, ".") && strcmp(dirp->d_name, "..")) {
			memset(buff, 0, sizeof(buff));
			snprintf(buff, sizeof(buff),"%s\n", dirp->d_name);
			if ((write(socket, buff, strlen(buff))) < 0) {
				return -1;
			}
		}
	}

	return 0;
}

int sendfile(const int socket, const char *filename)
{
	char buff[MAXLINE];
	int fd;
	ssize_t n;

	if ((fd = open(filename, O_RDONLY)) < 0) {
		return -1;
	}

	while ((n = read(fd, buff, sizeof(buff))) > 0)
		if (send(socket, buff, n, 0) < 0) {
			close(fd);
			return -1;
		}

	close(fd);

	return 0;
}
