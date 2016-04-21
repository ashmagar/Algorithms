#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
//hole indices
int hol_i;
int hol_j;

//index to traverse unique tromino id
static int m = 0;
//array of unique tromino ids
int *tid;
//function declaration 
void tromino_tiling(int **mat,int **trom,int size,int i,int j,int chi,int chj);

//function to allocate matrix
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

//function to generate random matrix
int** generateMatrix(int inputSize)
{
	int i,j;
	int limit = 10;
	int** matrix = allocateMatrix(inputSize);

	for(i = 0; i < inputSize; i++)
	{
		for(j = 0; j < inputSize; j++)
		{
			matrix[i][j] = (rand() % limit + 1);
		}
	}
	return matrix;
}

//function to print matrix
void printMatrix(int **matrix, int inputSize)
{
	//print generated matrix
	int i,j;
	for(i = 0; i < inputSize; i++)
	{
		for(j = 0; j < inputSize; j++)
		{
			if(matrix[i][j]==-1) printf("  X");
			else
			printf("%3d",matrix[i][j]);
		}
	printf("\n");
	}
}

int main(int argc,char *argv[])
{
	if(argc != 2)
	{
		printf("Format to run : ./tro <integer> \n");
		return 0;
	}

	srand(time(NULL));
	int kin= atoi(argv[1]);
	if(kin > 6 || kin < 0 )
	{
		printf("input should be between 0 to 6\n");
		return 0;
	}
	int size = pow(2,kin);
	int **inputMatrix = generateMatrix(size);
	printMatrix(inputMatrix,size);

	//generate id array
	int num_id = ( size*size-1) / 3;
	tid = malloc(sizeof(int) * num_id);
	int i;
	for(i=0;i<num_id;i++)
	{
		tid[i] = i+1;
		//printf("%d",tid[i]);
	}
	printf("\n");

	//random hole
	hol_i = rand()%size;
	hol_j = rand()%size;
	printf("hole is matrix[%d][%d] \n\n",hol_i,hol_j);
	inputMatrix[hol_i][hol_j] = -1;

	//tromino matrix
	int **tromino_matrix = allocateMatrix(size);
	tromino_matrix[hol_i][hol_j] = -1;
	tromino_tiling(inputMatrix,tromino_matrix,size,0,0,hol_i,hol_j);
	printMatrix(tromino_matrix,size);
	return 0;


}

