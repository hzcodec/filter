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
int active = 0;

void PushToQueue(float *p)
{
    buffer[end] = *p;
    end = (end + 1) % BUFFER_SIZE;

    if (active < BUFFER_SIZE)
    {
        active++;
    } 
    else 
    {
        /* Overwriting the oldest. Move start to next-oldest */
        start = (start + 1) % BUFFER_SIZE;
    }
}

float RetrieveFromQueue(void)
{
    float p;

    if (!active) 
    {
	printf("NULL\n");
        exit(-1);
    }

    p = buffer[start];
    start = (start + 1) % BUFFER_SIZE;

    active--;
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

    for (int i=0; i<8; i++)
    {
        val = RetrieveFromQueue();
        printf("val[%d]:%.2f\n", i, val);
    }

    return 0;
}
