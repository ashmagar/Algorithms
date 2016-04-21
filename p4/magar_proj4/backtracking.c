#include "backtracking.h"

struct item* sortKnapsack(struct item *knapsack,int n)
{
	struct item* sortedKnapsack = deepCopy(knapsack,n);

	 //sort knapsack on profit/weight
        int i,j;
        struct item temp;
        for(i=0;i<n;i++)
        {
                for(j=i+1;j<n;j++)
                {
			if( (float)((float)sortedKnapsack[i].profit/(float)sortedKnapsack[i].weight) <= (float)((float)sortedKnapsack[j].profit/(float)sortedKnapsack[j].weight) )
                        {
                                temp = sortedKnapsack[i];
                                sortedKnapsack[i] = sortedKnapsack[j];
                                sortedKnapsack[j] = temp;
                        }
                }
        }

	//create 0th element with 0 values, add to knapsack, to use algorithm provied in slide
	struct item *newKnapsack = malloc(sizeof(struct item)*(n+1));
	for(i=0;i<n;i++)
	{
		newKnapsack[i+1] = sortedKnapsack[i];
	}
	newKnapsack[0].id = -1;
	newKnapsack[0].profit = 0;
	newKnapsack[0].weight = 0;

	//return new knapsack
	return newKnapsack;
}


float KWF(int ii,int weightt,int profitt,int n)
{
	float bound = (float)profitt;
	int j;
//	int x[n];
	for(j=ii;j<n;j++)
	{
		//never used
	//	x[j] = 0;
	}

	while(weightt < capacity && ii<=n)
	{
		if(weightt+w[ii] <= capacity)
		{
			//x[ii] = 1;
			weightt = weightt + w[ii];
			bound = bound + (float)p[ii];
		}
		else
		{
			float xii = ((float)capacity - (float)weightt)/(float)w[ii];
			bound = bound + ((float)p[ii] * xii);
			weightt = capacity;
		}
		ii++;
	}
	return bound;
}

int Promising(int ii,int weightt,int profitt,int n)
{
	if (weightt >= capacity) return 0;

	float bound = KWF(ii,weightt,profitt,n);
	return(bound>(float)maxprofit);
}

void Knapsack(int ii,int profitt,int weightt,int n)
{
	if(weightt <= capacity && profitt > maxprofit)
	{
		maxprofit = profitt;
		num = ii;
		//set bestest = include
		for(int k = 1;k<n;k++) bestest[k] = include[k];
	}
	if(Promising(ii,weightt,profitt,n))
	{
		include[ii+1] = 1;
		Knapsack(ii+1,profitt+p[ii+1],weightt+w[ii+1],n);
		include[ii+1] = 0;
		Knapsack(ii+1,profitt,weightt,n);
	}
}


void backtracking(struct item *knapsack,int n)
{
	struct item *newKnapsack = sortKnapsack(knapsack,n);
        //printf("\nSorted knapsack, MAX PROFIT/WEIGHT first, first element is dummy element\n");
        //printKnapsack(newKnapsack,n+1);

	int i;
	include = malloc(sizeof(int)*(n+1));
	bestest = malloc(sizeof(int)*(n+1));
	p = malloc(sizeof(int)*(n+1));
	w = malloc(sizeof(int)*(n+1));
	maxprofit = 0;
	num = 0;

	//initialize data structures with required values
	for(i=0;i<n+1;i++)
	{
		bestest[i] = include[i] = 0;
	}
	for(i=0;i<n+1;i++)
	{
		p[i] = newKnapsack[i].profit;
		w[i] = newKnapsack[i].weight;
	}

	//call knapsack function
	Knapsack(0,0,0,n+1);

	//print maximum profit and included items
	printf("\nMaximum Profit = %d\n",maxprofit);
	printf("Best Set Array: \t");
	for(i=1;i<=num;i++)
	{
		printf("%d \t ",bestest[i]);
	}
	printf("\n\nItems included \n");
	int tp=0, tw=0;
	for(i=0;i<=num;i++)
	{
		if(bestest[i] == 1)
		{
			printItem(newKnapsack[i]);
			tp+= newKnapsack[i].profit;
			tw+= newKnapsack[i].weight;
		}
	}
	printf("Total profit: %d\n",tp);
	printf("Total weight: %d\n",tw);
	printf("\n");
}


