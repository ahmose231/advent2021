#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN 1024
#define TOTALDAYS 256

void main()
{
    long long int tank[9]={0};
    char line[LEN];
    fgets(line,LEN,stdin);
    char *token;
    token=strtok(line,",");
    while(token!=NULL)
    {
        tank[atoll(token)]++;
        token=strtok(NULL,",");
    }

        
    for(int i=0;i<TOTALDAYS;i++)
    {
        long long int temp=tank[0];
        for(int j=0;j<8;j++)
            tank[j]=tank[j+1];
        tank[6]+=temp;
        tank[8]=temp;

    }
    
    long long int sum=0;
    for(int i=0;i<9;i++)
        sum+=tank[i];
    
    printf("%lld\n",sum);
    return;
}
