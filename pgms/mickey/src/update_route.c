#ifndef lint
static char SccsId[] = "@(#)update_route.c	Yale Version 2.2 5/16/91" ;
#endif
/* -----------------------------------------------------------------

	FILE:		update_route.c
	AUTHOR:		Dahe Chen
	DATE:		Tue May  1 21:57:41 EDT 1989
	CONTENTS:	update_route()
	REVISION:
			Tue Oct 23 00:30:59 EDT 1990
		Deleted reference to limits.h

----------------------------------------------------------------- */

#include	"define.h"
#include	"dgraph.h"

#define		update_weight( a )	( (*update_weight_func)( a ) )

typedef struct elist {
    short	edge	;
    short	weight	;
} ELIST,
*ELISTPTR ;

void
update_route( Proute , update_weight_func )
ROUTEPTR Proute	;
int (*update_weight_func)() ;
{

int	i		;
int	j		;
int	n 		;
int	density		;
int	distance	;
int	index		;

DEDGEPTR	Pedge	;
DENSPTR		*Adens	;
NLISTPTR	Pnlist	;
OFSETPTR	Pelist	;
ROUTEPTR	Pnew	;

Pnew = Proute ;

while ( Pnew )
{
    /***********************************************************
    * Delete the old route of the net from the current state.
    ***********************************************************/
    n = Pnew->net ;
    i = narray[n]->route ;
    Pelist = narray[n]->Aroute[i]->Pedge ;

    while ( Pelist )
    {
	Pedge = dearray[Pelist->edge] ;

	if ( Pelist->l_off == INT_MIN )
	{
	    /***********************************************************
	    * The segment is not in the array for calculating the
	    * channel density.
	    ***********************************************************/
	    Pelist = Pelist->next ;
	    continue ;
	}

	if ( Pelist->l_off || Pelist->r_off )
	{
	    /*********************************************************
	    * One of the two end points or both end points are not
	    * zero. Then the net is the net list and the heap must
	    * be updated.
	    *********************************************************/
	    Adens = Pedge->Adens ;
	    i = j = Pedge->numpin / 2 ;

	    while ( Adens[i]->distance != Pelist->l_off )
	    {
		if ( Pelist->l_off < Adens[i]->distance )
		{
		    i /= 2 ;
		    j /= 2 ;
		}
		else
		{
		    if ( j == 1 )
		    {
			i++ ;
		    }
		    else
		    {
			j /= 2 ;
			i += j ;
		    }
		}
	    }

	    j = Pedge->numpin ;
	    distance = Pedge->length - Pelist->r_off ;

	    while ( i < j && Adens[i]->distance <= distance )
	    {
		Pnlist = Adens[i]->Pnlist ;

		while ( Pnlist->net != n )
		{
		    Pnlist = Pnlist->next ;
		}

		if ( Pnlist->prev && Pnlist->next )
		{
		    Pnlist->prev->next = Pnlist->next ;
		    Pnlist->next->prev = Pnlist->prev ;
		}
		else if ( Pnlist->next )
		{
		    Adens[i]->Pnlist = Pnlist->next ;
		    Pnlist->next->prev = NIL( NLIST ) ;
		}
		else if ( Pnlist->prev )
		{
		    Pnlist->prev->next = NIL( NLIST ) ;
		}
		else
		{
		    Adens[i]->Pnlist = NIL( NLIST ) ;
		}

		Ysafe_free( (char *) Pnlist ) ;
		density =
		( Adens[i]->density -= Pelist->width ) ;
		index = Adens[i]->Pheap->index ;
		dens_update( Pedge->Aindex , density , index ) ;
		i++ ;
	    }
	}
	else
	{
	    /*********************************************************
	    * The net is crossing this channel. Simply find the net
	    * from the net list and delete it from the list and update
	    * the dearray[e]->density and dearray[e]->weight.
	    *********************************************************/
	    Pnlist = Pedge->Pcnet ;

	    while ( Pnlist->net != n )
	    {
		Pnlist = Pnlist->next ;
	    }

	    if ( Pnlist->prev && Pnlist->next )
	    {
		Pnlist->prev->next = Pnlist->next ;
		Pnlist->next->prev = Pnlist->prev ;
	    }
	    else if ( Pnlist->next )
	    {
		Pedge->Pcnet = Pnlist->next ;
		Pnlist->next->prev = NIL( NLIST ) ;
	    }
	    else if ( Pnlist->prev )
	    {
		Pnlist->prev->next = NIL( NLIST ) ;
	    }
	    else
	    {
		Pedge->Pcnet = NIL( NLIST ) ;
	    }

	    Ysafe_free( (char *) Pnlist ) ;
	    Pedge->density -= Pelist->width ;
	}
	/*********************************************************
	* Update the channel density.
	*********************************************************/
	Pedge->weight = update_weight( Pedge ) ;
	Pelist = Pelist->next ;
    }

    /***********************************************************
    * Insert the new route to build a new state.
    ***********************************************************/
    i = Pnew->route ;
    Pelist = narray[n]->Aroute[i]->Pedge ;

    while ( Pelist )
    {
	Pedge = dearray[Pelist->edge] ;

	if ( Pelist->l_off == INT_MIN )
	{
	    /***********************************************************
	    * The segment is not needed for the channel density. Skip
	    * to the next segment.
	    ***********************************************************/
	    Pelist = Pelist->next ;
	    continue ;
	}

	if ( Pelist->l_off || Pelist->r_off )
	{
	    /*********************************************************
	    * One of the two end points is not zero. Then the net is
	    * the net list and the heap must be updated.
	    *********************************************************/
	    Adens = Pedge->Adens ;
	    i = j = Pedge->numpin / 2 ;
	    distance = Pedge->length - Pelist->r_off ;

	    while ( Adens[i]->distance != Pelist->l_off )
	    {
		if ( Pelist->l_off < Adens[i]->distance )
		{
		    i /= 2 ;
		    j /= 2 ;
		}
		else
		{
		    if ( j == 1 )
		    {
			i++ ;
		    }
		    else
		    {
			j /= 2 ;
			i += j ;
		    }
		}
	    }

	    j = Pedge->numpin ;

	    while ( i < j && Adens[i]->distance <= distance )
	    {

		Pnlist = (NLISTPTR) Ysafe_malloc( sizeof(NLIST) ) ;
		Pnlist->net = n ;
		Pnlist->prev = NIL( NLIST ) ;
		Pnlist->next = Adens[i]->Pnlist ;
		if ( Adens[i]->Pnlist )
		{
		    Adens[i]->Pnlist->prev = Pnlist ;
		}
		Adens[i]->Pnlist = Pnlist ;
		density =
		( Adens[i]->density += Pelist->width ) ;
		index = Adens[i]->Pheap->index ;
		dens_update( Pedge->Aindex , density , index ) ;
		i++ ;
	    }
	}
	else
	{
	    /*********************************************************
	    * The net is crossing this channel. Simply find the net
	    * from the net list and delete it from the list and update
	    * the dearray[e]->density and dearray[e]->weight.
	    *********************************************************/
	    Pnlist = (NLISTPTR) Ysafe_malloc( sizeof(NLIST) ) ;
	    Pnlist->net = n ;
	    Pnlist->prev = NIL( NLIST ) ;
	    Pnlist->next = Pedge->Pcnet ;
	    if ( Pedge->Pcnet )
	    {
		Pedge->Pcnet->prev = Pnlist ;
	    }
	    Pedge->Pcnet = Pnlist ;
	    Pedge->density += Pelist->width ;
	}
	Pedge->weight = update_weight( Pedge ) ;
	Pelist = Pelist->next ;
    }
    narray[n]->route = Pnew->route ;
    Pnew = Pnew->next ;
}

} /* end of update_route */
