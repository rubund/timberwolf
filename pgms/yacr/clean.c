#include "copyright.h"
#include "yacr.h"

/*******************************************************************
 *
 *  clean_channel goes through the channel and removes most of the
 *  strange looking things.  "Dangling" pieces of horiz_layer material
 *  are removed.  These dangling pieces sometimes occur because the
 *  maze routing for the leftmost (or rightmost) connects to the net's
 *  row at a different column.  If a net only occupies
 *  two adjacent locations on the horizontal layer they are both removed.
 *
 *  Author: Jim Reed
 *
 *  Date: 5-12-84
 * Modified 3-26-85 D. Braun to handle irregular channels.
 *
 ********************************************************************/

clean_channel (channel, num_rows, num_cols)
INOUT CHANNELPTR channel;	/* the channel data structure */
IN int num_rows;		/* number of rows in the channel */
IN int num_cols;		/* number of columns in the channel */
{
    register int i, j;		/* loop counters */
    register int current_net;	/* the net being checked for dangling
				   rectangles */
    int removing;		/* flag, YES if we are removing a dangling
				   rectangle */


    /*
     *  remove dangling horizontal rectangles
     */

    for (i = 1; i <= num_rows; i++)
    {
	current_net = channel->horiz_layer[i][0];
	removing = NO;
	for (j = 1; j <= num_cols; j++)
	    if (channel->horiz_layer[i][j] != current_net)
	    {
		current_net = channel->horiz_layer[i][j];
		if ((channel->vert_layer[i][j] == current_net) ||
		    (channel->horiz_layer[i+1][j] == current_net) ||
		    (channel->horiz_layer[i-1][j] == current_net))
		{
		    removing = NO;
		}
		else
		{
		    removing = YES;
		    channel->horiz_layer[i][j] = 0;
		}
	    }
	    else if (removing == YES)
	    {
		if ((channel->vert_layer[i][j] == current_net) ||
		    (channel->horiz_layer[i+1][j] == current_net) ||
		    (channel->horiz_layer[i-1][j] == current_net))
		    removing = NO;
		else
		    channel->horiz_layer[i][j] = 0;
	    }
	current_net = channel->horiz_layer[i][num_cols+1];
	removing = NO;
	for (j = num_cols; j >= 1; j--)
	    if (channel->horiz_layer[i][j] != current_net)
	    {
		current_net = channel->horiz_layer[i][j];
		if ((channel->vert_layer[i][j] == current_net) ||
		    (channel->horiz_layer[i+1][j] == current_net) ||
		    (channel->horiz_layer[i-1][j] == current_net))
		{
		    removing = NO;
		}
		else
		{
		    removing = YES;
		    channel->horiz_layer[i][j] = 0;
		}
	    }
	    else if (removing == YES)
	    {
		if ((channel->vert_layer[i][j] == current_net) ||
		    (channel->horiz_layer[i+1][j] == current_net) ||
		    (channel->horiz_layer[i-1][j] == current_net))
		    removing = NO;
		else
		    channel->horiz_layer[i][j] = 0;
	    }
    }

    /*
     *  remove from horizontal layer all nets that occupy only
     *  two spaces
     */

    for (i = 1; i <= num_rows; i++)
	for (j = 1; j < num_cols; j++)
	    if ((channel->horiz_layer[i][j-1] != channel->horiz_layer[i][j])&&
		(channel->horiz_layer[i][j] == channel->horiz_layer[i][j+1])&&
		(channel->horiz_layer[i][j] != channel->horiz_layer[i][j+2]))
		if ((channel->horiz_layer[i][j] !=
					channel->horiz_layer[i+1][j]) &&
		    (channel->horiz_layer[i][j] !=
					channel->horiz_layer[i-1][j]) &&
		    (channel->horiz_layer[i][j] !=
					channel->horiz_layer[i+1][j+1]) &&
		    (channel->horiz_layer[i][j] !=
					channel->horiz_layer[i-1][j+1]) &&
		    (channel->horiz_layer[i][j] > 0))
		{
		    /* remove this piece */
		    channel->horiz_layer[i][j] = 0;
		    channel->horiz_layer[i][j+1] = 0;
		}

}


