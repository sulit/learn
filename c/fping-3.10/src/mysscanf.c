#include <stdio.h>

int
main(int argc, char *argv[])
{
	char buf[512];
	sscanf("123456","%4s",buf);
	printf("%s\n",buf);

	return 0;
}
