#ifndef lint
static char SccsId[] = "@(#)analog_common_point.c	Yale Version 2.5 5/16/91";
#endif
/* -----------------------------------------------------------------

	FILE:		analog_common_point.c
	AUTHOR:		Dahe Chen
	DATE:		Fri May 25 14:39:40 EDT 1990
	CONTENTS:	This file contains functions to find a route
		for the nets wich common point request.
	REVISION:
		Thu Nov 29 19:01:18 EST 1990
	    Remove the use of x/y in the data structure for pins.
		Wed Dec  5 13:30:10 EST 1990
	    Remove h_width and v_width.
		Wed Jan 30 10:52:55 EST 1991
	    Rewrite the functions.
	NOTE:		Now only one route is generated for nets
			with common pins.

----------------------------------------------------------------- */

#include <define.h>
#include <gg_router.h>
#include <heap_func.h>
#include <steiner_tree.h>
#include <macros.h>
#include <dgraph.h>
#include <analog.h>

#define CASE_1	1
#define CASE_2	2
#define CASE_3	3

extern int segment_width();

static int cpins;
static int npins;
static int tpins;

static LINKPTR Phead_pin;
static LINKPTR Pthis_pin;
static PINPTR *Aterm1;
static PINPTR *Aterm2;
static ROUTPTR *Aproutes;

int
analog_common_point()
{
    /***********************************************************
    * Find the common points and save them in the list of common
    * point sets.
    ***********************************************************/
    if (!collect_pins())
    {
	ERROR1("\n\nMemory error in function collect_pins().\n");
    }
    if (!find_common_point())
    {
	ERROR1("\n\nMemory error in function find_common_point().\n");
    }
    if (!build_partial_route())
    {
	ERROR1("\n\nMemory error in function build_partial_route().\n");
    }

    /***********************************************************
    * Generate the partial pin graph for the rest of pins which
    * are not in the any common point set and the common points.
    ***********************************************************/
    if (!partial_pin_graph())
    {
	ERROR1("\n\nMemory error in function partial_pin_graph().\n");
    }

    if (numpins == 2)
    {
	two_pin_tree();
    }
    else
    {
	steiner_tree();
    }

    store_route();
    analog_func();

    /***********************************************************
    * Complete the construction of routes of the net.
    ***********************************************************/
    if (!complete_route())
    {
	ERROR1("\n\nMemory error in function complete_rouite().\n");
    }

    return;
} /* end of analog_common_point */

