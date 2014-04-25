#include "copyright.h"
#include "yacr.h"

/*********************************************************************
 *
 *  maze1a attempts to route around the vertical constraint violation
 *  using an adjacent columns and a short horizontal segment
 *  in the vertical layer.
 *  This routine assumes that the column with the VCV has already been
 *  emptied.
 *  maze1a returns YES if successful, NO otherwise.
 *
 *  Author: Jim Reed
 *
 *  Date: 4-20-84
 *
 *********************************************************************/

int maze1a (channel, num_rows, num_cols, column, top_net, bottom_net)
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
    int empty;			/* a flag. YES if the column is empty, NO
				   otherwise. */
    int high_row,		/* row in which the highest of top_net and
				   bottom_net is placed in */
	low_row;		/* row in which the lowest is placed */
    int check_col;		/* column being checked to see if it is empty
				   */
    int jog_row;		/* the row used to jog in if we have the
				   special case of maze1 causing parallel
				   lines */
    PATHPTR path;		/* the rectangles used to route a net */

    /*
     *  set high_row and low_row
     */
    high_row = top_net->row;
    low_row = bottom_net->row;

    /*
     *  check column-1
     */

    check_col = column - 1;
    if (check_col == 0)		/* dont work outside of the channel */
	empty = NO;
    else if (search_column (channel->vert_layer, DOWN, check_col,
			   low_row, high_row) == high_row)
	empty = YES;
    else
	empty = NO;


    if (empty == YES)
    {

	/* jog top_net */
	if (low_row > 1)
	{
	  	/* BEARDS -- added check on [low_row - 1][column] */
	    if ((channel->vert_layer[low_row - 1][check_col] == 0) &&
		((channel->vert_layer[low_row - 1][column] == 0) ||
		 (channel->vert_layer[low_row - 1][column] ==top_net->name)) &&
		((channel->horiz_layer[high_row][check_col] == top_net->name)
		 || (channel->horiz_layer[high_row][check_col] == 0)))
	    {
		/* route top_net */
		if (channel->vert_layer[low_row-1][column-2] != top_net->name)
		{
		    /* use the basic maze1 route */
		    path = insert_path ((PATHPTR) 0, VERT, VERT, 1, low_row - 1,
					column);
		    path = insert_path (path, VERT, VERT, low_row - 1,
					high_row, check_col);
		}
		else
		{
		    /* the standard maze1 route will cause parallel lines
		     * that may look like a ladder on a plot.  avoid that */
		    jog_row = search_column (channel->vert_layer, UP,
						check_col, low_row-1, 1);
		    while (channel->vert_layer[jog_row][column-2] != 
								top_net->name)
			jog_row++;
		    path = insert_path ((PATHPTR) 0, VERT, VERT, 1, jog_row, column);
		    path = insert_path (path, VERT, HORIZ, column - 2, column,
					jog_row);
		}
		draw_rect (channel, top_net->name, path);

		if (channel->horiz_layer[high_row][check_col] == 0)
		    channel->horiz_layer[high_row][check_col] = top_net->name;
		if (channel->horiz_layer[high_row][column+1] != top_net->name)
		    channel->horiz_layer[high_row][column] = 0;

		/* route bottom_net */
		draw_rect (channel, bottom_net->name, 
			   insert_path ((PATHPTR) 0, VERT, VERT, low_row, num_rows,
					column) );

		return (YES);
	    }
	}

	/* jog bottom_net */
	if (high_row < num_rows)
	{
	  	/* BEARDS -- added check on [high_row + 1][column] */
	    if ((channel->vert_layer[high_row + 1][check_col] == 0) &&
		((channel->vert_layer[high_row - 1][column] == 0) ||
		 (channel->vert_layer[high_row- 1][column] ==bottom_net->name)) &&
		((channel->horiz_layer[low_row][check_col]==bottom_net->name)
		 || (channel->horiz_layer[low_row][check_col] == 0) ))
	    {
		/* route bottom_net */
		if (channel->vert_layer[high_row+1][column-2] !=
							bottom_net->name)
		{
		    /* use the basic maze1 route */
		    path = insert_path ((PATHPTR) 0, VERT, VERT, high_row + 1,
					num_rows, column);
		    path = insert_path (path, VERT, VERT, high_row + 1,
					low_row, check_col);
		}
		else
		{
		    /* the standard maze1 route will cause parallel lines
		     * that may look like a ladder on a plot.  avoid that */
		    jog_row = search_column (channel->vert_layer, DOWN, 
					check_col, high_row+1, num_rows);
		    while (channel->vert_layer[jog_row][column-2] !=
							bottom_net->name)
			jog_row--;
		    path = insert_path ((PATHPTR) 0, VERT, VERT, jog_row,
					num_rows, column);
		    path = insert_path (path, VERT, HORIZ, column - 2, column,
					jog_row);
		}
		draw_rect (channel, bottom_net->name, path);

		if (channel->horiz_layer[low_row][check_col] == 0)
		    channel->horiz_layer[low_row][check_col]=bottom_net->name;
		if (channel->horiz_layer[low_row][column+1]!=bottom_net->name)
		    channel->horiz_layer[low_row][column] = 0;

		/* route top_net */
		draw_rect (channel, top_net->name,
			  insert_path((PATHPTR) 0, VERT, VERT, 1, high_row, column));

		return (YES);
	    }
	}
    }

    /*
     *  check column+1
     */

    check_col = column + 1;
    if (check_col > num_cols)
	empty = NO;
    else if (search_column (channel->vert_layer, DOWN, check_col,
			    low_row, high_row) == high_row)
	empty = YES;
    else
	empty = NO;


    if (empty == YES)
    {

	/* jog top_net */
	if (low_row > 1)
	  	/* BEARDS -- added check on [low_row - 1][column] */
	    if ((channel->vert_layer[low_row - 1][check_col] == 0) &&
		((channel->vert_layer[low_row - 1][column] == 0) ||
		 (channel->vert_layer[low_row - 1][column] ==top_net->name)) &&
		((channel->horiz_layer[high_row][check_col] == top_net->name)
		 || (channel->horiz_layer[high_row][check_col] == 0)))
	    {
		/* route top_net */
		if (channel->vert_layer[low_row-1][column+2] != top_net->name)
		{
		    path = insert_path ((PATHPTR) 0, VERT, VERT, 1, low_row - 1,
					column);
		    path = insert_path (path, VERT, VERT, low_row - 1,
					high_row, check_col);
		}
		else
		{
		    jog_row = search_column (channel->vert_layer, UP,
					     check_col, low_row-1, 1);
		    while (channel->vert_layer[jog_row][column+2] !=
							top_net->name)
			jog_row++;
		    path = insert_path ((PATHPTR) 0, VERT, VERT, 1, jog_row, column);
		    path = insert_path (path, VERT, HORIZ, column + 2, column,
						jog_row);
		}
		draw_rect (channel, top_net->name, path);

		if (channel->horiz_layer[high_row][check_col] == 0)
		    channel->horiz_layer[high_row][check_col] = top_net->name;
		if (channel->horiz_layer[high_row][column-1] != top_net->name)
		    channel->horiz_layer[high_row][column] = 0;

		/* route bottom_net */
		draw_rect (channel, bottom_net->name, 
			   insert_path ((PATHPTR) 0, VERT, VERT, low_row, num_rows,
					column) );

		return (YES);
	    }

	/* jog bottom_net */
	if (high_row < num_rows)
	  	/* BEARDS -- added check on [high_row + 1][column] */
	    if ((channel->vert_layer[high_row + 1][check_col] == 0) &&
		((channel->vert_layer[high_row - 1][column] == 0) ||
		 (channel->vert_layer[high_row- 1][column] ==bottom_net->name)) &&
		((channel->horiz_layer[low_row][check_col]==bottom_net->name)
		 || (channel->horiz_layer[low_row][check_col] == 0)))
	    {
		/* route bottom_net */
		if (channel->vert_layer[high_row+1][column+2] !=
							bottom_net->name)
		{
		    path = insert_path ((PATHPTR) 0, VERT, VERT, high_row + 1,
						num_rows, column);
		    path = insert_path (path, VERT, VERT, high_row + 1,
					low_row, check_col);
		}
		else
		{
		    jog_row = search_column (channel->vert_layer, DOWN,
					     check_col, high_row+1, num_rows);
		    while (channel->vert_layer[jog_row][column+2] !=
							bottom_net->name)
			jog_row--;
		    path = insert_path ((PATHPTR) 0, VERT, VERT, num_rows, jog_row,
							column);
		    path = insert_path (path, VERT, HORIZ, column + 2, column,
					jog_row);
		}
		draw_rect (channel, bottom_net->name, path);

		if (channel->horiz_layer[low_row][check_col] == 0)
		    channel->horiz_layer[low_row][check_col]=bottom_net->name;
		if (channel->horiz_layer[low_row][column-1]!=bottom_net->name)
		    channel->horiz_layer[low_row][column] = 0;

		/* route top_net */
		draw_rect (channel, top_net->name,
			  insert_path((PATHPTR) 0, VERT, VERT, 1, high_row, column));

		return (YES);
	    }
    }

    return (NO);
}



