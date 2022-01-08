#include<stdio.h>

int m[10][10];
int flashcount=0;

void check_for_flashes();
void flash_it();
void increase_each();

void flash_it(int i, int j)
{
    if(i>0)
    {
        if(m[i-1][j]) m[i-1][j]++;
        if(j>0)
            if(m[i-1][j-1]) m[i-1][j-1]++;
        if(j<9)
            if(m[i-1][j+1]) m[i-1][j+1]++;
    }

    if(j>0)
        if(m[i][j-1]) m[i][j-1]++;
    if(j<9)
        if(m[i][j+1]) m[i][j+1]++;
    
    if(i<9)
    {
        if(m[i+1][j]) m[i+1][j]++;
        if(j>0)
            if(m[i+1][j-1]) m[i+1][j-1]++;
        if(j<9)
            if(m[i+1][j+1]) m[i+1][j+1]++;
    }
    
    m[i][j]=0;
    flashcount++;
    check_for_flashes();
    
    return;
}


void check_for_flashes()
{
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
            if(m[i][j]>9)
                flash_it(i,j);
    return;
}



void increase_each()
{
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
            m[i][j]++;
    
    check_for_flashes();
    
    return;
}


int main() {
   
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
            m[i][j]=getchar()-'0';
        getchar();
    }
    
    for(int step=0;step<100;step++)
        increase_each();
        
    printf("%d\n",flashcount);
    
    return 0;
}
