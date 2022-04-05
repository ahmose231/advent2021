#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN 256

void main()
{
	char line[LEN];
	int len;
	int letters[7];
	int letters2[7];
	char *firsthalf, *secondhalf;
	char *token;
	int wlen;
	int word[12][12];
	int k;
	int rtop, rbottom, ltop, lbottom, top, bottom, mid;
	int right[2];
	int diff;
	int count;
	int flag;
	int sum=0;
	int wordlen[12];
	while(fgets(line,LEN,stdin)!=NULL)
	{
		int len=strlen(line);
		if(len<2) continue;
		if(line[len-1]=='\n' || line[len-1]==EOF)
			line[len-1]='\0';
		
		firsthalf=strtok(line," | ");
		secondhalf=strtok(NULL," | ");
		
		token=strtok(firsthalf," ");
		k=0;
		while(token!=NULL)
		{
			wordlen[k]=strlen(token);
			for(int i=0;i<wordlen[k];i++)
				word[k][i]=token[i]-'a';
			k++;
			token=strtok(NULL," ");
		}
		
		for(int i=0;i<k;i++)
			if(wordlen[i]==2)
			{
				right[0]=word[i][0];
				right[1]=word[i][1];
			}
		
		for(int i=0;i<k;i++)
			if(wordlen[i]==3)
				for(int j=0;j<3;j++)
					if(word[i][j]!=right[0] && word[i][j]!=right[1])
						top=word[i][j];
		
		for(int i=0;i<7;i++)
			letters[i]=0;
		
		for(int i=0;i<k;i++)
			if(wordlen[i]==4)
				for(int j=0;j<4;j++)
					letters[word[i][j]]++;
		letters[top]++;
		
		for(int i=0;i<k;i++)
			if(wordlen[i]==6)
			{
				for(int m=0;m<7;m++)
					letters2[m]=0;
				for(int m=0;m<6;m++)
					letters2[word[i][m]]++;
				
				count=0;
				for(int m=0;m<7;m++)
					if(letters[m]!=letters2[m])
					{
						count++;
						diff=m;
					}
				
				if(count==1)
				{
					bottom=diff;
					break;
				}
			}
			
		for(int i=0;i<k;i++)
			if(wordlen[i]==6)
			{
				flag=0;
				for(int m=0;m<7;m++)
					letters2[m]=0;
				for(int m=0;m<6;m++)
					letters2[word[i][m]]++;
				
				for(int m=0;m<7;m++)
					letters[m]=0;				
				letters[right[0]]++;
				letters[right[1]]++;
				
				for(int m=0;m<7;m++)
					if(letters[m])
						if(!letters2[m])
						{
							rtop=m;
							if(rtop==right[0])
								rbottom=right[1];
							else
								rbottom=right[0];
							flag=1;
							break;
						}
				if(flag)
					break;
			}		
							
		for(int i=0;i<k;i++)
			if(wordlen[i]==5)
			{
				for(int m=0;m<7;m++)
					letters[m]=0;
				for(int m=0;m<5;m++)
					letters[word[i][m]]++;
				
				if(letters[rtop] && letters[rbottom])
				{
					letters[top]=0;
					letters[bottom]=0;
					letters[rtop]=0;
					letters[rbottom]=0;
					
					for(int m=0;m<7;m++)
						if(letters[m])
						{
							mid=m;
							break;
						}
				}
				
				break;
			}
		
		for(int i=0;i<k;i++)
			if(wordlen[i]==6)
			{
				for(int m=0;m<7;m++)
					letters[m]=0;
				for(int m=0;m<6;m++)
					letters[word[i][m]]++;
				flag=0;
				for(int m=0;m<7;m++)
					if(!letters[m])
					{
						if(m==mid)
							break;
						if(m==rtop)
							break;
						
						lbottom=m;
						flag=1;
					}
				
				if(flag)
					break;
			}
		
		for(int i=0;i<k;i++)
			if(wordlen[i]==4)
			{
				for(int m=0;m<7;m++)
					letters[m]=0;
				for(int m=0;m<4;m++)
					letters[word[i][m]]++;				
				
				for(int m=0;m<7;m++)
					if(letters[m])
					{
						if(m==mid)
							continue;
						if(m==rtop)
							continue;
						if(m==rbottom)
							continue;
						
						ltop=m;
						flag=1;
						break;
					}
				
				if(flag)
					break;
			}
		
		token=strtok(secondhalf," ");
		while(token!=NULL)
		{
			wordlen[k]=strlen(token);	
			for(int i=0;i<wordlen[k];i++)
				word[k][i]=token[i]-'a';
			k++;
			token=strtok(NULL," ");
		}
		
		for(int i=0;i<k;i++)
		{
			for(int m=0;m<7;m++)
				letters[m]=0;
			
			for(int m=0;m<wordlen[i];m++)
				letters[word[i][m]]++;
			
			int x=0;
			for(int m=0;m<7;m++)
				if(letters[m])
					x=x*10 + m;
			
			sum += x;
			printf("%d\n",x);
		}
	}
	
	printf("%d\n",sum);
	return;
}
		
		
				
