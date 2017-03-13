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
    printf("Select type of signal to generate\n");
    printf(".................................\n");
    printf("  s => generate sinus\n");
    printf("  q => generate square\n");
    printf("  r => generate ramp\n");
    printf("  c => generate counter numbers\n");
    printf("  p => generate square numbers\n");
    printf("===========================================\n");
    printf("Change properties of the generated signal\n");
    printf(".........................................\n");
    printf("  n - number of samples [0 - 16384]\n");
    printf("  a - amplitude [0.0 - user def] (sinus / square)\n");
    printf("  e - enable noise [0/1]\n");
    printf("  k - minimum noise level [0.0 - 5.0] (sinus / ramp)\n");
    printf("  l - maximum noise level [0.0 - 5.0] (sinus / ramp)\n");
    printf("  w - window size [1 - 8192] ]\n");
    printf("  o - ratio (square)\n");
    printf("  t - ramp slope type [1-4]\n");
    printf("===========================================\n");
    printf("Select filtering type\n");
    printf(".....................\n");
    printf("  v - perform average calculation\n");
    printf("  f - perform filtering\n");
    printf("  g - perform simple filtering\n");
    printf("  y - alpha value for LP filter\n");
}


void print_configuration(Generator *g)
{
    printf(" Number of samples: %d\n", g->noSamples);
    printf(" Amplitude: %.4f\n", g->amplitude);
    printf(" Enable noise: %d\n", g->enableNoise);
    printf(" Min noise: %.4f\n", g->minNoise);
    printf(" Max noise: %.4f\n", g->maxNoise);
    printf(" Noise scale factor: %.4f\n", g->scaleFactor);
    printf(" Ratio: %d\n", g->ratio);
    printf(" Window size: %d\n", g->windowSize);
    printf(" Ramp slope type: %d\n", g->slope);
    printf(" Alpha value: %.4f\n", g->alpha);
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
			   0.1,    // alpha value
			   false,  // enable noise
			   0.1,    // min noise level
			   0.3,    // max noise level
			   2.0,   // scale factor of noise level
			   20,     // square wave ratio
			   30,     // window size
			   1,      // slope
			  };

    int option = 0;
    int select = 1; // select sinus/square/ramp, default sinus
    int filt = 0;   // select average calc or filtering
    int simple_filt = 0;   // select simple filtering

    while ((option = getopt(argc, argv,"sqrcpn:a:e:k:l:w:vfgo:t:y:h")) != -1) {
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
             case 'y' : generator.alpha = atof(optarg); 
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
        printf(" Filtering performed\n");
        printf("                \n");
        filter(array, &generator);
    }
    else if (simple_filt == 1)
    {
        printf("                \n");
        printf(" Simple filtering performed\n");
        printf("                \n");
        simple_filter(array, &generator);
    }

    free(array);
 
    return 0;
}

