#include <stdio.h>
#include <stdlib.h>

int myf(int n);

int main(void)
{
	int n = 10;

	printf("%d\n", myf(n));

	exit(0);
}

int myf(int n)
{
	if (n == 1)
		return 1;
	else if (n == 2)
		return 4;
	else
		return myf(n - 1) * 2 + myf(n - 2);

}
