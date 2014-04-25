#ifndef lint
static char SccsId[] = "@(#)analog_random_interchange.c	Yale Version 1.7 5/29/91";
#endif
/* -----------------------------------------------------------------

	FILE:		analog_random_interchange.c
	AUTHOR:		Dahe Chen
	DATE:		Wed Dec 12 15:56:09 EST 1990
	CONTENTS:	Functions in this file find the initial
		measure of the constraint violations for a given
		routing configuration; reduce this cost by the
		random interchange algorithm; and calculate the
		penalty for each edge violating the constraints.
	REVISION:
		Tue Apr 30 11:31:58 EDT 1991
	    Re-write the optimization procedure.
		Tue May 28 18:18:44 EDT 1991
	    Move cast from left to right.

----------------------------------------------------------------- */

#include <define.h>
#include <macros.h>
#include <gg_router.h>
#include <dgraph.h>
#include <analog.h>
#include <analog_min.h>
#include <yalecad/file.h>
#include <yalecad/string.h>

#define FIRST_ROUTE	1

extern void	print_iteration();
extern void	print_overflow();

static int	n_index;
static int	o_index;
static int	r_index;
static int	init_densityS;
static int	min_densityS;
static int	tot_densityS;
static int	init_penaltyS;
static int	min_penaltyS;
static int	tot_penaltyS;
static int	init_lengthS;
static int	min_lengthS;
static int	tot_lengthS;
static int	numberS;
static int	numnetsS;

static int	*Aact_nets;
static ACTSET	**AsetS;
static CLIST	**Achannels;

/*=====================================================================
*   Set a random seed for the random number generator.
=====================================================================*/
static void analog_set_random_seed()
{
    extern void YcurTime();
    extern void Yset_random_seed();

    char input[LRECL];
    int seed;
    FILE *fseed;

    /***********************************************************
    * Check if the file storing a random seed exists. If such a
    * file exists, read the seed; otherwise, generate a random
    * seed. This is very useful for debugging since we can re-
    * produce the run when it causes a crash.
    ***********************************************************/
    (void) sprintf(input, "%s.seed", cktName);
    if (fseed = TWOPEN(input, "r", NOABORT))
    {
	if (fgets(input, 128, fseed))
	{
	    seed = atoi(input);
	}
	TWCLOSE(fseed);
    }
    else
    {
	/***********************************************************
	* Get a random seed for the random number generator.
	***********************************************************/
	YcurTime(&seed);
    }
    Yset_random_seed(seed);
}

/*=====================================================================
*   Set FIRST_ROUTE as the initial route for all the nets.
=====================================================================*/
static void analog_set_initial_route()
{
    register int n;

    for (n = 1; n <= numnets; n++)
    {
        narray[n]->route = FIRST_ROUTE;
    }
}

/*=====================================================================
*   If file ckt.madj exists, there are edges overlapping. Read in the
* active sets and count the their number and the number of edges which
* are in one or more active set.
=====================================================================*/
static void analog_build_active_set()
{
    char input[LRECL];
    char **tokens;
    INT numtokens;
    int numedge;
    register int i;
    register int v1;
    register int v2;
    int *Astatus;
    FILE *fp;

    ACTSET *Pset;
    CLISTPTR Pnew;
    LISTPTR Pnode;

    AsetS = (ACTSETPTR *)Ysafe_malloc(numedges * sizeof(ACTSETPTR));
    Astatus = (int *)Ysafe_calloc((numedges+1), sizeof(int));

    numsets = numedge = 0;

    /***********************************************************
    * Check if the file ckt.madj exists. If so, there are
    * channels overlapping one another. Read in the active sets
    * and count the numberS of active sets and the numberS of
    * channels which are in one or more active sets.
    ***********************************************************/
    (void)sprintf(input, "%s.madj", cktName);
    if ((fp = TWOPEN(input, "r", NOABORT)) != NULL)
    {
	while (fgets(input, LRECL, fp))
	{
	    tokens = Ystrparser(input, " \t", &numtokens);
	    if (strncmp(tokens[0], "active", 6) == STRINGEQ)
	    {
		/*********************************************************
		* A new active set is reached. Allocate memory in the
		* set array and increment the numberS of active sets by
		* one.
		*********************************************************/
		AsetS[numsets++] =
		Pset = (ACTSETPTR)Ysafe_calloc(1, sizeof(ACTSET));
	    }
	    else
	    {
		if (strncmp(tokens[0], "channel", 7) == STRINGEQ)
		{
		    /*****************************************************
		    * A channel is read in. Find the channel index and
		    * store it. Also, count the numberS of channels which
		    * are in one or more active sets.
		    *****************************************************/
		    v1 = atoi(tokens[1]);
		    v2 = atoi(tokens[2]);
		    Pnode = garray[v1]->first;
		    while (Pnode->t_vertex != v2)
		    {
			Pnode = Pnode->next;
		    }
		    Pnew = (CLISTPTR)Ysafe_malloc(sizeof(CLIST));
		    Pnew->index = Pnode->edge;
		    Pnew->next = Pset->Phead;
		    Pset->Phead = Pnew;
		    if (!Astatus[Pnode->edge])
		    {
			numedge++;
			Astatus[Pnode->edge] = TRUE;
		    }
		}
		else
		{
		    ERROR3("\n\nUnknown key word %s in the file %s\n",
			tokens[0], cktName);
		    exit(GP_FAIL);
		}
	    }
	}
    }

    /***********************************************************
    * The total numberS of active sets, including single channels
    * without overlapping is:
    ***********************************************************/
    numberS = numsets + numedges - numedge;

    AsetS = (ACTSETPTR *)Ysafe_realloc((char *)AsetS, numberS*sizeof(ACTSETPTR));

    /***********************************************************
    * Complete the array of active sets with the channels with-
    * out overlapping.
    ***********************************************************/
    for (i = 1; i <= numedges; i++)
    {
	if (Astatus[i] == FALSE)
	{
	    /***********************************************************
	    * The channel is not in an active set of channels. Add it
	    * to the array AsetS.
	    ***********************************************************/
	    AsetS[numsets++] =
	    Pset = (ACTSETPTR)Ysafe_calloc(1, sizeof(ACTSET));
	    Pset->Phead = (CLISTPTR)Ysafe_malloc(sizeof(CLIST));
	    Pset->Phead->index = i;
	    Pset->Phead->next = NIL(CLIST);
	}
    }
    Ysafe_cfree((char *) Astatus);
}

