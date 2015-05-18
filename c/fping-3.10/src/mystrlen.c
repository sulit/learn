#include <stdio.h>
#include <string.h>

int
main(int argc, char *argv[])
{
	char s[] = "hello";

	printf("sizeof is %d\n",sizeof s);
	printf("strlen is %d\n",strlen(s));

	return 0;
}
