#include <stdio.h>
#include <stdlib.h>

struct L {
	int v;
	struct  L *next;
};

void showL(struct L *head);
void addvalue(struct L *head, int value);

int
main(int argc, char *argv[])
{
	struct L *p = NULL;
	struct L *head;

	int i;

	for (i = 0; i < 10; i++)
	{
		if (!p)
		{
			p = (struct L *)malloc(sizeof(struct L));
			head = p;
			p->v = i;
			p->next = NULL;
		}
		else
		{
			p->next = (struct L *)malloc(sizeof(struct L));
			p = p->next;
			p->v = i;
			p->next = NULL;
		}
	}
	showL(head);
	addvalue(head, 10);
	printf("After add, list L is:\n");
	showL(head);
	
	exit(0);
}

void showL(struct L *head)
{
	struct L *q;
	for (q = head; q;q = q->next)
		printf("This is %d\n", q->v);
}

void addvalue(struct L *head, int value)
{
	struct L *q;
	for (q = head; q->next; q = q->next)
		;
	q->next = (struct L *)malloc(sizeof(struct L));
	q = q->next;
	q->v = value;
	q->next = NULL;
}
