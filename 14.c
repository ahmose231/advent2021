#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define INPUTSIZE 1024
#define LINESIZE 16

void main()
{
    char *input=malloc(INPUTSIZE);
    input[0]='\0';
    char line[LINESIZE];
    int linecount=0;
    while(fgets(line,LINESIZE,stdin)!=NULL)
    {
        sprintf(input, "%s%s", input, line);
        linecount++;
    }
    char *token;
    token=strtok(input,"\n");
    
    int len=strlen(token);
    
    char *polymer=malloc(len);
    strcpy(polymer,token);
    
    token=strtok(NULL,"\n");

    char rules[linecount-2][8];
    int rulecount=0;
    while(token!=NULL)
    {
        strcpy(rules[rulecount++], token);
        token=strtok(NULL,"\n");
    }
    
    char *polymer2;
    char *temp;
    int p2index;
    int newlettercount;
    for(int step=0;step<10;step++)
    {
        newlettercount=0;
        
        len=strlen(polymer);
        
        for(int rindex=0;rindex<rulecount;rindex++)
            for(int pindex=0;pindex<len-1;pindex++)
                if(rules[rindex][0]==polymer[pindex] && rules[rindex][1]==polymer[pindex+1])
                    newlettercount++;
        polymer2=malloc(len + newlettercount + 1);
        p2index=0;

        for(int pindex=0;pindex<len-1;pindex++)
        {
            polymer2[p2index++]=polymer[pindex];
            
            for(int rindex=0;rindex<rulecount;rindex++)
                if(rules[rindex][0]==polymer[pindex] && rules[rindex][1]==polymer[pindex+1])
                    polymer2[p2index++]=rules[rindex][6];
        }
        
        polymer2[p2index++]=polymer[len-1];
        polymer2[p2index]='\0';
        temp=polymer;
        free(temp);
        polymer=polymer2;
    }
    
    int alphabet[26];
    for(int i=0;i<26;i++)
        alphabet[i]=0;
    len=strlen(polymer);
    for(int i=0;i<len;i++)
        alphabet[polymer[i]-'A']++;
        

    
    int max=INT_MIN;
    int min=INT_MAX;

        
    for(int i=0;i<26;i++)
    {
        if(alphabet[i]==0)
            continue;
        if(alphabet[i]>max)
            max=alphabet[i];
        if(alphabet[i]<min)
            min=alphabet[i];
    }


    printf("%d\n", max-min);


    return;
    
}
