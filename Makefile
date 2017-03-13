CC     = gcc
CFLAGS = -std=c99

m1: main.c
	$(CC) main.c -c
	$(CC) generator.c -c
	$(CC) filter.c -c
	$(CC) average.c -c
	gcc  generator.o filter.o average.o main.o -lm -o gen

m2: main_ring_buffer.c
	$(CC) main_ring_buffer.c -c
	$(CC) ring_buffer.c -c
	gcc  main_ring_buffer.o ring_buffer.o -o rb

clean:
	rm -f a.out *.txt *.o gen rb logfiles/*.txt

flush:
	rm -f logfiles/*.txt
