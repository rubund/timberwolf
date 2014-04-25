#ifndef lint
static char SccsId[] = "@(#)store_route.c	Yale Version 2.5 5/16/91";
#endif
/* -----------------------------------------------------------------

	FILE:		store_route.c
	AUTHOR:		Dahe Chen
	DATE:		Sat May 6 13:05:14 EDT 1989
	CONTENTS:
	REVISION:
		Fri Aug 17 15:47:52 PDT 1990
	    Add one print statement.
		Tue Oct  9 15:55:32 EDT 1990
	    Add statements initializing the fields in Aroute.
		Fri Oct 12 11:25:20 EDT 1990
	    The calculatoin of length of channels is wrong when pins
	    are shifted. Also, when pin are shifted, we may have
	    channels in the channel linked list for a route which
	    should not be there. Add code looking for these channels
	    and do not add them into the linked list.
		Tue Nov 20 18:08:52 EST 1990
	    Remove the function store_external and modify the code
	    to my new style. Change the function from store_internal
	    to store_route.
		Wed Nov 28 21:06:22 EST 1990
	    Remove x and y coordinates of parray.
		Sun Jan 27 16:06:22 EST 1991
	    Change the printout routine to routing.
		Tue Feb  5 13:11:37 EST 1991
	    Set net type.
		Wed Feb 13 17:58:11 EST 1991
	    There are bugs in the code removing an edge from a route.
	    Some cases were not covered in the old code. Rewrite this
	    function to cover all the cases.

----------------------------------------------------------------- */

#include <string.h>
#include <define.h>
#include <gg_router.h>
#include <dgraph.h>
#include <macros.h>
#include <analog.h>

static int distance;
static int mdistance;
static int Mdistance;
static int v1;
static int v2;
static int netCountS = 0;

static PINPTR Ppin;

extern int mlen;
extern int Mlen;
extern int alen;

