/*
    Auther       : Heinz Samuelsson
    Date         : 2017-03-02
    File         : generator.c
    Reference    : 
    Description  : generator is generating sinus, square or a ramp signal. Values
    		   are stored in its corresponding file.
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "generator.h"

static bool swap = false;  // swap noise offset
static float noise = 0.0;  // global noise value

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
        fprintf(fp, "Slope: %d\n", gen->slope);
}


float* ramp_array(Generator *gen)
{
        FILE *fp;
	float yVal;
	float noise = 0.0;
	float part;
	float maxValue = 10;
	float minValue = 3;
	int idx1;

        float *ar = (float *)malloc(sizeof(float) * gen->noSamples);    

        fp = fopen("ramp_samples.txt", "w");

	//print_header(fp, gen);

        for (int i=0; i<40; i++)
	{
            noise = rand_interval(gen->minNoise, gen->maxNoise);
	    fprintf(fp, "%.4f\n", minValue); //+ noise);
	    ar[i] = minValue + noise;
	}

	switch(gen->slope)
	{
	    case 1: idx1 = (int)(0.05*(float)gen->noSamples);
	            part = 0.05;
		    break;
	    case 2: idx1 = (int)(0.25*(float)gen->noSamples);
	            part = 0.25;
		    break;
	    case 3: idx1 = (int)(0.50*(float)gen->noSamples);
	            part = 0.50;
		    break;
	    case 4: idx1 = (int)(0.75*(float)gen->noSamples);
	            part = 0.75;
		    break;
            default: idx1 = 200;
	             part = 0.05;
		     break;
	}

        for (int i=0; i<idx1; i++)
	{
            float k = (maxValue-minValue)/(part*gen->noSamples);
	    yVal = k*i + minValue;
            noise = rand_interval(gen->minNoise, gen->maxNoise);
	    fprintf(fp, "%.4f\n", yVal);
	    ar[i] = yVal;// + noise;
	}

        for (int i=idx1+1; i<gen->noSamples; i++)
	{
            noise = rand_interval(gen->minNoise, gen->maxNoise);
	    fprintf(fp, "%.4f\n", maxValue); // + noise);
	    ar[i] = maxValue;// + noise;
	}

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

	//print_header(fp, gen);

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


float* counter_array(Generator *gen)
{
        FILE *fp;
	float counter = 1.0;

        fp = fopen("counter_samples.txt", "w");
        
        float *ar = (float *)malloc(sizeof(float) * gen->noSamples);    

        for (int i=0; i<gen->noSamples; i++)
        {
            fprintf(fp, "%.4f\n", counter++);
            ar[i] = counter;
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

	//print_header(fp, gen);

	for (int i=0; i<((int)start); i++)
	{
                noise = gen_noise(gen) / gen->scaleFactor;
                ar[i] = (out + noise) * gen->amplitude;
                fprintf(fp, "%.4f\n", (out + noise) * gen->amplitude);
	}

	out = 1.0;
	for (int i=start+1; i<((int)stop); i++)
	{
                noise = gen_noise(gen) / gen->scaleFactor;
                ar[i] = (out + noise) * gen->amplitude;
                fprintf(fp, "%.4f\n", (out + noise) * gen->amplitude);
	}

	out = 0.0;
	for (int i=stop+1; i<((int)gen->noSamples); i++)
	{
                noise = gen_noise(gen) / gen->scaleFactor;
                ar[i] = (out + noise) * gen->amplitude;
                fprintf(fp, "%.4f\n", (out + noise) * gen->amplitude);
	}

	fclose(fp);
        return ar;
}
