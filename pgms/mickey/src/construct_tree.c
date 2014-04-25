#ifndef lint
static char SccsId[] = "@(#)construct_tree.c	Yale Version 3.2 5/23/91" ;
#endif
/* -----------------------------------------------------------------
	FILE:		construct_tree.c
	AUTHOR:		Dahe Chen
	DATE:		Thu Mar 16 22:23:59 EDT 1989
	CONTENTS:	make_node()
			construct_segment()
			find_key()
			build_tree_heap()
			rebuild_tree_heap()
			construct_tree()
			nth_route_segment()
	REVISION:
		Tue Nov  6 20:14:15 EST 1990
	    Change the operand of the bit AND operation from 01 to
	    the actual route when there are equivalent pins because
	    now the base route is not necessarily the first route.
		Tue Feb  5 12:02:21 EST 1991
	    Reformat error message output.
		Thu May 23 18:31:33 EDT 1991
	    Not scan the channels which are adjacent to empty rooms.

----------------------------------------------------------------- */

#include	"define.h"
#include	"gg_router.h"
#include	"macros.h"
#include	"heap_func.h"
#include	"steiner_tree.h"

typedef struct stack {
    short	 degree		;
    struct mdata *Pparent	;
    struct stack *next		;
} STACK,
*STACKPTR ;

static	int	numnode		;

/* ==================================================================== */

MDATAPTR
make_node()
{

MDATAPTR node ;

if (Phead)
{
    node = Phead ;
    Phead = Phead->next ;
}
else
{
    node = (MDATAPTR) Ysafe_malloc(sizeof(MDATA)) ;
}

return(node) ;

} /* end of make_node */

/* ==================================================================== */

