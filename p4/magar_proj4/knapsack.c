#include "knapsack.h"

struct item* createKnapsack(int n)
{
	struct item *knapsack = malloc(sizeof(struct item) * n);
	int totalWeight = 0;

	for(int i = 0 ; i < n; i++)
	{
		knapsack[i].id = i;
		knapsack[i].weight = (rand() % (20+1-5)) + 5;
		totalWeight = totalWeight + knapsack[i].weight;
		knapsack[i].profit = (rand() % (30+1-10)) + 10;
	}
	capacity = (totalWeight * 0.6);
	
/*	hardcode values for testing

	knapsack[0].weight = 17;
	knapsack[0].profit = 23;
	knapsack[1].weight = 20;
	knapsack[1].profit = 21;
	knapsack[2].weight = 19;
	knapsack[2].profit = 17;
	capacity = 33;
*/
	return knapsack;
}
void printItem(struct item it)
{
	printf("item-%d \t profit-%d \t weight-%d \t profit/weight- %.3f\n",it.id,it.profit,it.weight,(float)it.profit/(float)it.weight);
}

void printKnapsack(struct item *knapsack, int n)
{
	for(int i = 0 ; i < n; i++)
	{
		printItem(knapsack[i]);
	}
}

struct item* deepCopy(struct item *knapsack,int n)
{
        struct item *copyKnapsack = malloc(sizeof(struct item) * n);
	int i;
	for(i=0;i<n;i++)
	{
		copyKnapsack[i].id = knapsack[i].id;
		copyKnapsack[i].weight = knapsack[i].weight;
		copyKnapsack[i].profit = knapsack[i].profit;
	}
	return copyKnapsack;
}
