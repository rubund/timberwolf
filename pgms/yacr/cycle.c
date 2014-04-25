#include "copyright.h"
#include "yacr.h"

#define PATH 101
#define LATER 102

NETPTR source;
NETPTR *stack;
int stack_size;
CYCLE_LIST cycles;

/********************************************************************
 *
 *  break_cycle breaks cycles in the vertical constraint graph by
 *  removing edges.  Currently, the alrogithm for finding a 'good'
 *  edge to remove is quite primitive:  (a) find a net with only
 *  one (or minimum number of) unmarked parents; (b) remove the edges
 *  between that net and its unmarked parents.  It would almost definitely
 *  be better to attempt to remove an edge that does not increase the
 *  level_from_top or level_from_bottom of any net.
 *  break_cycle returns a pointer to the net which has all unmarked pointers
 *  to parents deleted.  This tells the calling routine how the net has
 *  been treated.
 *
 *  Author: Jim Reed
 *
 *  Date: 3-21-84
 *
 *******************************************************************/

NET_STACK break_cycle (net_array, num_nets, top, bottom, num_cols)
INOUT NETPTR net_array;		/* array containing all the net data
				   structures */
IN int num_nets;		/* size of net_array */
IN NETPTR top[];		/* array of pointers to nets on top of the
				   channel */
