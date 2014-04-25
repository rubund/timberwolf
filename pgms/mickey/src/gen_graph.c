#ifndef lint
static char SccsId[] = "@(#)gen_graph.c	Yale Version 2.4 5/16/91";
#endif
/* -----------------------------------------------------------------

	FILE:		gen_graph.c
	AUTHOR:		Dahe Chen
	DATE:		Mon Mar 6 12:40:17 EDT 1990
	CONTENTS:	generate_pin_graph()
	REVISION:
		Wed Nov 28 21:34:28 EST 1990
	    Remove x and y coordinates from parray and determine
	    the x/y coordinates of the pins in a pin graph by the
	    following formula:

			   dist[0]*(x[2] - x[1])
		x = x[1] + ---------------------
				  length

			   dist[0]*(y[2] - y[1])
		y = y[1] + ---------------------
				  length
	    
	    where x[i]/y[i] are the coordinates of the two vertices
	    incident to the channel, dist[0] is the distance from
	    the pin to v[1], and the length is the length of the
	    channel.
		Wed Dec  5 11:14:41 EST 1990
	    Reassign the index of parray after sorting.
		Thu Dec  6 16:31:01 EST 1990
	    Assign the width to the new edges generated.

----------------------------------------------------------------- */

#include <define.h>
#include <gg_router.h>
#include <macros.h>

