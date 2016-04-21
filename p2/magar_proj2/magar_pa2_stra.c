#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//function declarations
int** allocateMatrix(int);
int** generateMatrix(int);
void printMatrix(int**, int);

int **multiplyTrad(int**,int**,int);
void multiplyStra(int sz, int** mat1, int** mat2, int **res);

void free_m(int**,int);

void baseCondition(int **mat1,int **mat2,int **res);
int **subMatrix(int **m1,int **m2,int sz);
int **addMatrix(int **m1,int **m2,int sz);
void copyMatrix(int n,int **child_matrix, int **parent_matrix,int i,int j);
void composeMatrix(int sz,int **c1,int **c2,int **c3,int **c4,int **res);

//main
int main(int argc,char *argv[])
{

	//validations
	if(argc!=2)
	{
		printf("Format to run: ./srta <size of matrix> , should be power of 2\n");
		return 0;
	}
	int inputSize = atoi(argv[1]);
	if(inputSize<2)
	{
		printf("Enter size in nonzero power of 2\n");
		return 0;
	}
	float temp = (float)inputSize;
	while(temp != 1.0)
	{
		temp = temp/2;
		if(temp < 1.0)
		{
			printf("Enter size in power of 2\n");
			return 0;
		}
	}


	srand(time(NULL));
	int **matrix1 = generateMatrix(inputSize);
	int **matrix2 = generateMatrix(inputSize);

	printf("\nMatrix1 is\n");
	printMatrix(matrix1,inputSize);
	printf("\n");
	printf("\nMatrix2 is\n");
	printMatrix(matrix2,inputSize);

	int **resultTrad = multiplyTrad(matrix1,matrix2,inputSize);
	printf("\nMultiplacation by traditional method\n");
	printMatrix(resultTrad,inputSize);

	int **resultStra = allocateMatrix(inputSize);
	multiplyStra(inputSize,matrix1,matrix2,resultStra);
	printf("\nMultiplacation by Strassen's method\n");
	printMatrix(resultStra,inputSize);

	free_m(resultTrad,inputSize);
	free_m(resultStra,inputSize);
	return 0;
}

//allocate memory to matrix
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

//generate matric with random numbers
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

//print matrix
void printMatrix(int **matrix, int inputSize)
{
	//print generated matrix
	int i,j;
	for(i = 0; i < inputSize; i++)
	{
		for(j = 0; j < inputSize; j++)
		{
			printf("%d ",matrix[i][j]);
		}
	printf("\n");
	}
}

//multiplication with traditional method
int **multiplyTrad(int **m1,int **m2,int sz)
{
	int **result = allocateMatrix(sz);
	int i,j,k;

	for(i=0;i<sz;i++)
		for(j=0;j<sz;j++)
			for(k=0;k<sz;k++)
				result[i][j] += m1[i][k]* m2[k][j];

	return result;
}

//copy matrix function to create child matrices
void copyMatrix(int n,int **child_matrix, int **parent_matrix,int i,int j)
{
	int p,q;
	int i_temp = i;
	int j_temp;
	for(p=0;p<n;p++)
	{
		j_temp = j;
		for(q=0;q<n;q++)
		{
			child_matrix[p][q] = parent_matrix[i_temp][j_temp];
			j_temp++;
		}
		i_temp++;
	}
}

//addition of 2 matrices
int **addMatrix(int **m1,int **m2,int sz)
{
	int **addition = allocateMatrix(sz);
	int i,j;
	for(i=0;i<sz;i++)
	{
		for(j=0;j<sz;j++)
		{
			addition[i][j] = m1[i][j] + m2[i][j];
		}
	}
	return addition;
}

//subtraction of 2 matrices
int **subMatrix(int **m1,int **m2,int sz)
{
	int **subtraction = allocateMatrix(sz);
	int i,j;
	for(i=0;i<sz;i++)
	{
		for(j=0;j<sz;j++)
		{
			subtraction[i][j] = m1[i][j] - m2[i][j];
		}
	}
	return subtraction;
}

//base condition
void baseCondition(int **mat1,int **mat2,int **res)
{
	int m1,m2,m3,m4,m5,m6,m7;
	m1 = (mat1[0][0] + mat1[1][1]) * (mat2[0][0] + mat2[1][1]);
	m2 = (mat1[1][0] + mat1[1][1]) * mat2[0][0];
	m3 = mat1[0][0] * (mat2[0][1] - mat2[1][1]);
	m4 = mat1[1][1] * (mat2[1][0] - mat2[0][0]);
	m5 = (mat1[0][0] + mat1[0][1]) * mat2[1][1];
	m6 = (mat1[1][0] - mat1[0][0]) * (mat2[0][0] + mat2[0][1]);
	m7 = (mat1[0][1] - mat1[1][1]) * (mat2[1][0] + mat2[1][1]);

	res[0][0] = m1+m4-m5+m7;
	res[0][1] = m3+m5;
	res[1][0] = m2+m4;
	res[1][1] = m1+m3-m2+m6;
}

