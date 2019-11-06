#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle{
	private:
		int length;
		int width;
	public:
		//Basic Constructors functions
		Rectangle();
		Rectangle(int input_length, int input_width);

		//Copy Constructor
		Rectangle( const Rectangle& other );
		
		//Setter and Getter functions
		void set_length(int input_length);
		void set_width(int input_width);
		int get_length(void) const;
		int get_width(void) const;

		//Calculate Area/Perimeter
		int area(void);
		int perimeter(void);
		
		//Addition operator overload
		Rectangle operator + (const Rectangle& other);
		Rectangle operator * (const Rectangle& other);
};

#endif
