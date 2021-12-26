#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN 64

void main(int argc, char *argv[])
{
	FILE*fp=fopen(argv[1],"r");
	if(fp==NULL) return;
	
	int m[1000][1000];
	for(int i=0;i<1000;i++)
		for(int j=0;j<1000;j++)
			m[i][j]=0;
	
	char *token1, *token2;		
	char line[LEN];
	int a,b,c,d;
	int min,max;
	while(fgets(line,LEN,fp)!=NULL)
	{
		token1=strtok(line," -> ");
		token2=strtok(NULL," -> ");
		
	
		a=atoi(strtok(token1,","));
		b=atoi(strtok(NULL,","));

		c=atoi(strtok(token2,","));
		d=atoi(strtok(NULL,","));
		
		if(a==c)
		{
			min=b>d?d:b;
			max=b>d?b:d;
			for(int i=min;i<=max;i++)
				m[a][i]++;
		}
		
		if(b==d)
		{
			min=a>c?c:a;
			max=a>c?a:c;
			for(int i=min;i<=max;i++)
				m[i][b]++;
		}
		
	}
	
	int count=0;
	for(int i=0;i<1000;i++)
		for(int j=0;j<1000;j++)
			if(m[i][j]>1)
				count++;
	
	printf("%d\n",count);
	
	fclose(fp);	
	return;
}
