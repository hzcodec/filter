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
#include <string.h>
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


void print_header(FILE *fp, Generator *gen, char *s)
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


float* ramp_array(Generator *gen)
{
        FILE *fp;
	float yVal;
	float noise = 0.0;
	float part;
	float minValue = 1;
	int   rampStartValue = 0.1 * gen->noSamples; // start condition 10% of max samples
	int   idx1;

        float *ar = (float *)malloc(sizeof(float) * gen->noSamples);    
        fp = fopen("logfiles/ramp_samples.txt", "w");

	char *str = "Ramp ";
	char c = gen->slope + '0';
	size_t len = strlen(str);
        char *str2 = malloc(len + 1 + 1 ); /* one for extra char, one for trailing zero */
        strcpy(str2, str);
        str2[len] = c;
        str2[len + 1] = '\0';

	print_header(fp, gen, str2);

        for (int i=0; i<rampStartValue; i++)
	{
	    if (gen->enableNoise == true)
	    {
                noise = rand_interval(gen->minNoise, gen->maxNoise);
	    }
	    fprintf(fp, "%.4f\n", minValue + noise);
	    ar[i] = minValue + noise;
	}

	switch(gen->slope)
	{
	    case 1: idx1 = (int)(0.05*(float)gen->noSamples);
	            part = 0.05; // 5%
		    break;
	    case 2: idx1 = (int)(0.25*(float)gen->noSamples);
	            part = 0.25; // 25%
		    break;
	    case 3: idx1 = (int)(0.50*(float)gen->noSamples);
	            part = 0.50; // 50%
		    break;
	    case 4: idx1 = (int)(0.75*(float)gen->noSamples);
	            part = 0.75; // 75%
		    break;
            default: idx1 = 200;
	             part = 0.05;
		     break;
	}

        for (int i=rampStartValue; i<rampStartValue+idx1; i++)
	{
            float k = (gen->amplitude-minValue)/(float)((rampStartValue+idx1) - rampStartValue);
	    yVal = k*(i-rampStartValue) + minValue;
	    if (gen->enableNoise == true)
	    {
                noise = rand_interval(gen->minNoise, gen->maxNoise);
	    }
	    fprintf(fp, "%.4f\n", yVal + noise);
	    ar[i] = yVal + noise;
	}

        for (int i=rampStartValue+idx1; i<gen->noSamples; i++)
	{
	    if (gen->enableNoise == true)
	    {
                noise = rand_interval(gen->minNoise, gen->maxNoise);
	    }
	    fprintf(fp, "%.4f\n", gen->amplitude + noise);
	    ar[i] = gen->amplitude + noise;
	}

	fclose(fp);

	return ar;
}


float* sinus_array(Generator *gen)
{
        FILE *fp;
	float noise = 0.0;

        fp = fopen("logfiles/sinus_samples.txt", "w");

	print_header(fp, gen, "Sinus");
        
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

	fclose(fp);

        return ar;
}


float* counter_array(Generator *gen)
{
        FILE *fp;
	float counter = 1.0;

        fp = fopen("logfiles/counter_samples.txt", "w");
	print_header(fp, gen, "Counter");

        
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
	float out = 0.0;

        fp = fopen("logfiles/square_samples.txt", "w");

	print_header(fp, gen, "Square");

        float *ar = (float *)malloc(sizeof(float) * (float)gen->noSamples);    
	float dist = (float)gen->ratio/100.0 * (float)gen->noSamples;
	float start = (float)gen->noSamples/2.0 - dist/2.0;
	float stop = (float)gen->noSamples/2.0 + dist/2.0;

	for (int i=0; i<((int)start); i++)
	{
	    if (gen->enableNoise == true)
	    {
                noise = gen_noise(gen) / gen->scaleFactor;
	    }
            ar[i] = (out + noise) * gen->amplitude;
            fprintf(fp, "%.4f\n", (out + noise) * gen->amplitude);
	    //printf("ar[%d]:%.4f\n", i, ar[i]);
	}

	out = 1.0;
	for (int i=start+1; i<((int)stop); i++)
	{
	    if (gen->enableNoise == true)
	    {
                noise = gen_noise(gen) / gen->scaleFactor;
	    }
            ar[i] = (out + noise) * gen->amplitude;
            fprintf(fp, "%.4f\n", (out + noise) * gen->amplitude);
	}

	out = 0.0;
	for (int i=stop+1; i<((int)gen->noSamples+2); i++)
	{
	    if (gen->enableNoise == true)
	    {
                noise = gen_noise(gen) / gen->scaleFactor;
	    }
            ar[i] = (out + noise) * gen->amplitude;
            fprintf(fp, "%.4f\n", (out + noise) * gen->amplitude);
	}

	fclose(fp);
        return ar;
}


float* power_of_2(Generator *gen)
{
        FILE *fp;
	float counter = 1.0;

        fp = fopen("logfiles/power2_samples.txt", "w");

	print_header(fp, gen, "Power of 2");
        
        float *ar = (float *)malloc(sizeof(float) * gen->noSamples);    

        for (int i=0; i<gen->noSamples; i++)
        {
	        if (gen->enableNoise == true)
		{
                        noise = rand_interval(gen->minNoise, gen->maxNoise);
			if (swap == true)
			{
			        noise = noise * (-1.0);
			}
			swap = !swap;
		}
            fprintf(fp, "%.4f\n", (float)(i*i) + noise);
            ar[i] = counter;
        }

	fclose(fp);

        return ar;
}
