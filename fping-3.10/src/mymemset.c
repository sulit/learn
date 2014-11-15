#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, char *argv[])
{
	char s[]="hello";
	char *pstr;

	printf("%s\n",s);

	pstr = memset(s,'*',strlen(s));

	if(pstr)
		printf("%s\n",s);

	exit(0);
}
