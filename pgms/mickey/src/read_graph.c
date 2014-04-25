#ifndef lint
static char SccsId[] = "@(#)read_graph.c	Yale Version 3.4 5/23/91";
#endif
/* -----------------------------------------------------------------

	FILE:		read_graph.c
	AUTHOR:		Dahe Chen
	DATE:		Wed Feb 22 12:58:04 EDT 1989
	CONTENTS:	read_graph()
	REVISION:
		Thu Nov 29 11:26:44 EST 1990
	    Rewrite the code reading data and add the code handling
	    errors.
		Wed Dec  5 14:11:20 EST 1990
	    Add width field to the earray.
		Fri Feb  8 14:32:55 EST 1991
	    Change the error messages to be more informative.
		Tue Mar  5 11:24:14 EST 1991
	    Change fclose to TWCLOSE.
		Thu May 23 18:36:40 EDT 1991
	    Add a new field "empty" to earray and set it to be TRUE
	    if the channel is adjacent to an empty room.

----------------------------------------------------------------- */

#include <yalecad/string.h>
#include <define.h>
#include <gg_router.h>
#include <macros.h>
#include <yalecad/file.h>

void
read_graph()
{
    char input[LRECL];
    char **tokens;
    INT numtokens;
    register int v1;
    register int v2;
    register int edge = 0;
    int lb_min_x = INT_MAX;
    int lb_min_y = INT_MAX;
    int rt_max_x = INT_MIN;
    int rt_max_y = INT_MIN;
    int HnotV;
    int state;

    EDGEPTR Pedge;
    LISTPTR Pnode;

    garray = (NODEPTR *) Ysafe_malloc((numnodes + 1) * sizeof(NODEPTR));
    for (v1 = 1; v1 <= numnodes; v1++)
    {
	garray[v1] = (NODEPTR) Ysafe_malloc(sizeof(NODE));
	garray[v1]->first = NIL(LIST);
	garray[v1]->tree = NIL(TREEPTR);
    }

    while (fgets(input, LRECL, fin))
    {
	tokens = Ystrparser(input, " :\n\t", &numtokens);
	if (strncmp(tokens[0], "node", 4) == STRINGEQ)
	{
	    v1 = atoi(tokens[1]);
	    garray[v1]->vertex = v1;
	    garray[v1]->xpos = atoi(tokens[3]);
	    garray[v1]->ypos = atoi(tokens[5]);
	}
	else if (strncmp(tokens[0], "adj", 3) == STRINGEQ)
	{
	    v2 = atoi(tokens[2]);
	    Pnode = (LISTPTR) Ysafe_malloc(sizeof(LIST));
	    Pnode->length = atoi(tokens[4]);
	    Pnode->f_vertex = v1;
	    Pnode->t_vertex = v2;
	    Pnode->next = garray[v1]->first;
	    garray[v1]->first = Pnode;
	}
	else
	{
	    ERROR2("\n\n%s.mrte:ERROR: ", cktName);
	    ERROR2("Unknown keyword %s.\n", tokens[0]);
	    exit(GP_FAIL);
	}
    }
    TWCLOSE(fin);

    /***********************************************************
    * Find the coordinates of the left-bottom corner and the
    * right-top corner.
    ***********************************************************/
    for (v1 = 1; v1 <= numnodes; v1++)
    {
	lb_min_x = MIN(lb_min_x, garray[v1]->xpos);
	lb_min_y = MIN(lb_min_y, garray[v1]->ypos);
	rt_max_x = MAX(rt_max_x, garray[v1]->xpos);
	rt_max_y = MAX(rt_max_y, garray[v1]->ypos);
    }

    fin = FOPEN("mgph","r");
    earray = (EDGEPTR *) Ysafe_malloc((numedges+1) * sizeof(EDGEPTR));
    while (fgets(input, LRECL, fin))
    {
	tokens = Ystrparser(input, " \n\t", &numtokens);
	if (strncmp(tokens[0], "edge", 4) == STRINGEQ)
	{
	    if (numtokens != 9)
	    {
		ERROR2("%s.mgph:ERROR: ", cktName);
		ERROR2("Incorrect number of fields: %d\n", numtokens);
		ERROR1("\tCorrect format:\n\t");
		ERROR1("edge INT INT length INT capacity INT width INT\n");
		exit(GP_FAIL);
	    }
	    earray[++edge] =
	    Pedge = (EDGEPTR) Ysafe_malloc(sizeof(EDGE));
	    Pedge->edge = edge;
	    Pedge->group = 0;
	    Pedge->length = atoi(tokens[4]);
	    Pedge->node[0] = v1 = atoi(tokens[1]);
	    Pedge->node[1] = v2 = atoi(tokens[2]);
	    Pedge->width = atoi(tokens[8]);
	    Pedge->numpins = 0;
	    Pedge->intree = 0;

	    if (Pedge->width <= 0)
	    {
		ERROR2("%s.mgph:ERROR: ", cktName);
		ERROR1("Channel width must greater than 0\n");
		exit(GP_FAIL);
	    }

	    Pnode = garray[v1]->first;
	    while (Pnode->t_vertex != v2)
	    {
		Pnode = Pnode->next;
	    }
	    Pnode->edge = edge;

	    Pnode = garray[v2]->first;
	    while (Pnode->t_vertex != v1)
	    {
		Pnode = Pnode->next;
	    }
	    Pnode->edge = edge;
	}
	else
	{
	    ERROR2("\n\n%s.mrte:ERROR: ", cktName);
	    ERROR2("Unknown keyword %s.\n", tokens[0]);
	    exit(GP_FAIL);
	}
    }
    TWCLOSE(fin);

    fin = FOPEN("mrte","r");
    while (fgets(input, LRECL, fin))
    {
	tokens = Ystrparser(input, " :\n\t", &numtokens);
	if (strncmp(tokens[0], "node", 4) == STRINGEQ)
	{
	    v1 = atoi(tokens[1]);
	}
	else if (strncmp(tokens[0], "adj", 3) == STRINGEQ)
	{
	    v2 = atoi(tokens[2]);

	    if (!atoi(tokens[18]))
	    {
		/***********************************************************
		* lb == 0. Check if the channel is on the boundary.
		***********************************************************/
		HnotV = atoi(tokens[16]);
		if (HnotV)
		{
		    if (garray[v1]->ypos != lb_min_y)
		    {
			state = FALSE;
		    }
		    else
		    {
		        state = TRUE;
		    }
		}
		else
		{
		    if (garray[v1]->xpos == lb_min_x)
		    {
		        state = FALSE;
		    }
		    else
		    {
		        state = TRUE;
		    }
		}
		Pnode = garray[v1]->first;
		while (Pnode->t_vertex != v2)
		{
		    Pnode = Pnode->next;
		}
		earray[Pnode->edge]->empty = state;
	    }
	    if (!atoi(tokens[20]))
	    {
		/***********************************************************
		* rt == 0. Check if the channel is on the boundary.
		***********************************************************/
		HnotV = atoi(tokens[16]);
		if (HnotV)
		{
		    if (garray[v1]->ypos != rt_max_y)
		    {
			state = FALSE;
		    }
		    else
		    {
		        state = TRUE;
		    }
		}
		else
		{
		    if (garray[v1]->xpos == rt_max_x)
		    {
		        state = FALSE;
		    }
		    else
		    {
		        state = TRUE;
		    }
		}
		Pnode = garray[v1]->first;
		while (Pnode->t_vertex != v2)
		{
		    Pnode = Pnode->next;
		}
		earray[Pnode->edge]->empty = state;
	    }
	}
    }
    TWCLOSE(fin);
    return;
} /* end of read_graph */
