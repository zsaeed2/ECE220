
BIN=floorplanner

$(BIN): main.c floorplan.c floorplan.h
	g++ -Wall -O3 -c floorplan.c -o floorplan.o
	g++ -Wall -O3 -c main.c -o main.o
	g++ -Wall -O3 floorplan.o main.o -L./lib -ltest -o $(BIN) 

.PHONY: clean
clean:
	rm floorplanner *.o

circuit1: $(BIN)
	./$(BIN) circuits/circuit1.txt

circuit2: $(BIN)
	./$(BIN) circuits/circuit2.txt

circuit3: $(BIN)
	./$(BIN) circuits/circuit3.txt

circuit4: $(BIN)
	./$(BIN) circuits/circuit4.txt

circuit5: $(BIN)
	./$(BIN) circuits/circuit5.txt
