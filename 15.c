#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128
#define SQUARESIZE 100

void move(int x, int y, int pile, int fromx, int fromy);

int m[SQUARESIZE][SQUARESIZE];
unsigned int bestscore=0-1;

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
   
    
    move(0,0,0,-1,-1);
    
    return;
}



void move(int x, int y, int pile, int fromx, int fromy)
{   
    if(!(x==0&&y==0))
    	pile += m[x][y];
    if(x==SQUARESIZE-1 && y==SQUARESIZE-1)
    {
        if(pile<bestscore)
        {
            printf("new best score: %d\n",pile);
            bestscore=pile;
        }
        return;
    }

 /* if(x>0 && fromx!=x-1)
        move(x-1, y, pile, x, y);    */     
    
    if(x<SQUARESIZE-1 && fromx!=x+1)
        move(x+1, y, pile, x, y);
   
 /* if(y>0 && fromy!=y-1)
        move(x, y-1, pile, x, y);     */ 
    
    if(y<SQUARESIZE-1 && fromy!=y+1)
        move(x, y+1, pile, x, y);
    
    return;
    
}
