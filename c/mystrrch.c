#include <string.h>
#include <stdio.h>
int main(void)
{
	char string[20];
	char *ptr, c = ':';
	strcpy(string, "[192.168.11.11:]80");
	ptr = strrchr(string, c);
	if (ptr)
	  printf("The character %c is at position: %s\n", c, ptr);
	else
	  printf("The character was not found\n");
	return 0;
}
