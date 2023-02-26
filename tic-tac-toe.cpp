#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include <stdbool.h>
#include <time.h>

#define WIDTH 450
#define HEIGHT 410
#define GRID_SIZE 150
#define MOVE_TIMER 9      // number of seconds for each player's turn


int board[3][3]; // matrix to keep track of moves
bool currentPlayer= true; // true represents first player, false represents second player
int playerSymbol[3] = {0, 1, 2};
int player1Choice, player2Choice;
time_t start,end;


// Function to allow players to choose their symbol
void chooseSymbol() {
    printf("Player 1, choose your symbol (1 for X, 2 for O): \n");
    scanf("%d", &player1Choice);
    while (player1Choice != 1 && player1Choice != 2) {
        printf("Invalid choice. Please choose 1 for X or 2 for O: \n");
        scanf("%d", &player1Choice);
    }
    player2Choice = playerSymbol[3 - player1Choice];
    printf("Player 1 chose %c and Player 2 chose %c\n", (player1Choice == 1) ? 'X' : 'O', (player2Choice == 1) ? 'X' : 'O');
    printf("Press any key to start the game\n");
    _getch();
    cleardevice();
}

//Function to draw a board 
void drawLine()
{
   setbkcolor(LIGHTBLUE);
   cleardevice();
   setcolor(WHITE);
   line(GRID_SIZE, 0, GRID_SIZE, HEIGHT);
   line(2 * GRID_SIZE, 0, 2 * GRID_SIZE, HEIGHT);
   line(0, GRID_SIZE, WIDTH, GRID_SIZE);
   line(0, 2 * GRID_SIZE, WIDTH, 2 * GRID_SIZE);
}

//Function to draw a circle in a board
void drawCircle(int row, int col)
{
   setcolor(BLUE);
   circle(row,col,GRID_SIZE/4);
   //ellipse(x, col, 0, 360, GRID_SIZE / 3, GRID_SIZE / 3); 
}

//Function to draw cross in a board
void drawCross(int row, int col)
{
   setcolor(BLACK);  //Turquoise
   line(row - GRID_SIZE / 6, col - GRID_SIZE / 6, row + GRID_SIZE / 6, col + GRID_SIZE / 6); //   drawing \    //
   line(row - GRID_SIZE / 6 + 1, col + GRID_SIZE / 6 + 1, row + GRID_SIZE / 6 + 1, col - GRID_SIZE / 6 + 1); //   drawing /    //
}

//Function to check for winning conditions 
int checkWin()
{
   // check rows
   for(int i=0;i<3;i++)
   {
      if(board[i][0]==board[i][1] && board[i][1]==board[i][2] && board[i][0]!=0)
         {
            setcolor(RED);
            line(37.5,150*i+75,150*2+112.5,150*i+75); 
            return board[i][0];
         }
   }

   // check columns
   for(int i=0;i<3;i++)
   {
      if(board[0][i]==board[1][i] && board[1][i]==board[2][i] && board[0][i]!=0)
         {
            setcolor(RED);
            line(150*i+75,37.5,150*i+75,150*2+112.5); 
            return board[0][i];
         }
   }

   // check diagonals
   if(board[0][0]==board[1][1] && board[1][1]==board[2][2] && board[0][0]!=0)
      {
         setcolor(RED);
         line(50,50,400,400);
         return board[0][0];
      }
   if(board[0][2]==board[1][1] && board[1][1]==board[2][0] && board[0][2]!=0)
      {
         setcolor(RED);
         line(50,400,400,50);
         return board[0][2];
      }
   // check draw
   for(int i=0;i<3;i++)
   {
      for(int j=0;j<3;j++)
      {
         if(board[i][j]==0)
            return 0;
      }
   }
   return -1;
}

