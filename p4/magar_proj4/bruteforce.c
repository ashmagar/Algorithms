#include "bruteforce.h"
#include<math.h>

void bruteForce(struct item *knapsack,int n)
{
	//printf("\n\n ********************* BRUTE FORCE ****************************** \n\n");

	int powSetSize = pow(2,n);
	int i,j,counter;
	//printf("\npowsetsize = %d\n",powSetSize);	

	//initialize powerset
	struct brutef *bf = malloc(sizeof(struct brutef) * powSetSize);
	for(j=0;j<powSetSize;j++)
	{
		for(i=0;i<10;i++)
		{
			bf[j].it[i].id = -1;
			bf[j].it[i].weight = 0;
			bf[j].it[i].profit = 0;
		}
		bf[j].tot_prof = 0;
		bf[j].tot_wt = 0;
	}

	//create power set	ref : geeksforgeeks.com
	/* Run from counter 000..0 to 111..1 */
		int a=0,b=0;
	    for(counter = 0; counter < powSetSize; counter++)
	    {
		b=0;
	       for(j = 0; j < n; j++)
	       {
	          /* Check if jth bit in the counter is set
	             If set then pront jth element from set */
	          if(counter & (1<<j)){
			bf[a].it[b] = knapsack[j];
			bf[a].tot_prof += knapsack[j].profit;
			bf[a].tot_wt += knapsack[j].weight;	
			b++;	
		  }
	       }
		a++;
	    }


	//print powerset only if n<=3
	if(n<=3)
	for(i=0;i<powSetSize;i++)
	{
		j=0;
		while(bf[i].it[j].id!= -1)
		{
			printItem(bf[i].it[j]);
			j++;
		}
		if(bf[i].tot_wt!=0)
		{
			printf("Total profit = %d\n",bf[i].tot_prof);
			printf("Total weight = %d\n",bf[i].tot_wt);
		}
		printf("\n");
	}

	//calculate and print maximum profit
	int max_profit = 0;
	int max_profit_index = 0;
	for(i=0;i<powSetSize;i++)
	{
		if(bf[i].tot_wt <= capacity)
		{
			if(bf[i].tot_prof > max_profit)
			{
				max_profit_index = i;
				max_profit = bf[i].tot_prof;
			}
		}
	}
	printf("MAX PROFIT : \n\n");
	j=0;;
	while(bf[max_profit_index].it[j].id!= -1)
	{
		printItem(bf[max_profit_index].it[j]);
		j++;
	}
	printf("Total profit = %d\n",bf[max_profit_index].tot_prof);
	printf("Total weight = %d\n\n",bf[max_profit_index].tot_wt);
}

