#include <stdio.h>
#include <stdlib.h>

struct hello{
 double f;
 int count;
};

struct hello * getp()
{
	struct hello *p = malloc(sizeof(struct hello));

	p->f = 1.0;
	p->count = 1;

	return p;
}

int
main(int argc, char *argv[])
{
	struct hello *p = getp();

	printf("p is %f, count is %d\n", p->f, p->count);

	free(p);

	exit(0);
}
