#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ring_buffer.h"

int indata[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
int outdata[16] = {1,4,9,16,25,36,49,64,81,100,121,144,169,196,225,256};

void init_fill(RingBuffer *b)
{
    for (int i=0; i<BUFFER_SIZE_TEST; i++)
    {
        rb_push(b, outdata[i]);
    }
}

int main(int argc, char *argv[])
{
    RingBuffer myBuff;
    int value = 0;

    rb_init(&myBuff, BUFFER_SIZE_TEST);
    init_fill(&myBuff);

    value = rb_pop(&myBuff);
    printf("value:%d\n", value);
    value = rb_pop(&myBuff);
    printf("value:%d\n", value);
    value = rb_pop(&myBuff);
    printf("value:%d\n", value);

    rb_free(&myBuff);

    return 0;
}