IN NETPTR bottom[];		/* nets on bottom of the channel */
IN int num_cols;		/* size of top[] and bottom[] */
{
    int i, j, k;		/* loop counter */
    NET_LIST_M traverse;	/* used to traverse parents list */
    int best_value;		/* the value of the best edge to remove
				   from a cycle */
    int best_index;		/* also refers to the best edge to remove */
    EDGE_LIST edges;		/* list of edges that will be removed to
				   break all cycles */
    EDGE_LIST temp_edge;	/* used to allocate new space */
    EDGE_LIST trav_edge;	/* used to traverse edges list */
    static int **reach = NULL;	/* adjacency matrix used for transitive
				   closure of the graph, space is allocated
				   first time this routine is called */
    int upper, lower;		/* upper_net->name, and lower_net->name
				   while building transitive closure */
    NET_LIST_M this_edge;	/* used to traverse list of children of a net
				   */
    INT_LIST trav_col;		/* used to traverse list of columns an edge
				   is related to */
    int this_col;		/* column being worked on */
    NET_STACK net_stack;	/* the stack of nets that is returned */
    NET_STACK temp_net_stack;	/* used to traverse net_stack */
    int process;		/* a flag */


    /*
     *  initialize variables that are global within this file
     */

    cycles = NULL;
    /* allocate space for the stack */
    stack = ALLOC(NETPTR, num_nets + 1);
    stack_size = 1;

    /* local to this procedure */
    edges = NULL;
    reach = allocate_matrix (num_nets);

    /*
     *  If a net has been leveled, mark it as NEVER available
     *  if it has not been leveled, mark it as YES available
     */

    for (i = 1; i <= num_nets; i++)
    {
	net_array[i].available = NEVER;
	if (net_array[i].leftmost != NULL)
	{
	    for (traverse = net_array[i].parents; traverse != NULL;
			traverse = traverse->next)
		if (traverse->marked == NO)
		    net_array[i].available = YES;
	}
    }


    /*
     *  Find all cycles in the graph
     */

    if (ioform == HUMAN && printcycles == YES)
	(void) fprintf (output_file,
	    "The vertical constraint graph contains the following cycles:\n");

    for (i = 1; i <= num_nets; i++)
    /* beards: added NULL check */
	if ((net_array[i].leftmost != NULL) && 
	    (net_array[i].available != NEVER))
	{
	    /* mark later nets as available */
	    for (j = i+1; j <= num_nets; j++)
		if (net_array[j].available != NEVER)
		    net_array[j].available = YES;

	    source = net_array + i;
	    /* j will be ignored here */
	    j = find_cycle (net_array + i);

/* 	(void) printf ("find_cycle(%d) says \n", number_to_name(i), j); */

	    /* mark net i to be used later */
	    net_array[i].available = LATER;
	}


    /*
     *  Find least costly edge from each cycle
     */

    for ( ; cycles != NULL; cycles = cycles->next)
    {
	for (this_edge = cycles->nets[1]->children;
	     this_edge->net != cycles->nets[2]; this_edge = this_edge->next);
	this_edge->break_value = 0;
	for (trav_col = this_edge->col_list; trav_col != NULL;
					trav_col = trav_col->next)
	{
	    this_col = trav_col->value;
	    if ((this_col != 0) && (this_col != num_cols+1))
		for (i = this_col - 1; i <= this_col + 1; i += 2)
		    if ((i >= 1) && (1 <= num_cols))
			if (number_to_name (top[this_col]->name) != 0)
			    if (number_to_name (bottom[this_col]->name) != 0)
				this_edge->break_value += HIGH;
			    else
				this_edge->break_value += MED;
			else
			    if (number_to_name (bottom[this_col]->name) != 0)
				this_edge->break_value += MED;
			    else
				this_edge->break_value += LOW;
		    else
			this_edge->break_value += HIGH;
	    else
		this_edge->break_value += INFINITY;
	}
	best_value = this_edge->break_value;
	best_index = 1;

	for (i = 2; i <= cycles->size; i++)
	{
	    for (this_edge = cycles->nets[i]->children;
		this_edge->net != cycles->nets[i+1];
		this_edge = this_edge->next);
	    this_edge->break_value = 0;
	    for (trav_col = this_edge->col_list; trav_col != NULL;
					trav_col = trav_col->next)
	    {
		this_col = trav_col->value;
		if ((this_col != 0) && (this_col != num_cols+1))
		    for (j = this_col - 1; j <= this_col + 1; j += 2)
		    {
			if ((j >= 1) && (j <= num_cols))
			    if (number_to_name (top[j]->name) != 0)
				if (number_to_name(bottom[j]->name)!=0)
				    this_edge->break_value += HIGH;
				else
				    this_edge->break_value += MED;
			    else
				if (number_to_name(bottom[j]->name)!=0)
				    this_edge->break_value += MED;
				else
				    this_edge->break_value += LOW;
			else
			    this_edge->break_value += HIGH;
		    }
		else
		    this_edge->break_value += INFINITY;
	    }
	    if (this_edge->break_value < best_value)
	    {
		best_value = this_edge->break_value;
		best_index = i;
	    }
	}

	/* make storage for this edge */
	temp_edge = ALLOC(EDGE_ELEM, 1);
	temp_edge->upper_net = cycles->nets[best_index];
	temp_edge->lower_net = cycles->nets[best_index+1];
	temp_edge->edge_cost = best_value;
	/* find edge with list of columns */
	for (this_edge = cycles->nets[best_index]->children;
	     this_edge->net != cycles->nets[best_index+1];
	     this_edge = this_edge->next);
	temp_edge->cols = this_edge->col_list;

	/* store this edge in 'edges' list */
	if ((edges == NULL) || (edges->edge_cost < best_value))
	{
	    temp_edge->next = edges;
	    edges = temp_edge;
	}
	else
	{
	    for (trav_edge = edges;
		 ((trav_edge->next != NULL) &&
			(trav_edge->next->edge_cost >= best_value));
		 trav_edge = trav_edge->next);
	    temp_edge->next = trav_edge->next;
	    trav_edge->next = temp_edge;
	}
    }

    /*
     *  Remove edges from graph
     */

    for (trav_edge = edges; trav_edge != NULL; trav_edge = trav_edge->next)
    {
	remove_edge (trav_edge->upper_net, trav_edge->lower_net);
    }


    /*
     *  Compute transitive closure
     */

    for (k = 1; k <= num_nets; k++)
    /* beards: added NULL check */
	if ((net_array[k].leftmost != NULL) && 
	    (net_array[k].available == LATER))
	{
	    upper = k;
	    for (traverse = net_array[upper].children; traverse != NULL;
			traverse = traverse->next)
	    {
		if (traverse->net->available == LATER)
		{
		    lower = traverse->net->name;
		    /* upper_net is above lower_net */
		    reach[upper][lower] = 1;
		    /* upper_net is above everybody lower_net is above */
		    for (i = 1; i <= num_nets; i++)
			reach[upper][i] += reach[lower][i];
		    /* everybody above upper_net is above
		     * everybody below upper_net */
		    for (i = 1; i <= num_nets; i++)
			if (reach[i][upper])
			    for (j = 1; j <= num_nets; j++)
				reach[i][j] += reach[upper][j];
		}
	    }
	}


    /*
     *  Attempt to reinsert each edge (starting at most costly first)
     */

    for (trav_edge = edges; trav_edge != NULL; trav_edge = trav_edge->next)
	if (!(reach[trav_edge->lower_net->name][trav_edge->upper_net->name]))
	{
	    /* reinsert this edge into the graph */
	    insert_edge (trav_edge->upper_net, trav_edge->lower_net,
				num_nets, 0);  /* using 0 for column number
					          because it doesn't matter */

	    /* update transitive closure */
	    upper = trav_edge->upper_net->name;
	    lower = trav_edge->lower_net->name;
	    if (ioform == HUMAN && printcycles == YES)
		(void) fprintf (output_file, "replacing edge from %d to %d\n",
			number_to_name(upper), number_to_name(lower));
	    /* upper_net is above lower_net */
	    reach[upper][lower] = 1;
	    /* upper_net is above everybody lower_net is above */
	    for (i = 1; i <= num_nets; i++)
		reach[upper][i] += reach[lower][i];
	    /* everybody above upper_net is above
	     * everybody below upper_net */
	    for (i = 1; i <= num_nets; i++)
		if (reach[i][upper])
		    for (j = 1; j <= num_nets; j++)
			reach[i][j] += reach[upper][j];
	}
	else
	{
	    /* add this edges columns to Cycle_cols list */
	    while (trav_edge->cols != NULL)
	    {
		Cycle_cols = insert_int (Cycle_cols, trav_edge->cols->value);
		trav_edge->cols = trav_edge->cols->next;
	    }
	}


    /*
     *  build net stack to return
     */

    net_stack = NULL;
    for (trav_edge = edges; trav_edge != NULL; trav_edge = trav_edge->next)
    {
 	process = YES;
	for (traverse = trav_edge->lower_net->parents; traverse != NULL;
			traverse = traverse->next)
	    if (traverse->marked == NO)
		process = NO;

	/* make sure this nets has not been put on stack yet */
	for (temp_net_stack = net_stack; temp_net_stack != NULL;
			temp_net_stack = temp_net_stack->next)
	    if (temp_net_stack->net == trav_edge->lower_net)
		process = NO;

	if (process == YES)
	{
	    push_net (&net_stack, trav_edge->lower_net);
	}
    }

    if (net_stack == NULL)
    {
	(void) fprintf (output_file, "oops, no nets in stack\n");
	exit(1);
    }

    return (net_stack);
}



