#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>

int
main(int argc, char *argv[])
{
	struct sockaddr *sa;    /* input */
	socklen_t len;         /* input */
	char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];

	if (getnameinfo(sa, len, hbuf, sizeof(hbuf), sbuf,
					sizeof(sbuf), NI_NUMERICHOST | NI_NUMERICSERV) == 0)
	  printf("host=%s, serv=%s\n", hbuf, sbuf);

	exit(0);
}