/*=====================================================================
*   Make the array Achannels which are sets of linked lists of active
* sets containing a channel. Also, build the pin array for each active
* set.
=====================================================================*/
static void analog_build_channels()
{
    register int i;
    register int count;
    int *Acounts;
    int *Alimits;
    int distance;
    int v1;
    int e;
    int j;
    int k;

    CHANSPTR *Achan;
    CLISTPTR Pnew;
    CLISTPTR Pblist;
    DENSPTR **Adensity;

    Achannels = (CLISTPTR *)Ysafe_calloc((numedges+1),sizeof(CLISTPTR));

    for (i = 0; i < numberS; i++)
    {
	count = 0;
	numpins = 0;
	Pblist = AsetS[i]->Phead;
	while (Pblist)
	{
	    /***********************************************************
	    * Make the linked list of active sets containing the channel
	    ***********************************************************/
	    Pnew = (CLISTPTR)Ysafe_calloc(1, sizeof(CLIST));
	    Pnew->index = i;
	    Pnew->next = Achannels[Pblist->index];
	    Achannels[Pblist->index] = Pnew;

	    /***********************************************************
	    * Count the numberS of channels in the active set and the
	    * numberS of pins in the channels.
	    ***********************************************************/
	    numpins += dearray[Pblist->index]->numpin;
	    count++;

	    Pblist = Pblist->next;
	}

	Achan = (CHANSPTR *)Ysafe_calloc(numpins, sizeof(CHANSPTR));
	Adensity = (DENSPTR **)Ysafe_malloc(count * sizeof(DENSPTR *));
	Acounts = (int *)Ysafe_malloc(count * sizeof(int));
	Alimits = (int *)Ysafe_malloc(count * sizeof(int));

	/***********************************************************
	* Use array Adensity to merge the pins of the channels in the
	* active set.
	***********************************************************/
	for (j = 0, Pblist = AsetS[i]->Phead; Pblist; Pblist = Pblist->next)
	{
	    if (dearray[Pblist->index]->Adens)
	    {
		Acounts[j] = 0;
		Alimits[j] = dearray[Pblist->index]->numpin;
		Adensity[j++] = dearray[Pblist->index]->Adens;
	    }
	    else
	    {
		Acounts[j] = 0;
		Alimits[j] = 0;
		Adensity[j++] = NIL(DENSPTR);
	    }
	}

	e = 0;
	while (TRUE)
	{
	    k = INT_MIN;
	    distance = INT_MAX;
	    for (j = 0; j < count; j++)
	    {
		if (Adensity[j])
		{
		    v1 = Acounts[j];
		    if (v1 < Alimits[j])
		    {
			if (Adensity[j][v1]->distance < distance)
			{
			    k = j;
			    distance = Adensity[j][v1]->distance;
			}
			else
			{
			    if (Adensity[j][v1]->distance == distance)
			    {
				Acounts[j]++;
			    }
			}
		    }
		    else
		    {
			Adensity[j] = NIL(DENSPTR);
		    }
		}
	    }
	    if (k < 0)
	    {
		break;
	    }
	    else
	    {
		Achan[e] = (CHANSPTR)Ysafe_calloc(1, sizeof(CHANS));
		Achan[e++]->distance = Adensity[k][Acounts[k]]->distance;
		Acounts[k]++;
	    }
	}

	if (e == 0)
	{
	    Ysafe_cfree((char *) Achan);
	    AsetS[i]->Achan = NIL(CHANSPTR);
	}
	else
	{
	    AsetS[i]->Achan = (CHANSPTR *)Ysafe_realloc((char *)Achan,
	    	e * sizeof(CHANSPTR));
	}
	AsetS[i]->numpin = e;

	Ysafe_free((char *) Acounts);
	Ysafe_free((char *) Alimits);
	Ysafe_free((char *) Adensity);
    }
}

/*=====================================================================
*   Find and initialize the active set.
=====================================================================*/
static void analog_find_active_set()
{
    analog_build_active_set();
    analog_build_channels();
}

/*=====================================================================
*   Compute the edge density over all the edges.
=====================================================================*/
static int analog_init_density()
{
    register int e;
    register int j;
    register int k;
    int c;
    int n;
    int r;
    int number;
    int distance;

    DEDGEPTR Pedge;
    DENSPTR *Adens;
    HLISTPTR *Aindex;
    NLISTPTR Pnet;
    OFSETPTR Pelist;

    /***********************************************************
    * For each net, assign its current route to the initial
    * configuration.
    ***********************************************************/
    for (n = 1; n <= numnets; n++)
    {
	r = narray[n]->route;
	if (!narray[n]->Aroute[r]->length)
	{
	    /***********************************************************
	    * The length of the route is zero, that is, its two pins
	    * locate on the opposite side of the same channel. This
	    * route wont be inserted into the density array for the
	    * calcualtion of the channel density of this channel since
	    * it does not affect the channel density.
	    ***********************************************************/
	    continue;
	}

	Pelist = narray[n]->Aroute[r]->Pedge;

	while (Pelist)
	{
	    e = Pelist->edge;
	    Adens = dearray[e]->Adens;

	    if (!Pelist->l_off && !Pelist->r_off)
	    {
		/*********************************************************
		* The segment crosses the channel. Insert it into the list
		* for crossing segments, which is headed by field Pcnet in
		* dearray.
		*********************************************************/
		Pnet = (NLISTPTR)Ysafe_malloc(sizeof(NLIST));
		Pnet->net = n;
		Pnet->prev = NIL(NLIST);
		Pnet->next = dearray[e]->Pcnet;

		if (dearray[e]->Pcnet)
		{
		    dearray[e]->Pcnet->prev = Pnet;
		}
		dearray[e]->Pcnet = Pnet;
		dearray[e]->density += Pelist->width;
	    }
	    else if (Pelist->l_off && Pelist->r_off)
	    {
		/*********************************************************
		* The both sides of the segment end in this channel. Use
		* the binary search to find the left end and scan through
		* to the right end.
		*********************************************************/
		j = k = dearray[e]->numpin / 2;
		while (Adens[j]->distance != Pelist->l_off)
		{
		    if (Pelist->l_off < Adens[j]->distance)
		    {
			/*************************************************
			* The left end is on the left side of pin j.
			*************************************************/
			j /= 2;
			k /= 2;
		    }
		    else
		    {
			/*************************************************
			* The left end is on the right side of pin j.
			*************************************************/
			if (k)
			{
			    k /= 2;
			    j += k;
			}
			else
			{
			    j++;
			}
		    }
		}

		distance = dearray[e]->length - Pelist->r_off;
		for (; Adens[j]->distance <= distance; j++)
		{
		    /*****************************************************
		    * The net crosses this pin. Insert the net into the
		    * net list of this pin and update the local density.
		    *****************************************************/
		    Pnet = (NLISTPTR)Ysafe_malloc(sizeof(NLIST));
		    Pnet->net = n;
		    Pnet->prev = NIL(NLIST);
		    Pnet->next = Adens[j]->Pnlist;
		    if (Adens[j]->Pnlist)
		    {
			Adens[j]->Pnlist->prev = Pnet;
		    }
		    Adens[j]->Pnlist = Pnet;
		    Adens[j]->density += Pelist->width;
		}
	    }
	    else
	    {
		/*********************************************************
		* One side of the segment ends in this channel. Scan pins
		* on the channel started from the left side if its right
		* side ends in the channel, started from the right side
		* if its left side ends in the channel.
		*********************************************************/
		if (!Pelist->l_off)
		{
		    distance = dearray[e]->length - Pelist->r_off;
		    for (j = 0; Adens[j]->distance <= distance; j++)
		    {
			/*************************************************
			* The net crosses this pin. Insert the net into	
			* the net list of this pin and update the local
			* density.
			*************************************************/
			Pnet = (NLISTPTR)Ysafe_malloc(sizeof(NLIST));
			Pnet->net = n;
			Pnet->prev = NIL(NLIST);
			Pnet->next = Adens[j]->Pnlist;
			if (Adens[j]->Pnlist)
			{
			    Adens[j]->Pnlist->prev = Pnet;
			}
			Adens[j]->Pnlist = Pnet;
			Adens[j]->density += Pelist->width;
		    }
		}
		else
		{
		    j = dearray[e]->numpin - 1;
		    for (; Adens[j]->distance >= Pelist->l_off; j--)
		    {
			/*************************************************
			* The net crosses this pin. Insert the net into
			* the net list of this pin and update the local
			* density.
			*************************************************/
			Pnet = (NLISTPTR)Ysafe_malloc(sizeof(NLIST));
			Pnet->net = n;
			Pnet->prev = NIL(NLIST);
			Pnet->next = Adens[j]->Pnlist;
			if (Adens[j]->Pnlist)
			{
			    Adens[j]->Pnlist->prev = Pnet;
			}
			Adens[j]->Pnlist = Pnet;
			Adens[j]->density += Pelist->width;
		    }
		}
	    }
	    Pelist = Pelist->next;
	}
    }

    /***********************************************************
    * Build up a priority tree of local densities over all pins
    * on a channel for each of channels, including two ends of
    * the channel.
    ***********************************************************/
    for (e = 1; e <= numedges; e++)
    {
	if (!dearray[e]->numpin)
	{
	    /***********************************************************
	    * This channel does not have any pins on it. So skip it.
	    ***********************************************************/
	    continue;
	}

	number = dearray[e]->numpin;
	Adens = dearray[e]->Adens;
	dearray[e]->Aindex =
	Aindex = (HLISTPTR *)Ysafe_malloc((number+1) * sizeof(HLISTPTR));
	Aindex[0] = (HLISTPTR)Ysafe_malloc(sizeof(HLIST));
	Aindex[0]->index = 0;
	Aindex[0]->key = INT_MAX;
	Aindex[0]->pin = 0;

	for (j = 1; j <= number; j++)
	{
	    Aindex[j] = (HLISTPTR)Ysafe_malloc(sizeof(HLIST));
	    Aindex[j]->index = j;
	    Aindex[j]->key = 0;
	    Aindex[j]->pin = j - 1;
	    Adens[j-1]->Pheap = Aindex[j];
	}

	for (j = 0; j < number; j++)
	{
	    dens_insert(Aindex, Adens[j]->density);
	}
    }

    c = 0;
    for (e = 1; e <= numedges; e++)
    {
	if ((Pedge = dearray[e])->numpin)
	{
	    Pedge->weight = Pedge->density
			  + Pedge->Aindex[1]->key
			  - Pedge->capacity;
	}
	else
	{
	    Pedge->weight = Pedge->density - Pedge->capacity;
	}

	if (Pedge->weight > 0)
	{
	    c += Pedge->weight;
	}
    }
    return(c);
}

