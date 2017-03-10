#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ring_buffer.h"


int indata[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
//int outdata[16] = {1,4,9,16,25,36,49,64,81,100,121,144,169,196,225,256};
int outdata[16] = {1,8,27,64,125,216,343,512,729,1000,1331,1728,2197,2744,3375,4096};
float ramp_indata[256];

void init_fill(RingBuffer *b)
{
    for (int i=0; i<BUFFER_SIZE_TEST_4; i++)
    {
        //rb_push(b, outdata[i]);
        rb_push(b, ramp_indata[i]);
    }
}

void calc_slope(int first, int last)
{
   float k = (float)(last - first) / 3.0; 
   printf("  --> k:%.2f\n", k);
}


int main(int argc, char *argv[])
{
    FILE *fp;
    RingBuffer myBuff;

    fp = fopen("ramp_samples.txt", "r");

    if (fp == NULL)
    {
        printf("Error: File does not exist\n");
        exit(-1);
    }

    for (int i=0; i<256; i++)
    {
        fscanf(fp, "%f,",&ramp_indata[i]);
    }

    rb_init(&myBuff, BUFFER_SIZE_TEST_4);

    init_fill(&myBuff);
    rb_peek(&myBuff);

    for (int i=0; i<5; i++)
    {
	rb_push(&myBuff, outdata[i+4]);
        rb_peek(&myBuff);
    }

    rb_free(&myBuff);
    fclose(fp);

    return 0;
}
