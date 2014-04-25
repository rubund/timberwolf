#ifndef lint
static char SccsId[] = "@(#)heap_func.c	Yale Version 2.2 5/16/91";
#endif
/* -----------------------------------------------------------------

	FILE:		heap_func.c
	AUTHOR:		Dahe Chen
	DATE:		Wed Mar 22 23:54:25 EDT 1989
	CONTENTS:	make_heap()
			shiftup()
			shiftdown()
			deletemin()
			insert()
			destroy_heap()
	REVISION:

----------------------------------------------------------------- */

#include <define.h>
#include <gg_router.h>
#include <heap_func.h>

HEAPSPTR
*make_heap(length)
    int length;
{

    int i;
    HEAPSPTR *heap_head;

    heap_head = (HEAPSPTR *) Ysafe_malloc((length+1) * sizeof(HEAPSPTR));

    for (i = 0; i <= length; i++)
    {
	heap_head[i] = (HEAPSPTR) Ysafe_malloc(sizeof(HEAPS));
    }
    heap_head[0]->key = 0;

    return(heap_head);

} /* end of make_heap */

/* ==================================================================== */

void
shiftup(heap_head, k)
    HEAPSPTR *heap_head;
    int k;
{

    char *data;
    int key;
    int maxheap;

    maxheap = heap_head[0]->key;
    heap_head[0]->key = INT_MIN;
    data = heap_head[k]->data;
    key = heap_head[k]->key;

    while (heap_head[k/2]->key > key)
    {
	heap_head[k]->data = heap_head[k/2]->data;
	heap_head[k]->key = heap_head[k/2]->key;
	k /= 2;
    }

    heap_head[k]->data = data;
    heap_head[k]->key = key;
    heap_head[0]->key = maxheap;

} /* end of shiftup */

/* ==================================================================== */

void
shiftdown(heap_head, k)
    HEAPSPTR *heap_head;
    int k;
{

    char *data;
    int j;
    int key;
    int maxheap;

    maxheap = heap_head[0]->key;
    data = heap_head[k]->data;
    key = heap_head[k]->key;

    while (k <= maxheap)
    {
	j = k + k;
	if (j < maxheap && heap_head[j]->key > heap_head[j+1]->key)
	{
	    j++;
	}
	if (j > maxheap || key <= heap_head[j]->key)
	{
	    break;
	}
	heap_head[k]->key = heap_head[j]->key;
	heap_head[k]->data = heap_head[j]->data;
	k = j;
    }

    heap_head[k]->key = key;
    heap_head[k]->data = data;

} /* end of shiftdown */

/* ==================================================================== */

char
*deletemin(heap_head)
    HEAPSPTR *heap_head;
{

    char *data;
    int maxheap;

    if (!(heap_head[0]->key) )
    {
	data = NIL(char);
    }
    else
    {
	maxheap = heap_head[0]->key;
	data = heap_head[1]->data;
	if (maxheap == 1)
	{
	    heap_head[0]->key = 0;
	}
	else
	{
	    heap_head[1]->key = heap_head[maxheap]->key;
	    heap_head[1]->data = heap_head[maxheap]->data;
	    heap_head[0]->key = --maxheap;
	    shiftdown(heap_head, 1);
	}
    }

    return(data);

} /* end of deletemin */

/* ==================================================================== */

void
insert(heap_head, key, data)
    HEAPSPTR *heap_head;
    int key;
    char *data;
{

    int maxheap;

    maxheap = ++heap_head[0]->key;
    heap_head[maxheap]->key = key;
    heap_head[maxheap]->data = data;

    shiftup(heap_head, maxheap);

} /* end of shiftdown */

/* ==================================================================== */

destroy_heap(heap_head, length, userdelete)
    HEAPSPTR *heap_head;
    int length;
    int (*userdelete)();
{

    int i;

    if (userdelete)
    {
	Ysafe_free((char *) heap_head[0]);
	for (i = 1; i <= length; i++)
	{
	    (*userdelete)(heap_head[i]->data);
	    Ysafe_free((char *) heap_head[i]);
	}
    }
    else
    {
	for (i = 0; i <= length; i++)
	{
	    Ysafe_free((char *) heap_head[i]);
	}
    }
    Ysafe_free((char *) heap_head);

} /* end of destroy_heap */
