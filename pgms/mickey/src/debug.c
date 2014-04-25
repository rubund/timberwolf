#ifndef lint
static char SccsId[] = "@(#)debug.c	Yale Version 2.5 5/29/91";
#endif
/* -----------------------------------------------------------------

	FILE:		debug.c
	AUTHOR:		Dahe Chen
	DATE:		Sun Apr  23 15:17:05 PDT 1989
	CONTENTS:	Various debugging functions. To
			use the functions, in dbx, call
			a function name and pass necessary
			parameters if any.
	REVISION:
		Thu Nov  1 15:44:15 EST 1990
	    Add functions debugging analog part of the program.
		Wed Dec  5 14:02:15 EST 1990
	    Remove h_width and v_width.
		Mon Jan 28 18:18:25 EST 1991
	    Remove functions which are defined in the file checker.c
		Tue Mar  5 10:55:22 EST 1991
	    Change fopen and fclose to TWOPEN and TWCLOSE,
	    respectively.

----------------------------------------------------------------- */

#include <define.h>
#include <gg_router.h>
#include <macros.h>
#include <heap_func.h>
#include <steiner_tree.h>
#include <dgraph.h>
#include <analog.h>
#include <yalecad/file.h>

#define FFLUSH	(void)fflush

static	int	i		;
static	FILE	*fp		;

void functions()
{
    PRINT(stdout, "call dump_channel_graph()\n");
    PRINT(stdout, "call dump_pin_list()\n");
    PRINT(stdout, "call dump_segment_tree()\n");
    PRINT(stdout, "call print_empty_room_list()\n");
    PRINT(stdout, "call print_marray(number)\n");
    PRINT(stdout, "call print_nth_tree(tree)\n");
    PRINT(stdout, "call print_polar_graph()\n");
    PRINT(stdout, "call print_route(route)\n");
    PRINT(stdout, "call print_this_route(Pelist)\n");
}

void dump_channel_graph()
{
    LISTPTR Pnlist;

    fp = FOPEN("gdbg","w");
    for (i = 1; i <= numnodes; i++)
    {
	PRINT(fp, "node: %-3d\n", i);
	Pnlist = sarray[i]->first;
	while (Pnlist)
	{
	    PRINT(fp, "     adj_node: %3d --- edge: %3d\n",
		Pnlist->t_vertex, Pnlist->edge);
	    Pnlist = Pnlist->next;
	}
    }
    PRINT(fp, "\n\n");
    FFLUSH(fp);
    TWCLOSE(fp);
}

void print_polar_graph()
{
    DLISTPTR Pnlist;

    fp = FOPEN("gdbg","w");
    PRINT(fp, "HORIZONTAL POLAR GRAPH\n");

    for (i = 0; i < h_numnodes; i++)
    {
	PRINT(fp, "node: %-3d\n", i);
	Pnlist = h_narray[i]->Panode;
	while (Pnlist)
	{
	    PRINT(fp, "     adj_node: %3d --- edge: %3d\n",
		Pnlist->node, Pnlist->edge);
	    Pnlist = Pnlist->next;
	}
    }
    PRINT(fp, "\n\nVERTICAL POLAR GRAPH\n");

    for (i = 0; i < v_numnodes; i++)
    {
	PRINT(fp, "node: %-3d\n", i);
	Pnlist = v_narray[i]->Panode;
	while (Pnlist)
	{
	    PRINT(fp, "     adj_node: %3d --- edge: %3d\n",
		Pnlist->node, Pnlist->edge);
	    Pnlist = Pnlist->next;
	}
    }
    PRINT(fp, "\n\n");
    FFLUSH(fp);
    TWCLOSE(fp);
}

void dump_segment_tree()
{
    MDATAPTR Pnode;

    fp = FOPEN("gdbg","w");
    Pnode = Proot;
    while (Pnode)
    {
	PRINT(fp, "ORDER: %-3d PARENT: %-3d VERTEX: %-3d DIST: %-7d",
		 Pnode->order, Pnode->parent, Pnode->vertex, Pnode->dist);
	PRINT(fp, "EQUIV: %-1d LEAF %-1d ", Pnode->equiv, Pnode->leaf);
	if (Pnode->f_node)
	{
	    PRINT(fp, "F_NODE: %-3d\n", Pnode->f_node->vertex);
	}
	else
	{
	    PRINT(fp, "\n");
	}
	Pnode = Pnode->next;
	FFLUSH(fp);
    }
    TWCLOSE(fp);
}

