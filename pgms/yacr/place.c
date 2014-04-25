#include "copyright.h"
#include "yacr.h"

/*******************************************************************
 *
 *  place_all_nets assigns each net in placeable_nets to a row in the
 *  channel.  The channel structure is updated to show where the net
 *  has been placed.
 *  The following algorithm is used.
 *	(1). The cost matrix is computed;
 *	(2). All nets that can be placed in only one row are placed;
 *	(3). If any nets remain, the net with the greatest sum of costs 
 *	     is placed;
 *	(4). If all nets are not placed, go to (2);
 *  This algorithm assumes that the first (zero-th) row of the cost matrix
 *  contains the number of rows each net can be placed in.
 *
 *  Author: Jim Reed
 *
 *  Date: 3-28-84
 *  Modified: 4-20-84
 *  Last modified: 9-21-84 changed place_singletons to place_max_info_nets
 *  Modified 3-26-85 by D. Braun to return success predicate for
 * irregular channels.
 *
 *******************************************************************/

/*ARGSUSED*/
place_all_nets (channel, cost, placeable_nets, num_rows, num_nets,
			num_cols)
INOUT CHANNELPTR channel;	/* the channel data structure */
IN int **cost;			/* the cost matrix */
INOUT NET_LIST placeable_nets;	/* the nets that are to be placed, when a net
				   is placed, it is removed from the list */
IN int num_rows;		/* number of rows in the channel */
IN int num_nets;		/* number of nets, probably just here for
				   print_cost */
IN int num_cols;		/* number of columns, probably just here for
				   print_channel */
{
    NET_LIST trav, oldtrav;	/* used to traverse placeable_nets */
    int max_cost;		/* used to find net to place */
    int sum;			/* sum of the row costs for a net */
    NETPTR max_net;		/* net with max_cost */



    while (placeable_nets != NULL)
    {

	/*
	 *  find the net with maximum cost
	 */

	max_net = placeable_nets->net;
	max_cost = column_sum (cost, max_net->name, num_rows);
	for (trav = placeable_nets->next; trav != NULL; trav = trav->next)
	{
	    sum = column_sum (cost, trav->net->name, num_rows);
	    if (max_cost < sum)
	    {
		max_net = trav->net;
		max_cost = sum;
	    }
/* 	    else if (max_cost == sum)
  (void) printf ("here is a choice, %d, %d\n", number_to_name(trav->net->name),
					number_to_name(max_net->name)); */
	}

	/*
	 *  place max_net.  If it cannot be placed, we fail and
	 *  return a value indicating failure.
	 */

	if (place_one_net (channel, cost, max_net, num_rows) == FALSE)
	    return(FALSE);;

	/*
	 *  remove max_net from placeable_nets list
	 */

	oldtrav = NULL;
	trav = placeable_nets;
	while (trav->net != max_net)
	{
	    oldtrav = trav;
	    trav = trav->next;
	}
	if (oldtrav == NULL)
	    placeable_nets = placeable_nets->next;
	else
	    oldtrav->next = trav->next;


/* print_channel (channel, num_rows, num_cols); */

    }

    return(TRUE);

}



/********************************************************************
 *
 *  place_one_net assigns 'net' to its most preferred row in the channel
 *  The channel data structure is updated, but cost is not.
 *
 *  This routine will update Vcv_cols if there is a vertical constraint
 *  violation found while placing the net.
 *
 *  Author: Jim Reed
 *
 *  Date: 3-28-84
 *  Updated 3/26/85 by D. Braun to only fill in vertical layer
 *  as far as the indented border.
 *  Also returns success predicate: FALSE if can't place net.
 *
 **********************************************************************/

