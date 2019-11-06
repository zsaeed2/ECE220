#include "shape.hpp"


//Base class
//Please implement Shape's member functions
//constructor, getName()
//
//Base class' constructor should be called in derived classes'
//constructor to initizlize Shape's private variable
Shape::Shape(string name)
{
  name_ = name;
}
string Shape::getName(){return name_;}
//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Rectangle::Rectangle(double w, double l) : Shape("Rectangle") {
  width_ = w;
  length_ = l;
}
double Rectangle::getArea()const{return width_*length_;}
double Rectangle::getVolume()const{return 0;}
double Rectangle::getWidth()const{return width_;}
double Rectangle::getLength()const{return length_;}
Rectangle Rectangle::operator + (const Rectangle& rec) {
  double length1 = getLength();
  double width1 = getWidth();
  double width2 = rec.width_;
  double length2 = rec.length_;
  double newlen = length1 + length2;
  double newwid = width1 + width2;
  Rectangle r = Rectangle(newwid,newlen);
  return r;
}
Rectangle Rectangle::operator - (const Rectangle& rec) {
  double length1 = getLength();
  double width1 = getWidth();
  double width2 = rec.width_;
  double length2 = rec.length_;
  double newlen = length1 - length2;
  double newwid = width1 - width2;
  newlen = (newlen > 0) ? newlen : 0;
  newwid = (newwid > 0) ? newwid : 0;
  Rectangle r = Rectangle(newwid,newlen);
  return r;
}
//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Circle::Circle(double radius) : Shape("Circle"){
  radius_ = radius;
}
double Circle::getRadius()const{return radius_;}
double Circle::getArea()const{return radius_*radius_ * M_PI;}
double Circle::getVolume()const{return 0;}
Circle Circle::operator + (const Circle& cir) {
  double rad1 = getRadius();
  double rad2 = cir.radius_;
  double newrad = rad1 + rad2;
  Circle c = Circle(newrad);
  return c;
}
Circle Circle::operator - (const Circle& cir) {
  double rad1 = getRadius();
  double rad2 = cir.radius_;
  double newrad = rad1 - rad2;
  newrad = (newrad > 0) ? newrad : 0;
  Circle c = Circle(newrad);
  return c;
}
//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Sphere::Sphere(double radius) : Shape("Sphere"){
  radius_ = radius;
}
double Sphere::getArea()const{return 4* M_PI* radius_ * radius_;}
double Sphere::getVolume()const{return ((4.0/3.0)* radius_ *radius_ *radius_ *M_PI);}
double Sphere::getRadius()const{return radius_;}
Sphere Sphere::operator + (const Sphere& sph) {
  double rad1 = getRadius();
  double rad2 = sph.radius_;
  double newrad = rad1 + rad2;
  Sphere s = Sphere(newrad);
  return s;
}
Sphere Sphere::operator - (const Sphere& sph) {
  double rad1 = getRadius();
  double rad2 = sph.radius_;
  double newrad = rad1 - rad2;
  newrad = (newrad > 0) ? newrad : 0;
  Sphere c = Sphere(newrad);
  return c;
}
//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
RectPrism::RectPrism(double width, double length, double height): Shape("RectPrism") {
  length_ = length;
  width_ = width;
  height_ = height;
}
double RectPrism::getArea()const{return (2*(length_*width_ + length_ * height_ + width_ * height_));}
double RectPrism::getVolume()const{return length_ * width_ * height_;}
double RectPrism::getWidth()const{return width_;}
double RectPrism::getHeight()const{return height_;}
double RectPrism::getLength()const{return length_;}
RectPrism RectPrism::operator + (const RectPrism& rectp) {
  double length1 = getLength();
  double width1 = getWidth();
  double height1 = getHeight();
  double width2 = rectp.width_;
  double length2 = rectp.length_;
  double height2 = rectp.height_;
  double newlen = length1 + length2;
  double newwid = width1 + width2;
  double newh = height1 + height2;
  RectPrism rp = RectPrism(newwid,newlen, newh);
  return rp;
}
RectPrism RectPrism::operator - (const RectPrism& rectp) {
  double length1 = getLength();
  double width1 = getWidth();
  double height1 = getHeight();
  double width2 = rectp.width_;
  double length2 = rectp.length_;
  double height2 = rectp.height_;
  double newlen = length1 - length2;
  double newwid = width1 - width2;
  double newh = height1 - height2;
  newlen = (newlen > 0) ? newlen : 0;
  newwid = (newwid > 0) ? newwid : 0;
  newh = (newh > 0) ? newh : 0;
  RectPrism rp = RectPrism(newwid,newlen, newh);
  return rp;
}



// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects
vector<Shape*> CreateShapes(char* file_name){
	//@@Insert your code here
  //class Shape;
  vector<Shape*> vec;
  string curshape;
  int objnum;
  double var1;
  double var2;
  double var3;
  Shape* shape_ptr;
  Shape* head = shape_ptr;
  ifstream ifs(file_name, std::ifstream::in);
  ifs >> objnum;
  while(objnum > 0)
  {
    ifs >> curshape;
    if(curshape == "Circle")
    {
      ifs >> var1;
      Shape* shape_ptr = new Circle(var1);
      vec.push_back(shape_ptr);
    }
    if(curshape == "Rectangle")
    {
      ifs >> var1 >> var2;
      Shape* shape_ptr = new Rectangle(var1, var2);
      vec.push_back(shape_ptr);
    }
    if(curshape == "Sphere")
    {
      ifs >> var1;
      Shape* shape_ptr = new Sphere(var1);
      vec.push_back(shape_ptr);
    }
    if(curshape == "RectPrism")
    {
      ifs >> var1 >> var2 >> var3;
      Shape* shape_ptr = new RectPrism(var1,var2,var3);
      vec.push_back(shape_ptr);
    }
    objnum = objnum-1;
    shape_ptr++;
  }
  ifs.close();
	return vec; // please remeber to modify this line to return the correct value
}

// call getArea() of each object
// return the max area

double MaxArea(vector<Shape*> shapes){
	double max_area = 0;
  int shapesize = shapes.size();
  int shapecount = 0;
  double temparea;
  while(shapecount < shapesize) {
    temparea = shapes[shapecount]->getArea();
    if(temparea > max_area)
    {
    max_area = temparea;
    }
    shapecount++;
  }
	return max_area;
}

// call getVolume() of each object
// return the max volume

double MaxVolume(vector<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here
  int shapesize = shapes.size();
  int shapecount = 0;
  double tempvol;
  while(shapecount < shapesize) {
    tempvol = shapes[shapecount]->getVolume();
    if(tempvol > max_volume)
    {
    max_volume = tempvol;
    }
    shapecount++;
  }
	return max_volume;
}
