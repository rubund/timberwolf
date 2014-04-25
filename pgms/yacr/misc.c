#include "copyright.h"
#include "yacr.h"

/******************************************************************
 *
 *  command_line processes all the information on the command line.
 *  Global flags are set from this, and input and output files are opened.
 *  If no input and output files are specified, stdin and stdout are
 *  assumed.
 *
 *  Author: Jim Reed
 *
 *  Date: 3-17-84
 *  Modified: 4-26-84  (ioform)
 *            5-12-84  (initial_column, debug)
 *
 *****************************************************************/

void command_line (argc, argv)
IN int argc;			/* argc and argv are used to get information
				   from the command line */
IN char *argv[];
{
    int i;			/* loop counter */

    /* set defaults */
    input_file = stdin;
    result_file = stdin;
    output_file = stdout;
    ioform = HUMAN;
    outform = HUMAN;
    printcycles = YES;
    initial_column = 0;
    debug = NO;
    stats_only = NO;
    maximize_metal = YES;
    can_add_columns = NO;

    for (i = 1; i < argc; i++)
    {
	if (strcmp (argv[i], "-H") == 0)
	    ioform = MACHINE;
	else if (strcmp (argv[i], "-C") == 0)
	    printcycles = NO;
	else if (strcmp (argv[i], "-O") == 0)
	{
	    outform = MACHINE;
	    if (i < argc-1) result_file = fopen(argv[++i], "w");
	    else outform = HUMAN;
	}
	else if (strcmp (argv[i], "-d") == 0)
	    debug = YES;
	else if (strcmp (argv[i], "-s") == 0)
	    stats_only = YES;
	else if (strcmp (argv[i], "-m") == 0)
	    maximize_metal = NO;
	else if (strcmp (argv[i], "-a") == 0)
	    can_add_columns = YES;
	else if (strcmp (argv[i], "-c") == 0)
	{
	    i++;
	    if (i < argc)
		(void) sscanf (argv[i], "%d", &initial_column);
	}
	else
	{
	    if (ioform == HUMAN)
	    {
		input_file = fopen (argv[i], "r");
		if (i + 1 < argc)
		    output_file = fopen (argv[i + 1], "w");
		(void) fprintf (output_file, "\nInput file: %s\n\n", argv[i]);
		return;
	    }
	}
    }
}



/******************************************************************
 *
 *  init_placeable returns a list of pointers to nets that occupy column
 *  "column".  insert_net is called to allocate space and
 *  perform the actuall insertion into the list.
 *  This routine also sets each nets 'row' to 0.
 *
 *  Author: Jim Reed
 *
 *  Date: 3-24-84
 *
 *****************************************************************/

NET_LIST init_placeable (net_array, num_nets, column, num_rows)
IN NETPTR net_array;		/* all of the net data structures */
IN int num_nets,		/* size of net_array */
    column;			/* all nets which occupy column "column" will
				   be placed in placeable_nets */
IN int num_rows;		/* number of rows in the channel */
{
    int i;			/* loop counter */
    NET_LIST placeable_nets;	/* the list that is created */
    NET_LIST trav;		/* used to traverse the placeable_nets list
				   while setting the available_rows field */

    placeable_nets = NULL;

    for (i = 1; i <= num_nets; i++)
	if (net_array[i].leftmost != NULL)
	{
	    net_array[i].row = 0;
	    if ((net_array[i].leftmost->col <= column) &&
			(net_array[i].rightmost->col >= column))
		placeable_nets = insert_net (placeable_nets, net_array + i);
	}

    for (trav = placeable_nets; trav != NULL; trav = trav->next)
	trav->available_rows = num_rows;

    return (placeable_nets);
}



/*************************************************************
 *
 *  print_cost prints the full cost matrix.  Used for debugging.
 *
 *  Author: Jim Reed
 *
 *  Date: 3-28-84
 *
 ***************************************************************/

void print_cost (cost, num_rows, num_cols)
IN int **cost;			/* the cost matrix */
IN int num_rows;		/* number of rows in cost matrix */
IN int num_cols;		/* number of columns in cost matrix */
{
    int i, j;			/* loop counters */

    if (ioform == HUMAN)
    {
	(void) printf ("The cost matrix is:\n");
	for (i = 0; i <= num_rows; i++)
	{
	    (void) printf ("net %2d: ", i);
	    for (j = num_cols; j >= 1; j--)
		(void) printf (" %7d", cost[j][i]);
	    (void) printf ("\n");
	}
    }
}


/*****************************************************************
 *
 *  column_sum returns the sum of the values in rows 1 through num_rows
 *  in column 'column'.
 *
 *  Author: Jim Reed
 *
 *  Date: 4-20-84
 *
 ***************************************************************/

