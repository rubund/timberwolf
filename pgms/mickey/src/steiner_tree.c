#ifndef lint
static char SccsId[] = "@(#)steiner_tree.c	Yale Version 2.6 5/16/91";
#endif
/* -----------------------------------------------------------------

	FILE:		steiner_tree.c
	AUTHOR:		Dahe Chen
	DATE:		Sat May 20 23:03:47 EDT 1989
	CONTENTS:	clean_up_first_tree()
			steiner_tree()
			find_more_routes()
	REVISION:
		Mon Nov  5 17:34:52 EST 1990
	    Change the type of included files. Add a function
	    generating more routes if the normal procedure does
	    not generate enough routes.
		Thu Nov  8 17:45:50 EST 1990
	    Set the upper bound of the loop setting a base route
	    from numtrees to numtrees - 1.
		Tue Dec  4 17:13:26 EST 1990
	    Add the code checking zero capacity channels.
		Fri Dec 21 14:50:42 EST 1990
	    Don't check zero capacity for the first objective function.
		Fri Jan 11 11:15:54 EST 1991
	    Set the upper limit of the initialization of dad and val
	    to the maximum of totnodes and totedges.
		Sat Jan 19 16:10:14 EST 1991
	    Initialize the variable numnode in the file find_more_routes.

----------------------------------------------------------------- */

#include <define.h>
#include <gg_router.h>

#include <heap_func.h>
#define STEINER_VARS
#include <steiner_tree.h>
#undef STEINER_VARS

extern char *deletemin();
extern unsigned get_mask();
extern HEAPSPTR *make_heap();
extern int find_zero_cap_channels();
extern void check_zero_cap_channels();

void
cleanup_first_tree()
{

    register int i;

    for (i = 1; i <= totedges; i++)
    {
	if (earray[i]->intree & MIN_MASK)
	{
	    earray[i]->intree = 1;
	}
	else
	{
	    earray[i]->intree = 0;
	}
    }

    MIN_MASK = numtrees = 1;

} /* end of cleanup_first_tree */

/* ==================================================================== */

