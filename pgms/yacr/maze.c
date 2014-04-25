#include "copyright.h"
#include "yacr.h"

/*******************************************************************
 *
 *  maze attempts to complete the route where there are vertical constraint
 *  violations.  This is done bye calling maze1 ... for each column
 *  untill the route is completed.
 *
 *  maze returns YES if the route is completed, NO if not.
 *  maze uses the global variable Vcv_cols.
 *
 *  Author: Jim Reed
 *
 *  Date: 4-20-84
 *
 ***************************************************************/

int maze (channel, num_rows, num_cols, top, bottom, bad_cols)
INOUT CHANNELPTR channel;	/* the channel data structure */
IN int num_rows;		/* number of rows in the channel */
IN int num_cols;		/* number of columns in the channel */
IN NETPTR *top,			/* the nets on the top edge of the channel */
	  *bottom;		/* the nets on the bottom of the channel */
INT_LIST *bad_cols;		/* columns that cant be routed */
{
    NETPTR top_net,		/* net to be connected to the top of the
				   channel */
	   bottom_net;		/* net to be connected to the bottom of the
				   channel */
    int column;			/* a column with a vertical constraint
				   violation */
    int status;			/* did the maze route succeed? */
    int *save_col;		/* for saving a col BEARDS */
    INT_LIST list1,		/* list of columns not corrected by maze1a or
				   maze1b */
	     list2,		/* list of columns not corrected by maze2 */
	     list3;		/* list of columns not corrected by maze3 */
    int i;			/* loop counter */

    list1 = NULL;
    list2 = NULL;
    list3 = NULL;

    save_col = ALLOC(int, num_rows + 2);
    while (Vcv_cols != NULL)
    {
	column = Vcv_cols->value;
	/* copy the column BEARDS */
	for (i = 1; i <= num_rows; i++)
	  save_col[i] = channel->vert_layer[i][column];
	/* empty the column */
	for (i = 1; i <= num_rows; i++)
	    channel->vert_layer[i][column] = 0;

	top_net = top[column];
	bottom_net = bottom[column];
	status = maze1a (channel, num_rows, num_cols, column, top_net, bottom_net);
	if (status == YES)
	{
	    if (ioform == HUMAN)
		(void) fprintf (output_file, "column %d was routed by maze1a\n", column);
	}
	if (status == NO)
	{
	    status = maze1b (channel, num_rows, num_cols, column, top_net, bottom_net);
	    if (status == YES)
	    {
		if (ioform == HUMAN)
		    (void) fprintf (output_file, "column %d was routed by maze1b\n", column);
	    }
	}
	if (status == NO)
	{
	    /* replace the column */
	    for (i = 1; i <= num_rows; i++)
	      {
		channel->vert_layer[i][column] = save_col[i];  /* BEARDS */
	      }
	    list1 = insert_int (list1, column);
	}
	
	Vcv_cols = Vcv_cols->next;
      }

    /* try using maze2 */
    while (list1 != NULL)
    {
	column = list1->value;
	/* copy the column BEARDS */
	for (i = 1; i <= num_rows; i++)
	  save_col[i] = channel->vert_layer[i][column];
	/* empty the column */
	for (i = 1; i <= num_rows; i++)
	  channel->vert_layer[i][column] = 0;

	top_net = top[column];
	bottom_net = bottom[column];
	status = maze2 (channel, num_rows, num_cols, column, top_net, bottom_net);
	if (status == YES)
	{
	    if (ioform == HUMAN)
		(void) fprintf (output_file,"column %d was routed by maze2\n",column);
	}
	else
	{
	    list2 = insert_int (list2, column);
	    /* refill the column */
	    for (i = 1; i <= num_rows; i++)
	      {
		channel->vert_layer[i][column] = save_col[i];  /* BEARDS */
	      }
	}


	list1 = list1->next;
    }


    /* try using maze3 */
    while (list2 != NULL)
    {
	column = list2->value;
	/* copy the column BEARDS */
	for (i = 1; i <= num_rows; i++)
	  save_col[i] = channel->vert_layer[i][column];
	/* empty the column */
	for (i = 1; i <= num_rows; i++)
	  channel->vert_layer[i][column] = 0;

	top_net = top[column];
	bottom_net = bottom[column];
	status = maze3 (channel, num_rows, num_cols, column, top_net, bottom_net);
	if (status == YES)
	{
	    if (ioform == HUMAN)
		(void) fprintf(output_file,"column %d was routed by maze3\n",column);
	}
	else
	{
	    list3 = insert_int (list3, column);
	    if (ioform == HUMAN)
		(void) fprintf (output_file, "column %d was not routed\n", column);
	    /* refill the column */
	    for (i = 1; i <= num_rows; i++)
	      {
		channel->vert_layer[i][column] = save_col[i]; /* BEARDS */
	      }

	}

	list2 = list2->next;
    }

    Vcv_cols = list3;

    /* return completion status */
    (*bad_cols) = list3;
    if (list3 == NULL)
	return (YES);
    else
	return (NO);
}



