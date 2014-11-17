#include <stdio.h>

int
main(int argc, char *argv[])
{
	printf("This program argc is %d\n",argc);
	for(int i=0; i<argc; i++)
		printf("This program argv[%d] is %s\n",i,argv[i]);
	
	return 0;
}
