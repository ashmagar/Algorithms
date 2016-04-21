#ifndef BRUTEFORCE_H_
#define BRUTEFORCE_H_

#include "knapsack.h"
#include<math.h>

struct brutef
{
	struct item it[10];
	int tot_prof;
	int tot_wt;
};

void bruteForce(struct item *knapsack,int n);

#endif

