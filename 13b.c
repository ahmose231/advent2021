#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN 32
#define FOLDCOUNT 16

void main()
{
	char line[LEN];
	int len;
	
	int coordinates[1000][2];
	int cindex=0;
	char *token;
	
	char fold[FOLDCOUNT][8];
	int findex=0;
	
	fgets(line,LEN,stdin);
	len=strlen(line);
	while(len>2)
	{
		token=strtok(line,",");
		coordinates[cindex][0]=atoi(token);
		
		token=strtok(NULL,",");
		coordinates[cindex][1]=atoi(token);
		
		cindex++;
		
		fgets(line,LEN,stdin);
		len=strlen(line);	
	}
	
	while(fgets(line,LEN,stdin)!=NULL)
	{
		len=strlen(line);
		if(len<2) break;
		
		token=strtok(line," ");
		token=strtok(NULL," ");
		token=strtok(NULL," ");
		
		strcpy(fold[findex], token);
		findex++;
	}	
	
	int along;
	int halfamount;
	int crop;
	
	for(int i=0;i<findex;i++)
	{
		token=strtok(fold[i],"=");
		along=token[0];
		
		token=strtok(NULL,"=");
		halfamount=atoi(token);
		
		switch(along)
		{
			case 'x':
				
				for(int j=0;j<cindex;j++)
				{
					if(coordinates[j][0]>halfamount)
					{
						crop=coordinates[j][0]-halfamount;
						crop=crop*2;
						coordinates[j][0] -= crop;
					}
				}

				break;
				
			case 'y':
				for(int j=0;j<cindex;j++)
				{
					if(coordinates[j][1]>halfamount)
					{
						crop=coordinates[j][1]-halfamount;
						crop=crop*2;
						coordinates[j][1] -= crop;
					}
				}

				break;
		}
			
			
			
	/*   FOR PART 1:
			
	int total=0;
	int flag;
	for(int i=0;i<cindex;i++)
	{
		flag=0;
		for(int j=0;j<i;j++)
			if(coordinates[i][0]==coordinates[j][0])
				if(coordinates[i][1]==coordinates[j][1])
				{
					flag=1;
					break;
				}
		
		if(!flag)
			total++;
	}
	printf("%d\n", total);
	return;
	
	*/

	}
	
	
	int m[40][7];
	for(int i=0;i<40;i++)
		for(int j=0;j<7;j++)
			m[i][j]='.';
	for(int i=0;i<cindex;i++)
		m[coordinates[i][0]][coordinates[i][1]]='#';
	
	
	for(int i=0;i<7;i++)
	{
		for(int j=0;j<40;j++)
			printf("%c",m[j][i]);
		printf("\n");
	}	

	
	return;
}
					
				
			
		
