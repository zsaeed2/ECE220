#include "sliding.h"
#include <malloc.h>
#include <stdlib.h>

//Prints grid in row major order.  Tries to ensure even spacing.
void print_grid(int * my_array, int rows, int cols){
	int i,j;
	for(i=0; i<rows; i++){
		for(j=0; j<cols; j++){
			if(my_array[i*cols + j]!=-1){
				printf(" %d ", my_array[i*cols + j]);
			}
			else{
				printf("%d ", my_array[i*cols + j]);
			}
		}
		printf("\n");
	}
}

int main(int argc, char *argv[])
{
	int seed,rows,cols;
	char buf[200];
	char garbage[2];
	//Get input from user as (seed rows columns)
	printf("Please provide input as: seed rows columns\n");
	if (NULL == fgets(buf,200,stdin)) {
		printf("\nProgram Terminated.\n");
		return 2;
	}

	//Checks input for validity
	if (3 != sscanf(buf,"%d%d%d%1s",&seed,&rows,&cols,garbage) ||
	rows < 0 || cols < 0){
		printf("Invalid Input\n");
		return 2;
	}

	//Seeds the random number generator
	srand(seed);

	//Allocate array grid
	int * my_array = (int *)malloc(rows*cols*sizeof(int));

	//Populate grid with random values -1, 1 and 2
	int i,j;
	for(i=0; i<rows; i++){
		for(j=0; j<cols; j++){
			if(rand()%3 < 2){
				my_array[i*cols + j] = rand()%2+1;
			}
			else{
				my_array[i*cols + j] = -1;
			}
		}
	}

	//Print initial grid
	printf("Initial grid: \n");
	print_grid(my_array, rows, cols);

	//Call sliding function
	slide_up(my_array, rows, cols);

	//Print resulting grid
	printf("Shifted grid: \n");
	print_grid(my_array, rows, cols);
	free(my_array);

	return 0;
}
