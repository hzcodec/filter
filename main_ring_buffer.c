#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ring_buffer.h"

int indata[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
int outdata[16] = {1,4,9,16,25,36,49,64,81,100,121,144,169,196,225,256};

void init_fill(RingBuffer *b)
{
    for (int i=0; i<BUFFER_SIZE_TEST_4; i++)
    {
        rb_push(b, outdata[i]);
    }
}

void calc_slope(int first, int last)
{
   float k = (float)(last - first) / 3.0; 
   printf("  --> k:%.2f\n", k);
}


int main(int argc, char *argv[])
{
    RingBuffer myBuff;
    int value = 0;
    int offset = 0;
    int firstSampledValue = 0;
    int lastSampledValue = 0;

    rb_init(&myBuff, BUFFER_SIZE_TEST_4);

    init_fill(&myBuff);
    rb_pop2(&myBuff);

    for (int i=0; i<5; i++)
    {
	rb_push(&myBuff, outdata[i+4]);
        rb_pop2(&myBuff);
    }
    rb_free(&myBuff);

    return 0;
}
