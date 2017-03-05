/*
    Auther       : Heinz Samuelsson
    Date         : 2017-03-05
    File         : average.c 
    Reference    : -
    Description  : -
*/ 
 
 
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_SIZE 10

 
void calculateAverage(float* a)
{
        FILE *fp;
        fp = fopen("average.txt", "w");
        float sum;
        
        for(int startPoint=0; startPoint<256; startPoint++)
	{
	    sum = 0.0;

            for(int i=startPoint; i<startPoint+WINDOW_SIZE; i++)
            {
                sum = sum + a[i];
	        printf("start:%d, i:%d, a:%.4f, sum:%.4f\n", startPoint, i, a[i], sum);
		//fprintf(fp, "startPoint:%d, i:%d, a:%.4f, sum: %.4f\n", startPoint, i, a[i], sum);
            }
            fprintf(fp, "%.2f\n", sum / WINDOW_SIZE);
	}

	fclose(fp);
}

