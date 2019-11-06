CC=gcc
CFLAGS=-g -Wall -Wextra

lab12: main.o vector.o
	$(CC) $(CFLAGS) main.o vector.o -o lab12

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

vector.o: vector.c
	$(CC) $(CFLAGS) -c vector.c

clean:
	rm -f *.o lab12
