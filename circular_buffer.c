/*
    Auther       : Heinz Samuelsson
    Date         : 2017-03-06
    File         : circular_buffer.c
    Reference    : -
    Description  : Ring buffer.
*/ 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>
 
 
#define BUFFER_SIZE 8

float buffer[BUFFER_SIZE];
int start = 0;
int end = 0;
int wrap = 0;

void PushToQueue(float *p)
{
    printf("Pushed data: %.2f at index: %d, wrap: %d, start: %d\n", *p, end, wrap, start);

    buffer[end] = *p;
    end = (end + 1) % BUFFER_SIZE;

    if (wrap < BUFFER_SIZE)
    {
        wrap++;
    } 
    else 
    {
        /* Overwriting the oldest. Move start to next-oldest */
        start = (start + 1) % BUFFER_SIZE;
	printf("Wrap around\n");
    }
}

float RetrieveFromQueue(void)
{
    float p;

    if (!wrap) 
    {
	printf("NULL\n");
        exit(-1);
    }

    p = buffer[start];
    start = (start + 1) % BUFFER_SIZE;

    wrap--;
    return p;
}


int main(int argc, char *argv[])
{
 
    float val = 1.0;
    float *pVal = &val;

    for (int i=0; i<8; i++)
    {
        PushToQueue(&val);
        val = val + 1.0;
    }

    PushToQueue(&val);
    val = val + 1.0;
    PushToQueue(&val);
    val = val + 1.0;
    PushToQueue(&val);
    val = val + 1.0;
    PushToQueue(&val);
    val = val + 1.0;
    PushToQueue(&val);
    val = val + 1.0;
    PushToQueue(&val);
    val = val + 1.0;
    PushToQueue(&val);
    val = val + 1.0;
    PushToQueue(&val);
    val = val + 1.0;
    PushToQueue(&val);
    val = val + 1.0;
    PushToQueue(&val);

    for (int i=0; i<8; i++)
    {
        val = RetrieveFromQueue();
        printf("val[%d]:%.2f\n", i, val);
    }

    val = val + 1.0;
    PushToQueue(&val);

    return 0;
}