/*=====================================================================
*   Test if the condition 5.9 is satisfied. If so, return 0, otherwise,
* return the number of shielding net required.
=====================================================================*/
static int analog_compute_penalty(n1, n2, n3, n4)
    int n1;
    int n2;
    int n3;
    int n4;
{
    register int n;

    if (n1 > 0)
    {
        if (n2 * n3 > 0)
	{
	    n = n1 + 1;
	}
	else if (n2 + n3 > 0)
	{
	    n = n1;
	}
	else
	{
	    n = n1 - 1;
	}
    }
    else
    {
        if (n2 * n3 > 0)
	{
	    n = 1;
	}
	else
	{
	    n = 0;
	}
    }
    return((n > n4) ? (n - n4) : 0);
}

/*=====================================================================
*   For a given routing configuration, compute the signal-coupling
* penalty.
=====================================================================*/
static int analog_init_penalty()
{
    int number;
    int distance;
    int e;
    int i;
    int j;
    int k;
    int p;
    int r;

    CHANSPTR *Achan;
    CLISTPTR Pblist;
    HLISTPTR *Aindex;
    NLISTPTR Pnlist;
    OFSETPTR Pelist;

    for (i = 1; i <= numnets; i++)
    {
	r = narray[i]->route;

	if (!narray[i]->Aroute[r]->length)
	{
	    /***********************************************************
	    * The length of the route is zero, that is, its two pins
	    * locate on the opposite side of the same channel. This
	    * route wont be inserted into the density array for the
	    * calcualtion of the channel density of this channel since
	    * it does not affect the channel density.
	    ***********************************************************/
	    continue;
	}

	Pelist = narray[i]->Aroute[1]->Pedge;

	while (Pelist)
	{
	    Pblist = Achannels[Pelist->edge];

	    if (!Pelist->l_off && !Pelist->r_off)
	    {
		/*********************************************************
		* The segment crosses the channel. Insert it into the list
		* for crossing segments, which is headed by field Pcnet in
		* dearray.
		*********************************************************/
		while (Pblist)
		{
		    e = Pblist->index;
		    Pnlist = (NLISTPTR)Ysafe_malloc(sizeof(NLIST));
		    Pnlist->net = i;
		    Pnlist->prev = NIL(NLIST);
		    Pnlist->next = AsetS[e]->Pnlist;

		    if (AsetS[e]->Pnlist)
		    {
			AsetS[e]->Pnlist->prev = Pnlist;
		    }
		    AsetS[e]->Pnlist = Pnlist;
		    switch (narray[i]->net_type)
		    {
			case MIXED:
			    AsetS[e]->mixed++;
			    break;

			case NOISY:
			    AsetS[e]->noisy++;
			    break;

			case SENSITIVE:
			    AsetS[e]->sensitive++;
			    break;

			case SHIELD:
			    AsetS[e]->shielding++;
			    break;

			default:
			    ERROR1("\n\n");
			    ERROR3("Unknown net type %d for the net %s\n",
				    narray[i]->net_type,
				    narray[i]->name);
			    exit(GP_FAIL);
		    }
		    Pblist = Pblist->next;
		}
	    }
	    else if (Pelist->l_off && Pelist->r_off)
	    {
		/*********************************************************
		* The both sides of the segment end in this channel. Use
		* the binary search to find the left end and scan through
		* to the right end.
		*********************************************************/
		while (Pblist)
		{
		    e = Pblist->index;
		    Achan = AsetS[e]->Achan;
		    j = k = AsetS[e]->numpin / 2;
		    while (Achan[j]->distance != Pelist->l_off)
		    {
			if (Pelist->l_off < Achan[j]->distance)
			{
			    /*********************************************
			    * The left end is on the left side of pin j.
			    *********************************************/
			    j /= 2;
			    k /= 2;
			}
			else
			{
			    /*********************************************
			    * The left end is on the right side of pin j.
			    *********************************************/
			    if (k)
			    {
				k /= 2;
				j += k;
			    }
			    else
			    {
				j++;
			    }
			}
		    }

		    distance = dearray[Pelist->edge]->length
			     - Pelist->r_off;

		    for (; Achan[j]->distance <= distance; j++)
		    {
			/*************************************************
			* The net crosses this pin. Insert the net into
			* the net list of this pin and update the local
			* density.
			*************************************************/
			Pnlist = (NLISTPTR)Ysafe_malloc(sizeof(NLIST));
			Pnlist->net = i;
			Pnlist->prev = NIL(NLIST);
			Pnlist->next = Achan[j]->Pnlist;
			if (Achan[j]->Pnlist)
			{
			    Achan[j]->Pnlist->prev = Pnlist;
			}
			Achan[j]->Pnlist = Pnlist;
			switch (narray[i]->net_type)
			{
			    case MIXED:
				Achan[j]->mixed++;
				break;

			    case NOISY:
				Achan[j]->noisy++;
				break;

			    case SENSITIVE:
				Achan[j]->sensitive++;
				break;

			    case SHIELD:
				Achan[j]->shielding++;
				break;

			    default:
				ERROR2("\n\nUnknown net type %d for the ",
					narray[i]->net_type);
				ERROR2("net %s\n", narray[i]->name);
				exit(GP_FAIL);
			}
		    }
		    Pblist = Pblist->next;
		}
	    }
	    else
	    {
		/*********************************************************
		* One side of the segment ends in this channel. Scan pins
		* on the channel started from the left side if its right
		* side ends in the channel, started from the right side
		* if its left side ends in the channel.
		*********************************************************/
		if (!Pelist->l_off)
		{
		    while (Pblist)
		    {
			e = Pblist->index;
			Achan = AsetS[e]->Achan;
			distance = dearray[Pelist->edge]->length
				 - Pelist->r_off;
			for (j = 0; Achan[j]->distance <= distance; j++)
			{
			    /*********************************************
			    * The net crosses this pin. Insert the net
			    * into the net list of this pin and update
			    * the local density.
			    *********************************************/
			    Pnlist = (NLISTPTR)Ysafe_malloc(sizeof(NLIST));
			    Pnlist->net = i;
			    Pnlist->prev = NIL(NLIST);
			    Pnlist->next = Achan[j]->Pnlist;
			    if (Achan[j]->Pnlist)
			    {
				Achan[j]->Pnlist->prev = Pnlist;
			    }
			    Achan[j]->Pnlist = Pnlist;
			    switch (narray[i]->net_type)
			    {
				case MIXED:
				    Achan[j]->mixed++;
				    break;

				case NOISY:
				    Achan[j]->noisy++;
				    break;

				case SENSITIVE:
				    Achan[j]->sensitive++;
				    break;

				case SHIELD:
				    Achan[j]->shielding++;
				    break;

				default:
				    ERROR1("\n\n");
				    ERROR2("Unknown net type %d for the ",
					    narray[i]->net_type);
				    ERROR2("net %s\n", narray[i]->name);
				    exit(GP_FAIL);
			    }
			}
			Pblist = Pblist->next;
		    }
		}
		else
		{
		    while (Pblist)
		    {
			e = Pblist->index;
			Achan = AsetS[e]->Achan;
			j = AsetS[e]->numpin - 1;
			for (; Achan[j]->distance >= Pelist->l_off; j--)
			{
			    /*********************************************
			    * The net crosses this pin. Insert the net
			    * into the net list of this pin and update
			    * the local density.
			    *********************************************/
			    Pnlist = (NLISTPTR)Ysafe_malloc(sizeof(NLIST));
			    Pnlist->net = i;
			    Pnlist->prev = NIL(NLIST);
			    Pnlist->next = Achan[j]->Pnlist;
			    if (Achan[j]->Pnlist)
			    {
				Achan[j]->Pnlist->prev = Pnlist;
			    }
			    Achan[j]->Pnlist = Pnlist;
			    switch (narray[i]->net_type)
			    {
				case MIXED:
				    Achan[j]->mixed++;
				    break;

				case NOISY:
				    Achan[j]->noisy++;
				    break;

				case SENSITIVE:
				    Achan[j]->sensitive++;
				    break;

				case SHIELD:
				    Achan[j]->shielding++;
				    break;

				default:
				    ERROR1("\n\n");
				    ERROR2("Unknown net type %d for the ",
					    narray[i]->net_type);
				    ERROR2("net %s\n", narray[i]->name);
				    exit(GP_FAIL);
			    }
			}
			Pblist = Pblist->next;
		    }
		}
	    }
	    Pelist = Pelist->next;
	}
    }

    /***********************************************************
    * Build up a priority tree of local penalties over all pins
    * on a channel for each of active sets, including two ends
    * of the active set.
    ***********************************************************/
    for (i = 0; i < numsets; i++)
    {
	if (!AsetS[i]->numpin)
	{
	    /***********************************************************
	    * This active set does not have any pins on it. So skip it.
	    ***********************************************************/
	    continue;
	}

	number = AsetS[i]->numpin;
	Achan = AsetS[i]->Achan;
	AsetS[i]->Aindex =
	Aindex = (HLISTPTR *)Ysafe_malloc((number+1) * sizeof(HLISTPTR));
	Aindex[0] = (HLISTPTR)Ysafe_malloc(sizeof(HLIST));
	Aindex[0]->index = 0;
	Aindex[0]->key = INT_MAX;
	Aindex[0]->pin = 0;

	for (j = 1; j <= number; j++)
	{
	    Aindex[j] = (HLISTPTR)Ysafe_malloc(sizeof(HLIST));
	    Aindex[j]->index = j;
	    Aindex[j]->key = 0;
	    Aindex[j]->pin = j - 1;
	    Achan[j-1]->Pheap = Aindex[j]; /*Pheap used as inverse func*/
	}

	for (j = 0; j < number; j++)
	{
	    Achan[j]->penalty
		    = analog_compute_penalty(Achan[j]->mixed,
					     Achan[j]->noisy,
					     Achan[j]->sensitive,
					     Achan[j]->shielding);
	    dens_insert(Aindex, Achan[j]->penalty);
	}
    }

    p = 0;

    /***********************************************************
    * Calculate the total penalty cost.
    ***********************************************************/
    for (i = 0; i < numsets; i++)
    {
	/***********************************************************
	* Count the number of nets in each category for the active
	* set.
	***********************************************************/
	Pnlist = AsetS[i]->Pnlist;
	while (Pnlist)
	{
	    if (narray[Pnlist->net]->net_type == MIXED)
	    {
		AsetS[i]->mixed++;
	    }
	    else if (narray[Pnlist->net]->net_type == SENSITIVE)
	    {
		AsetS[i]->sensitive++;
	    }
	    else if (narray[Pnlist->net]->net_type == NOISY)
	    {
		AsetS[i]->noisy++;
	    }
	    else
	    {
		AsetS[i]->shielding++;
	    }
	    Pnlist = Pnlist->next;
	}

	AsetS[i]->penalty
		= analog_compute_penalty(AsetS[i]->mixed,
					 AsetS[i]->noisy,
					 AsetS[i]->sensitive,
					 AsetS[i]->shielding);

	if (AsetS[i]->numpin)
	{
	    p += AsetS[i]->Aindex[1]->key;
	}
	p += AsetS[i]->penalty;
    }
    return(p);
}

