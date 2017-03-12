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

#define DELIMITER "------------------------\n"

void print_usage()
{
    printf("s => generate sinus\n");
    printf("q => generate square\n");
    printf("r => generate ramp\n");
    printf("c => generate counter\n");
    printf("p => generate squares\n");
    printf("n - number of samples\n");
    printf("a - amplitude\n");
    printf("k - minimum noise level\n");
    printf("l - maximum noise level\n");
    printf("w - window size\n");
    printf("v - calculate average\n");
    printf("f - perform filtering\n");
    printf("g - perform simple filtering\n");
    printf("o - ratio for square wave\n");
    printf("t - ramp slope type <1-4>\n");
}

void print_configuration(Generator *g)
{
    printf(" Number of samples: %d\n", g->noSamples);
    printf(" Amplitude: %.2f\n", g->amplitude);
    printf(" Enable noise: %d\n", g->enableNoise);
    printf(" Min noise: %.2f\n", g->minNoise);
    printf(" Max noise: %.2f\n", g->maxNoise);
    printf(" Scale factor: %.2f\n", g->scaleFactor);
    printf(" Ratio: %d\n", g->ratio);
    printf(" Window size: %d\n", g->windowSize);
    printf(" Slope type: %d\n", g->slope);
}

void print_header1(char* s)
{
    printf(DELIMITER);
    printf("%s", s);
    printf(DELIMITER);
}

 
int main(int argc, char *argv[])
{
    float* array;  // array holding sample values

    // default values
    Generator generator = {
                           256,    // number of samples
                           1.0,    // amplitude scale factor
			   false,  // enable noise
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
    int simple_filt = 0;   // select simple filtering

    while ((option = getopt(argc, argv,"sqrcpn:a:e:k:l:w:vfgo:t:h")) != -1) {
        switch (option) {
             case 's' : select = 1;
                        break;
             case 'q' : select = 2;
                        break;
             case 'r' : select = 3;
                        break;
             case 'c' : select = 4;
                        break;
             case 'p' : select = 5;
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
             case 'g' : simple_filt = 1;
                        break;
             case 'o' : generator.ratio = atof(optarg);
                        break;
             case 't' : if (atoi(optarg) > 4)
	                {
			    printf("Error to large!\n");
			    exit(-1);
			}
			else
			{
	                    generator.slope = atoi(optarg);
			}
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
	print_header1("     Generate Sinus\n");
        array = sinus_array(&generator);
    }
    else if (select == 2)
    {
	print_header1("     Generate Square\n");
        array = square_array(&generator);
    }
    else if (select == 3)
    {
	print_header1("     Generate Ramp\n");
        array = ramp_array(&generator);
    }
    else if (select == 4)
    {
	print_header1("     Generate Counter\n");
        array = counter_array(&generator);
    }
    else if (select == 5)
    {
	print_header1("     Generate Squares\n");
        array = power_of_2(&generator);
    }

    print_configuration(&generator);

    if (filt == 0 && simple_filt == 0)
    {
        printf("                \n");
        printf(" Calc average\n");
        printf("                \n");
        calculateAverage(array, &generator);
    }
    else if (filt == 1 && simple_filt == 0)
    {
        printf("                \n");
        printf(" Perform filtering\n");
        printf("                \n");
        filter(array, &generator);
    }
    else if (simple_filt == 1)
    {
        printf("                \n");
        printf(" Perform simple filtering\n");
        printf("                \n");
        simple_filter(array, &generator);
    }



    free(array);
 
    return 0;
}

