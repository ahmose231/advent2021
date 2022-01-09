#include <stdio.h>
#include <string.h>

#define LEN 128

int zing(int c);

void main()
{
	char line[LEN];
	int len;
	char stack[LEN];
	int si;
	int flag;
	int total=0;
	while(fgets(line,LEN,stdin)!=NULL)
	{
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
					{

						si--;
					}
					else
					{

						flag=1;
					}
				}
				else {
					if(stack[si-1]==line[i]-2)
					{

						si--;
					}
					else
					{

						flag=1;
					}
				}
			}
			
			if(flag)
			{
				total += zing(line[i]);	

				break;
			}
		}
	}
					
	printf("%d\n",total);
	
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


	
	
	
