#include<stdio.h>
#include<stdlib.h>

//allocates size to matrix
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

//prints matrix
void printMatrix(int **matrix, int inputSize)
{
	int i,j;
	for(i = 0; i < inputSize; i++)
	{
		for(j = 0; j < inputSize; j++)
		{
			printf("%d ",matrix[i][j]);
		}
	printf("\n");
	}
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

int main(int argc,char *argv[])
{

	int i;
	int j;
	int size;

	fscanf(stdin,"%d",&size);

	int **inputMatrix = allocateMatrix(size);
	for(i=0;i<size;i++)
	for(j=0;j<size;j++)
	{
		fscanf(stdin,"%d",&inputMatrix[i][j]);
	}

	printf("\ninput: size : %d \n",size);
	printMatrix(inputMatrix,size);

	//allocate space for d matrix and sequence matrix
	int **seq = allocateMatrix(size);
	int **d = allocateMatrix(size);
	for(i=0;i<size;i++)
	for(j=0;j<size;j++)
	{
		d[i][j] = inputMatrix[i][j];
		seq[i][j] = 0;
	}

	//function call
	floyd(d,seq,size);

	//print result
	printf("\n\n d:\n");
	printMatrix(d,size);
	printf("\n seq\n");
	printMatrix(seq,size);
	return 0;
}


