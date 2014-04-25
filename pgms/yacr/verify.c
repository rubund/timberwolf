#include "copyright.h"
#include "yacr.h"

CHANNELPTR channel;
int num_rows;
int num_cols;
int total_length;
int vias;
int this_vert;
int this_horiz;
int name;
NETPTR net_array;

static int verify_error;

/**********************************************************************
 *  8/26/85: D. Braun removed bug that allowed metal to constitute
 *           a connection to a top or bottom pin.
 *********************************************************************/

verify (chan, rows, cols, n_array, num_nets)
IN CHANNELPTR chan;		/* the channel data structure */
IN int rows;			/* number of rows in the channel */
IN int cols;			/* number of columns in the channel */
IN NETPTR n_array;		/* array of all the net data structures */
IN int num_nets;		/* size of net_array */
{
    int i;			/* loop counter */
    int long_net;		/* index to the net using most poly and metal
				   */
    int most_vert;		/* amount of vertical material in long_net */
    int most_horiz;		/* amount of horizontal material in long_net
				   */
    int long_length;		/* length of route for long_net, most_vert +
				   most_horiz */

    channel = chan;
    num_rows = rows;
    num_cols = cols;
    net_array = n_array;

    verify_error = NO;
    long_net = 0;
    most_vert = most_horiz = long_length = 0;
    total_length = vias = 0;
    for (i = 1; i <= num_nets; i++)
    {
	if (net_array[i].leftmost != NULL) {
	    verify_net (net_array + i);
	    if (this_horiz + this_vert > long_length)
	    {
		most_horiz = this_horiz;
		most_vert = this_vert;
		long_length = most_horiz + most_vert;
		long_net = i;
	    }
	}
    }

    if (ioform == HUMAN)
    {
	(void) fprintf (output_file, "\nThere are %d vias\n", vias);
	(void) fprintf (output_file, "The total net_length is %d\n", total_length);
	(void) fprintf (output_file,
	    "The longest net is %d, metal length = %d, poly length = %d\n\n",
	    number_to_name(long_net), most_horiz, most_vert);
    }
    else
	(void) fprintf (output_file, "%d %d %d\n",
		number_to_name(long_net), most_horiz, most_vert);

    return(verify_error);
}



void verify_net (net)
IN NETPTR net;			/* the net to be verified */
{
    this_vert = this_horiz = 0;
    name = net->name;

    if (net == NULL || net->leftmost == NULL)
	return;

    /* start traversing the net at the leftmost pin */
    switch (net->leftmost->edge)
    {
	case LEFT:
	    if (channel->horiz_layer[net->row][0] == net->name)
		horiz_traverse_net (net->row, 0);
	    else if (channel->horiz_layer[net->row+1][0] == net->name)
		horiz_traverse_net (net->row+1, 0);
	    break;
	case TOP:
	    if (channel->vert_layer[1][net->leftmost->col] == net->name)
		vert_traverse_net (1, net->leftmost->col);
	    break;
	case BOTTOM:
	    if(channel->vert_layer[num_rows][net->leftmost->col] == net->name)
		vert_traverse_net (num_rows, net->leftmost->col);
	    break;
    }

    if (net->rightmost != NULL)
    {
	FILE *fp = (ioform == HUMAN) ? output_file : stderr;
	verify_error = YES;
	(void) fprintf (fp, "net %d is not properly routed\n",
				number_to_name(net->name));
	(void) fprintf (fp, "\tbad pins are: ");
	while (net->leftmost != NULL)
	{
	    (void) fprintf(fp, " %d/%d", net->leftmost->col,net->leftmost->edge);
	    net->leftmost = net->leftmost->right_list;
	}
	(void) fprintf (fp, "\n");
    }

}


/******************************************************************
 *
 *  because of the order of the recursion, this only counts one of
 *  two adjacent contacts for the same net. If both contacts are to
 *  be counted, do the if (...SWITCH) recursion immediately before
 *  the other recursive calls and not after
 *
 ******************************************************************/

