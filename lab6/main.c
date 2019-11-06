#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "verify.h"
#include "matrix.h"

double *generate_matrix(int rows,int cols,int type);
void print_matrix(double *matrix,int rows,int cols);
void free_matrix(double *matrix,int rows);

//Code to generate two random matrices A and B
//and compute the product, C=A*B
//User must enter <m> <k> <n> as arguments,
//where A is m by k and B is k by n.
int main(int argc,char **argv)
{
  if(argc!=4)
  {
    fprintf(stderr,"Please execute as ./matMult <m> <k> <n>\n");
    exit(EXIT_FAILURE);
  }
  //Initialization of matrices
  srand(time(NULL));
  int m=strtol(argv[1],NULL,10);
  int k=strtol(argv[2],NULL,10);
  int n=strtol(argv[3],NULL,10);

  double* mat_A=generate_matrix(m,k,1);
  double* mat_B=generate_matrix(k,n,1);
  double* mat_C=generate_matrix(m,n,0);

  //Print and compute C=A*B
  printf("Matrix A:\n");
  print_matrix(mat_A,m,k);
  printf("\nMatrix B:\n");
  print_matrix(mat_B,k,n);
  matrix_multiply(mat_A,mat_B,mat_C,m,k,n);
  printf("\nMatrix C:\n");
  print_matrix(mat_C,m,n);

  //Check if solution is correct
  if(verify_matrix(mat_A,mat_B,mat_C, m, k, n))
  {
    printf("\nCorrect!\n");
  }
  else
  {
    fprintf(stderr,"\nIncorrect.\n");
  }

  //Free allocated memory
  free(mat_A);
  free(mat_B);
  free(mat_C);

  return 0;
}

//Generate matrix entries at random
//Memory for matrix allocated here
double *generate_matrix(int rows,int cols,int type)
{
  double *matrix=(double*)malloc(rows*cols*sizeof(double));
  int x,y;
  for(y=0;y<rows;y++)
  {
    for(x=0;x<cols;x++)
    {
        int loc = y*cols+x;
        if(type){
            matrix[loc]=(rand()%1000)/100.0;
        }
        else
        {
            matrix[loc]=0.0;
        }
    }
  }

  return matrix;
}

void print_matrix(double *matrix,int rows,int cols)
{
  int x,y;
  for(y=0;y<rows;y++)
  {
    for(x=0;x<cols;x++)
    {
        int loc = y*cols+x;
        printf("%.2lf ",matrix[loc]);
    }
    printf("\n");
  }
}

