#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>

/*Zayd Saeed	zsaeed2		MP10  	4/11/2019
* The purpose of this program was to create a way to algorithmically define matrices to maximize memory. While these "sparse matrices"	
* have already been created, our job was to implement them through C. The add and multiply functions were implemented based on the 	
* pseudocode provided on the wiki. The save, gv, and destroy functions were short and relatively simple, and done to the parameters  
* as described in the program details. The load and set function, however, was a bit more complicated, which is why I created an insertTuple 
* and deleteTuple function to assist me in implementing the set function. As such, the program runs, is commented, and fully functional
* bens3
*/

// deleteTuple searches for index to be deleted, removes it from list, frees it and updates nonZero if found. Does nothing if not found
void deleteTuple(sp_tuples_node** head, int item_index , int cols, int* nonZero){
	
	if ((*head) == NULL) 			// if no elements left, return
		return; 
	
	int head_index = (*head)->row * cols + (*head)->col;
	sp_tuples_node* temp;


	if( head_index > item_index)  		// if item index should have been found already, return	
		return;
		
	if( head_index == item_index){ 		// if item index is found
		temp = (*head); 		// point temp to node to be removed
		(*head) = (*head)->next; 	// replace head with its next
		free(temp); 			// free the old head
		(*nonZero)--; 	  		// update nonZero
		return;
	}
	
	deleteTuple( &((*head)->next), item_index, cols, nonZero); // else try next node
}

// insert tuples takes the head pointer, the current tuple to be inserted, number of cols of the matrix and a pointer to nonZero 
// and inserts the nodes in sorted order by index of the node. If node already exists, value is updated.
void insertTuple(sp_tuples_node** head, sp_tuples_node* cur_node, int cols, int* nonZero){
	if( *head == NULL){ 									// if at the end of the list, place node
		*head = cur_node;
		(*head)->next = NULL;
		(*nonZero)++; 									// update nonZero
		return; 									
		
	}
	
	sp_tuples_node* temp; 						//set temp value for swap of pointers  

	int head_index = (*head)->row * cols + (*head)->col; 		// set index of head to be its location in a 1D array
	int cur_index = cur_node->row * cols + cur_node->col; 		// same for current node

	
	if ( head_index > cur_index){ 	// if the head should be placed after current node, set new head, and point to old head
		temp = *head; 		
		*head = cur_node;
		(*head)->next = temp;
		(*nonZero)++; 		// update nonZero
		return;
	}
	else if( head_index == cur_index ){ 		
		(*head)->value = cur_node->value; 			// if we are overwriting a previous node
		free(cur_node); 					// simply update value and free cur_node
		return; 			 			// return without updating nonZero				
	}
	insertTuple( &((*head)->next) , cur_node, cols, nonZero); // if still smaller and head is not NULL try next node
} 

// loads tuples from input file and initialize sparse matrix 
sp_tuples * load_tuples(char* input_file)
{
	int rows;
	int cols;
	int nonZero = 0; 						// intially number of non-zero elements is zero

	FILE*  input = fopen(input_file,"r"); 				// open input file 

	fscanf(input, "%d %d ", &rows, &cols); 				// extract size of matrix

	sp_tuples* matrix = (sp_tuples*)malloc(sizeof(sp_tuples));  	// allocate space for the matrix pointer
	matrix->m = rows; 						// set row size
	matrix->n = cols; 						// set col size
	matrix->tuples_head = NULL; 					// set the head to NULL
	
	while( !feof(input)){ 			// while input file is not empty
		sp_tuples_node* cur_node = (sp_tuples_node*) malloc(sizeof(sp_tuples_node)); 		// create new node
		
		cur_node->next = NULL; 									// set the next to NULL
		
		fscanf(input, "%d %d %lf ", &(cur_node->row), &(cur_node->col), &(cur_node->value)); // get data from input file
		
		if(cur_node->value == 0){ 		// if the value is zero, free data and continue to next line of input
			deleteTuple(&(matrix->tuples_head),cur_node->row * cols + cur_node->col, cols, &nonZero); // just in case we are overwritting
			free(cur_node);
			continue;
		}
		
		insertTuple( &(matrix->tuples_head), cur_node, matrix->n, &nonZero); 			// call insert on current tuple	
	}
	
	fclose(input); 					// close the input file
	matrix->nz = nonZero; 				// store value of nonZero in matrix
	return matrix; 					// return pointer to struct
}


// this function traverses the list looking for an element with the given row and col, and returns its value
double gv_tuples(sp_tuples * mat_t,int row,int col)
{
	int item_index = row* (mat_t->n) + col; 			// set item index using given row and col
	sp_tuples_node* head = (mat_t->tuples_head); 			// set head pointer to point to head of list
	
	while( head != NULL){ 						// check that the head is not NULL
		if( (head->row)*(mat_t->n) + (head->col) == item_index) 	// compare indexes and return value
			return head->value;
		
		else if((head->row)*(mat_t->n) + (head->col) > item_index) 	// if the index specified has been passed, the object is not in list
			return 0;

		head = head->next; 						// update head to next pointer
	}
	return 0; 								// if not found and list exhausted, return 0;
}

