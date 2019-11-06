CC=gcc
CFLAGS= -Wall -Werror -std=c99

all: permutation

permutation: main.o verify.o
	$(CC) main.o verify.o -o permutation

main.o: main.c verify.h
	$(CC) $(CFLAGS) -c main.c

#Removed for student code
#verify.o: verify.c verify.h
#	$(CC) $(CFLAGS) -c verify.c

clean:
	rm main.o permutation
