#include "copyright.h"
#include "yacr.h"

/* This contains routines which are particular
to the irregular channel version of Yacr.
3/25/85  Doug Braun
*/


/*********************************************
 * Scale_offset adjusts the values of an offset list
 * so that they range from zero upwards. 
 * It also sets the values of offset[0] and offset[num_cols+1]
 * to the value of the next inner offset.
 *********************************************/


scale_offset(list,size)
int *list;
int size;
{
    int smallest;
    int j;

    smallest = list[1];
    for (j=1;j<=size;j++)
    {
	if (list[j] < smallest)
	    smallest = list[j];
    }
    for (j=1;j<=size;j++)
    {
	list[j] -= smallest;
    }

    list[0] = list[1];
    list[size+1] = list[size];
}



/*********************************************
 * This creates a zero_filled offset list and
 * returns a pointer to it.  It is called if
 * a top or bottom offset list was not spacified
 *********************************************/


int *create_offset(num_cols,val)
int num_cols;
int val;
{
    int *list;
    int j;

    list = ALLOC(int, num_cols + 2);

    for (j=0; j <= num_cols; j++)
	list[j] = val;
    
    return(list);
}



/* Indent_channel places -1's in the channel array in
all the places where there are indentations into
the channel.  Note that the irregularities are pushed into
the channel rather than pushed out.  This means that if
the channel was originally as high as density, it may
have to be widened for routing to succeed.
If the border regions overlap, FALSE is returned */

indent_channel(channel, num_rows, num_cols, top_offset, bottom_offset)

CHANNELPTR channel;
int num_rows,
    num_cols;
int *top_offset,
    *bottom_offset;

{
    int j,k;
    int max;  /* The maximum offset for the top or bottom */
    int overlap;  /* Whether there is an overlap of the borders. */

    /* First do the top of the channel */

    overlap = FALSE;
    max = max_offset(top_offset, num_cols);

    for (j=1; j <= max; j++)
    {
	for (k=1; k <= num_cols; k++)
	{
	    if (j <= top_offset[k])
	    {
		if ((channel->horiz_layer[j][k] != 0) ||
		    (channel->vert_layer[j][k] != 0))
		{
		   overlap = TRUE;
		}

		channel->horiz_layer[j][k] = BORDER;
		channel->vert_layer[j][k] = BORDER;
	    }
	}
    }


    /* Now do the bottom */

    max = max_offset(bottom_offset, num_cols);

    for (j=num_rows; j >= num_rows-max+1; j--)
    {
	for (k=1; k <= num_cols; k++)
	{
	    if (num_rows-j < bottom_offset[k])
	    {
		if ((channel->horiz_layer[j][k] != 0) ||
		    (channel->vert_layer[j][k] != 0))
		{
		overlap = TRUE;
		}

		channel->horiz_layer[j][k] = BORDER;
		channel->vert_layer[j][k] = BORDER;
	    }
	}
    }

    return(overlap);
}

/******************************************************************/


update_indent_channel(channel, num_rows, num_cols, top_offset, bottom_offset)

CHANNELPTR channel;
int num_rows,
    num_cols;
int *top_offset,
    *bottom_offset;

{
    int j,k;
    int max;  /* The maximum offset for the top or bottom */

    /* First do the top of the channel */

    max = max_offset(top_offset, num_cols);

    for (j=1; j <= max; j++)
    {
	for (k=1; k <= num_cols; k++)
	{
	    if ((j <= top_offset[k]) &&	
		((channel->horiz_layer[j][k] == -1) || (channel->horiz_layer[j][k] == BORDER)) &&
		((channel->vert_layer[j][k] == -1) || (channel->vert_layer[j][k] == BORDER)))
	    {
		channel->horiz_layer[j][k] = BORDER;
		channel->vert_layer[j][k] = BORDER;
	    }
	}
    }


    /* Now do the bottom */

    max = max_offset(bottom_offset, num_cols);

    for (j=num_rows; j >= num_rows-max+1; j--)
    {
	for (k=1; k <= num_cols; k++)
	{
	    if ((num_rows-j < bottom_offset[k]) && 
		((channel->horiz_layer[j][k] == -1) || (channel->horiz_layer[j][k] == BORDER)) &&
		((channel->vert_layer[j][k] == -1) || (channel->vert_layer[j][k] == BORDER)))
	    {
		channel->horiz_layer[j][k] = BORDER;
		channel->vert_layer[j][k] = BORDER;
	    }
	}
    }
}



