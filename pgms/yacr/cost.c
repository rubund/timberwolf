#include "copyright.h"
#include "yacr.h"

static NETPTR s_net_array;	/* array of net data structures */
static int s_num_nets;		/* size of net_array */
static NETPTR *top_list;	/* list of nets on top edge of channel */
static NETPTR *bottom_list;	/* list of nets on bottom edge of channel */


/*************************************************************
 *
 *  net_cost calculates the values for column net->name in the
 *  cost matrix.
 *  The cost is calculated as follows:
 *	(a) find the range of desired rows for the net ("top" and "bottom")
 *	    and "best_row" (see below for algorithm);
 *	(b) set the cost of each row in the range to MED * (#rows in range);
 *	(c) set the cost of each row outside of the range to HIGH;
 *	(d) add to each cost LOW * distance from best_row;
 *	(e) set the cost of each row the net cannot be placed in to INFINITY;
 *	(f) set cost[0][i] to the number of rows with cost less than INFINITY
 *	    for net i.
 *  top is the highest row the net can be placed in without definitely
 *  causing a vertical constraint violation.  bottom is the lowest row.
 *  Depending on how other nets are placed, there may be a vertical
 *  constraint violation even if the net is placed below (or in) top
 *  and above (or in) bottom.  bottom and top may be the same.
 *  range_size is the number of rows between top and bottom, inclusive.
 *  best_row is at relatively the same position in the range, as the
 *  range is in the channel.
 *
 *  Author: Jim Reed
 *
 *  Date: 3-26-84
 *
 *  Modified 3-26-85 D. Braun for irregular borders.  Calls
 *  to set_border_cost and set_irreg_cost added. Channel argument added
 *  Also sets top_ and bottom_free_row fields of the net.
 *
 *****************************************************************/


void net_cost (cost, channel, net, num_rows)
INOUT int **cost;		/* the cost matrix */
IN CHANNELPTR channel;		/* the channel */
IN NETPTR net;			/* net to be put in the cost matrix */
IN int num_rows;		/* number of rows in the channel */
{
    int col;			/* column of cost matrix being modified. Used
				   to reduce indirection */
    int top,			/* lowest numbered row in desired range */
	bottom,			/* highest numbered row in desired range */
	best_row;		/* the best row the net can be placed in */
    int temp;			/* used to interchange top and bottom if
				   necesary */
    int top_free_row,
	bottom_free_row;	/* the highest and lowest rows in which
				a net can be placed without hitting an
				irregular border. */
    int free_row;		/* for calculating above */
    
    int pin;			/* Col of the current pin of the net
				for calculating top_free_row. */


    /*
     * Calculate top_ and bottom_free_rows
     */

    top_free_row = 1;
    bottom_free_row = num_rows;

    for (pin=net->leftmost->col; pin <= net->rightmost->col; pin++)
    {
	free_row = 1;
	while (channel->vert_layer[free_row][pin] == BORDER &&
	       free_row < num_rows)
	    free_row++;
	if (free_row > top_free_row)
	    top_free_row = free_row;

	free_row = num_rows;
	while (channel->vert_layer[free_row][pin] == BORDER &&
	       free_row > 1)
	    free_row--;
	if (free_row < bottom_free_row)
	    bottom_free_row = free_row;
    }


    net->top_free_row = top_free_row;
    net->bottom_free_row = bottom_free_row;
	   
    /* make sure top_free_row <= bottom_free_row */
    /* Actually, if top_free_row > bottom_free_row,
    there is no way that the net can be placed,
    but that will be dealt with later. */

    if (top_free_row > bottom_free_row)
    {
	temp = top_free_row;
	top_free_row = bottom_free_row;
	bottom_free_row = temp;
    }

    col = net->name;

    /*
     *  find the desired range and best_row
     */

    top = net->level_from_top;
    if (top > bottom_free_row)
	top = bottom_free_row - 1;
    bottom = num_rows - net->level_from_bottom + 1;
    if (bottom < top_free_row)
	bottom = top_free_row+1;

    /* make sure top <= bottom */
    if (top > bottom)
    {
	temp = top;
	top = bottom;
	bottom = temp;
    }


    /* find best_row */
    if ((top != top_free_row) || (bottom != bottom_free_row))
	/*
	best_row = (top * num_rows - bottom) / ( num_rows - bottom + top - 1);
	*/
	best_row = top_free_row - 1 +
		   (((top-top_free_row+1)*(bottom_free_row-top_free_row+1)
		    - (bottom - top_free_row + 1))
		    / ((bottom_free_row-top_free_row+1)-bottom+top-1));



    else if ((net->level_from_bottom == (num_rows - bottom_free_row + 1)) &&
              (net->level_from_top == top_free_row))
    {
	if (net->pin_placement > 0)
	    best_row = top_free_row;
	else if (net->pin_placement < 0)
	    best_row = bottom_free_row;
	else
	    best_row = (top_free_row + bottom_free_row) / 2;
    }
    else
	best_row = (top_free_row + bottom_free_row) / 2;

    /*
     *  set cost of each row in range to MED * ((# of free rows) - range_size + 1)
     *  "+ 1" so that the cost will never be 0
     */

    set_med_cost ((bottom_free_row - top_free_row + 1), bottom, top, col, cost);

    /*
     *  set cost of each row outside of range to HIGH
     */

    set_high_cost (cost, col, top, bottom, num_rows);

    /*
     *  linear cost adjustment
     *  add LOW * distance from best_row to each cost
     */

    set_low_cost (best_row, col, cost, num_rows);

    set_border_cost(cost, channel, net, num_rows);

}


