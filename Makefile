CC     = gcc
CFLAGS = -std=c99

all: main.c
	$(CC) main.c -c
	$(CC) generator.c -c
	$(CC) filter.c -c
	$(CC) average.c -c
	gcc  generator.o filter.o average.o main.o -lm

clean:
	rm -f a.out *.txt *.o