place_one_net (channel, cost, net, num_rows)
INOUT CHANNELPTR channel;	/* the channel data */
IN int **cost;			/* the cost matrix */
IN NETPTR net;			/* the net to be placed */
IN int num_rows;		/* number of rows int the channel */
{
    int i,j;			/* loop counter */
    int name;			/* net->name */
    int best_row;		/* row with the least cost for 'net' */
    int least_vcv;		/* number of VCV's caused by placing 'net' in
				   one of the good rows */
    int this_vcv;		/* number of VCV's cauased by placing 'net'
				   in the current row */
    INT_STACK good_rows;	/* rows with minimum number of vertical
				   constraint violations */
    int least_cost;		/* cost of placing 'net' in best_row */
    PIN_LIST pin;		/* used to traverse the list of pins 'net' is
				   connected to */
    PATHPTR rect;		/* a rectangle that is being placed in the
				   channel */
/*     (void) printf ("placing net %d\n", number_to_name(net->name)); */
/*     print_cost (cost, 119, num_rows); */
/*  net_cost (cost, channel, net, num_rows); */

    name = net->name;

    /*
     *  find best_row
     */

    /* make list of rows in preferred range with min VCV for this net */
    least_vcv = INFINITY;
    good_rows = NULL;
    for (i = net->top_free_row; i <= net->bottom_free_row; i++)
	if (cost[i][name] < HIGH)
	{
	    /* count VCV's for this row */
	    this_vcv = 0;
	    for (pin = net->leftmost; pin != NULL; pin = pin->right_list)
		if ((channel->vert_layer[i][pin->col] != 0)
		   && (channel->vert_layer[i][pin->col] != name))
		    this_vcv++;
	    /* is this_vcv a new minimum? */
	    if (this_vcv < least_vcv)
	    {
		least_vcv = this_vcv;
		good_rows = insert_int ((INT_LIST) 0, i);
	    }
	    else if (this_vcv == least_vcv)
		good_rows = insert_int (good_rows, i);
	}
    /* if there were no available rows in the preferred range, then
	make list of rows with min VCV, but avoid using the top or
	bottom rows if possible */
    if (good_rows == NULL)
	for (i = net->top_free_row + 1; i < net->bottom_free_row; i++)
	    if (cost[i][name] < INFINITY)
	    {
		/* count VCV's for this row */
		this_vcv = 0;
		for (pin = net->leftmost; pin != NULL; pin = pin->right_list)
		    if ((channel->vert_layer[i][pin->col] != 0)
		        && (channel->vert_layer[i][pin->col] != name))
			this_vcv++;
		/* is this_vcv a new minimum? */
		if (this_vcv < least_vcv)
		{
		    least_vcv = this_vcv;
		    good_rows = insert_int ((INT_LIST) 0, i);
		}
		else if (this_vcv == least_vcv)
		    good_rows = insert_int (good_rows, i);
	    }
    /* use top and/or bottom row if necessary */
    if (good_rows == NULL)
	for (i = net->top_free_row, j=1; j <= 2;
   	           	i = net->bottom_free_row, j++)
	    if (cost[i][name] < INFINITY)
	    {
		/* count VCV's for this row */
		this_vcv = 0;
		for (pin = net->leftmost; pin != NULL; pin = pin->right_list)
		    if ((channel->vert_layer[i][pin->col] != 0)
		        && (channel->vert_layer[i][pin->col] != name))
			this_vcv++;
		/* is this_vcv a new minimum? */
		if (this_vcv < least_vcv)
		{
		    least_vcv = this_vcv;
		    good_rows = insert_int ((INT_LIST) 0, i);
		}
		else if (this_vcv == least_vcv)
		    good_rows = insert_int (good_rows, i);
	    }
if (good_rows == NULL)
 {
	(void) fprintf (output_file, "Cannot place net %d\n",
					number_to_name(name));

	if (are_indents() == NO)
	{
	    (void) fprintf(output_file,"This should not happen with no indentations!\n");
	    exit(1);
	}

	if (is_fixed_net(net)==YES)
	{
	    (void) fprintf(output_file,"A fixed net has collided with a channel indentation!\n");
	    (void) fprintf(output_file,"You must rearrange the fixed nets.\n");

	    exit(1);
	}

	return(FALSE);
 }
    /* select one of the good_rows as the best_row */
    best_row = good_rows->value;
    least_cost = cost[best_row][name];
    for (good_rows = good_rows->next; good_rows != NULL;
				      good_rows = good_rows->next)
	if (least_cost > cost[good_rows->value][name])
	{
	    best_row = good_rows->value;
	    least_cost = cost[best_row][name];
	}

    /*
     *  tell net what row it is in
     */

    net->row = best_row;

    /*
    (void) printf("Net name %d number %d placed on row %d\n",number_to_name(net->name),net->name,net->row);
    */

    /*
     *  put net in the row in channel
     */

    if (net->leftmost->col != net->rightmost->col)
    {
	rect = NULL;
	rect = insert_path (rect, HORIZ, HORIZ, net->leftmost->col,
			    net->rightmost->col, best_row);
	draw_rect (channel, name, rect);
    }

    /*
     *  connect the net to pins on top and bottom of channel
     */

    for (pin = net->leftmost; pin != NULL; pin = pin->right_list)
	/* check for vertical constraint violation */
	if ((channel->vert_layer[best_row][pin->col] != 0)
	    && (channel->vert_layer[best_row][pin->col] != name))
	{
	    /* register the vertical contraint violation */
	    if (ioform == HUMAN)
	    {
		(void) fprintf (output_file, "VCV: nets %2d %2d, column %3d\n",
		      number_to_name(name),
		      number_to_name(channel->vert_layer[best_row][pin->col]),
		      pin->col);
	    }
	    Vcv_cols = insert_int (Vcv_cols, pin->col);

	    /* fill the column to make sure nobody else takes it */
	    for (i = 1; i <= num_rows; i++)
		if (channel->vert_layer[i][pin->col] != BORDER)
		    channel->vert_layer[i][pin->col] = -1;
	}
	else
	{
	    /* connect the net to the pin */
	    if (pin->edge == TOP)
	    {
		for (i = 1; i <= best_row; i++)
		  channel->vert_layer[i][pin->col] = name;
	    }
	    if (pin->edge == BOTTOM)
	    {
		for (i = best_row; i <= num_rows; i++)
		  channel->vert_layer[i][pin->col] = name;
	    }
	}

    /* update the cost matrix to show that part of a row is now blocked */
    update_cost (cost, net);

    return(TRUE);    /* Return TRUE because we succeeded. */
}


