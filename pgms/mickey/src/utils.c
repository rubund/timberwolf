#ifndef lint
static char SccsId[] = "@(#)utils.c	Yale Version 2.3 5/16/91" ;
#endif
/* -----------------------------------------------------------------

	FILE:		utils.c
	AUTHOR:		Dahe Chen
	DATE:		Fri Apr 7 23:10:16 EDT 1989
	CONTENTS:	sort_parray()
			pin_compare()
			duplicate_node_edge()
			restore_node_edge()
			get_mask()
	REVISION:	Thu Oct  4 20:46:11 EDT 1990
		Change quicksort to Yquicksort.
		Mon Feb  4 11:25:18 EST 1991
	    The order of pins in a channel is sorted wrong. It
	    should be ordered in such a way that the pins are
	    from the from_vertex to the to_vertex.

----------------------------------------------------------------- */

#include	"define.h"
#include	"gg_router.h"
#include	"macros.h"

void
sort_parray( start , end )
int start ;
int end ;
{

int	i	;
int	j	;
int	min	;
int	pin	;
int	pin_compare() ;

PINPTR	Ppin	;

pin = end - start + 1 ;

if ( pin < 30 )
{
    /***********************************************************
    * The number of pins is less than 30. Use the bubblesort
    * algorithm to sort the pins.
    ***********************************************************/
    for ( i = start ; i <= end ; i++ )
    {
	min = parray[i]->key ;
	pin = i ;

	for ( j = i ; j <= end ; j++ )
	{
	    if ( min > parray[j]->key )
	    {
		min = parray[j]->key ;
		pin = j ;
	    }
	}

	Ppin = parray[i] ;
	parray[i] = parray[pin] ;
	parray[pin] = Ppin ;
    }
}
else
{
    /***********************************************************
    * The number of pins is greater than or equal to 30. Use
    * the quicksort algorithm to sort the pins.
    ***********************************************************/
    Yquicksort( (char *)(parray+start), pin, sizeof(PINPTR), pin_compare );
}

} /* end of sort_parray */

/* ==================================================================== */

int
pin_compare( item1 , item2 )
PINPTR	*item1	;
PINPTR	*item2	;
{

return((*item1)->key - (*item2)->key);

} /* end of pin_compare */

/* ==================================================================== */

void
duplicate_node_edge()
{

int v1 , v2 ;
LISTPTR Pnode , Pjnode ;
TREEPTR *tarray ;

/***********************************************************
* Make a copy of garray and save it as sarray for restore
* the graph after minimum Steiner trees ( shortest paths )
* are found for a given net.
***********************************************************/
sarray = (NODEPTR *) Ysafe_malloc( (numnodes+1) * sizeof(NODEPTR) ) ;

for ( v1 = 1 ; v1 <= numnodes ; v1++ )
{
    sarray[v1] = (NODEPTR) Ysafe_malloc( sizeof(NODE) ) ;
    sarray[v1]->vertex = garray[v1]->vertex ;
    sarray[v1]->status = garray[v1]->status ;
    sarray[v1]->xpos = garray[v1]->xpos ;
    sarray[v1]->ypos = garray[v1]->ypos ;
    sarray[v1]->first = NIL( LIST ) ;
    Pnode = garray[v1]->first ;

    while ( Pnode )
    {
	Pjnode = (LISTPTR) Ysafe_malloc( sizeof(LIST) ) ;
	Pjnode->edge = Pnode->edge ;
	Pjnode->f_vertex = Pnode->f_vertex ;
	Pjnode->t_vertex = Pnode->t_vertex ;
	Pjnode->length = Pnode->length ;
	Pjnode->next = sarray[v1]->first ;
	sarray[v1]->first = Pjnode ;

	Pnode = Pnode->next ;
    }

    sarray[v1]->tree =
    tarray = (TREEPTR *) Ysafe_malloc( (numnodes+1) * sizeof(TREEPTR) ) ;
    tarray[0] = (TREEPTR) Ysafe_malloc( sizeof(TREE) ) ;

    for ( v2 = 1 ; v2 <= numnodes ; v2++ )
    {
	tarray[v2] = (TREEPTR) Ysafe_malloc( sizeof(TREE) ) ;
	tarray[v2]->parent = garray[v1]->tree[v2]->parent ;
	tarray[v2]->root = garray[v1]->tree[v2]->root ;
	tarray[v2]->self = garray[v1]->tree[v2]->self ;
	tarray[v2]->edge = garray[v1]->tree[v2]->edge ;
	tarray[v2]->status = garray[v1]->tree[v2]->status ;
	tarray[v2]->dist = garray[v1]->tree[v2]->dist ;
    }
}

/***********************************************************
* Make a copy of earray and save it as carray for restore
* the graph after minimum steiner trees ( shortest paths )
* are found for a given net.
***********************************************************/
carray = (EDGEPTR *) Ysafe_malloc( (numedges+1) * sizeof(EDGEPTR) ) ;

for ( v1 = 1 ; v1 <= numedges ; v1++ )
{
    carray[v1] = (EDGEPTR) Ysafe_malloc( sizeof(EDGE) ) ;
    carray[v1]->edge = earray[v1]->edge ;
    carray[v1]->length = earray[v1]->length ;
    carray[v1]->node[0] = earray[v1]->node[0] ;
    carray[v1]->node[1] = earray[v1]->node[1] ;
}

} /* end of duplicate_node_edge */

