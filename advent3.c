#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN 32
#define B_LEN 12

void main()
{
	char line[LEN];
	int m[B_LEN];
	for(int i=0;i<B_LEN;i++)
		m[i]=0;
	int count=0;
	while(fgets(line,LEN,stdin))
	{
		count++;
		for(int i=0;i<B_LEN;i++)
			if(line[i]-'0')
				m[i]++;
	}
	
	for(int i=0;i<B_LEN;i++)
		if(m[i]>count/2)
			line[i]='1';
		else
			line[i]='0';
	line[B_LEN]='\0';
	printf("\n\n%s\n",line);
	int k=1;
	for(int i=0;i<B_LEN;i++)
		k=k*2;
		
	int sum1=0;
	int sum2=0;
	
	for(int i=0;i<B_LEN;i++)
	{
	
		k=k/2;
		
		if(line[i]-'0')
			sum1=sum1+k;
		else
			sum2=sum2+k;
		

	}
	
	printf("%d * %d = %d\n",sum1, sum2, sum1*sum2);
	
	return;
}
	
