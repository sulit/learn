#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int
main(int argc, char *argv[])
{
	char *str = NULL;
	/*分配内存空间*/
	str = (char*) calloc(10,sizeof(char));
	/*将hello写入*/
	strcpy(str,"Hello");
	/*显示变量内容*/
	printf("Stringis%s\n",str);
	/*释放空间*/
	free(str);

	exit(0);
}