/* ==================================================================== */

void
restore_node_edge()
{

int	d	;
int	i	;
int	j	;
int	n	;
int	n1	;
int	n2	;

EDGEPTR Pedge	;
EDGEPTR Peedge	;
EDGEPTR Pcedge	;
LISTPTR Panode	;
LISTPTR	Pnodee	;
LISTPTR	Pnodes	;
NODEPTR Pgnode	;
NODEPTR Psnode	;
PINPTR	Ppin	;
TREEPTR Pgtree	;
TREEPTR	Pstree	;

if ( numpins > THRESHOLD )
{
    /***********************************************************
    * The number of pins is greater than the preset threshold.
    * Restore garray and earray by coping from the backup.
    ***********************************************************/
    for ( i = 1 ; i <= numnodes ; i++ )
    {
	Pgnode = garray[i] ;
	Psnode = sarray[i] ;
	Pgnode->vertex = Psnode->vertex ;
	Pgnode->status = 0 ;
	Pgnode->xpos = Psnode->xpos ;
	Pgnode->ypos = Psnode->ypos ;
	Pnodee = Pgnode->first ;
	Pnodes = Psnode->first ;

	while ( Pnodes )
	{
	    Pnodee->edge = Pnodes->edge ;
	    Pnodee->f_vertex = Pnodes->f_vertex ;
	    Pnodee->t_vertex = Pnodes->t_vertex ;
	    Pnodee->length = Pnodes->length ;
	    Pnodee = Pnodee->next ;
	    Pnodes = Pnodes->next ;
	}

	for ( j = 1 ; j <= numnodes ; j++ )
	{
	    Pgtree = Pgnode->tree[j] ;
	    Pstree = Psnode->tree[j] ;
	    Pgtree->parent = Pstree->parent ;
	    Pgtree->root = Pstree->root ;
	    Pgtree->self = Pstree->self ;
	    Pgtree->edge = Pstree->edge ;
	    Pgtree->status = 0 ;
	    Pgtree->dist = Pstree->dist ;
	}
    }

    for ( i = 1 ; i <= numedges ; i++ )
    {
	Peedge = earray[i] ;
	Pcedge = carray[i] ;
	Peedge->edge = Pcedge->edge ;
	Peedge->length = Pcedge->length ;
	Peedge->node[0] = Pcedge->node[0] ;
	Peedge->node[1] = Pcedge->node[1] ;
	Peedge->numpins = 0 ;
	Peedge->intree = 0 ;
    }
}
else
{
    /***********************************************************
    * The number of pins is less than the preset threshold.
    * Restore garray and earray by changing these node and
    * edge which were changed only.
    ***********************************************************/
    for ( i = 1 ; i <= numpins ; i++ )
    {
	Ppin = parray[i] ;
	d = Ppin->dist[0] + Ppin->dist[1] ;
	n = numnodes + i ;
	for ( j = 1 ; j <= 2 ; j++ )
	{
	    if ( EVEN_ODD( j ) == ODD )
	    {
		n1 = Ppin->node[0] ;
		n2 = Ppin->node[1] ;
	    }
	    else
	    {
		n1 = Ppin->node[1] ;
		n2 = Ppin->node[0] ;
	    }
	    Panode = garray[n1]->first ;
	    while( Panode && Panode->t_vertex != n )
	    {
		Panode = Panode->next ;
	    }
	    if ( Panode )
	    {
		Panode->t_vertex = n2 ;
		Panode->length = d ;
	    }
	}

	Pedge = earray[Ppin->edge] ;
	Pedge->length = d ;
	if ( Pedge->node[0] == n )
	{
	    Pedge->node[0] = n2 ;
	}
	if ( Pedge->node[1] == n )
	{
	    Pedge->node[1] = n2 ;
	}

	n1 = Ppin->node[0] ;
	n2 = Ppin->node[1] ;
	for ( j = 1 ; j <= numnodes ; j++ )
	{
	    Pgtree = garray[n1]->tree[n2] ;
	    if ( Pgtree->parent == n )
	    {
		Pgtree->parent = n1 ;
	    }
	    Pgtree = garray[n2]->tree[n1] ;
	    if ( Pgtree->parent == n )
	    {
		Pgtree->parent = n2 ;
	    }
	}
    }
}

for ( i = 1 ; i <= numpins ; i++ )
{
    Ysafe_free( (char *) parray[i] ) ;
}
Ysafe_free( (char *) parray ) ;

} /* end of restore_node_edge */

/* ==================================================================== */

unsigned
get_mask( shift_bit )
int shift_bit ;
{

unsigned j = 1	;

return( j <<= shift_bit ) ;

} /* end of get_mask */
