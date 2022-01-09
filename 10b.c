//incomplete

#include <stdio.h>
#include <string.h>

#define LEN 128

int zing(int c);
int bling(int c);

void main()
{
	char line[LEN];
	int len;
	char stack[LEN];
	int si;
	int flag;
	unsigned long long int total=0;
	unsigned long long int bigtotal[100];
	int bigtotalindex=0;
	while(fgets(line,LEN,stdin)!=NULL)
	{
	    total=0;
		flag=0;
		si=0;
		len=strlen(line);
		if(len<2) continue;
		line[len-1]='\0';
		for(int i=0;i<len;i++)
		{
			if(strchr("{<[(", line[i])!=NULL)
				stack[si++]=line[i];
			else
			{
				if(line[i]==')')
				{
					if(stack[si-1]=='(')
						si--;
					else
						flag=1;
				}
				else 
				{
					if(stack[si-1]==line[i]-2)
						si--;
					else
						flag=1;
				}
			}
			
			if(flag)
			{
//				total += zing(line[i]);	
				break;
			}
		}
		
		if(!flag)
		{
		    for(int i=si-1;i>=0;i--)
		    {
		        total *= 5;
		        total += bling(stack[i]);
		    }
		}
		
		bigtotal[bigtotalindex++]=total;
	}
					
	unsigned long long int temp;
	for(int i=0;i<bigtotalindex-1;i++)
	{
		for(int j=i+1;j<bigtotalindex;j++)
		{
			if(bigtotal[i]>bigtotal[j])
			{
				temp=bigtotal[i];
				bigtotal[i]=bigtotal[j];
				bigtotal[j]=temp;
			}
		}
	}
			
	int count=0;	
	for(int i=0;i<bigtotalindex;i++)
		if(bigtotal[i]>0)
			count++;
	
	printf("%llu\n",bigtotal[bigtotalindex-count+(count/2)]);
	
	
	return;
}


int zing(int c)
{
	switch(c)
	{	
		case ')': return 3;
		case ']': return 57;
		case '}': return 1197;
		case '>': return 25137;
	}
	
	return 0;
}


int bling(int c)
{
    switch(c)
    {
		case '(': return 1;
		case '[': return 2;
		case '{': return 3;
		case '<': return 4;
	}
	
	return 0;
}
