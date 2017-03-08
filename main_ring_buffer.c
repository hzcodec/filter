#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ring_buffer.h"

int main(int argc, char *argv[])
{
    RingBuffer myBuff;
    int value = 0;

    rb_init(&myBuff, 4);

    for (int i=0; i<6; i++)
    {
        rb_push(&myBuff, 100+i);
    }

    //printf("buffer_end:%d\n", *myBuff.buffer_end);
    //printf("data_start:%d\n", *myBuff.data_start);
    //printf("data_end:%d\n", *myBuff.data_end);
    //printf("count:%d\n", myBuff.count);
    //printf("size:%d\n", myBuff.size);

    //for (int i=0; i<8; i++)
    //{
    //    value = rb_pop(&myBuff);
    //    printf("value[%d]:%d\n", i, value);
    //}

    //printf("buffer_end:%d\n", *myBuff.buffer_end);
    //printf("data_start:%d\n", *myBuff.data_start);
    //printf("data_end:%d\n", *myBuff.data_end);
    //printf("count:%d\n", myBuff.count);
    //printf("size:%d\n", myBuff.size);

    rb_free(&myBuff);

    return 0;
}
