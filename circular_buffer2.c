/*
    Auther       : Heinz Samuelsson
    Date         : 2017-03-06
    File         : circular_buffer2.c
    Reference    : -
    Description  : Ring buffer.
*/ 
 
#include <stdio.h>
#include <stdlib.h>
 
#define BUFFER_SIZE 8

typedef struct
{
    int a;
    int b;
}Item;


Item buffer[BUFFER_SIZE];
int start = 0;
int end = 0;
int wrap = 0;

void rb_push(Item *p)
{
    printf("a:%d, b:%d, start:%d, end:%d\n", p->a, p->b, start, end);

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

Item rb_pull(void)
{
    if (!wrap) 
    {
	printf("NULL\n");
        exit(-1);
    }
    wrap--;

    start = (start) % BUFFER_SIZE;

    printf("start:%d, end:%d\n", start, end);
    return buffer[start++];
}


int main(int argc, char *argv[])
{
 
    Item item;
    Item *pItem = &item;

    item.a = 100;
    item.b = 200;
    for (int i=0; i<8; i++)
    {
        rb_push(&item);
	item.a++;
	item.b--;
    }

    item.a = 600;
    item.b = 700;
    for (int i=0; i<8; i++)
    {
        rb_push(&item);
	item.a++;
	item.b--;
    }

    item = rb_pull();
    printf("   Pull - a:%d, b:%d\n", item.a, item.b);

    item = rb_pull();
    printf("   Pull - a:%d, b:%d\n", item.a, item.b);

    item = rb_pull();
    printf("   Pull - a:%d, b:%d\n", item.a, item.b);

    return 0;
}
