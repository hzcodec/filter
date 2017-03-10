#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ring_buffer.h"

#define LOCAL_BUFFER_SIZE  BUFFER_SIZE_128

static int indata[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
static int outdata[16] = {1,4,9,16,25,36,49,64,81,100,121,144,169,196,225,256};
//static float outdata[16] = {1.0,8.0,27.0,64.0,125.0,216.0,343.0,512.0,729.0,1000.0,1331.0,1728.0,2197.0,2744.0,3375.0,4096.0};
float ramp_indata[256];
static FILE *fp;

void init_fill(RingBuffer *b)
{
    for (int i=0; i<LOCAL_BUFFER_SIZE; i++)
    {
        //rb_push(b, outdata[i]);
        rb_push(b, ramp_indata[i]);
    }
}


void read_rampdata(void)
{
    fp = fopen("ramp_samples.txt", "r");

    if (fp == NULL)
    {
        printf("Error: File does not exist\n");
        exit(-1);
    }

    for (int i=0; i<512; i++)
    {
        fscanf(fp, "%f,",&ramp_indata[i]);
	printf("%s() - data[%d]:%.2f\n", __func__, i, ramp_indata[i]);
    }

    fclose(fp);
}


int main(int argc, char *argv[])
{
    RingBuffer myBuff;
    
    read_rampdata();

    rb_init(&myBuff, LOCAL_BUFFER_SIZE);

    init_fill(&myBuff);
    rb_peek(&myBuff);

    for (int i=0; i<120; i++)
    {
        ///rb_push(&myBuff, outdata[i+4]);
        rb_push(&myBuff, ramp_indata[i+LOCAL_BUFFER_SIZE-1]);
        rb_peek(&myBuff);
    }

    rb_free(&myBuff);
    close_fp();

    return 0;
}
