#ifndef lint
static char SccsId[] = "@(#)assign_net.c	Yale Version 2.3 5/16/91";
#endif
/* -----------------------------------------------------------------

	FILE:		assign_net.c
	AUTHOR:		Dahe Chen
	DATE:		Sun Apr 23 23:20:04 EDT 1989
	CONTENTS:
	REVISION:
		Tue Nov 20 17:50:52 EST 1990
	    Modify the code to my new style and remove the function
	    assign_net_external.
		Wed Dec  5 14:24:19 EST 1990
	    Remove h_width and v_width.

----------------------------------------------------------------- */

#include <define.h>
#include <gg_router.h>
#include <dgraph.h>
#include <macros.h>

/*=====================================================================
*   This function makes an array for the netlist for quick access.
=====================================================================*/
void
assign_net_internal()
{

    int i;
    int j;
    int length;

    NETDRPTR Pnet;
    OFSETPTR Pedge;

    Pnet = netlist;

    narray = (NETDRPTR *) Ysafe_malloc((numnets+1) * sizeof(NETDRPTR));

    for (i = 1; i <= numnets; i++)
    {
	narray[i] = Pnet;
	length = Pnet->num_of_routes;

	for (j = 1; j <= length; j++)
	{
	    Pedge = Pnet->Aroute[j]->Pedge;
	    while (Pedge)
	    {
		Pedge->width = dearray[Pedge->edge]->width;
		Pedge = Pedge->next;
	    }
	}
	Pnet = Pnet->next;
    }

    return;

} /* end of assign_net */