void
generate_pin_graph()
{

    int i;
    int j;
    int e;
    int v;
    int v1;
    int v2;
    int d1;
    int d2;
    int dist;
    int length;
    int limit;
    int parent;

    EDGEPTR Pedge ;
    LISTPTR Pnode1;
    LISTPTR Pnode2;
    NODEPTR Pnode ;
    PINPTR Ppin;
    TREEPTR *tarray;

    length = numnodes + maxpins;
    totnodes = numnodes + numpins;
    totedges = numedges + numpins;

    /***********************************************************
    * Generate a new linked list for the graph with pins also as
    * vertices. If numpins is greater thatn maxpins, reallocate
    * memory to expand adjacent list and shortest path trees.
    ***********************************************************/
    if (numpins > maxpins)
    {
	garray = (NODEPTR *) Ysafe_realloc((char *) garray,
		(totnodes + 1) * sizeof(NODEPTR));

	for (i = 1; i <= length; i++)
	{
	    garray[i]->tree =
	    tarray = (TREEPTR *) Ysafe_realloc((char *) garray[i]->tree,
		(totnodes + 1) * sizeof(TREEPTR));

	    for (j = numnodes + maxpins + 1; j <= totnodes; j++)
	    {
		tarray[j] = (TREEPTR) Ysafe_malloc(sizeof(TREE));
	    }
	}

	for (i = length + 1; i <= totnodes; i++)
	{
	    garray[i] = (NODEPTR) Ysafe_malloc(sizeof(NODE));
	    garray[i]->first = NIL(LIST);
	    garray[i]->tree =
	    tarray = (TREEPTR *) Ysafe_malloc((totnodes + 1)
		* sizeof(TREEPTR));

	    for (j = 0; j <= totnodes; j++)
	    {
		tarray[j] = (TREEPTR) Ysafe_malloc(sizeof(TREE));
	    }
	    for (j = 1; j <= 2; j++)
	    {
		Pnode1 = (LISTPTR) Ysafe_malloc(sizeof(LIST));
		Pnode1->next = garray[i]->first;
		garray[i]->first = Pnode1;
	    }
	}
	earray = (EDGEPTR *) Ysafe_realloc((char *) earray,
		(totedges+1)*sizeof(EDGEPTR));

	for (i = numedges + maxpins + 1; i <= totedges; i++)
	{
	    earray[i] = (EDGEPTR) Ysafe_malloc(sizeof(EDGE));
	}
	maxpins = numpins;
    }


    /***********************************************************
    * Assign edge index to the edge field in parray.
    ***********************************************************/
    for (i = 1; i <= numpins; i++)
    {
	v1 = parray[i]->node[0];
	v2 = parray[i]->node[1];
	Pnode1 = garray[v1]->first;

	while (Pnode1 && Pnode1->t_vertex != v2)
	{
	    Pnode1 = Pnode1->next;
	}

	parray[i]->edge = Pnode1->edge;
	parray[i]->key = Pnode1->edge;
    }

    /***********************************************************
    * Sort parray according to edge indices.
    ***********************************************************/
    sort_parray(1, numpins);

    /***********************************************************
    * Sort parray according to their x or y positions with
    * respect to that they are on a vertical or horizontal
    * channel.
    ***********************************************************/
    i = 1;

    while (i <= numpins)
    {
	e = parray[i]->edge;
	j = i;

	while (j <= numpins && e == parray[j]->edge)
	{
	    parray[j]->key = parray[j]->dist[0];
	    j++;
	}

	if (i < j - 1)
	{
	    sort_parray(i, j-1);
	    for (e = i; e < j; e++)
	    {
		if (e == i)
		{
		    parray[e]->pin[1] = e + 1;
		}
		else if (e == j - 1)
		{
		    parray[e]->pin[0] = e - 1;
		}
		else
		{
		    parray[e]->pin[0] = e - 1;
		    parray[e]->pin[1] = e + 1;
		}
	    }
	}
	for (e = i; e < j; e++)
	{
	    parray[e]->numpin = j - i;
	}
	i = j;
    }

    /***********************************************************
    * Complete the graph wth all the pins.
    ***********************************************************/
    i = 1;
    totedges = numedges;

    while (i <= numpins)
    {
	Ppin = parray[i];
	if (Ppin->numpin == 1)
	{
	    j = numnodes + i;
	    v1 = Ppin->node[0];
	    v2 = Ppin->node[1];
	    Pnode = garray[j];
	    Pnode->vertex = j;
	    Pnode->status = 0;
	    Pnode->set = 0;
	    Pnode->xpos = garray[v1]->xpos
			+ Ppin->dist[0]
			* (garray[v2]->xpos - garray[v1]->xpos)
			/ carray[Ppin->edge]->length;
	    Pnode->ypos = garray[v1]->ypos
			+ Ppin->dist[0]
			* (garray[v2]->ypos - garray[v1]->ypos)
			/ carray[Ppin->edge]->length;

	    /***********************************************************
	    * There is only one pin on the channel.
	    ***********************************************************/
	    Pnode1 = Pnode->first;
	    Pnode2 = garray[v1]->first;

	    while (Pnode2->t_vertex != v2)
	    {
		Pnode2 = Pnode2->next;
	    }

	    /***********************************************************
	    * The segment from v1 --- the node from parray[i]->node[0]
	    * --- to pin i is kept same as the edge itself.
	    ***********************************************************/
	    e = Pnode2->edge;
	    Pedge = earray[e];

	    Pnode1->edge = e;
	    Pnode1->f_vertex = j;
	    Pnode1->t_vertex = v1;
	    Pnode2->t_vertex = j;
	    Pnode1->length = 
	    Pnode2->length = Ppin->dist[0];

	    Pedge->length = Pnode1->length;
	    Pedge->node[1] = j;

	    /***********************************************************
	    * The segment from pin i to v2 --- the node from
	    * parray[i]->node[1] is assigned to a new edge.
	    ***********************************************************/
	    Pedge = earray[++totedges];

	    Pnode1 = Pnode1->next;
	    Pnode2 = garray[v2]->first;

	    while (Pnode2->t_vertex != v1)
	    {
		Pnode2 = Pnode2->next;
	    }

	    Pnode1->edge =
	    Pnode2->edge = totedges;
	    Pnode1->f_vertex =
	    Pnode2->t_vertex = j;
	    Pnode1->t_vertex = v2;
	    Pnode1->length = 
	    Pnode2->length = Ppin->dist[1];

	    Pedge->edge = totedges;
	    Pedge->group = 0;
	    Pedge->length = Pnode1->length;
	    Pedge->node[0] = j;
	    Pedge->node[1] = v2;
	    Pedge->numpins = 0;
	    Pedge->intree = 0;
	    Pedge->width = earray[e]->width;

	    /***********************************************************
	    * Update shortest path trees for each vertex if v1 is the
	    * parent of v2 or vice versa.
	    ***********************************************************/
	    for (v = 1; v <= numnodes; v++)
	    {
		if (garray[v]->tree[v1]->parent == v2)
		{
		    garray[v]->tree[v1]->parent = j;
		}

		if (garray[v]->tree[v2]->parent == v1)
		{
		    garray[v]->tree[v2]->parent = j;
		    garray[v]->tree[v2]->edge = totedges;
		}
	    }
	    i++;
	}
	else
	{
	    /***********************************************************
	    * There are more than one vertex on the channel. Generate
	    * linked list similarly to the one pin case but use a pin
	    * at one end and update the two vertices the channel connects.
	    ***********************************************************/
	    limit = i + Ppin->numpin;
	    for (v = i; v < limit; v++)
	    {
		Ppin = parray[v];
		j = numnodes + v;
		v1 = Ppin->node[0];
		v2 = Ppin->node[1];
		Pnode = garray[j];
		Pnode->vertex = j;
		Pnode->status = 0;
		Pnode->xpos = garray[v1]->xpos
			    + Ppin->dist[0]
			    * (garray[v2]->xpos - garray[v1]->xpos)
			    / carray[Ppin->edge]->length;
		Pnode->ypos = garray[v1]->ypos
			    + Ppin->dist[0]
			    * (garray[v2]->ypos - garray[v1]->ypos)
			    / carray[Ppin->edge]->length;

		if (v == i)
		{
		    Pnode1 = Pnode->first;
		    Pnode2 = garray[v1]->first;

		    while (Pnode2->t_vertex != v2)
		    {
			Pnode2 = Pnode2->next;
		    }

		    Pedge = earray[ e = Pnode2->edge ];
		    Pnode1->edge = e;
		    Pnode1->f_vertex = j;
		    Pnode1->t_vertex = v1;
		    Pnode2->t_vertex = j;
		    Pnode1->length = 
		    Pnode2->length = Ppin->dist[0];

		    Pedge->length = Pnode1->length;
		    Pedge->node[1] = j;

		    Pnode1 = Pnode1->next;

		    Pedge = earray[++totedges];

		    Pnode1->edge = totedges;
		    Pnode1->f_vertex = j;
		    Pnode1->t_vertex = j + 1;
		    Pnode1->length = parray[v+1]->dist[0]
				   - parray[v]->dist[0];

		    Pedge->edge = totedges;
		    Pedge->length = Pnode1->length;
		    Pedge->group = 0;
		    Pedge->node[0] = j;
		    Pedge->node[1] = j + 1;
		    Pedge->numpins = 0;
		    Pedge->intree = 0;
		    Pedge->width = earray[e]->width;

		    /*****************************************************
		    * Update shortest path trees for each vertex if v1 is
		    * the parent of v2.
		    *****************************************************/
		    for (e = 1; e <= numnodes; e++)
		    {
			if (garray[e]->tree[v1]->parent == v2)
			{
			    garray[e]->tree[v1]->parent = j;
			}
		    }
		}
		else if (v == limit - 1)
		{
		    Pnode1 = Pnode->first;
		    Pnode2 = garray[j-1]->first;

		    while (Pnode2->t_vertex != j)
		    {
			Pnode2 = Pnode2->next;
		    }

		    Pedge = earray[ e = Pnode2->edge ];
		    Pnode1->edge = e;
		    Pnode1->f_vertex = j;
		    Pnode1->t_vertex = j - 1;
		    Pnode2->t_vertex = j;
		    Pnode1->length = Pnode2->length;

		    Pedge->length = Pnode1->length;
		    Pedge->node[1] = j;

		    Pnode1 = Pnode1->next;
		    Pnode2 = garray[v2]->first;

		    while (Pnode2->t_vertex != v1)
		    {
			Pnode2 = Pnode2->next;
		    }

		    Pedge = earray[++totedges];

		    Pnode1->edge =
		    Pnode2->edge = totedges;
		    Pnode1->f_vertex = j;
		    Pnode1->t_vertex = v2;
		    Pnode2->t_vertex = j;
		    Pnode1->length = 
		    Pnode2->length = Ppin->dist[1];

		    Pedge->edge = totedges;
		    Pedge->length = Pnode1->length;
		    Pedge->group = 0;
		    Pedge->node[0] = j;
		    Pedge->node[1] = v2;
		    Pedge->numpins = 0;
		    Pedge->intree = 0;
		    Pedge->width = earray[e]->width;

		    /*****************************************************
		    * Update shortest path trees for each vertex if v2 is
		    * the parent of v1.
		    *****************************************************/
		    for (e = 1; e <= numnodes; e++)
		    {
			if (garray[e]->tree[v2]->parent == v1)
			{
			    garray[e]->tree[v2]->parent = j;
			    garray[e]->tree[v2]->edge = totedges;
			}
		    }
		}
		else
		{
		    Pnode1 = Pnode->first;
		    Pnode2 = garray[j-1]->first;

		    while (Pnode2->t_vertex != j)
		    {
			Pnode2 = Pnode2->next;
		    }

		    e = Pnode2->edge;
		    Pnode1->edge = e;
		    Pnode1->f_vertex = j;
		    Pnode1->t_vertex = j - 1;
		    Pnode1->length = Pnode2->length;

		    Pnode1 = Pnode1->next;

		    Pedge = earray[++totedges];

		    Pnode1->edge = totedges;
		    Pnode1->f_vertex = j;
		    Pnode1->t_vertex = j + 1;
		    Pnode1->length = parray[v+1]->dist[0]
				   - parray[v]->dist[0];

		    Pedge->edge = totedges;
		    Pedge->length = Pnode1->length;
		    Pedge->node[0] = j;
		    Pedge->node[1] = j + 1;
		    Pedge->numpins = 0;
		    Pedge->intree = 0;
		    Pedge->width = earray[e]->width;
		}
	    }
	    i = v;
	}
    }

    /***********************************************************
    * Calculate the distance from each of vertices to each of
    * pins and update shortest path trees.
    ***********************************************************/
    for (i = 1; i <= numnodes; i++)
    {
	tarray = garray[i]->tree;

	for (j = 1; j <= numpins; j++)
	{
	    v = numnodes + j;
	    v1 = parray[j]->node[0];
	    v2 = parray[j]->node[1];
	    d1 = parray[j]->dist[0] + tarray[v1]->dist;
	    d2 = parray[j]->dist[1] + tarray[v2]->dist;

	    /***********************************************************
	    * Test which path is shorter, the one through vertex
	    * parray[j]->node[0] or the other through parray[j]->node[1].
	    * Update the shortest path tree garray[i]->tree accordingly.
	    ***********************************************************/
	    if (d1 < d2)
	    {
		if (!parray[j]->pin[0])
		{
		    parent = v1;
		}
		else
		{
		    parent = numnodes + parray[j]->pin[0];
		}
		dist = d1;
	    }
	    else
	    {
		if (!parray[j]->pin[1])
		{
		    parent = v2;
		}
		else
		{
		    parent = numnodes + parray[j]->pin[1];
		}
		dist = d2;
	    }
	    tarray[v]->dist = dist;
	    tarray[v]->parent = parent;
	    tarray[v]->root = i;
	    tarray[v]->self = v;
	    tarray[v]->status = FALSE;

	    Pnode1 = garray[v]->first;

	    while (Pnode1->t_vertex != parent)
	    {
		Pnode1 = Pnode1->next;
	    }
	    tarray[v]->edge = Pnode1->edge;
	}
    }

    /***********************************************************
    * Calculate the distance from a pin to each of the vertices
    * and between a pair of pins and store the information in
    * tree of parray.
    ***********************************************************/
    for (i = 1; i <= numpins; i++)
    {
	v1 = parray[i]->node[0];
	v2 = parray[i]->node[1];
	v = numnodes + i;
	tarray = garray[v]->tree;

	for (j = 1; j <= numnodes; j++)
	{
	    d1 = garray[v1]->tree[j]->dist + parray[i]->dist[0];
	    d2 = garray[v2]->tree[j]->dist + parray[i]->dist[1];

	    if (d1 < d2)
	    {
		if (v1 == j)
		{
		    Pnode1 = garray[j]->first;

		    while (Pnode1 && Pnode1->t_vertex != v)
		    {
			Pnode1 = Pnode1->next;
		    }

		    if (Pnode1)
		    {
			parent = v;
		    }
		    else
		    {
			Pnode1 = garray[j]->first;

			while (Pnode1)
			{
			    if (Pnode1->t_vertex > numnodes)
			    {
				e = Pnode1->t_vertex - numnodes;
				if (parray[i]->edge == parray[e]->edge)
				{
				    parent = Pnode1->t_vertex;
				    break;
				}
			    }
			    Pnode1 = Pnode1->next;
			}
		    }
		}
		else
		{
		    parent = garray[v1]->tree[j]->parent;
		    Pnode1 = garray[j]->first;

		    while (Pnode1->t_vertex != parent)
		    {
			Pnode1 = Pnode1->next;
		    }
		}
		tarray[j]->parent = parent;
		tarray[j]->root = v;
		tarray[j]->self = j;
		tarray[j]->status = 0;
		tarray[j]->dist = d1;
		tarray[j]->edge = Pnode1->edge;
	    }
	    else
	    {
		if (v2 == j)
		{
		    Pnode2 = garray[j]->first;

		    while (Pnode2 && Pnode2->t_vertex != v)
		    {
			Pnode2 = Pnode2->next;
		    }

		    if (Pnode2)
		    {
			parent = v;
		    }
		    else
		    {
			Pnode2 = garray[j]->first;

			while (Pnode2)
			{
			    if (Pnode2->t_vertex > numnodes)
			    {
				e = Pnode2->t_vertex - numnodes;
				if (parray[i]->edge == parray[e]->edge)
				{
				    parent = Pnode2->t_vertex;
				    break;
				}
			    }
			    Pnode2 = Pnode2->next;
			}
		    }
		}
		else
		{
		    parent = garray[v2]->tree[j]->parent;
		    Pnode2 = garray[j]->first;

		    while (Pnode2->t_vertex != parent)
		    {
			Pnode2 = Pnode2->next;
		    }
		}
		tarray[j]->parent = parent;
		tarray[j]->root = v;
		tarray[j]->self = j;
		tarray[j]->status = 0;
		tarray[j]->dist = d2;
		tarray[j]->edge = Pnode2->edge;
	    }
	}
	for (j = numnodes+1; j <= totnodes; j++)
	{
	    if (v == j)
	    {
		tarray[v]->parent = v;
		tarray[v]->root = v;
		tarray[v]->self = v;
		tarray[v]->edge = parray[i]->edge;
		tarray[v]->status = 0;
		tarray[v]->dist = 0;
	    }
	    else
	    {
		/*********************************************************
		* Test if two pins are on the same channel. If not, use
		* the same method as above to find the shortest path;
		* otherwise, use parray to find the shortest path.
		*********************************************************/
		if (parray[i]->edge != parray[j-numnodes]->edge)
		{
		    d1 = garray[v1]->tree[j]->dist + parray[i]->dist[0];
		    d2 = garray[v2]->tree[j]->dist + parray[i]->dist[1];

		    if (d1 < d2)
		    {
			tarray[j]->parent =
			parent = garray[v1]->tree[j]->parent;
			tarray[j]->root = v;
			tarray[j]->self = j;
			tarray[j]->status = 0;
			tarray[j]->dist = d1;
		    }
		    else
		    {
			tarray[j]->parent =
			parent = garray[v2]->tree[j]->parent;
			tarray[j]->root = v;
			tarray[j]->self = j;
			tarray[j]->status = 0;
			tarray[j]->dist = d2;
		    }
		    Pnode1 = garray[j]->first;

		    while (Pnode1->t_vertex != parent)
		    {
			Pnode1 = Pnode1->next;
		    }
		    tarray[j]->edge = Pnode1->edge;
		}
		else
		{
		    if (v < j)
		    {
			tarray[j]->parent = j - 1;
			Pnode1 = garray[j-1]->first;
		    }
		    else
		    {
			tarray[j]->parent = j + 1;
			Pnode1 = garray[j+1]->first;
		    }
		    tarray[j]->root = v;
		    tarray[j]->self = j;
		    tarray[j]->status = 0;

		    while (Pnode1->t_vertex != j)
		    {
			Pnode1 = Pnode1->next;
		    }
		    tarray[j]->edge = Pnode1->edge;
		    tarray[j]->dist = Pnode1->length;
		}
	    }
	}
    }

    for (i = 1; i <= numpins; i++)
    {
	parray[i]->vertex = i;
    }

    return;

} /* end of generate_pin_graph */
