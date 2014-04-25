#include "copyright.h"
#include "yacr.h"

/***************************************************************
 *
 *  add_one_row checks to see if the channel can be routed with
 *  the simple addition of only one row.  If one more row is sufficient,
 *  a row is added to the channel and the route is completed.
 *  
 *  add_one_row returns YES if the route is completed, NO if not.
 *
 *  Author: Jim Reed
 *
 *  Date: 10-10-84      Routing only to another pin on same edge.
 *  Modified: 11-17-84  Using maze2 style routes.
 *
 *  Adapted for YACR 2.1 by Douglas Braun 8/21/85
 *
 *  Modified 3-27-85 by D. Braun to not try to place new rows
 *  that intersect the irregular borders.
 *  
 **************************************************************/

int add_one_row (channel, col_list, num_rows, num_cols, top, bottom)
INOUT CHANNELPTR channel;	/* the channel data structure */
INT_LIST col_list;		/* linked list of numbers of columns which
				   have not yet been routed */
IN int num_rows;		/* number of rows in the channel */
IN int num_cols;		/* number of columns in the channel */
IN NETPTR *top,			/* the nets on the top edge of the channel */
	  *bottom;		/* the nets on the bottom of the channel */
{
    int i,j;			/* loop counters */
    PATHPTR *new_rows;		/* all of the possible new rows, new_rows[i]
				   is NULL if a new row before row i
				   will not complete the route */
    PATHPTR trav_path;		/* used to traverse a row in new_rows */
    INT_LIST trav_col;		/* the column being checked for routing */
    NETPTR top_net;		/* a net that connects to the top of the
				   channel */
    NETPTR bottom_net;		/* a net that connects to the bottom edge of
				   the channel */
    PATHPTR path;		/* path actually used to connect a pin to its
				   net */
    int vcv_col;		/* column with vertical constraint violation
				   */
    int jog_col;		/* a column that is used in maze2 style
				   routing */
    int right_boundary;		/* rightmost edge of the region that may be
				   used to route the current net */
    int left_boundary;		/* leftmost edge of the region that may be
				   used to route the current net */
    int net_edge;		/* used in calculating right_boundary and
				   left_boundary, the farthest that a net may
				   be extended in its row without overlapping
				   another net */
    PATHPTR temp_path;		/* used to traverse a list of paths in
				   new_rows */

    /*
     *  allocate space for new_rows
     */

    new_rows = ALLOC(PATHPTR, num_rows + 2);
    for (i = 0; i <= num_rows + 1; i++)
	new_rows[i] = insert_path ((PATHPTR) 0, 0, 0, 0, 0, 0);

    for (trav_col = col_list; trav_col != NULL; trav_col = trav_col->next)
    {
	vcv_col = trav_col->value;
	/*
	 *  remove from new_rows rows that definitely cannot be used
	 *  to complete the route
	 */
	for (i = bottom[vcv_col]->row + 1;
	     i <= top[vcv_col]->row;
	     new_rows[i++] = NULL);
	
	/*
	 * Remove rows that intersect any indentations.
	 */
        for (j = 1; j <= num_rows + 1; j++)
	{
	    if (j <= max_top_offset || j > num_rows-max_bottom_offset)
		new_rows[j] = NULL;
	}



	/*
	 *  empty the column, so the route can be done
	 */
	for (i = 1; i <= num_rows; i++)
	    if (channel->vert_layer[i][vcv_col] != BORDER)
	        channel->vert_layer[i][vcv_col] = 0;
    }

    /*
     *  check each column to see if it can be routed by adding a row
     */

    for (trav_col = col_list; trav_col != NULL; trav_col = trav_col->next)
    {
	vcv_col = trav_col->value;
	top_net = top[vcv_col];
	bottom_net = bottom[vcv_col];

	/*
	 *  find rows that can be used to jog top_net
	 */

	/* find right_boundary of routing space for this net and column */
	if (trav_col->next == NULL)
	    right_boundary = num_cols;
	else
	    right_boundary = trav_col->next->value - 1;
	if (top_net->rightmost->edge == RIGHT)
	    net_edge = num_cols;
	else if (channel->horiz_layer[top_net->row][top_net->rightmost->col+1]
		 == 0)
	    net_edge = search_row (channel->horiz_layer, RIGHT, top_net->row,
				 top_net->rightmost->col + 1, num_cols);
	else
	    net_edge = top_net->rightmost->col;
	if (right_boundary > net_edge)
	    right_boundary = net_edge;

	/* find net_edge on left side of net */
	if (top_net->leftmost->edge == LEFT)
	    net_edge = 1;
	else if (channel->horiz_layer[top_net->row][top_net->leftmost->col-1]
		== 0)
	    net_edge = search_row (channel->horiz_layer, LEFT, top_net->row,
				 top_net->leftmost->col - 1, 1);
	else
	    net_edge = top_net->leftmost->col;

	for (i = bottom_net->row; i >= 1; i--)
	    if (new_rows[i] != NULL)
	    {
		/* find left_boundary for this row */
		left_boundary = net_edge;
		for (temp_path = new_rows[i]; temp_path != NULL;
					temp_path = temp_path->next)
		    if ((temp_path->num2 != 0) &&
				(temp_path->num2 > left_boundary))
			left_boundary = temp_path->num2 + 1;

		/* find a route using this row */
		path = top_path_route (i, top_net, vcv_col, channel,
					left_boundary, right_boundary);
		if ((path == NULL) ||
				(intersect_path (new_rows[i], path) == YES))
		    new_rows[i] = NULL;
		else
		{
		    path->next = new_rows[i];
		    new_rows[i] = path;
		}
	    }

	/*
	 *  find rows that can be used to jog bottom_net
	 */

	/* find right_boundary of routing space for this net and column */
	if (trav_col->next == NULL)
	    right_boundary = num_cols;
	else
	    right_boundary = trav_col->next->value - 1;
	if (bottom_net->rightmost->edge == RIGHT)
	    net_edge = num_cols;
	else 
	if(channel->horiz_layer[bottom_net->row][bottom_net->rightmost->col+1]
		 == 0)
	    net_edge = search_row (channel->horiz_layer, RIGHT,
				bottom_net->row, bottom_net->rightmost->col+1,
				num_cols);
	else
	    net_edge = bottom_net->rightmost->col;
	if (right_boundary > net_edge)
	    right_boundary = net_edge;

	/* find net_edge on left side of net */
	if (bottom_net->leftmost->edge == LEFT)
	    net_edge = 1;
	else
	if (channel->horiz_layer[bottom_net->row][bottom_net->leftmost->col-1]
		== 0)
	    net_edge = search_row(channel->horiz_layer, LEFT, bottom_net->row,
				 bottom_net->leftmost->col - 1, 1);
	else
	    net_edge = bottom_net->leftmost->col;

	for (i = top_net->row + 1; i <= num_rows + 1; i++)
	    if (new_rows[i] != NULL)
	    {
		/* find left_boundary for this row */
		left_boundary = net_edge;
		for (temp_path = new_rows[i]; temp_path != NULL;
					temp_path = temp_path->next)
		    if ((temp_path->num2 != 0) &&
				(temp_path->num2 > left_boundary))
			left_boundary = temp_path->num2 + 1;

		/* find a path using this row */
		path = bottom_path_route (i, bottom_net, vcv_col, channel,
					left_boundary, right_boundary);
		if ((path == NULL) ||
				(intersect_path (new_rows[i], path) == YES))
		    new_rows[i] = NULL;
		else
		{
		    path->next = new_rows[i];
		    new_rows[i] = path;
		}
	    }

    }

    /*
     *  if there is a row that can be used for all columns,
     *  then use it to complete the route
     */

    for (i = 1; i <= num_rows + 1; i++)
	if (new_rows[i] != NULL)
	{
	    if (ioform == HUMAN)
		(void) fprintf (output_file,
			"Row %d is being used to complete the route.\n", i);

	    /* make the channel larger by adding a row before row i */
	    enlarge_channel (channel, num_rows, num_cols, i, top, bottom,
				(NETPTR) 0, 0);

	    /* route each column with a vcv */
	    for (trav_col = col_list; trav_col != NULL;
				trav_col = trav_col->next)
	    {
		vcv_col = trav_col->value;
		top_net = top[vcv_col];
		bottom_net = bottom[vcv_col];

		for (trav_path = new_rows[i];
		    (trav_path->num1 != vcv_col) &&
					(trav_path->num2 != vcv_col);
		    trav_path = trav_path->next);

		/* route the nets */
		if (i <= bottom_net->row)
		{
		    /* top_net jogs, bottom_net does not */
		    path = insert_path ((PATHPTR) 0, HORIZ, HORIZ, trav_path->num1,
					trav_path->num2, i);
		    path = insert_path (path, HORIZ, HORIZ, trav_path->num1,
					trav_path->num2, top_net->row+1);
		    path = insert_path (path, VERT, VERT, 1, i, vcv_col);
		    if (trav_path->num1 != vcv_col)
			jog_col = trav_path->num1;
		    else
			jog_col = trav_path->num2;
		    if (channel->vert_layer[i][jog_col] != top_net->name)
			path = insert_path (path, VERT, VERT, i, 
					search_column (channel->vert_layer,
						       DOWN, jog_col, i,
						       top_net->row+1),
					jog_col);
		    draw_rect (channel, top_net->name, path);
		    path = insert_path ((PATHPTR) 0, VERT, VERT, num_rows+1,
					bottom_net->row+1, vcv_col);
		    draw_rect (channel, bottom_net->name, path);
		}
		else
		{
		    /* bottom_net jogs, top_net does not */
		    path = insert_path ((PATHPTR) 0, HORIZ, HORIZ, trav_path->num1,
					trav_path->num2, i);
		    path = insert_path (path, HORIZ, HORIZ, trav_path->num1,
					trav_path->num2, bottom_net->row);
		    path = insert_path (path, VERT, VERT, num_rows+1, i,
					vcv_col);
		    if (trav_path->num1 != vcv_col)
			jog_col = trav_path->num1;
		    else
			jog_col = trav_path->num2;
		    if (channel->vert_layer[i][jog_col] != bottom_net->name)
			path = insert_path (path, VERT, VERT, i, 
					search_column (channel->vert_layer,
						       UP, jog_col, i,
						       bottom_net->row),
					jog_col);
		    draw_rect (channel, bottom_net->name, path);
		    path = insert_path ((PATHPTR) 0, VERT, VERT, 1, top_net->row,
					vcv_col);
		    draw_rect (channel, top_net->name, path);
		}
	    }

	    return (YES);
	}

    /* if execution gets this far, a single row is not sufficient */
    return (NO);
}



