#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define LEN 128
#define GRIDSIZE 100



struct node {
	int x;
	int y;
	struct node* next;
};


// the grid
int m[GRIDSIZE][GRIDSIZE];

	

int max1=0,max2,max3;

int countlist[500];
int countindex=0;


void find_basin(int x, int y);
void move_in_basin(struct node* root, int x, int y);
int check_available(struct node* root, int x, int y);
int is_added(struct node* root, int x, int y);
void add_to_chain(struct node* root, int x, int y);
struct node* newchain(int x, int y);
void find_low_point();



void main()
{
	char line[LEN];
	int len;
	int k=0;
  
  
	while(fgets(line,LEN,stdin)!=NULL)
	{
		len=strlen(line);
		if(len<2) continue;
		for(int i=0;i<GRIDSIZE;i++)
			m[k][i]=line[i]-'0';
		k++;
	}

  
	find_low_point();
		
	int max1,max2,max3;
	max1=max2=max3=0;
    for(int i=0;i<countindex;i++)
    	if(countlist[i]>max1)
    		max1=countlist[i];
    for(int i=0;i<countindex;i++)
    	if(countlist[i]>max2 && countlist[i]!=max1)
    		max2=countlist[i];
    for(int i=0;i<countindex;i++)
    	if(countlist[i]>max3 && countlist[i]!=max1 && countlist[i]!=max2)
    		max3=countlist[i];

  	printf("%d * %d * %d = %d\n",max1,max2,max3,max1*max2*max3);
	return;
}




void find_low_point()
{
  
  // checking the input grid for the middle part
  // excluding the outermost 4 edges
	for(int i=1;i<GRIDSIZE-1;i++)
		for(int j=1;j<GRIDSIZE-1;j++)
			if(m[i][j]<m[i+1][j] &&
				m[i][j]<m[i-1][j] &&
				m[i][j]<m[i][j+1] &&
				m[i][j]<m[i][j-1])
					find_basin(i, j);
 
  
  //checking the four edges
  // edge 1
	for(int i=1;i<GRIDSIZE-1;i++)
		if(m[0][i]<m[0][i-1] &&
			m[0][i]<m[0][i+1] &&
			m[0][i]<m[1][i])
				find_basin(0, i);
  //edge 2
	for(int i=1;i<GRIDSIZE-1;i++)
		if(m[GRIDSIZE-1][i]<m[GRIDSIZE-1][i-1] &&
			m[GRIDSIZE-1][i]<m[GRIDSIZE-1][i+1] &&
			m[GRIDSIZE-1][i]<m[GRIDSIZE-2][i])
				find_basin(GRIDSIZE-1, i);
  //edge 3
	for(int i=1;i<GRIDSIZE-1;i++)
		if(m[i][0]<m[i-1][0] &&
			m[i][0]<m[i+1][0] &&
			m[i][0]<m[i][1])
				find_basin(i, 0);
  //edge 4
	for(int i=1;i<GRIDSIZE-1;i++)
		if(m[i][GRIDSIZE-1]<m[i-1][GRIDSIZE-1] &&
			m[i][GRIDSIZE-1]<m[i+1][GRIDSIZE-1] &&
			m[i][GRIDSIZE-1]<m[i][GRIDSIZE-2])
				find_basin(i, GRIDSIZE-1);
	
  
  //checking for the 4 corners
  //corner 1
	if(m[0][0]<m[1][0] && m[0][0]<m[0][1])
		find_basin(0, 0);
  //corner 2
	if(m[0][GRIDSIZE-1]<m[0][GRIDSIZE-2] && m[0][GRIDSIZE-1]<m[1][GRIDSIZE-1])
		find_basin(0, GRIDSIZE-1);
  //corner3
	if(m[GRIDSIZE-1][0]<m[GRIDSIZE-2][0] && m[GRIDSIZE-1][0]<m[GRIDSIZE-1][1])
		find_basin(GRIDSIZE-1, 0);
  //corner 4
	if(m[GRIDSIZE-1][GRIDSIZE-1]<m[GRIDSIZE-1][GRIDSIZE-2] && m[GRIDSIZE-1][GRIDSIZE-1]<m[GRIDSIZE-2][GRIDSIZE-1])
		find_basin(GRIDSIZE-1, GRIDSIZE-1);

	return;
}




struct node* newchain(int x, int y)
{
	struct node* root=malloc(sizeof(struct node));
	root->x=x;
	root->y=y;
	root->next=NULL;
  
	return root;
}




void add_to_chain(struct node* root, int x, int y)
{
	while(root->next!=NULL)
		root=root->next;

	root->next=malloc(sizeof(struct node));
	root=root->next;
	root->x=x;
	root->y=y;
	root->next=NULL;
	
	return;
}





int is_added(struct node* root, int x, int y)
{
	while(root!=NULL)
	{
		if(root->x==x && root->y==y)
			return 1;
		
		root=root->next;
	}
	
	return 0;
}
		



int check_available(struct node* root, int x, int y)
{
	// edges of grid
	if(x<0 || y<0) return 0;
	if(x>=GRIDSIZE || y>=GRIDSIZE) return 0;
	
	// 9 is the basin edge
	if(m[x][y]==9) return 0;
	
	// if already added
	if(is_added(root, x, y))
		return 0;

	// not added
	add_to_chain(root, x, y);
	return 1;
}
			
	



void move_in_basin(struct node* root, int x, int y)
{
	//four sides: up down right and left
	
	if(check_available(root, x-1, y))
		move_in_basin(root, x-1, y);
	
	if(check_available(root, x+1, y))
		move_in_basin(root, x+1, y);
	
	if(check_available(root, x, y-1))
		move_in_basin(root, x, y-1);
	
	if(check_available(root, x, y+1))
		move_in_basin(root, x, y+1);
	
	return;
}

void find_basin(int x, int y)
{
	// new low point found
	// recursive function move_in_basin() will
	// search inside the 'basin'
	//
	// a new linked link for each new low point 
	// will keep track of all the visited squares
	
	struct node* root = newchain(x, y);
	
	// recursive function
	move_in_basin(root, x, y);

	// count of the squares in basin
	// the size of this basin
	int count=0;
	while(root!=NULL)
	{
		count++;
		root=root->next;
	}
	
	free(root);
	
	countlist[countindex++]=count;
		
	return;
	
}
