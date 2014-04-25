#include "copyright.h"
#include "yacr.h"

/*******************************************************************
 *
 *  This routine reads the input for yacr, and returns an array of
 *  NETs.  The array contains all of the net data structures.
 *  The input is returned to
 *  the main routine in the form of arrays of pointers to NET structures.
 *  For example, top[i] is a pointer to the net connected to a pin on
 *  the top edge of the channel in column i.
 *
 *  Input should be in the following format:????????????????????????
 *
 *  Author: Jim Reed
 *
 *  Date: 3-18-84
 *  Last modified: 3-22-84
 *
 *  Modified: 6-24-66 to handle partial boundary constraints. H. Sheng
 *
 ********************************************************************/

NETPTR input (top, bottom, left, right, up, down, top_offset, bottom_offset,
		num_nets, num_cols, num_left_nets, num_right_nets,
                num_up_nets, num_down_nets)

OUT NETPTR *(top[]),		/* array of nets on top of channel */
	   *(bottom[]),		/* array of nets on bottom of channel */
	   *(left[]),		/* nets entering from left */
	   *(right[]),		/* nets entering from right */
           *(up[]),             /* nets with partial upward constraint */
           *(down[]);           /* nets with partial downward constraint */

OUT int	   *(top_offset[]),	/* vert. offset of top pins */
	   *(bottom_offset[]);	/* vert. offset of bottom pins */

OUT int *num_nets,		/* total number of nets */
	*num_cols,		/* number of columns (size of top[] and
				   bottom[]) */
	*num_left_nets,		/* number of nets entering from left (size of
				   left[]) */
	*num_right_nets,	/* number of nets entering form right (size
				   of right[]) */
        *num_up_nets,           /* number of nets with partial upper
				   constraints */
        *num_down_nets;         /* number of nets with partial downward
				   constraints */