/*****************************************************************
 *
 *  search_column searches the given column in the array starting
 *  from the given row and proceeding in the indicated direction.
 *  The row number of the last 0 in a continuous string is returned.  If 
 *  array[row][column] != 0, row is returned.  If array[row][column] == 0
 *  and array[row+1][column] != 0 (and direction==DOWN), row is still
 *  returned.  If row+1 is empty but row+2 is not, row+1 is returned.
 *  If the limit is reached before a nonzero element is found, limit
 *  is returned.  It is assumed that limit > row when direction == DOWN,
 *  and limit < row when direction == UP.
 *
 *  Author: Jim Reed
 *
 *  Date: 4-27-84
 *
 **************************************************************/

int search_column (array, direction, column, row, limit)
IN int **array;			/* the array to be searched */
IN int direction;		/* the direction to search */
IN int column;			/* the column to search in */
IN int row;			/* the starting row */
IN int limit;			/* the last row to look at */
{
    if (array[row][column] != 0)
	return (row);
    else
    {
	if (direction == UP)
	{
	    for (row--; row >= limit; row--)
		if (array[row][column] != 0)
		    return (row + 1);
	    return (limit);
	}
	else  /* direction == DOWN */
	{
	    for (row++; row <= limit; row++)
		if (array[row][column] != 0)
		    return (row - 1);
	    return (limit);
	}
    }
}



/*****************************************************************
 *
 *  search_row searches the given row in the array starting
 *  from the given column and proceeding in the indicated direction.
 *  The column number of the last 0 in a continuous string is returned.  If 
 *  array[row][column] != 0, column is returned.  If array[row][column] == 0
 *  and array[row][column + 1] != 0 (and direction==RIGHT), column is still
 *  returned.  If column+1 is empty but column+2 is not, column+1 is returned.
 *  If the limit is reached before a nonzero element is found, limit
 *  is returned.  It is assumed that limit > column when direction == RIGHT,
 *  and limit < column when direction == LEFT.
 *
 *  Author: Jim Reed
 *
 *  Date: 4-27-84
 *
 **************************************************************/

int search_row (array, direction, row, column, limit)
IN int **array;			/* the array to be searched */
IN int direction;		/* the direction to search */
IN int row;			/* the row to search in */
IN int column;			/* the starting column */
IN int limit;			/* the last column to look at */
{
    if (array[row][column] != 0)
	return (column);
    else
    {
	if (direction == LEFT)
	{
	    for (column--; column >= limit; column--)
		if (array[row][column] != 0)
		    return (column + 1);
	    return (limit);
	}
	else  /* direction == RIGHT */
	{
	    for (column++; column <= limit; column++)
		if (array[row][column] != 0)
		    return (column - 1);
	    return (limit);
	}
    }
}



/*****************************************************************
 *
 *  jog_top_net tries to find a path from check_row down to high_row.
 *  All (if any) paths that are found are placed in a list.  The list
 *  is returned.  If no paths are found, NULL is returned.
 *
 *  Author: Jim Reed
 *
 *  Date: 5-13-84
 *
 ******************************************************************/

PATH_LIST jog_top_net (check_row, left_edge, right_edge, column, top_name,
		     high_row, limit_row, channel)
IN int check_row;		/* the row to jog in */
IN int left_edge, right_edge;	/* how far to the left and right can the net
				   move? */
IN int column;			/* the column to start in */
IN int top_name;		/* the name of the net, so we will know if we
				   bump into it */
IN int high_row,		/* the row we are trying to route to */
       limit_row;		/* the row we are trying to route from */
