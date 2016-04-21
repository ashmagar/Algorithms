/*
Program to implement
1.Kruskal's Algorithm
2.Dijkstra's Algorithm
3.Floyd's Algorithm

by,
Ashish Magar
amagar1@binghamton.edu
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//struct for storing edge for kruskal
struct edge{
	int weight;
	int u;
	int v;
};

//struct for storing vertices (in heap or distance matrix) for dijkstra
struct vertex
{
	int d;
	int lable;
	int visited;
};

//Function Declaration
void generateMatrix(int **,int);
void printMatrix(int **, int);

//Kruskals
struct edge* generateEdges(int **adj,int n);
void kruskal(int **adj,int n);
void union3(int repx, int repy,int *set,int *height);
int find3(int,int*,int*);
void sortEdge(struct edge*, int );

//Dijkstras
int hsz = 0;
void dijkstra(int **adj, int n);
void createHeap(struct vertex *heap, struct vertex *dist,int n);
void insertHeap(struct vertex *heap, struct vertex v,int pos);
struct vertex deleteHeap(struct vertex *heap);
void heapify(struct vertex *heap,int heapSize,int pos);

//Floyds
void path(int i,int j,int **seq);
void floyd(int **d,int **seq,int size);
int** allocateMatrix(int sz);

int main()
{
	int n;
	int i,j;

	srand(time(NULL));
	n = rand() % 5 + 6;
	printf("n is %d\n",n);
	int **adj = malloc(sizeof(int*) * n);
	for(i=0;i<n;i++)
	{
		adj[i] = malloc(sizeof(int) * n);
	}
	generateMatrix(adj,n);
	printf("matrix is\n");
	printMatrix(adj,n);

	//Kruskal's Algorithm
	printf("\n\nKruskal's Algorithm:\n");
	kruskal(adj,n);

	//Disjkstra's Algorithm
	printf("\n\nDijkstra's Algorithm:\n");
	dijkstra(adj,n);

	//Floyds Algorithm
	//allocate space for d matrix and sequence matrix
	printf("\n\nFloyd's Algorithm:\n");
	int **seq = allocateMatrix(n);
	int **d = allocateMatrix(n);
	for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	{
		d[i][j] = adj[i][j];
		seq[i][j] = 0;
	}
	//function call
	floyd(d,seq,n);
	//print result
	printf("\n\n d:\n");
	printMatrix(d,n);
	printf("\n seq\n");
	printMatrix(seq,n);
	return 0;
}

void printMatrix(int **adj,int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++){
			printf("%d ",adj[i][j]);
		}
		printf("\n");
	}	
}

void generateMatrix(int **adj, int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=i;j<n;j++)
		{
			if(i==j)
			{
				adj[i][j]=0;
			}
			else
			{
				adj[i][j] = rand() % 10 + 1;
				adj[j][i] = adj[i][j];
			}	
		}
	}
}

/***********************************************************KRUSKAL'S****************************************************************/
//generate edges
struct edge* generateEdges(int **adj,int n)
{
	int noOfEdges = (n*n-n)/2;
	printf("%d no of edges\n",noOfEdges);
	struct edge *edgeArray = malloc(sizeof(struct edge) * noOfEdges);
	//struct edge edgeArray[noOfEdges];
	
	int i,j;
	int k = 0;
        for (i = 0; i < n; i++)
        {
                for (j = 0; j < n; j++)
		{
			if(i<j)
			{
				edgeArray[k].weight = adj[i][j];
				edgeArray[k].u = i;
				edgeArray[k].v = j;
				k++;
			}
                }
        }
	return edgeArray;
}

//kruskals algorithm
void kruskal(int **adj,int n)
{
        int i;
	int noOfEdges = (n*n-n)/2;
	struct edge *edgeArray = generateEdges(adj,n);
        sortEdge(edgeArray, noOfEdges); 
        int set[n],height[n];
        for (i = 0; i < n; i++){
                set[i] = i;
                height[i] = 0;
        }
	struct edge e;
	int ucomp,vcomp;
	struct edge *tree = malloc(sizeof(struct edge) *noOfEdges);
	int treeCount=0;
	for(i=0;i<noOfEdges;i++)
	{
		e = edgeArray[i];
		ucomp = find3(e.u,set,height);
		vcomp = find3(e.v,set,height);
		if(ucomp!=vcomp)
		{
			tree[treeCount++] = e;
			union3(ucomp,vcomp,set,height);
		}
	}
	int mst=0;
	printf("Tree is :\n");
	for(i=0;i<treeCount;i++)
	{
		printf("%d -> %d : %d\n",tree[i].u+1,tree[i].v+1,tree[i].weight);
		mst = mst + tree[i].weight;
	}	
	printf("minimum weight = %d\n",mst);
}
 
//union3 function
void union3(int repx, int repy,int *set,int *height)
{ 
        if (height[repx] == height[repy])
        {
                height[repx]++;
                set[repy] = repx;  //y's tree points to x's tree
        }
        else{
                if (height[repx] > height[repy])
	                set[repy] = repx;  //y's tree points to x's tree
                else
                        set[repx] = repy;  //x's tree points y's tree
        }
}
 
