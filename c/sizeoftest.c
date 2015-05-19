#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct test {
	char *p;
	int *i;
};

int
main()
{
	char *p = "hello world";
	int *i;
	float *f;
	double *d;
	long *l;
	long *ll;
	struct test *s;
	char *q;
	printf("%d\n", strlen(p));
	printf("%d\n", sizeof(p));
	printf("%d\n", sizeof(i));
	printf("%d\n", sizeof(f));
	printf("%d\n", sizeof(d));
	printf("%d\n", sizeof(l));
	printf("%d\n", sizeof(ll));
	printf("%d\n", sizeof(s));
	printf("%d\n", strlen(q));

	exit(0);
}
