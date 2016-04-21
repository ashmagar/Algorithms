#ifndef KNAPSACK_H_
#define KNAPSACK_H_

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

struct item
{
        int id;
        int weight;
        int profit;
};

int capacity;
struct item* createKnapsack(int n);
void printItem(struct item it);
void printKnapsack(struct item *knapsack, int n);
struct item* deepCopy(struct item *knapsack,int n);
#endif
