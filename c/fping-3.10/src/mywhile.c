#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
	char ch;

	while( (ch=getchar())!= 'q' )
		switch(ch){
			case 'a':
				printf("I am a!");
				break;
			case 'b':
				printf("I am b!");
				break;
			case 'c':
				printf("I am c!");
				break;
			case 'd':
				printf("I am c!");
				break;
			case 'e':
			case 'f':
			case 'g':
			default:
				printf("%c\n",ch);
		}

	exit(0);
}