/***************************************************************
 *
 *  enlarge_channel adds a row to the channel between rows new_row
 *  and new_row-1.  If new_row is num_rows+1, then the new row is
 *  added at the bottom of the array.
 *
 *  Author: Jim Reed
 *
 *  Date: 11-17-84
 *  Modified: 11-25-84	Update net_array added.
 *  Modified 3-26-85 by D. Braun to handle irreg boundaries
 *
 *****************************************************************/

void enlarge_channel (channel, num_rows, num_cols, new_row, top, bottom,
		net_array, num_nets)
IN CHANNELPTR channel;		/* the channel data structure */
IN int num_rows;		/* number of rows in old_layer (not counting
				   row 0) */
IN int num_cols;		/* number of columns in each row */
IN int new_row;			/* the loation of the new row in the layer */
IN NETPTR *top;			/* array of nets connected to the top edge of
				   the channel */
IN NETPTR *bottom;		/* array of nets connected to the bottom edge
				   of the channel */
IN NETPTR net_array;		/* array of net data structures */
IN int num_nets;		/* size of net_array */
{
    int **new_layer;		/* the newly allocated layer */
    int above_new;		/* new_row - 1 */
    int below_new;		/* new_row + 1 */
    int i;			/* loop counter */

    above_new = new_row - 1;
    below_new = new_row + 1;

    /* 
     * Make sure the new row is completely between the irregular
     * borders.
     */

    if (new_row <= max_top_offset || new_row > num_rows-max_bottom_offset)
    {
        (void) fprintf(output_file,"Can't add row %d that intersects border\n",
			    new_row);
	exit(1);
    }



    /*
     *  allocate new layers and move data from old_layers to new_layer
     */
    new_layer = ALLOC(int *, num_rows + 3);
    for (i = 0; i < new_row; i++)
	new_layer[i] = channel->horiz_layer[i];
    for (i = new_row; i <= num_rows+1; i++)
	new_layer[i+1] = channel->horiz_layer[i];
    channel->horiz_layer = new_layer;

    new_layer = ALLOC(int *, num_rows + 3);
    for (i = 0; i < new_row; i++)
	new_layer[i] = channel->vert_layer[i];
    for (i = new_row; i <= num_rows+1; i++)
	new_layer[i+1] = channel->vert_layer[i];
    channel->vert_layer = new_layer;

    /*
     *  add new row to each new layer
     */

    channel->horiz_layer[new_row] = ALLOC(int, num_cols + 2);
    channel->vert_layer[new_row] = ALLOC(int, num_cols + 2);
    /*
     *  make sure connectivity is maintained across the new row
     */

    /* horiz_layer */
    if ((new_row > 1) && (new_row < num_rows + 1))
    {
	for (i = 0; i <= num_cols + 1; i++)
	    if (channel->horiz_layer[above_new][i] ==
				channel->horiz_layer[below_new][i])
		channel->horiz_layer[new_row][i] =
				channel->horiz_layer[above_new][i];
	    else
		channel->horiz_layer[new_row][i] = 0;
    }
    else
	for (i = 0; i <= num_cols + 1; i++)
	    channel->horiz_layer[new_row][i] = 0;

    /* vert_layer */
    for (i = 1; i <= num_cols; i++)
    {
	if (channel->vert_layer[above_new][i] ==
				channel->vert_layer[below_new][i])
	    channel->vert_layer[new_row][i] =
				channel->vert_layer[above_new][i];
	else if (channel->vert_layer[above_new][i] == BORDER &&
		     channel->vert_layer[below_new][i] == top[i]->name)
	    channel->vert_layer[new_row][i] = top[i]->name;
        else if (channel->vert_layer[below_new][i] == BORDER &&
		  channel->vert_layer[above_new][i] == bottom[i]->name)
	    channel->vert_layer[new_row][i] = bottom[i]->name;
	else
	    channel->vert_layer[new_row][i] = 0;

    }
	 
    channel->vert_layer[new_row][0] = 0;
    channel->vert_layer[new_row][num_cols + 1] = 0;

    /*
     *  update net_array if it was passed in
     */

    if (net_array != NULL)
	for (i = 0; i <= num_nets; i++)
	    if (net_array[i].row >= new_row)
		net_array[i].row++;

}