{
    NETPTR net_array;		/* used to allocate space for net data
				   structure */
    int net_number;		/* used to translate input net name to a
				   pointer to the net */
    int i;			/* loop counter */
    char input_string[15];	/* used to parse input */
    int edge_count;		/* Used to check edge lists for bad pins */
  
    /*
     *  initialize variables in case some are not read in
     */
  
    *top = NULL;
    *bottom = NULL;
    *left = NULL;
    *right = NULL;
    *up = NULL;
    *down = NULL;
    *top_offset = NULL;
    *bottom_offset = NULL;
    *num_nets = 0;
    *num_cols = 0;
    *num_left_nets = 0;
    *num_right_nets = 0;

    /* place_relative is a global variable */
    place_relative = NO;
    place_fixed = NO;
    place_partial = NO;

    /*
     *  read input
     */

    if (ioform == MACHINE)
      {
	(void) fscanf (input_file, "%d", num_nets);
	(void) fscanf (input_file, "%d", num_cols);
	net_array = allocate_nets (*num_nets + 1);

	init_name_translation (*num_nets);

	*top = ALLOC(NETPTR, *num_cols + 1);
	for (i = 1; i <= *num_cols; i++)
	{
	    (void) fscanf (input_file, "%d", &net_number);
	    (*top)[i] = net_array + name_to_number (net_number);
	    store_pin ((*top)[i], i, TOP);
	}

	*bottom = ALLOC(NETPTR, *num_cols + 1);
	for (i = 1; i <= *num_cols; i++)
	{
	    (void) fscanf (input_file, "%d", &net_number);
	    (*bottom)[i] = net_array + name_to_number (net_number);
	    store_pin ((*bottom)[i], i, BOTTOM);
	  }

	(void) fscanf (input_file, "%s", input_string);
	if ((strcmp (input_string, "partial_up") == 0) ||
	    (strcmp (input_string, "PARTIAL_UP") == 0))
	  {
	    if (place_partial == DOWN)
	      place_partial = BOTH;
	    else
	      place_partial = UP;
	    (void) fscanf (input_file, "%d", num_up_nets);
	    *up = ALLOC(NETPTR, *num_up_nets + 1);
	    for (i=1; i<=*num_up_nets; i++)
	      {
		(void) fscanf (input_file, "%d", &net_number);
		(*up)[i] = net_array + name_to_number (net_number);
	      }
	    (void) fscanf (input_file, "%s", input_string);
	  }
	if ((strcmp (input_string, "partial_down") == 0) ||
	    (strcmp (input_string, "PARTIAL_DOWN") == 0))
	  {
	    if (place_partial == UP)
	      place_partial = BOTH;
	    else
	      place_partial = DOWN;
	    (void) fscanf (input_file, "%d", num_down_nets);
	    *down = ALLOC(NETPTR, *num_down_nets + 1);
	    for (i=1; i<=*num_down_nets; i++)
	      {
		(void) fscanf (input_file, "%d", &net_number);
		(*down)[i] = net_array + name_to_number (net_number);
	      }
	    (void) fscanf (input_file, "%s", input_string);
	  }
		
	    
	if ((strcmp (input_string, "relative") == 0) ||
	    (strcmp (input_string, "RELATIVE") == 0))
	{
	    place_relative = LEFT;
	    (void) fscanf (input_file, "%d", num_left_nets);
	}
	else if ((strcmp (input_string, "fixed") == 0) ||
	    (strcmp (input_string, "FIXED") == 0))
	{
	    place_fixed = LEFT;
	    (void) fscanf (input_file, "%d", num_left_nets);
	}
	else
	    (void) sscanf (input_string, "%d", num_left_nets);
	*left = ALLOC(NETPTR, *num_left_nets + 1);
	for (i = 1; i <= *num_left_nets; i++)
	{
	    (void) fscanf (input_file, "%d", &net_number);
	    (*left)[i] = net_array + name_to_number (net_number);
	    store_pin ((*left)[i], 0, LEFT);
	}

	(void) fscanf (input_file, "%s", input_string);
	if ((strcmp (input_string, "relative") == 0) ||
	    (strcmp (input_string, "RELATIVE") == 0))
	{
	    place_relative = RIGHT;
	    (void) fscanf (input_file, "%d", num_right_nets);
	}
	else if ((strcmp (input_string, "fixed") == 0) ||
	    (strcmp (input_string, "FIXED") == 0))
	{
	    place_fixed = RIGHT;
	    (void) fscanf (input_file, "%d", num_right_nets);
	}
	else
	    (void) sscanf (input_string, "%d", num_right_nets);
	*right = ALLOC(NETPTR, *num_right_nets + 1);
	for (i = 1; i <= *num_right_nets; i++)
	{
	    (void) fscanf (input_file, "%d", &net_number);
	    (*right)[i] = net_array + name_to_number (net_number);
	    store_pin ((*right)[i], *num_cols + 1, RIGHT);
	}

	/* Read the top and bottom offsets, if they are there */

        *top_offset = ALLOC(int, *num_cols + 2);
        for (i = 1; i <= *num_cols; i++)
        {
	    if (fscanf (input_file, "%d", &net_number) != 1)
	    {
		*top_offset = NULL;
		break;
	    }
	    (*top_offset)[i] = net_number;

        }

	/* We want to set the left and right edge top offsets. These must 
         * be equal to the leftmost and rightmost column top offsets,
         * respectively.
         */

	if (i!=1){      /* Check for offset list validity */
	  (*top_offset)[i] = (*top_offset)[i-1];
	  (*top_offset)[0] = (*top_offset)[1];
	}
		

        *bottom_offset = ALLOC(int, *num_cols + 1);
        for (i = 1; i <= *num_cols; i++)
        {
	    if (fscanf (input_file, "%d", &net_number) != 1)
	    {
		*bottom_offset = NULL;
		break;
	    }
	    (*bottom_offset)[i] = net_number;
        }

	/* Now, we want to set the left and right edge bottom offsets.
         * Again, these must be equal to the leftmost and rightmost 
         * column bottom offsets, respectively.
         */

	if (i!=1){      /* Check for offset list validity */
	  (*bottom_offset)[i] = (*bottom_offset)[i-1];
	  (*bottom_offset)[0] = (*bottom_offset)[1];
	}

    }
    else /* assume ioform == HUMAN */
    {
	while (fscanf (input_file, "%s", input_string) != EOF)
	{
	    if ((strcmp (input_string, "ncol=") == 0) ||
		(strcmp (input_string, "NCOL=") == 0))
	    {
		if (*num_cols == 0)
		    (void) fscanf (input_file, "%d", num_cols);
		else
		    (void) fprintf (output_file,
				"ncol already given, first number used.\n");
		if (place_relative == YES)
		    place_relative = NO;
		if (place_fixed == YES)
		    place_fixed = NO;
	    }
	    else if ((strcmp (input_string, "nnet=") == 0) ||
		     (strcmp (input_string, "NNET=") == 0))
	    {
		if (*num_nets == 0)
		{
		    (void) fscanf (input_file, "%d", num_nets);
		    net_array = allocate_nets (*num_nets + 1);
		    init_name_translation (*num_nets);
		}
		else
		    (void) fprintf (output_file,
				"nnet already given, first number used.\n");
		if (place_relative == YES)
		    place_relative = NO;
		if (place_fixed == YES)
		    place_fixed = NO;
	    }
	    else if ((strcmp (input_string, "top_list") == 0) ||
		     (strcmp (input_string, "TOP_LIST") == 0))
	    {
		if (*top == NULL)
		{
		    *top = ALLOC(NETPTR, *num_cols + 1);
		    for (i = 1; i <= *num_cols; i++)
		    {
			(void) fscanf (input_file, "%d", &net_number);
			(*top)[i] = net_array + name_to_number (net_number);
			store_pin ((*top)[i], i, TOP);
		    }
		}
		else
		    (void) fprintf (output_file,
			    "top_list already specified, first list used.\n");
		if (place_relative == YES)
		    place_relative = NO;
		if (place_fixed == YES)
		    place_fixed = NO;
	    }
	    else if ((strcmp (input_string, "bottom_list") == 0) ||
		     (strcmp (input_string, "BOTTOM_LIST") == 0))
	    {
		if (*bottom == NULL)
		{
		    *bottom = ALLOC(NETPTR, *num_cols + 1);
		    for (i = 1; i <= *num_cols; i++)
		    {
			(void) fscanf (input_file, "%d", &net_number);
			(*bottom)[i] = net_array + name_to_number(net_number);
			store_pin ((*bottom)[i], i, BOTTOM);
		    }
		}
		else
		    (void) fprintf (output_file,
			 "bottom_list already specified, first list used.\n");
		if (place_relative == YES)
		    place_relative = NO;
		if (place_fixed == YES)
		    place_fixed = NO;
	    }
	    else if ((strcmp (input_string, "top_offset") == 0) ||
		     (strcmp (input_string, "TOP_OFFSET") == 0))
	    {
		if (*top_offset == NULL)
		{
		    *top_offset = ALLOC(int, *num_cols + 2);
		    for (i = 1; i <= *num_cols; i++)
		    {
			(void) fscanf (input_file, "%d", &net_number);
			(*top_offset)[i] = net_number;
		    }
	/* We want to set the left and right edge top offsets. These must 
         * be equal to the leftmost and rightmost column top offsets,
         * respectively.
         */

		    if (i>1){      /* Check for offset list validity */
		      (*top_offset)[i] = (*top_offset)[i-1];
		      (*top_offset)[0] = (*top_offset)[1];
		    }
		  }
		else
		    (void) fprintf (output_file,
			    "top_offset already specified, first list used.\n");
	    }
	    else if ((strcmp (input_string, "bottom_offset") == 0) ||
		     (strcmp (input_string, "BOTTOM_OFFSET") == 0))
	    {
		if (*bottom_offset == NULL)
		{
/* beards - aug 87 - fixed (?) core dump problem by changing 1 to 2
		    *bottom_offset = ALLOC(int, *num_cols + 1);
*/
		    *bottom_offset = ALLOC(int, *num_cols + 2);
		    for (i = 1; i <= *num_cols; i++)
		    {
			(void) fscanf (input_file, "%d", &net_number);
			(*bottom_offset)[i] = net_number;
		    }
	/* Now, we want to set the left and right edge bottom offsets.
         * Again, these must be equal to the leftmost and rightmost 
         * column bottom offsets, respectively.
         */

		    if (i!=1){      /* Check for offset list validity */
		      (*bottom_offset)[i] = (*bottom_offset)[i-1];
		      (*bottom_offset)[0] = (*bottom_offset)[1];
		    }
		}
		else
		    (void) fprintf (output_file,
			 "bottom_offset already specified, first list used.\n");
	    }
	    else if ((strcmp (input_string, "partial_up") == 0) ||
		     (strcmp (input_string, "PARTIAL_UP") == 0))
	      {
		if (place_partial == DOWN)
		  place_partial = BOTH;
		else
		  place_partial = UP;
		(void) fscanf (input_file, "%d", num_up_nets);
		(void) printf("num_up_nets: %d\t",*num_up_nets);
		*up = ALLOC(NETPTR, *num_up_nets+1);
		for (i=1; i<=*num_up_nets; i++)
		  {
		    (void) fscanf (input_file, "%d", &net_number);
		    (*up)[i] = net_array + name_to_number (net_number);
		  }
	      }
	    else if ((strcmp (input_string, "partial_down") == 0) ||
		     (strcmp (input_string, "PARTIAL_DOWN") == 0))
	      {
		if (place_partial == UP)
		  place_partial = BOTH;
		else
		  place_partial = DOWN;
		(void) fscanf (input_file, "%d", num_down_nets);
		(void) printf("num_down_nets: %d\n",*num_down_nets);
		*down = ALLOC(NETPTR, *num_down_nets+1);
		for (i=1; i<=*num_down_nets; i++)
		  {
		    (void) fscanf (input_file, "%d", &net_number);
		    (*down)[i] = net_array + name_to_number (net_number);
		  }
	      }
	    
	    
	    else if ((strcmp (input_string, "left_list") == 0) ||
		     (strcmp (input_string, "LEFT_LIST") == 0))
	    {
		if (*left == NULL)
		{
		    (void) fscanf (input_file, "%d", num_left_nets);
		    *left = ALLOC(NETPTR, *num_left_nets + 1);
		    for (i = 1; i <= *num_left_nets; i++)
		    {
			(void) fscanf (input_file, "%d", &net_number);
			(*left)[i] = net_array + name_to_number (net_number);
			store_pin ((*left)[i], 0, LEFT);
		    }
		    if (place_relative == YES)
			if (*num_left_nets > 1)
			    place_relative = LEFT;
			else
			    place_relative = NO;
		    if (place_fixed == YES)
			if (*num_left_nets > 1)
			    place_fixed = LEFT;
			else
			    place_fixed = NO;
		  }
		else
		{
		    (void) fprintf (output_file,
			   "left_list already specified, first list used.\n");
		    if (place_relative == YES)
			place_relative = NO;
		    if (place_fixed == YES)
		        place_fixed = NO;
		}
	    }
	    else if ((strcmp (input_string, "right_list") == 0) ||
		     (strcmp (input_string, "RIGHT_LIST") == 0))
	    {
		if (*right == NULL)
		{
		    (void) fscanf (input_file, "%d", num_right_nets);
		    *right = ALLOC(NETPTR, *num_right_nets + 1);
		    for (i = 1; i <= *num_right_nets; i++)
		    {
			(void) fscanf (input_file, "%d", &net_number);
			(*right)[i] = net_array + name_to_number (net_number);
			store_pin ((*right)[i], *num_cols + 1, RIGHT);
		    }
		    if (place_relative == YES)
			if (*num_right_nets > 1)
			    place_relative = RIGHT;
			else
			    place_relative = NO;
		    if (place_fixed == YES)
			if (*num_right_nets > 1)
			    place_fixed = RIGHT;
			else
			    place_fixed = NO;
		}
		else
		{
		    (void) fprintf (output_file,
			  "right_list already specified, first list used.\n");
		    if (place_relative == YES)
			place_relative = NO;
		    if (place_fixed == YES)
			place_fixed = NO;
		}
	    }
	    else if ((strcmp (input_string, "relative") == 0) ||
		     (strcmp (input_string, "RELATIVE") == 0))
	    {
		if (place_relative == NO)
		    place_relative = YES;
	    }
	    else if ((strcmp (input_string, "fixed") == 0) ||
		     (strcmp (input_string, "FIXED") == 0))
	    {
		if (place_fixed == NO)
		    place_fixed = YES;
	    }
	}
    }

    /*
     *   If we are not doing fixed edge placement, remove any
     *   repeated, unique, and zero edge nets.
     *   This allows floating edge lists to have lots of garbage
     *   nets, and have the garbage be ignored.
     */

     edge_count = *num_left_nets;
     strip_dup_nets(*left, num_left_nets);
     if (*num_left_nets < edge_count && 
	 (place_relative == LEFT || place_fixed == LEFT))
     {
	 (void) fprintf(output_file,"You have duplicate left edge nets!\n");
	 exit(1);
     }

     edge_count = *num_right_nets;
     strip_dup_nets(*right, num_right_nets);
     if (*num_right_nets < edge_count && 
	 (place_relative == RIGHT || place_fixed == RIGHT))
     {
	 (void) fprintf(output_file,"You have duplicate right edge nets!\n");
	 exit(1);
     }

     if (place_fixed != LEFT)
     {
	 strip_zero_nets(*left, num_left_nets);
	 strip_unique_nets(*left, num_left_nets);
     }
     if (place_fixed != RIGHT)
     {
	 strip_zero_nets(*right, num_right_nets);
	 strip_unique_nets(*right, num_right_nets);
     }


    /* set correct value for num_nets */
    *num_nets = correct_num_nets();

    /* if any net has no pins or only one pin then delete it from 
     * net_array.  Delete net i by setting net_array[i].leftmost to NULL.
     */

    for (i = 1; i <= *num_nets; i++)
	if (net_array[i].leftmost == net_array[i].rightmost)
	{
	    if ((ioform == HUMAN) && (number_to_name(i) != 0))
		if (net_array[i].leftmost == NULL)
		    (void) fprintf (output_file, "Net %d has no pins.\n",
						number_to_name(i));
		else
		    (void) fprintf (output_file, "Net %d has only 1 pin.\n",
						number_to_name(i));
	    net_array[i].leftmost = net_array[i].rightmost = NULL;
	    net_array[i].name = 0;
	}

    return (net_array);
  }



