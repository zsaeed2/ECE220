all:
	gcc -Wall -g -std=c99 -I include/ -L lib/ main.c updateBoard.c -o gameoflife -lncurses
	gcc -Wall -g -std=c99 test.c updateBoard.c updateBoardGold.o -o test
clean:
	rm gameoflife
	rm test
