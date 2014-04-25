#ifndef lint
static char SccsId[] = "@(#)update_weight.c	Yale Version 2.2 5/16/91" ;
#endif
/* -----------------------------------------------------------------

	FILE:		update_weight.c
	AUTHOR:		Dahe Chen
	DATE:		Wed Aug 16 23:08:55 EDT 1989
	CONTENTS:	update_weight1()
			update_weight2()
	REVISION:
		Wed May 23 11:17:59 EDT 1990
		Modify function update_weight1.

----------------------------------------------------------------- */

#include	"dgraph.h"

int update_weight1( Pedge )
DEDGEPTR Pedge ;
{

if ( Pedge->capacity == -1 )
{
    return( -( Pedge->csize+Pedge->density ) ) ;
}
else
{
    if ( Pedge->numpin )
    {
	return( -( Pedge->csize+Pedge->density+Pedge->Aindex[1]->key ) ) ;
    }
    else
    {
	return( -( Pedge->csize + Pedge->density ) ) ;
    }
}

} /* end od update_weight1 */

/* ==================================================================== */

int update_weight2( Pedge )
DEDGEPTR Pedge ;
{

register int	cost	;

DEDGEPTR	Pthis	;

if ( Pedge->Pnext )
{
    if ( Pedge->capacity != -1 )
    {
	if ( Pedge->numpin )
	{
	    cost = Pedge->density + Pedge->Aindex[1]->key -
			Pedge->capacity ;
	}
	else
	{
	    cost = Pedge->density - Pedge->capacity ;
	}
	Pthis = Pedge->Pnext ;
	while ( Pthis != Pedge )
	{
	    cost += Pthis->density ;
	    Pthis = Pthis->Pnext ;
	}
    }
    else
    {
	cost = Pedge->density ;
	Pthis = Pedge->Pnext ;
	while ( Pthis != Pedge )
	{
	    cost += Pthis->density ;
	    Pthis = Pthis->Pnext ;
	}

	/***********************************************************
	* Now update the old weight.
	***********************************************************/
	Pthis = Pedge->Pnext ;
	while ( Pthis->capacity == -1 )
	{
	    Pthis = Pthis->Pnext ;
	}
	if ( Pthis->numpin )
	{
	    cost += Pthis->Aindex[1]->key ;
	}
	cost -= Pthis->capacity ;
	if ( Pthis->weight > 0 && cost > 0 )
	{
	    total_cost += ( cost - Pthis->weight ) ;
	}
	else if ( Pthis->weight > 0 )
	{
	    total_cost -= Pthis->weight ;
	}
	else if ( cost > 0 )
	{
	    total_cost += cost ;
	}
	Pthis->weight = cost ;
	cost = 0 ;
    }
}
else
{
    if ( Pedge->numpin )
    {
	cost = Pedge->density + Pedge->Aindex[1]->key - Pedge->capacity ;
    }
    else
    {
	cost = Pedge->density - Pedge->capacity ;
    }
}

if ( Pedge->weight > 0 && cost > 0 )
{
    total_cost += ( cost - Pedge->weight ) ;
}
else if ( Pedge->weight > 0 )
{
    total_cost -= Pedge->weight ;
}
else if ( cost > 0 )
{
    total_cost += cost ;
}

return( cost ) ;

} /* end of update_weight2 */
