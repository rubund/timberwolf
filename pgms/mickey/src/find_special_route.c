/***********************************************************
static char SccsId[] = "@(#)find_special_route.c	Yale Version 1.3 5/29/91" ;
***********************************************************/
/* -----------------------------------------------------------------

	FILE:		find_special_route.c
	AUTHOR:		Dahe Chen
	DATE:		Sat May  4 14:26:31 EDT 1991
	DESCRIPTION:	For a given route, check if it occupies
		channels which are adjacent to a same group of empty
		rooms multiple times. If so, revise the route.
	REVISION:

----------------------------------------------------------------- */

#include <define.h>
#include <macros.h>
#include <gg_router.h>
#include <dgraph.h>
#include <yalecad/file.h>
#include <yalecad/string.h>

#define ABOVE	1
#define BELOW	0
#define LEFT	-1
#define RIGHT	1

typedef struct _chlist {
    int count;
    INT chan[2];
    int l_node[2];
    int r_node[2];
    DEDGEPTR Pedge;
    struct _chlist *next;
} CHLIST,
*CHLISTPTR;

static int		netS;
static CHLISTPTR	Pchlist;

/*=====================================================================
*   Go through the channels in the list of the route and mark them with
* the net index in field status.
=====================================================================*/
static void mark_channels(net, Pelist)
    int net;
    OFSETPTR Pelist;
{
    OFSETPTR ptr = Pelist;

    while (ptr)
    {
        dearray[ptr->edge]->status = net;
	ptr = ptr->next;
    }
}

/*=====================================================================
*   Go through the channels in the list of the route again and find the
* sets of channels in which the route is.
=====================================================================*/
static void find_parallel_sets(net, Pelist)
    int net;
    OFSETPTR Pelist;
{
    CHLISTPTR Pnew;
    DEDGEPTR Pchan;
    OFSETPTR ptr = Pelist;
    Pchlist = NIL(CHLIST);

    while (ptr)
    {
	Pchan = dearray[ptr->edge];

        if (Pchan->status == net && Pchan->Pnext)
	{
	    /***********************************************************
	    * The channel is in the route and is adjacent to an empty
	    * room. Mark its status with negative net value and scan
	    * through the cyclic linked list of the channels.
	    ***********************************************************/
	    Pchan->status = -net;

	    {
		int count = 1;
		DEDGEPTR Pedge = Pchan->Pnext;

		while (Pedge != Pchan)
		{
		    if (Pedge->status == net)
		    {
			count++;
			Pedge->status = -net;
		    }
		    Pedge = Pedge->Pnext;
		}
		if (count == 2)
		{
		    Pnew = (CHLISTPTR)Ysafe_malloc(sizeof(CHLIST));
		    Pnew->count = count;
		    Pnew->l_node[0] =
		    Pnew->l_node[1] =
		    Pnew->r_node[0] =
		    Pnew->r_node[1] = -1;
		    Pnew->chan[0] =
		    Pnew->chan[1] = 0;
		    Pnew->Pedge = Pchan;
		    Pnew->next = Pchlist;
		    Pchlist = Pnew;
		}
	    }
	}
	ptr = ptr->next;
    }
}

/*=====================================================================
*   Go through the linked list of edges of the route and find the two
* edges which occupy the channels.
=====================================================================*/
static void find_the_pointers(Plist, Pedge, Pelist)
    CHLISTPTR Plist;
    DEDGEPTR Pedge;
    OFSETPTR Pelist;
{
    int e = 0;
    DEDGEPTR Pcptr = Pedge;
    OFSETPTR Peptr;

    do
    {
	Peptr = Pelist;

	while (Peptr)
	{
	    if (Peptr->edge == Pcptr->edge)
	    {
	        break;
	    }
	    Peptr = Peptr->next;
	}
	if (Peptr)
	{
	    Plist->chan[e++] = (INT)Peptr;
	}
	if (e == 2)
	{
	    break;
	}
	Pcptr = Pcptr->Pnext;
    } while (Pcptr != Pedge);
}

