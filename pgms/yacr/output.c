#include "copyright.h"
#include "yacr.h"

/*****************************************************************
 *
 *  print_channel prints out the contents of the horizontal and vertical
 *  route layers of the channel.  One column is included for each (left
 *  and right) edge.
 *
 *  Author: Jim Reed
 *
 *  Date: 3-30-84
 *
 ****************************************************************/

/*ARGSUSED*/
void print_channel (channel, num_rows, num_cols, num_nets)
IN CHANNELPTR channel;		/* the channel to be printed */
IN int num_rows;		/* number of rows in the channel */
IN int num_cols;		/* number of columns in the channel */
IN int num_nets;		/* number of nets in the channel */
{
    register int i, j;		/* loop counters */
    register int num, l;	/* used to convert integers to characters */
    char temp[20];		/* the caracter representation of a number */

    if ((ioform == MACHINE) || (outform == MACHINE))
    {
	if (outform != MACHINE)
	    result_file = output_file;  /* A hack */
	(void) fprintf (result_file, "%d\n", num_rows);
	(void) fprintf (result_file, "%d\n", num_cols);

	for (j = 1; j <= num_rows; j++)
	{
	    for (i = 1; i <= num_cols; i++)
	    {
		/* insert a space to separate the numbers */
		putc(' ', result_file);

		num = channel->horiz_layer[j][i];

		if (num == BORDER)
		{
		    putc(' ',result_file);
		    putc('0',result_file);
		}
		else
		{
		    num = number_to_name(num);

		    /* Generate digits (reverse order) */
		    l = 0; do temp[l++] = num % 10 + '0'; while ((num /= 10) > 0);

		    /* right justify the number in a two digit field */
		    if (l == 1)
		        putc(' ', result_file);
    
		    /* Copy them back in correct order */
		    do putc(temp[--l], result_file); while (l > 0);
	        }
	    }
	    putc('\n', result_file);
	}

	for (j = 1; j <= num_rows; j++)
	{
	    for (i = 1; i <= num_cols; i++)
	    {
		/* insert a space to separate the numbers */
		putc(' ', result_file);

		num = channel->vert_layer[j][i];

		if (num == BORDER)
		{
		    putc(' ',result_file);
		    putc('0',result_file);
		}
		else
		{
		    num = number_to_name(num);

		    /* Generate digits (reverse order) */
		    l = 0; do temp[l++] = num % 10 + '0'; while ((num /= 10) > 0);

		    /* right justify the number in a two digit field */
		    if (l == 1)
		        putc(' ', result_file);

		    /* Copy them back in correct order */
		    do putc(temp[--l], result_file); while (l > 0);
	        }
	    }
	    putc('\n', result_file);
	}
    }
    else
    {
	(void) fprintf (output_file, "\nThe horizontal layer (turned sideways):\n");
	for (j = 0; j <= num_cols + 1; j++)
	{
	    putc(' ', output_file);
	    for (i = num_rows; i >= 1; i--)
	    {
		num = channel->horiz_layer[i][j];

		if (num == BORDER)
		{
		    putc(' ',output_file);
		    putc('X',output_file);
		    putc(' ',output_file);
		}
		else
		{
		    num = number_to_name(num);

		    /* Generate digits (reverse order) */
		    l = 0; do temp[l++] = num % 10 + '0'; while ((num /= 10) > 0);

		    /* right justify the number in a two digit field */
		    if (l == 1)
		        putc(' ', output_file);
    
		    /* Copy them back in correct order */
		    do putc(temp[--l], output_file); while (l > 0);

		    /* insert a space to separate the numbers */
		    putc(' ', output_file);
	        }
	    }
	    (void) fprintf (output_file, " col = %3d\n", j + channel->left_column);
	}

	(void) fprintf (output_file, "\nThe vertical layer (turned sideways):\n");
	for (j = 0; j <= num_cols + 1; j++)
	{
	    putc(' ', output_file);
	    for (i = num_rows; i >= 1; i--)
	    {
		num = channel->vert_layer[i][j];
		if (num == BORDER)
		{
		    putc(' ',output_file);
		    putc('X',output_file);
		    putc(' ',output_file);
		}
		else
		{
		    num = number_to_name(num);

		    /* Generate digits (reverse order) */
		    l = 0; do temp[l++] = num % 10 + '0'; while ((num /= 10) > 0);

		    /* right justify the number in a 2 digit field */
		    if (l == 1)
		        putc(' ', output_file);

		    /* Copy them back in correct order */
		    do putc(temp[--l], output_file); while (l > 0);

		    /* insert a space to separate the numbers */
		    putc(' ', output_file);
	        }
	    }
	    (void) fprintf (output_file, "  col = %3d\n", j + channel->left_column);
	}
    }

    if ((place_relative != NO)&&(place_fixed != NO))
    {
	(void) fprintf(output_file,"Fatal error: You can't have fixed and relative edges!");
	exit(1);
    }
}


