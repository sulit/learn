#include <stdio.h>

int main(void)
{
	char *p;
	int *q;
	double *r = NULL;
	float *s = NULL;
	char chara[5];
	int inta[5];
	double doublea[5];
	float floata[5];

	chara[0] = 'a';
	chara[1] = 'b';
	chara[2] = 'c';
	chara[3] = 'd';
	chara[4] = 'e';
	inta[0] = 0;
	inta[1] = 1;
	inta[2] = 2;
	inta[3] = 3;
	inta[4] = 4;
	doublea[0] = 0;
	doublea[1] = 1;
	doublea[2] = 2;
	doublea[3] = 3;
	doublea[4] = 4;
	floata[0] = 0;
	floata[1] = 1;
	floata[2] = 2;
	floata[3] = 3;
	floata[4] = 4;
	p = chara;
	q = inta;

	printf("%d\n",chara[0]);
	printf("%p\n",chara);
	printf("%p\n",p);
	printf("%d\n",sizeof(p));
	printf("%p\n",p++);
	printf("%p\n",p+4);
	
	printf("\n");

	printf("%d\n",inta[0]);
	printf("%p\n",inta);
	printf("%p\n",q);
	printf("%d\n",sizeof(q));
	printf("%p\n",q++);
	printf("%p\n",q+4);

	printf("\n");

	printf("%f\n",doublea[0]);
	printf("%p\n",doublea);
	printf("%p\n",r);
	printf("%d\n",sizeof(r));
	printf("%p\n",r++);
	printf("%p\n",r+4);

	printf("\n");

	printf("%f\n",floata[0]);
	printf("%p\n",floata);
	printf("%p\n",s);
	printf("%d\n",sizeof(s));
	printf("%p\n",s++);
	printf("%p\n",s+4);

	printf("\n");
	return 0;
}
