#include <stdio.h>
#include <string.h>

#define LEN 1024

void main()
{
	char *token;
	int count;
	char line[LEN];
	count=0;
	while(fgets(line,LEN,stdin)!=NULL)
	{
		line[strlen(line)-1]='\0';
		token=strtok(line," ");
		while(token!=NULL)
		{
			if(token[0]=='|')
				break;
			token=strtok(NULL," ");
		}
		
		token=strtok(NULL," ");
		while(token!=NULL)
		{
			switch(strlen(token))
			{
				case 2:
				case 3:
				case 4:
				case 7:
					count++;
					break;
			}
			token=strtok(NULL," ");
		}
	}
	
	printf("%d\n",count);
	return;
}
