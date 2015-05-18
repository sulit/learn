#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, char *argv[])
{
	char src[] = "hello";
	char des[512];
	char *ptr;
	ptr = memcpy(des,src,strlen(src));
	if(ptr)
		printf("%s\n",des);

	exit(0);
}
