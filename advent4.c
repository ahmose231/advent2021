#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN 512

void main(int argc, char *argv[])
{
	FILE *fp=fopen(argv[1],"r");
	if(fp==NULL) return;
	
	char line[LEN];
	fgets(line,LEN,fp);

	int len=strlen(line);
	int drawncount=0;
	
	for(int i=0;i<len;i++)
		if(line[i]==',')
			drawncount++;

	drawncount++;
	
	int drawn[drawncount];
	char *token;
	int k=0;

	token=strtok(line,",");
	while(token!=NULL)
	{
		drawn[k++]=atoi(token);
		token=strtok(NULL,",");

	}

	int boardcount=0;
	
	while(!feof(fp))
	{
		fgets(line,LEN,fp);
		if(strlen(line)==1)
			boardcount++;
	}
	
	int boards[boardcount][5][5];
	
	rewind(fp);
	fgets(line,LEN,fp);
	
	for(int i=0;i<boardcount;i++)
	{
		fgets(line,LEN,fp);
		for(int j=0;j<5;j++)
		{
			k=0;
			fgets(line,LEN,fp);
			token=strtok(line," ");
			while(token!=NULL)
			{
				boards[i][j][k++]=atoi(token);
				token=strtok(NULL," ");
			}
		}
	}
	
	fclose(fp);
	
	int linebest;
	int boardlinebest[boardcount][5];
	
	for(int i=0;i<boardcount;i++)
	{
		for(int j=0;j<5;j++)
		{
			for(int m=0;m<drawncount;m++)
			{
				for(int n=0;n<5;n++)
				{
					if(drawn[m]==boards[i][j][n])
					{
						linebest=m;
						continue;
					}
				}
			}
			boardlinebest[i][j]=linebest;
		}
	}
	
	int boardbest[boardcount];
	int min;
	
	for(int i=0;i<boardcount;i++)
	{
		min=LEN;
		for(int j=0;j<5;j++)
			if(min>boardlinebest[i][j])
				min=boardlinebest[i][j];
		boardbest[i]=min;
	}
	
	min=LEN;
	int minindex;
	for(int i=0;i<boardcount;i++)
		if(min>boardbest[i])
		{
			min=boardbest[i];
			minindex=i;
		}
	
	int winningboard = minindex;
	int winningdrawindex = boardbest[minindex];
	
	int flag;
	int sum=0;
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			flag=0;
			
			for(int m=0;m<=winningdrawindex;m++)
				if(drawn[m]==boards[winningboard][i][j])
					flag=1;
					
			if(!flag)
				sum=sum+boards[winningboard][i][j];
		}
	}

	printf("%d\n",sum * drawn[winningdrawindex]);

	return;
	
}



