#ifndef BACKTRACKING_H_
#define BACKTRACKING_H_

#include "knapsack.h"

int maxprofit;
//int include[200];
//int bestest[200];
//int p[200];
//int w[200];

int *include;
int *bestest;
int *p;
int *w;
int num;

struct item* sortKnapsack(struct item *knapsack,int n);
float KWF(int ii,int weightt,int profitt,int n);
int Promising(int ii,int weightt,int profitt,int n);
void Knapsack(int ii,int profitt,int weightt,int n);
void backtracking(struct item *knapsack,int n);



#endif
