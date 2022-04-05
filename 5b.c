#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN 64
#define SIZE 1000

void main()
{
    char line[LEN];
    char *firsthalf,*secondhalf;
    int x1,x2,y1,y2;
    int grid[SIZE][SIZE];
    for(int i=0;i<SIZE;i++)
        for(int j=0;j<SIZE;j++)
            grid[i][j]=0;
    
    while(fgets(line,LEN,stdin)!=NULL)
    {
        int len=strlen(line);
        if(len<2) continue;
        if(line[len-1]=='\n' || line[len-1]==EOF)
            line[len-1]='\0';
            
        firsthalf=strtok(line," -> ");
        secondhalf=strtok(NULL," -> ");
        
        x1=atoi(strtok(firsthalf,","));
        y1=atoi(strtok(NULL,","));
        
        x2=atoi(strtok(secondhalf,","));
        y2=atoi(strtok(NULL,","));
        
        int minx, maxx;
        int miny, maxy;
        
        if(x1>x2)
        {
            maxx=x1;
            minx=x2;
        }
        else
        {
            maxx=x2;
            minx=x1;
        }
        
        if(y1>y2)
        {
            maxy=y1;
            miny=y2;
        }
        else
        {
            maxy=y2;
            miny=y1;
        }
        
        if(x1==x2)
            for(int i=miny;i<=maxy;i++)
                grid[x1][i]++;
        
        else if(y1==y2)
            for(int i=minx;i<=maxx;i++)
                grid[i][y1]++;
        
        else if(x1<x2 && y1<y2 || x1>x2 && y1>y2)
            for(;minx<=maxx;minx++,miny++)
                grid[minx][miny]++;
        
        else
            for(;miny<=maxy;maxx--,miny++)
                grid[maxx][miny]++;
        
    }
    
    int sum=0;
    for(int i=0;i<SIZE;i++)
        for(int j=0;j<SIZE;j++)
            if(grid[i][j]>1)
                sum++;
    
    printf("%d\n",sum);
    return;
}
            
