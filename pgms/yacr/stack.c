#include "copyright.h"
#include "yacr.h"

/**********************************************************************
 *
 *  push_net inserts the given NETPTR on top of the given stack.  The
 *  address of the NET_STACK must be passed so that it can be updated.
 *
 *  Author: Jim Reed
 *
 *  Date: 3-19-84
 *
 **********************************************************************/

void push_net (stack, net)
INOUT NET_STACK *stack;		/* the stack getting pushed */
IN NETPTR net;			/* the net pointer getting inserted on the
				   stack */
{
    NET_STACK temp;	/* new element to be pushed on stack */

    temp = ALLOC(NET_STACK_ELEMENT, 1);
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
 *  Author: Jim Reed
 *
 *  Date: 3-19-84
 *
 **********************************************************************/

NETPTR pop_net (stack)
INOUT NET_STACK *stack;		/* the stack being popped */
{
    NET_STACK temp;		/* keeps top of stack while stack is updated
				   */

    if (*stack == NULL)
    	return (NULL);
    else
    {
	temp = *stack;
	*stack = temp->next;
	return (temp->net);
    }
}


/******************************************************************
 *
 *  insert_net inserts net at the end of the list old_list.
 *
 *  Author: Jim Reed
 *
 *  Date: 3-24-84 inserted net at head of list
 *  Modified: 9-12-84 insert net at end of list
 *
 *******************************************************************/

NET_LIST insert_net (old_list, net)
IN NET_LIST old_list;		/* the list that is being added to */
IN NETPTR net;			/* the element being added */
{
    NET_LIST new_list;		/* the first element in the new list */

    if (old_list == NULL)
	new_list = old_list = ALLOC(NET_LIST_ELEMENT, 1);
    else
    {
	new_list = old_list;
	while (old_list->next != NULL)
	    old_list = old_list->next;
	old_list->next = ALLOC(NET_LIST_ELEMENT, 1);
	old_list = old_list->next;
    }

    old_list->next = NULL;
    old_list->net = net;

    return (new_list);
}



/********************************************************
 *
 *  delete_net deletes the net from the list
 *  This assumes that net is in the list, if not it will bomb.
 *
 *  Author:  Jim Reed
 *
 *  Date: 9-12-84
 *
 *****************************************************************/

NET_LIST delete_net (old_list, net)
IN NET_LIST old_list;		/* the list containing net */
IN NETPTR net;			/* the net to be deleted */
{
    NET_LIST trav, old_trav;	/* used to traverse old_list and remember
				   where are in the list */

    if (old_list->net == net)
	return (old_list->next);

    for (old_trav = old_list, trav = old_list->next;
	 trav->net != net;
	 old_trav = trav, trav = trav->next);

    old_trav->next = trav->next;

    return (old_list);
}


/******************************************************************
 *
 *  insert_int inserts value at the proper location in the ordered
 *  list.  It is assumed that the list is sorted in increasing order.
 *
 *  Author: Jim Reed
 *
 *  Date: 4-20-84
 *  Modified: 4-23-84
 *
 *********************************************************************/

INT_LIST insert_int (old_list, value)
IN INT_LIST old_list;		/* the list being updated */
IN int value;			/* the number being inserted into the list */
{
    INT_LIST new;		/* new element being inserted into the list */
    INT_LIST temp, temp1;	/* used to find proper location for new */

    new = ALLOC(INT_LIST_ELEMENT, 1);

    new->value = value;

    if (old_list == NULL)
    {
	new->next = NULL;
	return (new);
    }
    else
    {
	temp = old_list;
	temp1 = NULL;
	while (temp->value < value)
	{
	    temp1 = temp;
	    temp = temp->next;
	    if (temp == NULL)
	    {
		temp1->next = new;
		new->next = NULL;
		return (old_list);
	    }
	}
	if (temp1 == NULL)
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



/**********************************************************************
 *
 *  push_int inserts the given int on top of the given stack.  The
 *  address of the INT_STACK must be passed so that it can be updated.
 *
 *  Author: Jim Reed
 *
 *  Date: 4-22-84
 *
 **********************************************************************/

void push_int (stack, value)
INOUT INT_STACK *stack;		/* the stack getting pushed */
IN int value;			/* the value getting inserted on the
				   stack */
{
    INT_STACK temp;	/* new element to be pushed on stack */

    temp = ALLOC(INT_STACK_ELEMENT, 1);
    temp->value = value;
    temp->next = *stack;
    *stack = temp;
}



/***********************************************************************
 *
 *  pop_int returns the value that was on top of stack and deletes it
 *  from the stack.  If the stack was empty, NULL is returned. The address
 *  of the INT_STACK must be passed, so that it can be updated.
 *
 *  Author: Jim Reed
 *
 *  Date: 4-22-84
 *
 **********************************************************************/

int pop_int (stack)
INOUT INT_STACK *stack;		/* the stack being popped */
{
    INT_STACK temp;		/* keeps top of stack while stack is updated
				   */

    if (*stack == NULL)
    	return (NULL);
    else
    {
	temp = *stack;
	*stack = temp->next;
	return (temp->value);
    }
}



/**********************************************************************
 *
 *  insert_path inserts a rectangle at the begining of the given path.
 *  A pointer to the new path is returned.
 *
 *  Author: Jim Reed
 *
 *  Date: 5-8-84
 *
 **********************************************************************/

PATHPTR insert_path (oldpath, layer, orientation, num1, num2, num3)
IN PATHPTR oldpath;		/* the path that is being added to */
IN int layer;			/* the layer of the new rectangle */
IN int orientation;		/* the orientation of the new rectangle */
IN int num1, num2, num3;	/* where the new rectangle belongs */
{
    PATHPTR newpath;		/* the new path */
    extern PATHPTR new_path();  /* beards - sept 87 - added for overflow prob */

    newpath = new_path();       /* beards - sept 87 - added */
    newpath->layer = layer;
    newpath->orientation = orientation;
    /* num1 should be less than num2 */
    if (num1 < num2)
    {
	newpath->num1 = num1;
	newpath->num2 = num2;
    }
    else
    {
	newpath->num2 = num1;
	newpath->num1 = num2;
    }
    newpath->num3 = num3;
    newpath->next = oldpath;

    return (newpath);
}



/**********************************************************************
 *
 *  push_path calculates the cost of the given path.  This cost is then
 *  used to decide where the path is to be placed in the list.
 *
 *  Author: Jim Reed
 *
 *  Date: 5-13-84
 *
 **********************************************************************/

PATH_LIST push_path (old_list, path)
IN PATH_LIST old_list;		/* the list we are adding to */
IN PATHPTR path;		/* the path being added to the list */
{
    PATH_LIST new_element;	/* new element inserted in the list */
    PATH_LIST trav, old_trav;	/* used to find the proper location in the
				   list */
    PATHPTR temp;		/* used to traverse the rectangles in path */

    /*
     * allocate space for new_element
     */

    new_element = ALLOC(PATH_LIST_ELEMENT, 1);
    new_element->path = path;

    /*
     *  calculate cost of path
     */

    new_element->cost = 0;
    for (temp = path; temp != NULL; temp = temp->next)
	new_element->cost += abs (temp->num1 - temp->num2);

    /*
     *  if old_list is empty the new_list is trivial
     */

    if (old_list == NULL)
    {
	new_element->next = NULL;
	return (new_element);
    }

    /*
     *  is new_element first in the list?
     */

    if (new_element->cost < old_list->cost)
    {
	new_element->next = old_list;
	return (new_element);
    }

    /*
     *  traverse the list for proper location
     */

    for (trav = old_list->next, old_trav = old_list;
	 trav != NULL;
	 old_trav = trav, trav = trav->next)
        if (trav->cost < new_element->cost)
	{
	    new_element->next = trav;
	    old_trav->next = new_element;
	    return (old_list);
	}
    new_element->next = trav;
    old_trav->next = new_element;
    return (old_list);
}



/**************************************************************
 *
 *  merge_path_lists merges the two PATH_LISTS and returns a pointer
 *  to the new list.
 *
 *  Author: Jim Reed
 *
 *  Date: 5-13-84
 *
 ***************************************************************/

PATH_LIST merge_path_lists (list1, list2)
IN PATH_LIST list1, list2;	/* the lists to be merged */
{
    PATH_LIST new_list,		/* the merged list */
	      end;		/* the end of the merged list */
    /*
     *  either list empty?
     */

    if (list1 == NULL)
	return (list2);
    if (list2 == NULL)
	return (list1);

    /*
     *  merge the lists
     */

    if (list1->cost < list2->cost)
    {
	new_list = list1;
	end = new_list;
	list1 = list1->next;
    }
    else
    {
	new_list = list2;
	end = new_list;
	list2 = list2->next;
    }
    while ((list1 != NULL) && (list2 != NULL))
	if (list1->cost < list2->cost)
	{
	    end->next = list1;
	    end = list1;
	    list1 = list1->next;
	}
	else
	{
	    end->next = list2;
	    end = list2;
	    list2 = list2->next;
	}
    if (list1 == NULL)
	end->next = list2;
    else
	end->next = list1;

    return (new_list);
}


/***********************************************************
 *
 *  density_insert appends the integer 'column' to the end of 
 *  the old_list.  It allocates space for the new list element.
 *
 *  Author: Jim Reed
 *
 *  Date: 10-3-84
 *
 ******************************************************/

DENSITY_LIST density_insert (old_list, column)
IN DENSITY_LIST old_list;	/* the list being appended */
IN int column;			/* the column number of the new element */
{
    DENSITY_LIST trav;		/* used to traverse old_list */
    DENSITY_LIST temp;		/* used to allocate new storage */

    temp = ALLOC(DENSITY_COLUMN, 1);
    temp->next = NULL;
    temp->column = column;
    temp->col_value = 0;

    if (old_list == NULL)
	return (temp);

    for (trav = old_list; trav->next != NULL; trav = trav->next);

    trav->next = temp;

    return (old_list);
}