//function to multiply
void multiplyStra(int sz, int** mat1, int** mat2, int **res)
{
	if(sz==2)		//base condition
	{
		baseCondition(mat1,mat2,res);
		return;
	}

	int **mat1_11 = allocateMatrix(sz/2);	//A11
	int **mat1_12 = allocateMatrix(sz/2);	//A12
	int **mat1_21 = allocateMatrix(sz/2);	//A21
	int **mat1_22 = allocateMatrix(sz/2);	//A22

	int **mat2_11 = allocateMatrix(sz/2);	//B11
	int **mat2_12 = allocateMatrix(sz/2);	//B12
	int **mat2_21 = allocateMatrix(sz/2);	//B21
	int **mat2_22 = allocateMatrix(sz/2);	//B22

	//create small matrices
	copyMatrix((sz/2),mat1_11,mat1,0,0);
	copyMatrix((sz/2),mat1_12,mat1,0,sz/2);
	copyMatrix((sz/2),mat1_21,mat1,sz/2,0);
	copyMatrix((sz/2),mat1_22,mat1,sz/2,sz/2);

	copyMatrix((sz/2),mat2_11,mat2,0,0);
	copyMatrix((sz/2),mat2_12,mat2,0,sz/2);
	copyMatrix((sz/2),mat2_21,mat2,sz/2,0);
	copyMatrix((sz/2),mat2_22,mat2,sz/2,sz/2);

	//generate m1 through m7
	int** m1 = allocateMatrix(sz/2);
	multiplyStra(sz/2,addMatrix(mat1_11,mat1_22,sz/2),addMatrix(mat2_11,mat2_22,sz/2),m1);

	int** m2 = allocateMatrix(sz/2);
	multiplyStra(sz/2,addMatrix(mat1_21,mat1_22,sz/2),mat2_11,m2);

	int** m3 = allocateMatrix(sz/2);
	multiplyStra(sz/2,mat1_11,subMatrix(mat2_12,mat2_22,sz/2),m3);

	int** m4 = allocateMatrix(sz/2);
	multiplyStra(sz/2,mat1_22,subMatrix(mat2_21,mat2_11,sz/2),m4);

	int** m5 = allocateMatrix(sz/2);
	multiplyStra(sz/2,addMatrix(mat1_11,mat1_12,sz/2),mat2_22,m5);

	int** m6 = allocateMatrix(sz/2);
	multiplyStra(sz/2,subMatrix(mat1_21,mat1_11,sz/2),addMatrix(mat2_11,mat2_12,sz/2),m6);

	int** m7 = allocateMatrix(sz/2);
	multiplyStra(sz/2,subMatrix(mat1_12,mat1_22,sz/2),addMatrix(mat2_21,mat2_22,sz/2),m7);

	//compose
	int **c1  = addMatrix(subMatrix(addMatrix(m1,m4,sz/2),m5,sz/2),m7,sz/2);
	int **c2 =  addMatrix(m3,m5,sz/2);
	int **c3 =  addMatrix(m2,m4,sz/2);
	int **c4  = addMatrix(subMatrix(addMatrix(m1,m3,sz/2),m2,sz/2),m6,sz/2);
	composeMatrix(sz,c1,c2,c3,c4,res);

}

//compose
void composeMatrix(int sz,int **c1,int **c2,int **c3,int **c4,int **res)
{
	int i,j,p,q;
	for(i=0,p=0;i<sz/2;i++,p++)
	for(j=0,q=0;j<sz/2;j++,q++)
		res[i][j] = c1[p][q];

	for(i=0,p=0;i<sz/2;i++,p++)
	for(j=sz/2,q=0;j<sz;j++,q++)
		res[i][j] = c2[p][q];

	for(i=sz/2,p=0;i<sz;i++,p++)
	for(j=0,q=0;j<sz/2;j++,q++)
		res[i][j] = c3[p][q];

	for(i=sz/2,p=0;i<sz;i++,p++)
	for(j=sz/2,q=0;j<sz;j++,q++)
		res[i][j] = c4[p][q];
}

//free memory
void free_m(int **m,int s)
{
	int i;
	for(i=0;i<s;i++)
	{
		free(m[i]);
	}
	free(m);
}
