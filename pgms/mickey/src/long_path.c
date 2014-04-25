#ifndef lint
static char SccsId[] = "@(#)long_path.c	Yale Version 2.2 5/16/91" ;
#endif
/* -----------------------------------------------------------------

	FILE:		long_path.c
	AUTHOR:		Dahe Chen
	DATE:		Thu Nov 23 22:49:00 EDT 1989
	CONTENTS:	make_arrays()
			long_path()
	REVISION:
			Wed Aug 15 11:14:32 PDT 1990
		Some logic bugs are found existing in the function.
		The problem was that when a node is removed from
		the queue, its membership in Amember was never
		changed so that the width-first search was not
		complete.
			Thu Sep  6 15:18:08 PDT 1990
		Change the limit for the queue from numedges to
		numbernodes that is equal to h_numnodes since the
		array is allocated that many elements.
			Tue Oct 23 00:30:59 EDT 1990
		Deleted reference to limits.h

----------------------------------------------------------------- */

#include	"define.h"
#include	"dgraph.h"
#include	"macros.h"

static	int	*Adist		;
static	int	*Amember	;
static	int	*Aqueue		;

static	int	Qhead		;
static	int	Qtail		;
static	int	length		;

void
make_arrays()
{

register int	number	;

number = h_numnodes ;

Adist = (int *) Ysafe_malloc( number * sizeof(int) ) ;
Amember = (int *) Ysafe_malloc( number * sizeof(int) ) ;
h_parent = (int *) Ysafe_malloc( number * sizeof(int) ) ;
v_parent = (int *) Ysafe_malloc( number * sizeof(int) ) ;
Aqueue = (int *) Ysafe_malloc( number * sizeof(int) ) ;

h_critical = (char *) Ysafe_malloc( (numedges+1) * sizeof(char) ) ;
v_critical = (char *) Ysafe_malloc( (numedges+1) * sizeof(char) ) ;
for( number = 1 ; number <= numedges ; number++ )
{
    h_critical[number] = FALSE ;
    v_critical[number] = FALSE ;
}

} /* end of make_arrays */

/* ==================================================================== */

long_path( Anodes , numbernodes , Aparent , Acritical )
DNODEPTR	*Anodes		;
int		numbernodes	;
int		*Aparent	;
char		*Acritical	;
{

register int e	;
register int i	;
register int j	;

DLISTPTR Pnode	;

/***********************************************************
* Initialization.
***********************************************************/
Qhead = 0 ;
Qtail = 1 ;
Adist[0] = 0 ;
Amember[0] = TRUE ;
Aqueue[Qhead] = 0 ;
for ( i = 1 ; i < numbernodes ; i++ )
{
    Adist[i] = INT_MAX ;
    Amember[i] = FALSE ;
    Aparent[i] = -1 ;
}
for ( i = 1 ; i <= numedges ; i++ )
{
    Acritical[i] = FALSE ;
}

/***********************************************************
* Find a longest path using a shortest path algorithm since
* all weights are set to be negative o fthe distance.
***********************************************************/
while ( Qhead != Qtail )
{
    /***********************************************************
    * The queue is not empty.
    ***********************************************************/
    i = Aqueue[(Qhead++)%numbernodes] ;
    Amember[i] = FALSE ;
    Pnode = Anodes[i]->Panode ;

    while ( Pnode )
    {
	e = Pnode->edge ;
	j = Pnode->node ;

	if ( Adist[i] + dearray[e]->weight < Adist[j] )
	{
	    Adist[j] = Adist[i] + dearray[e]->weight ;
	    Aparent[j] = i ;

	    if ( !Amember[j] )
	    {
		Aqueue[(Qtail++)%numbernodes] = j ;
		Amember[j] = TRUE ;
	    }
	}
	Pnode = Pnode->next ;
    }
}

/***********************************************************
* Calculate the length of the longest path.
***********************************************************/
length = 0 ;
j = numbernodes - 1 ;
while ( j )
{
    i = Aparent[j] ;
    Pnode = Anodes[i]->Panode ;

    while ( Pnode->node != j )
    {
	Pnode = Pnode->next ;
    }

    j = i ;
    e = Pnode->edge ;
    length += dearray[e]->weight ;
    Acritical[e] = TRUE ;
}

return( -length ) ;

} /* end of long_path */