/*=====================================================================
*   This function creates a linked list of pins each of which belongs
* to a common point set and build the pin graph based on these pins.
=====================================================================*/
int
collect_pins()
{
    register int i;
    register int j;
    register int k;

    PINPTR Pnode;

    cpins = 0;
    Phead_pin = NIL(LINK);

    for (j = 1; j <= numpins; j++)
    {
	parray[j]->key = TRUE;
    }

    for (i = 0; i < numcomms; i++)
    {
	for (j = 1; j <= numpins; j++)
	{
	    if (parray[j]->next && parray[j]->key != FALSE)
	    {
		Pthis_pin = (LINKPTR) Ysafe_calloc(1, sizeof(LINK));
		if (Pthis_pin == NIL(LINK))
		{
		    return(FALSE);
		}
		Pthis_pin->index = j;
		Pthis_pin->next = Phead_pin;
		Phead_pin = Pthis_pin;

		Pnode = parray[j];
		do
		{
		    cpins++;
		    Pnode->key = FALSE;
		    Pnode = Pnode->next;
		} while (Pnode != parray[j]);
	    }
	}
    }

    /***********************************************************
    * Copy the common pins and non-common pins to two arrays
    * Aterm1 and Aterm2, respectively.
    ***********************************************************/
    npins = numpins - cpins;
    tpins = numpins;

    Aterm1 = (PINPTR *) Ysafe_malloc(cpins * sizeof(PINPTR));
    Aterm2 = (PINPTR *) Ysafe_malloc(npins * sizeof(PINPTR));
    if (Aterm1 == NIL(PINPTR) || Aterm2 == NIL(PINPTR))
    {
	return(FALSE);
    }

    for (i = 0, j =1; i < cpins; i++, j++)
    {
	Aterm1[i] = (PINPTR) Ysafe_malloc(sizeof(PIN));
	if (Aterm1[i] == NIL(PIN))
	{
	    return(FALSE);
	}
	Aterm1[i]->node[0] = parray[j]->node[0];
	Aterm1[i]->node[1] = parray[j]->node[1];
	Aterm1[i]->edge = parray[j]->edge;
	Aterm1[i]->numpin = parray[j]->numpin;
	Aterm1[i]->pin[0] = parray[j]->pin[0];
	Aterm1[i]->pin[1] = parray[j]->pin[1];
	Aterm1[i]->vertex = parray[j]->vertex;
	Aterm1[i]->shifted = parray[j]->shifted;
	Aterm1[i]->equiv = parray[j]->equiv;
	Aterm1[i]->density = parray[j]->density;
	Aterm1[i]->dist[0] = parray[j]->dist[0];
	Aterm1[i]->dist[1] = parray[j]->dist[1];
	Aterm1[i]->key = parray[j]->key;
    }

    for (i = 0, j = 1; i < cpins; i++, j++)
    {
	k = parray[j]->next->vertex - 1;
	Aterm1[i]->next = Aterm1[k];
    }

    for (i = 0; i < npins; i++, j++)
    {
	Aterm2[i] = (PINPTR) Ysafe_malloc(sizeof(PIN));
	if (Aterm2[i] == NIL(PIN))
	{
	    return(FALSE);
	}
	Aterm2[i]->node[0] = parray[j]->node[0];
	Aterm2[i]->node[1] = parray[j]->node[1];
	Aterm2[i]->edge = parray[j]->edge;
	Aterm2[i]->numpin = parray[j]->numpin;
	Aterm2[i]->pin[0] = parray[j]->pin[0];
	Aterm2[i]->pin[1] = parray[j]->pin[1];
	Aterm2[i]->vertex = parray[j]->vertex;
	Aterm2[i]->shifted = parray[j]->shifted;
	Aterm2[i]->equiv = parray[j]->equiv;
	Aterm2[i]->density = parray[j]->density;
	Aterm2[i]->dist[0] = parray[j]->dist[0];
	Aterm2[i]->dist[1] = parray[j]->dist[1];
	Aterm2[i]->key = parray[j]->key;
    }

    numpins = cpins;
    parray = (PINPTR *) Ysafe_realloc((char *) parray, (numpins+1) * sizeof(PINPTR));
    if (parray == NIL(PINPTR))
    {
	return(FALSE);
    }

    generate_pin_graph();

    return(TRUE);
} /* end of collect_pins */

/*=====================================================================
*   The function scans through all the vertices of the channel graph
* and finds a vertex for each subset Pi of the pins such that
* 	M_length(v->common) = min{M_length(w->common)|w in V}
* the paths from the vertex to all the pins in Pi do not cross each
* other.
*   There are three different cases: (1) the pins in Pi are at the same
* location; (2) the pins in Pi are in the same channel but at different
* locations; and (3) the pins in Pi are in different channels.
/* ==================================================================== */
int
find_common_point()
{
    register int i;
    register int v;
    int cur_length;
    int max_length;
    int min_length;
    int tot_length;

    PINPTR Pnode;

    Pthis_pin = Phead_pin;

    while (Pthis_pin)
    {
	/***********************************************************
	* Check if the pins in a subset are in the same channel.
	***********************************************************/
	Pnode = parray[Pthis_pin->index];
	do
	{
	    if (Pnode->edge != parray[Pthis_pin->index]->edge)
	    {
		break;
	    }
	    Pnode = Pnode->next;
	} while (Pnode != parray[Pthis_pin->index]);

	if (Pnode == parray[Pthis_pin->index])
	{
	    /***********************************************************
	    * Check if the pins are at the same location.
	    ***********************************************************/
	    Pnode = parray[Pthis_pin->index];
	    do
	    {
		if (Pnode->dist[0] != parray[Pthis_pin->index]->dist[0])
		{
		    break;
		}
		Pnode = Pnode->next;
	    } while (Pnode != parray[Pthis_pin->index]);

	    if (Pnode == parray[Pthis_pin->index])
	    {
		/*********************************************************
		* Assign the pin location as the location for the common
		* point and take one of the pins as the common point.
		*********************************************************/
		Pthis_pin->node = Pnode->vertex + numnodes;
		Pthis_pin->status = CASE_1;
	    }
	    else
	    {
		/*********************************************************
		* Take the pin that is closest to a graph vertex as the
		* common point.
		*********************************************************/
		min_length = INT_MAX;
		Pnode = parray[Pthis_pin->index];
		do
		{
		    if (min_length > Pnode->dist[0])
		    {
			min_length = Pnode->dist[0];
			Pthis_pin->node = Pnode->vertex + numnodes;
		    }
		    if (min_length > Pnode->dist[1])
		    {
			min_length = Pnode->dist[1];
			Pthis_pin->node = Pnode->vertex + numnodes;
		    }
		    Pnode = Pnode->next;
		} while (Pnode != parray[Pthis_pin->index]);

		Pthis_pin->status = CASE_2;
	    }
	}
	else
	{
	    /***********************************************************
	    * We don't check crossing of paths. That is guaranteed by
	    * the structure of the channel graphs.
	    ***********************************************************/
	    tot_length = INT_MAX;

	    for (i = 1; i <= numnodes; i++)
	    {
		max_length = INT_MIN;
		min_length = INT_MAX;
		Pnode = parray[Pthis_pin->index];
		do
		{
		    v = Pnode->vertex + numnodes;
		    cur_length = garray[i]->tree[v]->dist;
		    max_length = MAX(max_length, cur_length);
		    min_length = MIN(min_length, cur_length);
		    Pnode = Pnode->next;
		} while (Pnode != parray[Pthis_pin->index]);

		if ((max_length - min_length) / min_length != 0)
		{
		    continue;
		}
		if (max_length < tot_length)
		{
		    tot_length = max_length;
		    Pthis_pin->node = i;
		}
	    }
	    Pthis_pin->status = CASE_3;
	}
	Pthis_pin = Pthis_pin->next;
    }

    return(TRUE);
} /* end of find_common_point */

