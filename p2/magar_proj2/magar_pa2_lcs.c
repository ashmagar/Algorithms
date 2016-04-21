#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//function to calculate LCS declaration
void LCS(char* str1,char* str2, int str1_len, int str2_len);

int main(int argc, char* argv[])
{
	int str1_len,str2_len,final_len;
//	char str1[] = "AXYT";
//	char str2[] = "AYZX";

	if(argc!=3)
	{
		printf("run command : ./lcs <first_string> <second_string> string length should be < 100\n");
		return(0);
	}
	char str1[100];
	char str2[100];

	strcpy(str1,argv[1]);
	strcpy(str2,argv[2]);
	str1_len = strlen(str1);
	str2_len = strlen(str2);

	LCS(str1,str2,str1_len,str2_len);
	return 0;
}

//function to calculate LC definition
void LCS(char* str1,char* str2, int str1_len, int str2_len)
{
	int C[str1_len+1][str2_len+1];
	int i,j;

	for(i=0;i<=str1_len;i++)
	for(j=0;j<=str2_len;j++)
	{
		C[i][j] = 0;
	}
	for(i=1;i<=str1_len;i++)
	{
	for(j=1;j<=str2_len;j++)
	{
		if(i==0 || j==0)
		C[i][j] = 0;

		else if (str1[i-1] == str2[j-1])
		C[i][j] =  C[i-1][j-1] + 1;

		else if(C[i-1][j] >= C[i][j-1])
		C[i][j] = C[i-1][j];

		else
		C[i][j] = C[i][j-1];
	}
	}

	//printing matrix
	printf("\nMatrix is : \n");
	for(i=0;i<=str1_len;i++)
	{
		for(j=0;j<=str2_len;j++)
		{
			printf("%d ",C[i][j]);
		}
		printf("\n");
	}

	//printing LCS
	int final_len = C[str1_len][str2_len];
	printf("\nLCS length is %d\n",final_len);
	char subSeq[final_len+1];
	i = str1_len;
	j = str2_len;
	int reverse_index = final_len;
	int k=0;
	while(i>=0 && j>=0)
	{
		if(str1[i-1] == str2[j-1])
		{
			subSeq[reverse_index-1] = str1[i-1];
			i--; j--; reverse_index--;
		}else if(C[i-1][j] >= C[i][j-1]){
			i--;
		}else { j--; }
	}
	subSeq[final_len] = '\0';
	printf("LCS is : %s\n",subSeq);
}