void
construct_segment()
{

register int i	;
register int j	;
register int v	;
register int v1	;
register int v2	;
int	count	;
int	degree	;
int	Degree	;
int	order	;

LISTPTR  Pnode	  ;
MDATAPTR Pcurrent ;	/* vertex of its adjdacent list is searched	*/
MDATAPTR Plast	  ;	/* last vertex in the segment tree list		*/
MDATAPTR Pparent  ;	/* start of the path to current vertex		*/
MDATAPTR Pnew	  ;	/* temporary pointer for new vertex		*/
PINPTR	 Pfirst	  ;
PINPTR	 Ppin	  ;
STACKPTR Pstack	  ;
STACKPTR Psteiner ;

/***********************************************************
* Label all the vertices in the minimum Steiner tree with
* one and label the others with zero.
***********************************************************/
numnode = numpins ;
numtree_e = 0 ;
for (i=1; i<=numnodes; i++)
{
    garray[i]->status = FALSE ;
    iarray[i] = 0 ;
}
for (i=numnodes+1; i<=totnodes; i++)
{
    garray[i]->status = TRUE ;
    iarray[i] = 0 ;
}

for (i=1; i<=totedges; i++)
{
    earray[i]->numpins = FALSE ;

    if (earray[i]->intree&MIN_MASK)
    {
	earray[i]->numpins = TRUE ;
	jarray[++numtree_e] = i ;

	v1 = earray[i]->node[0] ;
	v2 = earray[i]->node[1] ;

	if (!garray[v1]->status)
	{
	    numnode++ ;
	    garray[v1]->status = TRUE ;
	}
	if (!garray[v2]->status)
	{
	    numnode++ ;
	    garray[v2]->status = TRUE ;
	}
    }
}

/***********************************************************
* Initialize field key of parray to be zero.
***********************************************************/
for (i=1; i<=numpins; i++)
{
    parray[i]->key = FALSE ;
}

i = numnodes + 1 ;

/***********************************************************
* Find a pin which is a leaf of the minimum Steiner tree.
***********************************************************/
while (1)
{
    degree = 0 ;
    Pnode = garray[i]->first ;

    while (Pnode)
    {
	if (earray[Pnode->edge]->numpins)
	{
	    degree++ ;
	}
	Pnode = Pnode->next ;
    }

    if (degree==1)
    {
	break ;
    }
    i++ ;
}

Pstack = NIL(STACK) ;

count = 0 ;
order = 1 ;

Pcurrent = Plast = Pparent = Proot = make_node() ;

Proot->dist = 0 ;
Proot->leaf = FALSE ;
Proot->order = 1 ;
Proot->parent = 0 ;
Proot->vertex = i ;
Proot->prev = NIL(MDATA) ;
Proot->next = NIL(MDATA) ;
Proot->f_node = NIL(MDATA) ;

if (parray[i-numnodes]->equiv)
{
    Proot->equiv = TRUE ;
    parray[i-numnodes]->key = TRUE ;
}
else
{
    Proot->equiv = FALSE ;
}

if (EQUIVAL==FALSE)
{
    do {
	degree = 0 ;
	Pnode = garray[i]->first ;

	if (!count)
	{
	    /***********************************************************
	    * Search the adjacent list of the current vertex to test if
	    * a vertex in the list is a pin or has a degree greater than
	    * two.
	    * count = 0 --- the current vertex is not a Steiner vertex.
	    ***********************************************************/
	    while (Pnode)
	    {
		v1 = Pnode->t_vertex ;

		if (garray[v1]->status && v1!=Pcurrent->parent)
		{
		    if (earray[Pnode->edge]->intree&MIN_MASK)
		    {
			j = v1 ;
			degree++ ;
		    }
		}
		Pnode = Pnode->next ;
	    }
	}
	else
	{
	    /***********************************************************
	    * The search just returns to a Steiner vertex. We need to
	    * go through the number of count times for adjacent vertices
	    * which are in the minimum Steiner tree and add the vertex
	    * into the segment tree.
	    * count!=0 --- the current vertex is a Steiner vertex.
	    ***********************************************************/
	    while (Pnode)
	    {
		v1 = Pnode->t_vertex ;

		if (garray[v1]->status && v1!=Pcurrent->parent)
		{
		    if (earray[Pnode->edge]->intree&MIN_MASK)
		    {
			j = v1 ;
			degree++ ;
		    }

		    if (degree==count)
		    {
			count = 0 ;
			break ;
		    }
		}
		Pnode = Pnode->next ;
	    }
	}

	if (degree)
	{
	    /***********************************************************
	    * The current vertex is not a leaf. Generate a new node and
	    * expand the tree.
	    ***********************************************************/
	    Pnew = make_node() ;

	    Pnew->equiv = FALSE ;
	    Pnew->leaf = FALSE ;
	    Pnew->order = ++order ;
	    Pnew->parent = i ;
	    Pnew->status = 0 ;
	    Pnew->vertex = j ;

	    Plast->next = Pnew ;
	    Pnew->prev = Plast ;
	    Plast = Pnew ;

	    Pnew->next = NIL(MDATA) ;
	    Pnew->f_node = Pparent ;
	    Pcurrent = Pnew ;

	    v = i ;
	    i = j ;
	}
	else
	{
	    Pcurrent->leaf = TRUE ;
	}

	if (degree==1 && j>numnodes)
	{
	    /***********************************************************
	    * A pin is reached which, with the start vertex i, forms a
	    * segment. Set Pparent to be Pnew and continue the search.
	    ***********************************************************/
	    Pparent = Pnew ;

	}
	else if (degree>1)
	{
	    /***********************************************************
	    * A Steiner vertex is reached which, with the start vertex
	    * i, forms a segment. Set Pparent to be Pnew, update the
	    * stack, and continue the search.
	    ***********************************************************/
	    if (Pstack && Pstack->Pparent->vertex==v)
	    {
		Pnew->f_node = Pstack->Pparent ;
		/*********************************************************
		* The Steiner point is in the stack already. Use goto to
		* jump over the part of pushing it to the stack.
		*********************************************************/
		goto contin ;
	    }

	    Psteiner = (STACKPTR) Ysafe_malloc(sizeof(STACK)) ;
	    Psteiner->degree = --degree ;
	    Psteiner->Pparent = Pnew->prev ;
	    Psteiner->next = Pstack ;
	    Pstack = Psteiner ;
	    Pnew->f_node = Pnew->prev ;

	    contin:

	    if (j>numnodes)
	    {
		Pparent = Pnew ;
	    }
	    else
	    {
		Pparent = Pnew->f_node ;
	    }
	}
	else if (!degree)
	{
	    /***********************************************************
	    * A leaf is reached. Pop a vertex from the stack and continue
	    * the search from that vertex.
	    ***********************************************************/
	    Psteiner = Pstack ;
	    Pcurrent = Pparent = Psteiner->Pparent ;
	    count = Psteiner->degree ;
	    i = Pcurrent->vertex ;
	    Psteiner->degree-- ;

	    if (!Psteiner->degree)
	    {
		Pstack = Pstack->next ;
		Ysafe_free(Psteiner) ;
	    }
	}
    } while (order<numnode) ;
}
else
{
    do {
	degree = 0 ;
	Pnode = garray[i]->first ;

	if (!count)
	{
	    /***********************************************************
	    * Search the adjacent list of the current vertex to test if
	    * a vertex in the list is a pin or has a degree greater than
	    * two.
	    * count = 0 --- the current vertex is not a Steiner vertex.
	    ***********************************************************/
	    while (Pnode)
	    {
		v1 = Pnode->t_vertex ;

		if (garray[v1]->status && v1!=Pcurrent->parent)
		{
		    if (earray[Pnode->edge]->intree&MIN_MASK)
		    {
			j = v1 ;
			degree++ ;
		    }
		}
		Pnode = Pnode->next ;
	    }
	}
	else
	{
	    /***********************************************************
	    * The search just returns to a Steiner vertex. We need to
	    * go through the number of count times for adjacent vertices
	    * which are in the minimum Steiner tree and add the vertex
	    * into the segment tree.
	    * count!=0 --- the current vertex is a Steiner vertex.
	    ***********************************************************/
	    while (Pnode)
	    {
		v1 = Pnode->t_vertex ;

		if (garray[v1]->status && v1!=Pcurrent->parent)
		{
		    if (earray[Pnode->edge]->intree&MIN_MASK)
		    {
			j = v1 ;
			degree++ ;
		    }

		    if (degree==count)
		    {
			count = 0 ;
			break ;
		    }
		}
		Pnode = Pnode->next ;
	    }
	}

	if (i>numnodes && parray[i-numnodes]->equiv)
	{
	    /***********************************************************
	    * The vertex is an equivalent pin. Scan through all its
	    * equivalent pins. If one is an isolated equivalent pin,
	    * then created a node in the segment tree for it and skip
	    * it; otherwise, create a node in the segment tree for it
	    * and push it into the stack.
	    ***********************************************************/
	    Pcurrent->equiv = TRUE ;
	    Pfirst = parray[i-numnodes] ;
	    Pfirst->key = TRUE ;
	    Ppin = Pfirst->next ;

	    while (Ppin!=Pfirst)
	    {
		if (Ppin->key==TRUE)
		{
		    Ppin = Ppin->next ;
		    continue ;
		}
		else
		{
		    Ppin->key = TRUE ;
		}
		Pnew = make_node() ;
		Pnew->equiv = TRUE ;
		Pnew->leaf = TRUE ;
		Pnew->order = ++order ;
		Pnew->parent = i ;
		Pnew->status = 0 ;
		Pnew->vertex = Ppin->vertex + numnodes ;
		Pnew->f_node = Pcurrent ;

		Plast->next = Pnew ;
		Pnew->prev = Plast ;
		Pnew->next = NIL(MDATA) ;
		Plast = Pnew ;

		Degree = 0 ;
		Pnode = garray[Ppin->vertex+numnodes]->first ; 
		while (Pnode)
		{
		    if (earray[Pnode->edge]->numpins)
		    {
			Degree++ ;
		    }
		    Pnode = Pnode->next ;
		}
		if (Degree)
		{
		    /*****************************************************
		    * The pin is not isolated. Push it into the stack.
		    *****************************************************/
		    Pnew->leaf = FALSE ;
		    Psteiner = (STACKPTR) Ysafe_malloc(sizeof(STACK)) ;
		    Psteiner->degree = Degree ;
		    Psteiner->Pparent = Pnew ;
		    Psteiner->next = Pstack ;
		    Pstack = Psteiner ;
		}
		/*
		Psteiner = (STACKPTR) Ysafe_malloc(sizeof(STACK)) ;
		Psteiner->degree = Degree ;
		Psteiner->Pparent = Pnew ;
		Psteiner->next = Pstack ;
		Pstack = Psteiner ;
		*/
		Ppin = Ppin->next ;
	    }
	}

	if (degree)
	{
	    /***********************************************************
	    * The current vertex is not a leaf. Generate a new node and
	    * expand the tree.
	    ***********************************************************/
	    Pnew = make_node() ;

	    Pnew->equiv = FALSE ;
	    Pnew->leaf = FALSE ;
	    Pnew->order = ++order ;
	    Pnew->parent = i ;
	    Pnew->status = 0 ;
	    Pnew->vertex = j ;

	    Plast->next = Pnew ;
	    Pnew->prev = Plast ;
	    Plast = Pnew ;

	    Pnew->next = NIL(MDATA) ;
	    Pnew->f_node = Pparent ;
	    Pcurrent = Pnew ;

	    v = i ;
	    i = j ;
	}
	else
	{
	    /***********************************************************
	    * If the current vertex is an equivalent pin, then check
	    * whether it has a son.
	    ***********************************************************/
	    if (Pcurrent->equiv && Pcurrent->next)
	    {
		v1 = Pcurrent->vertex - numnodes ;
		v2 = Pcurrent->next->vertex - numnodes ;
		if (parray[v1]->equiv==parray[v2]->equiv)
		{
		    Pcurrent->leaf = FALSE ;
		}
	    }
	    else
	    {
		Pcurrent->leaf = TRUE ;
	    }
	}

	if (degree==1 && j>numnodes)
	{
	    /***********************************************************
	    * A pin is reached which, with the start vertex i, forms a
	    * segment. Set Pparent to be Pnew and continue the search.
	    ***********************************************************/
	    Pparent = Pnew ;

	}
	else if (degree>1)
	{
	    /***********************************************************
	    * A Steiner vertex is reached which, with the start vertex
	    * i, forms a segment. Set Pparent to be Pnew, update the
	    * stack, and continue the search.
	    ***********************************************************/
	    if (Pstack && Pstack->Pparent->vertex==v)
	    {
		Pnew->f_node = Pstack->Pparent ;
		/*********************************************************
		* The Steiner point is in the stack already. Use goto to
		* jump over the part of pushing it to the stack.
		*********************************************************/
		goto contin_equiv ;
	    }

	    Psteiner = (STACKPTR) Ysafe_malloc(sizeof(STACK)) ;
	    Psteiner->degree = --degree ;
	    Psteiner->Pparent = Pnew->prev ;
	    Psteiner->next = Pstack ;
	    Pstack = Psteiner ;
	    Pnew->f_node = Pnew->prev ;

	    contin_equiv:

	    if (j>numnodes)
	    {
		Pparent = Pnew ;
	    }
	    else
	    {
		Pparent = Pnew->f_node ;
	    }
	}
	else if (!degree && Pstack)
	{
	    /***********************************************************
	    * A leaf is reached. Pop a vertex from the stack and continue
	    * the search from that vertex.
	    ***********************************************************/
	    Psteiner = Pstack ;
	    Pparent = Pcurrent = Psteiner->Pparent ;
	    count = Psteiner->degree ;
	    i = Pcurrent->vertex ;
	    Psteiner->degree-- ;

	    if (!Psteiner->degree)
	    {
		Pstack = Pstack->next ;
		Ysafe_free(Psteiner) ;
	    }
	}
    } while (order<numnode) ;
}

/***********************************************************
* Assign the segment tree to an array and set up the index
* array for quick access.
***********************************************************/
marray = (MDATAPTR *) Ysafe_malloc((numnode+1) * sizeof(MDATAPTR)) ;
marray[0] = NIL(MDATA) ;

Pcurrent = Proot ;
while (Pcurrent)
{
    i = Pcurrent->order ;
    marray[i] = Pcurrent ;
    j = Pcurrent->vertex ;
    iarray[j] = i ;

    Pcurrent = Pcurrent->next ;
}

/***********************************************************
* Assign the distance to the field in each entry of marray.
***********************************************************/
if (EQUIVAL==FALSE)
{
    for (i=2; i<=numnode; i++)
    {
	v1 = marray[i-1]->vertex ;
	v2 = marray[i]->vertex ;
	Pnode = garray[v1]->first ;

	while (Pnode && Pnode->t_vertex!=v2)
	{
	    Pnode = Pnode->next ;
	}

	if (Pnode && earray[Pnode->edge]->intree)
	{
	    marray[i]->dist = marray[i-1]->dist + Pnode->length ;
	}
	else
	{
	    j = marray[i]->f_node->order ;
	    v1 = marray[j]->vertex ;
	    Pnode = garray[v1]->first ;

	    while(Pnode && Pnode->t_vertex!=v2)
	    {
		Pnode = Pnode->next ;
	    }
	    marray[i]->dist = marray[j]->dist + Pnode->length ;
	}
    }
}
else
{
    for (i=2; i<=numnode; i++)
    {
	if (marray[i]->equiv && marray[i]->f_node->equiv)
	{
	    /***********************************************************
	    * Both pins are equivalent pins.
	    ***********************************************************/
	    v1 = marray[i]->vertex - numnodes ;
	    v2 = marray[i]->f_node->vertex - numnodes ;
	    if (parray[v1]->equiv==parray[v2]->equiv)
	    {
		/*********************************************************
		* Both pins are in the same group of equivalent pins.
		*********************************************************/
		marray[i]->dist = marray[i]->f_node->dist ;
	    }
	    else
	    {
		/*********************************************************
		* Both pins are not in the same group of equivalent pins.
		*********************************************************/
		goto USUAL_CASE ;
	    }
	}
	else
	{
	    USUAL_CASE:
	    v1 = marray[i-1]->vertex ;
	    v2 = marray[i]->vertex ;
	    Pnode = garray[v1]->first ;

	    while (Pnode && Pnode->t_vertex!=v2)
	    {
		Pnode = Pnode->next ;
	    }

	    if (Pnode && earray[Pnode->edge]->intree)
	    {
		marray[i]->dist = marray[i-1]->dist + Pnode->length ;
	    }
	    else
	    {
		j = marray[i]->f_node->order ;
		v1 = marray[j]->vertex ;
		Pnode = garray[v1]->first ;

		while(Pnode && Pnode->t_vertex!=v2)
		{
		    Pnode = Pnode->next ;
		}
		marray[i]->dist = marray[j]->dist + Pnode->length ;
	    }
	}
    }
}

marray[numnode]->leaf = TRUE ;

} /* end of construct_segment */

