#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------
/*Zayd Saeed	zsaeed2		MP7	13 March 2019
* The purpose of this program was to implement a sudoku solver. We did this through backtracking 
* recursive principles. We implemented 5 main functions, 2 of which used the other 3. The first
* 3 were for the purpose of determining whether a number could be validly placed in a space by
* checking the row, column, and 3x3 box for duplicates of that number. The fourth method was to
* test for all 3 of these simultaneously to simplify implementation. The fifth was the real 
* sudoku solver which included a self-created method to find the first unassigned space.
* We used recursion to implement the algorithm that was described to us in pseudocode, and have
* managed to successfully do so.
* Partner: srajag9
*/
// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  for(int j = 0; j < 9; j++){
    if(sudoku[i][j]==val){ //iterates through whole row to see if there is a duplicate value
      return 1;
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  for(int i = 0; i < 9; i++){
    if(sudoku[i][j]==val){ //iterates through whole  column to see if theres a duplicate value
      return 1;
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO
  int x,y;
  x = i/3; //truncate to determine which 3x3 column it's in
  y = j/3; //truncate to determine which 3x3 row it is in
  for(int a = x*3; a < x*3+3; a++){ //test for 3 rows
    for(int b = y*3; b < y*3+3; b++){// test for 3 columns
      if(sudoku[a][b] == val){ // tests if value is duplicated in 3x3 grid
	return 1;
      }
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  if(is_val_in_row(val,i,sudoku) || is_val_in_col(val,j,sudoku) || is_val_in_3x3_zone(val,i,j,sudoku)){ // simultaneously tests for any of 3 cases of invalid input
    return 0;
  }
  return 1;
  // END TODO
}

// Function defined to locate the first unassigned space
// Runs through whole sudoku grid in order until it locates a space that is unassigned
// Assigns column and row values to that specific place which is why theres '&' char
int find_unassigned(int sudoku[9][9],int &row,int &col) {
  for(row = 0; row < 9; row++){
    for(col = 0; col < 9; col++){
      if(sudoku[row][col] == 0){ 
	return 1;
      }
    }
  }
  return 0;
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  // declare row and column variables
  int row, col;
  // test to see if all spaces have assigned numbers, and return true if so
  if(!find_unassigned(sudoku, row, col)){
      return 1;
  } 
  for(int num = 1; num <= 9; num++){
    // test if number is valid in given space and if space is originally unassigned
    if(is_val_valid(num,row,col,sudoku) && sudoku[row][col] == 0){
      sudoku[row][col] = num; //set given space to num
      if(solve_sudoku(sudoku)){ // recursive call to function to test all numbers
	return 1; 
      }
      sudoku[row][col] = 0; // return value to unassigned to finalize an impossible case
    }
  }
  return 0; //return false for impossible case
  // END TODO.
}

  // Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}
