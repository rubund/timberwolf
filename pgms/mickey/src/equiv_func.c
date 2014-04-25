#ifndef lint
static char SccsId[] = "@(#)equiv_func.c	Yale Version 2.2 5/16/91";
#endif
/* -----------------------------------------------------------------

	FILE:		equiv_func.c
	AUTHOR:		Dahe Chen
	DATE:		Wed May 16 22:28:43 EDT 1990
	CONTENTS:	find_num_comps()
			visit()
	REVISION:
		Tue Nov 20 18:29:49 EST 1990
	    Modify the code to my new style.

----------------------------------------------------------------- */

#include <define.h>
#include <gg_router.h>
#include <macros.h>
#include <heap_func.h>
#include <steiner_tree.h>

#define IN_STACK -1

typedef struct stack_element {
    short index;
    struct stack_element *next;
} STACK_ELEMENT,
*STACK_ELEMENTPTR;

static int v1;
static int v2;

static STACK_ELEMENTPTR Pstack;

void
find_num_comps()
{

    void visit();
    register int i;

    /***********************************************************
    * Initialization.
    ***********************************************************/
    Pstack = NIL(STACK_ELEMENT);
    numcomps = 0;
    for (i = 0; i < totedges; i++)
    {
	val[i] = UNVISITED;
    }

    /***********************************************************
    * Use the depth-first search to find the number of
    * components.
    ***********************************************************/
    for (i = 1; i <= numpins; i++)
    {
	v1 = numnodes + i;
	if (garray[v1]->status == LABEL && val[v1] == UNVISITED)
	{
	    numcomps++;
	    visit();
	}
    }

} /* end of find_num_comps */

void
visit()
{

    int pop_up();
    LISTPTR Pnode;

    push_down(&Pstack, v1);
    val[v1] = IN_STACK;

    while ((v1 = pop_up(&Pstack)) != 0)
    {
	Pnode = garray[v1]->first;
	garray[v1]->set = numcomps;
	while (Pnode)
	{
	    v2 = Pnode->t_vertex;
	    if (garray[v2]->status == LABEL && val[v2] == UNVISITED)
	    {
		if (earray[Pnode->edge]->intree)
		{
		    push_down(&Pstack, v2);
		    val[v2] = IN_STACK;
		}
	    }
	    Pnode = Pnode->next;
	}
    }

} /* end of visit */
