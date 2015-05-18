#include <stdio.h>
#include <stdlib.h>

void setp(char *p)
{
	char a[] = "hello";

	p = a; //栈上的变量值不能赋给这个函数之外的指针，因为当这个函数调用结束时，变量的内容就被清除，这时指针指向的内容就变了，这种操作是不被允许的。
}

int
main()
{
	char * p;
	setp(p);
	printf("%s\n", p);

	exit(0);
}
