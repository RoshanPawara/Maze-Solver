#include<conio.h>
#include<stdio.h>
#include<graphics.h>
#include<iostream.h>
#include<stdlib.h>              // included for using exit() function
#include<dos.h>
#define size 1600
#define Up *(maze+(row-1)*n+col)
#define Down *(maze+(row+1)*n+col)
#define Left *(maze+(row)*n+(col-1))
#define Right *(maze+(row)*n+(col+1))


struct stack
{
	char a[size];
	int top;
};
typedef struct stack st;

int StackFull(st *s)
{
  if(s->top==size-1)
     return 1;
  else
     return 0;
}

int StackEmpty(st *s)
{
  if(s->top==0)
    return 1;
  else
    return 0;
}

char pop(st *s)
{
  char LastMove;
  if(StackEmpty(s))
    {
//      printf("Stack Empty.");
	outtextxy(10,460,"Solution does not exist.");
      getch();
      exit(1);
    }
  else
   {
      LastMove=s->a[s->top];
      s->top--;
      return LastMove;
   }////////else ends
}

void push(st *s,char direction)
{
  if(StackFull(s))
  {
    printf("Stack Full.");
    getch();
    exit(1);
	//break;
  }
 else
  {
    s->top++;
	///////elements to be pushed on the stack
	if(direction=='U')
	{

		s->a[s->top]='U';
//		gotoxy(2,5);
//		printf("Dir: U");
	}
	else if(direction=='D')
	{
		s->a[s->top]='D';
//		gotoxy(2,5);
//		printf("Dir: %c",s->a[s->top]);
	}

	else if(direction=='L')
	{
		s->a[s->top]='L';
//		gotoxy(2,5);
//		printf("Dir: L");
	}

	else if(direction=='R')
	{
		s->a[s->top]='R';
//		gotoxy(2,5);
//		printf("Dir: R");
	}
	//////////////
  }
}

void CreateStack(st *s)
{
	s->top=-1;
}

void Draw_maze(int x,int y,int status,int n)
{
	int xx=120+(10*x);
	int yy=45+(10*y);
	if(status==1)
	{
		setcolor(3);
		rectangle(xx,yy,xx+10,yy+10);
		setfillstyle(1,3);
		floodfill(xx+5,yy+5,3);
	}
	if(x==1 && y==1)
	outtextxy(xx+2,yy+2,"S");
	if(x==n-2 && y==n-2)
	outtextxy(xx+2,yy+2,"E");
}

void solvemaze(int *,st *,int);///parameters are 1.address of maze array, 2. Stack address, 3. dimension of the maze
void player(int,int,int);////parameters are x and y
void introScreen();
void main()
{
	st *s;
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"c:/turboc3/bgi");
	//1 is for wall
	//0 is for path
