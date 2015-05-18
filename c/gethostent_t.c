#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
	struct hostent *hostentinfo;
	hostentinfo = gethostent();

	printf("Host'name is %s\n", hostentinfo->h_name);
	while (*hostentinfo->h_aliases != NULL) {
		printf("Host aliases is %s\n", hostentinfo->h_aliases);
		hostentinfo->h_aliases++;
	}
	printf("Host'addrtype is %d\n", hostentinfo->h_addrtype);
	printf("Host'length is %d\n", hostentinfo->h_length);

	exit(0);
}
