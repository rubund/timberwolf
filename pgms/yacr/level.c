#include "copyright.h"
#include "yacr.h"

/********************************************************************
 *
 * level_graph calculates the level_from_top and level_from_bottom for
 * each net.  Cycles in the graph are detected and broken.  The current
 * method for breaking cycles seems to be rathr arbitrary.  When a cycle
 * is broken, a message is output.
 *
 * Author: Jim Reed
 *
 * Date: 3-19-84
 * Last modified: 3-21-84
 * 2/13/85:  Fixed bug that caused empty stack from deleted
 * unique nets by adding variable nets_to_level.    D. Braun
 *
 * Modified 3-28-85 by D. Braun to take into account border indent-
 * ations when computing the level of a net.
 *********************************************************************/

/*ARGSUSED*/
void level_graph (net_array, top, bottom, left, right, num_nets, num_cols, 
		num_left_nets, num_right_nets, top_offset, bottom_offset)
IN NETPTR net_array;		/* array containing all the net data
				   structures */
IN NETPTR top[],		/* array of pointers to nets on top of
				   channel */
	  bottom[],		/* nets on bottom of channel */
	  left[],		/* nets entering from left */
	  right[];		/* nets entering from right */
IN int num_nets,		/* size of net_array */
       num_cols,		/* size of top[], and bottom[] */
       num_left_nets,		/* size of left[] */
       num_right_nets;		/* size of right[] */
IN int *top_offset,
       *bottom_offset;		/* The boundary offsets */

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

    /*******************
     *
     *  Calculate level_from_top and break cycles
     *
     *******************/

    /*
     *  Initialize stack
     */

    stack = NULL;
    nets_to_level = 0;

    /*
     *  Set the level_from_top and level_from_bottom for each net to
     *  the first and last rows it can occupy without hitting an indentation.
     */

    for (i = 1; i <= num_nets; i++)
	if (net_array[i].leftmost != NULL)
	{
	    nets_to_level++;
	    net_array[i].level_from_top = 1;
	    net_array[i].level_from_bottom = 1;
	    for (j=net_array[i].leftmost->col;
	         j<=net_array[i].rightmost->col; j++)
	    {
		if (top_offset[j]+1 > net_array[i].level_from_top)
		    net_array[i].level_from_top = top_offset[j]+1;
		if (bottom_offset[j]+1 > net_array[i].level_from_bottom)
		    net_array[i].level_from_bottom = bottom_offset[j]+1;
	    }
	    /*
	    (void) printf("Net %d top level: %d bottom level: %d\n",i,net_array[i].level_from_top,net_array[i].level_from_bottom);
	    */
	}



    /*
     *  Construct stack of nets with no parents
     */

    for (i = 1; i <= num_nets; i++)
	if ((net_array[i].leftmost != NULL) && (net_array[i].parents == NULL))
	{
	    push_net (&stack, net_array + i);
	}


    /*
     *  Breadth first traversal of graph, setting level_from_top
     *  If there is a cycle, break it and continue traversal.
     */

    nets_leveled = 0;
    while (nets_leveled < nets_to_level)
    {
	/* check to se if there is a cycle */
	if (stack == NULL)
	{
	    /* break all cycles in the graph */
/* 	    (void) printf ("nets_leveled = %d\n", nets_leveled); */
	    stack = break_cycle (net_array, num_nets, top, bottom, num_cols);
	}

	while (stack != NULL)     /* if stack is empty we are either done
				     or there is a cycle */
	{
	    working_net = pop_net (&stack);
/* 	    (void) printf ("working_net = %d\n",
			number_to_name (working_net->name)); */
	    nets_leveled++;
	    new_level = working_net->level_from_top + 1;
            /* process children */
	    for (child_list = working_net->children;
		 child_list != NULL; child_list = child_list->next)
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
		for (parent_list = relative->parents; parent_list != NULL;
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

    stack = NULL;

    /*
     *  Construct stack of nets with no children,
     *  set their level_from_bottom = 1
     */

    for (i = 1; i <= num_nets; i++)
	if((net_array[i].leftmost != NULL) && (net_array[i].children == NULL))
	{
	    push_net (&stack, net_array + i);
	}

    /*
     *  Breadth first traversal of graph, setting level_from_bottom
     */

    nets_leveled = 0;
    while (stack != NULL) 	/* if stack is empty we are done or there is
				   a cycle, but that's impossible */
	{
	    working_net = pop_net (&stack);
	    nets_leveled++;
	    new_level = working_net->level_from_bottom + 1;

	    /* process parents */
	    for (parent_list = working_net->parents;
		 parent_list != NULL; parent_list = parent_list->next)
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
		for (child_list = relative->children; child_list != NULL;
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
/*     for (i = 1; i <= num_nets; i++)
	(void) fprintf (output_file, "net %2d, lft %2d, lfb %2d\n",
		number_to_name (i), net_array[i].level_from_top,
		net_array[i].level_from_bottom); */
}