/*=====================================================================
*   Return TRUE if the edge Pnode->edge is in the route and return
* FALSE if not.
=====================================================================*/
static int intree_edge(net, Pnode)
    int net;
    LISTPTR Pnode;
{
    OFSETPTR Pelist = narray[net]->Aroute[narray[net]->route]->Pedge;

    while (Pelist)
    {
        if (Pelist->edge == Pnode->edge)
	{
	    break;
	}
	Pelist = Pelist->next;
    }
    if (Pelist)
    {
        return(TRUE);
    }
    else
    {
        return(FALSE);
    }
}

/*=====================================================================
*   Check the given vertex with respect to the routing configuration.
* returns TRUE if the route only takes searching and affecting channels
=====================================================================*/
static int check_the_corner_node(node, direct, location, net)
    int node;
    int direct;
    int location;
    int net;
{
    int degree = 0;
    int affect = FALSE;
    int position;
    LISTPTR Pnode = garray[node]->first;

    if (direct == H)
    {
	position = garray[node]->ypos;

	if (location == BELOW)
	{
	    while (Pnode)
	    {
		if (intree_edge(net, Pnode) != FALSE)
		{
		    degree++;
		    if (garray[Pnode->t_vertex]->ypos > position)
		    {
			affect = TRUE;
		    }
		}
		Pnode = Pnode->next;
	    }
	}
	else
	{
	    while (Pnode)
	    {
		if (intree_edge(net, Pnode) != FALSE)
		{
		    degree++;
		    if (garray[Pnode->t_vertex]->ypos < position)
		    {
			affect = TRUE;
		    }
		}
		Pnode = Pnode->next;
	    }
	}
    }
    else
    {
	position = garray[node]->xpos;

	if (location == BELOW)
	{
	    while (Pnode)
	    {
		if (intree_edge(net, Pnode) != FALSE)
		{
		    degree++;
		    if (garray[Pnode->t_vertex]->xpos > position)
		    {
			affect = TRUE;
		    }
		}
		Pnode = Pnode->next;
	    }
	}
	else
	{
	    while (Pnode)
	    {
		if (intree_edge(net, Pnode) != FALSE)
		{
		    degree++;
		    if (garray[Pnode->t_vertex]->xpos < position)
		    {
			affect = TRUE;
		    }
		}
		Pnode = Pnode->next;
	    }
	}
    }
    if (affect != FALSE)
    {
	if (degree > 2)
	{
	    return(FALSE);
	}
	else
	{
	    return(TRUE);
	}
    }
    else
    {
	if (degree > 1)
	{
	    return(FALSE);
	}
	else
	{
	    return(TRUE);
	}
    }
}

/*=====================================================================
*   Find the the configuration of the channels with respect to the
* route.
=====================================================================*/
static void find_the_config(net, Plist)
    int net;
    CHLISTPTR Plist;
{
    int i;
    int direct;
    int location;

    OFSETPTR ptr1, ptr2;

    for (i = 0; i < 2; i++)
    {
        ptr1 = (OFSETPTR)Plist->chan[i];
	ptr2 = (OFSETPTR)Plist->chan[(i + 1) % 2];

	if (dearray[ptr1->edge]->f_xpos == dearray[ptr1->edge]->t_xpos)
	{
	    /***********************************************************
	    * The channel is vertical.
	    ***********************************************************/
	    direct = V;

	    if (dearray[ptr1->edge]->f_xpos > dearray[ptr2->edge]->f_xpos)
	    {
	        location = ABOVE;
	    }
	    else
	    {
	        location = BELOW;
	    }
	}
	else
	{
	    /***********************************************************
	    * The channel is horizontal.
	    ***********************************************************/
	    direct = H;

	    if (dearray[ptr1->edge]->f_ypos > dearray[ptr2->edge]->f_ypos)
	    {
	        location = ABOVE;
	    }
	    else
	    {
	        location = BELOW;
	    }
	}
	if (!ptr1->l_off)
	{
	    Plist->l_node[i] =
		check_the_corner_node(dearray[ptr1->edge]->f_vertex,
				      direct,
				      location,
				      net);
	}
	else
	{
	    Plist->l_node[i] = TRUE;
	}
	if (!ptr1->r_off)
	{
	    Plist->r_node[i] =
		check_the_corner_node(dearray[ptr1->edge]->t_vertex,
				      direct,
				      location,
				      net);
	}
	else
	{
	    Plist->r_node[i] = TRUE;
	}
    }
}

