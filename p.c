#include<stdio.h>	// include header files
#include<stdlib.h>

struct node{		// structure having index
int index;
struct node *next;
};

struct node **p, **q;	// global variables 
int *visited;
int *high_pt;
int *parent;
int *AP;
int *DFN;
int *bridge;
int dfn;
int check=0;
int k,n;

void create_head_pointers(int n)	// fuction creates adjacency list
{
	int i;
	p = (struct node **) malloc (n * sizeof(struct node *));
	q = (struct node **) malloc (n * sizeof(struct node *));
	
	for(i=0; i<n; i++)		// initialising all neighbours to null
	{
		p[i] = NULL;
		q[i] = NULL;
	}

}

void edge(int a, int b)			// fuction to create neighbour b in list of a 
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


int min(int a, int b)				// minimum of a & b
{
	if(a<b)
	return a;
	else
	return b;
}

void dfs(int i)					// fuction for dfs traversal
{						// calculates articulation points and bridges

	visited[i] = 1;
	DFN[i] = dfn++;
	high_pt[i] = n+1;
	
	struct node *temp;
	temp = p[i];

	if(parent[i] == k)
		check++;
	
 	
	int w;
	while(temp != NULL)					// for each neighbour of vertex i
	{
		w = temp->index;

		if(visited[w] == 0)
		{
			parent[w]=i;
			dfs(w);	
			high_pt[i] = min(high_pt[i], high_pt[w]);
			if(high_pt[w] >= DFN[i])			// calculate articulation point
				AP[i] = 1;

			if(parent[w] != -1) 				// calculate bridges
			{
				if((high_pt[w] == n+1) || (high_pt[i] >= DFN[w]))
				{	
					bridge[w]=1;
				}
			}


		}
		if(parent[i] != w)
			high_pt[i] = min(DFN[w],high_pt[i]);

		temp = temp -> next;					//move to next neighbour
	}
}

void printdfs(int i)	// dfs to print the components
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



void dfs_traversal(int n)	// dfs traversal contains calls to dfs and printdfs
{				// also prints the main statements except components
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
			if(check<=1)
				AP[i] = 0;
		}
	}


	printf("\nThere are %d components of the graph. These are\n",count);	

	for(i=0; i<n ;i++)
		visited[i] = 0;

	for(i=0 ; i<n ; i++)
	{
		if(visited[i] == 0)
		{
			printf("{");
			printdfs(i);			// print components
			printf("\b} , ");
		}
	}
	printf("\b\b\b\n");

	int apoints=0;

	printf("The aritculation points are :");
	for(i=0; i<n ;i++)
	{
		if(AP[i] == 1)
			printf("%d,",i);		// print articulation points
	}

	printf("\b\n");
	printf("The Bridges are: ");

	for(i=0; i<n; i++)
	{
		if(bridge[i] == 1)
			printf("{%d,%d}, ",i,parent[i]); // print bridges
	}
	printf("\b\b\b\n");
}

int main()			//main function
{
	int m;
	int i;
	int a,b;
	struct node *temp;

	scanf("%d %d",&n,&m);	// scan n& m
	create_head_pointers(n); // create neighbour list

	visited = (int *) malloc (n * sizeof(int));	//assign memory to various arrays
	AP = (int *) malloc (n * sizeof(int));
	DFN = (int *) malloc (n * sizeof(int));
	high_pt = (int *) malloc (n * sizeof(int));
	parent = (int *) malloc (n * sizeof(int));
	bridge = (int *) malloc (n * sizeof(int));

	for(i=0; i<n; i++)		// initialise the arrays
	{
		visited[i]=0;
		AP[i]=0;
		bridge[i]=0;
	}

	for(i=0; i<m; i++)		// scan the edges
	{
		scanf("%d%d",&a,&b);
		edge(a,b);
		edge(b,a);
	}

	dfs_traversal(n);		// print all the required data
	return 0;
}