CHANNELPTR channel;		/* the channel data structure */
{
    int check_col;		/* loop counter */
    int check_row_edge,		/* how far can we check in this row */
	check_col_edge;		/* how far can we check in this column */
    PATHPTR path;		/* one path that we find */
    PATH_LIST routes;		/* list of all paths that have been found */

    routes = NULL;

    /*
     *  try moving left
     */

    check_row_edge = search_row (channel->horiz_layer, LEFT, check_row,
				column, left_edge);
    for (check_col = column - 1;
	 check_col >= check_row_edge;
	 check_col--)
    {
	/* if we happen to cross top_net we should connect there */
	if (channel->vert_layer[check_row][check_col] == top_name)
	{
	    /* return the path */
	    path =insert_path((PATHPTR) 0, VERT, VERT, limit_row, check_row, column);
	    path = insert_path (path, HORIZ, HORIZ, check_col, column,
				check_row);
	    routes = push_path (routes, path);
	}
	/* see if this column can be used */
	check_col_edge = search_column (channel->vert_layer, DOWN,
				      check_col, check_row, high_row);
	if ((check_col_edge == high_row) ||
	    (channel->vert_layer[check_col_edge+1][check_col] == top_name))
	{
	    /* return the path */
	    path =insert_path((PATHPTR) 0, VERT, VERT, limit_row, check_row, column);
	    path = insert_path (path, HORIZ, HORIZ, check_col, column,
	    			check_row);
	    if (check_col_edge == high_row)
		path = insert_path (path, HORIZ, HORIZ, check_col,
				    column, high_row);
	    path = insert_path (path, VERT, VERT, check_row,
				check_col_edge,	check_col);
	    routes = push_path (routes, path);
	}
    }
    /* did we bump into ourself? */
    if (channel->horiz_layer[check_row][check_row_edge-1] == top_name)
    {
	/* return the path */
	path = insert_path ((PATHPTR) 0, VERT, VERT, limit_row, check_row, column);
	path = insert_path (path, HORIZ, HORIZ, check_row_edge, column,
			    check_row);
	routes = push_path (routes, path);
    }

    /*
     *  try moving right
     */

    check_row_edge = search_row(channel->horiz_layer, RIGHT, check_row,
				column, right_edge);
    for (check_col = column + 1;
	 check_col <= check_row_edge;
	 check_col++)
    {
	/* if we happen to cross top_net we should connect there */
	if (channel->vert_layer[check_row][check_col] == top_name)
	{
	    /* return the path */
	    path =insert_path((PATHPTR) 0, VERT, VERT, limit_row, check_row, column);
	    path = insert_path (path, HORIZ, HORIZ, column, check_col,
				check_row);
	    routes = push_path (routes, path);
	}

	/* see if this column can be used */
	check_col_edge = search_column (channel->vert_layer, DOWN,
				      check_col, check_row, high_row);
	if ((check_col_edge == high_row) ||
	    (channel->vert_layer[check_col_edge+1][check_col] == top_name))
	{
	    /* return the path */
	    path =insert_path((PATHPTR) 0, VERT, VERT, limit_row, check_row, column);
	    path = insert_path (path, HORIZ, HORIZ, column, check_col,
				check_row);
	    if (check_col_edge == high_row)
		path = insert_path (path, HORIZ, HORIZ, column,
				    check_col, high_row);
	    path = insert_path (path, VERT, VERT, check_row,
				check_col_edge,	check_col);
	    routes = push_path (routes, path);
	}

    }
    /* did we bump into ourself? */
    if (channel->horiz_layer[check_row][check_row_edge+1] == top_name)
    {
	/* return the path */
	path = insert_path ((PATHPTR) 0, VERT, VERT, limit_row, check_row, column);
	path = insert_path (path, HORIZ, HORIZ, column, check_row_edge,
			    check_row);
	routes = push_path (routes, path);
    }

    /* return the list of paths */
    return (routes);
}



/*****************************************************************
 *
 *  jog_bottom_net tries to find paths from check_row up to low_row.
 *  All (if any) paths are put into an ordered list.  The list is
 *  returned.  If no paths are found, NULL is returned.
 *
 *  Author: Jim Reed
 *
 *  Date: 5-13-84
 *
 ******************************************************************/

PATH_LIST jog_bottom_net (check_row, left_edge, right_edge, column,
			  bottom_name, low_row, limit_row, channel)