/* ==================================================================== */

PDATAPTR
find_key(e, v1, v2, p1, p2, state, Pdata)
int e ;
int v1 ;
int v2 ;
int p1 ;
int p2 ;
int state ;
PDATAPTR Pdata ;
{

int	v	;
int	dmax	;
int	fmax	;
int	tmax	;
int	dist	;
int	dist1	;
int	dist2	;
int	dist3	;
int	dist4	;
int	degree	;
int	equiv_degree	;

LISTPTR	 Pnlist		;
MDATAPTR Pnode1		;
MDATAPTR Pnode2		;
MDATAPTR Psteiner	;
PINPTR	 Pphead		;
PINPTR	 Pplist		;

if (marray[p1]->dist==marray[p2]->dist)
{
    /***********************************************************
    * The vertices in the minimum Steiner tree are equivalent
    * pins. Skip the pair.
    ***********************************************************/
    return(Pdata) ;
}

/***********************************************************
* Assign the distance from v1, one end of the edge, to p1,
* a vertex in the minimum Steiner tree, to dist1. Similarly,
* assign the distance from v2 to p2 to dist2.
***********************************************************/
switch (state)
{

case 1:
    dist1 = 
    dist2 = 0 ;
    break ;

case 2:
    dist1 = 0 ;
    v = marray[p2]->vertex ;
    dist2 = garray[v2]->tree[v]->dist ;
    break ;

case 3:
    v = marray[p1]->vertex ;
    dist1 = garray[v1]->tree[v]->dist ;
    dist2 = 0 ;
    break ;

case 4:
    v = marray[p1]->vertex ;
    dist1 = garray[v1]->tree[v]->dist ;
    dist3 = garray[v2]->tree[v]->dist ;
    v = marray[p2]->vertex ;
    dist2 = garray[v2]->tree[v]->dist ;
    dist4 = garray[v1]->tree[v]->dist ;
    break ;

case 5:
    v = marray[p1]->vertex ;
    dist1 = garray[v1]->tree[v]->dist ;
    v = marray[p2]->vertex ;
    dist2 = garray[v2]->tree[v]->dist ;
    break ;

default:
    ERROR1("\n\n");
    ERROR3("Unexpected state is found at %d of %s", __LINE__, __FILE__) ;
    break ;

}

/***********************************************************
* Swap the vertices and pins if necessary to make sure that
* p1 precedes p2 in the segment tree.
***********************************************************/
if (p1>p2)
{
    SAVE(v1, tmp, int) ;
    v1 = v2 ;
    RSTR(v2, tmp) ;

    SAVE(p1, tmp, int) ;
    p1 = p2 ;
    RSTR(p2, tmp) ;

    if (state==4)
    {
	SAVE(dist1, tmp, int) ;
	dist1 = dist3 ;
	RSTR(dist3, tmp) ;

	SAVE(dist2, tmp, int) ;
	dist2 = dist4 ;
	RSTR(dist4, tmp) ;
    }
}

/***********************************************************
* Find the longest segment in the cycle formed by a portion
* of the segment tree and the edge plus, probably, the
* extensions from its two end-points to the vertices.
***********************************************************/
dmax = INT_MIN ;

/***********************************************************
* Find the common Steiner vertex to which the two vertices
* in the minimum Steiner tree are connected or make sure p1
* and p2 are on the smae path.
***********************************************************/
marray[p1]->status = steiner_label ;
Pnode1 = marray[p1] ;

while (Pnode1)
{
    if (Pnode1->vertex <= numnodes)
    {
	Pnode1->status = steiner_label ;
    }
    else
    {
	if (Pnode1->equiv && !Pnode1->leaf)
	{
	    /***********************************************************
	    * This pin is an equivalent pin. Check if it is a Steiner
	    * point, too. To do so, first go through the edges incident
	    * the pin and count the degree of the edges in the first
	    * tree. And then go through the equivalent pins of the pin
	    * and count how many there.
	    ***********************************************************/
	    degree = 0 ;
	    Pnlist = garray[Pnode1->vertex]->first ;
	    while (Pnlist)
	    {
		if (earray[Pnlist->edge]->intree)
		{
		    degree++ ;
		}
		Pnlist = Pnlist->next ;
	    }

	    equiv_degree = -1 ;
	    Pphead = parray[Pnode1->vertex-numnodes] ;
	    Pplist = Pphead->next ;
	    while (Pplist!=Pphead)
	    {
		equiv_degree++ ;
		Pplist = Pplist->next ;
	    }
	    degree += equiv_degree ;

	    if (degree>1)
	    {
		Pnode1->status = steiner_label ;
	    }
	}
    }
    Pnode1 = Pnode1->f_node ;
}

v = p2 ;

while (v>1)
{
    if(v==p1)
    {
	break ;
    }

    if(marray[v]->status==steiner_label)
    {
	break ;
    }

    if(marray[v-1]->leaf)
    {
	v = marray[v]->f_node->order ;
    }
    else
    {
	v-- ;
    }
}

if (v==p1)
{
    /***********************************************************
    * p1 and p2 are on the same path.
    ***********************************************************/
    Psteiner = NIL(MDATA) ;
}
else
{
    /***********************************************************
    * p1 and p2 are on different paths and both will merge
    * to a common Steier vertex.
    ***********************************************************/
    Psteiner = marray[v] ;
}

/***********************************************************
* There are two possibilities: One is that p1 and p2 are on
* the same path in the minimum Steiner tree and another is
* that p1 and p2 are on different segments which merge at
* the common Steiner vertex.
***********************************************************/
Pnode1 = marray[p1] ;
Pnode2 = marray[p2] ;

if (!Psteiner)
{
    /***********************************************************
    * p1 and p2 are on the same path.
    ***********************************************************/
    while (Pnode2->f_node && Pnode2->f_node->order>p1)
    {
	dist = Pnode2->dist - Pnode2->f_node->dist ;

	if (dmax<dist)
	{
	    dmax = dist ;
	    fmax = Pnode2->order ;
	    tmax = Pnode2->f_node->order ;
	}

	Pnode2 = Pnode2->f_node ;
    }

    dist = Pnode2->dist - Pnode1->dist ;

    if (dmax<dist)
    {
	dmax = dist ;
	fmax = Pnode2->order ;
	tmax = Pnode1->order ;
    }
}
else
{
    do {
	dist = Pnode1->dist - Pnode1->f_node->dist ;

	if (dmax<dist)
	{
	    dmax = dist ;
	    fmax = Pnode1->order ;
	    tmax = Pnode1->f_node->order ;
	}

	Pnode1 = Pnode1->f_node ;

    } while (Pnode1!=Psteiner) ;

    do {
	dist = Pnode2->dist - Pnode2->f_node->dist ;

	if (dmax<dist)
	{
	    dmax = dist ;
	    fmax = Pnode2->order ;
	    tmax = Pnode2->f_node->order ;
	}

	Pnode2 = Pnode2->f_node ;
    } while (Pnode2!=Psteiner) ;
}


/***********************************************************
* For the first three casese there is only a single cycle
* which is feasible, so we need only to check if the current
* configuration is better than the previous one if there is
* one. For case 4, we need to test the feasibility of the
* cycle and compare two possible connections.
***********************************************************/
if (state==4)
{
    if (dist1 + dist2<dist3 + dist4)
    {
	/***********************************************************
	* The distance from v1 to p1 and from v2 to p2 is shorter
	* than the distance from v1 to p2 and from v2 to p1.
	*
	* First make sure that the paths do not merge to a same
	* vertex before they reach the corresponding end-points,
	* respectively.
	***********************************************************/
	v = marray[p1]->vertex ;
	v = garray[v1]->tree[v]->parent ;

	while (v!=v1)
	{
	    garray[v]->status = steiner_label ;
	    v = garray[v1]->tree[v]->parent ;
	}

	v = marray[p2]->vertex ;
	v = garray[v2]->tree[v]->parent ;

	while (v!=v2 && garray[v]->status!=steiner_label)
	{
	    v = garray[v2]->tree[v]->parent ;
	}

	if (v!=v2)
	{
	    return(Pdata) ;
	}

	dist = dist1 + dist2 + earray[e]->length - dmax ;

	if (Pdata)
	{
	    if (Pdata->key>dist)
	    {
		Pdata->key = dist ;
		Pdata->edge = e ;
		Pdata->mark[0] = fmax ;
		Pdata->mark[1] = tmax ;
		Pdata->node[0] = v1 ;
		Pdata->node[1] = v2 ;
		Pdata->pin[0] = p1 ;
		Pdata->pin[1] = p2 ;
	    }
	}
	else
	{
	    Pdata = (PDATAPTR) Ysafe_malloc(sizeof(PDATA)) ;
	    Pdata->key = dist ;
	    Pdata->edge = e ;
	    Pdata->mark[0] = fmax ;
	    Pdata->mark[1] = tmax ;
	    Pdata->node[0] = v1 ;
	    Pdata->node[1] = v2 ;
	    Pdata->pin[0] = p1 ;
	    Pdata->pin[1] = p2 ;
	}
    }
    else
    {
	/***********************************************************
	* The distance from v1 to p2 and from v2 to p1 is shorter
	* than the distance from v1 to p1 and from v2 to p2.
	*
	* First make sure that the paths do not merge to a same
	* vertex before they reach the corresponding end-points,
	* respectively.
	***********************************************************/
	v = marray[p1]->vertex ;
	v = garray[v2]->tree[v]->parent ;

	while (v!=v2)
	{
	    garray[v]->status = steiner_label ;
	    v = garray[v2]->tree[v]->parent ;
	}

	v = marray[p2]->vertex ;
	v = garray[v1]->tree[v]->parent ;

	while (v!=v1 && garray[v]->status!=steiner_label)
	{
	    v = garray[v1]->tree[v]->parent ;
	}

	if (v!=v1)
	{
	    return(Pdata) ;
	}

	dist = dist3 + dist4 + earray[e]->length - dmax ;

	if (Pdata)
	{
	    if (Pdata->key>dist)
	    {
		Pdata->key = dist ;
		Pdata->edge = e ;
		Pdata->mark[0] = fmax ;
		Pdata->mark[1] = tmax ;
		Pdata->node[0] = v2 ;
		Pdata->node[1] = v1 ;
		Pdata->pin[0] = p1 ;
		Pdata->pin[1] = p2 ;
	    }
	}
	else
	{
	    Pdata = (PDATAPTR) Ysafe_malloc(sizeof(PDATA)) ;
	    Pdata->key = dist ;
	    Pdata->edge = e ;
	    Pdata->mark[0] = fmax ;
	    Pdata->mark[1] = tmax ;
	    Pdata->node[0] = v2 ;
	    Pdata->node[1] = v1 ;
	    Pdata->pin[0] = p1 ;
	    Pdata->pin[1] = p2 ;
	}
    }
}
else
{
    if (state==5)
    {
	/***********************************************************
	* In this case we have an edge and two extended paths from
	* the edge's end-points. So we want to make sure that the
	* paths do not merge to a same vertex before they reach the
	* corresponding end-points, respectively.
	***********************************************************/
	v = marray[p1]->vertex ;
	v = garray[v1]->tree[v]->parent ;

	while (v!=v1)
	{
	    garray[v]->status = steiner_label ;
	    v = garray[v1]->tree[v]->parent ;
	}

	v = marray[p2]->vertex ;
	v = garray[v2]->tree[v]->parent ;

	while (v!=v2 && garray[v]->status!=steiner_label)
	{
	    v = garray[v2]->tree[v]->parent ;
	}

	if (v!=v2)
	{
	    return(Pdata) ;
	}
    }

    dist = dist1 + dist2 + earray[e]->length - dmax ;
    if (Pdata)
    {
	if (Pdata->key>dist)
	{
	    Pdata->key = dist ;
	    Pdata->edge = e ;
	    Pdata->mark[0] = fmax ;
	    Pdata->mark[1] = tmax ;
	    Pdata->node[0] = v1 ;
	    Pdata->node[1] = v2 ;
	    Pdata->pin[0] = p1 ;
	    Pdata->pin[1] = p2 ;
	}
    }
    else
    {
	Pdata = (PDATAPTR) Ysafe_malloc(sizeof(PDATA)) ;
	Pdata->key = dist ;
	Pdata->edge = e ;
	Pdata->mark[0] = fmax ;
	Pdata->mark[1] = tmax ;
	Pdata->node[0] = v1 ;
	Pdata->node[1] = v2 ;
	Pdata->pin[0] = p1 ;
	Pdata->pin[1] = p2 ;
    }
    return(Pdata) ;
}

return(Pdata) ;

} /* end of find_key */

