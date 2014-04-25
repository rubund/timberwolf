#include "copyright.h"
#include "yacr.h"

/*************************************************************
 *
 *  select_column calculates the maximum density of all the columns,
 *  and chooses one of the columns with the maximum density as the
 *  initial column for placing nets.
 *  The current choice of WHICH net with maximum density is a simplistic
 *  one, the leftmost column is chosen.
 *
 *  Author: Jim Reed
 *
 *  Date: 3-23-84
 *  Modified: 10-3-84	changed which column is selected
 *
 *****************************************************************/

void select_column (density, num_cols, initial_column, max_density, 
		    net_array, num_nets)
IN int *density;		/* array of density of each column */
IN int num_cols;		/* size of density */
OUT int *initial_column,	/* "best" choice for column to begin placing
				   nets in */
	*max_density;		/* maximum value in density[], minimum number
				   of rows required for routing */
IN NETPTR net_array;		/* array of information about all the nets */
IN int num_nets;		/* size of net_array */
{
    int i;			/* loop counter */
    DENSITY_LIST col_list;	/* list of columns with maximum density */
    DENSITY_LIST this_col,
		 a_col;		/* used to traverse col_list, loop counters */
    int max_density_count;	/* number of columns in col_list */
    int max_value;		/* used to find the maximum column value */

    *max_density = - 1;
    *initial_column = 0;

    /*
     *  make a list of columns with maximum density
     */

    for (i = 1; i <= num_cols; i++)
	if (*max_density < density[i])
	{
	    *max_density = density[i];
	    col_list = density_insert ((DENSITY_LIST) 0, i);
	    max_density_count = 1;
	}
	else if (*max_density == density[i])
	{
	    col_list = density_insert (col_list, i);
	    max_density_count++;
	}

    /*
     *  if there are only one or two columns, pick one
     */

    if (max_density_count < 3) 
	*initial_column = col_list->column;
    else
    {
	/*
	 *  find the column that shares the most nets with other columns
	 *  in the list
	 */

	/* set col_values and remove a columns that shares all of its nets
	 * with another column */
	for (this_col = col_list; this_col != NULL; this_col = this_col->next)
	{
	    for (i = 1; i <= num_nets; i++)
		if ((net_array[i].leftmost != NULL) &&
		    (net_array[i].leftmost->col <= this_col->column) &&
		    (net_array[i].rightmost->col >= this_col->column))
		{
		    for (a_col = col_list;
			a_col->column < net_array[i].leftmost->col;
		 	a_col = a_col->next);
		    while ((a_col != NULL) &&
			    (a_col->column <= net_array[i].rightmost->col))
		    {
			a_col->col_value++;
			a_col = a_col->next;
		    }
		}

	    /* remove columns that are equivalent (contain the same nets)
	     * to this_col */
	    while ((this_col->next != NULL) &&
			(this_col->col_value == this_col->next->col_value))
		this_col->next = this_col->next->next;
	}
      
	/*
	 *  find column with maximum col_value
	 */
	
	max_value = 0;
	for (this_col = col_list; this_col != NULL; this_col = this_col->next)
	  if (max_value < this_col->col_value)
	    {
	      max_value = this_col->col_value;
	      *initial_column = this_col->column;
	    }
      }
    
    /*
     *  print the maximum density column numbers
     */
    
    if (ioform == HUMAN)
      {
	(void) fprintf (output_file, "Columns with maximum density: ");
	for (this_col = col_list; this_col != NULL; this_col = this_col->next)
	    (void) fprintf (output_file, " %d", this_col->column);
	(void) fprintf (output_file, "\n");

	(void) fprintf(output_file, "Best choice(s) for starting column is (are): ");
	if (max_density_count<3) 
	  (void) fprintf(output_file,"%d",*initial_column);
	else {
	  for (this_col = col_list; this_col != NULL; this_col = this_col->next)
	    if (this_col->col_value == max_value)
	      (void) fprintf (output_file, " %d", this_col->column);
	  (void) fprintf (output_file, "\n");
	}
      }

}


