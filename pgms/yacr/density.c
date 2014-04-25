#include "copyright.h"
#include "yacr.h"

/*********************************************************************
 *
 *  find_density returns an array containing the density of each column.
 *  A net occupies all columns between its rightmost->col and its
 *  leftmost->col (inclusive).  rightmost and leftmost are set during
 *  the input routine, when the net data structures are being constructed.
 *
 *  Author: Jim Reed
 *
 *  Date: 3-21-84
 *
 *  Modified 3-28-85 by D. Braun to handle irregular channels
 *  It takes into account the amount of indentation of the irregular
 *  borders when calculating the density.
 *
 *  Modified 6-15-88 by H. Sheng. Gives a more accurate lower bound
 *  for channel widths. Eliminates some iterations in widening the
 *  channel to facilitate routing. Takes into account rows which
 *  no net can be placed when calculating density.
 **********************************************************************/

int *find_density (net_array, num_nets, num_cols, top_offset, bottom_offset)
IN NETPTR net_array;		/* array of all net data structures */
IN int num_nets,		/* size of net_array */
       num_cols;		/* size of returned array, number of columns
				   in the channel */
IN int *top_offset,
       *bottom_offset;		/* The arrays containing the border offsets */
{
    int i,j,k;			/* loop counters */
    int *density;		/* array that will contain the density of
				   each column */
    int found;                  /* flag for detecting end condition for 
                                   looping */
    int place = FALSE;
    int **t_colsn,               /* arrays for the top and bottom edge */
        **b_colsn;               /* collision constraints */

    int *num_cross;              /* array for keeping track of how many
                                    nets cross a column */

    /*
     *  allocate space for the density array
     */

    density = ALLOC(int, num_cols + 2);

    /* 
     * allocate space for the collision arrays 
     */

    t_colsn = ALLOC(int *, num_cols + 2);
    b_colsn = ALLOC(int *, num_cols + 2);

    num_cross = (int *) calloc((unsigned)num_cols+2, (unsigned) sizeof(int));

    for (i=0; i<=num_cols+1; i++) 
      t_colsn[i] = (int *) calloc((unsigned) max_top_offset+2,
				 (unsigned)sizeof(int));

    for (i=0; i<=num_cols+1; i++) 
      b_colsn[i] = (int *) calloc((unsigned) max_bottom_offset+2,
				 (unsigned) sizeof(int));


    /*
     * The last row in each column of the collision arrays is used to
     * keep track of the depth of the highest occurance of a net into the
     * channel. This facilitates the shrinking of the channel width if all
     * nets can be placed in an indentation.
     */

    for (i=0; i<=num_cols+1; i++)
      t_colsn[i][max_top_offset+1] = b_colsn[i][max_bottom_offset+1] = -1;
     
    /*
     *  initialize density[]
     */

    /* beards changed limits
	 old:
            for (i = 1; i <= num_cols; i++)
     */
    for (i = 0; i <= num_cols + 1; i++)
	density[i] = max_top_offset + max_bottom_offset;


    /* 
     * The following subtracts from the column densities for nets
     * that can be placed in indentations. The collision arrays 
     * guarantee that nets cannot overlap - there will be no horizontal
     * constraint violations.
     */
    for (i=1; i<=num_nets; i++)
      {
	if (net_array[i].leftmost == NULL)
	    continue;

	found = FALSE;
	if (net_array[i].pin_placement > 0) /* most pins on top*/
	  /*
	   * if most pins are on the top, then the algorithm attempts
           * first to place the net in an upper indentation.
	   */
	  {
	    for (j = 1; !found && j<=max_top_offset; j++)
	      {
		place = TRUE;
		for (k=net_array[i].leftmost->col; 
		     k<=net_array[i].rightmost->col; k++)
		  if ((t_colsn[k][j]!= 0) || (top_offset[k]>=j))
		    place = FALSE;
		if (place)
		  /* can be placed */
		  {
		    for (k=net_array[i].leftmost->col;
			 k<=net_array[i].rightmost->col; k++)
		      /* fill collision array */
		      {
			if (j>t_colsn[k][max_top_offset+1])
			  t_colsn[k][max_top_offset+1]=j;
			t_colsn[k][j]=abs(net_array[i].name);
			(density[k])--;
		      }
		    found = TRUE;
		  }
	      }
	  }
	for (j = 1; !found && j<=max_bottom_offset; j++)
	  /* trying to place in a lower indentation */
	  {
	    place = TRUE;
	    for (k=net_array[i].leftmost->col; 
		 k<=net_array[i].rightmost->col; k++)
	      if ((b_colsn[k][j]!=0) || (bottom_offset[k]>=j))
		place = FALSE;
	    if (place)
	      /* can be placed */
	      {
		for (k=net_array[i].leftmost->col;
		     k<=net_array[i].rightmost->col; k++)
		  /* fill collision array */
		  {
		    if (j<b_colsn[k][max_bottom_offset+1])
		      b_colsn[k][max_bottom_offset]=j;
		    b_colsn[k][j]=abs(net_array[i].name);
		    (density[k])--;
		  }
		found=TRUE;
	      }
	  }

	if (net_array[i].pin_placement <= 0) /* most pins not on top*/
	  {
	    /*
	     * if most pins are on the bottom or there are equal numbers
	     * of pins on top and bottom, then the algorithm will attempt
	     * to place the net in a lower indentation.
	     */
	    for (j = 1; !found && j<=max_top_offset; j++)
	      /* trying to place in an upper indentation */
	      {
		place = FALSE;
		for (k=net_array[i].leftmost->col; 
		     k<=net_array[i].rightmost->col; k++)
		  if ((t_colsn[k][j]!=0) || (top_offset[k]>=j))
		    place = TRUE;
		  if (!place)
		  /* can be placed */
		  {
		    for (k=net_array[i].leftmost->col;
			 k<=net_array[i].rightmost->col; k++)
		      /* fill collision array */
		      {
			if (j>t_colsn[k][max_top_offset+1])
			  t_colsn[k][max_top_offset+1]=j;
			t_colsn[k][j]=abs(net_array[i].name);
			(density[k])--;
		      }
		    found = TRUE;
		  }
	      }
	  }

    /*
     *  Adding the number of nets crossing the column to the density 
     * calculations. If the net was not able to be placed in an indentation,
     * then we keep track of it in num_cross[].
     */

	if (net_array[i].leftmost != NULL)
	  {
	    for (j = abs(net_array[i].leftmost->col);
		 j <= abs(net_array[i].rightmost->col);	j++)
	      {
		(density[j])++;
		if (!found) 
		  (num_cross[j])++;

	      }
	  }

      }

    /* 
     * Here, if all nets across a column could be placed in an indentation,
     * we adjust the density calculations accordingly.
     */

    for (i=1; i<=num_cols; i++)
      {
	if (num_cross[i] == 0)
	  density[i] =  MAX(t_colsn[i][max_top_offset+1], top_offset[i])
	    + MAX(b_colsn[i][max_bottom_offset+1], bottom_offset[i]);
      }


    /*
     * Set density at the left and right edges. They will be, at most, the
     * same as the first and last column, respectively.
     */

    density[0] = density[1];
    density[num_cols+1] = density[num_cols];
	   

    /*
     *  return result
     */

    return (density);
}



