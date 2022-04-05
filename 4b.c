#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LEN 512
#define CARDSMAX 100

int count_card_score(int mark[5][5], int card[5][5]);
int check_for_bingo(int x, int y, int mark[5][5], int card[5][5]);

void main()
{
    char line[LEN];
    fgets(line,LEN,stdin);
    int commacount=1;
    int len=strlen(line);
    for(int i=0;i<len;i++)
        if(line[i]==',')
            commacount++;
            
    int numbers[commacount];
    int k=0;
    char *token;
    token=strtok(line,",");
    while(token!=NULL)
    {
        numbers[k++]=atoi(token);
        token=strtok(NULL,",");
    }
    
    int card[5][5];
    int mark[5][5];
    int cardscore[CARDSMAX];
    int max=0;
    int min=commacount;
    int realcardscore[CARDSMAX];
    int maxscore, minscore;

    for(int cardno=0;cardno<CARDSMAX;cardno++)
    {
        for(int x=0;x<5;x++)
            for(int y=0;y<5;y++)     
                mark[x][y]=0;
                
        if(fgets(line,LEN,stdin)==NULL) break;
        for(int i=0;i<5;i++)
        {
            fgets(line,LEN,stdin);
            token=strtok(line," ");
            for(int j=0;j<5;j++)
            {
                card[i][j]=atoi(token);
                token=strtok(NULL," ");
            }
        }

        
        for(int i=0;i<commacount;i++)
            for(int x=0;x<5;x++)
                for(int y=0;y<5;y++)
                    if(numbers[i]==card[x][y])
                    {
                        mark[x][y]=1;

                        if(check_for_bingo(x,y,mark,card))
                        {
                            cardscore[cardno]=i;
                            realcardscore[cardno]=count_card_score(mark,card);
                            realcardscore[cardno] *= numbers[i];
                            goto outofloop;
                        }
                    }
        outofloop:
        if(cardscore[cardno]>max)
        {
            max=cardscore[cardno];
            maxscore=realcardscore[cardno];
        }
        if(cardscore[cardno]<min)
        {
            min=cardscore[cardno];
            minscore=realcardscore[cardno];
        }
        
    }
        
    printf("last to win:%d\nfirst to win:%d\n",maxscore,minscore);
    
    return;
}

int count_card_score(int mark[5][5], int card[5][5])
{
    int sum=0;
    for(int x=0;x<5;x++)
        for(int y=0;y<5;y++)
            if(mark[x][y]==0)
                sum+=card[x][y];
    return sum;
}

int check_for_bingo(int x, int y, int mark[5][5], int card[5][5])
{
    int bingo1=1;
    int bingo2=1;
    for(int i=0;i<5;i++)
    {
        if(!mark[x][i])
            bingo1=0;
        if(!mark[i][y])
            bingo2=0;
    }

    return bingo1 || bingo2;
}
