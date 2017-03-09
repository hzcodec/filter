#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ring_buffer.h"

int main(int argc, char *argv[])
{
    RingBuffer myBuff;
    int value = 0;

    rb_init(&myBuff, 4);

    for (int i=0; i<5; i++)
    {
        rb_push(&myBuff, 100+i);
    }
    value = rb_pop(&myBuff);
    printf("value:%d\n", value);
    value = rb_pop(&myBuff);
    printf("value:%d\n", value);

    rb_push(&myBuff, 800);
    rb_push(&myBuff, 900);

    value = rb_pop(&myBuff);
    printf("value:%d\n", value);
    value = rb_pop(&myBuff);
    printf("value:%d\n", value);
    value = rb_pop(&myBuff);
    printf("value:%d\n", value);
    value = rb_pop(&myBuff);
    printf("value:%d\n", value);

    rb_free(&myBuff);

    return 0;
}
