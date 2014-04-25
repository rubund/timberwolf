#ifndef lint
static char SccsId[] = "@(#)read_pin_list.c	Yale Version 2.3 5/16/91";
#endif
/* -----------------------------------------------------------------

	FILE:		read_pin_list.c
	AUTHOR:		Dahe Chen
	DATE:		Tue Aug  1 14:30:37 EDT 1989
	CONTENTS:	read_pin_list()
			numcmp()
	REVISION:
		Thu Oct  4 20:46:50 EDT 1990
	    Change quicksort to Yquicksort.
		Thu Oct 11 11:49:30 EDT 1990
	    Add the parameter do_debug for the conditional debug.
		Fri Jan 25 17:07:29 EST 1991
	    Change malloc to calloc so that guarantee
	    initialization. Add analog net to the test in the loop
	    decreasing the net index.
		Sun Jan 27 14:31:25 EST 1991
	    The index j is not increased when assing pins to the
	    array Adens.
		Tue Mar  5 11:25:44 EST 1991
	    Change fclose to TWCLOSE.

----------------------------------------------------------------- */

#include <define.h>
#include <gg_router.h>
#include <dgraph.h>
#include <macros.h>
#include <yalecad/string.h>
#include <yalecad/file.h>

typedef struct link_list {
    int net;
    int node;
    int dist;
    struct link_list *next;
} DLLIST,
*DLLISTPTR;

typedef struct pin_list {
    int number;
    struct link_list *Phead;
} PINLIST,
*PINLISTPTR;