remove_parallel (channel, num_rows, num_cols, top_offset, bottom_offset)
INOUT CHANNELPTR channel;	/* the channel data structure */
IN int num_rows;		/* number of rows in the channel */
IN int num_cols;		/* number of columns in the channel */
int top_offset[];
int bottom_offset[];
{
    int i, j;			/* loop counters */
    int row1, row2;		/* extent of each of the parallel columns */
    int first_row,
	last_row;               /* The first and last rows of interest
				   that are not interrupted by
				   indentations. */
					

    /*
     *  make parallel vertical lines a single line
     */


    for (i = 1; i < num_cols; i++)
    {

	first_row = MAX(top_offset[i],top_offset[i+1]) + 1;
	last_row = num_rows - MAX(bottom_offset[i],bottom_offset[i+1]); 

	/* are there parallel lines starting from the top edge? */
	if ((channel->vert_layer[first_row][i] == channel->vert_layer[first_row][i+1]) &&
		(channel->vert_layer[first_row][i] > 0))
	{
	    /* find out how far the lines extend into the channel */
	    for (j = first_row+1; (j <= last_row) &&
		   (channel->vert_layer[j][i] == channel->vert_layer[first_row][i]);
		   j++);
	    row1 = j - 1;
	    for (j = first_row+1; (j <= last_row) &&
		   (channel->vert_layer[j][i+1] == channel->vert_layer[first_row][i]);
		   j++);
	    row2 = j - 1;

	    if (row1 == row2)
		/* the lines are the same length */
		/* special case: if both lines extend across the entire
		   channel, delete the interior portion of one, leave
		   the edges to connect to pins */
		if (row1 == last_row)
		    vert_line_erase (channel, i, first_row+1, last_row - 1);
		else if (channel->horiz_layer[row1][i-1] !=
					channel->vert_layer[row1][i])
		{
		    /* delete the leftmost line */
		    vert_line_erase (channel, i, first_row+1, row1);
		    /* special case, if these are the only two pins,
		     * remove the metal part and shorten the right pin also */
		    if (channel->horiz_layer[row1][i+2] !=
					channel->vert_layer[row1][i+1])
		    {
			/* delete rightmost line and metal */
			vert_line_erase (channel, i+1, first_row+1, row1);
			channel->horiz_layer[row1][i] =
				channel->horiz_layer[row1][i+1] = 0;
		    }
		}
		else
		    /* delete the rightmost line */
		    vert_line_erase (channel, i + 1, first_row+1, row1);
	    else
		/* the lines are different lengths, remove the shorter */
		if (row1 < row2)
		    vert_line_erase (channel, i, first_row+1, row1);
		else
		    vert_line_erase (channel, i + 1, first_row+1, row2);
	}

	/* are there parallel lines starting from the bottom edge? */
	if ((channel->vert_layer[last_row][i] ==
				channel->vert_layer[last_row][i+1]) &&
		(channel->vert_layer[last_row][i] > 0))
	{
	    /* find out how far the lines extend into the channel */
	    for (j = last_row - 1; (j >= first_row) &&
		   (channel->vert_layer[j][i] ==
					channel->vert_layer[last_row][i]);
		   j--);
	    row1 = j + 1;
	    for (j = last_row - 1; (j >= first_row) &&
		   (channel->vert_layer[j][i+1] ==
					channel->vert_layer[last_row][i]);
		   j--);
	    row2 = j + 1;

	    if (row1 == row2)
	    {
		/* the lines are the same length */
		if (row1 == first_row)
		    ; /* Don't do anything! 
			 This means that the channel width is 2,
			 and we have found two lines that extend
			 all the way across the channel that were
			 not removed when the top row was checked. */

		else if (channel->horiz_layer[row1][i-1] != 
				channel->vert_layer[row1][i])
		{
		    /* delete the leftmost line */
		    vert_line_erase (channel, i, row1, last_row - 1);
		    /* special case, if these are the only two pins,
		     * remove the metal part and shorten the right pin also */
		    if (channel->horiz_layer[row1][i+2] !=
					channel->vert_layer[row1][i+1])
		    {
			/* delete rightmost line and metal */
			vert_line_erase (channel, i+1, row1, last_row - 1);
			channel->horiz_layer[row1][i] =
				channel->horiz_layer[row1][i+1] = 0;
		    }
		}
		else
		    /* delete the rightmost line */
		    vert_line_erase (channel, i + 1, row1, last_row - 1);
	    }
	    else
		/* the lines are different lengths, remove the shorter */
		if (row1 > row2)
		    vert_line_erase (channel, i, row1, last_row - 1);
		else
		    vert_line_erase (channel, i + 1, row2, last_row - 1);
	}
    }
}


