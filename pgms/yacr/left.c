#include "copyright.h"
#include "yacr.h"

/********************************************************************
 *
 *  move_left places all nets and connects all pins to the left of
 *  column initial_column.
 *
 *  Author: Jim Reed
 *
 *  Date: 4-8-84
 *
 *  Modified 3-26-85 by D. Braun to return success predicate for
 * irregular channels.
 *
 *******************************************************************/

move_left(channel, cost, top, bottom, initial_column, num_rows,
		num_cols, num_nets)
INOUT CHANNELPTR channel;	/* the channel data structure */
      int **cost;		/* pointer to space for cost matrix */
IN NETPTR *top,			/* the top edge of the channel */
	  *bottom;		/* the bottom edge of the channel */
IN int initial_column;		/* column to move left from */
IN int num_rows;		/* number of rows in the channel */
IN int num_cols;		/* number of columns in the channel */
IN int num_nets;		/* just here for place_all_nets */
{
    NET_LIST placeable_nets;	/* list of nets that have entered the
				   channel, but have not been assigned to a
				   row */
    int column;			/* the column being checked */

    placeable_nets = NULL;


    for (column = initial_column - 1; column > 0; column--)
    {
	/********
	 *  if a new net enters the channel, put it in placeable_nets
	 ********/

	/* check top edge for new net */

	if ((top[column]->name != 0) && (top[column] != bottom[column]))
	    if (column == top[column]->rightmost->col)
	    {
		placeable_nets = insert_net (placeable_nets, top[column]);
	    }

	/* check bottom edge for new net */

	if (bottom[column]->name != 0)
	    if (column == bottom[column]->rightmost->col)
	    {
		placeable_nets = insert_net (placeable_nets, bottom[column]);
	    }


	/********
	 *  if a net ends in this column, place all placeable_nets;
	 ********/

	/* check top edge for ending net */

	if (top[column]->name != 0)
	    if (column == top[column]->leftmost->col)
	    {
		if (place_all_nets (channel, cost, placeable_nets,
				num_rows, num_nets, num_cols) == FALSE)
		    return(FALSE);
		placeable_nets = NULL;
	    }

	/* check bottom edge for ending net */

	if (bottom[column]->name != 0)
	    if (column == bottom[column]->leftmost->col)
	    {
		if (place_all_nets (channel, cost, placeable_nets,
				num_rows, num_nets, num_cols) == FALSE)
		    return(FALSE);
		placeable_nets = NULL;
	    }
    }

    /*
     *  make sure all nets were placed
     */

    if (place_all_nets (channel, cost, placeable_nets,
    		num_rows, num_nets, num_cols) == FALSE)
    return(FALSE);

    return(TRUE);
}


