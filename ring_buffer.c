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
    rb->last = rb->buffer;
    rb->count = 0;
    printf("%s() - start:%p, end: %p, buffer_end:%p\n", __func__, rb->data_start, rb->data_end, rb->buffer_end);
}

void rb_free(RingBuffer* rb)
{
    free(rb->buffer);
}


void calc_average(RingBuffer *buff)
{
    int *tmp;
    tmp = buff->data_start;

    //printf("buff->last:%d\n", *buff->last);

    printf("buff->start:%d\n", *tmp);
    tmp++;
    printf("buff->start:%d\n", *tmp);
    tmp++;
    printf("buff->start:%d\n", *tmp);
    tmp++;
    printf("buff->start:%d\n", *tmp);
    tmp++;
}


bool rb_push(RingBuffer* rb, int data)
{
    printf("1.%s() - start:%p, end: %p, count:%d, data:%d\n", __func__, rb->data_start, rb->data_end, rb->count, data);
    if (rb == NULL || rb->buffer == NULL)
    {
        return false;
    }

    *rb->data_end = data;
    rb->last = rb->data_end;  // temp save the last values position
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

    printf("2.%s() - start:%p, end: %p, count:%d, data:%d\n\n", __func__, rb->data_start, rb->data_end, rb->count, data);
    return true;
}

int rb_pop(RingBuffer* rb)
{
    if (rb == NULL || rb->buffer == NULL)
    {
        return false;
    }

    int data = *rb->data_start;
    printf("3.%s() - start:%p, end: %p, count:%d, data:%d\n\n", __func__, rb->data_start, rb->data_end, rb->count, data);
    rb->data_start++;

    if (rb->data_start == rb->buffer_end)
    {
        rb->data_start = rb->buffer;
    }

    rb->count--;

    //printf("%s() - start:%p, end: %p, buffer_end:%p, count:%d\n", __func__, rb->data_start, rb->data_end, rb->buffer_end, rb->count);

    return data;
}

void rb_pop2(RingBuffer* rb)
{
    int *start;
    int *end;
    int data;
 
    start = rb->data_start;
    end = rb->data_end;

    for (int i=0; i<4; i++)
    {
        data = *start;
        printf("4.%s() - start:%p, end: %p, data:%d\n", __func__, start, end, data);
        start++;

        if (start == rb->buffer_end)
        {
            start = rb->buffer;
        }

    rb->count--;

    }
    printf("\n");
}


int rb_first(RingBuffer* rb)
{
    int data = *rb->data_start;
    return data;
}

int rb_last(RingBuffer* rb)
{
    int data = *rb->last;
    //printf("%s() - data:%d, last:%p\n", __func__, data, rb->last);
    return data;
}


bool rb_full(RingBuffer* rb)
{
    return rb->count == rb->size;
}
