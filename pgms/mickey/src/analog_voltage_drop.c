#ifndef lint
static char SccsId[] = "@(#)analog_voltage_drop.c	SDD Version 1.3 5/16/91" ;
#endif
/* -----------------------------------------------------------------

	FILE:		analog_voltage_drop.c
	AUTHOR:		Dahe Chen
	DATE:		Tue Feb  5 11:11:56 EST 1991
	CONTENTS:	This file contains functions computing the
		maximum voltage drop for a given route tree.
	REVISION:

----------------------------------------------------------------- */

#include <define.h>
#include <gg_router.h>
#include <heap_func.h>
#include <steiner_tree.h>
#include <macros.h>
#include <dgraph.h>
#include <analog.h>

#define EP 1.0e-10

static int width1;
static int width2;
static int number_of_routes;
static double resis1;
static double resis2;
static double c_voltage_drop;
static double m_voltage_drop;

/*=====================================================================
*   This function computes the voltage drop for each route of a two-pin
* net and compares the voltage drop with the maximum value of the
* voltage drop allowed.
=====================================================================*/
int
analog_two_pin_volt_drop()
{
    int i;
    register double density;
    register double volt_drop;

    register OFSETPTR Pelist;

    density = (double) ABS(parray[1]->density);
    number_of_routes = netlist->num_of_routes;

    for (i = 1; i <= number_of_routes; i++)
    {
	/***********************************************************
	* Compute the voltage drop of the path.
	***********************************************************/
	resis1 = (double) netlist->Aroute[i]->resistance;
	volt_drop = density * resis1;

	if (max_volt_drop < volt_drop)
	{
	    /***********************************************************
	    * The voltage drop of the path is greater than the maximum
	    * value of the toltage drop allowed.
	    ***********************************************************/
	    Pelist = netlist->Aroute[i]->Pedge;

	    while (Pelist)
	    {
		width1 = Pelist->width;
		resis2 = max_volt_drop / density;
		width2 = (int) ((double) width1 * resis1 / resis2);
		Pelist->width = MAX(width1, width2);
		Pelist = Pelist->next;
	    }
	    netlist->Aroute[i]->resistance = (float) resis2;
	}
    }

    return(TRUE);
} /* end of analog_two_pin_volt_drop */

/*=====================================================================
*   The function computes the voltage drop for each path from an output
* pin to an input pin using the segment tree.
=====================================================================*/
int
analog_multi_pin_volt_drop(route, Pstack)
    int route;
    LSTACKPTR Pstack;
{
    void resize_route_width();

    LSTACKPTR Pleaf;
    MDATAPTR Phnode;
    MDATAPTR Ptnode;

    Pleaf = Pstack;
    m_voltage_drop = DBL_MIN;

    while (Pleaf)
    {
	c_voltage_drop = 0.0;
	Ptnode = marray[Pleaf->index];

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

	    if (Ptnode->voltage < EP)
	    {
		Ptnode = Phnode;
		continue;
	    }

	    c_voltage_drop += Ptnode->voltage;
	    Ptnode = Phnode;
	}

	m_voltage_drop = MAX(m_voltage_drop, c_voltage_drop);
	if (m_voltage_drop > max_volt_drop)
	{
	    resize_route_width(route, Pleaf->index);
	}
	Pleaf = Pleaf->next;
    }

    return(TRUE);
} /* end of analog_multi_pin_volt_drop */

/*=====================================================================
*   The function resizes the width of a given route according to the
* voltage drop requirement.
=====================================================================*/
void
resize_route_width(route, index)
    int route;
    int index;
{
    register int i;
    register int j;
    register int d;
    int dist;

    LISTPTR Pnode;
    OFSETPTR Pelist;
    MDATAPTR Phnode;

    i = marray[index]->vertex;
    j = marray[index]->parent;
    j = marray[j]->vertex;
    Pnode = garray[i]->first;

    while (Pnode->t_vertex != j)
    {
	Pnode = Pnode->next;
    }

    Pelist = netlist->Aroute[route]->Pedge;

    while (Pelist->edge != Pnode->edge)
    {
	Pelist = Pelist->next;
    }

    width1 = Pelist->width;
    d = parray[i - numnodes]->density;
    dist = marray[i]->dist - marray[i]->f_node->dist;

    resis1 = R_SHEET * (double) dist * (double) d / (double) width1;
    resis2 = m_voltage_drop / (double) d;

    width2 = (int) (resis1 / resis2) * width1;

    Phnode = marray[i = index]->f_node;

    while (i != Phnode->order)
    {
	Pnode = garray[marray[i]->vertex]->first;
	j = marray[i]->parent;
	i = marray[j]->order;
	j = marray[j]->vertex;

	while (Pnode->t_vertex != j)
	{
	    Pnode = Pnode->next;
	}

	Pelist = netlist->Aroute[route]->Pedge;

	while (Pelist->edge != Pnode->edge)
	{
	    Pelist->width = width2;
	    Pelist = Pelist->next;
	}
    }

    return;
} /* end resize_route_width */
