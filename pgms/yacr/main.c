#include "copyright.h"
#define MAIN
#include "yacr.h"
#undef MAIN

/************************************************************************
 *
 * This is the main routine for yacr (pronounced 'yacker', stands for
 * 'Yet Another Channel Router').  The main routine does nothing but
 * call other routines.
 *
 * Author: Jim Reed
 *
 * Date: 3-17-84
 * Last modified: 3-21-84
 *
 ************************************************************************/


main (argc, argv)
IN int argc;			/* argc and argv are used to get
				   information from the command line */
IN char *argv[];
{
    int i;			/* loop counter */
    int done;			/* flag, YES if the channel was routed,
    				   NO if more rows are needed. */
    int save_maximum_density;
    int verify_error;
    INT_LIST bad_cols,bad_cols2;
    int bad_cnt,bad_place_cnt;
    int straight_sides;
    int *save_top_offset;
    int *save_bottom_offset;
    int defeat_relative;

    /*
     *  Initialize global variables
     */

    Vcv_cols = NULL;
    Cycle_cols = NULL;
    cyclecount = 0;

    /*
     *  process command line
     */
    
    straight_sides = FALSE;
    defeat_relative = FALSE;

RE_TRY:

    command_line (argc, argv);
    if (ioform == HUMAN) {
	(void) fprintf(stderr,"YACR 2.1: irregular channels and fixed end pins.\n");
    }

    /*
     * See if there was a problem opening files
     */
    
    if (input_file==NULL || output_file==NULL || result_file==NULL)
    {
	(void) fprintf(output_file,"Problem opening files!\n");
	exit(1);
    }

    /*
     *  read input
     */

    net_array = input (&top, &bottom, &left, &right, &up, &down,
			&top_offset, &bottom_offset,
			&num_nets, &num_cols,
			&num_left_nets, &num_right_nets,
		        &num_up_nets, &num_down_nets);

    if(defeat_relative == TRUE)
      place_relative = NO;
      
    
    /*
     * Check for bogus input
     */
    if (num_nets==0 || num_cols==0)
    {
	(void) fprintf(output_file,"Bogus input: No nets or no columns!\n");
	exit(1);
    }

    /*
     * Create the offset lists if they were not specified
     * in the input, and scale them.
     */

    if (top_offset == NULL)
	top_offset = create_offset(num_cols, 0);
    if (bottom_offset == NULL)
	bottom_offset = create_offset(num_cols, 0);


    scale_offset(top_offset,num_cols);
    scale_offset(bottom_offset,num_cols);

    if(straight_sides == TRUE)
      {
	top_offset = create_offset(num_cols,max_top_offset);
	bottom_offset = create_offset(num_cols,max_bottom_offset);
      }
    /* Set the variables max_top and _bottom_offsets. */

    max_top_offset = max_offset(top_offset,num_cols);
    max_bottom_offset = max_offset(bottom_offset,num_cols);


    if (ioform == HUMAN)
	(void) fprintf (output_file, 
	"num_nets= %d, num_cols= %d, num_left_nets= %d, num_right_nets= %d\n",
	 num_nets, num_cols, num_left_nets, num_right_nets);

    /*
     *  find density of each column
     */

    density = find_density (net_array, num_nets, num_cols,
   				 top_offset, bottom_offset);

    /*
     *  choose starting column
     */

    if (place_relative == LEFT || place_fixed == LEFT)
	initial_column = 1;
    else if (place_relative == RIGHT || place_fixed == RIGHT)
	initial_column = num_cols;
    if ((initial_column < 1) || (initial_column > num_cols))
	select_column (density, num_cols, &initial_column, &num_rows,
			net_array, num_nets);
    else
    {
	/* set num_rows to be the maximum density of the channel */
	num_rows = density[1];
	for (i = 2; i <= num_cols; i++)
	    if (density[i] > num_rows)
		num_rows = density[i];
	/* print the columns with maximum density */
	if (ioform == HUMAN)
	    print_densest (density, num_cols, num_rows);
    }


    if (ioform == HUMAN)
    {
	(void) fprintf (output_file, "max density = %d\n", num_rows);
    }
    save_maximum_density = num_rows;

    /* If we are using fixed edge placement, increase num_rows
       to the size of the edge, if necessary */

    if (place_fixed == LEFT)
    {
	if(num_left_nets < num_rows)
	{
	    (void) fprintf(output_file,"Not enough left nets to fill channel for fixed placement!\n");
	    exit(1);
	}
	num_rows = num_left_nets;
    }
    else if (place_fixed == RIGHT)
    {
	if(num_right_nets < num_rows)
	{
	    (void) fprintf(output_file,"Not enough right nets to fill channel for fixed placement!\n");
	    exit(1);
	}
	num_rows = num_right_nets;
    }

    /*
     *  print the starting column and density
     */

    if (ioform == HUMAN)
    {
	(void) fprintf (output_file, "initial_column = %d\n", initial_column);
    }

    /*
     *  build data structure linking nets in vertical constraint graph
     */

    build_graph (net_array, top, bottom, left, right, num_nets, num_cols,
		num_left_nets, num_right_nets, top_offset, bottom_offset);

    if (ioform == HUMAN)
    {
	(void) fprintf (output_file, "%d cycles were detected.\n", cyclecount);
    }


    /*
     *  beginning with max density, increase num_rows untill route succeeds
     */

    done = NO;
    channel = NULL;
    num_rows--;

    bad_cols = NULL;
    bad_cnt = 0;
    bad_place_cnt = 0;
    while ((done == NO) && (2 * num_nets + max_top_offset +
                                  max_bottom_offset >= num_rows))
    {
      if(channel != NULL)
	deallocate_channel(channel, num_rows, num_cols);  
/*      if(bad_place_cnt >= 5)
	goto STRAIGHTEN;*/
      (void) fflush(stdout);
	num_rows++;
	Vcv_cols = NULL;
	if (ioform == HUMAN)
	    (void) fprintf (output_file, "num_rows = %d\n", num_rows);

	/*
	 *  allocate memory for the channel and cost matrix
	 */

	channel = allocate_channel (num_rows, num_cols);

	/* Put the channel indentations into the channel array.
	If indent_channel returns TRUE, the borders overlap
	and the channel is too narrow. */

	if (indent_channel(channel, num_rows, num_cols,
			top_offset, bottom_offset)==TRUE)
	    continue;


	cost = init_cost (channel, num_rows, num_nets, net_array,
			  top, bottom, num_rows);
	if (debug == YES)
	{
            print_levels(net_array,num_nets);
            print_cost (cost, num_nets, num_rows); 
	}

	/*
	 *  put proper nets in placeable_nets list
	 */

	placeable_nets = init_placeable (net_array, num_nets, initial_column,
					 num_rows);

	/*
	 *  place nets in the starting column
	 */

	if (place_relative == LEFT)
	{
	  int temp;

	    if((temp = place_edge_nets (channel, cost, placeable_nets, num_rows,
				num_nets, num_cols, left, num_left_nets)) > 0)
	      {
		num_rows += (temp - 1);
		continue;
	      }
	}
	else if (place_relative == RIGHT)
	{
	  int temp;

	    if((temp = place_edge_nets (channel, cost, placeable_nets, num_rows,
			num_nets, num_cols, right, num_right_nets)) > 0)
	      {
		num_rows += (temp - 1);
		continue;
	      }
	}
	else if (place_fixed == LEFT)
	{
	    place_fixed_nets (channel, cost, placeable_nets, num_rows,
			num_nets, num_cols, left, num_left_nets);
	}
	else if (place_fixed == RIGHT)
	{
	    place_fixed_nets (channel, cost, placeable_nets, num_rows,
			num_nets, num_cols, right, num_right_nets);
	}
	else
	{
	    if (place_all_nets (channel, cost, placeable_nets,
			 num_rows, num_nets, num_cols)==FALSE)
	      {
		bad_place_cnt++;
		continue;
	      }
	}

	update_indent_channel(channel, num_rows, num_cols,
			      top_offset, bottom_offset);

	/*
	 *  place nets to the right of densest column
	 */

	if (move_right (channel, cost, top, bottom, initial_column, num_rows,
			 num_cols, num_nets) == FALSE) 
	  {
	    bad_place_cnt++;
	    continue;
	  }

	/*
	 *  place nets to the left of densest column
	 */

	if (move_left (channel, cost, top, bottom, initial_column,
			 num_rows, num_cols, num_nets) == FALSE) 
	  {
	    bad_place_cnt++;
	    continue;
	  }

	/*
	 *  remove the parallel lines generated above
	 */

	remove_parallel (channel, num_rows, num_cols, top_offset, bottom_offset);


	/*
	 *  route around vertical constraint violations
	 */

	done = maze (channel, num_rows, num_cols, top, bottom, &bad_cols2);


	/*
	 *  if maze could not complete the route, try adding a row
	 *  using the route so far accomplished
	 */

	if (done==NO && place_fixed == NO)
	{
	    done = add_one_row (channel, Vcv_cols, num_rows, num_cols,
				top, bottom);
	    if (done == YES)
		num_rows++;
	}

	/*
	 *  Find out if a cyclic constraint is causing problems
	 */

	if ((done == NO) && (can_add_columns == YES) &&
	(hopeless() == YES) && (max_top_offset == 0) &&
	(max_bottom_offset == 0) && (place_fixed == NO))
	{
	    add_columns (channel, &top, &bottom, net_array, num_nets,
			&num_rows, &num_cols);
	    Cycle_cols = NULL;
	    done = YES;
	}

	if (done == NO && hopeless() == YES && can_add_columns == YES &&
	    (max_top_offset > 0 || max_bottom_offset > 0))
	{
	    (void) fprintf(output_file,"I can't add a column when there are indentations.\n");
	}


	if (debug == YES)
	    print_channel (channel, num_rows, num_cols, num_nets);
	
	if (done==NO && place_fixed != NO)
	{
	    (void) fprintf(output_file,"There is a fixed edge, so I can't increase the channel width\n");
	    break;
	}

	(void) fflush(stdout);
	if(bad_cols2 == NULL)
	  {
	    bad_cnt = 0;
	    bad_cols = NULL;
	  }
	else
	  {
	    if(compare_cols(bad_cols,bad_cols2) == TRUE)
	      {
		bad_cnt++;
	      }
	    else
	      {
		bad_cols = bad_cols2;
		bad_cnt = 0;
	      }
	    if(bad_cnt >= 5)
	      {
STRAIGHTEN:
		if(straight_sides == TRUE)
		  break;
		(void) fprintf(stderr,"ERROR: cannot route irregular channel-- using straight_sides\n");
		straight_sides = TRUE;
		save_top_offset = top_offset;
		save_bottom_offset = bottom_offset;
		goto RE_TRY;
	      }
	  }
	  
    }

    if (done == NO)
    {
	(void) fprintf (output_file, "I'm sorry, but I can't route this channel\n");
	if (place_fixed == NO && max_top_offset == 0 &&
	    max_bottom_offset == 0 && can_add_columns == NO)
	{
	    (void) fprintf(output_file,"Why don't you try the -a option?\n");
	}

	exit (1);
    }

    /*
     *  clean up the channel
     */

    clean_channel (channel, num_rows, num_cols);

    /*
     *  maximize metal
     */

    if (maximize_metal == YES)
	max_metal (channel, num_rows, num_cols, top, bottom, 
			top_offset, bottom_offset);

    /*
     * make sure the border was not mutilated 
     * and that the routing is correct
     */

    check_border(channel, num_rows, num_cols, top, bottom,
			top_offset, bottom_offset);


    if(straight_sides == TRUE)
      {
	reconnect_pins(channel,num_cols,top,bottom);
	top_offset = save_top_offset;
	bottom_offset = save_bottom_offset;
      }

    /* 
     * Trim off all the vertical stuff that extends into the
     * border by refilling the border of the channel.
     * The return value of indent_channel will not be
     * meaningful.
     */

    (void) indent_channel(channel, num_rows, num_cols,
			top_offset, bottom_offset);

    /*
     *  print out the routed channel
     */

    if (ioform == HUMAN && outform == HUMAN)
    {
	(void) fprintf (output_file, "The final result is:\n");
    }
    if (stats_only == FALSE)
	print_channel (channel, num_rows, num_cols, num_nets);


    /*
     * Put the vert. segments back into the border regions
     * and verify the routing.
     * Verify must be called after the results are printed,
     * because it destroys the channel.
     *
     */

    unclip_border(channel, num_rows, num_cols, top, bottom,
			top_offset, bottom_offset);
    /* If there was an error, verify returns YES. */
    verify_error = verify (channel, num_rows, num_cols, net_array, num_nets);

    if(verify_error == YES)
      {
	if(straight_sides == FALSE)
	  {
	    goto STRAIGHTEN;
	  }
	if((place_relative != NO) && (defeat_relative == FALSE))
	  {
	    (void) fprintf(stderr, "ERROR - yacr cannot route this channel with relative edge pins -- retry without\n");
	    defeat_relative = TRUE;
	    goto RE_TRY;
	  }
      }

    if (ioform == HUMAN) {
        (void) fprintf (output_file, "%d rows were used.\n", num_rows);
    } else {
	(void) fprintf(output_file, "%d %d\n", 
	    save_maximum_density, cyclecount);
    }

    exit (verify_error);
}


compare_cols(cols,cols2)
INT_LIST cols,cols2;
{
INT_LIST i,i2;

if(cols == NULL)
  return(FALSE);

for(i = cols;i != NULL;i = i->next)
  {
    for(i2 = cols2;(i2 != NULL) && (i2->value != i->value);i2 = i2->next)
      {}
    if(i2 == NULL)
      return(FALSE);
  }
return(TRUE);
}

reconnect_pins(channel, num_cols,top,bottom)
INOUT CHANNELPTR channel;	/* the channel data structure */
int num_cols;
IN NETPTR *top,			/* the nets on the top edge of the channel */
	  *bottom;		/* the nets on the bottom of the channel */
{
int j,k;
int num;

for (j=1; j <= num_cols; j++)
  {
    if(top[j] != 0)
      {
	num = top[j]->name;
	for (k = max_top_offset;k > 0; k--)
	{
	  channel->vert_layer[k][j] = num;
	}
      }
    if(bottom[j] != 0)
      {
	num = bottom[j]->name;
	for (k = num_rows - max_bottom_offset + 1;k <= num_rows; k++)
	{
	  channel->vert_layer[k][j] = num;
	}
      }
  }
}
