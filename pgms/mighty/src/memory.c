#ifndef lint
static char SccsId[] = "@(#) memory.c version 6.1 6/19/90" ;
#endif

#include "mighty.h"

#define MEMBLKSIZ 512

/* global free list pointers and initializers */
SCHED_PTR S_intstackfree = (SCHED_PTR)NULL;
SCHED_ELEMENT S_intstackinit;

LINKPTR S_linkfree = (LINKPTR)NULL;
LINK S_linkinit;

LINKLISTPTR S_lklistfree = (LINKLISTPTR)NULL;
LINKLIST S_lklistinit;

SEARCHPTR S_searchfree = (SEARCHPTR)NULL;
SEARCH S_searchinit;

NET_STACK S_netstackfree = (NET_STACK)NULL;
NET_STACK_ELEMENT S_netstackinit;

EDGE_LIST S_edgefree = (EDGE_LIST)NULL;
EDGE_ELEM S_edgeinit;

CYCLE_LIST S_cyclefree = (CYCLE_LIST)NULL;
CYCLE_ELEM S_cycleinit;

PINPTR S_pinfree = (PINPTR)NULL;
PIN S_pininit;


/* SCHED_ELEMENT management */

SCHED_PTR S_getschedq()
{
SCHED_PTR tmpschedq;
int i;
	if( S_intstackfree == (SCHED_PTR)NULL ) {
	/* (=> Have to get a new block */
		S_intstackfree = (SCHED_PTR) calloc( MEMBLKSIZ, sizeof( SCHED_ELEMENT) );
		/* link the block together */
		for( i = 0; i < MEMBLKSIZ; i++ )
			(S_intstackfree + i)->next = S_intstackfree + i + 1;
		(S_intstackfree + MEMBLKSIZ - 1)->next = (SCHED_PTR)NULL;
	}
	tmpschedq = S_intstackfree;
	S_intstackfree = S_intstackfree->next;
	*tmpschedq = S_intstackinit;
	return( tmpschedq );
}

S_retschedq( intstack )
SCHED_PTR intstack;
{
	if( intstack != (SCHED_PTR)NULL ) {
		intstack->next = S_intstackfree;
		S_intstackfree = intstack;
	}
}


/* LINK management */

LINKPTR S_getlink()
{
LINKPTR tmplink;
int i;
	if( S_linkfree == (LINKPTR)NULL ) {
	/* (=> Have to get a new block */
		S_linkfree = (LINKPTR) calloc( MEMBLKSIZ , sizeof( LINK) );
		/* link the block together */
		for( i = 0; i < MEMBLKSIZ; i++ )
			(S_linkfree + i)->netnext = S_linkfree + i + 1;
		(S_linkfree + MEMBLKSIZ - 1)->netnext = (LINKPTR)NULL;
	}
	tmplink = S_linkfree;
	S_linkfree = S_linkfree->netnext;
	*tmplink = S_linkinit;
	return( tmplink );
}

S_retlink( linkstack )
LINKPTR linkstack;
{
	if( linkstack != (LINKPTR)NULL ) {
		linkstack->netnext = S_linkfree;
		S_linkfree = linkstack;
	}
}


/* SEARCH management */

SEARCHPTR S_getsearchq()
{
SEARCHPTR tmpsearch;
int i;
	if( S_searchfree == (SEARCHPTR)NULL ) {
	/* (=> Have to get a new block */
		S_searchfree = (SEARCHPTR) calloc( MEMBLKSIZ , sizeof( SEARCH) );
		/* link the block together */
		for( i = 0; i < MEMBLKSIZ; i++ )
			(S_searchfree + i)->next = S_searchfree + i + 1;
		(S_searchfree + MEMBLKSIZ - 1)->next = (SEARCHPTR)NULL;
	}
	tmpsearch = S_searchfree;
	S_searchfree = S_searchfree->next;
	*tmpsearch = S_searchinit;
	return( tmpsearch );
}

S_retsearchq( searchq )
SEARCHPTR searchq;
{
	if( searchq != (SEARCHPTR)NULL ) {
		searchq->next = S_searchfree;
		S_searchfree = searchq;
	}
}


/* LINKLIST management */

