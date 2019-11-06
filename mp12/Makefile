student: shape.cpp main.cpp
	g++ main.cpp shape.cpp -o mp12

verify:  shape.cpp verify.cpp
	g++ -g -c shape.cpp -o shape.o
	g++ -g -c verify.cpp -o verify.o
	g++ -g verify.o shape.o check.a -o verify_mp12

clean:
	rm  *.o mp12 


