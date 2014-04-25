#ifndef lint
static char SccsId[] = "@(#) stack.c version 6.1 6/19/90" ;
#endif

#include "mighty.h"

/**********************************************************************
 *
 *  push_net inserts the given NETPTR on top of the given stack.  The
 *  address of the NET_STACK must be passed so that it can be updated.
 *
 **********************************************************************/

void push_net (stack, net)
NET_STACK *stack;		/* the stack getting pushed */
NETPTR net;			/* the net pointer getting inserted on the
				   stack */
{
    NET_STACK temp;	/* new element to be pushed on stack */
    NET_STACK S_getnetstack();

    /*
    temp = (NET_STACK) alloc (1, sizeof (NET_STACK_ELEMENT));
    */
    temp = S_getnetstack();

    temp->net = net;
    temp->next = *stack;
    *stack = temp;
}



/***********************************************************************
 *
 *  pop_net returns the pointer that was on top of stack and deletes it
 *  from the stack.  If the stack was empty, NULL is returned. The address
 *  of the NET_STACK must be passed, so that it can be updated.
 *
 *
 **********************************************************************/

NETPTR pop_net (stack)
NET_STACK *stack;		/* the stack being popped */
{
    NET_STACK temp;		/* keeps top of stack while stack is updated
				   */
    NETPTR net;

    if (*stack == (NET_STACK)NULL)
    	return ((NETPTR)NULL);
    else
    {
	temp = *stack;
	net = temp->net;
	*stack = temp->next;
	S_retnetstack( temp );
	return (net);
    }
}



/******************************************************************
 *
 *  insert_int inserts value at the proper location in the ordered
 *  list.  It is assumed that the list is sorted in increasing order.
 *
 *********************************************************************/

INT_LIST insert_int (old_list, value)
INT_LIST old_list;		/* the list being updated */
int value;			/* the number being inserted into the list */
{
    INT_LIST new;		/* new element being inserted into the list */
    INT_LIST temp, temp1;	/* used to find proper location for new */

    new = (INT_LIST) alloc (1, sizeof(INT_LIST_ELEMENT));

    new->value = value;

    if (old_list == (INT_LIST)NULL)
    {
	new->next = (INT_LIST)NULL;
	return (new);
    }
    else
    {
	temp = old_list;
	temp1 = (INT_LIST)NULL;
	while (temp->value < value)
	{
	    temp1 = temp;
	    temp = temp->next;
	    if (temp == (INT_LIST)NULL)
	    {
		temp1->next = new;
		new->next = (INT_LIST)NULL;
		return (old_list);
	    }
	}
	if (temp1 == (INT_LIST)NULL)
	{
	    new->next = old_list;
	    return (new);
	}
	else
	{
	    temp1->next = new;
	    new->next = temp;
	    return (old_list);
	}
    }
}


