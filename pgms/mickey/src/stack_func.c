#ifndef lint
static char SccsId[] = "@(#)stack_func.c	Yale Version 2.2 5/16/91" ;
#endif
/* -----------------------------------------------------------------

	FILE:		stack_func.c
	AUTHOR:		Dahe Chen
	DATE:		Wed Mar 14 23:00:57 EDT 1990
	CONTENTS:	push_down()
			pop_up()
	REVISION:

----------------------------------------------------------------- */

#include	<stdio.h>

#include <yalecad/base.h>

typedef struct stack_element {
    short	index		;
    struct stack_element *next	;
} STACK_ELEMENT ,
*STACK_ELEMENTPTR ;

static	STACK_ELEMENTPTR	Pitem	;

void
push_down( Pstack_head, index )
STACK_ELEMENTPTR *Pstack_head	;
short		index	;
{

Pitem = (STACK_ELEMENTPTR) Ysafe_malloc( (INT)sizeof(STACK_ELEMENT) ) ;
Pitem->index = index ;
Pitem->next = *Pstack_head ;
(*Pstack_head) = Pitem ;

} /* end of push_down */

/* ==================================================================== */

int
pop_up( Pstack_head )
STACK_ELEMENTPTR *Pstack_head	;
{

int	item = 0	;

Pitem = *Pstack_head ;
if ( Pitem )
{
    item = Pitem->index ;
    (*Pstack_head) = (*Pstack_head)->next ;
    Ysafe_free( (char *) Pitem ) ;
}

return( item ) ;

} /* end of pop_up */
