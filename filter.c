/*
    Auther       : Heinz Samuelsson
    Date         : 2017-03-02
    File         : filter.c
    Reference    : -
    Description  : 
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

static float new = 0.0;
static float last = 0.0;

void filter(float *ar)
{
        FILE *fp;
        fp = fopen("filter.txt", "w");

        for(int n=0; n<256; n++)
        {
                new = ar[n];
                new = last + 0.1*(new - last);

                fprintf(fp, "%.4f\n", new);
                last = new;
        }

	fclose(fp);
}