/*******************************************************************
 *
 *  remove_edge deletes an edge from the vertical constraint graph.
 *  The edge is completely defined by lower_net (the child) and upper_net
 *  (the parent).  upper_net's children list is
 *  searched to find down_edge, the pointer to lower_net.  down_edge is
 *  deleted from upper_net's children list.  up_edge is deleted from
 *  lower_nets parents list.
 *
 *  Author: Jim Reed
 *
 *  Date: 3-21-84
 *  Modified:12-7-84  Return properly if edge not in graph
 *
 *******************************************************************/

void remove_edge (upper_net, lower_net)
INOUT NETPTR upper_net;		/* one-half of the edge to be deleted */
INOUT NETPTR lower_net;		/* child net of the edge to be deleted */

{
    NET_LIST_M this_edge,	/* used to traverse the lists of 'relatives'*/
	     previous_edge;	/* the edge which preceeds this_edge in the
				   list */

    if (ioform == HUMAN && printcycles == YES)
	(void) fprintf (output_file, "Removing edge from net %d to net %d\n",
			 number_to_name(upper_net->name),
			 number_to_name(lower_net->name));

    if (upper_net->children == NULL)
	return;

    /*
     *  make upper_net's level_from_bottom at least 2, and lower_net's
     *  level_from_top at least 2, this will keep them from being placed
     *  on the top or bottom of the channel were the VCV will be hard to
     *  deal with
     */
    if (lower_net->level_from_top < 2)
	lower_net->level_from_top = 2;
    if (upper_net->level_from_bottom < 2)
	upper_net->level_from_bottom = 2;

    /*
     *  find and remove down_edge in upper_net's children list
     */

    if (upper_net->children->net == lower_net)  /* then delete first edge in
					          the list */
    {
	this_edge = upper_net->children;
	if (ioform == HUMAN && printcycles == YES)
	{
	    (void) fprintf (output_file, "Affected columns are: ");
	    for ( ; this_edge->col_list != NULL;
			this_edge->col_list = this_edge->col_list->next)
		(void) fprintf (output_file, " %d", this_edge->col_list->value);
	    (void) fprintf (output_file, "\n");
	}
	upper_net->children = upper_net->children->next;
    }
    else
    {
	previous_edge = upper_net->children;
	this_edge = previous_edge->next;
	if (this_edge == NULL)
	    return;
	while (this_edge->net != lower_net)
	{
	    previous_edge = this_edge;
	    this_edge = this_edge->next;
	    if (this_edge == NULL)
		return;
	}
	previous_edge->next = this_edge->next;
	if (ioform == HUMAN && printcycles == YES)
	{
	    (void) fprintf (output_file, "Affected columns are: ");
	    for ( ; this_edge->col_list != NULL;
			this_edge->col_list = this_edge->col_list->next)
		(void) fprintf (output_file, " %d", this_edge->col_list->value);
	    (void) fprintf (output_file, "\n");
	}
    }

    /*
     *  find and remove up_edge in lower_net's parents list
     */

    if (lower_net->parents->net == upper_net)  /* then delete first edge in
					          the list */
	lower_net->parents = lower_net->parents->next;
    else
    {
	previous_edge = lower_net->parents;
	this_edge = previous_edge->next;
	while (this_edge->net != upper_net)
	{
	    previous_edge = this_edge;
	    this_edge = this_edge->next;
	}
	previous_edge->next = this_edge->next;
    }
}



