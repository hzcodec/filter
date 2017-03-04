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

float* sinus_array(Generator *gen)
{
        FILE *fp;
	float noise = 0.0;

        fp = fopen("sinus_samples.txt", "w");
        
        float deg = 0.0;
        float rad = 0.0;
        float *ar = (float *)malloc(sizeof(float) * gen->noSamples);    
        
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
        
        return ar;
}


float* square_array(Generator *gen)
{
        FILE *fp;
	float noise = 0.0;
	float out;

        fp = fopen("square_samples.txt", "w");
        float *ar = (float *)malloc(sizeof(float) * (float)gen->noSamples);    
	float stop = (float)gen->dutyCycle/100.0 * (float)gen->noSamples;

        for (int i=0; i<(int)stop; i++)
        {
               if (gen->enableNoise == true)
               {
                       noise = gen_noise(gen);
               }

               ar[i] = out + noise;
               fprintf(fp, "%.4f\n", out + noise);
        }

        out = 1.0;
        for (int i=(int)stop+1; i<256; i++)
        {
               if (gen->enableNoise == true)
               {
                       noise = gen_noise(gen);
               }

               ar[i] = out + noise;
               fprintf(fp, "%.4f\n", out + noise);
        }

        return ar;
}
