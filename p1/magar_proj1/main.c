/*
CS575: Programming Project 1

by,
Ashish P Magar
(amagar1@binghamton.edu)

contains,
Sorting Algorithms,
1.Selection Sort
2.Randomized Quick Sort
3.Counting Sort
4.Merge Sort
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <string.h>


/*Function to swap two numbers in an array
	@param: array, index1, index2
*/
void swap(int *arr, int x,int y)
{
    int t = arr[x];
    arr[x] = arr[y];
    arr[y] = t;
}


static int globalSize = 0;			//Global variable of size, to print pattern (size of problem changes in merge and quick sort)
static int iteration = 40;			//To print pattern

void selectionSort(int *data,int size);

void randomizedQuickSort(int*,int,int);
int partition(int*,int,int);

void countingSort(int*,int);

void mergeSort(int*,int);
void merge(int *data,int *arr1,int *arr2,int a1end,int a2end);

void printPattern(int*,int);

void generateArray(int *inputArray,int limits,int inputSize);

//main
int main()
{
	int i=0;
	int inputSize = 0;
	int *inputArray = NULL;
	int inputRange = 0;
	int choice;

	srand(time(NULL));
	while(1)
	{
		printf("\n 1.Selection Sort \n 2.Randomized Quick Sort \n 3.Counting Sort \n 4.Merge Sort \n 5.Exit\n\n ");
		printf("\n Enter Choice : ");
			//choice menu
		scanf("%d",&choice);

		//set input size
		if(choice < 1 || choice > 5) { printf(" Enter valid choice (between 1-5)\n"); continue; }
		if(choice==5) return 0;
		printf(" Enter input size: ");
		scanf("%d",&inputSize);
		globalSize=inputSize;
		if(inputSize <= 0) { printf(" Enter valid size (non-zero)\n"); continue; }

		//set input range as per project requirement
		if(inputSize<=20) { inputRange = 15; }
		else if(choice == 3) { inputRange = 99; }
		else { inputRange = 999; }

		//allocate size for array, taken from user as input
		inputArray = malloc(inputSize* sizeof(int));

		//choices
		switch(choice)
		{
			case 1:	//Selection Sort
				generateArray(inputArray,inputRange,inputSize);
				selectionSort(inputArray,inputSize);
				break;
			case 2: //Randomized Quick Sort
				generateArray(inputArray,inputRange,inputSize);
				randomizedQuickSort(inputArray,0,(inputSize-1));
				break;
			case 3:	//Counting Sort
				generateArray(inputArray,inputRange,inputSize);
				countingSort(inputArray,inputSize);
				break;
			case 4: //Merge Sort
				generateArray(inputArray,inputRange,inputSize);
				mergeSort(inputArray,inputSize);
				break;

			default:
				printf("Enter correct choice\n");

		}

		//print sorted array
		printf("\nSorted array is\n");
		for(i=0;i<inputSize;i++)
		{
			printf("%d ",inputArray[i]);
		}
		printf("\n");
		free(inputArray);
	}
}


/*Function to generate array of random numbers
	@param: pointer to array, range for random numbers, input size
*/
void generateArray(int *inputArray,int limits,int inputSize)
{
	int i=0;

	for(i = 0; i < inputSize; i++)
	{
		inputArray[i] = (rand() % limits + 1);
	}

	//print generated array
	printf("\nOriginal array is\n");
	for(i=0;i<inputSize;i++)
	{
		printf("%d ",inputArray[i]);
	}
	printf("\n");

}

/*Selecton Sort
	@param: array,size
*/
void selectionSort(int *data,int size)
{
	int i,next,originalSpot;
	for(i = 0; i < size-1; ++i)
	{
		originalSpot = i;
		//select appropriate index for current element
		for(next = i + 1; next < size; ++next)
		{
			if(data[next] < data[originalSpot])
			{
				originalSpot = next;
			}
		}

		//swap current element with appropriate index
		if(originalSpot != i)
		{
			int tmp = data[i];
			data[i] = data[originalSpot];
			data[originalSpot] = tmp;
			//print pattern
			printPattern(data,size);
		}
	}
}