//Function to initialize the game 
void playGame()
{
   int x=0,y=0;
   for(int i=0;i<3;i++)
   {
      for(int j=0;j<3;j++)
      {
          board[i][j]=0;
      }
   }
   while(1)
   {
      if(ismouseclick(WM_LBUTTONDOWN))
      {
      a: clearmouseclick(WM_LBUTTONDOWN);
         x=mousex();
         y=mousey();
         if(x>=0 && x<=WIDTH && y>=0 && y<=HEIGHT)
         {
            int row=0,col=0;
            if(x>0 && x<=GRID_SIZE) col=0;
            else if(x>GRID_SIZE && x<=(2*GRID_SIZE)) col=1;
            else if(x>(2*GRID_SIZE) && x<=WIDTH) col=2;
           
            if(y>0 && y<=GRID_SIZE) row=0;
            else if(y>GRID_SIZE && y<=(2*GRID_SIZE)) row=1;
            else if(y>(2*GRID_SIZE) && y<=HEIGHT) row=2;

            if(board[row][col]==0)
            {
               int now;
               if(currentPlayer == true)
                  {now = 1;}
               else
                  {now = 2; }     
               board[row][col]=now;      //updating player's choice in matrix
             
              //to check which player drawing cricle or cross
               x = col*150+75;
               y= row*150+75;
               int elapsed;
               time(&start);
               int symbol = (currentPlayer == true) ? player1Choice : player2Choice;
               if(symbol==1)
               {
                  drawCross(x,y);
                  currentPlayer = !currentPlayer;
               }
               else
               {
                  drawCircle(x,y);
                  currentPlayer = !currentPlayer;
               }

               int  result=checkWin();
               if(result!=0)
               {
                  char message[25];
                  setcolor(RED);
                  if(result==-1)
                  {
                     sprintf(message,"Draw");
                     outtextxy(190,430,message);     
                     sprintf(message,"Press Esc to cancel or Space to replay");
                     outtextxy(130,450,message);
                     sprintf(message,"  ");
                     outtextxy(10, 10,message);     
                  }
                  else
                  {
                     sprintf(message,"Player %d wins",result);
                     outtextxy(190,440,message);
                     sprintf(message,"Press Esc to cancel or Space to replay");
                     outtextxy(130,460,message);
                     sprintf(message,"  ");
                     outtextxy(10, 10,message);     
                  }
                  break;
               }

               while (1) // wait until the MOVE_TIMER has passed
               {
                  time(&end);    //detects the ed time for first move 
                  elapsed = difftime(end, start);
                  char timer[5];
                  int t_now = MOVE_TIMER - elapsed;
                  if(t_now < 0)
                  {
                     char message[25];
                     setcolor(RED);
                     sprintf(message,"Time's Up !!!");
                     outtextxy(190,420,message);
                     sprintf(message,"Player %d wins",now);
                     outtextxy(190,440,message);
                     sprintf(message,"Press Esc to cancel or Space to replay");
                     outtextxy(130,460,message); 
                     goto timeup;
                  }
                  sprintf(timer, "%d", t_now);
                  outtextxy(10, 10, timer); // display the remaining time
                  if (ismouseclick(WM_LBUTTONDOWN)) 
                  {
                     time(&start); // reset the start time when the player makes a move
                     goto a;
                  }
                  delay(998);
               }  
            }
         }
         // break;
      }
   }
timeup: delay(0.1);
}

int main()
{
   int gd=DETECT,gm;
   char re;
   char message[25];
   initgraph(&gd,&gm,(char*)"");  
   re = 32;
   while(1)
   {
      setcolor(RED);
      if(re == 32)
      {
         cleardevice();
         chooseSymbol();
         drawLine();
         playGame();
         currentPlayer = true;  //resseting every time to first player 1
         printf("Press Esc to cancel or Space to replay\n");
         re = _getch();
      }
      else if(re == 27)
      {
         break;
      }
      else
      {
         printf("Invalid choice!!!\nPress Esc to cancel or Space to replay\n");
         re = _getch();
      }
   }
   cleardevice();
   closegraph();
   return 0;
}
