#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include "ring_buffer.h"

#define LOCAL_BUFFER_SIZE 10 
#define RAMP_DATA_BUFFER 4095

static int indata[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
static int outdata[16] = {1,4,9,16,25,36,49,64,81,100,121,144,169,196,225,256};
//static float outdata[16] = {1.0,8.0,27.0,64.0,125.0,216.0,343.0,512.0,729.0,1000.0,1331.0,1728.0,2197.0,2744.0,3375.0,4096.0};
float ramp_indata[RAMP_DATA_BUFFER];
static FILE *fp;

// initial fill the buffer
void init_fill(RingBuffer *b)
{
    int cnt = 0;

    for (int i=0; i<WINDOW_SIZE; i++)
    {
	cnt++;
        //rb_push(b, outdata[i]);
        rb_push(b, ramp_indata[i]);
    }
    printf("Buffer initial filled with <%d> numbers of data\n", cnt);
}


void read_rampdata(int sel)
{
    if(sel == 1)
    {
	printf("ramp_samples opened\n");
        fp = fopen("ramp_samples.txt", "r");
    }
    else if(sel == 2)
    {
	printf("counter_samples opened\n");
        fp = fopen("counter_samples.txt", "r");
    }
    else
    {
	printf("filter opened\n");
        fp = fopen("filter.txt", "r");
    }

    if (fp == NULL)
    {
        printf("Error: File does not exist\n");
        exit(-1);
    }

    for (int i=0; i<RAMP_DATA_BUFFER; i++)
    {
        fscanf(fp, "%f,",&ramp_indata[i]);
	//printf("%s() - data[%d]:%.2f\n", __func__, i, ramp_indata[i]);
    }

    fclose(fp);
}


int main(int argc, char *argv[])
{
    RingBuffer myBuff;
    int option = 0;
    int selectFile = 1;

    while ((option = getopt(argc, argv,"s:")) != -1) {
        switch (option) {
             case 's' : selectFile = atoi(optarg);
                        break;
             default: selectFile = 0; 
                 exit(EXIT_FAILURE);
        }
    }

    printf("*****************************************************************\n");
    printf("*                          Ring Buffer                          *\n");
    printf("*****************************************************************\n");
    
    // read input data to ring buffer
    read_rampdata(selectFile);

    rb_init(&myBuff, WINDOW_SIZE);

    init_fill(&myBuff);
    rb_peek(&myBuff);

    for (int i=0; i<200; i++)
    {
        ///rb_push(&myBuff, outdata[i+4]);
        rb_push(&myBuff, ramp_indata[i+WINDOW_SIZE]);
        rb_peek(&myBuff);
    }

    rb_free(&myBuff);
    close_fp();

    return 0;
}
