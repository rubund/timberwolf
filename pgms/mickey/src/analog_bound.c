#ifndef lint
static char SccsId[] = "@(#)analog_bound.c	Yale Version 2.4 5/16/91";
#endif
/* -----------------------------------------------------------------

	FILE:		analog_bound.c
	AUTHOR:		Dahe Chen
	DATE:		Tue Nov 13 16:41:29 EST 1990
	CONTENTS:	analog_two_pin_upper_bound()
	REVISION:
		Thu Dec  6 14:27:30 EST 1990
	    Fix bugs in the function analog_multi_pin_upper_bound()
	    and make it similar to analog_multi_pin_width().
		Tue Feb  5 11:48:18 EST 1991
	    Reformat error message output.

----------------------------------------------------------------- */

#include <define.h>
#include <gg_router.h>
#include <dgraph.h>
#include <macros.h>
#include <analog.h>
#include <heap_func.h>
#include <steiner_tree.h>

/*=====================================================================
*   This function checks the capacitance and resistance of the only
* route for the given net against the upper bounds.
=====================================================================*/
void
analog_one_route_bound()
{

    int i;
    int length;
    float cap;
    float res;

    LISTPTR Pnode;
    OFSETPTR Pelist;

    Pnode = garray[numnodes+1]->first;
    while (Pnode->t_vertex > numnodes)
    {
	Pnode = Pnode->next;
    }

    length = earray[Pnode->edge]->length;

    for (i = numedges + 1; i <= totedges; i++)
    {
	length += earray[i]->length;
    }

    Pelist = netlist->Aroute[1]->Pedge;

    cap = C_SHEET * (float) length * (float) Pelist->width;
    res = R_SHEET * (float) length / (float) Pelist->width;

    if (cap > cap_upper_bound || res > res_upper_bound)
    {
	if ((cap - cap_upper_bound) < C_TOLERANCE
	 && (res - res_upper_bound) < R_TOLERANCE)
	{
	    netlist->Aroute[1]->capacitance = cap;
	    netlist->Aroute[1]->resistance = res;
	}
	else
	{
	    ERROR2("\n\nNo route for net %s ", netlist->name);
	    ERROR1("can meet constraints\n");
	    exit(GP_FAIL);
	}
    }
    else
    {
	netlist->Aroute[1]->capacitance = cap;
	netlist->Aroute[1]->resistance = res;
    }

    return;

} /* end of analog_one_route_bound */

/*=====================================================================
*   This function calculates the capacitance and resistance of a route
* for a given two-pin net and checks them against the capacitance and
* resistance upper bound specified for the net. The function returns
* TRUE if the bounds are satisfied; returns FALSE otherwise.
=====================================================================*/
int
analog_two_pin_upper_bound(route)
    int	route;
{

    int	status;
    float cap;
    float res;

    OFSETPTR Pelist;

    cap = 0.0;
    res = 0.0;
    Pelist = netlist->Aroute[route]->Pedge;

    while (Pelist != NIL(OFSET))
    {
	cap += (float) earray[Pelist->edge]->length
	     * (float) Pelist->width;
	res += (float) earray[Pelist->edge]->length
	     / (float) Pelist->width;
	Pelist = Pelist->next;
    }

    cap *= C_SHEET;
    res *= R_SHEET;

    if (cap > cap_upper_bound || res > res_upper_bound)
    {
	if ((cap - cap_upper_bound) < C_TOLERANCE
	 && (res - res_upper_bound) < R_TOLERANCE)
	{
	    netlist->Aroute[route]->capacitance = cap;
	    netlist->Aroute[route]->resistance = res;
	    status = TRUE;
	}
	else
	{
	    status = FALSE;
	}
    }
    else
    {
	netlist->Aroute[route]->capacitance = cap;
	netlist->Aroute[route]->resistance = res;
	status = TRUE;
    }

    return(status);

} /* end of analog_two_pin_upper_bound */

/*=====================================================================
*   This function calculates the capacitance and resistance of a route
* for a given multiple-pin net and checks them against the capacitance
* and resistance upper bound specified for the net. The function returns
* TRUE if the bounds are satisfied; returns FALSE otherwise.
=====================================================================*/
int
analog_multi_pin_upper_bound(route, Pstack)
    int route;
    LSTACKPTR Pstack;
{

    int i;
    int j;
    int degree;
    int status;
    float cap = 0.0;
    float res = 0.0;

    LISTPTR Pnode;
    LSTACKPTR Pleaf;
    MDATAPTR Phnode;
    MDATAPTR Ptnode;
    PINPTR Pnext;
    PINPTR Pthis;

    /***********************************************************
    * Create a segment tree for the route and find all the
    * leaves in the segment tree.
    ***********************************************************/
    while (Pstack != NIL(LSTACK))
    {
	/***********************************************************
	* Get the index of a new leaf in the segment tree and update
	* the leaf stack.
	***********************************************************/
	Pleaf = Pstack;
	i = Pleaf->index;
	Pstack = Pstack->next;
	Ysafe_free((char *) Pleaf);

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

	    if ((Ptnode->dist - Phnode->dist) == 0)
	    {
		Ptnode = Phnode;
		continue;
	    }

	    if (Ptnode->leaf != FALSE)
	    {
		/*********************************************************
		* For each edge along the segment, calcualte its
		* parameters.
		*********************************************************/
		calculate_parameters(Phnode, Ptnode);
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
			count_node_degree(Pnode, !=);
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
		    count_node_degree(Pnode, !=);
		}

		if (degree == 1)
		{
		    /*****************************************************
		    * For each edge along the segment, calcualte its
		    * parameters.
		    *****************************************************/
		    calculate_parameters(Phnode, Ptnode);
		}
		else
		{
		    break;
		}
	    }
	}
    }

    cap *= C_SHEET;
    res *= R_SHEET;

    if (cap > cap_upper_bound || res > res_upper_bound)
    {
	if ((cap - cap_upper_bound) < C_TOLERANCE
	 && (res - res_upper_bound) < R_TOLERANCE)
	{
	    netlist->Aroute[route]->capacitance = cap;
	    netlist->Aroute[route]->resistance = res;
	    status = TRUE;
	}
	else
	{
	    status = FALSE;
	}
    }
    else
    {
	netlist->Aroute[route]->capacitance = cap;
	netlist->Aroute[route]->resistance = res;
	status = TRUE;
    }

    return(status);

} /* end of analog_multi_pin_upper_bound */
