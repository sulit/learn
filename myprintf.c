#include <stdio.h>
#include <stdlib.h>

//测试printf的返回值
int
main(int argc, char * argv[])
{
	if (argc == 1)
	{
		if (*argv[0] == '.')
		{
			if (*(++argv[0]) == '/')
				argv[0]++;
			else
				argv[0]--;
		}
		printf("This out %d chars\n", printf("The program name is %s\n", argv[0]));
	}
	
	exit(0);
}