void tromino_tiling(int **mat,int **trom,int size,int i,int j,int current_hol_i,int current_hol_j)
{

	int itemp=i,jtemp=j;
	if(size==2)		//base condition
	{
		int k=0;int k2=0;
		while(k<size)
		{
			k2=0; jtemp=j;
			while(k2<size)
			{
				if(mat[itemp][jtemp]!=-1 || (itemp!=hol_i && jtemp!=hol_j))
				{
					trom[itemp][jtemp] = tid[m];
				}
				jtemp++;
				k2++;
			}
			itemp++;  k++;
		}
		m++;

/*			for(itemp=i;itemp<size;itemp++)
			for(jtemp=j;jtemp<size;jtemp++)
		{
			if(mat[itemp][jtemp]!=-1 || (itemp!=hol_i && jtemp!=hol_j))
			{
				trom[itemp][jtemp] = tid[m];
			}
		}
		m++;
*/

		return;
	}

	//check hole is in which part, and create virtual holes
	int part;
	int vhole1_i,vhole1_j;
	int vhole2_i,vhole2_j;
	int vhole3_i,vhole3_j;
//	if(current_hol_i < size/2)
	if(current_hol_i < (size/2+i))
	{
		if(current_hol_j< (size/2+j)) part = 1;
		else part = 2;
	}
	else
	{
		if(current_hol_j< (size/2+j)) part = 3;
		else part = 4;
	}

	switch(part)
	{
		case 1:
//			vhole1_i = (size/2-1); vhole1_j = size/2;
			vhole1_i = (size/2+i-1); vhole1_j = size/2+j;
//			mat[(size/2-1)][(size/2)] = -1;
			mat[vhole1_i][vhole1_j] = -1;

//			vhole2_i = (size/2); vhole2_j = size/2-1;
			vhole2_i = (size/2+i); vhole2_j = size/2+j-1;
			mat[vhole2_i][vhole2_j] = -1;
//			mat[(size/2)][(size/2)-1] = -1;

//			vhole3_i = (size/2); vhole3_j = size/2;
//			mat[(size/2)][(size/2)] = -1;
			vhole3_i = (size/2+i); vhole3_j = size/2+j;
			mat[vhole3_i][vhole3_j] = -1;


		tromino_tiling(mat,trom,size/2,i,j,current_hol_i,current_hol_j);	//part1
		tromino_tiling(mat,trom,size/2,i,(j+size/2),vhole1_i,vhole1_j);		//part2
		tromino_tiling(mat,trom,size/2,(i+size/2),j,vhole2_i,vhole2_j);		//part3
		tromino_tiling(mat,trom,size/2,(i+size/2),(j+size/2),vhole3_i,vhole3_j);//part4

			break;
		case 2:

//			vhole1_i = (size/2-1); vhole1_j = size/2-1;
//			mat[(size/2-1)][(size/2)-1] = -1;
			vhole1_i = (size/2+i-1); vhole1_j = size/2+j-1;
			mat[vhole1_i][vhole1_j] = -1;

//			vhole2_i = (size/2); vhole2_j = size/2-1;
//			mat[(size/2)][(size/2)-1] = -1;
			vhole2_i = (size/2+i); vhole2_j = size/2+j-1;
			mat[vhole2_i][vhole2_j] = -1;

//			vhole3_i = (size/2); vhole3_j = size/2;
//			mat[(size/2)][(size/2)] = -1;
			vhole3_i = (size/2+i); vhole3_j = size/2+j;
			mat[vhole3_i][vhole3_j] = -1;

		tromino_tiling(mat,trom,size/2,i,j,vhole1_i,vhole1_j);			//part1
		tromino_tiling(mat,trom,size/2,i,(j+size/2),current_hol_i,current_hol_j);//part2
		tromino_tiling(mat,trom,size/2,(i+size/2),j,vhole2_i,vhole2_j);		//part3
		tromino_tiling(mat,trom,size/2,(i+size/2),(j+size/2),vhole3_i,vhole3_j);//part4

			break;

		case 3:
//			vhole1_i = (size/2-1); vhole1_j = size/2-1;
//			mat[(size/2-1)][(size/2)-1] = -1;
			vhole1_i = (size/2+i-1); vhole1_j = size/2+j-1;
			mat[vhole1_i][vhole1_j] = -1;

//			vhole2_i = (size/2-1); vhole2_j = size/2;
//			mat[(size/2-1)][(size/2)] = -1;
			vhole2_i = (size/2+i-1); vhole2_j = size/2+j;
			mat[vhole2_i][vhole2_j] = -1;

//			vhole3_i = (size/2); vhole3_j = size/2;
//			mat[(size/2)][(size/2)] = -1;
			vhole3_i = (size/2+i); vhole3_j = size/2+j;
			mat[vhole3_i][vhole3_j] = -1;

		tromino_tiling(mat,trom,size/2,i,j,vhole1_i,vhole1_j);			//part1
		tromino_tiling(mat,trom,size/2,i,(j+size/2),vhole2_i,vhole2_j);		//part2
		tromino_tiling(mat,trom,size/2,(i+size/2),j,current_hol_i,current_hol_j);//part3
		tromino_tiling(mat,trom,size/2,(i+size/2),(j+size/2),vhole3_i,vhole3_j);//part4

			break;
		case 4:
//			vhole1_i = (size/2-1); vhole1_j = size/2-1;
//			mat[(size/2-1)][(size/2)-1] = -1;
			vhole1_i = (size/2+i-1); vhole1_j = size/2+j-1;
			mat[vhole1_i][vhole1_j] = -1;

//			vhole2_i = (size/2-1); vhole2_j = size/2;
//			mat[(size/2-1)][(size/2)] = -1;
			vhole2_i = (size/2+i-1); vhole2_j = size/2+j;
			mat[vhole2_i][vhole2_j] = -1;

//			vhole3_i = (size/2); vhole3_j = size/2-1;
//			mat[(size/2)][(size/2)-1] = -1;
			vhole3_i = (size/2+i); vhole3_j = size/2+j-1;
			mat[vhole3_i][vhole3_j] = -1;

		tromino_tiling(mat,trom,size/2,i,j,vhole1_i,vhole1_j);			//part1
		tromino_tiling(mat,trom,size/2,i,(j+size/2),vhole2_i,vhole2_j);		//part2
		tromino_tiling(mat,trom,size/2,(i+size/2),j,vhole3_i,vhole3_j);		//part3
		tromino_tiling(mat,trom,size/2,(i+size/2),(j+size/2),current_hol_i,current_hol_j);//part4
			break;

	}
/*
	//recursion
	tromino_tiling(mat,trom,size/2,i,j,vhole1_i,vhole_j);
	tromino_tiling(mat,trom,size/2,i,(j+size/2),vhole_i,vhole_j);
	tromino_tiling(mat,trom,size/2,(i+size/2),j,vhole_i,vhole_j);
	tromino_tiling(mat,trom,size/2,(i+size/2),(j+size/2),vhole_i,vhole_j);
*/
	//fill virtual holes
	trom[vhole1_i][vhole1_j] = tid[m];
	trom[vhole2_i][vhole2_j] = tid[m];
	trom[vhole3_i][vhole3_j] = tid[m];
	m++;
}