void
store_route()
{
    unsigned the_route;
    int	i;
    int	j;
    int	e;
    int	length;
    int *Al_off;
    int *Ar_off;

    NETDRPTR Pnet;
    OFSETPTR Pedge;
    ROUTPTR *Aroute;

    the_route = 1;
    distance = 0;
    mdistance = INT_MAX;
    Mdistance = INT_MIN;

    Pnet = (NETDRPTR) Ysafe_malloc(sizeof(NETDR));
    Pnet->net_type = net_type;
    Pnet->name = (char *)
		 Ysafe_malloc((strlen(netName) + 1) * sizeof(char));
    sprintf(Pnet->name, "%s", netName);
    Pnet->num_of_routes = numtrees;
    Pnet->numpins = numpins;
    Pnet->Aroute =
    Aroute = (ROUTPTR *) Ysafe_malloc((numtrees + 1) * sizeof(ROUTPTR));

    if (SHIFTED == TRUE)
    {
	/***********************************************************
	* There are pins shifted from their original locations to
	* avoid overlap of pins with nodes of the channel graph.
	***********************************************************/
	for (i = 1; i <= numpins; i++)
	{
	    Ppin = parray[i];
	    if (Ppin->shifted == FALSE)
	    {
		continue;
	    }
	    v1 = Ppin->node[0];
	    v2 = Ppin->node[1];
	    if (Ppin->dist[0] == 1)
	    {
		Ppin->dist[0]--;
		Ppin->dist[1]++;
		earray[Ppin->edge]->length--;
		earray[numedges+i]->length++;
		if (!earray[Ppin->edge]->length)
		{
		    earray[Ppin->edge]->intree = 0;
		}
	    }
	    else
	    {
		Ppin->dist[0]++;
		Ppin->dist[1]--;
		earray[Ppin->edge]->length++;
		earray[numedges + i]->length--;
		if (!earray[numedges + i]->length)
		{
		earray[numedges + i]->intree = 0;
	    }
	    }
	}
    }

    Al_off = (int *) Ysafe_malloc((numedges + 1) * sizeof(int));
    Ar_off = (int *) Ysafe_malloc((numedges + 1) * sizeof(int));

    for (i = 1; i <= numtrees; i++)
    {
	length = 0;
	Aroute[i] = (ROUTPTR) Ysafe_calloc(1, sizeof(ROUT));

	for (j = 1; j <= numedges; j++)
	{
	    Al_off[j] = -1;
	    Ar_off[j] = -1;
	}

	for (j = 1; j <= totedges; j++)
	{
	    if (earray[j]->intree & the_route)
	    {
		length += earray[j]->length;

		if (j <= numedges)
		{
		    if (earray[j]->node[0] <= numnodes)
		    {
			Al_off[j] = 0;
		    }
		    else
		    {
			ERROR3("\n\n%s, %d\n", __FILE__, __LINE__);
			ERROR1("This line should never be executed\n");
			ERROR1("Call Dahe Chen at (908)580-0102\n\n");
			exit(GP_FAIL);
		    }

		    if (earray[j]->node[1] <= numnodes)
		    {
			Ar_off[j] = 0;
		    }
		    else
		    {
			Ar_off[j] = carray[j]->length - earray[j]->length;
		    }
		}
		else
		{
		    e = parray[j - numedges]->edge;

		    if (earray[j]->node[0] <= numnodes)
		    {
			ERROR3("\n\n%s, %d\n", __FILE__, __LINE__);
			ERROR1("This line should never be executed\n");
			ERROR1("Call Dahe Chen at (908)580-0102\n\n");
			exit(GP_FAIL);
		    }
		    else
		    {
			if (Al_off[e] == -1)
			{
			    Al_off[e] = parray[j - numedges]->dist[0];
			}
			else
			{
			    if (Al_off[e] > parray[j - numedges]->dist[0])
			    {
				Al_off[e] = parray[j - numedges]->dist[0];
			    }
			}
		    }

		    if (earray[j]->node[1] <= numnodes)
		    {
			Ar_off[e] = 0;
		    }
		    else
		    {
			if (Ar_off[e] == -1)
			{
			    Ar_off[e] = parray[j - numedges + 1]->dist[1];
			}
			else
			{
			    if (Ar_off[e] > parray[j-numedges+1]->dist[1])
			    {
				Ar_off[e] = parray[j-numedges+1]->dist[1];
			    }
			}
		    }
		}
	    }
	}

	for (j = 1; j <= numedges; j++)
	{
	    if (Al_off[j] != -1)
	    {
		Pedge = (OFSETPTR) Ysafe_calloc(1, sizeof(OFSET));
		Pedge->edge = j;
		Pedge->l_off = Al_off[j];
		Pedge->r_off = Ar_off[j];
		Pedge->next = Aroute[i]->Pedge;
		Aroute[i]->Pedge = Pedge;
	    }
	}

	if (mdistance > length)
	{
	    mdistance = length;
	}

	if (Mdistance < length)
	{
	    Mdistance = length;
	}

	Aroute[i]->length = length;
	distance += length;
	the_route <<= 1;
    }

    Ysafe_free((char *) Al_off);
    Ysafe_free((char *) Ar_off);

    Pnet->next = netlist;
    netlist = Pnet;

    mlen += mdistance;
    Mlen += Mdistance;
    alen += distance;
    distance /= numtrees;

    totroutes += numtrees;
    if (verboseG)
    {
	PRINT(stdout, "%-20s    %-6d    %-6d   %-6d    %-6d     %-6d\n",
	    netName,
	    numpins,
	    numtrees,
	    mdistance,
	    Mdistance,
	    distance);
	fflush(stdout);
    }
    else
    {
	if (netCountS++ == 0)
	{
	    PRINT(stdout, "Global routing begins...\n");
	    PRINT(stdout, "\n\nGenerating multiple routes...\n");
	}
	else if ((netCountS % 10) == 0)
	{
	    PRINT(stdout, "%4d ", netCountS);
	    if ((netCountS % 150) == 0)
	    {
		PRINT(stdout, "\n");
	    }
	    fflush(stdout);
	}
    }
    PRINT(fdat, "%-20s    %-6d    %-6d   %-6d    %-6d     %-6d\n",
	    netName,
	    numpins,
	    numtrees,
	    mdistance,
	    Mdistance,
	    distance);
    fflush(fdat);
} /* end of store_route */
