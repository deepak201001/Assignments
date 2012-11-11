#include<stdio.h>
#include<stdlib.h>

struct node{
int index;
struct node *next;
};

struct node **p, **q;

void create_head_pointers(int n)
{
	int i;
	p = (struct node **) malloc (n * sizeof(struct node *));
	q = (struct node **) malloc (n * sizeof(struct node *));
	
	for(i=0;i<n;i++)
	{
		p[i]=NULL;
		q[i]=NULL;
	}

}

void edge(int a, int b)
{
	struct node *temp;
	temp = (struct node *) malloc (sizeof(struct node));

	if(p[a]==NULL)
	{
		
		p[a]=temp;
	}
}

int main()
{
	int n,m;
	int i;

	scanf("%d %d",&n,&m);
	create_head_pointers(n);

	for(i=0;i<n;i++)
	if(p[i]==NULL)
	{
		printf("%d OK\n",i);
	}

	return 0;
}