/*****************************************************************
 *
 *  maze1b attempts to route around the vertical constraint violation
 *  using both adjacent columns and short horizontal segments in the
 *  vertical layer.
 *  maze1b return YES if successful, NO otherwise.
 *
 *  Author: Jim Reed
 *
 *  Date:     4-20-84
 *  Modified: 1-17-85  removed unnecessary restrictions
 *
 *****************************************************************/

int maze1b (channel, num_rows, num_cols, column, top_net, bottom_net)
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
    int i, j;			/* loop counters */
    int high_row,		/* row in which top_net is placed */
	med_row,		/* one of the rows in which the nets meet */
	low_row;		/* row in which bottom_net is placed */

    /*
     *  if the entire column is not empty, maze1b will not work
     */

/* no need to search, the column is emptied before maze1b is called
    if (search_column (channel->vert_layer, UP, column, num_rows, 1) != 1)
	return (NO);
 */
    /*
     *  this algorithm cannot work if the column is first or last
     */

    if ((column == 1) || (column == num_cols))
	return (NO);

    /*
     *  set high_row and low_row
     */

    high_row = top_net->row;
    low_row = bottom_net->row;

    /*
     *  try top_net jogging left and bottom_net jogging right
     */

    /* search from low_row down to high_row */
    i = low_row;
    while (channel->vert_layer[i][column + 1] == 0)
	i++;
    med_row = i - 1;
    i -= 2;
    if (med_row >= low_row + 1)
	while (channel->vert_layer[i][column - 1] == 0)
	    i++;
    if ((med_row >= low_row + 1) && (i > high_row) &&
	((channel->horiz_layer[low_row][column + 1] == 0) ||
	 (channel->horiz_layer[low_row][column + 1] == bottom_net->name)) &&
	((channel->horiz_layer[high_row][column - 1] == 0) ||
	 (channel->horiz_layer[high_row][column - 1] == top_net->name))  )
    {
	/* connect top_net */
	channel->horiz_layer[high_row][column - 1] = top_net->name;
	for (j = 1; j < med_row; j++)
	    channel->vert_layer[j][column] = top_net->name;
	for (j = med_row - 1; j <= high_row; j++)
	    channel->vert_layer[j][column - 1] = top_net->name;

	/* connect bottom_net */
	channel->horiz_layer[low_row][column + 1] = bottom_net->name;
	for (j = low_row; j <= med_row; j++)
	    channel->vert_layer[j][column + 1] = bottom_net->name;
	for (j = med_row; j <= num_rows; j++)
	    channel->vert_layer[j][column] = bottom_net->name;

	/* signal success */
	return (YES);
    }

    /*
     *  try top_net jogging right and bottom_net jogging left
     */

    i = low_row;
    while (channel->vert_layer[i][column - 1] == 0)
	i++;
    med_row = i - 1;
    i -= 2;
    if (med_row >= low_row + 1)
	while (channel->vert_layer[i][column + 1] == 0)
	    i++;
    i--;
    if ((med_row >= low_row + 1) && (i > high_row) &&
	((channel->horiz_layer[low_row][column - 1] == 0) ||
	 (channel->horiz_layer[low_row][column - 1] == bottom_net->name)) &&
	((channel->horiz_layer[high_row][column + 1] == 0) ||
	 (channel->horiz_layer[high_row][column + 1] == top_net->name))  )
    {
	/* connect top_net */
	channel->horiz_layer[high_row][column + 1] = top_net->name;
	for (j = 1; j < med_row; j++)
	    channel->vert_layer[j][column] = top_net->name;
	for (j = med_row - 1; j <= high_row; j++)
	    channel->vert_layer[j][column + 1] = top_net->name;

	/* connect bottom_net */
	channel->horiz_layer[low_row][column - 1] = bottom_net->name;
	for (j = low_row; j <= med_row; j++)
	    channel->vert_layer[j][column - 1] = bottom_net->name;
	for (j = med_row; j <= num_rows; j++)
	    channel->vert_layer[j][column] = bottom_net->name;

	/* signal success */
	return (YES);
    }

    return (NO);
}