// this function should either delete an index if the value == 0, update a previous value, or add a new node to the list
void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
	int item_index = row * (mat_t->n) + col; 		// set item index
	
	if( value == 0){ 					// if the value is zero, use delete function to remove node
		deleteTuple(&(mat_t->tuples_head), item_index, mat_t->n, &(mat_t->nz));
		return;
	}	
	
	else{ 	// else initialize node and insert it to the matrix using the insert function
		sp_tuples_node* newNode = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
		newNode->row = row;
		newNode->col = col;
		newNode->value = value;
		insertTuple( &(mat_t->tuples_head), newNode, mat_t->n , &(mat_t->nz));
		return; 
	}
}

// save_tuples should output sparse matrix format into specified file
void save_tuples(char * file_name, sp_tuples * mat_t) {
    // check if matrix input is null (needed for unimplemented lil methods)
    if(mat_t != NULL) {
        FILE * file = fopen(file_name, "w");
        fprintf(file, "%d %d\n", mat_t->m, mat_t->n);

        sp_tuples_node * current = mat_t->tuples_head;

        // loop through the entire linked list and print out the values properly
        while(current != NULL) {
            // print the values from the currentent node
            fprintf(file, "%d %d %lf\n", current->row, current->col, current->value);

            // iterate
            current = current->next;
        }
        // close the file for writing
        fclose(file);
    }

    return;
}

sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){

	if ( matA->m != matB->m || matA->n != matB->n) 			// matrix A and B are not the same size 
		return NULL;

	double value;
	
	sp_tuples* matC = (sp_tuples*)malloc(sizeof(sp_tuples)); 	// intialize matrix 
	matC->tuples_head = NULL;
	matC->m = matA->m;
	matC->n = matB->n;
	matC->nz = matA->nz;
	
	sp_tuples_node** C_ptr = &(matC->tuples_head);
	
	sp_tuples_node* A_ptr = matA->tuples_head;
	sp_tuples_node* B_ptr = matB->tuples_head;

	while( A_ptr  != NULL){ 					// iterate over elements of A and save them in C	
		
		sp_tuples_node* newNode = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));  	// declare node
	 
		newNode-> row = A_ptr-> row; 				 // copy values of A into new node	
		newNode-> col = A_ptr-> col;
		newNode-> value = A_ptr-> value;
		newNode-> next = NULL; 					// set next to NULL

		*C_ptr = newNode; 					// copy new node into the current head in C
		C_ptr = &((*C_ptr)->next); 				// point to next head in C
		A_ptr = A_ptr->next; 					// point A_ptr to next node	
	}

	while( B_ptr != NULL){ 						// iterate over matB, add the value of its elements and set new value in matC
	
		value = gv_tuples(matC,B_ptr->row,B_ptr->col) + B_ptr->value;
		set_tuples(matC,B_ptr->row,B_ptr->col,value);
			
		B_ptr = B_ptr->next;
	}	
	
	return matC;
}

sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
    	
	if( matA->n != matB->m) 				// if multiplication is not possible, return NULL
		return NULL;

	sp_tuples* matC = (sp_tuples*)malloc(sizeof(sp_tuples)); 	// declare and initialize matC
	matC->m = matA->m; 						// set rows by mat A
	matC->n = matB->n; 						// cols by mat B
	matC->nz = 0; 					
	matC->tuples_head = NULL;

	int rowA;
	int colA;
	int rowB;
	int colB;
	double value; 

	sp_tuples_node* A_ptr = matA->tuples_head; 			// initialize pointers to loop over matrices
	sp_tuples_node* B_ptr = matB->tuples_head;

	while( A_ptr != NULL) {
		rowA = A_ptr->row; 		// set current row and col of element from A
		colA = A_ptr->col; 		
		B_ptr = matB->tuples_head; 	// reinitialize B_ptr to start of list for next loop over matrix B

		while( B_ptr != NULL){
			rowB = B_ptr->row;
			colB = B_ptr->col;
			if(rowB == colA){
				value = gv_tuples(matC,rowA,colB) + A_ptr->value * B_ptr->value;
				set_tuples(matC,rowA,colB,value);		
			}
			B_ptr = B_ptr->next;
		}
		A_ptr = A_ptr->next;
	}
	return matC;
}

void destroy_tuples(sp_tuples * mat_t) {
    if(mat_t != NULL) {
        sp_tuples_node * current = mat_t->tuples_head;
        sp_tuples_node * murica = NULL;

        while(current != NULL) { //loops through all nodes and deallocated memory one by one
            murica = current; 
            current = current->next;
            free(murica); //just for the memes so we could free murica
        }
        free(mat_t);
    }
    return;
}
