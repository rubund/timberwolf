#ifndef lint
static char SccsId[] = "@(#) cycle.c version 5.1 7/28/89" ;
#endif

#include "mighty.h"
#define PATH 101
#define LATER 102

static int cyclecountS = 0;
extern int bkcycleG ;

NETPTR source;
NETPTR *stack = (NETPTR *)NULL;
int stack_size;
CYCLE_LIST cycles = (CYCLE_LIST)NULL;

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
 *
 *
 *******************************************************************/

NET_STACK break_cycle (cutcol)
int cutcol;  /* column number of guide pins */
{
    int i, j, k;		/* loop counter */
    NET_LIST_M traverse;	/* used to traverse parents list */
    int best_value;		/* the value of the best edge to remove
				   from a cycle */
    int best_index;		/* also refers to the best edge to remove */
    static int **reach = (int **)NULL;
				/* adjacency matrix used for transitive
				   closure of the graph, space is allocated
				   first time this routine is called */
    register int *rptr;         /* make initialization fast */
    EDGE_LIST edges;		/* list of edges that will be removed to
				   break all cycles */
    EDGE_LIST temp_edge;	/* used to allocat new space */
    EDGE_LIST trav_edge;	/* used to traverse edges list */
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

    void S_delcycle();
    NETPTR *S_allocatenetptr();
    int **S_allocatematrix ();
    EDGE_LIST S_getedge();
    void S_retedge();
    INT_LIST insert_int();


    /*
     *  initialize variables that are global within this file
     */

    if( cycles != (CYCLE_LIST)NULL )
	S_delcycle();

    /* allocate space for the stack */
    if( stack == (NETPTR *)NULL )
	stack = S_allocatenetptr( num_netsG );
    else
	for( i = 1; i <= num_netsG; i++ )
	    stack[i] = (NETPTR)NULL;
/*
    stack = (NETPTR *) alloc ((unsigned) num_netsG+1, sizeof (NETPTR));
*/
    stack_size = 1;

    /* local to this procedure */
    edges = (EDGE_LIST)NULL;
    if( reach == (int **)NULL )
    	reach = S_allocatematrix (num_netsG, num_netsG);
    else
	for( i = 1; i <= num_netsG; i++ ){
	    rptr = reach[i] ;
	    for( j = 1; j <= num_netsG; j++ ){
		rptr[j] = 0 ;
	    }
	}

    /*
     *  If a net has been leveled, mark it as NEVER available
     *  if it has not been leveled, mark it as YES available
     */

    for (i = 1; i <= num_netsG; i++)
    {
	net_arrayG[i].available = NEVER;
/*
	if (net_arrayG[i].leftmost != NULL)
*/
	{
	    for (traverse = net_arrayG[i].parents; traverse != (NET_LIST_M)NULL;
			traverse = traverse->next)
		if (traverse->marked == NO)
		    net_arrayG[i].available = YES;
	}
    }


    /*
     *  Find all cycles in the graph
     */

    if (ioformG == HUMAN )
	fprintf (output_fileG,
	    "The vertical constraint graph contains the following cycles:\n");

    for (i = 1; i <= num_netsG; i++)
	if (net_arrayG[i].available != NEVER)
	{
	    /* mark later nets as available */
	    for (j = i+1; j <= num_netsG; j++)
		if (net_arrayG[j].available != NEVER)
		    net_arrayG[j].available = YES;

	    source = net_arrayG + i;
	    find_cycle (net_arrayG + i);

	    /* j will be ignored here */
	    /* 
		j = find_cycle (net_arrayG + i);
		printf ("find_cycle(%d) says %d\n", 
		    number_to_name(i), j);
	    */

	    /* mark net i to be used later */
	    net_arrayG[i].available = LATER;
	}


    /*
     *  Find least costly edge from each cycle
     */

    for ( ; cycles != (CYCLE_LIST)NULL; cycles = cycles->next)
    {
	bkcycleG = YES;  /* for pin.c */

	for (this_edge = cycles->nets[1]->children;
	     this_edge->net != cycles->nets[2]; this_edge = this_edge->next);
	/*
	this_edge->break_value = 0;
	*/
	this_col = INFINITY;
	for (trav_col = this_edge->col_list; trav_col != (INT_LIST)NULL;
					trav_col = trav_col->next)
	    this_col = MIN( this_col, ABS(trav_col->value - cutcol) );

 	this_edge->break_value = this_col;

	best_value = this_edge->break_value;
	best_index = 1;

	for (i = 2; i <= cycles->size; i++)
	{
	    for (this_edge = cycles->nets[i]->children;
		this_edge->net != cycles->nets[i+1];
		this_edge = this_edge->next);

	    this_col = INFINITY;

	    for (trav_col = this_edge->col_list; trav_col != (INT_LIST)NULL;
					trav_col = trav_col->next)
	        this_col = MIN( this_col, ABS(trav_col->value - cutcol) );
 	    this_edge->break_value = this_col;

	    /* choose largest ( farthest ) column */
	    if (this_edge->break_value > best_value)
	    {
		best_value = this_edge->break_value;
		best_index = i;
	    }
	}

	/* make storage for this edge */
	/*
	temp_edge = (EDGE_LIST) alloc (1, sizeof (EDGE_ELEM));
	*/
	temp_edge = S_getedge();

	temp_edge->upper_net = cycles->nets[best_index];
	temp_edge->lower_net = cycles->nets[best_index+1];
	temp_edge->edge_cost = best_value;
	/* find edge with list of columns */
	for (this_edge = cycles->nets[best_index]->children;
	     this_edge->net != cycles->nets[best_index+1];
	     this_edge = this_edge->next);
	temp_edge->cols = this_edge->col_list;

	/* store this edge in 'edges' list */
	if ((edges == (EDGE_LIST)NULL) || (edges->edge_cost > best_value))
	{
	    temp_edge->next = edges;
	    edges = temp_edge;
	}
	else
	{
	    for (trav_edge = edges;
		 ((trav_edge->next != (EDGE_LIST)NULL) &&
			(trav_edge->next->edge_cost <= best_value));
		 trav_edge = trav_edge->next);
	    temp_edge->next = trav_edge->next;
	    trav_edge->next = temp_edge;
	}
    }

    /*
     *  Remove edges from graph
     */

    for (trav_edge = edges; trav_edge != (EDGE_LIST)NULL; trav_edge = trav_edge->next)
    {
	remove_edge (trav_edge->upper_net, trav_edge->lower_net);
    }


    /*
     *  Compute transitive closure
     */

    for (k = 1; k <= num_netsG; k++)
	if (net_arrayG[k].available == LATER)
	{
	    upper = k;
	    for (traverse = net_arrayG[upper].children; traverse != (NET_LIST_M)NULL;
			traverse = traverse->next)
	    {
		if (traverse->net->available == LATER)
		{
		    lower = traverse->net->name;
		    /* upper_net is above lower_net */
		    reach[upper][lower] = 1;
		    /* upper_net is above everybody lower_net is above */
		    for (i = 1; i <= num_netsG; i++)
			reach[upper][i] += reach[lower][i];
		    /* everybody above upper_net is above
		     * everybody below upper_net */
		    for (i = 1; i <= num_netsG; i++)
			if (reach[i][upper])
			    for (j = 1; j <= num_netsG; j++)
				reach[i][j] += reach[upper][j];
		}
	    }
	}


    /*
     *  Attempt to reinsert each edge (starting at most costly first)
     */

    for (trav_edge = edges; trav_edge != (EDGE_LIST)NULL; trav_edge = trav_edge->next)
	if (!(reach[trav_edge->lower_net->name][trav_edge->upper_net->name]))
	{
	    /* reinsert this edge into the graph */
	    insert_edge ((trav_edge->upper_net - net_arrayG),
		  (trav_edge->lower_net - net_arrayG),
			num_netsG, 0);  /* using 0 for column number
				          because it doesn't matter */

	    /* update transitive closure */
	    upper = trav_edge->upper_net->name;
	    lower = trav_edge->lower_net->name;
	    if (ioformG == HUMAN )
		fprintf (output_fileG, "replacing edge from %d to %d\n",
			number_to_name(upper), number_to_name(lower));
	    /* upper_net is above lower_net */
	    reach[upper][lower] = 1;
	    /* upper_net is above everybody lower_net is above */
	    for (i = 1; i <= num_netsG; i++)
		reach[upper][i] += reach[lower][i];
	    /* everybody above upper_net is above
	     * everybody below upper_net */
	    for (i = 1; i <= num_netsG; i++)
		if (reach[i][upper])
		    for (j = 1; j <= num_netsG; j++)
			reach[i][j] += reach[upper][j];
	}
	else
	{
	    /* add this edges columns to Cycle_cols list */
	    while (trav_edge->cols != (INT_LIST)NULL)
	    {
		Cycle_colsG = insert_int (Cycle_colsG, trav_edge->cols->value);
		trav_edge->cols = trav_edge->cols->next;
	    }
	}


    /*
     *  build net stack to return
     */

    net_stack = (NET_STACK)NULL;
    for (trav_edge = edges; trav_edge != (EDGE_LIST)NULL; trav_edge = trav_edge->next)
    {
 	process = YES;
	for (traverse = trav_edge->lower_net->parents; traverse != (NET_LIST_M)NULL;
			traverse = traverse->next)
	    if (traverse->marked == NO)
		process = NO;

	/* make sure this nets has not been put on stack yet */
	for (temp_net_stack = net_stack; temp_net_stack != (NET_STACK)NULL;
			temp_net_stack = temp_net_stack->next)
	    if (temp_net_stack->net == trav_edge->lower_net)
		process = NO;

	if (process == YES)
	{
	    push_net (&net_stack, trav_edge->lower_net);
	}
    }

    if (net_stack == (NET_STACK)NULL)
    {
	fprintf (output_fileG, "oops, no nets in stack\n");
	YexitPgm(1);
    }

    /*
     *  clear edges
     */
    while( (trav_edge = edges) != (EDGE_LIST)NULL )
    {
	edges = edges->next;
	S_retedge( trav_edge );
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
 *
 *******************************************************************/

void remove_edge (upper_net, lower_net)
NETPTR upper_net;		/* one-half of the edge to be deleted */
NETPTR lower_net;		/* child net of the edge to be deleted */

{
    NET_LIST_M this_edge,	/* used to traverse the lists of 'relatives'*/
	     previous_edge;	/* the edge which preceeds this_edge in the
				   list */
    INT_LIST thislist;

    if (ioformG == HUMAN )
	fprintf (output_fileG, "Removing edge from net %d to net %d\n",
			 number_to_name(upper_net->name),
			 number_to_name(lower_net->name));

    if (upper_net->children == (NET_LIST_M)NULL)
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
	if (ioformG == HUMAN )
	{
	    fprintf (output_fileG, "Affected columns are: ");
	    for ( ; this_edge->col_list != (INT_LIST)NULL;
			this_edge->col_list = this_edge->col_list->next)
	    {
		fprintf (output_fileG, " %d", this_edge->col_list->value);
	    }
	    fprintf (output_fileG, "\n");
	    while( (thislist = this_edge->col_list) != (INT_LIST)NULL )
	    {
		this_edge->col_list = thislist->next;
		free( thislist );
	    }
	}
	upper_net->children = upper_net->children->next;
	free( this_edge );
    }
    else
    {
	previous_edge = upper_net->children;
	this_edge = previous_edge->next;
	if (this_edge == (NET_LIST_M)NULL)
	    return;
	while (this_edge->net != lower_net)
	{
	    previous_edge = this_edge;
	    this_edge = this_edge->next;
	    if (this_edge == (NET_LIST_M)NULL)
		return;
	}
	previous_edge->next = this_edge->next;
	if (ioformG == HUMAN )
	{
	    fprintf (output_fileG, "Affected columns are: ");
	    for ( ; this_edge->col_list != (INT_LIST)NULL;
			this_edge->col_list = this_edge->col_list->next)
		fprintf (output_fileG, " %d", this_edge->col_list->value);
	    fprintf (output_fileG, "\n");
	    while( (thislist = this_edge->col_list) != (INT_LIST)NULL )
	    {
		this_edge->col_list = thislist->next;
		free( thislist );
	    }
	}
	free( this_edge );
    }

    /*
     *  find and remove up_edge in lower_net's parents list
     */

    if (lower_net->parents->net == upper_net)  /* then delete first edge in
					          the list */
    {
	this_edge = lower_net->parents;
	lower_net->parents = lower_net->parents->next;
	free( this_edge );
    }
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
	free( this_edge );
    }
}