/*=====================================================================
=====================================================================*/
static int analog_init_length()
{
    register int l = 0;
    register int n;
    register int r;

    for (n = 1; n <= numnets; n++)
    {
        r = narray[n]->route;
	l += narray[n]->Aroute[r]->length;
    }
    return(l);
}

/*=====================================================================
*   Generate an index for net and one for route for the nets.
=====================================================================*/
static void analog_generate_index()
{
    register int r;

    /***********************************************************
    * Select a net and a route to which the current route will
    * be replaced by a new selected route. Before this function
    * is called, function Yset_random_seed(seed) must be
    * called in order to get non-zero random numbers.
    ***********************************************************/
    for (;;)
    {
	n_index = Aact_nets[Yacm_random() % numnetsS];
	r = narray[n_index]->num_of_routes;
	o_index = narray[n_index]->route;
	r_index = Yacm_random() % r + 1;
	if (o_index != r_index)
	{
	    break;
	}
    }
}

/*=====================================================================
*   Count the number of active nets. If TRUE is given, all the nets are
* active. If FALSE is given, only these nets with current route index
* greater than one are active.
=====================================================================*/
static void analog_find_active_nets(state)
    int state;
{
    register int i;

    numnetsS = 0;

    if (state != FALSE)
    {
	numnetsS = numnets;
	Aact_nets = (int *)Ysafe_malloc(numnets * sizeof(int));

        for (i = 1; i <= numnets; i++)
	{
	    Aact_nets[i - 1] = i;
	}
    }
    else
    {
	numnetsS = 0;

        for (i = 1; i <= numnets; i++)
	{
	    if (narray[i]->route > 1)
	    {
	        Aact_nets[numnetsS++] = i;
	    }
	}
    }
}

/*=====================================================================
*   Update edge density and the total density overflow.
=====================================================================*/
static analog_update_edge(Pedge)
    DEDGEPTR Pedge;
{
    register int cost;

    DEDGEPTR Pthis;

    if (Pedge->Pnext)
    {
	if (Pedge->capacity != -1)
	{
	    if (Pedge->numpin)
	    {
		cost = Pedge->density
		     + Pedge->Aindex[1]->key
		     - Pedge->capacity;
	    }
	    else
	    {
		cost = Pedge->density - Pedge->capacity;
	    }
	    Pthis = Pedge->Pnext;
	    while (Pthis != Pedge)
	    {
		cost += Pthis->density;
		Pthis = Pthis->Pnext;
	    }
	}
	else
	{
	    cost = Pedge->density;
	    Pthis = Pedge->Pnext;
	    while (Pthis != Pedge)
	    {
		cost += Pthis->density;
		Pthis = Pthis->Pnext;
	    }

	    /*******************************************************
	    * Now update the old weight.
	    *******************************************************/
	    Pthis = Pedge->Pnext;
	    while (Pthis->capacity == -1)
	    {
		Pthis = Pthis->Pnext;
	    }
	    if (Pthis->numpin)
	    {
		cost += Pthis->Aindex[1]->key;
	    }
	    cost -= Pthis->capacity;
	    if (Pthis->weight > 0 && cost > 0)
	    {
		total_cost += (cost - Pthis->weight);
	    }
	    else if (Pthis->weight > 0)
	    {
		total_cost -= Pthis->weight;
	    }
	    else if (cost > 0)
	    {
		total_cost += cost;
	    }
	    Pthis->weight = cost;
	    cost = 0;
	}
    }
    else
    {
	if (Pedge->numpin)
	{
	    cost = Pedge->density
		 + Pedge->Aindex[1]->key
		 - Pedge->capacity;
	}
	else
	{
	    cost = Pedge->density - Pedge->capacity;
	}
    }

    if (Pedge->weight > 0 && cost > 0)
    {
	tot_densityS += (cost - Pedge->weight);
    }
    else if (Pedge->weight > 0)
    {
	tot_densityS -= Pedge->weight;
    }
    else if (cost > 0)
    {
	tot_densityS += cost;
    }

    Pedge->weight = cost;
}

