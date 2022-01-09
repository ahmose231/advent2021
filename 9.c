//wrong answer

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LEN 128
#define SQUARESIZE 100

void main()
{
	char line[LEN];
	char m[SQUARESIZE][SQUARESIZE];
	int len;
	int k=0;
	while(fgets(line,LEN,stdin)!=NULL)
	{
		len=strlen(line);
		if(len<2) continue;
		for(int i=0;i<SQUARESIZE;i++)
			m[k][i]=line[i];
		k++;
	}
	int sum=0;
	for(int i=1;i<SQUARESIZE-1;i++)
		for(int j=1;j<SQUARESIZE-1;j++)
			if(m[i][j]<m[i+1][j] &&
				m[i][j]<m[i-1][j] &&
				m[i][j]<m[i][j+1] &&
				m[i][j]<m[i+1][j-1])
					sum=sum+1+m[i][j]-'0';

	for(int i=1;i<SQUARESIZE-1;i++)
		if(m[0][i]<m[0][i-1] &&
			m[0][i]<m[0][i+1] &&
			m[0][i]<m[1][i])
				sum=sum+1+m[0][i]-'0';

	for(int i=1;i<SQUARESIZE-1;i++)
		if(m[SQUARESIZE-1][i]<m[SQUARESIZE-1][i-1] &&
			m[SQUARESIZE-1][i]<m[SQUARESIZE-1][i+1] &&
			m[SQUARESIZE-1][i]<m[SQUARESIZE-2][i])
				sum=sum+1+m[SQUARESIZE-1][i]-'0';

	for(int i=1;i<SQUARESIZE-1;i++)
		if(m[i][0]<m[i-1][0] &&
			m[i][0]<m[i+1][0] &&
			m[i][0]<m[i][1])
				sum=sum+1+m[i][0]-'0';

	for(int i=1;i<SQUARESIZE-1;i++)
		if(m[i][SQUARESIZE-1]<m[i-1][SQUARESIZE-1] &&
			m[i][SQUARESIZE-1]<m[i+1][SQUARESIZE-1] &&
			m[i][SQUARESIZE-1]<m[i][SQUARESIZE-2])
				sum=sum+1+m[0][i]-'0';
	
	if(m[0][0]<m[1][0] && m[0][0]<m[0][1])
		sum=sum+1+m[0][0]-'0';
		
	if(m[0][SQUARESIZE-1]<m[0][SQUARESIZE-2] && m[0][SQUARESIZE-1]<m[1][00])
		sum=sum+1+m[0][SQUARESIZE-1]-'0';

	if(m[SQUARESIZE-1][0]<m[SQUARESIZE-2][0] && m[SQUARESIZE-1][0]<m[SQUARESIZE-1][1])
		sum=sum+1+m[SQUARESIZE-1][0]-'0';

	if(m[SQUARESIZE-1][SQUARESIZE-1]<m[SQUARESIZE-1][SQUARESIZE-2] && m[SQUARESIZE-1][SQUARESIZE-1]<m[SQUARESIZE-2][SQUARESIZE-1])
		sum=sum+1+m[SQUARESIZE-1][SQUARESIZE-1]-'0';
		
	printf("%d\n",sum);
		
	return;
}