/**************************************************************
 *
 *  place_edge_nets guarantees that the nets exiting the edge are
 *  placed in their specified order from top to bottom.  This is
 *  done by modifying the cost matrix for the nets, then calling
 *  place_all_nets.  This also ensures that any nets that connect to 
 *  a pin in the last (or first) column but don't exit the edge get
 *  placed also.
 *
 *  This routine decides which row each net in edge_list is to be placed
 *  in.  The cost of placing the net in its row is set to MED; the
 *  cost of placing the net in any other row is set to ININITY.
 *
 *  Author: Jim Reed
 *
 *  Date: 11-21-84
 *
 ****************************************************************/

int
place_edge_nets (channel, cost, placeable_nets, num_rows, num_nets,
			num_cols, edge_list, num_edge_nets)
INOUT CHANNELPTR channel;	/* the channel data structure */
IN int **cost;			/* the cost matrix */
INOUT NET_LIST placeable_nets;	/* the nets that are to be placed, when a net
				   is placed, it is removed from the list */
IN int num_rows;		/* number of rows in the channel */
IN int num_nets;		/* number of nets, probably just here for
				   print_cost */
IN int num_cols;		/* number of columns, probably just here for
				   print_channel */
IN NETPTR *edge_list;		/* array of nets that exit the channel edge */
IN int num_edge_nets;		/* number of nets in edge_list */
{
    int i, j;			/* loop counter */
    int *row;			/* row[i] is the row that net edge_list[i]
				   will be placed in, finding row[i] is the
				   object of this routine */
    int delta;			/* amount that total cost will change if nets
				   are moved to different rows */

    int curr_row,r;
    int extra;

    row = ALLOC(int, num_edge_nets + 1);

    /* place nets in top 'num_edge_nets' rows */
/*
    for (i = 1; i <= num_edge_nets; i++)
	row[i] = i;
*/

/*
    curr_row = 1;
    extra = 0;
    for(i = 1; i <= num_edge_nets;i++)
      {
	for(;(curr_row <= num_rows) && 
	      (cost[curr_row][edge_list[i]->name] == INFINITY);curr_row++)
	  {}
	if(curr_row <= num_rows)
	  row[i] = curr_row++;
	else
	  {
	    (void) fprintf (output_file, "Adding another row to handle relative pins\n");	    
	    return(0);
	  }
      }
*/

    curr_row = 1;
    extra = 0;
    for(i = 1; i <= num_edge_nets;i++)
      {
	for(r = curr_row;(r <= num_rows) && 
	      (cost[r][edge_list[i]->name] == INFINITY);r++)
	  {}
	if(r <= num_rows)
	  {
	    row[i] = r;
	    curr_row = r + 1;
	  }
	else
	  {
	    extra++;
	  }
      }
    if(extra != 0)
      {
	(void) fprintf (output_file, "Adding %d row(s) to handle relative pins\n",extra);
	return(extra);
      }

    /* adjust placement without changing order */
    for (i = num_edge_nets; i > 0; i--)
    {
	if (row[i] == num_rows)
	    delta = INFINITY;
	else
	  {
	    if((cost[row[i]+1][edge_list[i]->name] == INFINITY) &&
	       (cost[row[i]][edge_list[i]->name] == INFINITY))
	      delta = INFINITY;
	    else
	      delta = cost[row[i]+1][edge_list[i]->name] -
		cost[row[i]][edge_list[i]->name];
	  }

	for (j = i+1; (j <= num_edge_nets) && (row[j]-1 == row[j-1]); j++)
	    if (row[j] == num_rows)
		delta = INFINITY;
	    else
		delta += cost[row[j]+1][edge_list[j]->name] -
					cost[row[j]][edge_list[j]->name];
/* 	(void) printf ("delta = %d\n", delta); */
	if (delta <= MED)
	{
	    j = i++;		/* i++ to make sure that the same net will be
				   checked for possible movement again */
	    do {
		row[j++]++;
	    } while ((row[j] != num_rows) && (row[j] == row[j-1])); /* BEARDS added num_rows check */
/* 	    for (j = 1; j <= num_edge_nets; j++) 
		(void) printf (", %d",row[j]);
	    (void) printf ("\n");
*/
	}
    }

    /* set cost matrix so that each net will be placed in its selected row */
    for (i = 1; i <= num_edge_nets; i++)
    {
	cost[0][edge_list[i]->name] = 1;
	for (j = 1; j <= num_rows; cost[j++][edge_list[i]->name] = INFINITY);
	cost[row[i]][edge_list[i]->name] = MED;
    }

    (void) place_all_nets (channel, cost, placeable_nets, num_rows,
			num_nets, num_cols);
    return(0);
}