/*Randomized Quick Sort
	@param: Array, Start Index, End Index
*/
void randomizedQuickSort(int *data, int start, int end)
{
	if(start>=end)
	{
		return;
	}//base condition for recursion

	//partition the array about pivot index
	int pivIndex = partition(data,start,end);

	printPattern(data,globalSize);

	//recursion
	randomizedQuickSort(data,start,pivIndex-1);
	randomizedQuickSort(data,pivIndex+1,end);
}

/*Partition
	@param: Array, Start Index, End Index
*/
int partition(int *data,int start,int end)
{
	int i;
	int pivIndex = start;
	int randPivotIndex;

	//generate pivot index randomly
	double scaled = (double) rand() / RAND_MAX;
	randPivotIndex = (end - start +1)*scaled + start;

	//printf("%d is piv index\n",pivIndex);
	//swap the pivot with end and select pivot as last element, and apply same normal partition logic
	swap(data,randPivotIndex,end);
	int piv = data[end];

	//partitioning
	for(i=start;i<end;i++)
	{
		if(data[i]<piv)
		{
			swap(data,i,pivIndex);
			pivIndex++;
		}
	}
	swap(data,pivIndex,end);

	//return pivot index
	return pivIndex;
}


/*Selecton Sort
	@param: array,size
*/
void countingSort(int *data,int size)
{
	int countingArray[100];
	int i;

	printPattern(data,size);
	for(i=0;i<100;i++)
	{
		countingArray[i]=0;
	}

	for(i=0;i<size;i++)
	{
		countingArray[data[i]]++;
	}
	int j=0;
	for(i=0;i<100;i++)
	{
		while(countingArray[i]>0)
		{
			data[j++] = i;
			countingArray[i]--;
		}
	}

	printPattern(data,size);

}



/*Selecton Sort
	@param: array,size
*/
void mergeSort(int *data,int size)
{
	//base condition for recursion
	if(size<=1) return;

	//printing pattern
	int z=0;
	if(globalSize<=20)
	{
		iteration = iteration - 5;
		for(z=0;z<iteration;z++)
		{
			printf("#");
		}
		printf("\nInput at current level");
		printPattern(data,size);

	}

	int mid = size/2;
	int *arr1 = malloc( mid   * sizeof(int)   );		//left partition
	int *arr2 = malloc( (size-mid) * sizeof(int)   );	//right partition
	int i=0;
	int j=0;

	//copy data into left and right partition
	for(i=0;i<mid;i++)
	{
		arr1[j++] = data[i];
	}
	j=0;
	for(i=mid;i<size;i++)
	{
		arr2[j++] = data[i];
	}

	//printing pattern
	if(globalSize<=20)
	{
		printf("Divide\n");
		printf("Left:\n");
		printPattern(arr1,mid);
		printf("Right:\n");
		printPattern(arr2,(size-mid));
	}

	//recursion
	mergeSort(arr1,mid);
	mergeSort(arr2,(size-mid));

	//merge sorted partitions
	merge(data,arr1,arr2,mid,(size-mid));

	//printing pattern
	if(globalSize<=20)
	{
		printf("Merge\n");
		printPattern(data,size);
		for(z=0;z<iteration;z++)
		{
			printf("#");
		}
		printf("\n");
		iteration += 5;
	}

}

/*Function to merge
	@param: input array(to be formed merging two arrays,
		left sorted partition, right sorted partition,
		size of left partition, size of right partition
*/

void merge(int *data,int *arr1,int *arr2,int a1end,int a2end)
{
	int i=0,a1i,a2i;
	a1i=a2i=0;

	//merge 2 arrays int main array
	while(a1i<a1end && a2i<a2end)
	{
		if(arr1[a1i]<arr2[a2i])
		{
			data[i++] = arr1[a1i++];
		}

		else
		{
			data[i++] = arr2[a2i++];
		}
	}

	//add remaining elements
	while(a1i<a1end)
	{
			data[i++] = arr1[a1i++];
	}
	while(a2i < a2end)
	{
			data[i++] = arr2[a2i++];
	}

}


/*Print pattern
	@param: input data,size
*/

void printPattern(int *data, int size)
{
	if(size>20)
	{
		return;
	}
	int i=0;
	int j=0;
	printf("\n");
	for(i=0;i<size;i++)
	{
		j = data[i];
		while(j--)
		{
			printf("*");
		}
		printf("\n");
	}
}


/*********************************************************END OF PROGRAM*******************************************************/