void vert_traverse_net (row, column)
IN int row;			/* row coordinate of place we are checking */
IN int column;			/* column coordinate of place we are checking
				   */
{
    channel->vert_layer[row][column] = 0;
    this_vert++;
    total_length++;

    /*
     *  see if we may be at a pin
     */
    if ((row == 1) || (row == num_rows) || (column == 0) ||
					(column == num_cols + 1))
	check_pin (net_array + name, row, column);

    /*
     *  search from here in all directions that make sense
     */
    if ((row != 1) && (channel->vert_layer[row-1][column] == name))
	vert_traverse_net (row - 1, column);
    if ((row != num_rows) && (channel->vert_layer[row+1][column] == name))
	vert_traverse_net (row + 1, column);
    if ((column != 0) && (channel->vert_layer[row][column-1] == name))
	vert_traverse_net (row, column - 1);
    if ((column != num_cols+1) &&(channel->vert_layer[row][column+1] == name))
	vert_traverse_net (row, column + 1);
    if (channel->horiz_layer[row][column] == name)
    {
	vias++;
	horiz_traverse_net (row, column);
    }
}


/******************************************************************
 *
 *  because of the order of the recursion, this only counts one of
 *  two adjacent contacts for the same net. If both contacts are to
 *  be counted, do the if (...SWITCH) recursion immediately before
 *  the other recursive calls and not after
 *
 ******************************************************************/

void horiz_traverse_net (row, column)
IN int row;			/* row coordinate of place we are checking */
IN int column;			/* column coordinate of place we are checking
				   */
{
    channel->horiz_layer[row][column] = 0;
    this_horiz++;
    total_length++;

    /*
     *  see if we may be at a pin
     */
    if ((column == 0) || (column == num_cols + 1))
	check_pin (net_array + name, row, column);

    /*
     *  search from here in all directions that make sense
     */
    if ((row != 1) && (channel->horiz_layer[row-1][column] == name))
	horiz_traverse_net (row - 1, column);
    if ((row != num_rows) && (channel->horiz_layer[row+1][column] == name))
	horiz_traverse_net (row + 1, column);
    if ((column != 0) && (channel->horiz_layer[row][column-1] == name))
	horiz_traverse_net (row, column - 1);
    if ((column != num_cols+1)&&(channel->horiz_layer[row][column+1] == name))
	horiz_traverse_net (row, column + 1);
    if (channel->vert_layer[row][column] == name)
    {
	vias++;
	vert_traverse_net (row, column);
    }
}


void check_pin (net, row, column)
INOUT NETPTR net;		/* the net which may have a pin here */
IN int row;			/* the row this alleged pin may be in */
IN int column;			/* the column it may be in */
{
    PIN_LIST trav;		/* used to traverse the pin list of the net */

    for (trav = net->leftmost; (trav != NULL) && (trav->col <= column); trav = trav->right_list)
	if (column == trav->col)
	    switch (trav->edge) {
	    case TOP:
		if (row == 1)
		    delete_pin (trav, net);
		break;
	    case BOTTOM:
		if (row == num_rows)
		  delete_pin (trav, net);
		break;
	    case LEFT:
		if (column == 0)
		  delete_pin (trav, net);
		break;
	    case RIGHT:
		if (column == num_cols + 1)
		    delete_pin (trav, net);
		break;
	      }
}


void delete_pin (pin, net)
IN PIN_LIST_ELEMENT *pin;	/* the pin to be deleted from net s list */
INOUT NETPTR net;		/* the net losing a pin */
{
    if (pin->left_list == NULL)
        net->leftmost = pin->right_list;
    else
	pin->left_list->right_list = pin->right_list;
    if (pin->right_list == NULL)
	net->rightmost = pin->left_list;
    else
	pin->right_list->left_list = pin->left_list;
}

