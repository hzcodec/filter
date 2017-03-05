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
#include "average.h"
#include "filter.h"
 
int main(int argc, char *argv[])
{
    float* array;

    Generator generator = {
                           256,    // number of samples
                           1.0,    // amplitude scale factor
			   true,  // enable noise
			   0.1,    // min noise level
			   0.3,    // max noise level
			   10.0,   // scale factor of noise level
			   20,     // square wave ratio
			   30,     // window size
			  };

    if (argc < 2) {
        printf("Usage: <number of samples> <window size>\n");
	exit(-1);
    }

    generator.noSamples = atoi(argv[1]);
    generator.windowSize = atoi(argv[2]);

    array = sinus_array(&generator);
    //array = square_array(&generator);

    //calculateAverage(array, &generator);
    filter(array, &generator);

    free(array);
 
    return 0;
}

