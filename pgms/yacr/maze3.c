#include "copyright.h"
#include "yacr.h"

/********************************************************************
 *
 *  maze3 is a more complex maze routing scheme.  Both the top and
 *  bottom nets are routed with a jog to the left or right.  The jogs
 *  are attempted between the rows that the nets were placed in.
 *  maze3 returns YES if the route succeeds, NO otherwise.
 *
 *  Author: Jim Reed
 *
 *  Date: 5-13-84
 *
 ********************************************************************/

int maze3 (channel, num_rows, num_cols, column, top_net, bottom_net)
INOUT CHANNELPTR channel;	/* channel data structure */
IN int num_rows;		/* number of rows in the channel */
IN int num_cols;		/* number of columns in the channel */
IN int column;			/* the column with a vertical constraint
				   violation */
IN NETPTR top_net,		/* net to be connected to the top of the
				   channel */
	  bottom_net;		/* net to be connected to the bottom of the
				   channel */
{
    int i;			/* loop counter */
    int high_row,		/* row containing top_net */
	low_row,		/* row containing bottom_net */
	top_name,		/* top_net->name */
	bottom_name;		/* bottom_net->name */
    int left_edge,		/* farthest to the left the net may be
				   extended without overlapping another net */
	right_edge;		/* farthest to the right the net may be
				   extended */
    int check_row;		/* a row that might be used for the route */
    INT_STACK row_stack;	/* stack of rows that might be used for the
				   route */
    INT_STACK trav_stack;	/* used to traverse the stack (list) */
    PATH_LIST new_routes,	/* list of possible routes */
	      top_routes,	/* list of all ways to route top_net */
	      bottom_routes;	/* list of all ways to route bottom_net */
    PATH_LIST trav_top,		/* used to traverse top_routes */
	      trav_bottom;	/* used to traverse bottom_routes */

    new_routes = NULL;
    top_routes = NULL;
    bottom_routes = NULL;
    row_stack = NULL;
    high_row = top_net->row;
    low_row = bottom_net->row;
    top_name = top_net->name;
    bottom_name = bottom_net->name;

    /* if there are not at least 2 rows between high_row and low_row
	maze3 will not work */

    if (high_row - low_row < 3)
	return (NO);

    /* if the column is not empty, maze3 will not work */
    if (search_column (channel->vert_layer, UP, column, num_rows, 1) != 1)
	return (NO);

    /*
     *  make a list of rows that we can jog in
     */

    for (i = low_row + 1; i < high_row; i++)
	if (channel->horiz_layer[i][column] == 0)
	    push_int (&row_stack, i);

    /* if there are not at least two rows, maze3 will not work */
    if (row_stack == NULL)
	return (NO);
    else if (row_stack->next == NULL)
	return (NO);

    /*
     *  find all routes with jog in top_net
     */

    /* find left_edge */
    if (top_net->leftmost->edge == LEFT)
	left_edge = 1;
    else if (channel->horiz_layer[high_row][top_net->leftmost->col - 1] == 0)
	left_edge = search_row (channel->horiz_layer, LEFT, high_row,
				 top_net->leftmost->col - 1, 1);
    else
	left_edge = top_net->leftmost->col;

    /* find right_edge */
    if (top_net->rightmost->edge == RIGHT)
	right_edge = num_cols;
    else if (channel->horiz_layer[high_row][top_net->rightmost->col + 1] == 0)
	right_edge = search_row (channel->horiz_layer, RIGHT, high_row,
				 top_net->rightmost->col + 1, num_cols);
    else
	right_edge = top_net->rightmost->col;

    /* find the routes */
    for (trav_stack = row_stack; trav_stack != NULL;
				 trav_stack = trav_stack->next)
    {
	check_row = trav_stack->value;
	new_routes = jog_top_net (check_row, left_edge, right_edge, column,
				  top_name, high_row, 1, channel);
	top_routes = merge_path_lists (new_routes, top_routes);
    }

    /*
     *  find all routes with jog in bottom_net
     */

    /* find left_edge */
    if (bottom_net->leftmost->edge == LEFT)
	left_edge= 1;
    else if (channel->horiz_layer[low_row][bottom_net->leftmost->col-1] == 0)
	left_edge = search_row (channel->horiz_layer, LEFT, low_row,
				bottom_net->leftmost->col - 1, 1);
    else
	left_edge = bottom_net->leftmost->col;

    /* find right_edge */
    if (bottom_net->rightmost->edge == RIGHT)
	right_edge = num_cols;
    else if (channel->horiz_layer[low_row][bottom_net->rightmost->col+1] == 0)
	right_edge = search_row (channel->horiz_layer, RIGHT, low_row,
				 bottom_net->rightmost->col + 1, num_cols);
    else
	right_edge = bottom_net->rightmost->col;

    /* find the routes */
    for (trav_stack = row_stack; trav_stack != NULL;
				 trav_stack = trav_stack->next)
    {
	check_row = trav_stack->value;
	new_routes = jog_bottom_net (check_row, left_edge, right_edge, column,
				bottom_name, low_row, num_rows, channel);
	bottom_routes = merge_path_lists (new_routes, bottom_routes);
    }

    /*
     *  try to find a pair of routes that will work
     */

    for (trav_top = top_routes; trav_top != NULL; trav_top = trav_top->next)
	for (trav_bottom = bottom_routes; trav_bottom != NULL;
					trav_bottom = trav_bottom->next)
	    if (intersect_path (trav_top->path, trav_bottom->path) == NO)
	    {
		draw_rect (channel, top_name, trav_top->path);
		draw_rect (channel, bottom_name, trav_bottom->path);
		return (YES);
	    }

    return (NO);
}
