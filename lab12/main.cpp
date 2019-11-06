#include <iostream>
#include <fstream>
#include <string>
#include "Rectangle.h"
#include <sstream>
#include <vector>
#define ARGS 2


using namespace std;

int calc_area_of_sum_Rectangle(vector<Rectangle> all_rectangles);
int calc_perimeter_of_product_Rectangle(vector<Rectangle> all_rectangles);

//Main function: do not modify
int main(int argc,char *argv[])
{
	if (argc != ARGS) {
		fprintf(stderr,"Wrong number of arguments.\nCorrect usage: %s test.txt\n",
					argv[0]);
		return -1;
	}
   	vector<Rectangle> all_rectangles = vector<Rectangle>();
	ifstream ifs (argv[1], std::ifstream::in);
  	double num_shapes = 0;
  	ifs >> num_shapes;
	for(int i = 0; i < num_shapes; ++i){
		int l, w;
		ifs >> l >> w;
		Rectangle current_Rectangle = Rectangle(l, w);
		all_rectangles.push_back(current_Rectangle);
	}
    ifs.close();	
   	cout << "Area of Sum: " << calc_area_of_sum_Rectangle(all_rectangles) << endl;
   	cout << "Perimeter of Product: " << calc_perimeter_of_product_Rectangle(all_rectangles) << endl;

   	return 0;
}

/* calc_area_of_sum_Rectangle
*  Using a Rectangle to hold the sumation results, add together all the rectangles contained in "all_rectangles" vector
*  The rectangle used for storing sumation should be intialized with length and width equal to 0
*  Use the member function area() to return the calculate and return resulting area 
*/
int calc_area_of_sum_Rectangle(vector<Rectangle> all_rectangles){
	int number_of_rectangles = all_rectangles.size();
//INSERT YOUR CODE HERE:

}

/* calc_perimeter_of_product_Rectangle
*  Using a Rectangle to hold the product results, multiply together all the rectangles contained in "all_rectangles" vector
*  The rectangle used for storing product should be intialized with length and width equal to 1
*  Use the member function area() to return the calculate and return resulting area 
*/
int calc_perimeter_of_product_Rectangle(vector<Rectangle> all_rectangles){
	int number_of_rectangles = all_rectangles.size();
//INSERT YOUR CODE HERE:

	
}
