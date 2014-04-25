#ifndef lint
static char SccsId[] = "@(#)find_subgraph.c	Yale Version 2.3 5/16/91";
#endif
/* -----------------------------------------------------------------

	FILE:		find_subgraph.c
	AUTHOR:		Dahe Chen
	DATE:		Sat Feb 11 22:37:00 EDT 1990
	CONTENTS:	find_pin_complete_graph()
			find_complete_spanning_tree()
			find_subgraph_from_spanning_tree()
	REVISION:
		Fri Jan 11 11:23:49 EST 1991
	    Allocate memory for dad and val to the maximum of
	    totedges and totnodes.

----------------------------------------------------------------- */

#include <define.h>
#include <gg_router.h>

void
find_pin_complete_graph()
{

    register int i;
    register int j;
    register int v1;
    register int v2;

    darray = (int **) Ysafe_malloc((numpins+1) * sizeof(int *));

    for (i = 1; i <= numpins ; i++)
    {
	darray[i] = (int *) Ysafe_malloc((numpins+1) * sizeof(int));
    }

    if (EQUIVAL == TRUE)
    {
	/***********************************************************
	* Construct the complete graph spanned by the pins. The
	* weight on each edge is equal to the distance of the
	* shortest path between the two pins, but is set to be
	* one if two pins are equivalent in order to have the
	* minimum spanning tree algorithm work correctly.
	***********************************************************/
	for (i = 1; i <= numpins ; i++)
	{
	    v1 = numnodes + i;
	    for (j = i; j <= numpins ; j++)
	    {
		if (parray[i]->equiv
		 && parray[i]->equiv == parray[j]->equiv)
		{
		    /*****************************************************
		    * Assign the weight between equivalent pins to be one.
		    *****************************************************/
		    if (i == j)
		    {
			darray[i][j] =
			darray[j][i] = 0;
		    }
		    else
		    {
			darray[i][j] =
			darray[j][i] = 1;
		    }
		}
		else
		{
		    /*****************************************************
		    * Assign the weight between two pins to be the
		    * distance between the two pins.
		    *****************************************************/
		    v2 = numnodes + j;
		    darray[i][j] =
		    darray[j][i] = garray[v1]->tree[v2]->dist;
		}
	    }
	}
    }
    else
    {
	/***********************************************************
	* Construct the complete graph spanned by the pins. The
	* weight on each edge is equal to the distance of the short-
	* est path between the two endpoints of the pin.
	***********************************************************/
	for (i = 1; i <= numpins ; i++)
	{
	    v1 = numnodes + i;
	    for (j = i; j <= numpins ; j++)
	    {
		/*********************************************************
		* Assign the weight between two pins to be the distance
		* between the two pins.
		*********************************************************/
		v2 = numnodes + j;
		darray[i][j] =
		darray[j][i] = garray[v1]->tree[v2]->dist;
	    }
	}
    }

} /* end of find_pin_complete_graph */

/* ==================================================================== */

void
find_complete_spanning_tree()
{

    register int i;
    register int j;
    register int min;
    register int unseen;

    /***********************************************************
    * Find  the minimum spanning tree for the complete graph.
    * Algorithm is from the book "Algorithms" by Robert
    * Sedgewick, 2nd Edition. P. 466.
    ***********************************************************/
    i = MAX(totedges, totnodes);
    val = (int *) Ysafe_malloc((i + 1) * sizeof(int));
    dad = (int *) Ysafe_malloc((i + 1) * sizeof(int));

    unseen = INT_MAX - 3;

    for (i = 1; i <= numpins ; i++)
    {
	val[i] = - unseen;
	dad[i] = 0;
    }

    val[0] = - (unseen+1);
    min = 1;

    do
    {
	i = min;
	val[i] = - val[i];
	min = 0;
	if (val[i] == unseen)
	{
	    val[i] = 0;
	}
	for (j = 1; j <= numpins ; j++)
	{
	    if (val[j] < 0)
	    {
		if (darray[i][j] && val[j] < - darray[i][j])
		{
		    val[j] = - darray[i][j];
		    dad[j] = i;
		}
		if (val[j] > val[min])
		{
		    min = j;
		}
	    }
	}
    } while(min);

} /* end of complete_spanning_tree */

/* ==================================================================== */

int
find_subgraph_from_spanning_tree()
{

    register int i;
    register int v1;
    register int v2;
    register int e;
    register int n;

    /***********************************************************
    * Construct a subgraph of the original graph by replacing
    * each edge in the minimum spanning tree just found above
    * with the corresponding shourtest path in the original graph.
    *
    * Note that field numpins in earray is used to indicate if
    * the edge is in the minimum spanning tree in this function.
    *
    * In the case that there exists equivalent pins, this
    * function will detect pins which are equivalent to some
    * other pins and which are leaves in the minimum spanning
    * tree; and delete them from the minimum spanning tree
    * since they don't contribute anything to the first minimum
    * Steiner tree.
    ***********************************************************/
    n = 0;
    if (EQUIVAL == FALSE)
    {
	/***********************************************************
	* Label all the vertices and the edges which are in the
	* minimum spanning tree of the pins. Count the number of
	* the edges in the minimum spanning tree and save the edge
	* indices in array val.
	***********************************************************/
	for (i = 1; i <= numpins ; i++)
	{
	    v1 = numnodes + i;
	    garray[v1]->status = LABEL;
	    if (!dad[i])
	    {
		continue;
	    }
	    v2 = numnodes + dad[i];
	    while (v2 != v1)
	    {
		garray[v1]->status = LABEL;
		e = garray[v2]->tree[v1]->edge;
		if (!earray[e]->numpins)
		{
		    earray[e]->numpins = LABEL;
		    val[++n] = e;
		}
		v1 = garray[v2]->tree[v1]->parent;
	    }
	}
    }
    else
    {
	/***********************************************************
	* Label all the vertices and the edges which are in the
	* minimum spanning tree of the pins. Count the number of
	* the edges in the minimum spanning tree and save the edge
	* indices in array val.
	* However, we now have equivalent pins in the net. The edges
	* between two equivalent pins will be discarded.
	***********************************************************/
	for (i = 1; i <= numpins ; i++)
	{
	    v1 = numnodes + i;
	    garray[v1]->status = LABEL;
	    if (!dad[i])
	    {
		continue;
	    }
	    if (parray[i]->equiv &&
		 parray[i]->equiv == parray[dad[i]]->equiv)
	    {
		/*********************************************************
		* Jump over for equivalent pins since there are no
		* explicit channels between the equivalent pins.
		*********************************************************/
		continue;
	    }
	    v2 = numnodes + dad[i];
	    while (v2 != v1)
	    {
		garray[v1]->status = LABEL;
		e = garray[v2]->tree[v1]->edge;
		if (!earray[e]->numpins)
		{
		    earray[e]->numpins = LABEL;
		    val[++n] = e;
		}
		v1 = garray[v2]->tree[v1]->parent;
	    }
	}
    }

    return(n);

} /* end of find_subgraph_from_spanning_tree */