/**********************************************************
 *
 *  top_path_route finds (if it exists) a maze2 style route that will
 *  connect 'net' to the top of column 'col' using a metal jog in row
 *  'new_row'.  If a route exists, a pointer to the metal rectangle is
 *  returned.  If no route exists, NULL is returned.
 *
 *  Author: Jim Reed
 *
 *  Date: 11-17-84
 *
 ******************************************************/

PATHPTR top_path_route (new_row, net, column, channel, left_boundary, 
			right_boundary)
IN int new_row;			/* the row that will be added for this route
				   */
IN NETPTR net;			/* the new being routed */
IN int column;			/* the column with the VCV */
IN CHANNELPTR channel;		/* the channel data structure */
IN int left_boundary;		/* farthest point to the left that may be
				   used for this route */
IN int right_boundary;		/* farthest point to the right that may be
				   used for this route */
{
    int check_col;		/* loop counter */
    int check_col_edge;		/* how far can we move down in this column */
    int name;			/* net->name */

    name = net->name;

    /* try moving left */
    for (check_col = column - 1; check_col >= left_boundary; check_col--)
    {
	/* if we happen to cross 'net' we should connect there */
	if (channel->vert_layer[new_row][check_col] == name)
	    return (insert_path ((PATHPTR) 0, HORIZ, HORIZ, check_col, column, 
				 new_row));

	/* see if this column can be used */
	check_col_edge = search_column (channel->vert_layer, DOWN, 
				check_col, new_row, net->row);
	if ((check_col_edge == net->row) ||
	    ((check_col_edge > net->row) &&
	     (channel->vert_layer[check_col_edge+1][check_col] == name)))
	    return (insert_path ((PATHPTR) 0, HORIZ, HORIZ, check_col, column,
				 new_row));
    }

    /* try moving right */
    for (check_col = column + 1; check_col <= right_boundary; check_col++)
    {
	/* if we happen to cross 'net' we should connect there */
	if (channel->vert_layer[new_row][check_col] == name)
	    return (insert_path ((PATHPTR) 0, HORIZ, HORIZ, check_col, column,
				 new_row));

	/* see if this column can be used */
	check_col_edge = search_column (channel->vert_layer, DOWN,
				check_col, new_row, net->row);
	if ((check_col_edge == net->row) ||
	    ((check_col_edge > net->row) &&
	     (channel->vert_layer[check_col_edge+1][check_col] == name)))
	    return (insert_path ((PATHPTR) 0, HORIZ, HORIZ, check_col, column,
				 new_row));
    }

    /* if we have not returned by now, there is no route */
    return (NULL);
}


