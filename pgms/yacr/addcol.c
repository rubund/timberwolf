#include "copyright.h"
#include "yacr.h"

void add_columns (channel, top, bottom, net_array, num_nets, num_rows,
		num_cols)
INOUT CHANNELPTR channel;	/* the channel data structure */
INOUT NETPTR *(top[]);		/* array of nets on top edge of channel */
INOUT NETPTR *(bottom[]);	/* array of nets on bottom edge of channel */
IN NETPTR net_array;		/* array containing all the nets routed */
IN int num_nets;		/* size of net_array */
INOUT int *num_rows;		/* number of rows in the channel */
INOUT int *num_cols;		/* number of columns in the channel */
{
    int i, j;			/* loop counters */
    int num_new_cols;		/* number of columns that will be added to
				   the channel to complete the route */
    INT_LIST temp_int;		/* used to traverse the Vcv_cols list */
    INT_LIST rest_of_list;	/* Vcv_cols except the one being routed */
    INT_LIST route_col;		/* the column that is being routed */
    int added_rows;		/* number of rows that have been added at the
				   top edge of the channel */
    PATHPTR path;		/* list of rectangles used for a route */
    int routing_col;		/* column to use when routing a net */
    NETPTR *newtop;		/* used to allocate larger space for new
				   empty columns */
    NETPTR *newbottom;		/* used to allocate larger space for new
				   empty columns */
    int *new_top_offset,
	*new_bottom_offset;     /* same for offset lists. */

    if (max_top_offset != 0 || max_bottom_offset != 0)
    {
        (void) fprintf(output_file,"Add_cols can't handle irregular channels\n");
        exit(1);
    }

    added_rows = 0;

    /*
     *  set num_new_cols equal to the number of Vcv_cols.
     */

    num_new_cols = 0;
    for (temp_int = Vcv_cols; temp_int != NULL; temp_int = temp_int->next)
	num_new_cols++;

    if (ioform == HUMAN)
	(void) fprintf (output_file,
		"There will be %d columns added to the right edge.\n",
		num_new_cols);

    /*
     *  enlarge the channel
     */

    routing_col = *num_cols + 1;
    append_columns (channel, *num_rows, *num_cols, 0, num_new_cols);

    /* change top[] and bottom[] to reflect the new reality */
    newtop = ALLOC(NETPTR, *num_cols + 1 + 0 + num_new_cols);
    newbottom = ALLOC(NETPTR, *num_cols + 1 + 0 + num_new_cols);
    new_top_offset = ALLOC(int, *num_cols + 1 + 0 + num_new_cols);
    new_bottom_offset = ALLOC(int, *num_cols + 1 + 0 + num_new_cols);

    for (i = 0; i <= 0/*num new left cols */; i++)
    {
	newbottom[i] = newtop[i] = net_array + 0;
	new_top_offset[i] = new_bottom_offset[i] = 0;
    }
    for (j = 1; j <= *num_cols; j++, i++)
    {
	newtop[i] = (*top)[j];
	newbottom[i] = (*bottom)[j];
	new_top_offset[i] = top_offset[j];
	new_bottom_offset[i] = bottom_offset[j];
    }
    for (j = 1; j <= num_new_cols/*num new right cols */+1; j++, i++)
    {
	newbottom[i] = newtop[i] = net_array + 0;
	new_top_offset[i] = new_bottom_offset[i] = 0;
    }
    *top = newtop;
    *bottom = newbottom;
    *num_cols += 0 + num_new_cols;
    top_offset = new_top_offset;
    bottom_offset = new_bottom_offset;
    /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
    /* !!!change column number for pins on all nets!!! */
    /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

    if (debug == YES)
	print_channel (channel, *num_rows, *num_cols, num_nets);

    /*
     *  do the routing
     */

    while (Vcv_cols != NULL)
    {
	route_col = Vcv_cols;
	rest_of_list = NULL;
	for (temp_int = Vcv_cols->next; temp_int != NULL;
					temp_int = temp_int->next)
	{
	    if ((*top)[temp_int->value]->row > (*top)[route_col->value]->row)
	    {
		rest_of_list = insert_int (rest_of_list, route_col->value);
		route_col = temp_int;
	    }
	    else
		rest_of_list = insert_int (rest_of_list, temp_int->value);
	}
	Vcv_cols = rest_of_list;

	/* route the bottom net */
	path = insert_path ((PATHPTR) 0, VERT, VERT, *num_rows,
			(*bottom)[route_col->value]->row+added_rows,
			route_col->value);
	draw_rect (channel, (*bottom)[route_col->value]->name, path);
	/* add rows and route top net */
	enlarge_channel (channel, *num_rows, *num_cols, 1,
			*top, *bottom, net_array, num_nets);
	*num_rows += 1;
	enlarge_channel (channel, *num_rows, *num_cols,
			(*top)[route_col->value]->row, *top, *bottom,
			net_array, num_nets);
	*num_rows += 1;
	path = insert_path ((PATHPTR) 0, VERT, VERT, 1,
			(*top)[route_col->value]->row-1, routing_col);
	path = insert_path (path, VERT, VERT, 1, 1, route_col->value);
	path = insert_path (path, HORIZ, HORIZ, route_col->value,
			routing_col, 1);
	path = insert_path (path, HORIZ, HORIZ, route_col->value,
			routing_col, (*top)[route_col->value]->row-1);
	draw_rect (channel, (*top)[route_col->value]->name, path);
	routing_col++;
    }
}


void append_columns (channel, num_rows, num_cols, new_left_cols,
		new_right_cols)
INOUT CHANNELPTR channel;	/* the channel data structure */
IN int num_rows;		/* number of rows in the channel */
IN int num_cols;		/* number of columns in the old channel */
IN int new_left_cols;		/* number of columns added to the left edge
				   of the channel */
IN int new_right_cols;		/* number of columns added to the right edge
				   of the channel */
{
    int i, j, k;		/* loop counters */
    int *new_vert_row;		/* used to allocate space */
    int *new_horiz_row;		/* used to allocate space */

    for (i = 0; i <= num_rows+1; i++)
    {
	new_vert_row = ALLOC(int, num_cols+new_left_cols + new_right_cols + 2);
	new_horiz_row = ALLOC(int, num_cols+new_left_cols + new_right_cols + 2);

	for (j = 0; j < new_left_cols; j++)
	{
	    new_vert_row[j] = 0;
	    new_horiz_row[j] = channel->horiz_layer[i][0];
	}
	for (k = 0; k <= num_cols + 1; k++, j++)
	{
	    new_vert_row[j] = channel->vert_layer[i][k];
	    new_horiz_row[j] = channel->horiz_layer[i][k];
	}
	for (k = 0; k < new_right_cols; k++, j++)
	{
	    new_vert_row[j] = 0;
	    new_horiz_row[j] = channel->horiz_layer[i][num_cols+1];
	}

	channel->vert_layer[i] = new_vert_row;
	channel->horiz_layer[i] = new_horiz_row;
    }

    /* make sure entire row below bottom is full of "-1" */
    for (i = 0; i <= new_left_cols+num_cols+1+new_right_cols; i++)
    {
	channel->vert_layer[num_rows+1][i] = -1;
	channel->horiz_layer[num_rows+1][i] = -1;
    }
}
