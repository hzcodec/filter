/*
    Auther       : Heinz Samuelsson
    Date         : 2017-03-05
    File         : average.c 
    Reference    : -
    Description  : -
*/ 
 
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "generator.h"

void calculateAverage(float* a, Generator *gen)
{
        FILE *fp;
        fp = fopen("average.txt", "w");
        float sum;
        
        for(int startPoint=0; startPoint<gen->noSamples; startPoint++)
	{
	    sum = 0.0;

            for(int i=startPoint; i<startPoint+gen->windowSize; i++)
            {
                sum = sum + a[i];
	        //printf("start:%d, i:%d, a:%.4f, sum:%.4f\n", startPoint, i, a[i], sum);
		//fprintf(fp, "startPoint:%d, i:%d, a:%.4f, sum: %.4f\n", startPoint, i, a[i], sum);
            }
            fprintf(fp, "%.2f\n", sum / gen->windowSize);
	}

	fclose(fp);
}

