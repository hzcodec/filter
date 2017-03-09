#ifndef _RING_BUFFER_H_
#define _RING_BUFFERE_H_

// PWM = 12 KHz => 83.3 us
#define BUFFER_SIZE_TEST_4  4
#define BUFFER_SIZE_TEST_8  8
#define BUFFER_SIZE_1024  1024   // 85 ms
#define BUFFER_SIZE_2048  2048   // 171 ms
#define BUFFER_SIZE_4096  4096   // 341 ms
#define BUFFER_SIZE_8192  8192   // 683 ms
#define BUFFER_SIZE_16384 16384  // 1365 ms



typedef struct
{
     int* buffer;
     int* buffer_end;  // pointer where data is pushed to
     int* data_start;  // pointer where data is poped from
     int* data_end;    // pointer to the last value 
     int* last;        // temporarily pointing at the last value
     int  count;
     int  size;
 } RingBuffer;


void rb_init(RingBuffer* rb, int size);
void rb_free(RingBuffer* rb);
bool rb_push(RingBuffer* rb, int data);
int  rb_pop(RingBuffer* rb);
bool rb_full(RingBuffer* rb);

int  rb_first(RingBuffer* rb);
int  rb_last(RingBuffer* rb);
void calc_average(RingBuffer *buff);
void rb_pop2(RingBuffer* rb);

#endif
