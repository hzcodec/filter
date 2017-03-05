gcc sinus_generator.c -c

gcc generator.c -c
gcc average.c -c
gcc main.c -c
gcc generator.o average.o main.o -lm
