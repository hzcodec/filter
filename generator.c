/*
    Auther       : Heinz Samuelsson
    Date         : 2017-03-02
    File         : generator.c
    Reference    : 
    Description  : Generating sinus data and store it in a file. Noise can be added.
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "generator.h"

static bool swap = false;
static float noise = 0.0;

float rand_interval(float min, float max)
{
    int r;
    const float range = 1 + max - min;
    const float buckets = RAND_MAX / range;
    const float limit = buckets * range;

    do
    {
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);
}

// generate noise
float gen_noise(Generator *gen)
{
        noise = rand_interval(gen->minNoise, gen->maxNoise) / gen->scaleFactor;
      	if (swap == true)
      	{
      	        noise = noise * (-1.0);
      	}

      	swap = !swap;
	return noise;
}

void print_header(FILE *fp, Generator *gen)
{
        fprintf(fp, "noSamples: %d\n", gen->noSamples); 
        fprintf(fp, "amplitude: %.2f\n", gen->amplitude);
        fprintf(fp, "enableNoise: %d\n", gen->enableNoise);
        fprintf(fp, "minNoise: %.2f\n", gen->minNoise); 
        fprintf(fp, "maxNoise: %.2f\n", gen->maxNoise);
        fprintf(fp, "scaleFactor: %.2f\n", gen->scaleFactor);
        fprintf(fp, "ratio: %d\n", gen->ratio);
        fprintf(fp, "windowSize: %d\n", gen->windowSize);
}

#define MAX_NOISE 3.6
#define MIN_NOISE 0.1
float* ramp_array(Generator *gen)
{
        FILE *fp;
	float val;
	float noise = 0.0;

        float *ar = (float *)malloc(sizeof(float) * gen->noSamples);    

        fp = fopen("ramp_samples.txt", "w");

	print_header(fp, gen);

        for (int i=0; i<60; i++)
	{
            noise = rand_interval(gen->minNoise, gen->maxNoise);
	    fprintf(fp, "%.4f\n", 3.0 + noise);
	    ar[i] = 3.0 + noise;
	}

        for (int i=61; i<120; i++)
        //for (int i=61; i<81; i++)
	{
	    val = 1.0/6.0 * (i-60) + 3.0;
            noise = rand_interval(gen->minNoise, gen->maxNoise);
	    fprintf(fp, "%.4f\n", val + noise);
	    ar[i] = val + noise;
	}

        for (int i=121; i<256; i++)
        //for (int i=82; i<90; i++)
	{
            noise = rand_interval(gen->minNoise, gen->maxNoise);
	    fprintf(fp, "%.4f\n", 10.0 + noise);
	    ar[i] = 10.0 + noise;
	}

        //for (int i=91; i<256; i++)
	//{
        //    noise = rand_interval(gen->minNoise, gen->maxNoise);
	//    fprintf(fp, "%.4f\n", 2.0 + noise);
	//    ar[i] = 2.0 + noise;
	//}

	fclose(fp);

	return ar;
}

float* sinus_array(Generator *gen)
{
        FILE *fp;
	float noise = 0.0;

        fp = fopen("sinus_samples.txt", "w");
        
        float deg = 0.0;
        float rad = 0.0;
        float *ar = (float *)malloc(sizeof(float) * gen->noSamples);    

	print_header(fp, gen);

        for (int i=0; i<gen->noSamples; i++)
        {
	        if (gen->enableNoise == true)
		{
                        noise = rand_interval(gen->minNoise, gen->maxNoise) / gen->scaleFactor;
			if (swap == true)
			{
			        noise = noise * (-1.0);
			}
			swap = !swap;
		}

                deg = (float)i*(360.0 / gen->noSamples);
                rad = gen->amplitude * sin(deg * M_PI / 180) + noise;

                fprintf(fp, "%.4f\n", rad);
                ar[i] = rad;
        }

	fclose(fp);

        return ar;
}

float* square_array(Generator *gen)
{
        FILE *fp;
	float noise = 0.0;
	float out;

        fp = fopen("square_samples.txt", "w");
        float *ar = (float *)malloc(sizeof(float) * (float)gen->noSamples);    
	float dist = (float)gen->ratio/100.0 * (float)gen->noSamples;
	float start = (float)gen->noSamples/2.0 - dist/2.0;
	float stop = (float)gen->noSamples/2.0 + dist/2.0;

	print_header(fp, gen);

	for (int i=0; i<((int)start); i++)
	{
                noise = gen_noise(gen);
                ar[i] = out + noise;
                fprintf(fp, "%.4f\n", out + noise);
	}

	out = 1.0;
	for (int i=start+1; i<((int)stop); i++)
	{
                noise = gen_noise(gen);
                ar[i] = out + noise;
                fprintf(fp, "%.4f\n", out + noise);
	}

	out = 0.0;
	for (int i=stop+1; i<((int)gen->noSamples); i++)
	{
                noise = gen_noise(gen);
                ar[i] = out + noise;
                fprintf(fp, "%.4f\n", out + noise);
	}

	fclose(fp);
        return ar;
}
