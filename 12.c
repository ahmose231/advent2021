// does not work

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAMELEN 8
#define LINELEN 16
#define LISTLEN 32

void move_to_caves(int thiscave, char* fromwhere);

struct node {
    char *name;
    int connection_count;
    char *connection[LISTLEN];
};

struct node cave[LISTLEN];
int caveindex=0;
int valid_path_total=0;

void main()
{

    int flag;
    char line[LINELEN];
    char *token1, *token2;
    int len;
    
    
    while(fgets(line,LINELEN,stdin)!=NULL)
    {
        len=strlen(line);

        if(len==1) break;
        
        line[len-1]='\0';

        token1=strtok(line,"-");
        token2=strtok(NULL,"-");
        
        
        flag=0;
        
        for(int i=0;i<caveindex;i++)
        {
            if(strcmp(token1, cave[i].name)==0)
            {
                flag=1;
                
                cave[i].connection[ cave[i].connection_count ] = malloc(NAMELEN);
                strcpy(cave[i].connection[ cave[i].connection_count ], token2);
                
                cave[i].connection_count++;
                
                break;
            }
        }
        
        if(!flag)
        {
            cave[caveindex].name = malloc(NAMELEN);
            strcpy(cave[caveindex].name, token1);
            
            cave[caveindex].connection_count=0;
            
            cave[caveindex].connection[ cave[caveindex].connection_count ] = malloc(NAMELEN);
            strcpy(cave[caveindex].connection[ cave[caveindex].connection_count ], token2);
            
            cave[caveindex].connection_count++;
            caveindex++;
        }
        
        
        flag=0;
        
        for(int i=0;i<caveindex;i++)
        {
            if(strcmp(token2,cave[i].name)==0)
            {
                flag=1;
                
                cave[i].connection[ cave[i].connection_count ] = malloc(NAMELEN);
                strcpy(cave[i].connection[ cave[i].connection_count ], token1);
                
                cave[i].connection_count++;
                break;
            }
        }
        
        if(!flag)
        {
            cave[caveindex].name = malloc(NAMELEN);
            strcpy(cave[caveindex].name, token2);
            
            cave[caveindex].connection_count=0;
            
            cave[caveindex].connection[ cave[caveindex].connection_count ] = malloc(NAMELEN);
            strcpy(cave[caveindex].connection[ cave[caveindex].connection_count ], token1);
            
            cave[caveindex].connection_count++;
            caveindex++;
        }
    }
    
    
    for(int i=0;i<caveindex;i++)
        if(strcmp(cave[i].name, "start")==0)
        {
            move_to_caves(i, "nowhere");
            break;
        }
    
    printf("%d\n", valid_path_total);
    
    return;
}



void move_to_caves(int thiscave, char* fromwhere)
{
    if(strcmp(cave[thiscave].name, "end")==0)
    {
        valid_path_total++;
        return;
    }
    
    int nextcave;
    
    for(int i=0;i<cave[thiscave].connection_count;i++)
    {
        if(strcmp(cave[thiscave].connection[i], fromwhere)==0)
            if(fromwhere[0]>='a' && fromwhere[0]<='z')
                continue;
        
        for(int j=0;j<caveindex;j++)
            if(strcmp(cave[thiscave].connection[i], cave[j].name)==0)
            {
                nextcave=j;
                break;
            }

        move_to_caves(nextcave, cave[thiscave].name);
        
    }
    
    return;
}

