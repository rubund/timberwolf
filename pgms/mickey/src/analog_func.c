#ifndef lint
static char SccsId[] = "@(#)analog_func.c	Yale Version 2.3 5/16/91";
#endif
/* -----------------------------------------------------------------

	FILE:		analog_func.c
	AUTHOR:		Dahe Chen
	DATE:		Tue Nov 13 16:19:54 EST 1990
	CONTENTS:	Miscellaneous functions for analog VLSI
		circuits.
	REVISION:
		Tue Feb  5 11:51:35 EST 1991
	    Reformat error message output.

----------------------------------------------------------------- */

#include <define.h>
#include <gg_router.h>
#include <heap_func.h>
#include <steiner_tree.h>
#include <dgraph.h>
#include <macros.h>
#include <analog.h>

/*=====================================================================
*   This function deletes the given route from the list of routes in
* the net. Free the memory allocated for the route and assign a null
* pointer to the entry for this route in the route array.
=====================================================================*/ 
int
analog_remove_route(route)
    int route;
{

    OFSETPTR Pdlist;
    OFSETPTR Pelist;

    Pelist = netlist->Aroute[route]->Pedge;

    while (Pelist != NIL(OFSET))
    {
	Pdlist = Pelist->next;
	Ysafe_free((char *) Pelist);
	Pelist = Pdlist;
    }

    netlist->Aroute[route] = NIL(ROUT);

    return(TRUE);

} /* end of analog_remove_route */

/*=====================================================================
*   This function scans through the route array of the given net and
* shifts down all the entries of the array to fill any empty entries
* in the array caused by removing from the list of routes for the net.
=====================================================================*/
void
analog_update_route()
{

    int i;
    int j;
    int number;

    ROUTPTR *Aroute;

    number = netlist->num_of_routes;
    Aroute = netlist->Aroute;

    for (i = 1, j = 2; j <= number; )
    {
	if (Aroute[i] != NIL(ROUT))
	{
	    i++;
	    j++;
	}
	else
	{
	    while (j <= number && Aroute[j] == NIL(ROUT))
		j++;
	    if (j <= number)
	    {
		Aroute[i++] = Aroute[j];
		Aroute[j++] = NIL(ROUT);
	    }
	}
    }

    if (--i < 1)
    {
	ERROR2("\n\nNo route for net %s ", netlist->name);
	ERROR1("can meet constraints\n");
	exit(GP_FAIL);
    }

    netlist->num_of_routes = i;
    netlist->Aroute = (ROUTPTR *) Ysafe_realloc((char *) Aroute,
				    (i+1) * sizeof(ROUTPTR));

    return;

} /* end of analog_update_route */

/*===================================================================== 
*   This function scans through all the pins if the net has equivalent
* pins or all the vertices in the segment tree if the net does not have
* equivalent pins finds all the pins which are a leaf in the segment
* tree and stores them in a stack. The function returns the pointer to
* the head of the stack.
=====================================================================*/ 
LSTACKPTR
analog_find_leaves(numnode)
    int numnode ;
{

    int i;
    int j;
    int k;
    int degree;
    int checked;
    int leaf_pin;

    LISTPTR Pnode;
    LSTACKPTR Pstack;
    LSTACKPTR Pleaf;
    PINPTR Pnext;

    Pstack = NIL(LSTACK);
    if (EQUIVAL != FALSE)
    {
	/***********************************************************
	* There are equivalent pins in the set of pins. First assign
	* different numbers to key as an indicator to the type of
	* the pin.
	* key < 0 --- the pin is not an equivalent pin.
	* key = 0 --- the pin is an equivalent pin and also is an
	*			isolated pin.
	* key > 0 --- the pin is an equivalent pin but is not an
	*		    isolated pin. Furthermore, the degree
	*		    associated with the pin is equal to key.
	***********************************************************/
	checked = 2358;	/* arbitrary number */
	for (i = 1; i <= numpins; i++)
	{
	    parray[i]->key = -1;
	    if (parray[i]->next != NIL(PIN))
	    {
		/*********************************************************
		* Count the degree of the pin according to the route.
		*********************************************************/
		degree = 0;
		Pnode = garray[numnodes+i]->first;
		while (Pnode)
		{
		    if ((earray[Pnode->edge]->intree & MIN_MASK) != FALSE)
		    {
			degree++;
		    }
		    Pnode = Pnode->next;
		}
		parray[i]->key = degree;
	    }
	}

	for (i = 1; i <= numnode; i++)
	{
	    if (marray[i]->leaf != FALSE)
	    {
		j = marray[i]->vertex - numnodes;
		if (parray[j]->key < 0)
		{
		    /*****************************************************
		    * The pin is not an equivalent pin. Thus it is really
		    * a leaf pin.
		    *****************************************************/
		    Pleaf = (LSTACKPTR) Ysafe_malloc(sizeof(LSTACK));
		    Pleaf->index = i;
		    Pleaf->next = Pstack;
		    Pstack = Pleaf;
		}
		else
		{
		    if (parray[j]->key == checked)
		    {
			/*************************************************
			* The set is checked already. Skip it.
			*************************************************/
			continue;
		    }

		    /*****************************************************
		    * The pin is an equivalent pin. Go through the set of
		    * equivalent pins and check if the set is a leaf set.
		    *****************************************************/
		    leaf_pin = 0;
		    Pnext = parray[j];
		    do
		    {
			if (Pnext->key == 1)
			{
			    /*********************************************
			    * The pin has a degree of one.
			    *********************************************/
			    if (leaf_pin != FALSE)
			    {
				/*****************************************
				* There is already a previous pin in the
				* set of equivalent pins having a degree
				* of 1.
				*****************************************/
				if (leaf_pin > 0)
				{
				    leaf_pin = -1;
				}
			    }
			    else
			    {
				/*****************************************
				* No previous pins in the set of
				* equivalent pins have a degree of 1.
				*****************************************/
				leaf_pin = Pnext->vertex;
			    }
			}
			else
			{
			    if (Pnext->key > 0)
			    {
				leaf_pin = -1;
			    }
			}
			Pnext->key = checked;
			Pnext = Pnext->next;
		    } while (Pnext != parray[j]);

		    if (leaf_pin > 0)
		    {
			leaf_pin += numnodes;
			for (k = 1; marray[k]->vertex != leaf_pin; k++)
			    ;
			if (leaf_pin != marray[1]->vertex)
			{
			    Pleaf = (LSTACKPTR)
					Ysafe_malloc(sizeof(LSTACK));
			    Pleaf->index = k;
			    Pleaf->next = Pstack;
			    Pstack = Pleaf;
			}
		    }
		}
	    }
	}
    }
    else
    {
	for (i = 1; i <= numnode; i++)
	{
	    if (marray[i]->leaf != FALSE)
	    {
		Pleaf = (LSTACKPTR) Ysafe_malloc(sizeof(LSTACK));
		Pleaf->index = i;
		Pleaf->next = Pstack;
		Pstack = Pleaf;
	    }
	}
    }

    return(Pstack);

} /* end of analog_find_leaves */