introScreen();
getch();
cleardevice();
rectangle(0,0,639,479);
int maze[39][39]={{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1 ,1 ,1 ,1 ,1 ,1, 1 ,1 ,1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1 },
		{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 ,0, 0 ,1 },
		{1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1 ,1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1 ,1 ,0 ,1 },
		{1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 ,0 ,0 ,1 },
		{1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1 ,0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1 ,1, 1 },
		{1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1 ,0, 0, 0, 1, 0, 0, 0, 1 ,0, 0, 0 ,0, 0 ,1 },
		{1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1 ,1, 0 ,1},
		{1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0 ,0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0 ,1},
		{1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0 ,1},
		{1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 ,1 ,0 ,1},
		{1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1 ,1 ,0 ,1},
		{1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 ,1},
		{1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 ,1},
		{1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0 ,1},
		{1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0 ,1},
		{1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0 ,1},
		{1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1 ,0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0 ,1},
		{1 ,0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 ,0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0 ,1},
		{1, 0, 1, 0, 1, 1, 1, 1, 1 ,0, 1, 0, 1 ,1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0 ,1},
		{1, 0, 1, 0, 0, 0, 0, 0, 0 ,0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1 ,0, 1 ,0, 0,0 ,1},
		{1 ,0, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1 ,1, 1 ,1, 1, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,0, 0 ,0, 0, 0, 1},
		{1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1},
		{1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 ,1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
		{1, 0, 0, 0, 0 ,0 ,1 ,0 ,0, 0, 0, 0 ,1, 0, 0, 0, 0 ,0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1},
		{1, 0, 1 ,0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 1, 0, 0, 0 ,0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
		{1, 0, 1 ,0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1},
		{1, 0, 0 ,0 ,1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1 ,1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
		{1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1 ,1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1 ,0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
		{1 ,0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1}};
int i,j,row,col,n=39;
	for(i=0;i<39;i++)
	{
		for(j=0;j<39;j++)
			Draw_maze(j,i,maze[i][j],39);
	}
	/*	printf("Enter Size of Maze matrix:\n");
	printf("Rows: ");
	scanf("%d",&row);
	printf("Cols: ");
	scanf("%d",&col);
	printf("Enter maze matrix:\n");*/
      /*	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
			scanf("%d",&maze[i][j]);
	}
	cleardevice();   */
	for(i=0;i<39;i++)
	{
		for(j=0;j<39;j++)
			Draw_maze(j,i,maze[i][j],n);
	}
	CreateStack(s);
solvemaze(&maze[0][0],s,n);
getch();
}////////////main ends

void solvemaze(int *maze,st *s,int n)////////n is the dimension of the maze
{
	int visited[39][39]={0};
	int row=0,col=1;
	char backtrack;
	//printf("%d ",*(maze+2*n+1));
	outtextxy(10,460,"Press any key to start.");
	getch();
	setcolor(14);//////////erasing previous message on the screen
	rectangle(8,458,200,475);
	setfillstyle(1,0);
	floodfill(15,465,14);
	setcolor(0);
	rectangle(8,458,200,475);///////////end

//	player(row,col,14);//////to display the player at starting position
	while(1)
	{
// 		gotoxy(2,2);
//		printf("Row: %d		Col: %d",row,col);
//		gotoxy(2,3);
//		printf("top: %d",s->top);
//		gotoxy(2,4);
//		printf("visited: %d",visited[3][1]);
		if(row==n-2 && col==n-2)///////////Destination reached condition
		{
			outtextxy(10,460,"Solution Exists.");
			getch();
			exit(1);
		}
delay(60);
		if(Down==0 && !visited[row+1][col])///checking path DOWN
		{
			push(s,'D');
//			player(++row,col,4);
			visited[++row][col]=1;
		}

		else if(Right==0 && !visited[row][col+1])///checking path RIGHT
		{
			push(s,'R');
//			player(row,++col,6);
			visited[row][++col]=1;
		}

		else if(Up==0 && !visited[row-1][col]) ///checking path UP
		{
			push(s,'U');
//			player(--row,col,12);
			visited[--row][col]=1;
		}
		else if(Left==0 && !visited[row][col-1])///checking path LEFT
		{
			push(s,'L');
//			player(row,--col,5);
			visited[row][--col]=1;
		}
		else
		{
			gotoxy(2,4);
//			printf("Already visited.");
			backtrack=pop(s);
			player(row,col,0);///////////for erasing the current position before backtracking
			switch(backtrack)/////then erasing the backtracked position
			 {
				case 'D':row--;
					break;
				case 'R':col--;
					break;
				case 'U':row++;
					break;
				case 'L':col++;
					break;
				default: break;
			 }
		}
		player(row,col,14);
	}/////////////////////while loop ends.
}

void player(int i,int j,int color)
{
	int xx=120+(10*j);
	int yy=45+(10*i);
	if(color==0)
	{
		setcolor(0);
		rectangle(xx+1,yy+1,xx+9,yy+9);
		setfillstyle(1,color);
		floodfill(xx+5,yy+5,0);
	}
	else
	{
		setcolor(14);
		rectangle(xx+1,yy+1,xx+9,yy+9);
		setfillstyle(1,14);
		floodfill(xx+5,yy+5,14);
	}
}

void introScreen()/////////////////Drawing screen 1
{
int tx=0,ty=0;
setcolor(14);
rectangle(0,0,639,479);////////////border
line(105+tx,155+ty,149+tx,155+ty);//////////////////M start
line(149+tx,155+ty,171+tx,188+ty);
line(171+tx,188+ty,193+tx,155+ty);
line(193+tx,155+ty,236+tx,155+ty);
line(236+tx,155+ty,236+tx,212+ty);///////////////////////////end point is the intersection for M and A

line(105+tx,155+ty,105+tx,269+ty);
line(105+tx,269+ty,144+tx,269+ty);
line(144+tx,269+ty,144+tx,206+ty);
line(144+tx,206+ty,171+tx,247+ty);
line(171+tx,247+ty,198+tx,206+ty);
line(198+tx,206+ty,198+tx,269+ty);
line(198+tx,269+ty,528+tx,269+ty);///////////////bottom long line
///////////////////M ends

////////////////////////////////////////////////////////////A start
line(218+tx,242+ty,231+tx,269+ty);////////////////////left most bottom line of A\
line(274+tx,155+ty,305+tx,155+ty);
line(274+tx,155+ty,218+tx,242+ty);
line(218+tx,242+ty,303+tx,242+ty);
line(303+tx,242+ty,287+tx,209+ty);
line(287+tx,209+ty,273+tx,229+ty);
line(296+tx,229+ty,258+tx,229+ty);//////////////////outer triangle base line
line(258+tx,229+ty,305+tx,155+ty);
line(305+tx,155+ty,347+tx,243+ty);
line(347+tx,243+ty,332+tx,269+ty);
line(332+tx,269+ty,295+tx,196+ty);//////////////upper point of left triangle
line(295+tx,196+ty,287+tx,209+ty);
////////////////////////////////////////////////////////////A ends


/////////////////////////////////////////////////////////////////////////////Z begins
line(335+tx,155+ty,528+tx,155+ty);////////////////////////////////upper long line
line(335+tx,155+ty,335+tx,188+ty);
line(335+tx,188+ty,376+tx,188+ty);
line(376+tx,188+ty,340+tx,226+ty);
line(429+tx,186+ty,382+tx,236+ty);
line(382+tx,236+ty,429+tx,236+ty);
//////////////////////////////////////////////////intersection of Z and A


////////////////////////////////////////////////////////Z ends
////////////////////////////////////////////////////////////E start
line(528+tx,155+ty,509+tx,191+ty);
line(509+tx,191+ty,468+tx,191+ty);
line(468+tx,191+ty,468+tx,203+ty);
line(468+tx,203+ty,503+tx,203+ty);
line(503+tx,203+ty,503+tx,222+ty);
line(503+tx,222+ty,468+tx,222+ty);
line(468+tx,222+ty,468+tx,236+ty);
line(468+tx,236+ty,513+tx,236+ty);
line(513+tx,236+ty,528+tx,269+ty);
line(429+tx,155+ty,429+tx,269+ty);////////////////line between Z and E
////////////////////////////////////////////////////////////E ends

settextstyle(0,0,3);
outtextxy(250,273,"SOLVER");

settextstyle(11,0,3);
outtextxy(430,443,"Developer: Roshan Pawara");
outtextxy(340,455,"(Vishwakarma Institue of Technology)");
}



