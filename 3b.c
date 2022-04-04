#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 16

int binary2decimal(char word[]);
int power(int a, int b);

void main(int argc, char *argv[])
{
    if(argc==1)
    {
        printf("need filename as parameter\n");
        exit(0);
    }
    
    FILE *fp;
    fp=fopen(argv[1],"r");
    
    if(fp==NULL)
    {
        printf("file open error\n");
        exit(0);
    }
    
    char line[LEN];
    int linecount=0;
    
    while(fgets(line,LEN,fp)!=NULL)
    {
        if(strlen(line)<2)
            continue;
        linecount++;
    }
    
    
    rewind(fp);
    
    int k=0;  
    int len;
    char lines[linecount][LEN];
    
    while(fgets(line,LEN,fp)!=NULL)
    {
        len=strlen(line);
        if(len<2) continue;
        if(line[len-1]=='\n' || line[len-1]==EOF)
            line[len-1]='\0';
        
        strcpy(lines[k++], line);
    }
    
    fclose(fp);
    
    int tracklist[linecount];
    
    for(int i=0;i<linecount;i++)
        tracklist[i]=1;
    
    int trackcount=linecount;
    k=0;   
    
    int count;   
    char m;
    
    while(trackcount>1)
    {
        count=0;
        for(int i=0;i<linecount;i++)
            if(tracklist[i])
                if(lines[i][k]=='1')
                    count++;
  
        if(count>=(double)trackcount/2) 
            m='1';
        else 
            m='0';
        
        for(int i=0;i<linecount;i++)
            if(tracklist[i])
                if(lines[i][k]!=m)
                {
                    tracklist[i]=0;
                    trackcount--;
        
                }

        k++;
    }
    
    int oxygen;
    for(int i=0;i<linecount;i++)
        if(tracklist[i])
            oxygen=binary2decimal(lines[i]);
    
    for(int i=0;i<linecount;i++)
        tracklist[i]=1;
    
    trackcount=linecount;
    k=0;
    
    while(trackcount>1)
    {
        count=0;
        for(int i=0;i<linecount;i++)
            if(tracklist[i])
                if(lines[i][k]=='0')
                    count++;
  
        if(count>(double)trackcount/2) 
            m='1';
        else 
            m='0';
        
        for(int i=0;i<linecount;i++)
            if(tracklist[i])
                if(lines[i][k]!=m)
                {
                    tracklist[i]=0;
                    trackcount--;
        
                }

        k++;
    }
    
    int co2;
    for(int i=0;i<linecount;i++)
        if(tracklist[i])
            co2=binary2decimal(lines[i]);
            
    printf("%d * %d = %d\n",oxygen,co2, oxygen*co2);
    
    return;
}
                
int power(int a, int b)
{
    int sum=1;
    for(int i=0;i<b;i++)
        sum *= a;
    return sum;
}

int binary2decimal(char word[])
{
    int k=0;
    int len=strlen(word);
    int sum=0;
    for(int i=len-1;i>=0;i--)
    {
        sum += (word[i]-'0') * power(2,k);
        k++;
    }
    return sum;
}
