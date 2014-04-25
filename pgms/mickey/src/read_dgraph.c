#ifndef lint
static char SccsId[] = "@(#)read_dgraph.c	Yale Version 2.4 5/16/91";
#endif
/* -----------------------------------------------------------------

	FILE:		read_dgraph.c
	AUTHOR:		Dahe Chen
	DATE:		Wed Jun 14 3:56:45 EDT 1989
	CONTENTS:	read_dgraph()
	REVISION:
		Tue Oct  9 18:44:17 EDT 1990
	    Add the code that will skip reading the polar graphs
	    if the second objective function is used. Instead it
	    reads all the necessary information for dearray from
	    earray and the file cktName.mgph.
		Wed Oct 10 18:00:26 EDT 1990
	    Add the initialization of edge index in dearray.
		Fri Oct 12 16:25:54 EDT 1990
	    Fix problems with the round-off of channel capacities.
		Thu Nov 29 18:41:10 EST 1990
	    Rewrtie the code reading data and add the code handling
	    errors.
		Wed Dec  5 13:00:09 EST 1990
	    Remove h_width and v_width. Instead, use the width
	    associated with each channel.
		Tue Feb  5 12:08:30 EST 1991
	    Reformat error message output.

----------------------------------------------------------------- */

#include <yalecad/string.h>
#include <define.h>
#include <gg_router.h>
#define DG_MAIN
#include <dgraph.h>
#undef DG_MAIN
#include <macros.h>

