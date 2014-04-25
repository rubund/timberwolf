#ifndef lint
static char SccsId[] = "@(#)analog_route.c	Yale Version 2.3 5/16/91";
#endif
/* -----------------------------------------------------------------

	FILE:		analog_route.c
	AUTHOR:		Dahe Chen
	DATE:		Fri Mar 2 21:54:44 EDT 1990
	CONTENTS:	analog_func()
	REVISION:
		Tue Nov 13 15:23:38 EST 1990
	    Rewrite all the functions in the file and split them
	    into several files.
		Fri Dec 21 11:10:33 EST 1990
	    Assign the net type to the field net_type in narray.
	    Remove graphics routine which can be called in dbx for
	    debugging purpose.

----------------------------------------------------------------- */

#include <define.h>
#include <gg_router.h>
#include <dgraph.h>
#include <heap_func.h>
#include <steiner_tree.h>
#define ANALOG
#include <analog.h>
#undef ANALOG

#define TWO 2

extern void analog_two_pin_width();
extern void analog_multi_pin_width();
extern void analog_update_route();
extern void analog_one_route_bound();
extern void analog_one_route_width();
extern int analog_remove_route();
extern int analog_two_pin_upper_bound();
extern int analog_multi_pin_upper_bound();
extern LSTACKPTR analog_find_leaves();

/*=====================================================================
*   This function is a controller for analog nets. It calls different
* functions according to the number of pins for a given net and to
* the uesr-specified requirements.
=====================================================================*/
void
analog_func()
{

    int e;
    int v;
    int number;
    int status;
    int numnode;

    LSTACKPTR Pstack;

    netlist->net_type = net_type;

    if (numtrees == 1)
    {
	/***********************************************************
	* The pins of the net are in the same channel.
	***********************************************************/
	analog_one_route_width();
	analog_one_route_bound();
    }

    /***********************************************************
    * First calculate the wire width of nets and then check the
    * capacitance and resistance upper bounds for all routes.
    ***********************************************************/
    status = FALSE;
    number = netlist->num_of_routes;

    if (numpins == TWO)
    {
	/***********************************************************
	* This net is a two-pin net and each ruote is a simple path
	* in the channel graph.
	***********************************************************/
	for (v = 1; v <= number; v++)
	{
	    analog_two_pin_width(v);

	    if (analog_two_pin_upper_bound(v) == FALSE)
	    {
		/*********************************************************
		* The capacitance upper bound or the resistance upper
		* bound or both are violated. Discard this route.
		*********************************************************/
		status = analog_remove_route(v);
	    }
	}
    }
    else
    {
	/***********************************************************
	* This net is a multiple-pin net. First, generate a segment
	* tree for each route. Then calculate the width for each
	* segment based on the segment tree.
	***********************************************************/
	Adens = (int *) Ysafe_malloc((totedges+1) * sizeof(int));
	Asize = (int *) Ysafe_malloc((totedges+1) * sizeof(int));
	iarray = (short *) Ysafe_malloc((totnodes+1) * sizeof(short)) ;
	jarray = (short *) Ysafe_malloc((totedges+1) * sizeof(short)) ;

	for (v = 1; v <= number; v++)
	{
	    for (e = 1 ; e <= totedges; e++)
	    {
		Adens[e] = 0;
		Asize[e] = 0;
	    }

	    MIN_MASK = get_mask(v-1);

	    /***********************************************************
	    * Create a segment tree for the route and find all the
	    * leaves in the segment tree. And then calculates the width
	    * for each segment in the segment tree.
	    ***********************************************************/
	    numnode = nth_route_segment();
	    Pstack = analog_find_leaves(numnode);
	    analog_multi_pin_width(v, Pstack);

	    if (analog_multi_pin_upper_bound(v, Pstack) == FALSE)
	    {
		/*********************************************************
		* The capacitance upper bound or the resistance upper
		* bound or both are violated. Discard this route.
		*********************************************************/
		status = analog_remove_route(v);
	    }
	}

	Ysafe_free((char *) Adens);
	Ysafe_free((char *) Asize);
	Ysafe_free((char *) iarray);
	Ysafe_free((char *) jarray);
    }

    if (status != FALSE)
    {
	analog_update_route();
    }

    return;

} /* end of analog_func */
