#ifndef lint
static char SccsId[] = "@(#)dens_heap.c	Yale Version 2.2 5/16/91";
#endif
/* -----------------------------------------------------------------

	FILE:		dens_heap.c
	AUTHOR:		Dahe Chen
	DATE:		Tue May 16 22:26:09 EDT 1990
	CONTENTS:	dens_shiftup()
			dens_shiftdown()
			dens_insert()
			dens_update()
	REVISION:
		Tue Nov 20 18:20:55 EST 1990
	    Modify the code to my new style.

----------------------------------------------------------------- */

#include <dgraph.h>

static HLISTPTR Pitem;

/*=====================================================================
*   Shift the item up in the heap.
=====================================================================*/
void
dens_shiftup(heap_head, k)
    HLISTPTR *heap_head;
    int k;
{

    Pitem = heap_head[k];

    while (heap_head[k/2]->key < Pitem->key)
    {
	heap_head[k] = heap_head[k/2];
	heap_head[k]->index = k;
	k /= 2;
    }

    heap_head[k] = Pitem;
    heap_head[k]->index = k;

} /* end of dens_shiftup */

/*=====================================================================
*   Shift the item down in the heap.
=====================================================================*/
void
dens_shiftdown(heap_head, k)
    HLISTPTR *heap_head;
    int k;
{

    int j;
    int maxheap;

    Pitem = heap_head[k];
    maxheap = heap_head[0]->index;

    while (k <= maxheap)
    {
	j = k + k;
	if (j < maxheap && heap_head[j]->key < heap_head[j+1]->key)
	{
	    j++;
	}
	if(j > maxheap || Pitem->key >= heap_head[j]->key)
	{
	    break;
	}
	heap_head[k] = heap_head[j];
	heap_head[k]->index = k;
	k = j;
    }

    heap_head[k] = Pitem;
    heap_head[k]->index = k;

} /* end of dens_shiftdown */

/*=====================================================================
*   Insert the item into the heap.
=====================================================================*/
void
dens_insert(heap_head, key)
    HLISTPTR *heap_head;
    int key;
{

    int maxheap;

    maxheap = ++heap_head[0]->index;
    heap_head[maxheap]->key = key;
    dens_shiftup(heap_head, maxheap);

} /* end of shiftdown */

/*=====================================================================
*   Update the heap.
=====================================================================*/
void
dens_update(heap_head, key, index)
    HLISTPTR *heap_head;
    int key;
    int index;
{

    if (heap_head[index]->key < key)
    {
	heap_head[index]->key = key;
	dens_shiftup(heap_head, index);
    }
    else
    {
	heap_head[index]->key = key;
	dens_shiftdown(heap_head, index);
    }

} /* end of dens_update */