/*=====================================================================
*   According to the types of the corner nodes, determine if the route
* is special and if it is needed to treat specially.
=====================================================================*/
static void determine_the_route(net, Plist)
    int net;
    CHLISTPTR Plist;
{
    int l_dist[2];
    int r_dist[2];

    DENSPTR *Adens;

    /***********************************************************
    * First of all, find the left-most and right-most end for
    * the channels if the channels have pins of the net.
    ***********************************************************/
    l_dist[0] = l_dist[1] = INT_MAX;
    r_dist[0] = r_dist[1] = INT_MIN;
    Adens = Plist->Pedge->Adens;

    if (Adens)
    {
	int i;
	int j;
	INT e;
	int p = Plist->Pedge->numpin;

	for (j = 0; j < 2; j++)
	{
	    e = ((OFSETPTR)Plist->chan[j])->edge;
	    for (i = 0; i < p; i++)
	    {
		if ((Adens[i]->net[0] == net || Adens[i]->net[1] == net)
		 && (Adens[i]->channel[0] == e || Adens[i]->channel[1] == e))
		{
		    l_dist[j] = MIN(l_dist[j], Adens[i]->distance);
		    r_dist[j] = MAX(r_dist[j], Adens[i]->distance);
		}
	    }
	    if (l_dist[j] == INT_MAX)
	    {
	        l_dist[j] = INT_MIN;
	        r_dist[j] = INT_MAX;
	    }
	}
    }

    if (l_dist[0] != INT_MIN && l_dist[1] == INT_MIN)
    {
	OFSETPTR Pelist0 = (OFSETPTR)Plist->chan[0];
	OFSETPTR Pelist1 = (OFSETPTR)Plist->chan[1];

	if (!Pelist0->l_off && Pelist0->r_off && Plist->l_node[0] == TRUE)
	{
	    Pelist0->back = (int *)Ysafe_malloc(2 * sizeof(int));
	    Pelist0->back[0] = Pelist0->l_off;
	    Pelist0->back[1] = Pelist0->r_off;
	    Pelist1->back = (int *)Ysafe_malloc(2 * sizeof(int));
	    Pelist1->back[0] = Pelist1->l_off;
	    Pelist1->back[1] = Pelist1->r_off;
	    Pelist1->l_off = INT_MIN;
	    Pelist1->r_off = INT_MAX;
	    if (l_dist[0] == r_dist[0])
	    {
		Pelist0->l_off = INT_MIN;
		Pelist0->r_off = INT_MAX;
	    }
	    else
	    {
	        Pelist0->l_off = l_dist[0];
	    }
	}
	if (Pelist0->l_off && !Pelist0->r_off && Plist->r_node[0] == TRUE)
	{
	    Pelist0->back = (int *)Ysafe_malloc(2 * sizeof(int));
	    Pelist0->back[0] = Pelist0->l_off;
	    Pelist0->back[1] = Pelist0->r_off;
	    Pelist1->back = (int *)Ysafe_malloc(2 * sizeof(int));
	    Pelist1->back[0] = Pelist1->l_off;
	    Pelist1->back[1] = Pelist1->r_off;
	    Pelist1->l_off = INT_MIN;
	    Pelist1->r_off = INT_MAX;
	    if (l_dist[0] == r_dist[0])
	    {
		Pelist0->l_off = INT_MIN;
		Pelist0->r_off = INT_MAX;
	    }
	    else
	    {
	        Pelist0->r_off = dearray[Pelist0->edge]->length - r_dist[0];
	    }
	}
    }
    if (l_dist[0] == INT_MIN && l_dist[1] != INT_MIN)
    {
	OFSETPTR Pelist0 = (OFSETPTR)Plist->chan[0];
	OFSETPTR Pelist1 = (OFSETPTR)Plist->chan[1];

	if (!Pelist1->l_off && Pelist1->r_off && Plist->l_node[1] == TRUE)
	{
	    Pelist0->back = (int *)Ysafe_malloc(2 * sizeof(int));
	    Pelist0->back[0] = Pelist0->l_off;
	    Pelist0->back[1] = Pelist0->r_off;
	    Pelist0->l_off = INT_MIN;
	    Pelist0->r_off = INT_MAX;
	    Pelist1->back = (int *)Ysafe_malloc(2 * sizeof(int));
	    Pelist1->back[0] = Pelist1->l_off;
	    Pelist1->back[1] = Pelist1->r_off;
	    if (l_dist[1] == r_dist[1])
	    {
		Pelist1->l_off = INT_MIN;
		Pelist1->r_off = INT_MAX;
	    }
	    else
	    {
	        Pelist1->l_off = l_dist[1];
	    }
	}
	if (Pelist1->l_off && !Pelist1->r_off && Plist->r_node[1] == TRUE)
	{
	    Pelist0->back = (int *)Ysafe_malloc(2 * sizeof(int));
	    Pelist0->back[0] = Pelist0->l_off;
	    Pelist0->back[1] = Pelist0->r_off;
	    Pelist0->l_off = INT_MIN;
	    Pelist0->r_off = INT_MAX;
	    Pelist1->back = (int *)Ysafe_malloc(2 * sizeof(int));
	    Pelist1->back[0] = Pelist1->l_off;
	    Pelist1->back[1] = Pelist1->r_off;
	    if (l_dist[1] == r_dist[1])
	    {
		Pelist1->l_off = INT_MIN;
		Pelist1->r_off = INT_MAX;
	    }
	    else
	    {
	        Pelist1->r_off = dearray[Pelist1->edge]->length - r_dist[1];
	    }
	}
    }
}

