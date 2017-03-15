/*
    Auther       : Heinz Samuelsson
    Date         : 2017-03-03
    File         : main_ring_buffer.c
    Reference    : -
    Description  : -
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include "main_ring_buffer.h"
#include "ring_buffer.h"

#define LOCAL_BUFFER_SIZE 10 
#define RAMP_DATA_BUFFER 8192

static int indata[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
static int outdata[16] = {1,4,9,16,25,36,49,64,81,100,121,144,169,196,225,256};
float ramp_indata[RAMP_DATA_BUFFER];
static FILE *fp;

// initial fill the buffer
void init_fill(RingBuffer *b, int wz)
{
    int cnt = 0;

    for (int i=0; i<wz; i++)
    {
	cnt++;
        //rb_push(b, outdata[i]);
        rb_push(b, ramp_indata[i]);
    }
    printf("Buffer initial filled with [%d] numbers of data, window size = %d \n", cnt, wz);
}


void print_usage()
{
    printf("./rb -s <1-3> -b <size>\n");
    printf("  1 - ramp_samples\n");
    printf("  2 - counter_samples\n");
    printf("  3 - power2_samples\n");
}


void read_indata(int sel)
{
    if(sel == 1)
    {
	printf("ramp_samples opened\n");
        fp = fopen("logfiles/ramp_samples.txt", "r");
    }
    else if(sel == 2)
    {
	printf("counter_samples opened\n");
        fp = fopen("logfiles/counter_samples.txt", "r");
    }
    else if(sel == 3)
    {
	printf("power2_samples opened\n");
        fp = fopen("logfiles/power2_samples.txt", "r");
    }
    else
    {
	printf("filter opened\n");
        fp = fopen("logfiles/filter.txt", "r");
    }

    if (fp == NULL)
    {
        printf("Error: File does not exist\n");
        exit(-1);
    }

    for (int i=0; i<RAMP_DATA_BUFFER; i++)
    {
        fscanf(fp, "%f,",&ramp_indata[i]);
	printf("%s() - data[%d]:%.2f\n", __func__, i, ramp_indata[i]);
    }

    fclose(fp);
}


int main(int argc, char *argv[])
{
    RingBuffer myBuff;
    int option = 0;
    int selectFile = 1;
    int windowSize = 10;

    while ((option = getopt(argc, argv,"s:b:h")) != -1) {
        switch (option) {
             case 's' : selectFile = atoi(optarg);
                        break;
             case 'b' : windowSize = atoi(optarg);
                        break;
             case 'h' : print_usage();
	                exit(1);
                        break;
             default: selectFile = 0; 
                 exit(EXIT_FAILURE);
        }
    }

    printf("*****************************************************************\n");
    printf("*                          Ring Buffer                          *\n");
    printf("*****************************************************************\n");
    
    // read input data to ring buffer
    read_indata(selectFile);

    // setup ring buffer
    rb_init(&myBuff, windowSize);

    // initialize the first part of the buffer
    init_fill(&myBuff, windowSize);
    rb_peek(&myBuff, windowSize);

    for (int i=0; i<2000-windowSize; i++)
    {
        rb_push(&myBuff, ramp_indata[i+windowSize]);
        rb_peek(&myBuff, windowSize);
    }

    rb_free(&myBuff);
    close_fp();

    return 0;
}
