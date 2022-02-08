#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 8
#define ARRAY 1024

int compare(const void *a, const void *b)
{
	return (*(int*)a - *(int*)b);
}

void main()
{
	char token[LEN];
	int tokenindex;
	
	int c;
	
	int list[ARRAY];
	int listindex;
	
	tokenindex=0;
	listindex=0;
	
	while(1)
	{
		c = getchar();
		if(c==',' || c=='\n' || c==EOF)
		{
			token[tokenindex] = '\0';
			list[listindex++] = atoi(token);
			tokenindex = 0;
			
			if(c!=',')
				break;
		}
		else
			token[tokenindex++] = c;
	}
	

	qsort(list, listindex, sizeof(int), compare);
	
	puts("");
	int sum=0;
	for(int i=0;i<listindex;i++)
		sum += abs(list[listindex/2] - list[i]);
	
	printf("%d\n",sum);
	
	return;
}

