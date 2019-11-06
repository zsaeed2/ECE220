#include "Rectangle.h"

//Empty Constructor sets instantiates a rectangle with length and width set as 0
Rectangle::Rectangle(){
//INSERT YOUR CODE HERE:

}

//Standard Constructor sets instantiates a rectangle with length and width set as input values
Rectangle::Rectangle(int input_length, int input_width){
//INSERT YOUR CODE HERE:

}

//Copy Constructor
//Instantiate a rectangle with length R1 = length R2 and width R1 = width R2
Rectangle::Rectangle( const Rectangle& other ){
//INSERT YOUR CODE HERE:

}

//Setter and Getter functions
void Rectangle::set_length(int input_length){
//INSERT YOUR CODE HERE:

}

void Rectangle::set_width(int input_width){
//INSERT YOUR CODE HERE:

}

int Rectangle::get_length(void) const{
//INSERT YOUR CODE HERE:

}

int Rectangle::get_width(void) const{
//INSERT YOUR CODE HERE:

}

//Calculate Area of rectangle
int Rectangle::area(void){
//INSERT YOUR CODE HERE:

}

//Calculate Perimeter of rectangle
int Rectangle::perimeter(void){
//INSERT YOUR CODE HERE:

}

/*Addition operator overload
* We define addition of two rectangles to be as follows: R3 = R1 + R2
* where length of R3 = length R1 + length R2
* and width R3 = width R1 + width R2
*/
Rectangle Rectangle::operator + (const Rectangle& other){
//INSERT YOUR CODE HERE:

}

/*Multiplication operator overload
* We define addition of two rectangles to be as follows: R3 = R1 * R2
* where length of R3 = length R1 * length R2
* and width R3 = width R1 * width R2
*/
Rectangle Rectangle::operator * (const Rectangle& other){
//INSERT YOUR CODE HERE:

}
