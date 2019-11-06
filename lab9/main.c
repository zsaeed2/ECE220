#include <stdio.h>
#include "vector.h"

int main()
{
    vector_t * vector = createVector(2);
    printf("Vector has size %d and max size %d\n", vector->size, vector->maxSize);
    push_back(vector, 1);
    push_back(vector, 2);
    push_back(vector, 3);
    printf("Vector has size %d and max size %d\n", vector->size, vector->maxSize);
    printf("Accessing first three elements:\n%d\n%d\n%d\n", access(vector, 0),
           access(vector, 1), access(vector, 2));

    printf("Popping back:\n%d\n", pop_back(vector));
    printf("Vector has size %d and max size %d\n", vector->size, vector->maxSize);
    printf("Destroying vector\n");
    destroyVector(vector);
    return 0;
}