/* ==================================================================== */

int
build_tree_heap()
{

int	status	;
int	status1	;
int	status2	;
int	i	;
int	j	;
int	i1	;
int	i2	;
int	v1	;
int	v2	;

PDATAPTR Pdata	;

construct_segment() ;

steiner_label = 3 ;

for (i=1; i<=totedges; i++)
{
    if (earray[i]->intree || earray[i]->empty)
    {
	continue ;
    }

    Pdata = NIL(PDATA) ;

    /***********************************************************
    * The edge is not in any tree yet. Insert it into the heap.
    ***********************************************************/
    v1 = earray[i]->node[0] ;
    v2 = earray[i]->node[1] ;
    i1 = iarray[v1] ;
    i2 = iarray[v2] ;

    if (i1 && i2)
    {
	/***********************************************************
	* Both vertices are in the minimum Steiner tree. Find the
	* longest segment in the cycle formed by portion of the
	* minimum Steiner tree and the edge. Set the key to be the
	* difference of the length of the edge and the distance of
	* the longest segment.
	***********************************************************/
	steiner_label++ ;
	Pdata = find_key(i, v1, v2, i1, i2, 1, Pdata) ;
    }
    else if (i1)
    {
	/***********************************************************
	* One vertex is in the minimum Steiner tree. Scan through
	* all the other vertices in the minimum Steiner tree and
	* do the same work as above.
	***********************************************************/
	for (j=1; j<=numnode; j++)
	{
	    if (j==i1)
	    {
		continue ;
	    }

	    /***********************************************************
	    * Check whether the vertices of the path from i2 to j are
	    * in the minimum Steiner tree. If so, discard this vertex
	    * continue for the next vertex in the segment tree.
	    ***********************************************************/
	    status = FALSE ;

	    i2 = marray[j]->vertex ;
	    i2 = garray[v2]->tree[i2]->parent ;

	    if (i2==v1)
	    {
		continue ;
	    }

	    while (i2!=v2)
	    {
		if (iarray[i2])
		{
		    status = TRUE ;
		    break ;
		}

		if (i2==v1)
		{
		    status = TRUE ;
		    break ;
		}

		i2 = garray[v2]->tree[i2]->parent ;
	    }

	    if (status==TRUE)
	    {
		continue ;
	    }

	    steiner_label++ ;
	    Pdata = find_key(i, v1, v2, i1, j, 2, Pdata) ;
	}

    }
    else if (i2)
    {
	/***********************************************************
	* One vertex is in the minimum Steiner tree. Scan through
	* all the other vertices in the minimum Steiner tree and
	* do the same work as above.
	***********************************************************/
	for (j=1; j<=numnode ; j++)
	{
	    if (j==i2)
	    {
		continue ;
	    }

	    /***********************************************************
	    * Check whether the vertices of the path from i2 to j are
	    * in the minimum Steiner tree. If so, discard this vertex
	    * continue for the next vertex in the segment tree.
	    ***********************************************************/
	    status = FALSE ;

	    i1 = marray[j]->vertex ;
	    i1 = garray[v1]->tree[i1]->parent ;

	    if (i1==v2)
	    {
		continue ;
	    }

	    while (i1!=v1)
	    {
		if (iarray[i1])
		{
		    status = TRUE ;
		    break ;
		}

		if (i1==v2)
		{
		    status = TRUE ;
		    break ;
		}

		i1 = garray[v2]->tree[i1]->parent ;
	    }

	    if (status==TRUE)
	    {
		continue ;
	    }

	    steiner_label++ ;
	    Pdata = find_key(i, v1, v2, j, i2, 3, Pdata) ;
	}
    }
    else
    {
	/***********************************************************
	* None of the two vertices is in the minimum Steiner tree.
	* Scan through all pairs of the vertices in the minimum
	* Steiner tree and search for a pair of vertices which give
	* a feasible cycle by adding the edge and the paths extended
	* from its two end-points to the pair of vertices in the
	* minimum Steiner tree.
	* In this case, we first check whether any vertex on a path
	* from one end-point of the edge to a vertex in the minimum
	* Steiner tree is in the minimum Steiner tree. If so, discard
	* the vertex in the minimum Steiner tree and continue to
	* the next pair.
	***********************************************************/
	for (i1=1; i1<numnode; i1++)
	{
	    /***********************************************************
	    * First check if is any vertex on the shortest path from v1
	    * to i1 in the minimum Steiner tree or v2.
	    *
	    * Code for variable status1:
	    *	0 --- both v1->i1 and v2->i1 generate a feasible path
	    *	1 --- the path from v1 to i1 is not feasible
	    *	2 --- the path from v2 to i1 is not feasible
	    *	3 --- none of v1->i1 and v2->i1 generates a feasible
	    *		path
	    * Code for variable status2:
	    *	0 --- both v1->i2 and v2->i2 generate a feasible path
	    *	1 --- the path from v1 to i2 is not feasible 
	    *	2 --- the path from v2 to i2 is not feasible 
	    *	3 --- none of v1->i2 and v2->i2 generates a feasible
	    *		path
	    ***********************************************************/
	    status1 = 0 ;
	    j = marray[i1]->vertex ;
	    j = garray[v1]->tree[j]->parent ;

	    while (j!=v1)
	    {
		if (iarray[j])
		{
		    status1 = 1 ;
		    break ;
		}
		if (j==v2)
		{
		    status1 = 1 ;
		    break ;
		}
		j = garray[v1]->tree[j]->parent ;
	    }

	    /***********************************************************
	    * Now check if is any vertex on the shortest path from v2 
	    *  to i1 in the minimum Steiner tree or v1.
	    ***********************************************************/
	    j = marray[i1]->vertex ;
	    j = garray[v2]->tree[j]->parent ;

	    if (!status1)
	    {
		/*********************************************************
		* The previous path is feasible.
		*********************************************************/
		while (j!=v2)
		{
		    if (iarray[j])
		    {
			status1 = 2 ;
			break ;
		    }
		    if(j==v1)
		    {
			status1 = 2 ;
		    }
		    j = garray[v2]->tree[j]->parent ;
		}
	    }
	    else
	    {
		/*********************************************************
		* The previous path is not feasible.
		*********************************************************/
		while (j!=v2)
		{
		    if (iarray[j])
		    {
			status1 = 3 ;
			break ;
		    }
		    if(j==v1)
		    {
			status1 = 3 ;
		    }
		    j = garray[v2]->tree[j]->parent ;
		}
	    }

	    if (status1==3)
	    {
		continue ;
	    }

	    for (i2=i1+1; i2<=numnode; i2++)
	    {
		/*********************************************************
		* Check for another vertex in the minimum Steiner tree.
		*********************************************************/
		status2 = 0 ;
		j = marray[i2]->vertex ;
		j = garray[v1]->tree[j]->parent ;

		while (j!=v1)
		{
		    if (iarray[j])
		    {
			status2 = 1 ;
			break ;
		    }
		    if (j==v2)
		    {
			status2 = 1 ;
			break ;
		    }
		    j = garray[v1]->tree[j]->parent ;
		}

		j = marray[i2]->vertex ;
		j = garray[v2]->tree[j]->parent ;

		if (!status2)
		{
		    while (j!=v2)
		    {
			if (iarray[j])
			{
			    status2 = 2 ;
			    break ;
			}
			if (j==v1)
			{
			    status2 = 2 ;
			    break ;
			}
			j = garray[v2]->tree[j]->parent ;
		    }
		}
		else
		{
		    while (j!=v2)
		    {
			if (iarray[j])
			{
			    status2 = 3 ;
			    break ;
			}
			if (j==v1)
			{
			    status2 = 3 ;
			    break ;
			}
			j = garray[v2]->tree[j]->parent ;
		    }
		}

		if (status2==3)
		{
		    continue ;
		}

		/*********************************************************
		* Paths from v1, one of the edge, to j, a vertex in the
		* minimum Steiner tree and from v2, another edge of the
		* edge, to i2, another vertex in the minimum Steiner tree.
		* ---------
		****** Notice that i1 always precedes i2. ******
		*********************************************************/
		steiner_label++ ;
		if (!status1)
		{
		    if (!status2)
		    {
			Pdata = find_key(i, v1, v2, i1, i2, 4, Pdata) ;
		    }
		    else if (status2==1)
		    {
			Pdata = find_key(i, v1, v2, i1, i2, 5, Pdata) ;
		    }
		    else
		    {
			Pdata = find_key(i, v2, v1, i1, i2, 5, Pdata) ;
		    }
		}
		else if (status1==1)
		{
		    if (status2!=1)
		    {
			Pdata = find_key(i, v2, v1, i1, i2, 5, Pdata) ;
		    }
		}
		else
		{
		    if (status2!=2)
		    {
			Pdata = find_key(i, v1, v2, i1, i2, 5, Pdata) ;
		    }
		}
	    }
	}
    }

    /***********************************************************
    * If status is TRUE (=1), then a feasible path has been
    * found; therefore, insert the edge into the heap.
    ***********************************************************/
    if (Pdata)
    {
	insert(harray, Pdata->key, Pdata) ;
    }
}

STATE = TRUE ;

return(numnode) ;

} /* end of build_tree_heap */

