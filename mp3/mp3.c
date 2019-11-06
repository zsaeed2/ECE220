/* Zayd Saeed	zsaeed2	MP3	2/12/2019
* This program is used to find an inputted row of Pascal's triangle
* using inputted values for the row, and prints out each coefficient 
* in the row using a formula identified below. Prints a space after 
* every coefficient and an extraneous space at the end. Still looks
* normal and works fine
* Partner: sraraj9
*/
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int row;

  printf("Enter a row index: ");
  scanf("%d",&row);

  // Write your code here
  unsigned long result = 1;
  //uses product  that is given to us for each row and coefficient number
  for (int i = 0; i <= row; i++)
    {
      for (double j = 1; j <= row - i; j++)
	{
	  result = (result * (row + 1 - j))/j;	  
	}
      printf("%lu ", result);
      result = 1;
    }

  return 0;
}