set_med_cost (num_rows, bottom, top, col, cost)
IN int num_rows;
IN int top, bottom, col;
INOUT int **cost;
{
    register int med_cost;
    register int i;

    med_cost = MED * (num_rows - bottom + top);
    for (i = top; i <= bottom; cost[i++][col] = med_cost);
}

set_high_cost (cost, col, top, bottom, num_rows)
IN int **cost;
IN int col, top, bottom, num_rows;
{
    register int i;

	for (i = 1; i < top; cost[i++][col] = HIGH);
	for (i = bottom + 1; i <= num_rows; cost[i++][col] = HIGH);
}


/* This procedure allows modification of the cost function to facilitate
 * the implementation of partial boundary constraints. 'set_partial_cost'
 * adds a linearly-graded function, f(row), to the cost function to weight
 * top or bottom edges.                          H. Sheng   6/88
 */

set_partial_cost (cost, num_rows)
INOUT int **cost;
IN int num_rows;
{
  register int i,k;                        /* loop counters */

  for (i=1; i<=num_up_nets; i++)
    {
      for (k=1;k<=num_rows;k++)
	cost[k][up[i]->name] += ALPHA*(k-1) - ALPHA*(num_rows-1)+MED*ALPHA; 
    }
  for (i=1; i<=num_down_nets; i++)
    {
      for (k=1;k<=num_rows;k++)
	cost[k][down[i]->name] -= ALPHA*(k-1) - MED*ALPHA;
    }
}
	
  
set_low_cost (best_row, col, cost, num_rows)
IN int best_row, col;
IN int **cost;
IN int num_rows;
{
    register int i;
    register int j;

    for (i = 1, j = LOW * (best_row-1); i < best_row; j -= LOW)
	cost[i++][col] += j;
    for (i = best_row + 1, j = LOW; i <= num_rows; j += LOW)
	cost[i++][col] += j;
}


int** init_cost (channel, num_rows, n_nets, n_array, t_list, b_list, n_rows)
IN CHANNELPTR channel;		/* The channel */
IN int num_rows;		/* number of rows in the channel */
IN int n_nets;			/* number of nets in n_array */
IN NETPTR n_array;		/* array of all the net data structures */
IN NETPTR *t_list;		/* list of nets on top of channel */
IN NETPTR *b_list;		/* list of nets on bottom of channel */
IN int n_rows;			/* number of rows in the channel */
{
    int i;			/* loop counter */
    int **cost;			/* the cost matrix */

    /*
     *  initialize s_num_nets, s_net_array, top_list, and bottom_list
     *  which are static and local to this file
     */
    s_num_nets = n_nets;
    s_net_array = n_array;
    top_list = t_list;
    bottom_list = b_list;
    num_rows = n_rows;

    /* allocate space for the cost matrix */
    cost = allocate_cost (num_rows, s_num_nets);

    /* set the values in the cost matrix */
    for (i = 1; i <= s_num_nets; i++)
	if (s_net_array[i].leftmost != NULL)
	{
	    net_cost (cost, channel, s_net_array + i, num_rows);
	}
    /* modify cost matrix for partial constraints.  H. Sheng 6/88 */
    if (max_bottom_offset!=0 || max_top_offset!=0)
      set_irreg_cost(cost, num_rows);
    if (place_partial != NO)
      set_partial_cost(cost, num_rows);
    return (cost);
}


update_cost (cost, net)
INOUT int **cost;		/* the cost matrix */
IN NETPTR net;			/* a net which was just placed in the channel
				   */
{
    register int i;		/* loop counter */
    register int left_col;	/* leftmost column occupied by 'net' */
    register int right_col;	/* rightmost column occupied by 'net' */
    register int row;		/* the row 'net' was placed in */

    left_col = net->leftmost->col;
    right_col = net->rightmost->col;
    row = net->row;

    /* mark blocked rows */
    for (i = 1; i <= s_num_nets; i++)
	if ((s_net_array[i].leftmost != NULL) &&
	    (s_net_array[i].row == 0) &&
	    (s_net_array[i].rightmost->col >= left_col) &&
	    (s_net_array[i].leftmost->col <= right_col))
	{
	    cost[row][i] = INFINITY;
	}
}