/**********************************************************
 *
 *  bottom_path_route finds (if it exists) a maze2 style route that will
 *  connect 'net' to the bottom of column 'col' using a metal jog in row
 *  'new_row'.  If a route exists, a pointer to the metal rectangle is
 *  returned.  If no route exists, NULL is returned.
 *
 *  Author: Jim Reed
 *
 *  Date: 11-17-84
 *
 ******************************************************/

PATHPTR bottom_path_route (new_row, net, column, channel, left_boundary, 
			right_boundary)
IN int new_row;			/* the row that will be added for this route
				   */
IN NETPTR net;			/* the new being routed */
IN int column;			/* the column with the VCV */
IN CHANNELPTR channel;		/* the channel data structure */
IN int left_boundary;		/* farthest point to the left that may be
				   used for this route */
IN int right_boundary;		/* farthest point to the right that may be
				   used for this route */
{
    int check_col;		/* loop counter */
    int check_col_edge;		/* how far can we move down in this column */
    int name;			/* net->name */

    name = net->name;

    /* try moving left */
    for (check_col = column - 1; check_col >= left_boundary; check_col--)
    {
	/* if we happen to cross 'net' we should connect there */
	if (channel->vert_layer[new_row][check_col] == name)
	    return (insert_path ((PATHPTR) 0, HORIZ, HORIZ, check_col, column, 
				 new_row));

	/* see if this column can be used */
	check_col_edge = search_column (channel->vert_layer, UP,
				check_col, new_row, net->row);
	if ((check_col_edge == net->row) ||
	    ((check_col_edge < net->row) &&
	     (channel->vert_layer[check_col_edge-1][check_col] == name)))
	    return (insert_path ((PATHPTR) 0, HORIZ, HORIZ, check_col, column,
				 new_row));
    }

    /* try moving right */
    for (check_col = column + 1; check_col <= right_boundary; check_col++)
    {
	/* if we happen to cross 'net' we should connect there */
	if (channel->vert_layer[new_row][check_col] == name)
	    return (insert_path ((PATHPTR) 0, HORIZ, HORIZ, check_col, column,
				 new_row));

	/* see if this column can be used */
	check_col_edge = search_column (channel->vert_layer, UP,
				check_col, new_row, net->row);
	if ((check_col_edge == net->row) ||
	    ((check_col_edge < net->row) &&
	     (channel->vert_layer[check_col_edge-1][check_col] == name)))
	    return (insert_path ((PATHPTR) 0, HORIZ, HORIZ, check_col, column,
				 new_row));
    }

    /* if we have not returned by now, there is no route */
    return (NULL);
}
