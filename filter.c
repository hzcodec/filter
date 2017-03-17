/*
    Auther       : Heinz Samuelsson
    Date         : 2017-03-02
    File         : filter.c
    Reference    : -
    Description  : Filtering function.
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "generator.h"

static float new = 0.0;
static float last = 0.0;

void print_header3(FILE *fp, Generator *gen, char *s)
{
        fprintf(fp, "Input signal type: %s\n", s); 
        fprintf(fp, "noSamples: %d\n", gen->noSamples); 
        fprintf(fp, "amplitude: %.4f\n", gen->amplitude);
        fprintf(fp, "alpha: %.4f\n", gen->alpha);
        fprintf(fp, "enableNoise: %d\n", gen->enableNoise);
        fprintf(fp, "minNoise: %.4f\n", gen->minNoise); 
        fprintf(fp, "maxNoise: %.4f\n", gen->maxNoise);
        fprintf(fp, "scaleFactor: %.4f\n", gen->scaleFactor);
        fprintf(fp, "ratio: %d\n", gen->ratio);
        fprintf(fp, "windowSize: %d\n", gen->windowSize);
        fprintf(fp, "Slope: %d\n", gen->slope);
}

void filter(float *ar, Generator *gen)
{
        FILE *fp;
        fp = fopen("logfiles/filter.txt", "w");

	print_header3(fp, gen, "Filter Sinus");

        for(int n=0; n<gen->noSamples; n++)
        {
                new = ar[n];
                new = last + gen->alpha*(new - last);
		//printf("ar[%d]:%.4f, new:%.4f, last:%.4f, diff:%.4f\n", n, ar[n], new, last, (new-last));

                fprintf(fp, "%.4f\n", new);
                last = new;
        }

	fclose(fp);
}


// this is the same as above, just slightly another implementation
void simple_filter(float *ar, Generator *gen)
{
        FILE *fp;
        fp = fopen("logfiles/simple_filter.txt", "w");

	print_header3(fp, gen, "Simple Filter Sinus");

	float out_new;
	float out_old;

        for(int n=0; n<gen->noSamples; n++)
        {
                out_new = 0.1*ar[n] + 0.9*out_old;
		out_old = out_new;

                fprintf(fp, "%.4f\n", out_new);
        }

	fclose(fp);
}