/*****************************************************************
 *	place_fixed_nets has the same function as place_edge_nets
 *	above, except that it is called when fixed edge placement
 *	is used. Since it does not have to make any decisions,
 *	it is simpler.
 *
 *
 *	Author:  Doug Braun 2/6/85
 *
 ***************************************************************/


void
place_fixed_nets(channel, cost, placeable_nets, num_rows, num_nets,
			num_cols, edge_list, num_edge_nets)

INOUT CHANNELPTR channel;	/* the channel data structure */
IN int **cost;			/* the cost matrix */
INOUT NET_LIST placeable_nets;	/* the nets that are to be placed, when a net
				   is placed, it is removed from the list */
IN int num_rows;		/* number of rows in the channel */
IN int num_nets;		/* number of nets, probably just here for
				   print_cost */
IN int num_cols;		/* number of columns, probably just here for
				   print_channel */
IN NETPTR *edge_list;		/* array of nets that exit the channel edge */
IN int num_edge_nets;		/* number of nets in edge_list */
{

    int i;    /* loop counter */
    int j;    /* loop counter */

    /* set cost matrix so that each net will be placed in its selected row */
    if(num_rows != num_edge_nets)
    {
	(void) fprintf(output_file, "place_fixed_nets: num_edge_nets not the same as num_rows!\n");
	(void) fflush(output_file);
	abort();
    }

    for (i = 1; i <= num_rows; i++)
    {
	cost[0][edge_list[i]->name] = 1;
	for (j = 1; j <= num_rows; cost[j++][edge_list[i]->name] = INFINITY);
	cost[i][edge_list[i]->name] = MED;
    }

    (void) place_all_nets (channel, cost, placeable_nets, num_rows,
			num_nets, num_cols);
    return;
}