/*=====================================================================
*   Free memory of the parallel sets.
=====================================================================*/
static void free_parallel_sets()
{
    CHLISTPTR ptr = Pchlist;

    while (ptr)
    {
	Pchlist = ptr;
        ptr = ptr->next;
	Ysafe_free((char *)Pchlist);
    }
}

/*=====================================================================
*   Main function for finding special routes.
=====================================================================*/
static void find_special_route(net, Pelist)
    int net;
    OFSETPTR Pelist;
{
    CHLISTPTR Plist;

    netS = net;
    Pchlist = NIL(CHLIST);

    /***********************************************************
    * Mark all the channels, which are in the given route, with
    * net in the status field.
    ***********************************************************/
    mark_channels(net, Pelist);

    /***********************************************************
    * Scan through the channels, which are in the given route,
    * again and find the channels which are adjacent to empty
    * rooms (of course, they are in the route). Furthermore,
    * mark only these channels which are parallel and are in
    * the route TWO times.
    * If you find a route which goes three or more times,
    * congradulations that you have found something I don't have
    * an easy way to solve. Plus I don't considering this case
    * makes much difference if you look at the caes more
    * carefully. You probably find these channels are very
    * short and represent a huge channel in which over-estimate
    * wont cause any trouble.
    ***********************************************************/
    find_parallel_sets(net, Pelist);

    /***********************************************************
    * Find the two pointers in the offset linked list which take
    * up the channels.
    * Find the configuration of the channels with respect to the
    * the route.
    ***********************************************************/
    for (Plist = Pchlist; Plist; Plist = Plist->next)
    {
	find_the_pointers(Plist, Plist->Pedge, Pelist);
	find_the_config(net, Plist);
	determine_the_route(net, Plist);
    }
    free_parallel_sets();
}

/*=====================================================================
*   For each of all the routes, check if it is a special route. If so,
* process it.
=====================================================================*/
void find_special_routes()
{
    int i;
    int j;
    int e;
    int numrtes;

    OFSETPTR Pelist;

    for (i = 1; i <= numnets; i++)
    {
        numrtes = narray[i]->num_of_routes;

	for (j = 1; j <= numrtes; j++)
	{
	    narray[i]->route = j;
	    Pelist = narray[i]->Aroute[j]->Pedge;

	    while (Pelist)
	    {
		if (dearray[e = Pelist->edge]->Pnext && dearray[e]->status != -i)
		{
		    /***********************************************************
		    * Check if the route is a special one. If so, the channels
		    * are marked in the function find_special_route().
		    ***********************************************************/
		    find_special_route(i, narray[i]->Aroute[j]->Pedge) ;
		}
		Pelist = Pelist->next;
	    }
	}
    }
}
