#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#include "knapsack.h"
#include "bruteforce.h"
#include "greedy.h"
#include "backtracking.h"

int main()
{
	srand(time(NULL));
	int n = (rand() % (8 + 1- 4))+ 4;
	//int n = 3;
	printf("n = %d",n);
	struct item *knapsack = createKnapsack(n);	
	printf("\n\n ************************* KNAPSACK ************************* \n\n");
	printf("Capacity = %d\n",capacity);
	printKnapsack(knapsack,n);

	printf("\n\n ************************* BRUTEFORCE ************************* \n\n");
	bruteForce(knapsack,n);
	printf("\n\n *************************** GREEDY *************************** \n\n");
	greedy(knapsack,n);
	printf("\n\n *************************** BACKTRACKING ************************* \n\n");
	backtracking(knapsack,n);	

return 0;
}
