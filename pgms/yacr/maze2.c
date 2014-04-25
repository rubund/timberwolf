#include "copyright.h"
#include "yacr.h"

/*******************************************************************
 *
 *  maze2 attempts to route around the vertical constraint violation
 *  by connecting one net directly in the column, and using an unoccupied
 *  row move sideways to a column where the other net can be connected.
 *  maze2 returns YES if the route succeeds, NO otherwise.
 *
 *  Author: Jim Reed
 *
 *  Date: 4-22-84
 *  Last Modified: 5-8-84
 *
 ************************************************************************/

int maze2 (channel, num_rows, num_cols, column, top_net, bottom_net)
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
    int possible;		/* a flag */
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
    PATH_LIST new_routes,	/* list of possible routes */
	      routes;		/* complete list of possible routes */
    PATHPTR path;		/* list of rectangles used for a route */


    row_stack = NULL;
    path = NULL;

    /*
     *  set high_row, low_row, top_name, and bottom_name
     */

    high_row = top_net->row;
    low_row = bottom_net->row;
    top_name = top_net->name;
    bottom_name = bottom_net->name;


    /**********
     *  try to route with jog in top_net
     *********/

    /*
     *  can bottom_net be routed in a single line of metal?
     */

    if (search_column(channel->vert_layer, UP, column, num_rows, low_row)
		     == low_row)
	possible = YES;
    else
	possible = NO;

    /*
     *  make a stack of rows which might be used, rows closest to low_row
     *  should be nearest the top of the stack
     */

    if (possible == YES)
	for (i = 1; i < low_row; i++)
	{
	    if (channel->vert_layer[i][column] == 0)
	    {
		if (channel->horiz_layer[i][column] == 0)
		    push_int (&row_stack, i);
	        else if (channel->horiz_layer[i][column] == top_name)
		{   /* we bumped into what we were looking for */
		    /* route bottom net */
		    path = insert_path ((PATHPTR) 0, VERT, VERT, low_row, num_rows,
					column);
		    draw_rect (channel, bottom_name, path);
		    /* route top net */
		    path = insert_path ((PATHPTR) 0, VERT, VERT, 1, i, column);
		    draw_rect (channel, top_name, path);
		    return (YES);
		}
	    }
	    else if (channel->vert_layer[i][column] == top_name)
	    {   /* we bumped into what we were looking for */
		/* route bottom net */
		path = insert_path ((PATHPTR) 0, VERT, VERT, low_row, num_rows,
					column);
		draw_rect (channel, bottom_name, path);
		/* route top net */
		path = insert_path ((PATHPTR) 0, VERT, VERT, 1, i, column);
		draw_rect (channel, top_name, path);
		return (YES);
	    }
	    else
		/* this column is obstructed, jump out of loop */
		i = low_row;
	}

    /*
     *  if it is possible, try to route
     */

    if ((possible == YES) && (row_stack != NULL))
    {
	/* find left_edge */
	if (top_net->leftmost->edge == LEFT)
	    left_edge = 1;
	else if(channel->horiz_layer[high_row][top_net->leftmost->col-1] == 0)
	    left_edge = search_row (channel->horiz_layer, LEFT, high_row,
				 top_net->leftmost->col - 1, 1);
	else
	    left_edge = top_net->leftmost->col;

	/* find right_edge */
	if (top_net->rightmost->edge == RIGHT)
	    right_edge = num_cols;
	else if(channel->horiz_layer[high_row][top_net->rightmost->col+1] ==0)
	    right_edge = search_row (channel->horiz_layer, RIGHT, high_row,
				 top_net->rightmost->col + 1, num_cols);
	else
	    right_edge = top_net->rightmost->col;

	/* try to route using rows in row_stack */
	routes = NULL;
	while (row_stack != NULL)
	{
	    check_row = pop_int (&row_stack);
	    new_routes = jog_top_net(check_row, left_edge, right_edge, column,
			 top_name, high_row, 1, channel);
	    routes = merge_path_lists (new_routes, routes);
	}
	if (routes != NULL)
	{
	    /* route the nets and return */
	    /* top net */
	    draw_rect (channel, top_name, routes->path);
	    /* bottom net */
	    path = insert_path ((PATHPTR) 0, VERT, VERT, low_row, num_rows,
				    column);
	    draw_rect (channel, bottom_name, path);

/* beards - sept 87 - added memory saving stuff because of overflow problem
 	    in channels with large numbers of VCV's */

	    free_path_list(routes);

	    return (YES);
	    
	}
    }



    /**********
     *  try to route with jog in bottom_net
     *********/

    /*
     *  can top_net be routed in a single line of metal?
     */

    if (search_column(channel->vert_layer, DOWN, column, 1, high_row)
			== high_row)
	possible = YES;
    else
	possible = NO;

    /*
     *  make a stack of rows which might be used, rows closest to high_row
     *  should be nearest the top of the stack
     */

    /* start with an empty stack */
    row_stack = NULL;

    if (possible == YES)
	for (i = num_rows; i > high_row; i--)
	{
	    if (channel->vert_layer[i][column] == 0)
	    {
		if (channel->horiz_layer[i][column] == 0)
		    push_int (&row_stack, i);
		else if (channel->horiz_layer[i][column] == bottom_name)
		{   /* we bumped into what we were looking for */
		    /* route top net */
		    path = insert_path((PATHPTR) 0, VERT, VERT, 1, high_row, column);
		    draw_rect (channel, top_name, path);
		    /* route bottom net */
		    path = insert_path((PATHPTR) 0, VERT, VERT, i, num_rows, column);
		    draw_rect (channel, bottom_name, path);
		    return (YES);
		}
	    }
	    else if (channel->vert_layer[i][column] == bottom_name)
	    {   /* we bumped into what we were looking for */
		/* route top net */
		path = insert_path ((PATHPTR) 0, VERT, VERT, 1, high_row, column);
		draw_rect (channel, top_name, path);
		/* route bottom net */
		path = insert_path ((PATHPTR) 0, VERT, VERT, i, num_rows, column);
		draw_rect (channel, bottom_name, path);
		return (YES);
	    }
	    else
		/* this column is obstructed, jump out of loop */
		i = high_row;
	}

    /*
     *  if it is possible, try to route
     */

    if ((possible == YES) && (row_stack != NULL))
    {
	/* find left_edge */
	if (bottom_net->leftmost->edge == LEFT)
	    left_edge = 1;
	else if (channel->horiz_layer[low_row][bottom_net->leftmost->col-1] ==
									    0)
	    left_edge = search_row (channel->horiz_layer, LEFT, low_row,
				bottom_net->leftmost->col - 1, 1);
	else
	    left_edge = bottom_net->leftmost->col;

	/* find right_edge */
	if (bottom_net->rightmost->edge == RIGHT)
	    right_edge= num_cols;
	else if(channel->horiz_layer[low_row][bottom_net->rightmost->col+1] ==
									    0)
	    right_edge = search_row (channel->horiz_layer, RIGHT, low_row,
				 bottom_net->rightmost->col + 1, num_cols);
	else
	    right_edge = bottom_net->rightmost->col;

	/* try to route using rows in row_stack */
	routes = NULL;
	while (row_stack != NULL)
	{
	    check_row = pop_int (&row_stack);
	    new_routes = jog_bottom_net (check_row, left_edge, right_edge,
			 column, bottom_name, low_row, num_rows, channel);
	    routes = merge_path_lists (new_routes, routes);
	}
	if (routes != NULL)
	{
	    /* route the nets and return */
	    /* bottom net */
	    draw_rect (channel, bottom_name, routes->path);
	    /* top net */
	    path = insert_path ((PATHPTR) 0, VERT, VERT, 1, high_row, column);
	    draw_rect (channel, top_name, path);

/* beards - sept 87 - added memory saving stuff because of overflow problem
 	    in channels with large numbers of VCV's */

	    free_path_list(routes);

	    return (YES);
	}
    }

    return (NO);
}