/*=====================================================================
*   This function determines the minimum width for the paths from the
* common point to each pin in a subset Pi.
=====================================================================*/
int
build_partial_route()
{
    register int v;
    register int n1;
    register int n2;

    LISTPTR Pnlist;
    OFSETPTR Pofset;
    PINPTR Pnode;
    ROUTPTR Proute;

    Aproutes = (ROUTPTR *) Ysafe_malloc(numpins * sizeof(ROUTPTR));
    if (Aproutes == NIL(ROUTPTR))
    {
	return(FALSE);
    }

    Pthis_pin = Phead_pin;
    while (Pthis_pin)
    {
	if (Pthis_pin->status == CASE_1)
	{
	    continue;
	}

	Pnode = parray[Pthis_pin->index];
	do
	{
	    Aproutes[Pnode->vertex - 1] =
	    Proute = (ROUTPTR) Ysafe_calloc(1, sizeof(ROUT));
	    if (Proute == NIL(ROUT))
	    {
		return(FALSE);
	    }

	    n1 = Pnode->vertex + numnodes;
	    n2 = Pthis_pin->node;
	    do
	    {
		Pnlist = garray[n2]->first;
		n2 = garray[n1]->tree[n2]->parent;

		while (Pnlist->t_vertex != n2)
		{
		    Pnlist = Pnlist->next;
		}

		Pofset = (OFSETPTR) Ysafe_calloc(1, sizeof(OFSET));
		if (Pofset == NIL(OFSET))
		{
		    return(FALSE);
		}

		if (Pnlist->edge > numedges)
		{
		    Pofset->edge = Pnode->edge;
		}
		else
		{
		    Pofset->edge = Pnlist->edge;
		}

		v = earray[Pnlist->edge]->node[0];
		if (v > numnodes)
		{
		    Pofset->l_off = parray[v - numnodes]->dist[0];
		}
		else
		{
		    Pofset->l_off = 0;
		}

		v = earray[Pnlist->edge]->node[1];
		if (v > numnodes)
		{
		    Pofset->r_off = parray[v - numnodes]->dist[1];
		}
		else
		{
		    Pofset->r_off = 0;
		}

		Pofset->next = Proute->Pedge;
		Proute->Pedge = Pofset;
		Proute->length += earray[Pnlist->edge]->length;
	    } while (n2 != n1);

	    Pnode = Pnode->next;
	} while (Pnode != parray[Pthis_pin->index]);

	Pthis_pin = Pthis_pin->next;
    }

    /***********************************************************
    * Determine the minimum width of the routes.
    ***********************************************************/
    for (v = 0; v < cpins; v++)
    {
	n1 = segment_width(Aproutes[v]->length, Aterm1[v]->density);
	Pofset = Aproutes[v]->Pedge;

	while (Pofset)
	{
	    Pofset->width = MAX(n1, earray[Pofset->edge]->width);
	    Pofset = Pofset->next;
	}
    }

    return(TRUE);
} /* end of build_partial_route */

