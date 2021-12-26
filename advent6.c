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
		if(counter==-1)
		{
			counter=6;
			newfish(i+1, 8);
		}
	}
	return;
}

int main(int argc, char *argv[]) {
	FILE*fp=fopen(argv[1],"r");
	char line[LEN];
	fgets(line,LEN,fp);

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