void
read_dgraph()
{

    char input[LRECL];
    char **tokens;
    INT numtokens;
    int i;
    int c;
    int s;
    int n1;
    int n2;
    int v1;
    int v2;
    int width;
    FILE *fgp;

    DEDGEPTR Pedge;
    DNODEPTR Pnode1;
    DLISTPTR Panode;
    LISTPTR  Pgnode;

    /***********************************************************
    * Allocate memory for the edge array of the directed graphs
    * and initialize it.
    ***********************************************************/
    dearray = (DEDGEPTR *) Ysafe_malloc((numedges+1) * sizeof(DEDGEPTR));
    dearray[0] = NIL(DEDGE);

    for (i = 1; i <= numedges; i++)
    {
	dearray[i] =
	Pedge = (DEDGEPTR) Ysafe_calloc(1, sizeof(DEDGE));
	Pedge->edge = i;
    }

    if (CASE == 1)
    {
	/***********************************************************
	* The first objective functions is used. Read in the
	* directed graph from file cktName.mhvg, where hvg stands
	* for Horizontal-Vertical-Graph.
	***********************************************************/
	fgp = FOPEN("mhvg","r");

	/***********************************************************
	* Horizontal direction. The first line in the file must give
	* the number of nodes and the number of edges in the
	* horizontal direction.
	***********************************************************/
	if (fgets(input, LRECL, fgp))
	{
	    tokens = Ystrparser(input, " :\n\t", &numtokens);
	    if (strncmp(tokens[0], "h_numnodes", 10) == STRINGEQ)
	    {
		h_numnodes = atoi(tokens[1]);
		if (strncmp(tokens[2], "h_numedges", 10) == STRINGEQ)
		{
		    h_numedges = atoi(tokens[3]);
		}
		else
		{
		    ERROR1("\n\n");
		    ERROR3("Unknown keyword \"%s\" in file %s.mhvg\n",
			tokens[2], cktName);
		    exit(GP_FAIL);
		}
	    }
	    else
	    {
		ERROR1("\n\n");
		ERROR3("Unknown keyword \"%s\" in file %s.mhvg\n",
		    tokens[2], cktName);
		exit(GP_FAIL);
	    }
	}

	/***********************************************************
	* Check the validality of the two parameters
	***********************************************************/
	if (h_numnodes <= 0 || h_numedges <= 0)
	{
	    ERROR2("\n\nError at line 1 of file %s\n", __FILE__);
	    exit(GP_FAIL);
	}

	/***********************************************************
	* Allocate memory and read in data.
	***********************************************************/
	h_narray = (DNODEPTR *) Ysafe_malloc(h_numnodes
					   * sizeof(DNODEPTR));

	for (i = 0; i < h_numnodes; i++)
	{
	    h_narray[i] = (DNODEPTR) Ysafe_malloc(sizeof(DNODE));
	    h_narray[i]->Panode = NIL(DLIST);
	}

	for (i = 0; i < h_numedges; i++)
	{
	    if (fgets(input, LRECL, fgp))
	    {
		tokens = Ystrparser(input, " \n\t", &numtokens);
		n1 = atoi(tokens[0]);
		n2 = atoi(tokens[1]);
		v1 = atoi(tokens[2]);
		v2 = atoi(tokens[3]);
		c  = atoi(tokens[4]);
		s  = atoi(tokens[5]);
		Pnode1 = h_narray[n1];
		Panode = (DLISTPTR) Ysafe_malloc(sizeof(DLIST));
		Panode->node = n2;
		Panode->next = Pnode1->Panode;
		Pnode1->Panode = Panode;
		Pgnode = garray[v1]->first;

		while (Pgnode && Pgnode->t_vertex != v2)
		{
		    Pgnode = Pgnode->next;
		}

		Pedge = dearray[Pgnode->edge];
		Pedge->capacity = c;
		Pedge->direct = H;
		Pedge->f_node = n1;
		Pedge->t_node = n2;
		Pedge->f_vertex = v1;
		Pedge->t_vertex = v2;
		Pedge->csize = s;
		Pedge->f_xpos = garray[v1]->xpos;
		Pedge->f_ypos = garray[v1]->ypos;
		Pedge->t_xpos = garray[v2]->xpos;
		Pedge->t_ypos = garray[v2]->ypos;
		Pedge->length = Pedge->t_ypos - Pedge->f_ypos;
		Panode->edge = Pgnode->edge;
	    }
	    else
	    {
		ERROR2("\n\nError detected while reading %s\n", __FILE__);
		exit(GP_FAIL);
	    }
	}

	/***********************************************************
	* Vertical direction. The first line in the file must give
	* the number of nodes and the number of edges in the
	* vertical direction.
	***********************************************************/
	if (fgets(input, LRECL, fgp))
	{
	    tokens = Ystrparser(input, " :\n\t", &numtokens);
	    if (strncmp(tokens[0], "v_numnodes", 10) == STRINGEQ)
	    {
		v_numnodes = atoi(tokens[1]);
		if (strncmp(tokens[2], "v_numedges", 10) == STRINGEQ)
		{
		    v_numedges = atoi(tokens[3]);
		}
		else
		{
		    ERROR1("\n\n");
		    ERROR3("Unknown keyword \"%s\" in file %s.mhvg\n",
			tokens[2], cktName);
		    exit(GP_FAIL);
		}
	    }
	    else
	    {
		ERROR1("\n\n");
		ERROR3("Unknown keyword \"%s\" in file %s.mhvg\n",
		    tokens[2], cktName);
		exit(GP_FAIL);
	    }
	}

	/***********************************************************
	* Check the validality of the two parameters
	***********************************************************/
	if (v_numnodes <= 0 || v_numedges <= 0) 
	{
	    ERROR1("\n\n");
	    ERROR3("Error at line %d of file %s\n", __FILE__, __LINE__);
	    exit(GP_FAIL);
	}

	if (h_numnodes != v_numnodes)
	{
	    /***********************************************************
	    * The number of nodes in h_polar graph does not match the
	    * number of nodes in v_polar graph. Placement is probably
	    * invalid.
	    ***********************************************************/
	    ERROR1("\n\n");
	    ERROR1("The number of nodes in two polar graphs does not \n");
	    ERROR1("match.\nThe given graphs are not valid.\n");
	    exit(GP_FAIL);
	}

	/***********************************************************
	* Allocate memory and read in data.
	***********************************************************/
	v_narray = (DNODEPTR *) Ysafe_malloc(v_numnodes
					   * sizeof(DNODEPTR));

	for (i = 0; i < v_numnodes; i++)
	{
	    v_narray[i] = (DNODEPTR) Ysafe_malloc(sizeof(DNODE));
	    v_narray[i]->Panode = NIL(DLIST);
	}

	for (i = 0; i < v_numedges; i++)
	{
	    if (fgets(input, LRECL, fgp))
	    {
		tokens = Ystrparser(input, " \n\t", &numtokens);
		n1 = atoi(tokens[0]);
		n2 = atoi(tokens[1]);
		v1 = atoi(tokens[2]);
		v2 = atoi(tokens[3]);
		c  = atoi(tokens[4]);
		s  = atoi(tokens[5]);
		Pnode1 = v_narray[n1];
		Panode = (DLISTPTR) Ysafe_malloc(sizeof(DLIST));
		Panode->node = n2;
		Panode->next = Pnode1->Panode;
		Pnode1->Panode = Panode;
		Pgnode = garray[v1]->first;

		while (Pgnode && Pgnode->t_vertex != v2)
		{
		    Pgnode = Pgnode->next;
		}

		Pedge = dearray[Pgnode->edge];
		Pedge->capacity = c;
		Pedge->direct = V;
		Pedge->f_node = n1;
		Pedge->t_node = n2;
		Pedge->f_vertex = v1;
		Pedge->t_vertex = v2;
		Pedge->csize = s;
		Pedge->f_xpos = garray[v1]->xpos;
		Pedge->f_ypos = garray[v1]->ypos;
		Pedge->t_xpos = garray[v2]->xpos;
		Pedge->t_ypos = garray[v2]->ypos;
		Pedge->length = Pedge->t_xpos - Pedge->f_xpos;
		Panode->edge = Pgnode->edge;
	    }
	    else
	    {
		ERROR2("\n\nError detected while reading %s\n", __FILE__);
		exit(GP_FAIL);
	    }
	}
    }
    else
    {
	/***********************************************************
	* The second objective functio is used. The polar graphs are
	* not used in this case so skip the rest of the function.
	***********************************************************/
	for (i = 1; i <= numedges; i++)
	{
	    Pedge = dearray[i];
	    v1 = earray[i]->node[0];
	    v2 = earray[i]->node[1];
	    if (garray[v1]->xpos == garray[v2]->xpos)
	    {
		Pedge->direct = H;
	    }
	    else
	    {
		Pedge->direct = V;
	    }
	    Pedge->f_vertex = v1;
	    Pedge->t_vertex = v2;
	    Pedge->f_xpos = garray[v1]->xpos;
	    Pedge->f_ypos = garray[v1]->ypos;
	    Pedge->t_xpos = garray[v2]->xpos;
	    Pedge->t_ypos = garray[v2]->ypos;
	    Pedge->length = earray[i]->length;
	}

	/***********************************************************
	* Read the channel capacity from the file cktName.mgph.
	***********************************************************/
	fgp = FOPEN("mgph","r");
	while (fgets(input, LRECL, fgp))
	{
	    tokens = Ystrparser(input, " \n\t", &numtokens);
	    v1 = atoi(tokens[1]);
	    v2 = atoi(tokens[2]);
	    s  = atoi(tokens[4]);
	    c  = atoi(tokens[6]);

	    Pgnode = garray[v1]->first;
	    while (Pgnode->t_vertex != v2)
	    {
		Pgnode = Pgnode->next;
	    }
	    Pedge = dearray[Pgnode->edge];
	    Pedge->capacity = c;
	}
    }

    /***********************************************************
    * Truncate the capacity to the multiple of the minimum width
    * in a channel if necessary and assign the minimum width.
    ***********************************************************/
    for (i = 1; i <= numedges; i++)
    {
	width =
	(Pedge = dearray[i])->width = earray[i]->width;
	if (Pedge->capacity > 0)
	{
	    Pedge->capacity /= width;
	    Pedge->capacity *= width;
	}
    }

    return;

} /* end of read_dgraph */