void
steiner_tree()
{

    int find_more_routes();

    register int i;
    register int j;
    register int e;
    register int p;
    register int v;
    int v1;
    int v2;
    int numnode;
    int numedge;

    EDGEPTR Pedge;
    LISTPTR Pnode;
    PDATAPTR Pdata;

    /***********************************************************
    * These functions handle both the cases with and without
    * equivalent pins in the net.
    * In existence of equivalent pins, the weight between the
    * equivalent pins are set to be one so that these edges are
    * guaranteed to be in the minimum spanning tree.
    ***********************************************************/
    find_pin_complete_graph();
    find_complete_spanning_tree();
    numedge = find_subgraph_from_spanning_tree();

    /***********************************************************
    * Save all the edges in a heap to be used for finding the
    * minimum spanning tree.
    ***********************************************************/
    harray = make_heap(numedge);
    for (i = 1; i <= numedge; i++)
    {
	e = val[i];
	insert(harray, earray[e]->length, earray[e]);
    }

    p = MAX(totedges, totnodes);
    for (i = 1; i <= p; i++)
    {
	dad[i] = 0;
	val[i] = 0;
    }

    /***********************************************************
    * Get an edge with a minimum length each time. If the edge
    * does not form a cycle, then it is in the minimum spanning
    * tree and mark the field intree of this edge to be one to
    * indicate that the edge is in the minimum spanning tree.
    ***********************************************************/
    v = 0;
    while ((Pedge = (EDGEPTR) deletemin(harray)) != NIL(EDGE))
    {
	v1 = Pedge->node[0];
	v2 = Pedge->node[1];
	i = v1;
	j = v2;
	while (dad[i])
	{
	    i = dad[i];
	}
	while (dad[j])
	{
	    j = dad[j];
	}
	if (i != j)
	{
	    dad[j] = i;
	    Pedge->intree = 1;
	    val[++v] = Pedge->edge;
	}
    }

    /***********************************************************
    * Find all leaves and test if they are pins. If not, remove
    * the vertex and the edge connecting to it and repeat for
    * the vertex adjacent to the one just deleted. As a result,
    * a Steiner tree is obtained.
    ***********************************************************/
    for (i = 1; i <= v; i++)
    {
	j = val[i];
	if (!earray[j]->intree)
	{
	    continue;
	}

	numedge = 0;
	if (earray[j]->node[1] > numnodes)
	{
	    v1 = earray[j]->node[0];
	    p = 1;
	    if (v1 > numnodes)
	    {
		continue;
	    }
	}
	else
	{
	    v1 = earray[j]->node[1];
	    p = 0;
	}

	while (TRUE)
	{
	    Pnode = garray[v1]->first;

	    while (Pnode)
	    {
		if (earray[Pnode->edge]->intree)
		{
		    e = Pnode->edge;
		    numedge++;
		    v2 = Pnode->t_vertex;
		}

		Pnode = Pnode->next;
	    }

	    if (numedge == 1)
	    {
		earray[e]->intree = 0;
		v1 = v2;
	    }
	    else
	    {
		break;
	    }
	}
	numedge = 0;
	v1 = earray[j]->node[p];
	if (v1 > numnodes)
	{
	    continue;
	}

	while (TRUE)
	{
	    Pnode = garray[v1]->first;

	    while (Pnode)
	    {
		if (earray[Pnode->edge]->intree)
		{
		    e = Pnode->edge;
		    numedge++;
		    v2 = Pnode->t_vertex;
		}
		Pnode = Pnode->next;
	    }

	    if (numedge == 1)
	    {
		earray[e]->intree = 0;
		v1 = v2;
	    }
	    else
	    {
		break;
	    }
	}
    }

    destroy_heap(harray, numedge, NIL(int));

    /***********************************************************
    * Now we have obtained first Steiner tree or forest and want
    * to find next NUMTREES - 1 "minimum" Steiner trees subject
    * to that at least one channel of each of the trees is not
    * in any of the other trees. We use the same method as that
    * for two pin nets, that is, build up a heap with respect to
    * the distance equal to diffference of the sum of the lengths
    * of two shortest paths from the two endpoints of a channel
    * plus the length of the channel and the longest segment in
    * cycle.
    * Since the first Steiner is obtained by an approximation
    * algorithm so that it is not necessarily a minimum one.
    ***********************************************************/
    harray = make_heap(totedges);

    if (EQUIVAL == TRUE)
    {
	/***********************************************************
	* There are equivalent pins in this net. Do a postprocessing
	* to check if there exist any cycles generated by equivalent
	* pins. If so, break the cycles; otherwise calculate the
	* number of components in the first Steiner tree only.
	***********************************************************/
	for (i = 1; i <= numpins; i++)
	{
	    parray[i]->vertex = i;
	}
	find_num_comps();
	/*
	find_delete_cycles();
	*/
    }

    MIN_MASK = numtrees = 1;
    iarray = (short *) Ysafe_malloc((totnodes+1) * sizeof(short));
    jarray = (short *) Ysafe_malloc((totedges+1) * sizeof(short));
    numnode = build_tree_heap();

    while (numtrees < NUMTREES &&
	    (Pdata = (PDATAPTR) deletemin(harray)) != NIL(PDATA))
    {
	/***********************************************************
	* When a smaller tree is found, the heap is rebuilt; however
	* since some edges are in trees already so that they are
	* not available for further consideration. Now I will try
	* another way to deal this case, that is, if a smaller tree
	* is found, then only this tree is kept and the others
	* are discarded and reset numtrees to be 1 and restart
	* again.
	***********************************************************/
	MIN_MASK = get_mask(numtrees);
	if (Pdata->key < 0)
	{
	    construct_tree(Pdata, MIN_MASK, 1);
	    cleanup_first_tree();
	    Ysafe_free((char *) marray);
	    numnode = rebuild_tree_heap();
	}
	else
	{
	    if (!earray[Pdata->edge]->intree)
	    {
		construct_tree(Pdata, MIN_MASK, 1);
	    }
	}
	Ysafe_free((char *) Pdata);
    }

    if (numtrees < NUMTREES)
    {
	/***********************************************************
	* The number of routes generated is less than the preset
	* number. Call function find_more_routes() to generate more
	* routes.
	***********************************************************/
	numnode = find_more_routes(numnode);
    }

    if (CASE == 2)
    {
	if (find_zero_cap_channels() != FALSE)
	{
	    check_zero_cap_channels();
	}
    }

    for (i = 1; i <= numnode; i++)
    {
	Ysafe_free((char *) marray[i]);
	marray[i] = NIL(MDATA);
    }

    Proot = Phead;

    while (Phead)
    {
	Phead = Phead->next;
	Ysafe_free((char *) Proot);
	Proot = Phead;
    }

    for (i = 1; i <= numpins; i++)
    {
	Ysafe_free((char *) darray[i]);
    }

    Ysafe_free((char *) darray);
    Ysafe_free((char *) marray);
    Ysafe_free((char *) iarray);
    Ysafe_free((char *) jarray);
    Ysafe_free((char *) dad);
    Ysafe_free((char *) val);

    destroy_heap(harray, totedges, NIL(int));

    return;

} /* end of steiner_tree */

/* ==================================================================== */

int
find_more_routes(number)
    int number;
{

    int i;
    int j;
    unsigned *Aroute;

    PDATAPTR Pdata;

    number = 0;

    Aroute = (unsigned *) Ysafe_malloc((totedges+1)*sizeof(unsigned));

    for (i = 1; i < numtrees; i++)
    {
	/***********************************************************
	* The number of routes is less than the preset number of
	* routes. Store the current route configuration in Aroute.
	***********************************************************/
	MIN_MASK = get_mask(i);
	for (j = 1; j <= totedges; j++)
	{
	    Aroute[j] = earray[j]->intree;
	    earray[j]->intree = (earray[j]->intree&MIN_MASK) ? 1 : 0;
	}

	MIN_MASK = 1;
	Ysafe_free((char *) marray);
	number = rebuild_tree_heap();

	/***********************************************************
	* Restore the routes from Aroute into the field intree in
	* earray.
	***********************************************************/
	for (j = 1; j <= totedges; j++)
	{
	    earray[j]->intree = Aroute[j];
	}

	while (numtrees < NUMTREES
	   && (Pdata = (PDATAPTR) deletemin(harray)) != NIL(PDATA))
	{
	    MIN_MASK = get_mask(numtrees);
	    if (!earray[Pdata->edge]->intree)
	    {
		construct_tree(Pdata, MIN_MASK, get_mask(i));
	    }
	    Ysafe_free((char *) Pdata);
	}

	if (numtrees == NUMTREES)
	{
	    break;
	}
    }

    return(number);

} /* end of find_more_routes */
