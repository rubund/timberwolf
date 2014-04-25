#include "copyright.h"
#include "yacr.h"

/**********************************************************************
 *
 *  print_densest prints out a list of columns with maximum density.
 *
 *********************************************************************/

print_densest (density, num_cols, max_density)
IN int *density;		/* an array of teh density in each column */
IN int num_cols;		/* number of columns in the channel */
IN int max_density;		/* the maximum density of the channel */
{
    int i;			/* loop counter */


    (void) fprintf (output_file, "Columns with maximum density: ");

    for (i = 0; i < num_cols; )
	if (density[++i] == max_density)
	    (void) fprintf (output_file, " %d", i);

    (void) fprintf (output_file, "\n");
}


