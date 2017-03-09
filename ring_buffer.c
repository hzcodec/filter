/*
    Auther       : Heinz Samuelsson
    Date         : 2017-03-06
    File         : circular_buffer2.c
    Reference    : http://codereview.stackexchange.com/questions/16468/circular-ringbuffer
    Description  : Ring buffer.
*/ 
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ring_buffer.h" 

void rb_init(RingBuffer* rb, int size)
{
    rb->buffer = malloc(sizeof(int) * size);
    rb->buffer_end = rb->buffer + size;
    rb->size = size;
    rb->data_start = rb->buffer;
    rb->data_end = rb->buffer;
    rb->count = 0;
    printf("%s() - start:%p, end: %p, buffer_end:%p\n", __func__, rb->data_start, rb->data_end, rb->buffer_end);
}

void rb_free(RingBuffer* rb)
{
    free(rb->buffer);
}

bool rb_push(RingBuffer* rb, int data)
{
    if (rb == NULL || rb->buffer == NULL)
    {
        return false;
    }

    *rb->data_end = data;
    //printf("1.%s() - data_end: %d\n", __func__, *rb->data_end);
    rb->data_end++;

    if (rb->data_end == rb->buffer_end)
    {
        rb->data_end = rb->buffer;
    }

    if (rb_full(rb))
    {
        if ((rb->data_start + 1) == rb->buffer_end)
        {
            rb->data_start = rb->buffer;
	}
        else
	{
            rb->data_start++;
	}
    } 
    else
    {
        rb->count++;
    }

    printf("%s() - start:%p, end: %p, buffer_end:%p, count:%d\n", __func__, rb->data_start, rb->data_end, rb->buffer_end, rb->count);
    return true;
}

int rb_pop(RingBuffer* rb)
{
    if (rb == NULL || rb->buffer == NULL)
    {
        return false;
    }

    int data = *rb->data_start;
    rb->data_start++;

    if (rb->data_start == rb->buffer_end)
    {
        rb->data_start = rb->buffer;
    }

    rb->count--;

    printf("%s() - start:%p, end: %p, buffer_end:%p, count:%d\n", __func__, rb->data_start, rb->data_end, rb->buffer_end, rb->count);

    return data;
}

bool rb_full(RingBuffer* rb)
{
    return rb->count == rb->size;
}
