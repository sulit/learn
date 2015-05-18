#include <stdio.h>

int
main(int argc, char *argv[])
{
	FILE *fp = fopen("/srv/tftp/test","w+");

	fprintf(fp,"hello world\n");
	fclose(fp);
	
	return 0;
}
