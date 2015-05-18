#include<stdlib.h>
#include<stdio.h>

int
main(int argc, char *argv[])
{
	float n;
	char const *str="12345.67";
	n=atoi(str);
	printf("string=%s,float=%f\n",str,n);
	return 0;
}
