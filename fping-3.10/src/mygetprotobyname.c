#include <stdio.h>
#include <netdb.h>

int
main(int argc, char *argv[])
{
	struct protoent *info = NULL;
	info = getprotobyname("icmp");
	//info = getprotobyname("ip");
	//info = getprotobyname("tcp");
	//info = getprotobyname("udp");

	printf("%s\n",info->p_name);
	printf("list start\n");
	while (*(info->p_aliases))
	{
		printf("%s\n",*(info->p_aliases));
		info->p_aliases++;
	}
	printf("list end\n");
	printf("%d\n",info->p_proto);
	
	return 0;
}