//find3 function
int find3(int x,int *set,int *height)
{
        int parent;
        //find root of tree with x
        int root = x;
        while (root != set[root])
                root = set[root];
 
        //compress path from x to root
        int node = x;
        while (node != root){
                parent = set[node];
                set[node] = root; // node points to root
                node = parent;
		height[x]++;
        }
        return root;
}
 
//sorting edge array
void sortEdge(struct edge *edgeArray, int noOfEdges)
{
	int i, j;
	struct edge temp;
	for (i = 0; i < noOfEdges; i++){
                for (j = 0; j < noOfEdges; j++){
                        if (edgeArray[i].weight < edgeArray[j].weight)
                        {
				temp = edgeArray[i];
				edgeArray[i] = edgeArray[j];
				edgeArray[j] = temp;
                        }
                }
        }

}

/***********************************************************DIJKSTRA'S****************************************************************/
//create heap data structure
void createHeap(struct vertex *heap, struct vertex *dist,int n)
{
	int i;
	int heapSize=0;
	for(i=0;i<n;i++)
	{
		if(dist[i].visited == 0)
		{
			insertHeap(heap,dist[i],heapSize);
			heapSize++;
		}
	}
	hsz = heapSize;
}
//insert into heap
void insertHeap(struct vertex *heap, struct vertex v,int pos)
{
        heap[pos] = v;
        while (pos > 0){
                if (heap[pos].d < heap[(pos - 1) / 2].d){
                        struct vertex temp = heap[pos];
                        heap[pos] = heap[(pos - 1) / 2];
                        heap[(pos - 1) / 2] = temp;
                }
                pos = (pos - 1) / 2;
        }
}
//delete from heap
struct vertex deleteHeap(struct vertex *heap)
{
        struct vertex returnVal = heap[0];
        hsz--;
        heap[0] = heap[hsz];
        //hsz--;
        if (hsz > 0)
                heapify(heap, hsz,0);
        return returnVal;
}
//heapify
void heapify(struct vertex *heap,int heapSize,int pos)
{
        int leftpos, rightpos, smaller;
	//int larger;
        leftpos = (2 * pos) + 1;
        rightpos = (2 * pos) + 2;
 
        if (rightpos >= heapSize){
                if (leftpos >= heapSize){ 
                        return;
                }
                smaller = leftpos;
                //larger = 999;
        }
        else{
                if (heap[rightpos].d > heap[leftpos].d){
                        //larger = rightpos;
                        smaller = leftpos;
                }
                else{
                        //larger = leftpos;
                        smaller = rightpos;
                }
        }
        if (heap[pos].d > heap[smaller].d){
                struct vertex temp = heap[smaller];
                heap[smaller] = heap[pos];
                heap[pos] = temp;
 
                heapify(heap, heapSize, smaller);
        }
}

//dijkstra
void dijkstra(int **adj, int n)
{
	//int dist[n];
	struct vertex dist[n];
	int i,j;
	for(i=0;i<n;i++)
	{
		dist[i].lable = i;		
		if(i==0){
			 dist[i].d = 0;
		}
		else {
			dist[i].d = 99;
		}
		dist[i].visited = 0;
	}

	struct vertex heap[n];
	int vis = n;
	struct vertex near;
	i=0;
	while(vis != 0)
	{
		createHeap(heap,dist,n);
		near = deleteHeap(heap);
		near.visited = 1;
		vis--;
		for(j=0;j<n;j++)
		{	
			if(dist[j].d > dist[near.lable].d + adj[near.lable][j])
			{
				dist[j].d = dist[near.lable].d + adj[near.lable][j];
			}
		}
		i++;
	}

	//printf("Dijkstra: \n");
	for(i=0;i<n;i++)
	{
		printf("dist of %d - %d\n",dist[i].lable,dist[i].d);
	}
}

/*************************************************************FLOYD'S***********************************************************************/
//allocate function
int** allocateMatrix(int sz)
{
	int i,j;
	int **temp;
	temp = malloc(sizeof(int*) * sz);
	for(i = 0; i < sz; i++)
	{
		temp[i] = malloc(sizeof(int) * sz);
	}
	for(i=0;i<sz;i++)
		for(j=0;j<sz;j++)
			temp[i][j] = 0;
	return temp;
}

//prints path
void path(int i,int j,int **seq)
{
	if(seq[i][j] !=0)
	{
		path(i,(seq[i][j]-1),seq);	//recursion
		printf("->%d",seq[i][j]);
		path((seq[i][j]-1),j,seq);	//recursion
	}
}

//floyds algorithm
void floyd(int **d,int **seq,int size)
{
	//printf("inside floyd");
	int k;
	int i,j;
	for(k=0;k<size;k++)
	{
		for(i=0;i<size;i++)
		for(j=0;j<size;j++)
		{
			if(d[i][j] > (d[i][k]+d[k][j]))
			{
				d[i][j] = d[i][k] + d[k][j];
				seq[i][j] = k+1;
			}
		}
	}
	//print path
	for(i=0;i<size;i++)
	for(j=0;j<size;j++)
	{
		printf("\n Path %d to %d : ",i+1,j+1);
		if(d[i][j] < 500 && i != j)
		{
			printf("%d",i+1);
			path(i,j,seq);
			printf("->%d ",j+1);
		}
	}
}

/******************************************************************END OF PROGRAM********************************************************************/