void vert_line_erase (channel, column, top_row, bottom_row)
INOUT CHANNELPTR channel;	/* the channel data structure */
IN int column;			/* the column which is to be modified */
IN int top_row;			/* the top (lowest numbered) part of the
				   column to be deleted */
IN int bottom_row;		/* the bottom (highest numbered) part of the
				   column to be deleted */
{
    while (top_row <= bottom_row)
	channel->vert_layer[top_row++][column] = 0;
}

/*******************************
 *
 * Modified by D. Braun 3-28-85 for irregular channels.
 * Does not try to work within the boundary area.
 * Bug fixed 8/26/85 that messed up when there was the same
 * net at the top and bottom of the column, and the horiz.
 * segment was in the first or last row.
 *******************************/

void max_metal (channel, num_rows, num_cols, top_list, bottom_list,
			top_offset, bottom_offset)
INOUT CHANNELPTR channel;	/* the channel data structure */
IN int num_rows;		/* number of rows in the channel */
IN int num_cols;		/* number of columns in the channel */
IN NETPTR *top_list;		/* list of nets connecting to top edge of
				   channel */
IN NETPTR *bottom_list;		/* list of nets connecting to bottom edge of
				   channel */
IN int *top_offset,
       *bottom_offset;		/* Border offset lists */
{
    int i, j;			/* loop counters */
    int this_net;		/* the net for the pin currently being worked
				   on */

    for (j = 1; j <= num_cols; j++)
    {
	/* try to maximize metal to top pin */
	if ((this_net = channel->vert_layer[1][j]) > 0)
	{
	    i = 1;
	    while ((i++ < num_rows) &&
		   (channel->vert_layer[i][j] == this_net) &&
		   (channel->horiz_layer[i][j] != this_net));
	    if ((channel->vert_layer[i][j] == this_net) &&
		   (channel->horiz_layer[i][j] == this_net))
	    {  /*
		*  this_row is in metal in row i
		*  change as much of the poly to metal as possible
		*/
		/* make sure a pin on opposite edge can still be connected */
		if ((bottom_list[j]->name == this_net || 
		        channel->vert_layer[i+1][j] == this_net) &&
		    (channel->horiz_layer[i-1][j] == 0))
		{
		    i--;
		    channel->horiz_layer[i][j] = this_net;
		}
		while ((i > top_offset[j]+1) &&
			((channel->horiz_layer[i-1][j] == 0) ||
			 (channel->horiz_layer[i-1][j] == this_net)) )
		{
		    channel->vert_layer[i--][j] = 0;
		    channel->horiz_layer[i][j] = this_net;
		}
		if ((i == top_offset[j]+1) && (top_list[j]->name != this_net)
					   && (top_list[j]->name != 0))
		    channel->vert_layer[i][j] = 0;
	    }
	}
	/* try to maximize metal to bottom pin */
	if ((this_net = channel->vert_layer[num_rows-bottom_offset[j]][j]) > 0)
	{
	    i = num_rows-bottom_offset[j];
	    while ((i-- > 1) &&
		   (channel->vert_layer[i][j] == this_net) &&
		   (channel->horiz_layer[i][j] != this_net));
	    if ((channel->vert_layer[i][j] == this_net) &&
		   (channel->horiz_layer[i][j] == this_net))
	    {  /*
		*  this_row is in metal in row i
		*  change as much of the poly to metal as possible
		*/
		/* make sure a pin on opposite edge can still be connected */
		if ((top_list[j]->name == this_net ||
		        channel->vert_layer[i-1][j] == this_net) &&
		    (channel->horiz_layer[i+1][j] == 0 ||
		     channel->horiz_layer[i+1][j] == this_net))
		{
		    i++;
		    channel->horiz_layer[i][j] = this_net;
		}
		while ((i < num_rows-bottom_offset[j]) &&
			((channel->horiz_layer[i+1][j] == 0) ||
			 (channel->horiz_layer[i+1][j] == this_net)) )
		{
		    channel->vert_layer[i++][j] = 0;
		    channel->horiz_layer[i][j] = this_net;
		}
		if ((i == num_rows-bottom_offset[j]) && (bottom_list[j]->name != this_net)
		   			&& (bottom_list[j]->name != 0))
		    channel->vert_layer[i][j] = 0;
	    }
	}
    }
}

