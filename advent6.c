// gives the wrong answer

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FINALDAY 80
#define LEN 1024

int totalfish=0;

void newfish(int today, int counter)
{
	totalfish++;

	for(int i=today;i<FINALDAY;i++)
	{
		counter--;
		if(counter==0)
		{
			counter=7;
			newfish(i, 8);
		}
	}
	return;
}

int main(void) {
	char line[LEN];
	fgets(line,LEN,stdin);
	
	char *token;
	token=strtok(line,",");
	while(token!=NULL)
	{
		newfish(0,atoi(token));
		token=strtok(NULL,",");
	}
	
	printf("%d\n",totalfish);
	return 0;
}
