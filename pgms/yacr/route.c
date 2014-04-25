#include "copyright.h"
#include "yacr.h"

/******************************************************************
 *
 *  draw_rect places the rectangles into the channel data structure.
 *  path is a linked list of rectangles.  Each rectangle is specified 
 *  to be on a layer and is oriented in a given direction.
 *
 *  Author: Jim Reed
 *
 *  Date: 5-8-84
 *
 ******************************************************************/

void draw_rect (channel, name, path)
INOUT CHANNELPTR channel;	/* where the rectangles get placed */
IN int name;			/* the name for the rectangles */
IN PATHPTR path;		/* description of the rectangles */
{
    int i;			/* loop counter */

    while (path != NULL)
    {
	if (path->orientation == HORIZ)
	    if (path->layer == HORIZ)
		for (i = path->num1; i <= path->num2; i++)
		    channel->horiz_layer[path->num3][i] = name;
	    else
		for (i = path->num1; i <= path->num2; i++)
		    channel->vert_layer[path->num3][i] = name;
	else
	    if (path->layer == HORIZ)
		for (i = path->num1; i <= path->num2; i++)
		    channel->horiz_layer[i][path->num3] = name;
	    else
		for (i = path->num1; i <= path->num2; i++)
		    channel->vert_layer[i][path->num3] = name;

	path = path->next;
    }
}



/*******************************************************************
 *
 *  intersect_path determines whether path1 intersects path2.
 *  If the paths intersect YES is returned, if the paths do not
 *  intersect, NO is returned.
 *
 *  Author: Jim Reed
 *
 *  Date: 5-13-84
 *
 ******************************************************************/

int intersect_path (path1, path2)
IN PATHPTR path1, path2;	/* the paths to be checked for intersection */
{
    PATHPTR trav1,		/* used to traverse path1 */
	    trav2;		/* used to traverse path2 */

    for (trav1 = path1; trav1 != NULL; trav1 = trav1->next)
	for (trav2 = path2; trav2!= NULL; trav2 = trav2->next)
	    if (trav1->layer == trav2->layer)
	    {
		if (trav1->orientation == trav2->orientation)
		{
		    if ((trav1->num2 >= trav2->num1) &&
			(trav1->num1 <= trav2->num2) &&
			(trav1->num3 == trav2->num3))
			return (YES);
		}
		else
		{
		    if ((trav1->num3 <= trav2->num2) &&
			(trav1->num3 >= trav2->num1))
			return (YES);
		}
	    }

    return (NO);
}

