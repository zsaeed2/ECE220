/***************************
 *   pgm.c
 ***************************/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "binarytree.h"
#define ARRAY_SIZE 9
int main(void)
{
	int a[ARRAY_SIZE] = {10,5,11,3,8,6,9,15,13};
	NODE* root;
	root = create_tree( a, ARRAY_SIZE );


	int first_number;
	int second_number;
	printf("Select two numbers (10 , 5 , 11 , 3 , 8 , 6 , 9 , 15 , 13): ");
	scanf("%d %d", &first_number , &second_number);

	int i;
    int exist = 0;
	for( i = 0 ; i < ARRAY_SIZE ; i ++ ){
		if( a[i] == first_number ){
			exist += 1;
			break;
		}
	}
	for( i = 0 ; i < ARRAY_SIZE ; i ++ ){
		if( a[i] == second_number ){
			exist += 1;
			break;
		}
	}
	if( exist != 2 ){
		printf("The input numbers are not valid. Input numbers should be in the tree\n");
		return 1;
	}
	

	NODE* lca = lowest_common_ancestor( root , first_number , second_number );
	printf("lca of %d and %d is \n%d\n", first_number, second_number, lca->d );
	return 0;
}
