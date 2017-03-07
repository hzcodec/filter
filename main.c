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
#include <getopt.h>
#include "generator.h"
#include "average.h"
#include "filter.h"

void print_usage()
{
    printf("s => generate sinus\n");
    printf("q => generate square\n");
    printf("r => generate ramp\n");
    printf("n - number of samples\n");
    printf("a - amplitude\n");
    printf("k - minimum noise level\n");
    printf("l - maximum noise level\n");
    printf("w - window size\n");
    printf("v - calculate average\n");
    printf("f - perform filtering\n");
    printf("o - ratio for square wave\n");
    printf("t - ramp slope type\n");
}

void print_configuration(Generator *g)
{
    printf("Number of samples: %d\n", g->noSamples);
    printf("Amplitude: %.2f\n", g->amplitude);
    printf("Enable noise: %d\n", g->enableNoise);
    printf("Min noise: %.2f\n", g->minNoise);
    printf("Max noise: %.2f\n", g->maxNoise);
    printf("Scale factor: %.2f\n", g->scaleFactor);
    printf("Ratio: %d\n", g->ratio);
    printf("Window size: %d\n", g->windowSize);
    printf("Slope type: %d\n", g->slope);
}

 
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
			   1,      // slope
			  };

    int option = 0;
    int select = 1; // select sinus/square/ramp, default sinus
    int filt = 0;   // select average calc or filtering

    while ((option = getopt(argc, argv,"sqrn:a:e:k:l:w:vfo:t:h")) != -1) {
        switch (option) {
             case 's' : select = 1;
                        break;
             case 'q' : select = 2;
                        break;
             case 'r' : select = 3;
                        break;
             case 'n' : generator.noSamples = atoi(optarg);
                        break;
             case 'a' : generator.amplitude = atof(optarg);
                        break;
             case 'e' : generator.enableNoise = atoi(optarg); 
                        break;
             case 'k' : generator.minNoise = atof(optarg); 
                        break;
             case 'l' : generator.maxNoise = atof(optarg); 
                        break;
             case 'w' : generator.windowSize = atoi(optarg); 
                        break;
             case 'v' : filt = 0;
                        break;
             case 'f' : filt = 1;
                        break;
             case 'o' : generator.ratio = atof(optarg);
                        break;
             case 't' : generator.slope = atoi(optarg);
                        break;
             case 'h' : print_usage();
	                exit(1);
                        break;
             default: print_usage(); 
                 exit(EXIT_FAILURE);
        }
    }

    if (select == 1)
    {
        printf("-----------------------\n");
        printf("Generate Sinus\n");
        printf("-----------------------\n");
        array = sinus_array(&generator);
    }
    else if (select == 2)
    {
        printf("-----------------------\n");
        printf("Generate Square\n");
        printf("-----------------------\n");
        array = square_array(&generator);
    }
    else if (select == 3)
    {
        printf("-----------------------\n");
        printf("Generate Ramp\n");
        printf("-----------------------\n");
        array = ramp_array(&generator);
    }

    print_configuration(&generator);

    if (filt == 0)
    {
        printf("                \n");
        printf("Calc average\n");
        printf("                \n");
        calculateAverage(array, &generator);
    }
    else if (filt == 1)
    {
        printf("                \n");
        printf("Perform filtering\n");
        printf("                \n");
        filter(array, &generator);
    }

    free(array);
 
    return 0;
}

