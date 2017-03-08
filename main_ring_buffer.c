#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ring_buffer.h"

int main(int argc, char *argv[])
{

//typedef struct
//{
//     int* buffer;
//     int* buffer_end;
//     int* data_start;
//     int* data_end;
//     int  count;
//     int  size;
// } RingBuffer;

    RingBuffer myBuff;
    int value = 0;

    rb_init(&myBuff, 8);

    rb_push(&myBuff, 100);
    rb_push(&myBuff, 200);
    rb_push(&myBuff, 300);

    printf("[0]:%d\n", myBuff.buffer[0]);
    printf("[1]:%d\n", myBuff.buffer[1]);
    printf("[2]:%d\n", myBuff.buffer[2]);

    value = rb_pop(&myBuff);
    printf("value:%d\n", value);
    value = rb_pop(&myBuff);
    printf("value:%d\n", value);
    value = rb_pop(&myBuff);
    printf("value:%d\n", value);
    value = rb_pop(&myBuff);
    printf("value:%d\n", value);

    return 0;
}
