// does not work


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAMELEN 8
#define LINELEN 16
#define LISTLEN 32


void move_to_caves(int thiscave, int pid);

struct node {
    char *name;
    int connection_count;
    char *connection[LISTLEN];
} cave[LISTLEN];

int caveindex=0;            // the index for the array cave[]
int valid_path_total=0;
int pid=0;                  // path id


// for a linked list, each node is a new path taken
// with its own list of caves visited and unvisited
struct pathnode {
    int path_id;
    int visited[LISTLEN];
    struct pathnode *prev;
    struct pathnode *next;
} *v_root, *v_current, *v_temp;

void main()
{

    int flag;
    char line[LINELEN];
    char *token1, *token2;
    int len;
    
    
    /// parsing the input to place them neatly in our array of structs called cave[]
    
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
    
    
    
    // everything above this comment is about parsing input
    // and placing it inside an array of structs called cave[]
    
    
    
    // pid is path id, set at 0

    for(int i=0;i<caveindex;i++)
        if(strcmp(cave[i].name, "start")==0)
        {
            v_root=malloc(sizeof(struct pathnode));
            v_root->next=v_root->prev=NULL;
            v_current=v_root;
            v_current->path_id = pid;
            for(int j=0;j<LISTLEN;j++)
                v_current->visited[j]=0;
             
            // the real action   
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

    // to check if this cave is the 'end'
    if(strcmp(cave[thiscave].name, "end")==0)
    {
        // since this path ended, let's free its path-visited stack
        v_temp=v_root;
        while(v_temp!=NULL)
        {
            v_temp=v_temp->next;
            if(v_temp->path_id == oldpid)
            {
                v_temp->prev->next = v_temp->next;
                free(v_temp);
            }
        }
        
        // a valid path
        valid_path_total++;
        
        // recursion ends here
        return;
    }

    // to find the current path's associated path-visited stack
    v_temp = v_root;
    while(v_temp!=NULL)
    {
        v_temp = v_temp->next;
        if(v_temp->path_id == oldpid)
            break;
    }
    
    // to mark it visited
    v_temp->visited[thiscave]++;
    
    int nextcave;
    
    // to go through this current cave's list of connected caves
    for(int i=0;i<cave[thiscave].connection_count;i++)
    {
        //we dont want to go back to 'start'
        if(strcmp(cave[thiscave].connection[i], "start")==0)
            continue;
        
        //to find the next cave in the list to move to, by its id number
        for(int j=0;j<caveindex;j++)
            if(strcmp(cave[thiscave].connection[i], cave[j].name)==0)
            {
                nextcave=j;
                break;
            }
        
        //increase the path id
        pid++;
        
        //we need to create a new link in the chain where we keep
        //the information about the current path's list of visited caves
        v_current->next = malloc(sizeof(struct pathnode));
        v_temp = v_current;
        v_current = v_current->next;
        v_current->prev = v_temp;
        v_current->path_id = pid;
        v_current->next = NULL;
        
        //to find the path id of the parent path
        v_temp = v_root;
        while(v_temp!=NULL)
        {
            v_temp = v_temp->next;
            if(v_temp->path_id == oldpid)
                break;
        }

        //to copy the parent path's visited list onto the child path's visited list
        for(int j=0;j<LISTLEN;j++)
            v_current->visited[j] = v_temp->visited[j];

        if(cave[nextcave].name[0]>='a' && cave[nextcave].name[0]<='z')
            if(v_current->visited[nextcave])
                continue;
        
        // if this is the last round in our list of connected caves
        // then let's remove and free the oldpid's associated node
        // from the chain
        
        if(i==cave[thiscave].connection_count-1)
        {
            v_temp=v_root;
            while(v_temp!=NULL)
            {
                v_temp=v_temp->next;
                if(v_temp->path_id == oldpid)
                {
                    v_temp->prev->next = v_temp->next;
                    free(v_temp);
                }
            }
        }
        
        // the function calls itself, the pid becomes oldpid next time
        move_to_caves(nextcave, pid);
        
    }
    

    // if we reach here, then this is a dead end
    // we free the current path's visited stack

    v_temp=v_root;
    while(v_temp!=NULL)
    {
        v_temp=v_temp->next;
        if(v_temp->path_id == oldpid)
        {
            v_temp->prev->next = v_temp->next;
            free(v_temp);
        }
    }
        
    return;
}

