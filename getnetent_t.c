#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
	struct netent *netentinfo;
	netentinfo = getnetent();

	printf("net'name is %s\n", netentinfo->n_name);
	while (*netentinfo->n_aliases != NULL) {
		printf("net aliases is %s\n", netentinfo->n_aliases);
		netentinfo->n_aliases++;
	}
	printf("net'addrtype is %d\n", netentinfo->n_addrtype);
	printf("net'net is %d\n", netentinfo->n_net);

	exit(0);
}