/**********************************************************
 *
 *  find_cycle recursively detects cycles whose lowest numbered
 *  node is 'source'.
 *  
 *  Author: Jim Reed
 *  
 *  Date: 12-4-84
 *  
 ***********************************************************/

int find_cycle (this_node)
IN NETPTR this_node;		/* current spot in the recursion */
{
    int part_of_cycle;		/* a flag */
    NET_LIST_M trav;		/* used to traverse list of children of
				   this_node */
    int i;			/* loop counter */
    CYCLE_LIST hold_cycle;	/* used to allocate storage for newly found
				   cycle */

    /* set things up */
    part_of_cycle = NO;
    stack[stack_size++] = this_node;
    this_node->available = PATH;

    for (trav = this_node->children; trav != NULL; trav = trav->next)
    {
	if (trav->net->available == YES)
	{
	    switch (find_cycle (trav->net)) {
	    case YES:
		part_of_cycle = YES;
		break;
	    case MAYBE:
		if (part_of_cycle == NO)
		    part_of_cycle = MAYBE;
		break;
	    }
	}
	else if (trav->net == source)
	{
	    this_node->available = YES;
	    part_of_cycle = YES;
	    hold_cycle = ALLOC(CYCLE_ELEM, 1);
	    hold_cycle->nets = ALLOC(NETPTR, stack_size + 1);
	    hold_cycle->size = stack_size-1;
	    for (i = 1; i < stack_size; i++)
		hold_cycle->nets[i] = stack[i];
	    hold_cycle->nets[stack_size] = stack[1];
	    hold_cycle->next = cycles;
	    cycles = hold_cycle;

	    cyclecount++;

	    /* print out the cycle */
	    if (ioform == HUMAN && printcycles == YES)
	    {
		for (i = 1; i < stack_size; i++)
		    (void) fprintf (output_file,
				    "%d -> ", number_to_name(stack[i]->name));
		(void) fprintf (output_file, "%d\n", number_to_name(stack[1]->name));
	    }
	}
	else if (trav->net->available == PATH)
	{
	    if (part_of_cycle == NO)
	    {
		part_of_cycle = MAYBE;
	    }
	}
    }

    stack_size--;
    switch (part_of_cycle) {
    case YES:
    case MAYBE:
	this_node->available = YES;
	break;
    case NO:
	this_node->available = NO;
	break;
    }
    return (part_of_cycle);
}
