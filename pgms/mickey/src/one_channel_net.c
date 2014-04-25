#ifndef lint
static char SccsId[] = "@(#)one_channel_net.c	Yale Version 2.2 5/16/91" ;
#endif
/* -----------------------------------------------------------------

	FILE:		one_channel_net.c
	AUTHOR:		Dahe Chen
	DATE:		Wed Feb 1 23:50:22 EDT 1989
	CONTENTS:	one_channel_net()
	REVISION:
		Thu Oct 11 11:51:08 EDT 1990
	    Add the parameter do_debug for the conditional debug.

----------------------------------------------------------------- */

#include	"define.h"
#include	"gg_router.h"
#include	"macros.h"

BOOLEAN
one_channel_net()
{

int	i	;

#ifdef	DEBUG
    int	do_debug = 0	;
#endif	/* DEBUG */

if ( parray[1]->edge == parray[numpins]->edge )
{
    /***********************************************************
    * All pins are on the same channel; therefore, we want only
    * the first shortest path.
    ***********************************************************/
    for ( i = numedges+1 ; i < numedges+numpins ; i++ )
    {
#ifdef	DEBUG
    if (do_debug)
    {
	if (earray[i]->node[0]<numnodes && earray[i]->node[1]<numnodes)
	{
	    ASSERT( 0 ) ;
	}
    }
#endif /* DEBUG */
	earray[i]->intree = 1 ;
    }
    numtrees = 1 ;
    return( TRUE ) ;
}

return( FALSE ) ;

} /* end of one_channel_net */
