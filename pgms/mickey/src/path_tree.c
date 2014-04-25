#ifndef lint
static char SccsId[] = "@(#)path_tree.c	Yale Version 2.2 5/16/91" ;
#endif
/* -----------------------------------------------------------------

	FILE:		path_tree.c
	AUTHOR:		Dahe Chen
	DATE:		Wed Mar 22 11:54:32 EDT 1989
	CONTENTS:	tree_shiftup()
			tree_shiftdown()
			tree_deletemin()
			tree_insert()
			path_tree()
	REVISION:

----------------------------------------------------------------- */

#include	"define.h"
#include	"gg_router.h"

static		int		*pinv		;
static		int		*heap		;
static		TREEPTR		*tree_head	;


void
tree_shiftup( index )
int index ;
{

int v ;

v = pinv[index] ;

while ( v / 2 )
{
    if ( tree_head[index]->dist < tree_head[heap[v/2]]->dist )
    {
	heap[v] = heap[v/2] ;
	pinv[heap[v/2]] = v ;
	v /= 2 ;
    }
    else
    {
    	break ;
    }
}
heap[v] = index ;
pinv[index] = v ;

} /* end of tree_shiftup */

/* ==================================================================== */

void
tree_shiftdown( index )
int index ;
{

int j , v ;

v = pinv[index] ;

while ( v <= heap[0] / 2 )
{
    j = v + v ;
    if ( j < heap[0] )
    {
	if ( tree_head[heap[j]]->dist > tree_head[heap[j+1]]->dist )
	{
	    j++ ;
	}
    }
    if ( tree_head[index]->dist < tree_head[heap[j]]->dist )
    {
	break ;
    }
    heap[v] = heap[j] ;
    pinv[heap[v]] = v ;
    v = j ;
}
heap[v] = index ;
pinv[index] = v ;

} /* end of tree_shiftdown */

/* ==================================================================== */

int
tree_deletemin()
{

int length , minnode ;

length = heap[0] ;
if ( length )
{
    minnode = heap[1] ;
    heap[1] = heap[length] ;
    pinv[heap[1]] = 1 ;
    --( heap[0] ) ;
    tree_shiftdown( heap[1] ) ;
}
else
{
    minnode = 0 ;
}

return( minnode ) ;

} /* end of tree_deletemin */

/* ==================================================================== */

void
tree_insert( index )
int index ;
{

int v ;

v = ++( heap[0] ) ;
heap[v] = index ;
pinv[index] = v ;
tree_shiftup( index ) ;

} /* end of tree_insert */

/* ==================================================================== */

void generate_path_tree()
{

int v , v1 , v2 ;
LISTPTR Pnode ;
TREEPTR Ptree ;

heap = (int *) Ysafe_malloc( (numnodes+1) * sizeof(int) ) ;
pinv = (int *) Ysafe_malloc( (numnodes+1) * sizeof(int) ) ;

heap[0] = 0 ;

for ( v1 = 1 ; v1 <= numnodes ; v1++ )
{
    tree_head = (TREEPTR *) Ysafe_malloc((numnodes+1) * sizeof(TREEPTR));
    tree_head[0] = (TREEPTR) Ysafe_malloc( sizeof(TREE));
    tree_head[0]->parent = 0 ;
    tree_head[0]->root = v1 ;
    tree_head[0]->self = 0 ;
    tree_head[0]->dist = INT_MIN ;
    for ( v2 = 1 ; v2 <= numnodes ; v2++  )
    {
	tree_head[v2] = (TREEPTR) Ysafe_malloc( sizeof(TREE));
	tree_head[v2]->parent = v2 ;
	tree_head[v2]->root = v1 ;
	tree_head[v2]->self = v2 ;
	tree_head[v2]->dist = INFINITY ;
	tree_head[v2]->status = FALSE ;
	heap[v2] = 0 ;
	pinv[v2] = 0 ;
    }
    v = v1 ;
    tree_head[v]->dist = 0 ;
    while ( v )
    {
	Pnode = garray[v]->first ;
	while ( Pnode )
	{
	    Ptree = tree_head[Pnode->t_vertex] ;
	    if ( tree_head[v]->dist + Pnode->length < Ptree->dist )
	    {
		Ptree->dist = tree_head[v]->dist + Pnode->length ;
		Ptree->parent = tree_head[v]->self ;
		Ptree->edge = Pnode->edge ;

		if ( Ptree->status == FALSE )
		{
		    Ptree->status = TRUE ;
		    tree_insert( Pnode->t_vertex ) ;
		}
		else
		{
		    tree_shiftup( Pnode->t_vertex ) ;
		}
	    }
	    Pnode = Pnode->next ;
	}
	v = tree_deletemin() ;
    }
    garray[v1]->tree = tree_head ;
}
Ysafe_free( heap ) ;
Ysafe_free( pinv ) ;

} /* end of path_tree */


