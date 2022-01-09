#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128
#define SQUARESIZE 10

void move(int x, int y, int pile);

int m[SQUARESIZE][SQUARESIZE];
int bestscore=0;

void main()
{
    char line[LINESIZE];
    int k=0;
    while(fgets(line,LINESIZE,stdin)!=NULL)
    {
        if(strlen(line)<2) continue;
        for(int i=0;i<SQUARESIZE;i++)
            m[k][i]=line[i]-'0';
        k++;
    }
    
    for(int i=0;i<SQUARESIZE;i++)
    {
        for(int j=0;j<SQUARESIZE;j++)
            printf("%d",m[i][j]);
        printf("\n");
    }
    
    move(0,0,0);
    
    return;
}



void move(int x, int y, int pile)
{   
    pile += m[x][y];
    if(x==SQUARESIZE-1 && y==SQUARESIZE-1)
    {
        if(pile<bestscore)
        {
            printf("new best score: %d\n",pile);
            bestscore=pile;
        }
    }
    
    if(x>0)
        move(x-1, y, pile);
    if(x<SQUARESIZE-2)
        move(x+1, y, pile);
    if(y>0)
        move(x, y-1, pile);
    if(y<SQUARESIZE-2)
        move(x, y+1, pile);
    
    return;
    
}