IN int check_row;		/* the row to jog in */
IN int left_edge, right_edge;	/* how far to the left and right can the net
				   move? */
IN int column;			/* the column to start in */
IN int bottom_name;		/* the name of the net, so we will know if we
				   bump into it */
IN int low_row,			/* the row we are trying to route to */
       limit_row;		/* the row we are trying to route from */
CHANNELPTR channel;		/* the channel data structure */
{
    int check_col;		/* loop counter */
    int check_row_edge,		/* how far can we check in this row */
	check_col_edge;		/* how far can we check in this column */
    PATHPTR path;		/* the path that we find */
    PATH_LIST routes;		/* list of possible paths */

    routes = NULL;

    /*
     *  try moving left
     */

    check_row_edge = search_row (channel->horiz_layer, LEFT, check_row,
				column, left_edge);
    for (check_col = column - 1;
	 check_col >= check_row_edge;
	 check_col--)
    {
	/* if we happen to cross bottom_net we should connect there */
	if (channel->vert_layer[check_row][check_col] == bottom_name)
	{
	    /* return the path */
	    path = insert_path ((PATHPTR) 0, VERT, VERT, check_row, limit_row,
				column);
	    path = insert_path (path, HORIZ, HORIZ, check_col, column,
				check_row);
	    routes = push_path (routes, path);
	}
	/* see if this column can be used */
	check_col_edge = search_column (channel->vert_layer, UP,
				      check_col, check_row, low_row);
	if ((check_col_edge == low_row) ||
	    (channel->vert_layer[check_col_edge-1][check_col] == bottom_name))
	{
	    /* return the path */
	    path = insert_path ((PATHPTR) 0, VERT, VERT, check_row, limit_row,
				column);
	    path = insert_path (path, HORIZ, HORIZ, check_col, column,
				check_row);
	    if (check_col_edge == low_row)
		path = insert_path (path, HORIZ, HORIZ, check_col,
				    column, low_row);
	    path = insert_path (path, VERT, VERT, check_col_edge,
				check_row, check_col);
	    routes = push_path (routes, path);
	}
    }
    /* did we bump into ourself? */
    if (channel->horiz_layer[check_row][check_row_edge-1] == bottom_name)
    {
	/* return the path */
	path = insert_path ((PATHPTR) 0, VERT, VERT, check_row, limit_row,
			    column);
	path = insert_path (path, HORIZ, HORIZ, check_row_edge, column,
			    check_row);
	routes = push_path (routes, path);
    }

    /*
     *  try moving right
     */

    check_row_edge = search_row(channel->horiz_layer, RIGHT, check_row,
				column, right_edge);
    for (check_col = column + 1;
	 check_col <= check_row_edge;
	 check_col++)
    {
	/* if we happen to cross bottom_net we should connect there */
	if (channel->vert_layer[check_row][check_col] == bottom_name)
	{
	    /* return the path */
	    path = insert_path ((PATHPTR) 0, VERT, VERT, check_row, limit_row,
				column);
	    path = insert_path (path, HORIZ, HORIZ, column, check_col,
				check_row);
	    routes = push_path (routes, path);
	}

	/* see if this column can be used */
	check_col_edge = search_column (channel->vert_layer, UP,
				      check_col, check_row, low_row);
	if ((check_col_edge == low_row) ||
	    (channel->vert_layer[check_col_edge-1][check_col] == bottom_name))
	{
	    /* return the path */
	    path = insert_path ((PATHPTR) 0, VERT, VERT, check_row, limit_row,
				column);
	    path = insert_path (path, HORIZ, HORIZ, column, check_col,
				check_row);
	    if (check_col_edge == low_row)
		path = insert_path (path, HORIZ, HORIZ, column,
				    check_col, low_row);
	    path = insert_path (path, VERT, VERT, check_col_edge, 
				check_row, check_col);
	    routes = push_path (routes, path);
	}

    }
    /* did we bump into ourself? */
    if (channel->horiz_layer[check_row][check_row_edge+1] == bottom_name)
    {
	/* return the path */
	path = insert_path ((PATHPTR) 0, VERT, VERT, check_row, limit_row,
			    column);
	path = insert_path (path, HORIZ, HORIZ, column, check_row_edge,
			    check_row);
	routes = push_path (routes, path);
    }

    /* return the list of paths */
    return (routes);
}

