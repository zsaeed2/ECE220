#include<fstream>
#include <iomanip>    
#include "shape.hpp"



int main(int argc, char *argv[]){
	if(argc != 2) {
    	cerr << "USAGE: ./mp12 test1.txt" << endl; 
    	return -1;
  	}
	vector<Shape*> shape_ptrs = CreateShapes(argv[1]);
	cout << "max area = " << MaxArea(shape_ptrs) << endl;	
  	cout << "max volume = " << MaxVolume(shape_ptrs) << endl;
	return 0;
}
