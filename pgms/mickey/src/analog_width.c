#ifndef lint
static char SccsId[] = "@(#)analog_width.c	Yale Version 2.7 5/16/91";
#endif
/* -----------------------------------------------------------------

	FILE:		analog_width.c
	AUTHOR:		Dahe Chen
	DATE:		Tue Nov 13 15:43:01 EST 1990
	CONTENTS:	It contains functions deciding the width
			for a given segment in either a two-pin
			net or a multiple-pin net.
	REVISION:
		Wed Dec  5 11:40:51 EST 1990
	    Fix the bug in the calculation of distance in the
	    function for multiple pin nets.
		Wed Dec  5 13:46:39 EST 1990
	    Remove h_width and v_width.
		Thu Dec  6 13:10:37 EST 1990
	    Fix bugs in the function analog_multi_pin_width for
	    checking if two equivalent pins are in the same set.
		Fri Jan  4 10:32:30 EST 1991
	    In the function analog_one_route_width, the assignment
	    to the field group has a bug when the one route is
	    caused by pin shifting. So a conditional loop will be
	    added.
		Thu Jan 10 10:13:48 EST 1991
	    Now we have the case that all pins are vertices of the
	    channel graph at the same time. Hence the code to get
	    a leaf needs to be changed.
		Tue Feb  5 11:58:50 EST 1991
	    Reformat error message output.
		Wed Feb  6 14:39:53 EST 1991
	    Add the code computing voltage drops.

----------------------------------------------------------------- */

#include <define.h>
#include <macros.h>
#include <gg_router.h>
#include <dgraph.h>
#include <heap_func.h>
#include <steiner_tree.h>
#include <analog.h>

extern int nth_route_segment();
extern int segment_width();
extern unsigned get_mask();
extern LSTACKPTR analog_find_leaves();

/*=====================================================================
*   This function calculates the width of the only route for a given
* net.
=====================================================================*/
void
analog_one_route_width()
{

    int i;
    int j;
    int dens;
    int dist;
    int size;
    int degree;
    int max_size;

    LISTPTR Pnode;
    OFSETPTR Pelist;

    /***********************************************************
    * Find a leaf pin.
    ***********************************************************/
    for (i = numedges + 1; i <= totedges; i++)
    {
	degree = 0;
	j = earray[i]->node[0];
	Pnode = garray[j]->first;
	while (Pnode)
	{
	    if (earray[Pnode->edge]->intree != FALSE)
	    {
		degree++;
	    }
	    Pnode = Pnode->next;
	}

	if (degree == 1)
	{
	    break;
	}
    }

    if (SHIFTED != FALSE)
    {
	/***********************************************************
	* The one route is caused by pin shifting so that we have to
	* search for the channels which are in the route.
	***********************************************************/
	Pnode = garray[j]->first;
	while (Pnode)
	{
	    if (earray[Pnode->edge]->intree != FALSE
	     && earray[Pnode->edge]->group == FALSE)
	    {
		earray[Pnode->edge]->group = TRUE;
		Pnode = garray[Pnode->t_vertex]->first;
	    }
	    else
	    {
		Pnode = Pnode->next;
	    }
	}
    }
    else
    {
	for (i = numedges + 1; i <= totedges; i++)
	{
	    earray[i]->group = TRUE;
	}
    }

    dens = 0;
    max_size = 0;

    /***********************************************************
    * Start from the leaf pin found, calculate the wire width
    * for each channel between two consecutive pins.
    ***********************************************************/
    Pnode = garray[j]->first;
    while (Pnode)
    {
	if (earray[Pnode->edge]->intree != FALSE
	 && earray[Pnode->edge]->group != FALSE)
	{
	    earray[Pnode->edge]->group = FALSE;
	    dens += parray[j-numnodes]->density;
	    dist = earray[Pnode->edge]->length;
	    size = segment_width(dist, dens);
	    max_size = MAX(max_size, size);
	    Pnode = garray[Pnode->t_vertex]->first;
	}
	else
	{
	    Pnode = Pnode->next;
	}
    }

    Pelist = netlist->Aroute[1]->Pedge;
    while (Pelist)
    {
	Pelist->width = MAX(max_size, earray[Pelist->edge]->width);
	Pelist = Pelist->next;
    }

    return;

} /* end of analog_one_route_width */

/*=====================================================================
*   This function calculates the width of a given route for a two-pin
* net.
=====================================================================*/
void
analog_two_pin_width(route)
    int route;
{

    int i;
    int dens;
    int dist;
    int size;

    OFSETPTR Pelist;
    ROUTPTR *Aroute;

    Aroute = netlist->Aroute;

    dens = parray[1]->density;
    dist = Aroute[route]->length;
    size = segment_width(dist, dens);

    /***********************************************************
    * Assign the widths to each segment of the route.
    ***********************************************************/
    Pelist = Aroute[route]->Pedge;
    while (Pelist != NIL(OFSET))
    {
	i = Pelist->edge;
	Pelist->width = MAX(size, earray[i]->width);
	Pelist = Pelist->next;
    }

    return;

} /* end of analog_two_pin_width */

