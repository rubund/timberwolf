#ifndef lint
static char SccsId[] = "@(#)find_zero_cap_channel.c	Yale Version 1.4 5/16/91" ;
#endif
/* -----------------------------------------------------------------

	FILE:		find_zero_cap_channel.c
	AUTHOR:		Dahe Chen
	DATE:		Tue Dec  4 11:34:17 EST 1990
	CONTENTS:	This file contains functions finding channels
			with zero capacity and the routes which uss
			these channels.
	REVISION:
		Thu Jan 10 11:29:39 EST 1991
	    There are bugs in the code removing a middle route from
	    the set of routes.
		Thu Jan 24 13:24:47 EST 1991
	    There are bugs in setting the capacity of the channels
	    with indices higher than numedges.
		Tue Feb  5 12:03:44 EST 1991
	    Reformat error message output.
		Tue Mar  5 11:07:09 EST 1991
	    Change fclose to TWCLOSE.

----------------------------------------------------------------- */

#include <define.h>
#include <macros.h>
#include <gg_router.h>
#include <heap_func.h>
#include <steiner_tree.h>
#include <yalecad/file.h>
#include <yalecad/string.h>

extern unsigned get_mask();

static int *Azero;

/*=====================================================================
*   In this function, the capacity of each channel is read in from the
* file ckt.mgph and the channels with zero capacity are stored in the
* array Azero.
=====================================================================*/
int
find_zero_cap_channels()
{

    char input[LRECL];
    char **tokens;
    INT numtokens;
    int e;
    int i;
    int v1;
    int v2;
    int status = FALSE;

    FILE *fp;
    LISTPTR Pnode;

    fp = FOPEN("mgph","r");
    Azero = (int *) Ysafe_calloc((totedges+1), sizeof(int));
    while (fgets(input, LRECL, fp))
    {
	tokens = Ystrparser(input, " \n\t", &numtokens);
	if (atoi(tokens[6]) == 0)
	{
	    v1 = atoi(tokens[1]);
	    v2 = atoi(tokens[2]);
	    Pnode = garray[v1]->first;
	    while (Pnode)
	    {
		if (Pnode->t_vertex > numnodes)
		{
		    i = Pnode->t_vertex - numnodes;
		    if (parray[i]->node[0] == v1
		     && parray[i]->node[1] == v2)
		    {
			break;
		    }
		}
		else
		{
		    if (Pnode->t_vertex == v2)
		    {
			break;
		    }
		}
		Pnode = Pnode->next;
	    }
	    Azero[Pnode->edge] = TRUE;
	    status = TRUE;
	}
    }
    TWCLOSE(fp);

    for (i = numedges + 1; i <= totedges; i++)
    {
	e = parray[i - numedges]->edge;
	Azero[i] = Azero[e];
    }

    return(status);

} /* end of find_zero_cap_channels */

/*=====================================================================
*   This function finds the channels with zero capacity and with routes
* in. Removes the routes in these channels.
=====================================================================*/
void
check_zero_cap_channels()
{

    int *Aroute;
    int i;
    int j;
    int numrtes;
    unsigned mask;
    unsigned l_bits;
    unsigned r_bits;

    /***********************************************************
    * Find the routes using zero capacity channel(s).
    ***********************************************************/
    Aroute = (int *) Ysafe_calloc((numtrees+1), sizeof(int));
    for (i = 1; i <= totedges; i++)
    {
	if (Azero[i] != FALSE && earray[i]->intree)
	{
	    /***********************************************************
	    * The channel has zero capacity and has routes in it.
	    ***********************************************************/
	    for (j = 0; j < numtrees; j++)
	    {
		mask = get_mask(j);
		if (earray[i]->intree & mask)
		{
		    Aroute[j+1] = TRUE;
		}
	    }
	}
    }

    /***********************************************************
    * Count the number of routes using zero capacity channel(s).
    ***********************************************************/
    numrtes = 0;
    for (i = 1; i <= numtrees; i++)
    {
	if (Aroute[i] != FALSE)
	{
	    numrtes++;
	}
    }

    if (numrtes == numtrees)
    {
	ERROR1("\n\n");
	ERROR2("All the routes for net %s use infeasible channel(s)\n",
	    netName);
	exit(GP_FAIL);
    }

    /***********************************************************
    * Remove the routes using zero capacity channel(s).
    ***********************************************************/
    for (i = numtrees; i >= 1; i--)
    {
	if (Aroute[i] != FALSE)
	{
	    if (i == numtrees)
	    {
		/*********************************************************
		* The route to be removed is the last route.
		*********************************************************/
		mask = ~get_mask(i - 1);
		for (j = 1; j <= totedges; j++)
		{
		    earray[j]->intree &= mask;
		}
	    }
	    else
	    {
		/*********************************************************
		* The route to be removed is not the last route. We need
		* to shift the routes whose bits are on the left side of
		* the removed route to the right by one.
		*********************************************************/
		for (j = 1; j <= totedges; j++)
		{
		    l_bits = (earray[j]->intree & (~0 << i)) >> 1;
		    r_bits = earray[j]->intree & ~(~0 << (i -1));
		    earray[j]->intree = l_bits | r_bits;
		}
	    }
	    numtrees--;
	}
    }

    Ysafe_free((char *) Azero);
    Ysafe_free((char *) Aroute);

    return;

} /* end of check_zero_cap_channels */