/*=====================================================================
*   This function builds up a pin graph with the pins which are not in
* any common point set and the common points.
=====================================================================*/
int
partial_pin_graph()
{
    register int i;
    register int j;
    register int e;
    int v1;
    int v2;

    PINPTR *Aterms;

    i = npins + numcomms + 1;
    Aterms = (PINPTR *) Ysafe_malloc(i * sizeof(PINPTR));
    if (Aterms == NIL(PINPTR))
    {
	return(FALSE);
    }

    /***********************************************************
    * Assign the common point(s) to the parray.
    ***********************************************************/
    j = 1;
    Pthis_pin = Phead_pin;

    while (Pthis_pin)
    {
	v1 = Pthis_pin->index;

	if (v1 > numnodes)
	{
	    v1 -= numnodes;

	    for (i = 0; i < cpins; i++)
	    {
		if (Aterm1[i]->edge == parray[v1]->edge
		 && Aterm1[i]->dist[0] == parray[v1]->dist[0]
		 && Aterm1[i]->dist[1] == parray[v1]->dist[1])
		{
		    Aterms[j] = Aterm1[i];
		    break;
		}
	    }
	}
	else
	{
	    Aterms[j] = (PINPTR) Ysafe_malloc(sizeof(PIN));
	    if (Aterms[j] == NIL(PIN))
	    {
		return(FALSE);
	    }

	    v2 = garray[v1]->first->t_vertex;
	    e = garray[v1]->first->edge;
	    if (earray[e]->node[0] == v1 && earray[e]->node[1] == v2)
	    {
		Aterms[j]->node[0] = v1;
		Aterms[j]->node[1] = v2;
		Aterms[j]->shifted = 1;
		Aterms[j]->dist[0] = 1;
		Aterms[j]->dist[1] = earray[e]->length - 1;
	    }
	    else
	    {
		Aterms[j]->node[0] = v2;
		Aterms[j]->node[1] = v1;
		Aterms[j]->shifted = -1;
		Aterms[j]->dist[0] = earray[e]->length - 1;
		Aterms[j]->dist[1] = 1;
	    }
	    Aterms[j]->edge = e;
	    Aterms[j]->numpin = 1;
	    Aterms[j]->pin[0] = 0;
	    Aterms[j]->pin[1] = 0;
	    Aterms[j]->vertex = j;
	    Aterms[j]->equiv = 0;
	    Aterms[j]->density = 0;
	    Aterms[j]->key = 0;
	    Aterms[j]->next = NIL(PIN);
	    SHIFTED = TRUE;
	}
	j++;
	Pthis_pin = Pthis_pin->next;
    }

    restore_node_edge();

    numpins = npins + numcomms;
    parray = Aterms;

    for (i = 0; i < npins; i++, j++)
    {
	Aterms[j] = Aterm2[i];
	Aterms[j]->vertex = j;
    }

    generate_pin_graph();

    return(TRUE);
} /* end of partial_pin_graph */

/*=====================================================================
*   The function completes the routes for the net which has common
* point set(s).
=====================================================================*/
int
complete_route()
{
    register int i;
    register int j;
    register int l;

    OFSETPTR Pelist1;
    OFSETPTR Pelist2;

    l = Aproutes[0]->length;

    for (j = cpins - 1; j > 0; j--)
    {
	Pelist2 = Aproutes[j]->Pedge;

	while (Pelist2->next)
	{
	    Pelist2 = Pelist2->next;
	}

	Pelist2->next = Aproutes[j - 1]->Pedge;
	l += Aproutes[j]->length;
    }

    for (i = 1; i <= numtrees; i++)
    {
	Pelist1 = netlist->Aroute[i]->Pedge;

	while (Pelist1->next)
	{
	    Pelist1 = Pelist1->next;
	}

	Pelist1->next = Aproutes[cpins - 1]->Pedge;
	netlist->Aroute[i]->length += l;
    }

    return(TRUE);
} /* end of complete_route */
