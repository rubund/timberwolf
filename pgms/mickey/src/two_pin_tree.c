#ifndef lint
static char SccsId[] = "@(#)two_pin_tree.c	Yale Version 3.2 5/23/91";
#endif
/* -----------------------------------------------------------------

	FILE:		two_pin_tree.c
	AUTHOR:		Dahe Chen
	DATE:		Sun Feb 19 23:06:46 EDT 1989
	CONTENTS:	first_path()
			build_heap()
			save_data()
			two_pin_tree()
			construct_path()
			find_more_paths()
			calculate_the_length()
	REVISION:
		Fri Nov  2 11:05:47 EST 1990
	    Mickey sometimes can not generate enough routes for a
	    two-pin net. We add functions that will generate routes
	    based on an existing route.
		Wed Nov  7 15:13:44 EST 1990
	    By shifting a route down in the bit indicator it is
	    much easier to find more routes based on an existing
	    route. Also, the function build_heap must be rewritten
	    such that it will extend two endpoints of a channel
	    not only to the two pins but also the every other pair
	    of vertices in the first path.
		Thu Nov  8 17:44:52 EST 1990
	    Set the upper bound of the loop setting a base route
	    from numtrees to numtrees - 1.
		Fri Dec 21 14:48:18 EST 1990
	    Don't check channel capacity if the first objective is
	    used.
		Thu May 23 18:34:31 EDT 1991
	    Not scan the channels which are adjacent to empty rooms.

----------------------------------------------------------------- */

#include <define.h>
#include <gg_router.h>
#include <heap_func.h>
#include <macros.h>

typedef struct hdata {
    short edge;
    short vertex[2];
    short to_pin[2];
    int dist;
} HDATA,
*HDATAPTR;

extern char *deletemin();
extern unsigned	get_mask();
extern HEAPSPTR	*make_heap();
extern int find_zero_cap_channels();
extern void check_zero_cap_channels();

static int *Anodes;
static unsigned	MASK;
static HEAPSPTR	*Aheap;

/* ==================================================================== */

void
first_path()
{

    int v;
    int v1;
    int v2;

    LISTPTR Pnode;

    v1 = numnodes + 1;
    v2 = numnodes + 2;

    while (v1 != v2)
    {
	v = garray[v1]->tree[v2]->parent;
	Pnode = garray[v2]->first;

	while (Pnode->t_vertex != v)
	{
	    Pnode = Pnode->next;
	}

	earray[Pnode->edge]->intree = 1;
	v2 = v;
    }

    numtrees = 1;

} /* end of first_path */

/* ==================================================================== */