/*=====================================================================
*   Delete the route from the density array in the global routing
* graph.
=====================================================================*/
static void analog_delete_edge(r)
    int r;
{
    register int i;
    register int j;
    int density;
    int distance;

    DEDGEPTR Pedge;
    DENSPTR *Adens;
    NLISTPTR Pnlist;
    OFSETPTR Pelist;

    Pelist = narray[n_index]->Aroute[r]->Pedge;

    while (Pelist)
    {
	Pedge = dearray[Pelist->edge];

	if (Pelist->l_off == INT_MIN)
	{
	    /***********************************************************
	    * The segment is not in the array for calculating the
	    * channel density.
	    ***********************************************************/
	    Pelist = Pelist->next;
	    continue;
	}

	if (Pelist->l_off || Pelist->r_off)
	{
	    /*********************************************************
	    * One of the two end points or both end points are not
	    * zero. Then the net is the net list and the heap must
	    * be updated.
	    *********************************************************/
	    Adens = Pedge->Adens;
	    i = j = Pedge->numpin / 2;

	    while (Adens[i]->distance != Pelist->l_off)
	    {
		if (Pelist->l_off < Adens[i]->distance)
		{
		    i /= 2;
		    j /= 2;
		}
		else
		{
		    if (j == 1)
		    {
			i++;
		    }
		    else
		    {
			j /= 2;
			i += j;
		    }
		}
	    }

	    j = Pedge->numpin;
	    distance = Pedge->length - Pelist->r_off;

	    while (i < j && Adens[i]->distance <= distance)
	    {
		Pnlist = Adens[i]->Pnlist;

		while (Pnlist->net != n_index)
		{
		    Pnlist = Pnlist->next;
		}

		if (Pnlist->prev && Pnlist->next)
		{
		    Pnlist->prev->next = Pnlist->next;
		    Pnlist->next->prev = Pnlist->prev;
		}
		else if (Pnlist->next)
		{
		    Adens[i]->Pnlist = Pnlist->next;
		    Pnlist->next->prev = NIL(NLIST);
		}
		else if (Pnlist->prev)
		{
		    Pnlist->prev->next = NIL(NLIST);
		}
		else
		{
		    Adens[i]->Pnlist = NIL(NLIST);
		}

		Ysafe_free((char *) Pnlist);
		density = (Adens[i]->density -= Pelist->width);
		dens_update(Pedge->Aindex,
		    density,
		    Adens[i]->Pheap->index);
		i++;
	    }
	}
	else
	{
	    /*********************************************************
	    * The net is crossing this channel. Simply find the net
	    * from the net list and delete it from the list and update
	    * the dearray[e]->density and dearray[e]->weight.
	    *********************************************************/
	    Pnlist = Pedge->Pcnet;

	    while (Pnlist->net != n_index)
	    {
		Pnlist = Pnlist->next;
	    }

	    if (Pnlist->prev && Pnlist->next)
	    {
		Pnlist->prev->next = Pnlist->next;
		Pnlist->next->prev = Pnlist->prev;
	    }
	    else if (Pnlist->next)
	    {
		Pedge->Pcnet = Pnlist->next;
		Pnlist->next->prev = NIL(NLIST);
	    }
	    else if (Pnlist->prev)
	    {
		Pnlist->prev->next = NIL(NLIST);
	    }
	    else
	    {
		Pedge->Pcnet = NIL(NLIST);
	    }

	    Ysafe_free((char *) Pnlist);
	    Pedge->density -= Pelist->width;
	}
	analog_update_edge(Pedge);
	Pelist = Pelist->next;
    }
}

/*=====================================================================
*   Delete the route from the active set in the global routing
* graph.
=====================================================================*/
static void analog_delete_set(r)
    int r;
{
    register int i;
    register int j;
    register int distance;

    ACTSETPTR Pset;
    CLISTPTR Pblist;
    CHANSPTR *Achan;
    NLISTPTR Pnlist;
    OFSETPTR Pelist;

    Pelist = narray[n_index]->Aroute[r]->Pedge;

    while (Pelist)
    {
	Pblist = Achannels[Pelist->edge];

	if (Pelist->l_off || Pelist->r_off)
	{
	    /*********************************************************
	    * One of the two end points or both end points are not
	    * zero. Then the net is the net list and the heap must
	    * be updated.
	    *********************************************************/
	    while (Pblist)
	    {
		Pset = AsetS[Pblist->index];

		/*********************************************************
		* Remove the part of the penalty of the active set, that
		* is associated with pins, from the total penalty.
		*********************************************************/
		tot_penaltyS -= Pset->Aindex[1]->key;

		Achan = Pset->Achan;
		i = j = Pset->numpin / 2;

		while (Achan[i]->distance != Pelist->l_off)
		{
		    if (Pelist->l_off < Achan[i]->distance)
		    {
			i /= 2;
			j /= 2;
		    }
		    else
		    {
			if (j == 1)
			{
			    i++;
			}
			else
			{
			    j /= 2;
			    i += j;
			}
		    }
		}

		j = Pset->numpin;
		distance = dearray[Pelist->edge]->length - Pelist->r_off;

		while (i < j && Achan[i]->distance <= distance)
		{
		    Pnlist = Achan[i]->Pnlist;

		    while (Pnlist->net != n_index)
		    {
			Pnlist = Pnlist->next;
		    }

		    if (Pnlist->prev && Pnlist->next)
		    {
			Pnlist->prev->next = Pnlist->next;
			Pnlist->next->prev = Pnlist->prev;
		    }
		    else if (Pnlist->next)
		    {
			Achan[i]->Pnlist = Pnlist->next;
			Pnlist->next->prev = NIL(NLIST);
		    }
		    else if (Pnlist->prev)
		    {
			Pnlist->prev->next = NIL(NLIST);
		    }
		    else
		    {
			Achan[i]->Pnlist = NIL(NLIST);
		    }

		    switch (narray[Pnlist->net]->net_type)
		    {
			case MIXED:
			    Achan[i]->mixed--;
			    break;

			case NOISY:
			    Achan[i]->noisy--;
			    break;

			case SENSITIVE:
			    Achan[i]->sensitive--;
			    break;

			case SHIELD:
			    Achan[i]->shielding--;
			    break;

			default:
			    ERROR1("\n\n");
			    ERROR3("Unknown net type %d for the net %s",
				narray[Pnlist->net]->net_type,
				narray[Pnlist->net]->name);
			    exit(GP_FAIL);
		    }

		    Ysafe_free((char *) Pnlist);
		    Achan[i]->penalty
			= analog_compute_penalty(Achan[i]->mixed,
						 Achan[i]->noisy,
						 Achan[i]->sensitive,
						 Achan[i]->shielding);
		    dens_update(AsetS[Pblist->index]->Aindex,
				Achan[i]->penalty,
				Achan[i]->Pheap->index);
		    if (Achan[i]->noisy < 0
		     || Achan[i]->sensitive < 0
		     || Achan[i]->shielding < 0)
		    {
			ERROR1("\n\nERROR ON NET TYPE!!!\n");
		    }
		    i++;
		}

		/*********************************************************
		* Add the part of the penalty of the active set, that is
		* associated with pins, from the total penalty.
		*********************************************************/
		tot_penaltyS += Pset->Aindex[1]->key;

		Pblist = Pblist->next;
	    }
	}
	else
	{
	    /*********************************************************
	    * The net is crossing this channel. Simply find the net
	    * from the net list and delete it from the list and update
	    * the dearray[e]->density and dearray[e]->weight.
	    *********************************************************/
	    while (Pblist)
	    {
		i = Pblist->index;

		/*********************************************************
		* Remove the part of the penalty of the active set, that
		* is associated with the set, from the total penalty.
		*********************************************************/
		tot_penaltyS -= AsetS[i]->penalty;

		Pnlist = AsetS[i]->Pnlist;

		while (Pnlist->net != n_index)
		{
		    Pnlist = Pnlist->next;
		}

		if (Pnlist->prev && Pnlist->next)
		{
		    Pnlist->prev->next = Pnlist->next;
		    Pnlist->next->prev = Pnlist->prev;
		}
		else if (Pnlist->next)
		{
		    AsetS[i]->Pnlist = Pnlist->next;
		    Pnlist->next->prev = NIL(NLIST);
		}
		else if (Pnlist->prev)
		{
		    Pnlist->prev->next = NIL(NLIST);
		}
		else
		{
		    AsetS[i]->Pnlist = NIL(NLIST);
		}

		switch (narray[n_index]->net_type)
		{
		    case MIXED:
			AsetS[i]->mixed--;
			break;

		    case NOISY:
			AsetS[i]->noisy--;
			break;

		    case SENSITIVE: AsetS[i]->sensitive--;
			break;

		    case SHIELD:
			AsetS[i]->shielding--;
			break;

		    default:
			ERROR3("\n\nUnknown net type %d for the net %s",
			    narray[n_index]->net_type,
			    narray[n_index]->name);
			exit(GP_FAIL);
		}
		if (AsetS[i]->noisy < 0
		 || AsetS[i]->sensitive < 0
		 || AsetS[i]->shielding < 0)
		{
		    ERROR1("\n\nERROR ON NET TYPE!!!\n");
		}
		AsetS[i]->penalty
		    = analog_compute_penalty(AsetS[i]->mixed,
					     AsetS[i]->noisy,
					     AsetS[i]->sensitive,
					     AsetS[i]->shielding);
		/*********************************************************
		* Add the part of the penalty of the active set, that
		* is associated with the set, from the total penalty.
		*********************************************************/
		tot_penaltyS += AsetS[i]->penalty;

		Pblist = Pblist->next;
	    }
	}
	Pelist = Pelist->next;
    }
}

