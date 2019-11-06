/*Zayd Saeed	zsaeed2		MP9	6 April 2019
* This program uses a DFS (depth-first search) algorithm to solve a maze. This is a new way of maze solving
* and the first time I have used it. In this, we also were assigned the task of creating and allocating 
* memory for the maze, as well as deallocating it, and printing it. The DFS algorithm seemed to be the most
* straightforward part of this MP as it was recursive backtracking and I have worked with it before. Making 
* the base case and the recursive cases of checking the up, left, right, and down cells recursively to find
* the quickest path to the end was simple. 
* Partner: bens3
*/


#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
  int rows, cols, i, j, k, l;
  FILE* file = fopen(fileName, "r"); // open input stream
  
  fscanf(file,"%d", &cols); 	// get width(cols) and height(rows)  
  fscanf(file,"%d", &rows);

  maze_t* maze = (maze_t*) malloc(sizeof(maze_t)); // allocate space for the maze
  maze->cells = calloc(rows,sizeof(char*)); // allocate space for each char array pointer (rows)
  
  for(k = 0; k < rows; k++){
    maze->cells[k] = calloc(cols,sizeof(char)); // for each row allocate space for char array of size cols
  }
  
  maze->width = cols; // assign cols to width
  maze->height = rows; //assign rows to height
  
  char buffer[rows][cols+2]; 	// buffer for input, cols + 2 because it takes a space and newline char
  
  for(l = 0; l < rows; l++){	 
    fgets(buffer[l],cols+2,file); // get one row of chars for each input line 
  }
	
  for(i = 0; i < rows; i++){ 	// loop over rows and cols to save cells
    for(j = 0; j < cols; j++){
      maze->cells[i][j] = buffer[i][j];
      if(buffer[i][j] == 'S'){ 		// if cell contains start/end, update start row and col
	maze->startRow = i;
	maze->startColumn = j;
      }
      if(buffer[i][j] == 'E'){ 
	maze->endRow = i;
	maze->endColumn = j;
      }
    }
  }
  return maze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
  int i;
  for(i = 0; i < maze->height; i++){
    free(maze->cells[i]); // deallocate memory for each cell
  }
  
  free(maze->cells); // deallocate memory for cells array
  free(maze); // deallocate memory for maze itself 
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{ 
  int i,j;	 
  for(i = 0; i < maze->height; i++){
    for(j = 0; j < maze->width; j++){
      printf("%c", maze->cells[i][j]); // loop through and print all cells
    }
    printf("\n"); // new line for a e s t h e t i c
  }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{ 	
  if( col < 0 || row < 0 || col >= maze->width || row >= maze->height) 	// check to make sure row,col values are valid
    return 0;
  
  if(maze->cells[row][col] == 'E') // Base case - check if maze is at end
    return 1;	

  if(maze->cells[row][col] != 'S' && maze->cells[row][col] != ' ') // return if cell is not empty, return false
    return 0;
	
  if(maze->cells[row][col] != 'S') // if cell is empty, set to soln path
    maze->cells[row][col] = '*';
	
  if(solveMazeDFS(maze,col+1,row)) // check right cell
    return 1;

  if(solveMazeDFS(maze,col,row+1)) // check cell above
    return 1;
	
  if(solveMazeDFS(maze,col-1,row)) // check cell below
    return 1;

  if(solveMazeDFS(maze,col,row-1)) // check cell left
    return 1;

  if(maze->cells[row][col] != 'S') // backtrack - return to previous state
    maze->cells[row][col] = '~';

  return 0; // no solution case
}
