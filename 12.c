
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAMELEN 8
#define LINELEN 16
#define LISTLEN 32


void move_to_caves(int thiscave, int pid);
void lose(int pid);
struct pathnode* find_by_pid(int pid);
struct pathnode* create_by_pid(int pid);

struct node {
    char *name;
    int connection_count;
    char *connection[LISTLEN];
} cave[LISTLEN];

int caveindex=0;            
int valid_path_total=0;
int pid=0;                  


struct pathnode {
    int path_id;
    int visited[LISTLEN];
    struct pathnode *next;
} *v_root, *v_current, *v_temp, *v_temp2;

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
            v_root=malloc(sizeof(struct pathnode));
            v_root->next=NULL;
            v_current=v_root;
            v_current->path_id = pid;
            for(int j=0;j<LISTLEN;j++)
                v_current->visited[j]=0;
             
            move_to_caves(i, pid);
            
            break;
        }
    
    printf("cave total: %d\n",caveindex);
    printf("valid paths: %d\n", valid_path_total);
    printf("path id total: %d\n",pid);
    return;
}



void move_to_caves(int thiscave, int oldpid)
{

    if(strcmp(cave[thiscave].name, "end")==0)
    {
        valid_path_total++;
        return;
    }
    
    v_temp = find_by_pid(oldpid);
    v_temp->visited[thiscave]++;

    int nextcave;
    
    for(int i=0;i<cave[thiscave].connection_count;i++)
    {
        if(strcmp(cave[thiscave].connection[i], "start")==0)
            continue;
        
        for(int j=0;j<caveindex;j++)
            if(strcmp(cave[thiscave].connection[i], cave[j].name)==0)
            {
                nextcave=j;
                break;
            }
        
        pid++;
        
        v_current = create_by_pid(pid);
        
        v_temp = find_by_pid(oldpid);
        
        for(int j=0;j<LISTLEN;j++)
            v_current->visited[j] = v_temp->visited[j];

        if(cave[nextcave].name[0]>='a' && cave[nextcave].name[0]<='z')
            if(v_current->visited[nextcave])
                continue;

        move_to_caves(nextcave, pid);
        
    }


    lose(oldpid);
        
    return;
}


struct pathnode* create_by_pid(int pid)
{
    v_current->next = malloc(sizeof(struct pathnode));
    v_current = v_current->next;
    v_current->path_id = pid;
    v_current->next = NULL;
    
    return v_current;
}


struct pathnode* find_by_pid(int pid)
{
            
    v_temp = v_root;
    while(v_temp!=NULL)
    {
        if(v_temp->path_id == pid)
            break;
        
        v_temp = v_temp->next;
    }
    
    return v_temp;
}

void lose(int pid)
{
    v_temp=v_temp2=v_root;
    while(v_temp!=NULL)
    {
        if(v_temp->path_id == pid)
        {
            v_temp2->next=v_temp->next;
            free(v_temp);
            break;
        }
        
        v_temp2=v_temp;
        v_temp=v_temp->next;
    }
    
    return;
}