void
build_heap()
{

    int calculate_the_length();
    HDATAPTR save_data();

    int e;
    int i;
    int j;
    int v;
    int i1;
    int i2;
    int j1;
    int j2;
    int v1;
    int v2;
    int dist;
    int label;
    int number;
    int status;

    HDATAPTR Pdata;
    LISTPTR	Pnode;

    Aheap = make_heap(totedges);
    Anodes = (int *) Ysafe_malloc((totnodes+1)*sizeof(int));

    /***********************************************************
    * Initialize the status of garray.
    ***********************************************************/
    for (i = 1; i <= totnodes; i++)
    {
	garray[i]->status = FALSE;
    }

    /***********************************************************
    * Mark the vertices in the first shortest path and store
    * the vertices in Anodes.
    ***********************************************************/
    i = 1;
    Anodes[0] = v = numnodes + 1;
    v1 = numnodes + 2;
    v2 = numnodes + 1;

    while (v != v1)
    {
	Pnode = garray[v]->first;

	while (!earray[Pnode->edge]->intree || Pnode->t_vertex == v2)
	{
	    Pnode = Pnode->next;
	}

	Anodes[i++] = Pnode->t_vertex;
	v2 = v;
	v = Pnode->t_vertex;
	garray[Pnode->f_vertex]->status = TRUE;
	garray[Pnode->t_vertex]->status = TRUE;
    }
    number = i - 1;

    label = 2;

    /***********************************************************
    * Scan through all the channels.
    ***********************************************************/
    for (e = 1; e <= totedges; e++)
    {
	if (earray[e]->intree || earray[e]->empty)
	{
	    continue;
	}

	status = FALSE;
	Pdata = NIL(HDATA);
	i1 = earray[e]->node[0];
	i2 = earray[e]->node[1];

	if (garray[i1]->status == TRUE && garray[i2]->status == TRUE)
	{
	    /*********************************************************
	    * Both endpoints of the channel are in the base route.
	    *********************************************************/
	    dist = earray[e]->length - calculate_the_length(i1, i2);
	    Pdata = save_data(Pdata, e, i1, i2, v1, v2, dist);
	}
	else if (garray[i1]->status == TRUE)
	{
	    /***********************************************************
	    * One of endpoints of the channel is in the base route.
	    ***********************************************************/
	    v1 = i1;
	    for (i = 0; i <= number; i++)
	    {
		v2 = Anodes[i];
		if (v1 == v2)
		{
		    status = TRUE;
		    continue;
		}

		/*********************************************************
		* Check if the shortest path from Anodes[i] to i2, along
		* with the channel, forms feasible cycle.
		*********************************************************/
		j2 = garray[i2]->tree[v2]->parent;
		while (j2 != i2)
		{
		    if (garray[j2]->status)
		    {
			break;
		    }
		    j2 = garray[i2]->tree[j2]->parent;
		}

		if (j2 == i2)
		{
		    /*****************************************************
		    * A feasible cycle is found. Calculate the key for the
		    * cycle.
		    *****************************************************/
		    dist = earray[e]->length +
			   garray[v1]->tree[v2]->dist -
			   calculate_the_length(v1, v2);
		    if (status)
		    {
			Pdata = save_data(Pdata, e, i1, i2, v1, v2, dist);
		    }
		    else
		    {
			Pdata = save_data(Pdata, e, i2, i1, v2, v1, dist);
		    }
		}
	    }
	}
	else if (garray[i2]->status == TRUE)
	{
	    /***********************************************************
	    * One of endpoints of the channel is in the base route.
	    ***********************************************************/
	    v2 = i2;
	    for (i = 0; i <= number; i++)
	    {
		v1 = Anodes[i];
		if (v1 == v2)
		{
		    status = TRUE;
		    continue;
		}

		/*********************************************************
		* Check if the shortest path from Anodes[i] to i2, along
		* with the channel, forms feasible cycle.
		*********************************************************/
		j1 = garray[i1]->tree[v1]->parent;
		while (j1 != i1)
		{
		    if (garray[j1]->status)
		    {
			break;
		    }
		    j1 = garray[i1]->tree[j1]->parent;
		}

		if (j1 == i1)
		{
		    /*****************************************************
		    * A feasible cycle is found. Calculate the key for the
		    * cycle.
		    *****************************************************/
		    dist = earray[e]->length +
			   garray[v1]->tree[v2]->dist -
			   calculate_the_length(v1, v2);
		    if (status)
		    {
			Pdata = save_data(Pdata, e, i2, i1, v2, v1, dist);
		    }
		    else
		    {
			Pdata = save_data(Pdata, e, i1, i2, v1, v2, dist);
		    }
		}
	    }
	}
	else
	{
	    /***********************************************************
	    * None of endpoints of the channel is in the base route.
	    ***********************************************************/
	    for (i = 0; i < number; i++)
	    {
		for (j = i + 1; j <= number; j++)
		{
		    v1 = Anodes[i];
		    v2 = Anodes[j];
		    /*****************************************************
		    * Check if the shortest paths, along with the channel,
		    * form a feasible cycle.
		    *****************************************************/
		    j1 = garray[i1]->tree[v1]->parent;
		    while (j1 != i1)
		    {
			if (garray[j1]->status)
			{
			    break;
			}
			garray[j1]->status = label;
			j1 = garray[i1]->tree[j1]->parent;
		    }
		    if (garray[j1]->status == FALSE)
		    {
			garray[j1]->status = label;
		    }
		    j2 = garray[i2]->tree[v2]->parent;
		    while (j2 != i2)
		    {
			if (garray[j2]->status)
			{
			    break;
			}
			j2 = garray[i2]->tree[j2]->parent;
		    }
		    if (garray[j2]->status == label)
		    {
			j2 = j1;
		    }

		    if (i1 == j1 && i2 == j2)
		    {
			dist = garray[i1]->tree[v1]->dist +
			       garray[i2]->tree[v2]->dist +
			       earray[e]->length -
			       calculate_the_length(v1, v2);
			Pdata = save_data(Pdata, e, i1, i2, v1, v2, dist);
		    }
		    j1 = garray[i1]->tree[v1]->parent;
		    while (j1 != i1)
		    {
			if (garray[j1]->status == label)
			{
			    garray[j1]->status = FALSE;
			}
			j1 = garray[i1]->tree[j1]->parent;
		    }
		    if (garray[j1]->status == label)
		    {
			garray[j1]->status = FALSE;
		    }
		}
	    }
	    for (i = 0; i < number; i++)
	    {
		for (j = i + 1; j <= number; j++)
		{
		    v1 = Anodes[j];
		    v2 = Anodes[i];
		    /*****************************************************
		    * Check if the shortest paths, along with the channel,
		    * form a feasible cycle.
		    *****************************************************/
		    j1 = garray[i1]->tree[v1]->parent;
		    while (j1 != i1)
		    {
			if (garray[j1]->status)
			{
			    break;
			}
			garray[j1]->status = label;
			j1 = garray[i1]->tree[j1]->parent;
		    }
		    if (garray[j1]->status == FALSE)
		    {
			garray[j1]->status = label;
		    }
		    j2 = garray[i2]->tree[v2]->parent;
		    while (j2 != i2)
		    {
			if (garray[j2]->status)
			{
			    break;
			}
			j2 = garray[i2]->tree[j2]->parent;
		    }
		    if (garray[j2]->status == label)
		    {
			j2 = j1;
		    }

		    if (i1 == j1 && i2 == j2)
		    {
			dist = garray[i1]->tree[v1]->dist +
			       garray[i2]->tree[v2]->dist +
			       earray[e]->length -
			       calculate_the_length(v1, v2);
			Pdata = save_data(Pdata, e, i2, i1, v2, v1, dist);
		    }
		    j1 = garray[i1]->tree[v1]->parent;
		    while (j1 != i1)
		    {
			if (garray[j1]->status == label)
			{
			    garray[j1]->status = FALSE;
			}
			j1 = garray[i1]->tree[j1]->parent;
		    }
		    if (garray[j1]->status == label)
		    {
			garray[j1]->status = FALSE;
		    }
		}
	    }
	}

	if (Pdata)
	{
	    insert(Aheap, Pdata->dist, Pdata);
	}
    }

    return;

} /* end of build_heap */

