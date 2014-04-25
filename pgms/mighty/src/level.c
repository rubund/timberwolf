#ifndef lint
static char SccsId[] = "@(#) level.c version 6.2 12/27/90" ;
#endif


#include "mighty.h"

/********************************************************************
 *
 * level_graph calculates the level_from_top and level_from_bottom for
 * each net.  Cycles in the graph are detected and broken.  The current
 * method for breaking cycles tries to break
 * on a farthest column from critical columns.
 *
 *********************************************************************/

void level_graph (cutcol)
int cutcol;  /* column number of the guiding pins */
{
    int i,j;			/* loop counter */
    int nets_leveled;		/* number of nets that have their level_from_
				   set */
    int nets_to_level;		/* Number of nets to level, excluding
				   nets with no pins */
    int new_level;		/* new level for a net's children (parents) */
    int process;		/* flag, used to determine if all of a nets
				   parents (children) have been processed */
    NETPTR working_net,		/* net whose children (parents) are being
				   processed */
	   relative;		/* the child (parent) which is being
				   processed */
    NET_LIST_M parent_list,	/* list of parents being traversed */
	     child_list;	/* list of children being traversed */
    NET_STACK stack;		/* contains nets whose children (parents) can
				   be treated */
    NET_STACK break_cycle ();
    NETPTR pop_net ();

    /*******************
     *
     *  Calculate level_from_top and break cycles
     *
     *******************/

    /*
     *  Initialize stack
     */

    stack = (NET_STACK)NULL;
    nets_to_level = 0;

    /*
     *  Set the level_from_top and level_from_bottom for each net to
     *  the first and last rows it can occupy without hitting an indentation.
     */

    for (i = 1; i <= num_netsG; i++)
    {
/*
	if (net_arrayG[i].leftmost != NULL)
*/
	    nets_to_level++;
	net_arrayG[i].level_from_top = 1;
	net_arrayG[i].level_from_bottom = 1;
    }

    /*
     *  Construct stack of nets with no parents
     */

    for (i = 1; i <= num_netsG; i++)
	if ( /* (net_arrayG[i].leftmost != NULL) && */
		(net_arrayG[i].parents == (NET_LIST_M)NULL))
	{
	    push_net (&stack, net_arrayG + i);
	}

    /*
     *  Breadth first traversal of graph, setting level_from_top
     *  If there is a cycle, break it and continue traversal.
     */

    nets_leveled = 0;
    while (nets_leveled < nets_to_level)
    {
	/* check to se if there is a cycle */
	if (stack == (NET_STACK)NULL)
	{
	    /* break all cycles in the graph */
 	    /* printf ("nets_leveled = %d\n", nets_leveled); */
	    stack = break_cycle (cutcol);
	}

	while (stack != (NET_STACK)NULL)     /* if stack is empty we
				are either done or there is a cycle */
	{
	    working_net = pop_net (&stack);
/* 	    printf ("working_net = %d\n",
			number_to_name (working_net->name)); */
	    nets_leveled++;
	    new_level = working_net->level_from_top + 1;
            /* process children */
	    for (child_list = working_net->children;
		 child_list != (NET_LIST_M)NULL; child_list = child_list->next)
	    {
		relative = child_list->net;
		if (relative->level_from_top < new_level)
		    relative->level_from_top = new_level;

		/* mark this child's parents list */
		parent_list = relative->parents;
		while (parent_list->net != working_net)
		    parent_list = parent_list->next;
		parent_list->marked = YES;

		/* find out if all of this relative's parents have
		 * been processed */
		process = YES;
		for (parent_list = relative->parents; parent_list != (NET_LIST_M)NULL;
				parent_list = parent_list->next)
		    if (parent_list->marked == NO)
			process = NO;

		/* if this relative can be processed, put it in the stack */
		if (process == YES)
		    push_net (&stack, relative);
	    }
	}
    }


    /*******************
     *
     *  Calculate level_from_bottom for each net
     *
     *******************/

    /*
     *  Initialize stack
     */

    stack = (NET_STACK)NULL;

    /*
     *  Construct stack of nets with no children,
     *  set their level_from_bottom = 1
     */

    for (i = 1; i <= num_netsG; i++)
	if( /* (net_arrayG[i].leftmost != NULL) && */
		(net_arrayG[i].children == (NET_LIST_M)NULL))
	{
	    push_net (&stack, net_arrayG + i);
	}

    /*
     *  Breadth first traversal of graph, setting level_from_bottom
     */

    /* nets_leveled = 0; */
    while (stack != (NET_STACK)NULL) 	/* if stack is empty we are done or there is
				   a cycle, but that's impossible */
	{
	    working_net = pop_net (&stack);
	    /* nets_leveled++; doesn't do anything  */
	    new_level = working_net->level_from_bottom + 1;

	    /* process parents */
	    for (parent_list = working_net->parents;
		 parent_list != (NET_LIST_M)NULL; parent_list = parent_list->next)
	    {
		relative = parent_list->net;
		if (relative->level_from_bottom < new_level)
		    relative->level_from_bottom = new_level;

		/* mark this parent's children list */
		child_list = relative->children;
		while (child_list->net != working_net)
		    child_list = child_list->next;
		child_list->marked = YES;

		/* find out if all of this relative's children have
		 *  been processed */

		process = YES;
		for (child_list = relative->children; child_list != (NET_LIST_M)NULL;
				child_list = child_list->next)
 {
		    if (child_list->marked == NO)
			process = NO;
 }

		/* if this relative can be processed, put it in the stack */
		if (process == YES)
		    push_net (&stack, relative);
	    }
	}

    /* print levels for all nets */
    /*
    for (i = 1; i <= num_netsG; i++)
	fprintf (output_fileG, "net %2d( %2d ), lft %2d, lfb %2d t-b %3d\n",
		number_to_name(i), i, net_arrayG[i].level_from_top,
		net_arrayG[i].level_from_bottom,
		net_arrayG[i].level_from_top - net_arrayG[i].level_from_bottom);
    */
}



