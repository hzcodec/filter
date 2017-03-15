/*
    Auther       : Heinz Samuelsson
    Date         : 2017-03-06
    File         : circular_buffer2.c
    Reference    : http://codereview.stackexchange.com/questions/16468/circular-ringbuffer
    Description  : Ring buffer.
                   
		   +------+------+------+------+
		   |      |      |      |      |
		   |      |      |      |      |
		   +------+------+------+------+
*/ 
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include "ring_buffer.h" 

static FILE *fp;
static int loopCounter = 0;

void rb_init(RingBuffer* rb, int size)
{
    rb->buffer = malloc(sizeof(float) * size);
    rb->buffer_end = rb->buffer + size;
    rb->size = size;
    rb->data_start = rb->buffer;
    rb->data_end = rb->buffer;
    rb->last = rb->buffer;
    rb->count = 0;
    printf("%s() - start:%p, end: %p, buffer_end:%p\n", __func__, rb->data_start, rb->data_end, rb->buffer_end);

    fp = fopen("logfiles/slope.txt", "w");
}


void rb_free(RingBuffer* rb)
{
    free(rb->buffer);
}


bool rb_push(RingBuffer* rb, float data)
{
    //printf("1.%s() - start:%p, end: %p, count:%d, data:%d\n", __func__, rb->data_start, rb->data_end, rb->count, data);
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

    //printf("2.%s() - start:%p, end: %p, count:%d, data:%d\n\n", __func__, rb->data_start, rb->data_end, rb->count, data);
    return true;
}


float rb_pop(RingBuffer* rb)
{
    if (rb == NULL || rb->buffer == NULL)
    {
        return false;
    }

    float data = *rb->data_start;
    //printf("3.%s() - start:%p, end: %p, count:%d, data:%.2f\n\n", __func__, rb->data_start, rb->data_end, rb->count, data);
    rb->data_start++;

    if (rb->data_start == rb->buffer_end)
    {
        rb->data_start = rb->buffer;
    }

    rb->count--;

    //printf("%s() - start:%p, end: %p, buffer_end:%p, count:%d\n", __func__, rb->data_start, rb->data_end, rb->buffer_end, rb->count);

    return data;
}


void rb_peek(RingBuffer* rb, int windowSize)
{
    float *start;
    float *end;
    float data;               // current sampled data within the window
    float average_data = 0.0; // calculated average data within the window
    int dataCounter = 0;
 
    start = rb->data_start;
    end = rb->data_end;

    printf("data_end:%.4f, last:%.4f\n", *rb->data_end, *rb->last);

    // calculate slope collected in the window
    // HzS -  testing to skip divisor float slope = (*rb->last - *rb->data_end) / (float)windowSize;
    float slope = (*rb->last - *rb->data_end);
    printf("  --> slope:%.4f <--\n", slope);
    fprintf(fp, "%.4f\n", slope);

    for (int i=0; i<windowSize; i++)
    {
        data = *start;
	average_data = average_data + data;
        //printf("%s() - start:%p, end: %p, data:%.4f, cnt:%d, [%d]\n", __func__, start, end, data, loopCounter, dataCounter);
        start++;

        if (start == rb->buffer_end)
        {
            start = rb->buffer;
        }

	dataCounter++;
        rb->count--;
    }

    loopCounter++;

    //printf("%s() - average_data:%.4f\n", __func__, average_data/(float)windowSize);
    //printf("\n");
}


float rb_first(RingBuffer* rb)
{
    float data = *rb->data_start;
    return data;
}


float rb_last(RingBuffer* rb)
{
    float data = *rb->last;
    //printf("%s() - data:%d, last:%p\n", __func__, data, rb->last);
    return data;
}


bool rb_full(RingBuffer* rb)
{
    return rb->count == rb->size;
}


void close_fp(void)
{
    fclose(fp);
}
