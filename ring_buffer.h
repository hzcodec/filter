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

#define WINDOW_SIZE 4

typedef struct
{
     float* buffer;
     float* buffer_end;  // pointer where data is pushed to
     float* data_start;  // pointer where data is poped from
     float* data_end;    // pointer to the last value 
     float* last;        // temporarily pointing at the last written value in the window
     int  count;
     int  size;
 } RingBuffer;

void rb_init(RingBuffer* rb, int size);
void rb_free(RingBuffer* rb);
bool rb_push(RingBuffer* rb, float data);
float  rb_pop(RingBuffer* rb);
bool rb_full(RingBuffer* rb);

float  rb_first(RingBuffer* rb);
float  rb_last(RingBuffer* rb);
void rb_peek(RingBuffer* rb);

#endif
