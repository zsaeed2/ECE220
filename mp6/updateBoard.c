/* Zayd Saeed	zsaeed2		MP6	7 March 2019
* The purpose of this program is to simulate an old and relatively famous game: The game 
* of life. It is a 2 dimensional orthoganal grid of square cells, each of which has one of
* two possible states: alive or dead. It is governed by 4 rules: a cell with fewer than 2
* neigbors dies by underpopulation; a cell with 2 or 3 live neighbors lives on; a cell with 
* more than 3 live neighbors dies due to overpopulation; a cell with exactly 3 neigbors 
* becomes alive by reproduction. Our task was to implement these four rules and we did that
* using the algorithms given to us in the MP description, pointers, for loops, and conditional
* statements. 
* Partners: Srajag9 aliesas2
*/
#include <stdio.h>
/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col)
  { //opening bracket
int i;			//variable names and initialization
int j;
int toprow = 0;
int bottomrow = 0;
int rightcol  = 0;
int leftcol = 0;
int edgeorcor = 0;
int neighborcount = 0;
     if(row == boardRowSize-1) //test for neighbors and to revive different layers of cells
    {
        bottomrow = 1;
        edgeorcor = 1;
    }
     if(row == 0)
    {
      toprow = 1;
        edgeorcor = 1;
    }
     if(col == boardColSize-1)
     {
      rightcol = 1;
        edgeorcor = 1;
     }
     if(col == 0)
     {
       leftcol = 1;
        edgeorcor = 1;
      }
  if(edgeorcor == 0) //not edge or corner
  {
    //printf("not edge or corner \n");
    for (i = -1; i<2; i++) // runs tests for edges and corners
    {
      for (j = -1; j <2; j++)
      {
        if (j ==0 && i == 0)
        {
          continue;
        }
        else
          {
            if (board[(row + i)*boardColSize + (col + j)] == 1)
            {
            neighborcount++;
            }
          }
       
       }
    }
   } //next couple of for loops are used to repaint the board
  if(leftcol == 1 && toprow == 0 && bottomrow == 0) //left column
  {
    //printf("Left column \n");
    for (i = -1; i<2; i++)
    {
      for (j = 0; j <2; j++)
      {
        if (j ==0 && i == 0)
        {
          continue;
        }
        else
        {
          if (board[(row + i)*boardColSize + (col + j)] == 1)
          {
            neighborcount++;
          }
        }
      }
    }
  }
  if(rightcol == 1 && toprow == 0 && bottomrow == 0) //right column
  {
    //printf("Right column \n");
    for (i = -1; i<2; i++)
    {
      for (j = -1; j <1; j++)
      {
        if (j ==0 && i == 0)
        {
          continue;
        }
        else
        {
          if (board[(row + i)*boardColSize + (col + j)] == 1)
          {
            neighborcount++;
          }
        }
      }
    }
  }
  if(toprow == 1 && leftcol != 1 && rightcol != 1) //top row
  {
    //printf("toprow \n");
    for (i = 0; i<2; i++)
    {
      for (j = -1; j <2; j++)
      {
        if (j ==0 && i == 0)
        {
          continue;
        }
        else
        {
          if (board[(row + i)*boardColSize + (col + j)] == 1)
          {
            neighborcount++;
          }
        }
      }
    }
  }
  if(bottomrow == 1 && leftcol != 1 && rightcol != 1) //bottom row
  {
    //printf("bottomrow \n");
    for (i = -1; i<1; i++)
    {
      for (j = -1; j <2; j++)
      {
        if (j ==0 && i == 0)
        {
          continue;
        }
        else
        {
          if (board[(row + i)*boardColSize + (col + j)] == 1)
          {
            neighborcount++;
          }
        }
      }
    }
  }
  if(toprow == 1 && leftcol == 1) //top left corner
  {
    //printf("topleftcorner \n");
    for (i = 0; i<2; i++) //row
    {
      for (j = 0; j <2; j++) //column
      {
        if (j ==0 && i == 0)
        {
          continue;
        }
        else
        {
          if (board[(row + i)*boardColSize + (col + j)] == 1)
          {
            neighborcount++;
          }
        }
      }
    }
  }
  if(bottomrow == 1 && toprow != 1 && leftcol == 1) //bottom left corner
  {
    //printf("bottomleft corner \n");
    for (i = -1; i<1; i++) //row
    {
      for (j = 0; j <2; j++) //column
      {
        if (j ==0 && i == 0)
        {
          continue;
        }
        else
        {
          if (board[(row + i)*boardColSize + (col + j)] == 1)
          {
            neighborcount++;
          }
        }
      }
    }
  }
  if(toprow == 1 && leftcol != 1 &&rightcol == 1) //top right corner
  {
    //printf("top right corner \n");
    for (i = 0; i<2; i++) //row
    {
      for (j = -1; j <1; j++) //column
      {
        if (j ==0 && i == 0)
        {
          continue;
        }
        else
        {
          if (board[(row + i)*boardColSize + (col + j)] == 1)
          {
            neighborcount++;
          }
        }
      }
    }
  }
  if(bottomrow == 1 && toprow != 1 && leftcol !=1 && rightcol == 1) //bottom right corner
  {
   // printf("bottom right corner \n");
    for (i = -1; i<1; i++) //row
    {
      for (j = -1; j <1; j++) //column
      {
        if (j ==0 && i == 0)
        {
          continue;
        }
        else
        {
          if (board[(row + i)*boardColSize + (col + j)] == 1)
          {
            neighborcount++;
          }
        }
      }
    }
  }
  if (neighborcount >= 0)
  {
    //printf("%d \n", neighborcount);
  }
  return neighborcount;
} // last closing bracket
 /*
 * Update the game board to the next step.
 * Input:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize)
{ //variable initialization
  int a;
  int b;
  int c;
  int count;
  int totalsize = boardRowSize * boardColSize;
  int updatedboard[totalsize];
  for (a = 0; a < boardRowSize; a++) //called multiple times throughout the program. 
  {				     //used to update the whole board and repaint
    for (b = 0; b < boardColSize; b++)
    {
      count = countLiveNeighbor(board, boardRowSize, boardColSize, a, b);
      if (board[a * boardColSize + b] == 1)
      {
        if(count == 2 || count == 3)
        {
          updatedboard[a * boardColSize + b] = 1; //for number of live neighbors 2 <= x <= 3
        }
        else
        {
          updatedboard[a * boardColSize + b] = 0;
        }
      }
      else if (board[a * boardColSize + b] == 0)
      {
        if (count == 3) //bring cell to life
        {
          updatedboard[a * boardColSize + b] = 1;
        }
        else
        {
          updatedboard[a * boardColSize + b] = 0;
        }
      }
     
    }//b for loop
  }//a for loop
  for (c=0; c < totalsize; c++) //recursive call
  {
    board[c] = updatedboard[c];
  }
}//final bracket

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */
int aliveStable(int* board, int boardRowSize, int boardColSize)
{ //variable initialization
  int a;
  int b;
  int c;
  int same;
  int count;
  int totalsize = boardRowSize * boardColSize;
  int updatedboard[totalsize];
 // int checkboard[totalsize];
  for (a = 0; a < boardRowSize; a++)	//tests if board is updated and updates accordingly
  {
    for (b = 0; b < boardColSize; b++)
    {
      count = countLiveNeighbor(board, boardRowSize, boardColSize, a, b);
      if (board[a * boardColSize + b] == 1)
      {
        if(count == 2 || count == 3)
        {
          updatedboard[a * boardColSize + b] = 1;
        }
        else
        {
          updatedboard[a * boardColSize + b] = 0;
        }
      }
      else if (board[a * boardColSize + b] == 0)
      {
        if (count == 3)
        {
          updatedboard[a * boardColSize + b] = 1;
        }
        else
        {
          updatedboard[a * boardColSize + b] = 0;
        }
      }
     
    }//b for loop
  }//a for loop
  for (c = 0; c < totalsize; c++)
  {
    if (board[c] == updatedboard[c]) //check if board is updated
    {
      same = 1;
    }
    else
    {
      same = 0;
      break;
    }
  }
  return same;
}
