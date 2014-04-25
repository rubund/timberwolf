#include "copyright.h"
#include "yacr.h"

/******************************************************************
 *
 *  build_graph is responsible for constructing the vertical constraint
 *  graph, breaking cycles in the graph, and calculating level_from_top
 *  and level_from_bottom for each net.  build_graph calls make_graph
 *  to construct the full graph, and level_graph to break the cycles and
 *  find levels for the nets.
 *
 *  Author: Jim Reed
 *
 *  Date: 3-18-84
 *
 * Adapted for YACR 2.1 by Douglas Braun 8/21/85
 *******************************************************************/

void build_graph (net_array, top, bottom, left, right, num_nets, num_cols, 
		num_left_nets, num_right_nets, top_offset, bottom_offset)
IN NETPTR net_array;		/* array containing net data structures, used
				   to find the levels in the vertical
				   constraint graph */
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
       *bottom_offset;		/* The border offsets */
{
    make_graph (top, bottom, left, right, num_cols,
		num_left_nets, num_right_nets, num_nets);
    level_graph (net_array, top, bottom, left, right, num_nets, num_cols,
		num_left_nets, num_right_nets, top_offset, bottom_offset);
}


/**********************************************************************
 *
 *  make_graph constructs the vertical constraint graph.  There was no
 *  attempt to remove cycles from the graph in this routine.  make_graph
 *  calls insert_edge to actually construct an edge in the graph.
 *
 *  Author: Jim Reed
 *
 *  Date: 3-18-84
 *  Modified: 10-28-84  Remove cycles while building the graph.
 *  Modified: ~12-84	Stoped removing cycles while building the graph.
 *
 *********************************************************************/

void make_graph (top, bottom, left, right, num_cols,
		num_left_nets, num_right_nets, num_nets)
IN NETPTR top[],		/* array of pointers to nets on top of
				   channel */
	  bottom[],		/* nets on bottom of channel */
	  left[],		/* nets entering from left */
	  right[];		/* nets entering from right */
IN int num_cols,		/* size of top[], and bottom[] */
       num_left_nets,		/* size of left[] */
       num_right_nets,		/* size of right[] */
       num_nets;		/* number of nets in the channel */
{
    int i;			/* loop counter */

    /*
     *  insert graph edges caused by nets entering channel from left
     */

    if (place_relative == LEFT || place_fixed == LEFT)
	for (i = 1; i < num_left_nets; i++)
	    insert_edge (left[i], left[i+1], num_nets, 0);

    /*
     *  insert graph edges caused by nets entering channel from right
     */

    if (place_relative == RIGHT || place_fixed == RIGHT)
	for (i = 1; i < num_right_nets; i++)
	    insert_edge (right[i], right[i+1], num_nets, num_cols+1);

    /*
     *  insert graph edges for body of channel
     */

    for (i = 1; i <= num_cols; i++)
    	insert_edge (top[i], bottom[i], num_nets, i);
}



/*******************************************************************
 *
 *  insert_edge updates the 'parents' and 'children' lists in the NET
 *  structures to indicate the upper_net is a parent of lower_net, and
 *  lower_net is a child of upper_net.
 *
 *  Author: Jim Reed
 *
 *  Date: 3-18-84
 *  Modified: 12-4-84  add list of columns that cause each edge
 *
 *******************************************************************/

/*ARGSUSED*/
void insert_edge (upper_net, lower_net, num_nets, column)
INOUT NETPTR upper_net,		/* inserted edge will indicate that upper_net
				   should be placed above lower_net */
	  lower_net;
IN int num_nets;		/* number of nets in the channel */
IN int column;			/* column in the channel that this edge is
				   related to, this is only used when this
				   edge would close a cycle */
{
    NET_LIST_M link,		/* used to allocate space for new elements
				   inserted into parents and children lists */
	     traverse;		/* used to traverse upper_net's children list
				   to make sure edge does not already exist */
    INT_LIST temp_int_list;	/* used to allocate element in list of
				   columns that cause an edge */


    /*
     *  if one of the nets has name 0 then don't do anything
     */

    if ((number_to_name(upper_net->name) == 0) ||
		(number_to_name(lower_net->name) == 0))
	return;

    /*
     *  don't make an edge from a net to itself
     */

    if (upper_net == lower_net)
	return;

    /*
     *  if the edge already exists, don't make another one,
     *  but add this column to the list of columns causing this edge
     */

    for (traverse = upper_net->children; traverse != NULL;
			traverse = traverse->next)
	if (traverse->net == lower_net)
	{
	    temp_int_list = ALLOC(INT_LIST_ELEMENT, 1);
	    temp_int_list->value = column;
	    temp_int_list->next = traverse->col_list;
	    return;
	}

    /*
     *  tell upper_net that lower_net is its child
     */

    link = ALLOC(NET_LIST_ELEMENT_M, 1);
    link->net = lower_net;
    link->marked = NO;
    link->next = upper_net->children;
    link->col_list = ALLOC(INT_LIST_ELEMENT, 1);
    link->col_list->next = NULL;
    link->col_list->value = column;
    upper_net->children = link;

    /*
     *  tell lower_net that upper_net is its parent
     */

    link = ALLOC(NET_LIST_ELEMENT_M, 1);
    link->net = upper_net;
    link->marked = NO;
    link->next = lower_net->parents;
    /* make col_list physically the same as above */
    link->col_list = upper_net->children->col_list;
    lower_net->parents = link;
}


