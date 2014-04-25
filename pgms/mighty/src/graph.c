#ifndef lint
static char SccsId[] = "@(#) graph.c version 6.2 12/27/90" ;
#endif

#include "mighty.h"


/******************************************************************
 *
 *  build_graph is responsible for constructing the vertical constraint
 *  graph, breaking cycles in the graph, and calculating level_from_top
 *  and level_from_bottom for each net.  build_graph calls make_graph
 *  to construct the full graph, and level_graph to break the cycles and
 *  find levels for the nets.
 *
 *******************************************************************/

/**********************************************************************
 *
 *  make_graph constructs the vertical constraint graph.  There was no
 *  attempt to remove cycles from the graph in this routine.  make_graph
 *  calls insert_edge to actually construct an edge in the graph.
 *
 *********************************************************************/

void S_makegraph (fromcol, tocol)
int fromcol,
    tocol;
{
    int col,
	row;			/* loop counter */
    int lowernet;
    int uppernet;
    int oldcol ;                /* used to determine new column */
    PIN_LISTPTR curpin ;        /* current pin in list of third layer pins */

    /*
     *  insert graph edges caused by pins on hlayer
     */
    /*
    for( col = fromcol; col <= tocol; col++ ) {
	lowernet = 0;
	uppernet = 0;

	for( row = 1; row <= num_rows; row++ ) {
	    if( hlayer[row][col] > num_nets ) {
		lowernet = 0;
		uppernet = 0;
	    }
	    if( playerh[row][col] > 0 ) {
		if( uppernet != 0 ) {
		    lowernet = playerh[row][col];
	            insert_edge (uppernet, lowernet, num_nets, col);
		    uppernet = lowernet;

		} else {
		    uppernet = playerh[row][col];
		}
	    }
	}
    }
    */

    /*
     *  insert graph edges caused by pins on vlayer
     */
    for( col = 1; col <= num_colsG; col++ ) {
	uppernet = 0;

	for( row = 1; row <= num_rowsG; row++ ) {
	    /* if outside of channel, reset */
	    if( vlayerG[row][col] > num_netsG ) {
		uppernet = 0;
	    }
	    if( playervG[row][col] > 0 ) {
		if( uppernet != 0 ) {
		    lowernet = playervG[row][col];
	            insert_edge (uppernet, lowernet, num_netsG, col);
		    uppernet = lowernet;
		} else {
		    uppernet = playervG[row][col];
		}
	    }
	}
    }

    /*
     *  insert graph edges caused by pins on third layer poly
     *  pins have been sorted previously in pins.c.  Note that
     *  row 1 is at top of channel so pins are sorted in increasing
     *  x and decreasing y to be consistent with above code.
     */

     /* commented out layer 3 vertical contraints 10/89 RAWeier. */
/*    oldcol = 0 ;
    for( curpin = two5pinsG; curpin ; curpin = curpin->next ){
	col = curpin->pin->x ;

	if( oldcol == col ){
	    insert_edge (uppernet, curpin->net, num_netsG, col);
	}
	oldcol = col ;
	uppernet = curpin->net ;

    } */


/*
    if (place_relative == LEFT || place_fixed == LEFT)
	for (i = 1; i < num_left_nets; i++)
	    insert_edge (left[i], left[i+1], num_nets, 0);
*/

    /*
     *  insert graph edges caused by nets entering channel from right
     */

/*
    if (place_relative == RIGHT || place_fixed == RIGHT)
	for (i = 1; i < num_right_nets; i++)
	    insert_edge (right[i], right[i+1], num_nets, num_cols+1);
*/

    /*
     *  insert graph edges for body of channel
     */

/*
    for (i = 1; i <= num_cols; i++)
    	insert_edge (top[i], bottom[i], num_nets, i);
*/
}



/*******************************************************************
 *
 *  insert_edge updates the 'parents' and 'children' lists in the NET
 *  structures to indicate the upper_net is a parent of lower_net, and
 *  lower_net is a child of upper_net.
 *
 *******************************************************************/

void insert_edge (uppernet, lowernet, num_nets, column)
int uppernet,		/* inserted edge will indicate that upper_net
				   should be placed above lower_net */
    lowernet;
int num_nets;		/* number of nets in the channel */
int column;			/* column in the channel that this edge is
				   related to, this is only used when this
				   edge would close a cycle */
{
    NET_LIST_M list,		/* used to allocate space for new elements
				   inserted into parents and children lists */
	     traverse;		/* used to traverse upper_net's children list
				   to make sure edge does not already exist */
    INT_LIST temp_int_list;	/* used to allocate element in list of
				   columns that cause an edge */


    /*
     *  don't make an edge from a net to itself
     */

    if (uppernet == lowernet)
	return;

    /*
     *  if the edge already exists, don't make another one,
     *  but add this column to the list of columns causing this edge
     */

    for (traverse = net_arrayG[uppernet].children; traverse != (NET_LIST_M)NULL;
			traverse = traverse->next)
	if (traverse->net == net_arrayG + lowernet)
	{
	    temp_int_list = (INT_LIST) alloc (1, sizeof (INT_LIST_ELEMENT));
	    temp_int_list->value = column;
	    temp_int_list->next = traverse->col_list;
	    traverse->col_list = temp_int_list;
	    return;
	}

    /*
     *  tell uppernet that lower_net is its child
     */

    list = (NET_LIST_M) alloc (1, sizeof (NET_LIST_ELEMENT_M));
    list->net = net_arrayG + lowernet;
    list->marked = NO;
    list->next = net_arrayG[uppernet].children;
    list->col_list = (INT_LIST) alloc (1, sizeof(INT_LIST_ELEMENT));
    list->col_list->next = (INT_LIST)NULL;
    list->col_list->value = column;
    net_arrayG[uppernet].children = list;

    /*
     *  tell lower_net that upper_net is its parent
     */

    list = (NET_LIST_M) alloc (1, sizeof (NET_LIST_ELEMENT_M));
    list->net = net_arrayG + uppernet;
    list->marked = NO;
    list->next = net_arrayG[lowernet].parents;
    /* make col_list physically the same as above */
    list->col_list = (net_arrayG[uppernet].children)->col_list;
    net_arrayG[lowernet].parents = list;
}