/*=====================================================================
*   Add the route to the edge in the global routing graph.
=====================================================================*/
static void analog_add_edge(r)
    int r;
{
    register int i;
    register int j;
    int density;
    int distance;

    DEDGEPTR Pedge;
    DENSPTR *Adens;
    NLISTPTR Pnlist;
    OFSETPTR Pelist;

    Pelist = narray[n_index]->Aroute[r]->Pedge;

    while (Pelist)
    {
	Pedge = dearray[Pelist->edge];

	if (Pelist->l_off == INT_MIN)
	{
	    /***********************************************************
	    * The segment is not needed for the channel density. Skip
	    * to the next segment.
	    ***********************************************************/
	    Pelist = Pelist->next;
	    continue;
	}

	if (Pelist->l_off || Pelist->r_off)
	{
	    /*********************************************************
	    * One of the two end points is not zero. Then the net is
	    * the net list and the heap must be updated.
	    *********************************************************/
	    Adens = Pedge->Adens;
	    i = j = Pedge->numpin / 2;
	    distance = Pedge->length - Pelist->r_off;

	    while (Adens[i]->distance != Pelist->l_off)
	    {
		if (Pelist->l_off < Adens[i]->distance)
		{
		    i /= 2;
		    j /= 2;
		}
		else
		{
		    if (j == 1)
		    {
			i++;
		    }
		    else
		    {
			j /= 2;
			i += j;
		    }
		}
	    }

	    j = Pedge->numpin;

	    while (i < j && Adens[i]->distance <= distance)
	    {

		Pnlist = (NLISTPTR)Ysafe_malloc(sizeof(NLIST));
		Pnlist->net = n_index;
		Pnlist->prev = NIL(NLIST);
		Pnlist->next = Adens[i]->Pnlist;
		if (Adens[i]->Pnlist)
		{
		    Adens[i]->Pnlist->prev = Pnlist;
		}
		Adens[i]->Pnlist = Pnlist;
		density = (Adens[i]->density += Pelist->width);
		dens_update(Pedge->Aindex, density,
		    Adens[i]->Pheap->index);
		i++;
	    }
	}
	else
	{
	    /*********************************************************
	    * The net is crossing this channel. Simply find the net
	    * from the net list and delete it from the list and update
	    * the dearray[e]->density and dearray[e]->weight.
	    *********************************************************/
	    Pnlist = (NLISTPTR)Ysafe_malloc(sizeof(NLIST));
	    Pnlist->net = n_index;
	    Pnlist->prev = NIL(NLIST);
	    Pnlist->next = Pedge->Pcnet;
	    if (Pedge->Pcnet)
	    {
		Pedge->Pcnet->prev = Pnlist;
	    }
	    Pedge->Pcnet = Pnlist;
	    Pedge->density += Pelist->width;
	}
	analog_update_edge(Pedge);
	Pelist = Pelist->next;
    }
}

