#include<stdio.h>
#include<malloc.h>

int main(int argc, char *argv[])
{
	char *p;

	p=(char *)malloc(1);
	if(p)
	  printf("Memory Allocated at: %x\n",(unsigned int)p);
	else
	  printf("Not Enough Memory!\n");
	free(p);
	return 0;
}
