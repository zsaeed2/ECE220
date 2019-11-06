/* Zayd Saeed	zsaeed2	MP4	2/23/2019
* This program is designed to print all of the semiprimes between a range of
* 2 inputted numbers. It tests all the numbers between the ranges, tests
* whether they are the product of 2 primes, and prints them if they are.
* Partner: srajag9
*/

#include <stdlib.h>
#include <stdio.h>


int is_prime(int number);
int print_semiprimes(int a, int b);


int main(){   
   int a, b;
   printf("Input two numbers: ");
   scanf("%d %d", &a, &b);
   if( a <= 0 || b <= 0 ){
     printf("Inputs should be positive integers: \n");
     return 1;
   }

   if( a > b ){
     printf("The first number should be smaller than or equal to the second number\n");
     return 1;
   }

   // TODO: call the print_semiprimes function to print semiprimes in [a,b] (including a and b)
   print_semiprimes(a,b);
   printf("\n"); // prints new line character for a e s t h e t i c
}


/*
 * TODO: implement this function to check the number is prime or not.
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
  if(number <= 1){ // test case for 0 or negative numbers
    return 0;
  }
  if(number % 2 == 0 && number > 2){ // test case for 2
    return 0;
  }
  for(int i = 3; i < number; i++){ // tests all numbers between 3 and n - 1
    if(number % i == 0){	   // to see if reminder when you divide the 
      return 0;			   // two numbers is 0
    }
  }
  return 1;
}


/*
 * TODO: implement this function to print all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b){
  for(int n = a; n <= b; n++){
    for(int k = 2; k < n-1; k++){
      if(is_prime(k) && n%k==0 && is_prime(n/k)){ // tests for semiprime as 
    printf("%d ", n);				  // specified by the algorithm
    break;
      }  
    }
  }

  for(int n = a; n <= b; n++){
    for(int k = 2; k < n; k++){
      if(is_prime(k) && n%k==0 && is_prime(n/k)){ // same test but for return value
    return 1;
      }
    }
  }
  return 0;
}
