#ifndef lint
static char SccsId[] = "@(#)init_assign.c	Yale Version 3.4 5/28/91" ;
#endif
/* -----------------------------------------------------------------

	FILE:		init_assign.c
	AUTHOR:		Dahe Chen
	DATE:		Thu Aug 24 14:45:24 EDT 1989
	CONTENTS:	init_assign()
	REVISION:
		Sun May 20 15:20:49 EDT 1990
	    Add code for handling segments which are in channels
	    adjacent to empty rooms.
	    Also, add code checking if the length of a route is
	    zero. If so, this route will not be inserted into the
	    array for the calculation of channel densities since
	    it does not affect the channel density of the channel
	    it locates.
		Thu Oct 11 15:02:24 EDT 1990
	    Reformat the code to my new style.
		Tue Oct 23 00:30:59 EDT 1990
	    Deleted reference to limits.h
		Sat May  4 17:35:28 EDT 1991
	    Change the test from
		dearray[e]->status != i
	    to
		dearray[e]->status != -i
		Thu May 23 18:39:53 EDT 1991
	    Remove the function call to find_special_route.

----------------------------------------------------------------- */

#include	<define.h>
#include	<dgraph.h>

extern	int	CASE			;

BOOLEAN
init_assign()
{

int	e, i, j, k	;
int	weight		;
int	number		;
int	distance	;
int	status = 1	;

DENSPTR	 *Adens		;
HLISTPTR *Aindex	;
NLISTPTR Pnet		;
OFSETPTR Pelist		;
DEDGEPTR Pedge		;
DEDGEPTR Pthis		;

/***********************************************************
* For each net, assign its first route (shortest route) to
* the initial configuration.
***********************************************************/
for (i=1; i<=numnets; i++)
{
    narray[i]->route = 1 ;

    if (!narray[i]->Aroute[1]->length)
    {
	/***********************************************************
	* The length of the route is zero, that is, its two pins
	* locate on the opposite side of the same channel. This
	* route wont be inserted into the density array for the
	* calcualtion of the channel density of this channel since
	* it does not affect the channel density.
	***********************************************************/
	continue ;
    }

    Pelist = narray[i]->Aroute[1]->Pedge ;

    while (Pelist)
    {
	Adens = dearray[e = Pelist->edge]->Adens ;

	if (Pelist->l_off==INT_MIN)
	{
	    /***********************************************************
	    * The segment is not needed for the channel density. Skip
	    * to the next segment.
	    ***********************************************************/
	    Pelist = Pelist->next ;
	    continue ;
	}

	if (!Pelist->l_off && !Pelist->r_off)
	{
	    /***********************************************************
	    * The segment crosses the channel. Insert it into the list
	    * for crossing segments, which is headed by field Pcnet in
	    * dearray.
	    ***********************************************************/
	    Pnet = (NLISTPTR) Ysafe_malloc(sizeof(NLIST)) ;
	    Pnet->net = i ;
	    Pnet->prev = NIL(NLIST) ;
	    Pnet->next = dearray[e]->Pcnet ;

	    if (dearray[e]->Pcnet)
	    {
		dearray[e]->Pcnet->prev = Pnet ;
	    }
	    dearray[e]->Pcnet = Pnet ;
	    dearray[e]->density += Pelist->width ;
	}
	else if (Pelist->l_off && Pelist->r_off)
	{
	    /***********************************************************
	    * The both sides of the segment end in this channel. Use the
	    * binary search to find the left end and scan through to the
	    * right end.
	    ***********************************************************/
	    j = k = dearray[e]->numpin / 2 ;
	    while (Adens[j]->distance!=Pelist->l_off)
	    {
		if (Pelist->l_off<Adens[j]->distance)
		{
		    /*****************************************************
		    * The left end is on the left side of pin j.
		    *****************************************************/
		    j /= 2 ;
		    k /= 2 ;
		}
		else
		{
		    /*****************************************************
		    * The left end is on the right side of pin j.
		    *****************************************************/
		    if (k)
		    {
			k /= 2 ;
			j += k ;
		    }
		    else
		    {
			j++ ;
		    }
		}
	    }

	    distance = dearray[e]->length - Pelist->r_off ;
	    for (; Adens[j]->distance<=distance; j++)
	    {
		/*********************************************************
		* The net crosses this pin. Insert the net into the net
		* list of this pin and update the local density.
		*********************************************************/
		Pnet = (NLISTPTR) Ysafe_malloc(sizeof(NLIST)) ;
		Pnet->net = i ;
		Pnet->prev = NIL(NLIST) ;
		Pnet->next = Adens[j]->Pnlist ;
		if (Adens[j]->Pnlist)
		{
		    Adens[j]->Pnlist->prev = Pnet ;
		}
		Adens[j]->Pnlist = Pnet ;
		Adens[j]->density += Pelist->width ;
	    }
	}
	else
	{
	    /***********************************************************
	    * One side of the segment ends in this channel. Scan pins on
	    * the channel started from the left side if its right side
	    * ends in the channel, started from the right side if its
	    * left side ends in the channel.
	    ***********************************************************/
	    if (!Pelist->l_off)
	    {
		distance = dearray[e]->length - Pelist->r_off ;
		for (j=0; Adens[j]->distance<=distance; j++)
		{
		    /*****************************************************
		    * The net crosses this pin. Insert the net into the
		    * net list of this pin and update the local density.
		    *****************************************************/
		    Pnet = (NLISTPTR) Ysafe_malloc(sizeof(NLIST)) ;
		    Pnet->net = i ;
		    Pnet->prev = NIL(NLIST) ;
		    Pnet->next = Adens[j]->Pnlist ;
		    if (Adens[j]->Pnlist)
		    {
			Adens[j]->Pnlist->prev = Pnet ;
		    }
		    Adens[j]->Pnlist = Pnet ;
		    Adens[j]->density += Pelist->width ;
		}
	    }
	    else
	    {
		j = dearray[e]->numpin - 1 ;
		for (; Adens[j]->distance >= Pelist->l_off ; j--)
		{
		    /*****************************************************
		    * The net crosses this pin. Insert the net into the
		    * net list of this pin and update the local density.
		    *****************************************************/
		    Pnet = (NLISTPTR) Ysafe_malloc(sizeof(NLIST)) ;
		    Pnet->net = i ;
		    Pnet->prev = NIL(NLIST) ;
		    Pnet->next = Adens[j]->Pnlist ;
		    if (Adens[j]->Pnlist)
		    {
			Adens[j]->Pnlist->prev = Pnet ;
		    }
		    Adens[j]->Pnlist = Pnet ;
		    Adens[j]->density += Pelist->width ;
		}
	    }
	}
	Pelist = Pelist->next ;
    }
}

/***********************************************************
* Build up a priority tree of local densities over all pins
* on a channel for each of channels, including two ends of
* the channel.
***********************************************************/
for (i=1; i<=numedges; i++)
{
    if (!dearray[i]->numpin)
    {
	/***********************************************************
	* This channel does not have any pins on it. So skip it.
	***********************************************************/
	continue ;
    }
    else
    {
	if (dearray[i]->Pnext && dearray[i]->capacity==-1)
	{
	    /***********************************************************
	    * This channel shares a pin array with another channel.
	    * Skip it and assign the index array of the other channel
	    * to it later.
	    ***********************************************************/
	    continue ;
	}
    }

    number = dearray[i]->numpin ;
    Adens = dearray[i]->Adens ;
    dearray[i]->Aindex =
    Aindex = (HLISTPTR *) Ysafe_malloc((number+1) * sizeof(HLISTPTR)) ;
    Aindex[0] = (HLISTPTR) Ysafe_malloc(sizeof(HLIST)) ;
    Aindex[0]->index = 0 ;
    Aindex[0]->key = INT_MAX ;
    Aindex[0]->pin = 0 ;

    if (dearray[i]->Pnext)
    {
	Pthis = dearray[i]->Pnext ;
	while (!Pthis->numpin)
	{
	    Pthis = Pthis->Pnext ;
	}
	Pthis->Aindex = Aindex ;
    }

    for (j=1; j<=number; j++)
    {
	Aindex[j] = (HLISTPTR) Ysafe_malloc(sizeof(HLIST)) ;
	Aindex[j]->index = j ;
	Aindex[j]->key = 0 ;
	Aindex[j]->pin = j - 1 ;
	Adens[j-1]->Pheap = Aindex[j] ;	/* Pheap used as inverse func	*/
    }

    for (j=0; j<number; j++)
    {
	dens_insert(Aindex, Adens[j]->density) ;
    }
}

/***********************************************************
* Assign the summation of a channel density plus cell size
* to variable weight in dearray for finding the longest path
* or assign the subtraction of the channel density minus the
* channel capacity to variable weight in dearray for finding
* overflow.
***********************************************************/
if (CASE==1)
{
    for (i=1; i<=numedges; i++)
    {
	if ((Pedge=dearray[i])->numpin && Pedge->capacity!=-1)
	{
	    Pedge->weight = -(Pedge->csize + Pedge->density +
			       Pedge->Aindex[1]->key) ;
	}
	else
	{
	    Pedge->weight = -(Pedge->csize + Pedge->density) ;
	}
    }
}
else
{
    total_cost = 0 ;
    for (i=1; i<=numedges; i++)
    {
	if ((Pedge=dearray[i])->Pnext)
	{
	    /***********************************************************
	    * The channel is adjacent to an empty room. The channel
	    * density of the channel and the channel(s) in the same
	    * list will be calculated together.
	    ***********************************************************/
	    if (Pedge->capacity!=-1)
	    {
		if (Pedge->numpin)
		{
		    weight = Pedge->density - Pedge->capacity +
				Pedge->Aindex[1]->key ;
		}
		else
		{
		    weight = Pedge->density - Pedge->capacity ;
		}
		Pthis = Pedge->Pnext ;
		while (Pthis!=Pedge)
		{
		    weight += Pthis->density ;
		    Pthis->weight = 0 ;
		    Pthis = Pthis->Pnext ;
		}
		Pedge->weight = weight ;
		if (weight>0)
		{
		    total_cost += weight ;
		    status = 0 ;
		}
	    }
	}
	else
	{
	    if ((Pedge=dearray[i])->numpin)
	    {
		Pedge->weight = Pedge->density - Pedge->capacity +
				Pedge->Aindex[1]->key ;
	    }
	    else
	    {
		Pedge->weight = Pedge->density - Pedge->capacity ;
	    }
	    if (Pedge->weight>0)
	    {
		total_cost += Pedge->weight ;
		status = 0 ;
	    }
	}
    }
}

return(status) ;

} /* end of init_assign */