/*=====================================================================
*   Add the route to the active set in the global routing
* graph.
=====================================================================*/
static void analog_add_set(r)
    int r;
{
    register int i;
    register int j;
    register int distance;

    ACTSETPTR Pset;
    CLISTPTR Pblist;
    CHANSPTR *Achan;
    NLISTPTR Pnlist;
    OFSETPTR Pelist;

    Pelist = narray[n_index]->Aroute[r]->Pedge;

    while (Pelist)
    {
	Pblist = Achannels[Pelist->edge];

	if (Pelist->l_off || Pelist->r_off)
	{
	    /*********************************************************
	    * One of the two end points or both end points are not
	    * zero. Then the net is the net list and the heap must
	    * be updated.
	    *********************************************************/
	    while (Pblist)
	    {
		Pset = AsetS[Pblist->index];

		/*********************************************************
		* Remove the part of the penalty of the active set, that
		* is associated with pins, from the total penalty.
		*********************************************************/
		tot_penaltyS -= Pset->Aindex[1]->key;

		Achan = Pset->Achan;
		i = j = Pset->numpin / 2;

		while (Achan[i]->distance != Pelist->l_off)
		{
		    if (Pelist->l_off < Achan[i]->distance)
		    {
			i /= 2;
			j /= 2;
		    }
		    else
		    {
			if (j == 1)
			{
			    i++;
			}
			else
			{
			    j /= 2;
			    i += j;
			}
		    }
		}

		j = Pset->numpin;
		distance = dearray[Pelist->edge]->length - Pelist->r_off;

		while (i < j && Achan[i]->distance <= distance)
		{
		    Pnlist = (NLISTPTR)Ysafe_malloc(sizeof(NLIST));
		    Pnlist->net = n_index;
		    Pnlist->prev = NIL(NLIST);
		    Pnlist->next = Achan[i]->Pnlist;
		    if (Achan[i]->Pnlist)
		    {
			Achan[i]->Pnlist->prev = Pnlist;
		    }
		    Achan[i]->Pnlist = Pnlist;

		    switch (narray[Pnlist->net]->net_type)
		    {
			case MIXED:
			    Achan[i]->mixed++;
			    break;

			case NOISY:
			    Achan[i]->noisy++;
			    break;

			case SENSITIVE:
			    Achan[i]->sensitive++;
			    break;

			case SHIELD:
			    Achan[i]->shielding++;
			    break;

			default:
			    ERROR1("\n\n");
			    ERROR3("Unknown net type %d for the net %s",
				narray[Pnlist->net]->net_type,
				narray[Pnlist->net]->name);
			    exit(GP_FAIL);
		    }

		    Achan[i]->penalty
			= analog_compute_penalty(Achan[i]->mixed,
						 Achan[i]->noisy,
						 Achan[i]->sensitive,
						 Achan[i]->shielding);
		    dens_update(AsetS[Pblist->index]->Aindex,
				Achan[i]->penalty,
				Achan[i]->Pheap->index);
		    i++;
		}
		/*********************************************************
		* Add the part of the penalty of the active set, that
		* is associated with pins, from the total penalty.
		*********************************************************/
		tot_penaltyS += Pset->Aindex[1]->key;

		Pblist = Pblist->next;
	    }
	}
	else
	{
	    /*********************************************************
	    * The net is crossing this channel. Simply find the net
	    * from the net list and delete it from the list and update
	    * the dearray[e]->density and dearray[e]->weight.
	    *********************************************************/
	    while (Pblist)
	    {
		i = Pblist->index;

		/*********************************************************
		* Remove the part of the penalty of the active set, that
		* is associated with the set, from the total penalty.
		*********************************************************/
		tot_penaltyS -= AsetS[i]->penalty;

		/*********************************************************
		* The net is crossing this channel. Simply find the net
		* from the net list and delete it from the list and update
		* the dearray[e]->density and dearray[e]->weight.
		*********************************************************/
		Pnlist = (NLISTPTR)Ysafe_malloc(sizeof(NLIST));
		Pnlist->net = n_index;
		Pnlist->prev = NIL(NLIST);
		Pnlist->next = AsetS[i]->Pnlist;
		if (AsetS[i]->Pnlist)
		{
		    AsetS[i]->Pnlist->prev = Pnlist;
		}
		AsetS[i]->Pnlist = Pnlist;

		switch (narray[n_index]->net_type)
		{
		    case MIXED:
			AsetS[i]->mixed++;
			break;

		    case NOISY:
			AsetS[i]->noisy++;
			break;

		    case SENSITIVE:
			AsetS[i]->sensitive++;
			break;

		    case SHIELD:
			AsetS[i]->shielding++;
			break;

		    default:
			ERROR3("\n\nUnknown net type %d for the net %s",
			    narray[n_index]->net_type,
			    narray[n_index]->name);
			exit(GP_FAIL);
		}
		if (AsetS[i]->noisy < 0
		 || AsetS[i]->sensitive < 0
		 || AsetS[i]->shielding < 0)
		{
		    ERROR1("\n\nERROR ON NET TYPE!!!\n");
		}
		AsetS[i]->penalty
		    = analog_compute_penalty(AsetS[i]->mixed,
					     AsetS[i]->noisy,
					     AsetS[i]->sensitive,
					     AsetS[i]->shielding);
		/*********************************************************
		* Remove the part of the penalty of the active set, that
		* is associated with the set, from the total penalty.
		*********************************************************/
		tot_penaltyS += AsetS[i]->penalty;

		Pblist = Pblist->next;
	    }
	}
	Pelist = Pelist->next;
    }
}

/*=====================================================================
*   Delete the given route from the routing configuration.
=====================================================================*/
static void analog_delete_route(r)
    int r;
{
    analog_delete_edge(r);
    analog_delete_set(r);
}

/*=====================================================================
*   Add the given route from the routing configuration.
=====================================================================*/
static void analog_add_route(r)
    int r;
{
    analog_add_edge(r);
    analog_add_set(r);
}

/*=====================================================================
*   Minimize the total density overflow.
=====================================================================*/
static void analog_min_density(limit)
    int limit;
{
    register int iter;
    register int no_change_iter = 0;
    register int no_change_limit = 2 * numnets * NUMTREES;

    PRINT(fdat, "\n\n");
    PRINT(fdat, "Minimizing the total channel density overflow...\n");
    FFLUSH(fdat);
    PRINT(stdout, "\n\n");
    PRINT(stdout, "Minimizing the total channel density overflow...\n");
    FFLUSH(stdout);

    for (iter = 1; iter <= limit; iter++)
    {
	print_iteration(iter);
	print_overflow(iter, min_densityS);

	/*********************************************************
	* Generate an index for a net and an index for a route of
	* the net.
	*********************************************************/
	analog_generate_index();

	/*********************************************************
	* Delete the current route indexed by o_index of the net
	* indexed by n_index. Variables tot_densityS and
	* tot_penaltyS is updated in the function.
	*********************************************************/
	analog_delete_route(o_index);

	/***********************************************************
	* Add the new current indexed by r_index for the net indexed
	* by n_index. Variables tot_densityS and tot_penaltyS is
	* updated in the function.
	***********************************************************/
	analog_add_route(r_index);

	if (tot_densityS < min_densityS)
	{
	    /***********************************************************
	    * The new total density overflow is less than the old total
	    * density overflow. Accept the new routing configuration.
	    ***********************************************************/
	    no_change_iter = 0;
	    narray[n_index]->route = r_index;
	    min_densityS = tot_densityS;
	    if (tot_penaltyS < min_penaltyS)
	    {
	        min_penaltyS = tot_penaltyS;
	    }
	}
	else if (tot_densityS == min_densityS)
	{
	    /***********************************************************
	    * The new total density overflow is equal to the old total
	    * density overflow. Accept the new routing configuration but
	    * set variable no_change_iter according to the total signal-
	    * coupling penalty.
	    ***********************************************************/
	    if (tot_penaltyS < min_penaltyS)
	    {
		no_change_iter = 0;
		min_penaltyS = tot_penaltyS;
	    }
	    else
	    {
		no_change_iter++;
	    }
	    narray[n_index]->route = r_index;
	}
	else
	{
	    no_change_iter++;
	    analog_delete_route(r_index);
	    analog_add_route(o_index);
	}

	if (min_densityS == 0 || no_change_iter > no_change_limit)
	{
	    /*****************************************************
	    * The number of non-improvement iterations is greater
	    * than the pre-set limit. Quit the iteration.
	    *****************************************************/
	    break;
	}
    }
    PRINT(fdat, "\n...minimization ends\n");
    PRINT(stdout, "\n...minimization ends\n");
}

/*=====================================================================
*   Minimize the total signal-coupling penalty.
=====================================================================*/
static void analog_min_penalty(limit)
    int limit;
{
    register int iter;
    register int no_change_iter = 0;
    register int no_change_limit = 2 * numnets * NUMTREES;

    PRINT(fdat, "\n\n");
    PRINT(fdat, "Minimizing the total signal-coupling penalty...\n");
    FFLUSH(fdat);
    PRINT(stdout, "\n\n");
    PRINT(stdout, "Minimizing the total signal-coupling penalty...\n");
    FFLUSH(stdout);

    for (iter = 1; iter <= limit; iter++)
    {
	print_iteration(iter);
	print_overflow(iter, min_penaltyS);

	/*********************************************************
	* Generate an index for a net and an index for a route of
	* the net.
	*********************************************************/
	analog_generate_index();

	/*********************************************************
	* Delete the current route indexed by o_index of the net
	* indexed by n_index.
	*********************************************************/
	analog_delete_route(o_index);

	/***********************************************************
	* Add the new current indexed by r_index for the net indexed
	* by n_index.
	***********************************************************/
	analog_add_route(r_index);

	if (tot_densityS <= min_densityS)
	{
	    /***********************************************************
	    * The new total density overflow is not greater than the
	    * old density overflow. Accept the new routing configuration
	    * if the new total signal-coupling penalty is not greater
	    * than the old one.
	    ***********************************************************/
	    if (tot_penaltyS < min_penaltyS)
	    {
		no_change_iter = 0;
		narray[n_index]->route = r_index;
		min_densityS = tot_densityS;
		min_penaltyS = tot_penaltyS;
	    }
	    else if(tot_penaltyS == min_penaltyS)
	    {
		no_change_iter++;
		narray[n_index]->route = r_index;
		min_densityS = tot_densityS;
	    }
	    else
	    {
		no_change_iter++;
		analog_delete_route(r_index);
		analog_add_route(o_index);
	    }
	}
	else
	{
	    no_change_iter++;
	    analog_delete_route(r_index);
	    analog_add_route(o_index);
	}

	if (min_penaltyS == 0 || no_change_iter > no_change_limit)
	{
	    /*****************************************************
	    * The number of non-improvement iterations is greater
	    * than the pre-set limit. Quit the iteration.
	    *****************************************************/
	    break;
	}
    }
    PRINT(fdat, "\n...minimization ends\n");
    PRINT(stdout, "\n...minimization ends\n");
}