/* ==================================================================== */

int
rebuild_tree_heap()
{

DELETE_SEGMENT_TREE(Phead, Proot) ;

harray[0]->key = 0 ;

return(build_tree_heap()) ;

} /* end of rebuild_tree_heap */

/* ==================================================================== */

void
construct_tree(Pdata, MASK, mask)
PDATAPTR Pdata	;
unsigned MASK	;
unsigned mask	;
{

int	m1	;
int	m2	;
int	v1	;
int	v2	;
int	e	;
int	v	;

LISTPTR Pnode	;
LISTPTR Pnode1	;

numtrees++ ;

m1 = Pdata->mark[0] ;
m2 = Pdata->mark[1] ;

/***********************************************************
* Mark the edges which are removed from the minimum Steiner
* tree to construct a new tree.
***********************************************************/
if (EQUIVAL==FALSE)
{
    if (m1<m2)
    {
	while (m2>m1)
	{
	    v = marray[m2]->vertex ;
	    Pnode = garray[v]->first ;

	    if (marray[m2-1]->leaf)
	    {
		m2 = marray[m2]->f_node->order ;
	    }
	    else
	    {
		m2-- ;
	    }

	    v = marray[m2]->vertex ;

	    while (Pnode->t_vertex!=v)
	    {
		Pnode = Pnode->next ;
	    }

	    e = Pnode->edge ;
	    earray[e]->numpins = numtrees ;
	}
    }
    else
    {
	while (m1>m2)
	{
	    v = marray[m1]->vertex ;
	    Pnode = garray[v]->first ;

	    if (marray[m1-1]->leaf)
	    {
		m1 = marray[m1]->f_node->order ;
	    }
	    else
	    {
		m1-- ;
	    }

	    v = marray[m1]->vertex ;

	    while (Pnode->t_vertex!=v)
	    {
		Pnode = Pnode->next ;
	    }

	    e = Pnode->edge ;
	    earray[e]->numpins = numtrees ;
	}
    }
}
else
{
    if (m1<m2)
    {
	while (m2>m1)
	{
	    v = marray[m2]->vertex ;
	    Pnode = Pnode1 = garray[v]->first ;

	    if (marray[m2-1]->leaf)
	    {
		m2 = marray[m2]->f_node->order ;
	    }
	    else
	    {
		m2-- ;
	    }

	    if (marray[m2]->equiv)
	    {
		while (1)
		{
		    v = marray[m2]->vertex ;

		    while (Pnode && Pnode->t_vertex!=v)
		    {
			Pnode = Pnode->next ;
		    }

		    if (Pnode)
		    {
			break ;
		    }
		    else
		    {
			m2-- ;
			Pnode = Pnode1 ;
		    }
		}
	    }
	    else
	    {
		v = marray[m2]->vertex ;

		while (Pnode)
		{
		    while (Pnode)
		    {
			if (Pnode->t_vertex!=v)
			{
			    Pnode = Pnode->next ;
			}
			else
			{
			    if (parray[v-numnodes]->equiv !=
				 parray[Pnode->t_vertex-numnodes]->equiv)
			    {
				Pnode = Pnode->next ;
			    }
			    else
			    {
				if (earray[Pnode->edge]->intree&mask)
				{
				    break ;
				}
				else
				{
				    Pnode = Pnode->next ;
				}
			    }
			}
		    }

		    if (Pnode)
		    {
			break ;
		    }
		    else
		    {
			m1-- ;
			Pnode = Pnode1 ;
		    }
		}
	    }

	    e = Pnode->edge ;
	    earray[e]->numpins = numtrees ;
	}
    }
    else
    {
	while (m1>m2)
	{
	    v = marray[m1]->vertex ;
	    Pnode = Pnode1 = garray[v]->first ;

	    if (marray[m1-1]->leaf)
	    {
		m1 = marray[m1]->f_node->order ;
	    }
	    else
	    {
		m1-- ;
	    }

	    if (marray[m1]->equiv)
	    {
		while (1)
		{
		    v = marray[m1]->vertex ;

		    while (Pnode)
		    {
			if (Pnode->t_vertex!=v)
			{
			    Pnode = Pnode->next ;
			}
			else
			{
			    if (parray[v-numnodes]->equiv !=
				 parray[Pnode->t_vertex-numnodes]->equiv)
			    {
				Pnode = Pnode->next ;
			    }
			    else
			    {
				if (earray[Pnode->edge]->intree&mask)
				{
				    break ;
				}
				else
				{
				    Pnode = Pnode->next ;
				}
			    }
			}
		    }

		    if (Pnode)
		    {
			break ;
		    }
		    else
		    {
			m1-- ;
			Pnode = Pnode1 ;
		    }
		}
	    }
	    else
	    {
		v = marray[m1]->vertex ;

		while (Pnode && Pnode->t_vertex!=v)
		{
		    Pnode = Pnode->next ;
		}
	    }

	    e = Pnode->edge ;
	    earray[e]->numpins = numtrees ;
	}
    }
}

/***********************************************************
* Update the field intree of earray to add the edges which
* are in the minimum Steiner tree into the new tree.
***********************************************************/
for (v=1; v<=numtree_e; v++)
{
    e = jarray[v] ;
    if (earray[e]->numpins==numtrees)
    {
	continue ;
    }
    earray[e]->intree |= MASK ;
}

/***********************************************************
* Add two extensions from the two endpoints of the edge into
* the intree field of earray for the new tree.
***********************************************************/
m1 = Pdata->pin[0] ;
m2 = Pdata->pin[1] ;
v1 = Pdata->node[0] ;
v2 = Pdata->node[1] ;

v = marray[m1]->vertex ;

while (v!=v1)
{
    e = garray[v1]->tree[v]->edge ;
    earray[e]->intree |= MASK ;
    v = garray[v1]->tree[v]->parent ;
}

v = marray[m2]->vertex ;

while (v!=v2)
{
    e = garray[v2]->tree[v]->edge ;
    earray[e]->intree |= MASK ;
    v = garray[v2]->tree[v]->parent ;
}

/***********************************************************
* Add the edge into the new tree.
***********************************************************/
e = Pdata->edge ;
earray[e]->intree |= MASK ;

} /* end of construct_tree */

/* ==================================================================== */

int
nth_route_segment()
{

construct_segment() ;

return(numnode) ;

}
