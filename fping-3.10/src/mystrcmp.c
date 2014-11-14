#include <stdio.h>
#include<string.h>

int
main(int argc, char *argv[])
{
	char *s1 = "Hello,Programmers!";
	char *s2 = "Hello,Programmers!";
	int r;

	r = strcmp(s1,s2);

	printf("%d\n",r);
	if(!r)
	  printf("s1 and s2 are identical\n");
	else if(r < 0)
		printf("s1 less than s2\n");
	else
	  printf("s1 greater than s2\n");

	return 0;
}