/********************************************************************
 *
 *  store_pin adds a pin to the list of pins a net is connected to.
 *  The list is ordered by the column number of the pin.
 *  Space is allocated for the pin element, and its values are set.
 *  It will not add a duplicate entry for a pin with the same column
 *  and edge as one already in the list.
 *
 *  Author: Jim Reed
 *
 *  Date: 3-22-84
 *  Modified: 9-24-84	pin_placement added
 *  Modified: 2-12-85	duplicate pin supression added
 *
 *******************************************************************/

void store_pin (net, column, this_edge)
INOUT NETPTR net;		/* The net connected to the column */
IN int column,			/* The column the net is connected to */
       this_edge;		/* The edge of the channel the pin is on */

{
    PIN_LIST temp;		/* for allocation of space */
    PIN_LIST this_pin;		/* for finding proper location of inserted
				   edge */

    temp = ALLOC(PIN_LIST_ELEMENT, 1);
    temp->edge = this_edge;
    temp->col = column;

    /*
     *  Update pin_placement for the net
     */

    if (this_edge == TOP) 
      {
	net->num_top++;
	net->pin_placement++;
      }
    else if (this_edge == BOTTOM)
      {
	net->num_bot++;
	net->pin_placement--;
      }
    /*
     *  Insert temp at proper place in list
     */

    this_pin = net->leftmost;

    if (this_pin == NULL)
    {				/* new pin is the only one in the list */
	temp->right_list = NULL;
	temp->left_list = NULL;
	net->rightmost = temp;
	net->leftmost = temp;
    }
    else if (net->rightmost->col <= column)
    { 				/* new pin belongs at the end of the list */
	/* Dont put in a duplicate */
	if (net->rightmost->col != column ||
	    net->rightmost->edge != this_edge)
	{
	    temp->right_list = NULL;
	    temp->left_list = net->rightmost;
	    net->rightmost->right_list = temp;
	    net->rightmost = temp;
	}
    }
    else			/* find location for new pin */
    {
	while (this_pin->col < column)
	    this_pin = this_pin->right_list;
	temp->right_list = this_pin;
	if (this_pin->left_list == NULL)
	{			/* this pin is first in list */

	    /* Dont put in duplicates */
	    if (this_pin->col != column ||
		this_pin->edge != this_edge)
	    {
	        temp->left_list = NULL;
	        temp->right_list = this_pin;
	        net->leftmost = temp;
	        this_pin->left_list = temp;
	    }
	}
	else
	{			/* this pin is in interior of list */
	    /* Dont put in duplicates */
	    if (this_pin->col != column ||
		this_pin->edge != this_edge)
	    {
	        temp->left_list = this_pin->left_list;
	        temp->right_list = this_pin;
	        this_pin->left_list->right_list = temp;
	        this_pin->left_list = temp;
	    }
	}
    }

      }



