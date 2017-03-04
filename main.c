/*
    Auther       : Heinz Samuelsson
    Date         : 2017-03-03
    File         : main.c
    Reference    : -
    Description  : -
*/ 
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "generator.h"
 
int main(int argc, char *argv[])
{
    float* array;

    Generator generator = {
                           256,    // number of samples
                           1.0,    // amplitude scale factor
			   true,  // enable noise
			   0.1,    // min noise level
			   0.2,    // max noise level
			   12.0,   // scale factor of noise level
			   80,     // duty cycle for square wave
			  };

    array = sinus_array(&generator);
    array = square_array(&generator);
    free(array);
 
    return 0;
}