void print_empty_room_list()
{
    int *Atrue;

    DEDGEPTR Phead;
    DEDGEPTR Ptail;

    fp = FOPEN("gdbg","w");
    Atrue = (int *)Ysafe_calloc(numedges+1, sizeof(int));
    for (i = 1; i <= numedges; i++)
    {
	if ((Phead=dearray[i])->Pnext && !Atrue[i])
	{
	    Ptail = Phead->Pnext;
	    while (Ptail != Phead)
	    {
		PRINT(fp, "EDGE: %-3d NEXT_EDGE: %-3d CAP: %-6d",
		    Ptail->edge, Ptail->Pnext->edge, Ptail->capacity);
		if (Ptail->Adens)
		{
		    PRINT(fp, " ADENS: %8x AINDEX: %8x STATUS: %-3d\n",
			Ptail->Adens, Ptail->Aindex, Ptail->status);
		}
		else
		{
		    PRINT(fp, " ADENS: %8x AINDEX: %8x STATUS: %-3d\n",
			Ptail->Adens, Ptail->Aindex, Ptail->status);
		}
		Atrue[Ptail->edge] = TRUE;
		Ptail = Ptail->Pnext;
	    }
	    PRINT(fp, "EDGE: %-3d NEXT_EDGE: %-3d CAP: %-6d",
		Ptail->edge, Ptail->Pnext->edge, Ptail->capacity);
	    if (Ptail->Adens)
	    {
		PRINT(fp, " ADENS: %8x AINDEX: %8x STATUS: %-3d\n",
		    Ptail->Adens, Ptail->Aindex, Ptail->status);
	    }
	    else
	    {
		PRINT(fp, " ADENS: %8x AINDEX: %8x STATUS: %-3d\n",
		    Ptail->Adens, Ptail->Aindex, Ptail->status);
	    }
	    Atrue[Ptail->edge] = TRUE;
	    PRINT(fp, "\n");
	}
    }
    TWCLOSE(fp);
    Ysafe_cfree((char *) Atrue);
}

void print_this_route(Pelist)
    OFSETPTR Pelist;
{
    OFSETPTR Pedge;

    fp = FOPEN("gdbg","w");
    Pedge = Pelist;
    while (Pedge)
    {
	PRINT(fp,
	    "EDGE: %-3d NODES: %-3d %-3d L_OFF: %-6d R_OFF: %-6d NET: %-3d\n",
	    Pedge->edge,
	    dearray[Pedge->edge]->f_vertex,
	    dearray[Pedge->edge]->t_vertex,
	    Pedge->l_off,
	    Pedge->r_off,
	    Pedge->net);
	Pedge = Pedge->next;
    }
    TWCLOSE(fp);
}

/* ==================================================================== */

void print_marray(number)
    int number;
{
    fp = FOPEN("gdbg","w");

    for (i = 1; i <= number; i++)
    {
	PRINT(fp, "EQUIV:%1d LEAF:%1d ORDER:%-3d PARENT:%-3d VERTEX:%-3d ",
	    marray[i]->equiv,
	    marray[i]->leaf,
	    marray[i]->order,
	    marray[i]->parent,
	    marray[i]->vertex);
	if (marray[i]->f_node)
	{
	    PRINT(fp, "STATUS:%-4d DIST:%-4d F_NODE:%d\n", marray[i]->status,
		marray[i]->dist,
		marray[i]->f_node->vertex);
	}
	else
	{
	    PRINT(fp, "STATUS:%-4d DIST:%-4d F_NODE:nil\n", marray[i]->status,
		marray[i]->dist);
	}
    }
    TWCLOSE(fp);
}

void print_nth_tree(tree)
    int tree;
{
    extern unsigned get_mask();
    char Aname[LRECL];
    int	length;
    unsigned mask;

    if (tree == 1)
    {
	mask = 1;
    }
    else
    {
	mask = get_mask(tree-1);
    }

    sprintf(Aname, "%s.%s.%d", cktName, netName, tree);
    if ((fp = TWOPEN(Aname, "w", ABORT)) == NIL(FILE))
    {
	PRINT(stderr, "Error while opeing file %s\n", Aname);
	exit(GP_FAIL);
    }

    for (length = 0, i = 1; i <= totedges; i++)
    {
	if (earray[i]->intree&mask)
	{
	    length += earray[i]->length;
	    PRINT(fp, "EDGE:%-3d NODE1:%-3d NODE2:%-d\n", i, earray[i]->node[0],
		    earray[i]->node[1]);
	}
    }
    PRINT(fp, "LENGTH:%d\n", length);
    TWCLOSE(fp);
}

/*=====================================================================
*   Print the list of channels in a given route for the current net.
=====================================================================*/
void print_route(route)
    int route;
{
    OFSETPTR Pelist;

    fp = FOPEN("gdbg","w");
    Pelist = netlist->Aroute[route]->Pedge;
    while (Pelist)
    {
	PRINT(fp, "EDGE:%-3d L_OFF:%-4d R_OFF:%-4d WIDTH:%d\n", Pelist->edge,
		Pelist->l_off,
		Pelist->r_off,
		Pelist->width);
	Pelist = Pelist->next;
    }
    TWCLOSE(fp);
}

/*=====================================================================
*   Print the pin list of a net.
=====================================================================*/
void dump_pin_list()
{
    fp = FOPEN("gdbg","w");
    for (i = 1; i <= numpins; i++)
    {
	PRINT(fp, "PIN: %-3d NODES: %-3d %-3d\n",
	    i, parray[i]->node[0], parray[i]->node[1]);
    }
    TWCLOSE(fp);
}