/***********************************************
 * Strip_zero_nets removes all zero nets from the edge list,
 * and updates num_edge_nets. 
 **************************************************/

void strip_zero_nets(edge_list, num_edge_nets)

INOUT NETPTR* edge_list;    	/* array of nets that exit the channel edge*/
INOUT int* num_edge_nets;	/* number in above list */

{
    int i;	/* loop counter */
    int j;	/* loop counter */

    for( i=1; i <= *num_edge_nets; i++)
    {
	if((edge_list[i]->name)==0)
	{
	     for( j=i; j < *num_edge_nets; j++)
		 edge_list[j] = edge_list[j+1];  /* Move the rest down one */
  	     (*num_edge_nets)--;   	/* Decrement the quantity of nets */
	     i--;	/* Look at net we just moved down. */
	}
    }
}
		 

/************************************************************
 * Strip_dup_nets removes duplicate instances of non-zero nets
 * from the edge lists. It moves the rest of the list down
 * like strip_zero_nets above.
 *********************************************************/

void strip_dup_nets(edge_list, num_edge_nets)

INOUT NETPTR* edge_list;    	/* array of nets that exit the channel edge*/
IN int* num_edge_nets;	/* number in above list */
{
    int i;
    int j;		/* Loop counters */
    int k;

    for (i=1; i < *num_edge_nets; i++)
    {
        for (j=i+1; j <= *num_edge_nets; j++)
        {
	    if (edge_list[i]->name == edge_list[j]->name &&
		edge_list[i]->name != 0)
	    {
	         for( k=j; k < *num_edge_nets; k++)
		     edge_list[k] = edge_list[k+1];  /* Move the rest down one */
  	         (*num_edge_nets)--;   	/* Decrement the quantity of nets */
	         j--;	/* Look at net we just moved down. */
	    }
        }
    }
}


/***********************************************
 * Strip_unique_nets removes all unique nets (those that
 * have no other pins) from the edge list,
 * and updates num_edge_nets. 
 **************************************************/

void strip_unique_nets(edge_list, num_edge_nets)

INOUT NETPTR* edge_list;    	/* array of nets that exit the channel edge*/
INOUT int* num_edge_nets;	/* number in above list */

{
    int i;	/* loop counter */
    int j;	/* loop counter */

    for( i=1; i <= *num_edge_nets; i++)
    {
	/* If there is only one pin in a net, the nets pin list
	pointers both point to it, and are equal */

	if(edge_list[i]->leftmost==edge_list[i]->rightmost)
	{
	     for( j=i; j < *num_edge_nets; j++)
		 edge_list[j] = edge_list[j+1];  /* Move the rest down one */
  	     (*num_edge_nets)--;   	/* Decrement the quantity of nets */
	     i--;	/* Look at net we just moved down. */
	}
    }
}
