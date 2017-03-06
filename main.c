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
#include <string.h>
#include "generator.h"
#include "average.h"
#include "filter.h"
 
int main(int argc, char *argv[])
{
    float* array;  // array holding sample values

    // default values
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

    if (argc < 4) {
        printf("Usage: <s | q | r> <a | f> <number of samples> <window size> <min noise> <max noise>\n");
	exit(-1);
    }

    generator.noSamples = atoi(argv[3]);
    generator.windowSize = atoi(argv[4]);
    generator.minNoise = atoi(argv[5]);
    generator.maxNoise = atoi(argv[6]);

    if (!strcmp(argv[1],"s"))
    {
	printf("----------------\n");
	printf("Sinus generated\n");
	printf("----------------\n");
        array = sinus_array(&generator);
    }
    else if (!strcmp(argv[1],"q"))
    {
	printf("----------------\n");
	printf("Square generated\n");
	printf("----------------\n");
        array = square_array(&generator);
    }
    else
    {
	printf("----------------\n");
	printf("Ramp generated\n");
	printf("----------------\n");
        array = ramp_array(&generator);
    }


    if (!strcmp(argv[2],"a"))
    {
	printf("----------------\n");
	printf("Calc average\n");
	printf("----------------\n");
        calculateAverage(array, &generator);
    }
    else
    {
	printf("----------------\n");
	printf("Perform filtering\n");
	printf("----------------\n");
        filter(array, &generator);
    }

    free(array);
 
    return 0;
}