/* Max offset returns the highest value on an offset list */

int max_offset(list,size)
int *list;
int size;
{
    int j;
    int max;

    max = list[1];
    for (j=1;j<=size; j++)
    {
	if (list[j] > max)
	    max = list[j];
    }

    return(max);
}



/***********************************
 *
 * This is called from net_cost. It sets the cost
 * to INFINITY for each row where the net would
 * hit an irregular boundary.  Same parameters
 * as net_cost.
 *
 * D. Braun   3-26-85
 *
 * Modified for early end condition. H. Sheng 6/9/88
 *
 ************************************/

void set_border_cost (cost, channel, net, num_rows)
INOUT int **cost;		/* the cost matrix */
IN CHANNELPTR channel;		/* the channel */
IN NETPTR net;			/* net to be put in the cost matrix */
IN int num_rows;		/* number of rows in the channel */
{
    int row;	/* The row we are looking at */
    int col;    /* The column */

    for (row=1; row <= num_rows; row++)
    {
	/* Don't waste time on rows that have no indentations. */

	if (row > max_top_offset && row <= num_rows-max_bottom_offset)
	    continue;

	for (col=net->leftmost->col; (col<= net->rightmost->col) && (cost[row][net->name]!=INFINITY); col++)
	{
	    if (channel->vert_layer[row][col] == BORDER)
		cost[row][net->name] = INFINITY;
	}
    }
}


/***********************************
 *
 * This is called from net_cost. It adjusts
 * of a net so it will be placed in an indentation
 * if possible.  Same parameters
 * as net_cost.
 *
 * NOT IMPLEMENTED YET!!!
 *
 * D. Braun   3-26-85
 *
 ************************************/

void set_irreg_cost (cost, num_rows)
INOUT int **cost;		/* the cost matrix */
IN int num_rows;		/* number of rows in the channel */
{
  int i,j,k;
  int found, place;

  for (i=1; i<=num_nets; i++)
    {
      if (net_array[i].leftmost == NULL)
	continue;

      found = FALSE;
      for (j = 1; !found && j<=max_top_offset; j++)
	{
	  place = TRUE;
	  for (k=net_array[i].leftmost->col; 
	       k<=net_array[i].rightmost->col; k++)
	    if ((cost[j][net_array[i].name]>= INFINITY) || 
		(top_offset[k]>=j))
	      place = FALSE;
	  if (place)
	    /* can be placed */
	    cost[j][net_array[i].name] += (-num_rows)
	      -ALPHA*(max_top_offset - j);
	}

      for (j = num_rows; j>=num_rows - max_bottom_offset; j--)
	/* trying to place in a lower indentation */
	{
	  place = TRUE;
	  for (k=net_array[i].leftmost->col; 
	       k<=net_array[i].rightmost->col; k++)
	    if ((cost[j][net_array[i].name]>=INFINITY) || 
		(bottom_offset[k]>=j))
	      place = FALSE;
	  if (place)
	    /* can be placed */
	    cost[j][net_array[i].name] += (-num_rows)
	      - ALPHA*(max_bottom_offset - (num_rows - j));
	}


    }

}




/*************************************************
 *
 * After the nets have been placed the border area of the channel
 * will contain the vertical segments, which must be clipped off.
 * This checks to make sure that the border region of each column
 * contains only material belonging to the net at that column,
 * or that the border region is empty if there is no net for it.
 * Also the border region of the horizontal layer must be empty.
 * Any violation represents a fatal error.
 *
 * 3-26-85 D. Braun
 *
 **********************************************/

void check_border(channel, num_rows, num_cols, top, bottom,
			top_offset, bottom_offset) 
CHANNELPTR channel;
int num_rows,
    num_cols;
NETPTR top[],	/* Top and bottom lists of nets */
       bottom[];
