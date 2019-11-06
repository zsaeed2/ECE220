#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
	int data;
     	struct node_t *next;
} node;

void printList(node * Node) {
	int j = 1;
        printf("data = ");
	while( Node != NULL){
		printf(" %d", Node->data);
		Node = Node->next;
		j++;
	}
        printf("\n");
}

/*Implement this function for Lab 10*/
void reverse(node** head){

}

/*Implement this function for Lab 10*/
void removeDuplicates(node* head){

}

int main() {
    node * head = NULL;
    node * temp;
    int i = 0;
    int j = 0;
    //Create Sorted linked list with repeats
    for(i = 9; i > 0; i--) {
        if(i%3==0){
            for(j = 0; j < 3; j++){
                temp = head;
	        head = (node *) malloc(sizeof(node));
	        head->data = i;
	        head->next = temp;     
            }
        }else{
            temp = head;
            head = (node *) malloc(sizeof(node));
            head->data = i;
            head->next = temp;
        }
    }
    printf("Printing the original list:\n");
    printList(head);
    removeDuplicates(head);
    printf("Printing the removeDuplicates list:\n");
    printList(head);
    reverse(&head);
    printf("Printing the reverse list:\n");
    printList(head);
    //free list
    while(head!=NULL){
        temp = head;
        head = head->next;
        free(temp);
    }
    return 0;
}