int column_sum (matrix, column, num_rows)
IN int **matrix;		/* the matrix of interest */
IN int column;			/* the column of the matrix */
IN int num_rows;		/* number of rows in the matrix */
{
    register int sum;		/* the sum */
    register int i;		/* loop counter */

    sum = 0;
    for (i = num_rows; i > 0; sum += matrix[i--][column]);

    return (sum);
}



/*****************************************************
 *
 *  name_to_number and number_to_name handle the translation from the
 *  external (input) to the internal numbers used for the various nets
 *  being routed.  init_name_translation is called to set up the static
 *  variables declared below that are used in the translation.
 *  Since this name_to_number is called only once per pin on the channel
 *  it is not done in a very efficient way.  number_to_name is called
 *  (at least) once for every piece of metal or poly in the final routed
 *  channel, so it is very efficient.
 *  
 *  Author: Jim Reed
 *  
 *  Date: 11-9-84
 *  
 ******************************************************/

static int max_net_number;	/* largest net number used so far */

void init_name_translation (num_nets)
IN int num_nets;		/* number of nets that will be in the channel
				   */
{
    int i;			/* loop counter */

    /* allocate the name_array */
    name_array = ALLOC(int, num_nets + 1);

    /* empty the array */
    for (i = 0; i <= num_nets; name_array[i++] = 0);

    /* set max_net_number */
    max_net_number = 0;
}

/* number_to_name has been changed to a macro.  It (and name_array) would
 * have to be moved to "yacr.h"
 */
/* int number_to_name (number)
IN int number;			* the net number whose name is desired *
{
    return (name_array[number]);
} */

int correct_num_nets ()
{
    return (max_net_number);
}

int name_to_number (name)
IN int name;			/* the external name of a net */
{
    int i;			/* loop counter */

/*     name_array[name] = name;
    return(name);
 */

    /* if "name" has already been assigned a number, return that number */
    for (i = 0; i <= max_net_number; i++)
	if (name_array[i] == name)
	    return (i);

    /* assign max_net_number+1 to be name */
    max_net_number++;
    name_array[max_net_number] = name;
    return (max_net_number);
}


/********************************************************
 *
 *  hopeless compares the contents of Vcv_cols and Cycle_cols.
 *  If all of the Vcv_cols are also Cycle_cols, hopeless returns
 *  YES, otherwise hopeless returns NO.
 *  
 *  Author: Jim Reed
 *  
 *  Date: 11-22-84
 *  
 *****************************************************/

int hopeless()
{
    INT_LIST v_list;		/* traverses Vcv_list */
    INT_LIST c_list;		/* traverses Cycle_list */
    int found;			/* a flag. YES if the item in the Vcv_list is
				   found in the Cycle_list */

    for (v_list = Vcv_cols; v_list != NULL; v_list = v_list->next)
    {
	found = NO;
	for (c_list = Cycle_cols; c_list != NULL; c_list = c_list->next)
	    if (v_list->value == c_list->value)
		found = YES;
	if (found == NO)
	    return (NO);
    }

    return (YES);
}




/* This dumps data about the VCG for diagnostic purposes. */

void print_levels(net_array,num_nets)
NETPTR net_array;
int num_nets;
{
    int j;
    int max_lt,
	max_lb,
	max_total;

    max_lt = max_lb = max_total = 0;

    for (j=0; j < num_nets; j++)
    {
	if (number_to_name(net_array[j].name) != 0)
	{
	    (void) printf("Net: %d Level_from_top: %d Level_from_bottom: %d\n",
		    number_to_name(net_array[j].name),
		    net_array[j].level_from_top,
		    net_array[j].level_from_bottom);

	    if (net_array[j].level_from_top > max_lt)
	        max_lt = net_array[j].level_from_top;
	    if (net_array[j].level_from_bottom > max_lb)
	        max_lb = net_array[j].level_from_bottom;
	    if (net_array[j].level_from_top +
        	    net_array[j].level_from_bottom > max_total)
	        max_total = net_array[j].level_from_top
	                        + net_array[j].level_from_bottom;
	}
    }
    (void) printf("Max level_from_top: %d Max level_from_bottom: %d Max depth: %d\n",max_lt, max_lb, max_total);
}



/* This returns YES if the given net is fixed at one end of
the channel.  */

int is_fixed_net(net)
NETPTR net;
{
    int j;    /* Loop counter. */

    if (place_fixed == LEFT)
    {
	for (j=1; j <= num_left_nets; j++)
	{
	    if (left[j] == net)
		return (YES);
	}
	return (NO);
    }
    else if (place_fixed == RIGHT)
    {
	for (j=1; j <= num_right_nets; j++)
	{
	    if (right[j] == net)
		return (YES);
	}
	return (NO);
    }
    
    return (NO);
}