/**********************************************************
 *
 *  find_cycle recursively detects cycles whose lowest numbered
 *  node is 'source'.
 *  
 ***********************************************************/

int find_cycle (this_node)
NETPTR this_node;		/* current spot in the recursion */
{
    int part_of_cycle;		/* a flag */
    NET_LIST_M trav;		/* used to traverse list of children of
				   this_node */
    int i;			/* loop counter */
    CYCLE_LIST hold_cycle;	/* used to allocate storage for newly found
				   cycle */
    CYCLE_LIST S_getcycle();
    NETPTR *S_allocatenetptr();

    /* set things up */
    part_of_cycle = NO;
    stack[stack_size++] = this_node;
    this_node->available = PATH;

    for (trav = this_node->children; trav != (NET_LIST_M)NULL; trav = trav->next)
    {
	if (trav->net->available == YES)
	{
	    if (find_cycle (trav->net) == YES ) 
		part_of_cycle = YES;
	}
	else if (trav->net == source)
	{
	    this_node->available = YES;
	    part_of_cycle = YES;
	    /*
	    hold_cycle = (CYCLE_LIST) alloc (1, sizeof (CYCLE_ELEM));
	    hold_cycle->nets = (NETPTR *) alloc ((unsigned) stack_size+1,
						sizeof (NETPTR));
	    */
	    hold_cycle = S_getcycle();
	    hold_cycle->nets = S_allocatenetptr(stack_size);

	    hold_cycle->size = stack_size-1;
	    for (i = 1; i < stack_size; i++)
		hold_cycle->nets[i] = stack[i];
	    hold_cycle->nets[stack_size] = stack[1];
	    hold_cycle->next = cycles;
	    cycles = hold_cycle;

	    cyclecountS++;

	    /* print out the cycle */
	    if (ioformG == HUMAN )
	    {
		for (i = 1; i < stack_size; fprintf (output_fileG,
				"%d -> ", number_to_name(stack[i++]->name)));
		fprintf (output_fileG, "%d\n", number_to_name(stack[1]->name));
		if (stack_size > num_netsG) {
	   	  fprintf (output_fileG,"stack overflow:find_cyle()\n");
		  YexitPgm(1);
		  }
	    }
	}
	else if (trav->net->available == PATH)
	{
	    part_of_cycle = NO; 
	}
    }

    stack_size--;

    if (part_of_cycle != YES)
	this_node->available = NO;

    return (part_of_cycle);
}


S_delcycle()
{
    CYCLE_LIST tmpcycle;
    void S_retcycle();

    while( (tmpcycle = cycles) != (CYCLE_LIST)NULL )
    {
	cycles = cycles->next;
	free( tmpcycle->nets );
	S_retcycle( tmpcycle );
    }
}



void S_cleargraph()
{
    NET_LIST_M this_edge;	/* used to traverse the lists of 'relatives'*/
    INT_LIST thislist;
    int i;

    for( i = 1; i <= num_netsG; i++ )
    {
        /*
         *  find and remove down_edge in upper_net's children list
         */
	while( (this_edge = net_arrayG[i].children) != (NET_LIST_M)NULL )
	{
	    while( (thislist = this_edge->col_list) != (INT_LIST)NULL )
	    {
		this_edge->col_list = thislist->next;
		free( thislist );
	    }
	    net_arrayG[i].children = this_edge->next;
	    free( this_edge );
        }
	while( (this_edge = net_arrayG[i].parents) != (NET_LIST_M)NULL )
	{
	    net_arrayG[i].parents = this_edge->next;
	    free( this_edge );
	}
    }
}
