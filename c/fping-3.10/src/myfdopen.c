#include<stdio.h>
int
main(int argc, char *argv[])
{
	FILE * fp = fdopen(1,"w+");
	fprintf(fp,"%s\n","hello!");
	fclose(fp);

	return 0;
}