/* ==================================================================== */

HDATAPTR
save_data(Pdata, e, i1, i2, v1, v2, dist)
    HDATAPTR Pdata;
    int i1;
    int i2;
    int v1;
    int v2;
    int dist;
{

    if (Pdata)
    {
	if (Pdata->dist > dist)
	{
	    Pdata->edge = e;
	    Pdata->vertex[0] = i1;
	    Pdata->vertex[1] = i2;
	    Pdata->to_pin[0] = v1;
	    Pdata->to_pin[1] = v2;
	    Pdata->dist = dist;
	}
    }
    else
    {
	Pdata = (HDATAPTR) Ysafe_malloc(sizeof(HDATA));
	Pdata->edge = e;
	Pdata->vertex[0] = i1;
	Pdata->vertex[1] = i2;
	Pdata->to_pin[0] = v1;
	Pdata->to_pin[1] = v2;
	Pdata->dist = dist;
    }

    return(Pdata);

} /* end of save_data */

/* ==================================================================== */

void
two_pin_tree()
{

    HDATAPTR Pdata;

    void construct_path();
    void find_more_paths();

    /***********************************************************
    * Mark the first shortest path.
    ***********************************************************/
    first_path();

    /***********************************************************
    * Build a heap function based on the first path.
    ***********************************************************/
    build_heap();

    while (numtrees < NUMTREES
	&& (Pdata = (HDATAPTR) deletemin(Aheap)) != NIL(HDATA))
    {
	if (!earray[Pdata->edge]->intree)
	{
	    MASK = get_mask(numtrees);
	    construct_path(Pdata, 1);
	}
	Ysafe_free((char *) Pdata);
    }

    destroy_heap(Aheap, totedges, NIL(int));

    if (numtrees < NUMTREES)
    {
	find_more_paths();
    }

    if (CASE == 2)
    {
	if (find_zero_cap_channels() != FALSE)
	{
	    check_zero_cap_channels();
	}
    }

    return;

} /* end of two_pin_tree */

/* ==================================================================== */