LINKLISTPTR S_getlklist()
{
LINKLISTPTR tmplklist;
int i;
	if( S_lklistfree == (LINKLISTPTR)NULL ) {
	/* (=> Have to get a new block */
		S_lklistfree = (LINKLISTPTR) calloc( MEMBLKSIZ , sizeof( LINKLIST) );
		/* link the block together */
		for( i = 0; i < MEMBLKSIZ; i++ )
			(S_lklistfree + i)->next = S_lklistfree + i + 1;
		(S_lklistfree + MEMBLKSIZ - 1)->next = (LINKLISTPTR)NULL;
	}
	tmplklist = S_lklistfree;
	S_lklistfree = S_lklistfree->next;
	*tmplklist = S_lklistinit;
	return( tmplklist );
}

S_retlklist( lklist )
LINKLISTPTR lklist;
{
	if( lklist != (LINKLISTPTR)NULL ) {
		lklist->next = S_lklistfree;
		S_lklistfree = lklist;
	}
}

/* NET_STACK_ELEMENT management */

NET_STACK S_getnetstack()
{
NET_STACK tmpstack;
int i;
	if( S_netstackfree == (NET_STACK)NULL ) {
	/* (=> Have to get a new block */
		S_netstackfree = (NET_STACK) calloc( MEMBLKSIZ , sizeof( NET_STACK_ELEMENT) );
		/* link the block together */
		for( i = 0; i < MEMBLKSIZ; i++ )
			(S_netstackfree + i)->next = S_netstackfree + i + 1;
		(S_netstackfree + MEMBLKSIZ - 1)->next = (NET_STACK)NULL;
	}
	tmpstack = S_netstackfree;
	S_netstackfree = S_netstackfree->next;
	*tmpstack = S_netstackinit;
	return( tmpstack );
}

S_retnetstack( netstack )
NET_STACK netstack;
{
	if( netstack != (NET_STACK)NULL ) {
		netstack->next = S_netstackfree;
		S_netstackfree = netstack;
	}
}


/* EDGE_ELEM management */

EDGE_LIST S_getedge()
{
EDGE_LIST tmpedge;
int i;
	if( S_edgefree == (EDGE_LIST)NULL ) {
	/* (=> Have to get a new block */
		S_edgefree = (EDGE_LIST) calloc( MEMBLKSIZ , sizeof( EDGE_ELEM) );
		/* link the block together */
		for( i = 0; i < MEMBLKSIZ; i++ )
			(S_edgefree + i)->next = S_edgefree + i + 1;
		(S_edgefree + MEMBLKSIZ - 1)->next = (EDGE_LIST)NULL;
	}
	tmpedge = S_edgefree;
	S_edgefree = S_edgefree->next;
	*tmpedge = S_edgeinit;
	return( tmpedge );
}

S_retedge( edge )
EDGE_LIST edge;
{
	if( edge != (EDGE_LIST)NULL ) {
		edge->next = S_edgefree;
		S_edgefree = edge;
	}
}


/* CYCLE_ELEM management */

CYCLE_LIST S_getcycle()
{
CYCLE_LIST tmpcycle;
int i;
	if( S_cyclefree == (CYCLE_LIST)NULL ) {
	/* (=> Have to get a new block */
		S_cyclefree = (CYCLE_LIST) calloc( MEMBLKSIZ , sizeof( CYCLE_ELEM) );
		/* link the block together */
		for( i = 0; i < MEMBLKSIZ; i++ )
			(S_cyclefree + i)->next = S_cyclefree + i + 1;
		(S_cyclefree + MEMBLKSIZ - 1)->next = (CYCLE_LIST)NULL;
	}
	tmpcycle = S_cyclefree;
	S_cyclefree = S_cyclefree->next;
	*tmpcycle = S_cycleinit;
	return( tmpcycle );
}

S_retcycle( cycle )
CYCLE_LIST cycle;
{
	if( cycle != (CYCLE_LIST)NULL ) {
		cycle->next = S_cyclefree;
		S_cyclefree = cycle;
	}
}


/* PIN management */

PINPTR S_getpin()
{
PINPTR tmppin;
int i;
	if( S_pinfree == (PINPTR)NULL ) {
	/* (=> Have to get a new block */
		S_pinfree = (PINPTR) calloc( MEMBLKSIZ , sizeof( PIN) );
		/* link the block together */
		for( i = 0; i < MEMBLKSIZ; i++ )
			(S_pinfree + i)->next = S_pinfree + i + 1;
		(S_pinfree + MEMBLKSIZ - 1)->next = (PINPTR)NULL;
	}
	tmppin = S_pinfree;
	S_pinfree = S_pinfree->next;
	*tmppin = S_pininit;
	return( tmppin );
}

S_retpin( pin )
PINPTR pin;
{
	if( pin != (PINPTR)NULL ) {
		pin->next = S_pinfree;
		S_pinfree = pin;
	}
}
