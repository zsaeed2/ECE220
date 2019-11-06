/* Zayd Saeed	zsaeed2	  MP5	2/28/2019
*  This program serves to set up a text game. It involves entering a seed which generates
*  a random 4 digit number. The player then has 12 chances to guess the 4 digit number
*  correctly, where the four digits can be repeated and are between 1 and 8, inclusive
*  The program will tell the player how many correctly placed digits and how many misplaced
*  digits there are. In addition, the seed must be an integer, and an error message will pop
*  up for invalid seed entries and invalid guesses (non digits, letters, more than 4 digits)
*  partner: srajag9
*/


/*           
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */



#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid.
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int set_seed (const char seed_str[])
{
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read.
//    We declare
   int seed;
   char post[2];
//    The sscanf statement below reads the integer into seed.
    if(sscanf(seed_str, "%d%1s", &seed, post)==1)
    {
       srand(seed);
       return 1;
    }

    else
    {
     printf("set_seed: invalid seed\n"); //prints line for invalid seed
     return 0;
     }
   //    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
   //    The return value of sscanf indicates the number of items read succesfully.
   //    When the user has typed in only an integer, only 1 item should be read sucessfully.
   //    Check that the return value is 1 to ensure the user enters only an integer.
   //    Feel free to uncomment these statements, modify them, or delete these comments as necessary.
   //    You may need to change the return statement below
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above.
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void
start_game (int* one, int* two, int* three, int* four)
{
    //your code here
    *one = (rand()%8)+1; //generates random numbers for all four values
    *two = (rand()%8)+1;
    *three = (rand()%8)+1;
    *four = (rand()%8)+1;
    solution1 = *one;	//creates pointers for four solutions
    solution2 = *two;
    solution3 = *three;
    solution4 = *four;
    guess_number = 1;
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str.
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess)
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int make_guess (const char guess_str[], int* one, int* two,
        int* three, int* four)
{
 
//  One thing you will need to read four integers from the string guess_str, using a process
//  similar to set_seed
//  The statement, given char post[2]; and four integers w,x,y,z,
int perfect = 0;
int misplaced = 0;
//int i;
//int j;
int w;
int x;
int y;
int z;
int onepair = 0;
int twopair = 0;
int threepair = 0;
int fourpair = 0;
int solone = 0;
int soltwo = 0;
int solthree = 0;
int solfour = 0;
char post[2];
int check;
check = sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post);
if (check==4) //this block of code is primarily a brute-force way to test all combinations
{	      //of inputs to see which ones are mismatched and which ones are ok
  if(w<=8 && w>=1 && x<=8 && x>=1 && y<=8 && y>=1 && z<=8 && z>=1)
  {
    *one=w;
    *two=x;
    *three=y;
    *four=z;
    if(solution1 == w)
    {
      perfect++;
      onepair = 1;
      solone = 1;
    }
    if(solution2 == x)
    {
      perfect++;
      twopair = 1;
      soltwo = 1;
    }
    if(solution3 == y)
    {
      perfect++;
      threepair = 1;
      solthree = 1;
    }
    if(solution4 == z)
    {
      perfect++;
      fourpair = 1;
      solfour = 1;
    }
    //first variable
    if(solution2 == w && onepair != 1 && soltwo != 1)
    {
      misplaced++;
      onepair = 1;
      soltwo = 1;
    }
    if(solution3 == w && onepair != 1 && solthree != 1)
    {
      misplaced++;
      onepair = 1;
      solthree = 1;
     
    }
    if(solution4 == w && onepair != 1 && solfour != 1)
    {
      misplaced++;
      onepair = 1;
      solfour = 1;
    }
    //second variable
    if(solution1 == x && twopair != 1  && solone != 1)
    {
      misplaced++;
      twopair = 1;
      solone = 1;
     
    }
    if(solution3 == x && twopair != 1 && solthree != 1)
    {
      misplaced++;
      twopair = 1;
      solthree = 1;
     
    }
    if(solution4 == x && twopair != 1 && solfour != 1)
    {
      misplaced++;
      twopair = 1;
      solfour = 1;
    }
    //third variable
    if(solution2 == y && threepair != 1 && soltwo != 1)
    {
      misplaced++;
      threepair = 1;
      soltwo = 1;
    }
    if(solution1 == y && threepair != 1 && solone != 1)
    {
      misplaced++;
      threepair = 1;
      solone = 1;
    }
    if(solution4 == y && threepair != 1 && solfour != 1)
    {
      misplaced++;
      threepair = 1;
      solfour = 1;
    }
    //fourth pair
    if(solution2 == z && fourpair != 1 && soltwo != 1)
    {
      misplaced++;
      fourpair = 1;
      soltwo = 1;
    }
    if(solution3 == z && fourpair != 1 && solthree != 1)
    {
      misplaced++;
      fourpair = 1;
      solthree = 1;
    }
    if(solution1 == z && fourpair != 1 && solone != 1)
    {
      misplaced++;
      fourpair = 1;
      solone = 1;
    }
   
    /* int solutionarray[] = {w,x,y,z};
    for (i=0; i < 4; i++)
    {
      for (j=0; j<4; j++)
        if (i != j && solutionarray[i] == solutionarray[j])
        {
          misplaced++;
        }
    } */
    //if (perfect < 4)
    //{ //random code used to test but decided to do other way insted
     printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perfect, misplaced); //message for correctness of guess
     guess_number++;
     return 1;
    }
    //else
    //{
      //return 1;
   // }
  //}
  else
  {
    printf("make_guess: invalid guess\n"); //prints invalidation message
    return 0;
  }
}
else
{
  printf("make_guess: invalid guess\n"); //prints invalidation message
  return 0;
}
//  will read four integers from guess_str into the integers and read anything else present into post
//  The return value of sscanf indicates the number of items sucessfully read from the string.
//  You should check that exactly four integers were sucessfully read.
//  You should then check if the 4 integers are between 1-8. If so, it is a valid guess
//  Otherwise, it is invalid. 
//  Feel free to use this sscanf statement, delete these comments, and modify the return statement as needed
}


