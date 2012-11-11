#include<stdio.h>
#include<stdlib.h>

struct node{
int index;
struct node *next;
};

struct node **p, **q;
int *visited;
int *high_pt;
int *parent;
int *AP;
int *DFN;
int dfn;
int check=0;
int k,n;

void create_head_pointers(int n)
{
	int i;
	p = (struct node **) malloc (n * sizeof(struct node *));
	q = (struct node **) malloc (n * sizeof(struct node *));
	
	for(i=0; i<n; i++)
	{
		p[i] = NULL;
		q[i] = NULL;
	}

}

void edge(int a, int b)
{
	struct node *temp;
	temp = (struct node *) malloc (sizeof(struct node));

	temp->index = b;
	temp->next = NULL;

	if(q[a] == NULL)
	{
		p[a] = temp;
		q[a]=temp;
	}
	else
	{
		q[a] -> next = temp;
		q[a] = temp;
	}
}


int min(int a, int b)
{
	if(a<b)
	return a;
	else
	return b;
}

void dfs(int i)
{

	visited[i] = 1;
	DFN[i] = dfn++;
	high_pt[i] = n+1;
	
	struct node *temp;
	temp = p[i];

	if(parent[i] == k)
	{
		printf("%d,%d\n",i,k);
		check++;
	}
 	
	int w;
	while(temp != NULL)
	{
		w = temp->index;

		if(visited[ temp -> index ] == 0)
		{
			parent[w]=i;
			dfs(w);	
			high_pt[i] = min(high_pt[i], high_pt[w]);
			if(high_pt[w] >= DFN[i])
				AP[i] = 1;

		}
		else if(parent[i] != w)
			high_pt[i] = min(DFN[w],high_pt[i]);


		temp = temp -> next;
	}
}

void printdfs(int i)
{
	visited[i] = 1;
	printf("%d,",i);
	struct node *temp;
	temp = p[i];

	while(temp != NULL)
	{
		if(visited[ temp -> index ] == 0)
		{
			printdfs(temp -> index);      
		}
		temp = temp -> next;
	}

}



void dfs_traversal(int n)
{
	int i, count=0;
	dfn = 0;	

	for(i=0; i<n; i++)
	{
		if(visited[i] == 0)
		{
			k=i;
			check = 0;
			parent[i]=-1;
			dfs(i);			
			count++;
			printf("check is %d\n",check);
			if(check<=1)
			AP[i] = 0;
		}
	}


	printf("There are %d components of the graph. These are\n",count);

	for(i=0; i<n ;i++)
		visited[i] = 0;

	for(i=0 ; i<n ; i++)
	{
		if(visited[i] == 0)
		{
			printf("{");
			printdfs(i);
			printf("\b} , ");
		}
	}
	printf("\b\b\b\n");

	int apoints=0;
	
	printf("The aritculation points are :");
	for(i=0; i<n ;i++)
	{
		if(AP[i] == 1)
		printf("%d,",i);
	}

	printf("\b\n");
}

int main()
{
	int m;
	int i;
	int a,b;
	struct node *temp;

	scanf("%d %d",&n,&m);
	create_head_pointers(n);

	visited = (int *) malloc (n * sizeof(int));
	AP = (int *) malloc (n * sizeof(int));
	DFN = (int *) malloc (n * sizeof(int));
	high_pt = (int *) malloc (n * sizeof(int));
	parent = (int *) malloc (n * sizeof(int));


	for(i=0; i<n; i++)
	{
		visited[i]=0;
		AP[i]=0;
	}

	for(i=0; i<m; i++)
	{
		scanf("%d%d",&a,&b);
		edge(a,b);
		edge(b,a);
	}

	dfs_traversal(n);
	return 0;
}
