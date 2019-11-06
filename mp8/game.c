/*Zayd Saeed	zsaeed2		MP8	28 March 2019
* This program is used to simulate the 2048 game through terminal (text version). The way we did this
* is through using multiple pointers, as we had the game struct defined in another file. The make and
* remake game simply initialize the rows, cols, score, and cells[] pointers. The get cell function
* returns a pointer to the cell with the specified index. the move w, a, s, d functions are all variations
* in the for loops of a parent function, the move function which I did not write in this program. I defined
* a 2dconvert function. I got this idea from quiz 4 which makes it much easier to convert the indices from
* 1d to a 2d array. Finally, the find legal move function loops through the board and tests to see if 
* there are any empty cells and also if adjacent cells are similar. Through the implementation of these 
* functions, we were able to implement the whole 2048 game
* Partners: aliesis2, srajag2
*/
#include "game.h"

game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
    mygame->rows = rows;//defines rows and columns pointer for struct
    mygame->cols = cols;
	
    mygame->score = 0; //assigns initial value to score pointer in struct
	
    for(int i = 0; i < rows*cols; i++){
	mygame->cells[i] = -1; //assigns value of -1 to all cells
    }

    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
	(*_cur_game_ptr)->rows = new_rows; //recreate game with new number of rows, columns, and 
	(*_cur_game_ptr)->cols = new_cols; //initialized score
	(*_cur_game_ptr)->score = 0;

	int i;
	for (i = 0; i < (new_rows*new_cols); i++) {
            (*_cur_game_ptr)->cells[i] = -1; //reassign all values of cells to -1
    	}
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
    if(row > cur_game->rows || col > cur_game->cols){
	return NULL;
    }
    return &cur_game->cells[row * cur_game->cols + col]; //returns pointer to specified cell index
}

