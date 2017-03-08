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
int head = 0;
int tail = 0;
int wrap = 0;

void rb_push(Item *p)
{
    printf("a:%d, b:%d, head:%d, tail:%d\n", p->a, p->b, head, tail);

    buffer[tail] = *p;
    tail = (tail + 1) % BUFFER_SIZE;

    if (wrap < BUFFER_SIZE)
    {
        wrap++;
    } 
    else 
    {
        /* Overwriting the oldest. Move head to next-oldest */
        head = (head + 1) % BUFFER_SIZE;
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

    head = (head) % BUFFER_SIZE;

    printf("head:%d, tail:%d\n", head, tail);
    return buffer[head++];
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