void
construct_path(Pdata, mask)
    HDATAPTR Pdata;
    unsigned mask;
{

    int i;
    int i1;
    int i2;
    int v;
    int v1;
    int v2;

    LISTPTR Pnode;

    numtrees++;

    /***********************************************************
    * Mark the channels in the i-th route from p[1|2] to
    * to_pin[0|1].
    ***********************************************************/
    if (Pdata->to_pin[0] <= numnodes && Pdata->to_pin[1] <= numnodes)
    {
	i1 = 0;
	i2 = 1;
    }
    else if (Pdata->to_pin[0] <= numnodes)
    {
	i1 = 0;
	i2 = 0;
    }
    else if (Pdata->to_pin[1] <= numnodes)
    {
	i1 = 1;
	i2 = 1;
    }
    else
    {
	i1 = 1;
	i2 = 0;
    }

    for (i = i1; i <= i2; i++)
    {
	v = numnodes + 1 + i;
	v1 = Pdata->to_pin[i];
	v2 = numnodes + 1 + i;
	while (v != v1)
	{
	    Pnode = garray[v]->first;

	    while (!(earray[Pnode->edge]->intree&mask)
		|| Pnode->t_vertex == v2)
	    {
		Pnode = Pnode->next;
	    }

	    earray[Pnode->edge]->intree |= MASK;
	    v2 = v;
	    v = Pnode->t_vertex;
	}
    }

    /***********************************************************
    * Mark the channels in the shortest paths from to_pin[0|1]
    * to the endpoints of the scanned channel.
    ***********************************************************/
    for (i = 0; i <= 1; i++)
    {
	v1 = Pdata->vertex[i];
	v2 = Pdata->to_pin[i];

	while (v1 != v2)
	{
	    v = garray[v1]->tree[v2]->parent;
	    Pnode = garray[v2]->first;

	    while (Pnode->t_vertex != v)
	    {
		Pnode = Pnode->next;
	    }

	    earray[Pnode->edge]->intree |= MASK;
	    v2 = v;
	}
    }

    /***********************************************************
    * Mark the scanned channel.
    ***********************************************************/
    earray[Pdata->edge]->intree |= MASK;

    return;

} /* end of construct_path */

/* ==================================================================== */

void
find_more_paths()
{

    int i;
    int j;
    unsigned *Aroute;

    HDATAPTR Pdata;

    Aroute = (unsigned *) Ysafe_malloc((totedges+1)*sizeof(unsigned));

    for (i = 1; i < numtrees; i++)
    {
	/***********************************************************
	* The number of routes is less than the preset number of
	* routes. Store the current route configuration in Aroute
	* and shift the (i+1)st route as the first route.
	***********************************************************/
	MASK = get_mask(i);
	for (j = 1; j <= totedges; j++)
	{
	    Aroute[j] = earray[j]->intree;
	    earray[j]->intree = (earray[j]->intree&MASK) ? 1 : 0;
	}

	build_heap();

	/***********************************************************
	* Restore the routes from Aroute into the field intree in
	* earray.
	***********************************************************/
	for (j = 1; j <= totedges; j++)
	{
	    earray[j]->intree = Aroute[j];
	}

	while (numtrees < NUMTREES &&
	      (Pdata = (HDATAPTR) deletemin(Aheap)) != NIL(HDATA))
	{
	    if (!earray[Pdata->edge]->intree)
	    {
		MASK = get_mask(numtrees);
		construct_path(Pdata, get_mask(i));
	    }
	    Ysafe_free((char *) Pdata);
	}

	if (numtrees == NUMTREES)
	{
	    break;
	}

	destroy_heap(Aheap, totedges, NIL(int));
    }

    return;

} /* end of find_more_paths */

/* ==================================================================== */

int
calculate_the_length(index1, index2)
    int index1;
    int index2;
{

    int i = 0;
    int len = 0;

    LISTPTR Pnode;

    while (Anodes[i] != index1 && Anodes[i] != index2)
    {
	i++;
    }

    if (Anodes[i] == index1)
    {
	while (Anodes[i] != index2)
	{
	    Pnode = garray[Anodes[i]]->first;
	    i++;
	    while (Pnode->t_vertex != Anodes[i])
	    {
		Pnode = Pnode->next;
	    }
	    len += earray[Pnode->edge]->length;
	}
    }
    else
    {
	while (Anodes[i] != index1)
	{
	    Pnode = garray[Anodes[i]]->first;
	    i++;
	    while (Pnode->t_vertex != Anodes[i])
	    {
		Pnode = Pnode->next;
	    }
	    len += earray[Pnode->edge]->length;
	}
    }

    return(len);

} /* end of calculate_the_length */