//created this method to make it easier to convert from 1d array to 2d array
int convert_2d(game * cur_game, int row, int col) {
    // check if out of bounds first and return -1
	if (col<0 || row<0 || col>=cur_game->cols || row>=cur_game->rows) {
		return -1;
	}

    // return the index of the cell
	return row*cur_game->cols + col;
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE
	int didChange = 0;
	int empty, row, col, behind, currentIndex, currentCell, behindIndex, behindCell;
	    // loop through all cells
	    for (col=0; col<cur_game->cols; col++) {
		for (row=0; row<cur_game->rows; row++) {
		    // get current index in array using helper method
		    currentIndex = convert_2d(cur_game, row, col);
		    // set label to reloop if necessary and set empty to true
		    reloop:;
		    empty = 1;
		    // get current cell from index
		    currentCell = cur_game->cells[currentIndex];
		    // loop through the entire row checking for nonzero values
		    for (behind=row+1; behind<cur_game->rows; behind++) {
			behindIndex = convert_2d(cur_game, behind, col);
			behindCell  = cur_game->cells[behindIndex];
			if (behindCell != -1) {
			    if (currentCell == -1) {
		                // if its empty, we can move the tile all the way over
				cur_game->cells[currentIndex] = behindCell;
				cur_game->cells[behindIndex]  = -1;
				didChange = 1;
			    } else if (currentCell == behindCell) {
		                // if they are the same value, then they can be combined! so combine then
				cur_game->cells[currentIndex] = currentCell * 2;
				cur_game->score += currentCell * 2;
				cur_game->cells[behindIndex]  = -1;
				didChange = 1;
		   	    }
		            // it was not empty, so set it to false
			    empty = 0;
			    break;
			}
		    }
		    // if column is empty, go to the next column and dont waste our time
		    if (empty)
			goto nextCol;

		    // if the current cell has a value of -1, reloop and do the same thing
		    if (currentCell == -1)
			goto reloop;
		}
		nextCol:;
	    }
	    return didChange;
};

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE
	int didChange = 0;
	int empty, row, col, behind, currentIndex, currentCell, behindIndex, behindCell;
	    // loop through all cells
	    for (col=cur_game->cols-1; col>=0; col--) {
		for (row=cur_game->rows-1; row>=0; row--) {
		    // get current index in array using helper method
		    currentIndex = convert_2d(cur_game, row, col);
		    // set label to reloop if necessary and set empty to true
		    reloop:;
		    empty = 1;
		    // get current cell from index
		    currentCell = cur_game->cells[currentIndex];
		    // loop through the entire row checking for nonzero values
		    for (behind=row-1; behind>=0; behind--) {
			behindIndex = convert_2d(cur_game, behind, col);
			behindCell  = cur_game->cells[behindIndex];
			if (behindCell != -1) {
			    if (currentCell == -1) {
		                // if its empty, we can move the tile all the way over
				cur_game->cells[currentIndex] = behindCell;
				cur_game->cells[behindIndex]  = -1;
				didChange = 1;
			    } else if (currentCell == behindCell) {
		                // if they are the same value, then they can be combined! so combine then
				cur_game->cells[currentIndex] = currentCell * 2;
				cur_game->score += currentCell * 2;
				cur_game->cells[behindIndex]  = -1;
				didChange = 1;
		   	    }
		            // it was not empty, so set it to false
			    empty = 0;
			    break;
			}
		    }
		    // if column is empty, go to the next column and dont waste our time
		    if (empty)
			goto nextCol;

		    // if the current cell has a value of -1, reloop and do the same thing
		    if (currentCell == -1)
			goto reloop;
		}
		nextCol:;
	    }
	    return didChange;
};

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE
	int didChange = 0;
	int empty, row, col, behind, currentIndex, currentCell, behindIndex, behindCell;
	    // loop through all cells
	    for (row=0; row<cur_game->rows; row++) {
		for (col=0; col<cur_game->cols; col++) {
		    // get current index in array using helper method
		    currentIndex = convert_2d(cur_game, row, col);
		    // set label to reloop if necessary and set empty to true
		    reloop:;
		    empty = 1;
		    // get current cell from index
		    currentCell = cur_game->cells[currentIndex];
		    // loop through the entire row checking for nonzero values
		    for (behind=col+1; behind<cur_game->cols; behind++) {
			behindIndex = convert_2d(cur_game, row, behind);
			behindCell  = cur_game->cells[behindIndex];
			if (behindCell != -1) {
			    if (currentCell == -1) {
			        // if its empty, we can move the tile all the way over
				cur_game->cells[currentIndex] = behindCell;
				cur_game->cells[behindIndex]  = -1;
				didChange = 1;
			    } else if (currentCell == behindCell) {
			        // if they are the same value, then they can be combined! so combine then
				cur_game->cells[currentIndex] = currentCell * 2;
				cur_game->score += currentCell * 2;
				cur_game->cells[behindIndex]  = -1;
				didChange = 1;
		   	    }
			    // it was not empty, so set it to false
			    empty = 0;
			    break;
			}
		    }
		    // if column is empty, go to the next column and dont waste our time
		    if (empty)
			goto nextCol;

		    // if the current cell has a value of -1, reloop and do the same thing
		    if (currentCell == -1)
			goto reloop;
		}
		nextCol:;
	    }
	    return didChange;
};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE
	int didChange = 0;
	int empty, row, col, behind, currentIndex, currentCell, behindIndex, behindCell;
	    // loop through all cells
	    for (row=cur_game->rows-1; row>=0; row--) {
		for (col=cur_game->cols-1; col>=0; col--) {
		    // get current index in array using helper method
		    currentIndex = convert_2d(cur_game, row, col);
		    // set label to reloop if necessary and set empty to true
		    reloop:;
		    empty = 1;
		    // get current cell from index
		    currentCell = cur_game->cells[currentIndex];
		    // loop through the entire row checking for nonzero values
		    for (behind=col-1; behind>=0; behind--) {
			behindIndex = convert_2d(cur_game, row, behind);
			behindCell  = cur_game->cells[behindIndex];
			if (behindCell != -1) {
			    if (currentCell == -1) {
		                // if its empty, we can move the tile all the way over
				cur_game->cells[currentIndex] = behindCell;
				cur_game->cells[behindIndex]  = -1;
				didChange = 1;
			    } else if (currentCell == behindCell) {
		                // if they are the same value, then they can be combined! so combine then
				cur_game->cells[currentIndex] = currentCell * 2;
				cur_game->score += currentCell * 2;
				cur_game->cells[behindIndex]  = -1;
				didChange = 1;
		   	    }
		            // it was not empty, so set it to false
			    empty = 0;
			    break;
			}
		    }
		    // if column is empty, go to the next column and dont waste our time
		    if (empty)
			goto nextCol;

		    // if the current cell has a value of -1, reloop and do the same thing
		    if (currentCell == -1)
			goto reloop;
		}
		nextCol:;
	    }
	    return didChange;
    return 1;
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
    int row, col, cell, index1, index2;
    // loop through entire board
    for (row=0; row<cur_game->rows; row++) {
        for (col=0; col<cur_game->cols; col++) {
            // get cell at current location
	    cell = cur_game->cells[convert_2d(cur_game, row, col)];
            // if cell is marked empty, there are spaces to move
	    if (cell == -1)
		return 1;

            // find index of one row more and one column more
	    index1 = convert_2d(cur_game, row+1, col);
	    index2 = convert_2d(cur_game, row, col+1);
            
	    if (index1 != -1) {
		if (cell == cur_game->cells[index1])//tests for out of bounds index
		    return 1;
	    }    
	    if (index2 != -1) {
	        if (cell == cur_game->cells[index2])
		    return 1;
	    }
	}
    }
    return 0;
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
