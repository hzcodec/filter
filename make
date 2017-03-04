gcc sinus_generator.c -c

gcc generator.c -c
gcc main.c -c
gcc sinus_generator.o main.o -lm