void
read_pin_list()
{

    char input[LRECL];
    char **tokens;
    INT numtokens;
    int i;
    int j;
    int v1;
    int v2;
    int net;
    int dist;
    int length;
    int number;
    int numcmp();
    FILE *fp;

    DENSPTR *Adens;
    DLLISTPTR Pnew;
    DLLISTPTR *Alist;
    LISTPTR Pnode;
    PINLISTPTR *Apin;

    Apin = (PINLISTPTR *) Ysafe_calloc((numedges+1), sizeof(PINLISTPTR));

    for (i = 1; i <= numedges; i++)
    {
	Apin[i] = (PINLISTPTR) Ysafe_calloc(1, sizeof(PINLIST));
    }

    net = numnets + 1;
    length = 0;
    fp = FOPEN("mtwf","r");

    while (fgets(input, LRECL, fp))
    {
	tokens = Ystrparser(input, " \n\t", &numtokens);
	if (!numtokens)
	{
	    continue;
	}
	if (strncmp(tokens[0], "net", 3) == STRINGEQ
	 || strncmp(tokens[0], "analog_net", 10) == STRINGEQ)
	{
	    net--;
	}

	if (strncmp(tokens[0], "pin", 3) == STRINGEQ
	 || strncmp(tokens[0], "equiv", 5) == STRINGEQ)
	{
	    /***********************************************************
	    * A pin or an equivalent pin is read in. Find the channel
	    * this pin locates and insert it into the pin list of the
	    * channel.
	    ***********************************************************/
	    v1 = atoi(tokens[5]);
	    v2 = atoi(tokens[6]);
	    dist = atoi(tokens[8]);

	    Pnode = sarray[v1]->first;
	    while (Pnode->t_vertex != v2)
	    {
		Pnode = Pnode->next;
	    }

	    number = Pnode->edge;
	    Pnew = (DLLISTPTR) Ysafe_calloc(1, sizeof(DLLIST));
	    Pnew->net = net;
	    Pnew->dist = dist;
	    Pnew->next = Apin[number]->Phead;
	    Apin[number]->Phead = Pnew;
	    Apin[number]->number++;

	    /***********************************************************
	    * Store the from_node in the field node of Pnew.
	    ***********************************************************/
	    if (dearray[number]->f_vertex == v1)
	    {
		Pnew->node = v1;
	    }
	    else
	    {
		Pnew->node = v2;
	    }
	    length = MAX(length, Apin[number]->number);
	}
    }
    TWCLOSE(fp);

    Alist = (DLLISTPTR *) Ysafe_calloc(length, sizeof(DLLISTPTR));
    for (i = 0; i < length; i++)
    {
	Alist[i] = (DLLISTPTR) Ysafe_calloc(1, sizeof(DLLIST));
    }

    for (i = 1; i <= numedges; i++)
    {
	/***********************************************************
	* Sort all pins according to their positions in a channel
	***********************************************************/
	number = Apin[i]->number;
	Pnew = Apin[i]->Phead;
	if (!Pnew)
	{
	    /***********************************************************
	    * There are no pins on this channel. Skip it and go to the
	    * next channel.
	    ***********************************************************/
	    continue;
	}
	for (j = 0; j < number; j++)
	{
	    Alist[j] = Pnew;
	    Pnew = Pnew->next;
	}

	Yquicksort((char *) Alist, number, sizeof(DLLISTPTR), numcmp);

	/***********************************************************
	* Scan through the sorted list and remove any pins which
	* locate at the same position as some other pins. The
	* resulted non-duplicated list is represented by the linked
	* list.
	***********************************************************/
	Alist[number-1]->next = NIL(DLLIST);
	Pnew = Alist[0];
	for (j = 1; j < number; j++)
	{
	    if (Pnew->dist != Alist[j]->dist)
	    {
		Pnew->next = Alist[j];
		Pnew = Pnew->next;
	    }
	    else
	    {
		Apin[i]->number--;
		Pnew->next = NIL(DLLIST);
	    }
	}
	/*
	#ifdef DEBUG
	if (do_debug)
	{
	    for (j = 1; j < number; j++)
	    {
		if (Alist[j-1]->node != Alist[j]->node)
		{
		    fprintf(stderr, "Error in Alist at %d\n", j);
		}
	    }
	}
	#endif DEBUG
	*/

	if (Alist[0]->dist > 0 &&
	     Alist[number-1]->dist < dearray[i]->length)
	{
	    /***********************************************************
	    * No pins locate at the end points. The number of points for
	    * local densities is the number of pins plus two end points.
	    ***********************************************************/
	    number = dearray[i]->numpin = Apin[i]->number + 2;
	    dearray[i]->Adens =
	    Adens = (DENSPTR *) Ysafe_calloc(number, sizeof(DENSPTR));
	    Adens[0] = (DENSPTR) Ysafe_calloc(1, sizeof(DENS));
	    Adens[number-1] = (DENSPTR) Ysafe_calloc(1, sizeof(DENS));
	    Adens[number-1]->distance = dearray[i]->length;
	    j = 1;
	    Pnew = Alist[0];
	}
	else if (Alist[0]->dist == 0 &&
		  Alist[number-1]->dist == dearray[i]->length)
	{
	    /***********************************************************
	    * Pins locate at the both end points. The number of points
	    * for local densities is the same as the number of pins on
	    * this channel.
	    ***********************************************************/
	    number = dearray[i]->numpin = Apin[i]->number;
	    dearray[i]->Adens =
	    Adens = (DENSPTR *) Ysafe_calloc(number, sizeof(DENSPTR));
	    j = 0;
	    Pnew = Alist[0];
	}
	else
	{
	    /***********************************************************
	    * A pin locates at one of the two end points. The number of
	    * points for local densities is the number of pins plus one.
	    ***********************************************************/
	    number = dearray[i]->numpin = Apin[i]->number + 1;
	    dearray[i]->Adens =
	    Adens = (DENSPTR *) Ysafe_calloc(number, sizeof(DENSPTR));
	    if (Alist[0]->dist == 0)
	    {
		/*********************************************************
		* A pin locates at the from end point.
		*********************************************************/
		Adens[number-1] = (DENSPTR) Ysafe_calloc(1, sizeof(DENS));
		Adens[number-1]->distance = dearray[i]->length;
		j = 0;
	    }
	    else
	    {
		Adens[0] = (DENSPTR) Ysafe_calloc(1, sizeof(DENS));
		j = 1;
	    }
	    Pnew = Alist[0];
	}

	while (Pnew)
	{
	    Adens[j] = (DENSPTR) Ysafe_calloc(1, sizeof(DENS));
	    Adens[j]->net[0] = Pnew->net;
	    Adens[j]->density = 0;
	    Adens[j]->distance = Pnew->dist;
	    Adens[j++]->channel[0] = i;
	    Pnew = Pnew->next;
	}
	Ysafe_cfree((char *) Apin[i]);
    }

    for (j = 0; j < length; j++)
    {
	Ysafe_cfree((char *) Alist[j]);
    }
    Ysafe_cfree((char *) Alist);
    Ysafe_cfree((char *) Apin);

} /* end of read_pin_list */

/* ==================================================================== */

int
numcmp(item1, item2)
    DLLISTPTR *item1;
    DLLISTPTR *item2;
{

    return((*item1)->dist - (*item2)->dist);

} /* end of numcmp */