int *top_offset,
    *bottom_offset;
{
    int row, col;       /* Indices for the channel */

    /* First check the top border */

    for (col=1; col <= num_cols; col++)
    {
	for (row=1; row <= top_offset[col]; row++)
	{
	    if (top[col]->name != 0 &&
	        top[col]->name != channel->vert_layer[row][col])
	    {
		(void) fprintf(output_file,"Row %d Column %d has border problem 1!\n",
					row,col);
	    }
	    if (top[col]->name == 0 &&
		channel->vert_layer[row][col] != BORDER)
	    {
		(void) fprintf(output_file,"Row %d Column %d has border problem 2!\n",
					row,col);
	    }
	    if (channel->horiz_layer[row][col] != BORDER)
	    {
		(void) fprintf(output_file,"Row %d Column %d has border problem 3!\n",
					row,col);
	    }
	}
    }


   /* Now do the bottom */

    for (col=1; col <= num_cols; col++)
    {
	for (row=num_rows; row >= num_rows - bottom_offset[col] + 1; row--)
	{
	    if (bottom[col]->name != 0 &&
	        bottom[col]->name != channel->vert_layer[row][col])
	    {
		(void) fprintf(output_file,"Row %d Column %d has border problem 4!\n",
					row,col);
	    }
	    if (bottom[col]->name == 0 &&
		channel->vert_layer[row][col] != BORDER)
	    {
		(void) fprintf(output_file,"Row %d Column %d has border problem 5!\n",
					row,col);
	    }
	    if (channel->horiz_layer[row][col] != BORDER)
	    {
		(void) fprintf(output_file,"Row %d Column %d has border problem 6!\n",
					row,col);
	    }
	}
    }
}


/*********************************
 *
 * Unclip_border restores the vertical segments
 * to the border regions.  This is so verify
 * can be called to check the connectivity.
 * Verify cannot be used before the borders
 * are trimmed and the results are output because
 * it destroys the contents of the channel
 *
 */

void unclip_border(channel, num_rows, num_cols, top, bottom,
			top_offset, bottom_offset) 
CHANNELPTR channel;
int num_rows,
    num_cols;
NETPTR top[],	/* Top and bottom lists of nets */
       bottom[];
int *top_offset,
    *bottom_offset;
{
    int row, col;       /* Indices for the channel */

    /* First check the top border */

    for (col=1; col <= num_cols; col++)
    {
	for (row=1; row <= top_offset[col]; row++)
	{
	    if (top[col]->name != 0)
	        channel->vert_layer[row][col] = top[col]->name;
	}
    }


   /* Now do the bottom */

    for (col=1; col <= num_cols; col++)
    {
	for (row=num_rows; row >= num_rows - bottom_offset[col] + 1; row--)
	{
	    if (bottom[col]->name != 0)
	        channel->vert_layer[row][col] = bottom[col]->name;
	}
    }
}



/* This returns TRUE if any of the offsets are non-zero */

int are_indents()
{
    int j;

    for (j=1; j <= num_cols; j++)
    {
	if (top_offset[j] != 0)
	    return(TRUE);
    }

    for (j=1; j <= num_cols; j++)
    {
	if (bottom_offset[j] != 0)
	    return(TRUE);
    }

    return (FALSE);
}



/* This checks to see if the placement was optimal.
This is true if there is a column where every row
in the horizontal layer
contains either a net or a part of an indentation.
If this is true, there is no way the channel width
could be reduced. With irregular edges, the channel
might not be optimal, because doglegs could allow
the channel width to be reduced. */

void check_indented_placement()
{
    int row,
	col;
    int space;  /* flag */

    for (col=1; col <= num_cols; col++)
    {
	space = NO;
	for (row=1; row <= num_rows; row++)
	    if (channel->horiz_layer[row][col] == 0)
	    {
		space = YES;
		break;
	    }

	if (space == NO)
	{
	    /* We have found a full column. */
	    return;
	}
    }

    /* If we get here, we have looked at every column, and each one
    has had empty space. */

    if (ioform == HUMAN)
        (void) fprintf(output_file, "Doglegging would allow the channel to be narrower.\n");


}

