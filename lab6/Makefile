CC=gcc
CFLAGS= -Wall -Werror -std=c99

all: matMult

matMult: main.o matrix.o verify.o
	$(CC) main.o matrix.o verify.o -o matMult

main.o: main.c 
	$(CC) $(CFLAGS) -c -g main.c

matrix.o: matrix.c 
	$(CC) $(CFLAGS) -c -g matrix.c

#Removed for student code
#verify.o: verify.c
#	$(CC) $(CFLAGS) -c verify.c

clean:
	rm main.o matMult
