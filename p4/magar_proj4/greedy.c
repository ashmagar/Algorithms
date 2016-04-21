#include "greedy.h"

void greedy1(struct item* knapsack, int n)
{
	struct item *sortKnapsack = deepCopy(knapsack,n);

	//sort knapsack on profit
	int i,j;
	struct item temp;
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(sortKnapsack[i].profit <= sortKnapsack[j].profit)
			{	
				temp = sortKnapsack[i];
				sortKnapsack[i] = sortKnapsack[j];
				sortKnapsack[j] = temp;
			}	
		}
	}
	//printf("************** GREEDY 1 ***************");
	//printf("\nSorted knapsack, MAX profit first\n");
	//printKnapsack(sortKnapsack,n);

	printf("\nGreedy1 Solution\n\n");
	int tot_prof = 0;
	int tot_wt = 0;
	i=0;
	for(i=0;i<n;i++)
	{
		tot_wt += sortKnapsack[i].weight;
		if(tot_wt>capacity) 
		{
			tot_wt -= sortKnapsack[i].weight;
			break;
		}
		tot_prof += sortKnapsack[i].profit;
		printItem(sortKnapsack[i]);
	}
	printf("Total profit = %d\n",tot_prof);
        printf("Total weight = %d\n\n",tot_wt);
}

void greedy2(struct item* knapsack, int n)
{
	struct item *sortKnapsack = deepCopy(knapsack,n);

	//sort knapsack on weight
	int i,j;
	struct item temp;
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(sortKnapsack[i].weight > sortKnapsack[j].weight)
			{	
				temp = sortKnapsack[i];
				sortKnapsack[i] = sortKnapsack[j];
				sortKnapsack[j] = temp;
			}	
		}
	}
	//printf("************** GREEDY 2 ***************");
	//printf("\nSorted knapsack, MIN weight first\n");
	//printKnapsack(sortKnapsack,n);

	printf("\nGreedy2 Solution\n\n");
	int tot_prof = 0;
	int tot_wt = 0;
	i=0;
	for(i=0;i<n;i++)
	{
		tot_wt += sortKnapsack[i].weight;
		if(tot_wt>capacity) 
		{
			tot_wt -= sortKnapsack[i].weight;
			break;
		}
		tot_prof += sortKnapsack[i].profit;
		printItem(sortKnapsack[i]);
	}
	printf("Total profit = %d\n",tot_prof);
        printf("Total weight = %d\n\n",tot_wt);
}

void greedy3(struct item* knapsack, int n)
{
	struct item *sortKnapsack = deepCopy(knapsack,n);

	//sort knapsack on weight
	int i,j;
	struct item temp;
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(sortKnapsack[i].weight <= sortKnapsack[j].weight)
			{	
				temp = sortKnapsack[i];
				sortKnapsack[i] = sortKnapsack[j];
				sortKnapsack[j] = temp;
			}	
		}
	}
	//printf("************** GREEDY 3 ***************");
	//printf("\nSorted knapsack, MAX weight first\n");
	//printKnapsack(sortKnapsack,n);

	printf("\nGreedy3 Solution\n\n");
	int tot_prof = 0;
	int tot_wt = 0;
	i=0;
	for(i=0;i<n;i++)
	{
		tot_wt += sortKnapsack[i].weight;
		if(tot_wt>capacity) 
		{
			tot_wt -= sortKnapsack[i].weight;
			break;
		}
		tot_prof += sortKnapsack[i].profit;
		printItem(sortKnapsack[i]);
	}
	printf("Total profit = %d\n",tot_prof);
        printf("Total weight = %d\n\n",tot_wt);
}

void greedy4(struct item* knapsack, int n)
{
	struct item *sortKnapsack = deepCopy(knapsack,n);

	//sort knapsack on weight
	int i,j;
	struct item temp;
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if( (float)(sortKnapsack[i].profit/sortKnapsack[i].weight) <= (float)(sortKnapsack[j].profit/sortKnapsack[j].weight) )
			{	
				temp = sortKnapsack[i];
				sortKnapsack[i] = sortKnapsack[j];
				sortKnapsack[j] = temp;
			}	
		}
	}
	//printf("************** GREEDY 4 ***************");
	//printf("\nSorted knapsack, MAX weight per profit first\n");
	//printKnapsack(sortKnapsack,n);

	printf("\nGreedy4 Solution\n\n");
	int tot_prof = 0;
	int tot_wt = 0;
	i=0;
	for(i=0;i<n;i++)
	{
		tot_wt += sortKnapsack[i].weight;
		if(tot_wt>capacity) 
		{
			tot_wt -= sortKnapsack[i].weight;
			break;
		}
		tot_prof += sortKnapsack[i].profit;
		printItem(sortKnapsack[i]);
	}
	printf("Total profit = %d\n",tot_prof);
        printf("Total weight = %d\n\n",tot_wt);
}


void greedy(struct item *knapsack,int n)
{
	greedy1(knapsack,n);
	greedy2(knapsack,n);
	greedy3(knapsack,n);
	greedy4(knapsack,n);
}