/*=====================================================================
*   This function calculates the width of a given route for a multiple-
* pin net.
=====================================================================*/
void
analog_multi_pin_width(route, Pstack)
    int route;
    LSTACKPTR Pstack;
{

    int e;
    int i;
    int j;
    int dist;
    int dens;
    int size;
    int degree;

    LISTPTR Pnode;
    LSTACKPTR Pleaf;
    MDATAPTR Phnode;
    MDATAPTR Ptnode;
    OFSETPTR Pelist;
    PINPTR Pnext;
    PINPTR Pthis;

    /***********************************************************
    * Scan through the segments of the segment tree. For each
    * segment, calcualte the width according the length and the
    * current density of the segment.
    ***********************************************************/
    Pleaf = Pstack;
    while (Pleaf != NIL(LSTACK))
    {
	/***********************************************************
	* Get the index of a new leaf in the segment tree.
	***********************************************************/
	i = Pleaf->index;

	Ptnode = marray[i];
	for (;;)
	{
	    /***********************************************************
	    * Get the pin or Steiner point exceeding the vertex denoted
	    * by Ptnode.
	    ***********************************************************/
	    Phnode = Ptnode->f_node;
	    if (!Phnode)
	    {
		/*********************************************************
		* The tail node is the root of the segment tree already.
		* Go to next leaf.
		*********************************************************/
		break;
	    }

	    dist = Ptnode->dist - Phnode->dist;
	    if (dist == 0)
	    {
		Ptnode = Phnode;
		continue;
	    }

	    if (Ptnode->leaf != FALSE)
	    {
		/*********************************************************
		* The vertex of Ptnode is a leaf in teh segment tree.
		* For each edge along the segment, calcualte its width
		* by calling the function segment_width() and assigns
		* to the channels in the segment.
		*********************************************************/
		if (Ptnode->vertex > numnodes)
		{
		    dens = parray[Ptnode->vertex - numnodes]->density;
		}
		else
		{
		    for (j = 1; j <= numpins; j++)
		    {
			if (parray[j]->node[0] == Ptnode->vertex
			 && parray[j]->node[1] == Ptnode->parent
			 || parray[j]->node[0] == Ptnode->parent
			 && parray[j]->node[1] == Ptnode->vertex)
			{
			    break;
			}
		    }
		    if (j > numpins)
		    {
			ERROR1("\n\nCan't find the leaf pin\n");
			ERROR2("Error occurs: in %s ", __FILE__);
			ERROR2("at %d\n", __LINE__);
		    }
		    dens = parray[j]->density;
		}
		size = segment_width(dist, dens);
		Ptnode->voltage = R_SHEET
				* (double) dens
				* (double) dist
				/ (double) size;
		assign_channel_width(Phnode, Ptnode);
	    }
	    else
	    {
		/*********************************************************
		* The tail node is not a leaf. Count the number of edges
		* incident to it whose width has not been calculated yet.
		*********************************************************/
		degree = 0;
		if (Ptnode->vertex > numnodes)
		{
		    /*****************************************************
		    * This vertex is a pin. Use parray in case it has
		    * equivalent pins.
		    *****************************************************/
		    Pthis =
		    Pnext = parray[Ptnode->vertex - numnodes];
		    do
		    {
			Pnode = garray[Pnext->vertex + numnodes]->first;
			count_node_degree(Pnode, ==);
			Pnext = Pnext->next;
		    } while (Pnext != NIL(PIN) && Pnext != Pthis);
		}
		else
		{
		    /*****************************************************
		    * This vertex is not a pin. We only need to check its
		    * degree with respect to the segment tree.
		    *****************************************************/
		    Pnode = garray[Ptnode->vertex]->first;
		    count_node_degree(Pnode, ==);
		}

		if (degree == 1)
		{
		    /*****************************************************
		    * There is only one channel incident to the vertex of
		    * Ptnode without the width determined. Calculate the
		    * current density carried by it and its width.
		    *****************************************************/
		    dens = 0;
		    Pnode = garray[Ptnode->vertex]->first;
		    while (Pnode)
		    {
			dens += Adens[Pnode->edge];
			Pnode = Pnode->next;
		    }
		    if ((e = Ptnode->vertex - numnodes) > 0)
		    {
			dens += parray[e]->density;
		    }
		    size = segment_width(dist, dens);
		    Ptnode->voltage = R_SHEET
				    * (double) dens
				    * (double) dist
				    / (double) size;
		    assign_channel_width(Phnode, Ptnode);
		}
		else
		{
		    /*****************************************************
		    * There are more than one channel incident to the
		    * vertex of Ptnode without the width determined.
		    * Go to next leaf.
		    *****************************************************/
		    break;
		}
	    }
	}
	Pleaf = Pleaf->next;
    }

    Pelist = netlist->Aroute[route]->Pedge;
    while (Pelist != NIL(OFSET))
    {
	e = Pelist->edge;
	Pelist->width = Asize[e];
	Pelist = Pelist->next;
    }

    return;

} /* end of analog_multi_pin_width */