/*=====================================================================
*   Minimize the total wire length.
=====================================================================*/
static void analog_min_length(limit)
    int limit;
{
    int difference;
    register int iter;
    register int no_change_iter = 0;
    register int no_change_limit = 2 * numnets * NUMTREES;

    PRINT(fdat, "\n\n");
    PRINT(fdat, "Minimizing the total wire length...\n");
    FFLUSH(fdat);
    PRINT(stdout, "\n\n");
    PRINT(stdout, "Minimizing the total wire length...\n");
    FFLUSH(stdout);

    for (iter = 1; iter <= limit; iter++)
    {
	print_iteration(iter);
	print_overflow(iter, min_lengthS);

	/*********************************************************
	* Generate an index for a net and an index for a route of
	* the net.
	*********************************************************/
	analog_generate_index();

	/*********************************************************
	* Delete the current route indexed by o_index of the net
	* indexed by n_index.
	*********************************************************/
	analog_delete_route(o_index);

	/***********************************************************
	* Add the new current indexed by r_index for the net indexed
	* by n_index.
	***********************************************************/
	analog_add_route(r_index);

	difference = narray[n_index]->Aroute[r_index]->length
		   - narray[n_index]->Aroute[o_index]->length;

	if (difference < 0)
	{
	    if (tot_densityS <= min_densityS)
	    {
		/*********************************************************
		* The new total density overflow is not greater than the
		* old density overflow. Accept the new routing configura-
		* tion if the new total signal-coupling penalty is not
		* greater than the old one.
		*********************************************************/
		if (tot_penaltyS < min_penaltyS)
		{
		    no_change_iter = 0;
		    narray[n_index]->route = r_index;
		    min_densityS = tot_densityS;
		    min_penaltyS = tot_penaltyS;
		    min_lengthS = (tot_lengthS += difference);
		}
		else if(tot_penaltyS == min_penaltyS)
		{
		    no_change_iter = 0;
		    narray[n_index]->route = r_index;
		    min_densityS = tot_densityS;
		    min_lengthS = (tot_lengthS += difference);
		}
		else
		{
		    no_change_iter++;
		    analog_delete_route(r_index);
		    analog_add_route(o_index);
		}
	    }
	    else
	    {
		no_change_iter++;
		analog_delete_route(r_index);
		analog_add_route(o_index);
	    }
	}
	else if (!difference)
	{
	    if (tot_densityS <= min_densityS)
	    {
		/*********************************************************
		* The new total density overflow is not greater than the
		* old density overflow. Accept the new routing configura-
		* tion if the new total signal-coupling penalty is not
		* greater than the old one.
		*********************************************************/
		if (tot_penaltyS < min_penaltyS)
		{
		    no_change_iter++;
		    narray[n_index]->route = r_index;
		    min_densityS = tot_densityS;
		    min_penaltyS = tot_penaltyS;
		}
		else if(tot_penaltyS == min_penaltyS)
		{
		    no_change_iter++;
		    narray[n_index]->route = r_index;
		    min_densityS = tot_densityS;
		}
		else
		{
		    no_change_iter++;
		    analog_delete_route(r_index);
		    analog_add_route(o_index);
		}
	    }
	    else
	    {
		no_change_iter++;
		analog_delete_route(r_index);
		analog_add_route(o_index);
	    }
	}
	else
	{
	    no_change_iter++;
	    analog_delete_route(r_index);
	    analog_add_route(o_index);
	}

	if (no_change_iter > no_change_limit)
	{
	    /*****************************************************
	    * The number of non-improvement iterations is greater
	    * than the pre-set limit. Quit the iteration.
	    *****************************************************/
	    break;
	}
    }
    PRINT(fdat, "\n...minimization ends\n");
    PRINT(stdout, "\n...minimization ends\n");
}

/*=====================================================================
*   Print the final results.
=====================================================================*/
static void analog_print_results()
{
    PRINT(stdout,"\n\n");
    PRINT(stdout,
       "=========================================================\n");
    PRINT(stdout,
	"      INITIAL PENALTY      |      MINIMUM PENALTY\n");
    PRINT(stdout,
       "---------------------------|-----------------------------\n");
    PRINT(stdout, "          %5d            |         %5d\n",
	init_penaltyS, min_penaltyS);
    PRINT(stdout,
       "=========================================================\n");
    FFLUSH(stdout);

    PRINT(fdat,"\n\n");
    PRINT(fdat,
       "=========================================================\n");
    PRINT(fdat,
	"      INITIAL PENALTY      |      MINIMUM PENALTY\n");
    PRINT(fdat,
       "---------------------------|-----------------------------\n");
    PRINT(fdat, "          %5d            |         %5d\n",
	init_penaltyS, min_penaltyS);
    PRINT(fdat,
       "=========================================================\n");
    FFLUSH(fdat);

    PRINT(stdout,"\n\n");
    PRINT(stdout,
       "=========================================================\n");
    PRINT(stdout,
	"  TOTAL DENSITY OVERFLOW   |      FINAL DENSITY OVERFLOW\n");
    PRINT(stdout,
       "---------------------------|-----------------------------\n");
    PRINT(stdout, "          %-9d        |         %-9d\n",
	init_densityS, min_densityS);
    PRINT(stdout,
       "=========================================================\n");
    FFLUSH(stdout);

    PRINT(fdat,"\n\n");
    PRINT(fdat,
       "=========================================================\n");
    PRINT(fdat,
	"  TOTAL DENSITY OVERFLOW   |      FINAL DENSITY OVERFLOW\n");
    PRINT(fdat,
       "---------------------------|-----------------------------\n");
    PRINT(fdat, "          %-9d        |         %-9d\n",
	init_densityS, min_densityS);
    PRINT(fdat,
       "=========================================================\n");
    FFLUSH(fdat);

    PRINT(stdout,"\n\n");
    PRINT(stdout,
       "=========================================================\n");
    PRINT(stdout,
	" INITIAL TOTAL WIRE LENGTH |      FINAL WIRE LENGTH\n");
    PRINT(stdout,
       "---------------------------|-----------------------------\n");
    PRINT(stdout, "          %-9d        |         %-9d\n",
	init_lengthS, min_lengthS);
    PRINT(stdout,
       "=========================================================\n");
    FFLUSH(stdout);

    PRINT(fdat,"\n\n");
    PRINT(fdat,
       "=========================================================\n");
    PRINT(fdat,
	" INITIAL TOTAL WIRE LENGTH |      FINAL WIRE LENGTH\n");
    PRINT(fdat,
       "---------------------------|-----------------------------\n");
    PRINT(fdat, "          %-9d        |         %-9d\n",
	init_lengthS, min_lengthS);
    PRINT(fdat,
       "=========================================================\n");
    FFLUSH(fdat);
}

/*=====================================================================
*   The main function for the random interchange algorithm.
=====================================================================*/
void analog_random_interchange(iter_limit)
    int iter_limit;
{
    analog_set_random_seed();
    analog_set_initial_route();
    analog_find_active_set();
    analog_find_active_nets(TRUE);

    init_densityS = min_densityS = tot_densityS = analog_init_density();
    init_penaltyS = min_penaltyS = tot_penaltyS = analog_init_penalty();

    if (min_densityS > 0)
    {
	analog_min_density(iter_limit);
    }

    if (min_penaltyS > 0)
    {
	analog_min_penalty(iter_limit);
    }

    analog_find_active_nets(FALSE);
    init_lengthS  = min_lengthS  = tot_lengthS  = analog_init_length();
    analog_min_length(iter_limit);
    analog_print_results();
    Ysafe_free((char *)Aact_nets);
}
