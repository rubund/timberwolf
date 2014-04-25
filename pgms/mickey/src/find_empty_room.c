#ifndef lint
static char SccsId[] = "@(#)find_empty_room.c	Yale Version 2.3 5/16/91" ;
#endif
/* -----------------------------------------------------------------

	FILE:		find_empty_room.c
	AUTHOR:		Dahe Chen
	DATE:		Fri Apr 20 17:23:25 EDT 1990
	CONTENTS:	find_empty_room()
			find_special_route()
	REVISION:
		Wed Oct 10 18:41:55 EDT 1990
	    There are bugs in the function find_empty_room. Rewrite
	    the part which makes the linked list for the channels
	    which are adjacent to consecutive empty rooms.
		Thu Oct 11 14:50:54 EDT 1990
	    Add the assignment statement for numpin in dearray if
	    Pone or Ptwo but not both is a null pointer.
		Tue Oct 23 00:36:53 EDT 1990
	    Added string.h to remove compiliing problems on the
		SUN.
		Tue Nov 20 18:30:57 EST 1990
	    Modify the code to my new style and remove #define LEN.
		Mon Dec  3 14:31:19 EST 1990
	    Replace sscanf by Ystrparser.
		Tue Feb  5 12:00:00 EST 1991
	    Reformat error message output.
		Tue Mar  5 11:05:32 EST 1991
	    Change fclose to TWCLOSE.

----------------------------------------------------------------- */

#include <define.h>
#include <macros.h>
#include <gg_router.h>
#include <dgraph.h>
#include <yalecad/file.h>
#include <yalecad/string.h>

#define MINUS_ONE -1
int no_empty_room;

void
find_empty_room()
{

    char input[LRECL];
    char **tokens;
    INT numtokens;
    int i;
    int j;
    int l;
    int r;
    int lb;
    int rt;
    int v1;
    int v2;
    int len;
    int HnotV;
    int edge_m;
    int edge_lb;
    int edge_rt;
    int lb_min_x;
    int lb_min_y;
    int rt_max_x;
    int rt_max_y;

    DEDGEPTR Pedge;
    DEDGEPTR Pone;
    DEDGEPTR Ptwo;
    DENSPTR *Adens;
    LISTPTR Pnode;
    LISTPTR Pnode1;
    LISTPTR Pnode2;
    FILE *fp;

    /***********************************************************
    * Check if there are empty rooms by looking for capacity
    * equal to minus one (-1). If there are no channels with
    * capacity equal to minus one, quit the function.
    ***********************************************************/
    no_empty_room = FALSE;
    for (i = 1; i <= numedges; i++)
    {
	if (dearray[i]->capacity == MINUS_ONE)
	{
	    no_empty_room = TRUE;
	    break;
	}
    }
    if (no_empty_room == FALSE)
    {
	return;
    }

    /***********************************************************
    * Find the coordinates of the left-bottom corner and the
    * right-top corner.
    ***********************************************************/
    lb_min_x = INT_MAX;
    lb_min_y = INT_MAX;
    rt_max_x = INT_MIN;
    rt_max_y = INT_MIN;
    for (i = 1; i <= numnodes; i++)
    {
	lb_min_x = MIN(lb_min_x, garray[i]->xpos);
	lb_min_y = MIN(lb_min_y, garray[i]->ypos);
	rt_max_x = MAX(rt_max_x, garray[i]->xpos);
	rt_max_y = MAX(rt_max_y, garray[i]->ypos);
    }

    fp = FOPEN("mrte","r");

    if (!fgets(input, LRECL, fp))
    {
	ERROR1("\n\n");
	ERROR2("Error occured while reading the file %s.mrte\n", cktName);
	exit(GP_FAIL);
    }

    /***********************************************************
    * Find all the channels adjacent to empty rooms and link the
    * channels which are adjacent to a set of consecutive empty
    * rooms.
    ***********************************************************/
    while (fgets(input, LRECL, fp))
    {
	tokens = Ystrparser(input, " :\n\t", &numtokens);
	if (strncmp(tokens[0], "node", 4) == STRINGEQ)
	{
	    if (numtokens != 14)
	    {
		ERROR1("\n\n");
		ERROR2("The number of fields %d incorrect ", numtokens);
		ERROR2("in file %s.mrte.\nIt should be 14", cktName);
		exit(GP_FAIL);
	    }
	    v1 = atoi(tokens[1]);
	}
	else
	{
	    if (numtokens != 21)
	    {
		ERROR1("\n\n");
		ERROR2("The number of fields %d incorrect\n", numtokens);
		ERROR1("It should be 21");
		exit(GP_FAIL);
	    }
	    v2 = atoi(tokens[2]);
	    len = atoi(tokens[4]);
	    HnotV = atoi(tokens[16]);
	    lb = atoi(tokens[18]);
	    rt = atoi(tokens[20]);
	    
	    /***********************************************************
	    * Check if the channel is on the boundary of the chip. If
	    * so, we must reset variables lb and/or rt properly since
	    * they take zero value for the outside of the chip boundary,
	    * too.
	    ***********************************************************/
	    if (HnotV)
	    {
		if (garray[v1]->ypos == lb_min_y)
		{
		    /*****************************************************
		    * The channel is on the bottom boundary of the chip.
		    *****************************************************/
		    lb = 1;
		}
		if (garray[v1]->ypos == rt_max_y)
		{
		    /*****************************************************
		    * The channel is on the top boundary of the chip.
		    *****************************************************/
		    rt = 1;
		}
	    }
	    else
	    {
		if (garray[v1]->xpos == lb_min_x)
		{
		    /*****************************************************
		    * The channel is on the left boundary of the chip.
		    *****************************************************/
		    lb = 1;
		}
		if (garray[v1]->xpos == rt_max_x)
		{
		    /*****************************************************
		    * The channel is on the right boundary of the chip.
		    *****************************************************/
		    rt = 1;
		}
	    }

	    /***********************************************************
	    * Find the index of the channel and save it in variable
	    * edge_m.
	    ***********************************************************/
	    Pnode = garray[v1]->first;
	    while (Pnode->t_vertex != v2)
	    {
		Pnode = Pnode->next;
	    }
	    edge_m = Pnode->edge;

	    if (!(lb + rt))
	    { 
		/*********************************************************
		* Both sides of the channel are empty rooms.
		*********************************************************/
		if (HnotV)
		{
		    /*****************************************************
		    * The channel is horizontal in the channel graph. Find
		    * the channel below edge_m and parallel to edge_m.
		    *****************************************************/
		    Pnode1 = garray[v1]->first;
		    while (garray[v1]->ypos
			<= garray[Pnode1->t_vertex]->ypos)
		    {
			Pnode1 = Pnode1->next;
		    }

		    Pnode2 = garray[v2]->first;
		    while (garray[v2]->ypos
			<= garray[Pnode2->t_vertex]->ypos)
		    {
			Pnode2 = Pnode2->next;
		    }

		    Pnode = garray[Pnode1->t_vertex]->first;
		    while (Pnode->t_vertex != Pnode2->t_vertex)
		    {
			Pnode = Pnode->next;
		    }
		    edge_lb = Pnode->edge;

		    /*****************************************************
		    * Find the channel above edge_m and parallel to
		    * edge_m.
		    *****************************************************/
		    Pnode1 = garray[v1]->first;
		    while (garray[v1]->ypos
			>= garray[Pnode1->t_vertex]->ypos)
		    {
			Pnode1 = Pnode1->next;
		    }

		    Pnode2 = garray[v2]->first;
		    while (garray[v2]->ypos
			>= garray[Pnode2->t_vertex]->ypos)
		    {
			Pnode2 = Pnode2->next;
		    }

		    Pnode = garray[Pnode1->t_vertex]->first;
		    while (Pnode->t_vertex != Pnode2->t_vertex)
		    {
			Pnode = Pnode->next;
		    }
		    edge_rt = Pnode->edge;
		}
		else
		{
		    /*****************************************************
		    * The channel is vertical in the channel graph. Find
		    * the channel to the left of edge_m and parallel to
		    * edge_m.
		    *****************************************************/
		    Pnode1 = garray[v1]->first;
		    while (garray[v1]->xpos
			<= garray[Pnode1->t_vertex]->xpos)
		    {
			Pnode1 = Pnode1->next;
		    }

		    Pnode2 = garray[v2]->first;
		    while (garray[v2]->xpos
		        <= garray[Pnode2->t_vertex]->xpos)
		    {
			Pnode2 = Pnode2->next;
		    }

		    Pnode = garray[Pnode1->t_vertex]->first;
		    while (Pnode->t_vertex != Pnode2->t_vertex)
		    {
			Pnode = Pnode->next;
		    }
		    edge_lb = Pnode->edge;

		    /*****************************************************
		    * Find the channel to the right of edge_m and parallel
		    * to edge_m.
		    *****************************************************/
		    Pnode1 = garray[v1]->first;
		    while (garray[v1]->xpos
			>= garray[Pnode1->t_vertex]->xpos)
		    {
			Pnode1 = Pnode1->next;
		    }

		    Pnode2 = garray[v2]->first;
		    while (garray[v2]->xpos
			>= garray[Pnode2->t_vertex]->xpos)
		    {
			Pnode2 = Pnode2->next;
		    }

		    Pnode = garray[Pnode1->t_vertex]->first;
		    while (Pnode->t_vertex != Pnode2->t_vertex)
		    {
			Pnode = Pnode->next;
		    }
		    edge_rt = Pnode->edge;
		}

		/*********************************************************
		* Check each of the channels found adjacent to an empty
		* room if they are linked already. Note that the linking
		* direction will be edge_lb --> edge_m --> edge_rt if
		* they are linked already.
		********************************************************/
		if (!dearray[edge_m]->Pnext)
		{
		    /*****************************************************
		    * The channel edge_m is not in any linked list.
		    *****************************************************/
		    if (!dearray[edge_lb]->Pnext)
		    {
			dearray[edge_m]->Pnext = dearray[edge_lb];
			dearray[edge_lb]->Pnext = dearray[edge_m];
		    }
		    else
		    {
			dearray[edge_m]->Pnext = dearray[edge_lb]->Pnext;
			dearray[edge_lb]->Pnext = dearray[edge_m];
		    }

		    if (!dearray[edge_rt]->Pnext)
		    {
			dearray[edge_rt]->Pnext = dearray[edge_m]->Pnext;
		    }
		    else
		    {
			Pedge = dearray[edge_rt]->Pnext;
			while (Pedge->Pnext != dearray[edge_rt])
			{
			    Pedge = Pedge->Pnext;
			}
			Pedge->Pnext = dearray[edge_m]->Pnext;
		    }
		    dearray[edge_m]->Pnext = dearray[edge_rt];
		}
		else
		{
		    /*****************************************************
		    * The channel edge_m is in a linked list.
		    *****************************************************/
		    if (dearray[edge_m]->Pnext == dearray[edge_rt])
		    {
			/*************************************************
			* Channel edge_m is linked to channel edge_rt.
			*************************************************/
			Pedge = dearray[edge_m]->Pnext;
			while (Pedge->Pnext != dearray[edge_m])
			{
			    Pedge = Pedge->Pnext;
			}

			if (!dearray[edge_lb]->Pnext)
			{
			    Pedge->Pnext = dearray[edge_lb];
			    dearray[edge_lb]->Pnext = dearray[edge_m];
			}
			else
			{
			    if (dearray[edge_lb]->Pnext
			     != dearray[edge_m])
			    {
				Pedge->Pnext = dearray[edge_lb]->Pnext;
				dearray[edge_lb]->Pnext = dearray[edge_m];
			    }
			}
		    }
		    else
		    {
			/*************************************************
			* Channel edge_m is linked to edge_lb.
			*************************************************/
			if (!dearray[edge_rt]->Pnext)
			{
			    dearray[edge_rt]->Pnext =
						dearray[edge_m]->Pnext;
			    dearray[edge_m]->Pnext = dearray[edge_rt];
			}
			else
			{
			    Pedge = dearray[edge_rt]->Pnext;
			    while (Pedge->Pnext != dearray[edge_rt])
			    {
				Pedge = Pedge->Pnext;
			    }
			    Pedge->Pnext = dearray[edge_m]->Pnext;
			    dearray[edge_m]->Pnext = dearray[edge_rt];
			}
		    }
		}
	    }    
	    else if (!lb)
	    {
		/*********************************************************
		* The left or bottom side of the channel is an empty room.
		*********************************************************/
		if (dearray[edge_m]->Pnext)
		{
		    /*****************************************************
		    * The channel is already in the linked list. Skip it.
		    *****************************************************/
		    continue;
		}

		if (HnotV)
		{
		    /*****************************************************
		    * The channel is horizontal in the channel graph. Find
		    * the channel below edge_m and parallel to edge_m.
		    *****************************************************/
		    Pnode1 = garray[v1]->first;
		    while (garray[v1]->ypos
			<= garray[Pnode1->t_vertex]->ypos)
		    {
			Pnode1 = Pnode1->next;
		    }

		    Pnode2 = garray[v2]->first;
		    while (garray[v2]->ypos
			<= garray[Pnode2->t_vertex]->ypos)
		    {
			Pnode2 = Pnode2->next;
		    }

		    Pnode = garray[Pnode1->t_vertex]->first;
		    while (Pnode->t_vertex != Pnode2->t_vertex)
		    {
			Pnode = Pnode->next;
		    }
		    edge_lb = Pnode->edge;
		}
		else
		{
		    /*****************************************************
		    * The channel is vertical in the channel graph. Find
		    * the channel to the left of edge_m and parallel to
		    * edge_m.
		    *****************************************************/
		    Pnode1 = garray[v1]->first;
		    while (garray[v1]->xpos
			<= garray[Pnode1->t_vertex]->xpos)
		    {
			Pnode1 = Pnode1->next;
		    }

		    Pnode2 = garray[v2]->first;
		    while (garray[v2]->xpos
			<= garray[Pnode2->t_vertex]->xpos)
		    {
			Pnode2 = Pnode2->next;
		    }

		    Pnode = garray[Pnode1->t_vertex]->first;
		    while (Pnode->t_vertex != Pnode2->t_vertex)
		    {
			Pnode = Pnode->next;
		    }
		    edge_lb = Pnode->edge;
		}

		if (dearray[edge_lb]->Pnext)
		{
		    dearray[edge_m]->Pnext = dearray[edge_lb]->Pnext;
		    dearray[edge_lb]->Pnext = dearray[edge_m];
		}
		else
		{
		    dearray[edge_m]->Pnext = dearray[edge_lb];
		    dearray[edge_lb]->Pnext = dearray[edge_m];
		}
	    }
	    else if (!rt)
	    {
		/*********************************************************
		* The right or top side of the channel is an empty room.
		*********************************************************/
		if (dearray[edge_m]->Pnext)
		{
		    /*****************************************************
		    * The channel is already in the linked list. Skip it.
		    *****************************************************/
		    continue;
		}

		if (HnotV)
		{
		    /*****************************************************
		    * Find the channel above edge_m and parallel to
		    * edge_m.
		    *****************************************************/
		    Pnode1 = garray[v1]->first;
		    while (garray[v1]->ypos
			>= garray[Pnode1->t_vertex]->ypos)
		    {
			Pnode1 = Pnode1->next;
		    }

		    Pnode2 = garray[v2]->first;
		    while (garray[v2]->ypos
			>= garray[Pnode2->t_vertex]->ypos)
		    {
			Pnode2 = Pnode2->next;
		    }

		    Pnode = garray[Pnode1->t_vertex]->first;
		    while (Pnode->t_vertex != Pnode2->t_vertex)
		    {
			Pnode = Pnode->next;
		    }
		    edge_rt = Pnode->edge;
		}
		else
		{
		    /*****************************************************
		    * Find the channel to the right of edge_m and parallel
		    * to edge_m.
		    *****************************************************/
		    Pnode1 = garray[v1]->first;
		    while (garray[v1]->xpos
			>= garray[Pnode1->t_vertex]->xpos)
		    {
			Pnode1 = Pnode1->next;
		    }

		    Pnode2 = garray[v2]->first;
		    while (garray[v2]->xpos
			>= garray[Pnode2->t_vertex]->xpos)
		    {
			Pnode2 = Pnode2->next;
		    }

		    Pnode = garray[Pnode1->t_vertex]->first;
		    while (Pnode->t_vertex != Pnode2->t_vertex)
		    {
			Pnode = Pnode->next;
		    }
		    edge_rt = Pnode->edge;
		}

		if (dearray[edge_rt]->Pnext)
		{
		    Pedge = dearray[edge_rt]->Pnext;
		    while (Pedge->Pnext != dearray[edge_rt])
		    {
			Pedge = Pedge->Pnext;
		    }
		    dearray[edge_m]->Pnext = dearray[edge_rt];
		    Pedge->Pnext = dearray[edge_m];
		}
		else
		{
		    dearray[edge_m]->Pnext = dearray[edge_rt];
		    dearray[edge_rt]->Pnext = dearray[edge_m];
		}
	    }
	}
    }
    TWCLOSE(fp);

    /***********************************************************
    * Now update the pin arrays for the channels which are
    * adjacent to empty rooms. What we want here is to assign
    * the pointer to the pin array of the two channels, which
    * are on the boundary of a set of consecutive empty rooms,
    * to the same pin array.
    ***********************************************************/
    for (i = 1; i <= numedges; i++)
    {
	if (dearray[i]->Pnext && dearray[i]->capacity != MINUS_ONE)
	{
	    Pone = dearray[i];
	    Ptwo = Pone->Pnext;
	    while (Ptwo->Pnext != Pone)
	    {
		Ptwo = Ptwo->Pnext;
	    }
	    if (Pone->numpin && Ptwo->numpin)
	    {
		/*********************************************************
		* Both channels have pins. Merge the two pin arrays into
		* one array.
		*********************************************************/
		l = Pone->numpin - 2;
		r = Ptwo->numpin - 2;
		len = l + r + 2;
		Adens = (DENSPTR *) Ysafe_malloc(len*sizeof(DENSPTR));
		Adens[0] = Ptwo->Adens[0];
		Ptwo->Adens[0] = NIL(DENS);

		j = 1;
		v1 = 1;
		v2 = 1;
		for (;;)
		{
		    if (v1 <= l && v2 <= r)
		    {
			if (Pone->Adens[v1]->distance
			  < Ptwo->Adens[v2]->distance)
			{
			    Adens[j++] = Pone->Adens[v1];
			    Pone->Adens[v1++] = NIL(DENS);
			}
			else if (Pone->Adens[v1]->distance
			   > Ptwo->Adens[v2]->distance)
			{
			    Adens[j++] = Ptwo->Adens[v2];
			    Ptwo->Adens[v2++] = NIL(DENS);
			}
			else
			{
			    Adens[j] = Pone->Adens[v1];
			    Adens[j]->net[1] = Ptwo->Adens[v2]->net[0];
			    Adens[j++]->channel[1] =
				Ptwo->Adens[v2]->channel[0];
			    Pone->Adens[v1++] = NIL(DENS);
			    v2++;
			}
		    }
		    else if (v1 <= l)
		    {
			Adens[j++] = Pone->Adens[v1];
			Pone->Adens[v1++] = NIL(DENS);
		    }
		    else if (v2 <= r)
		    {
			Adens[j++] = Ptwo->Adens[v2];
			Ptwo->Adens[v2++] = NIL(DENS);
		    }
		    else
		    {
			break;
		    }
		}

		Adens[j] = Pone->Adens[v1];
		Pone->Adens[v1] = NIL(DENS);

		if (j < len)
		{
		    len = j + 1;
		    Adens = (DENSPTR *)
			Ysafe_realloc((char *)Adens, len*sizeof(DENSPTR));
		}
		Pone->numpin =
		Ptwo->numpin = len;

		l += 2;
		for (j = 0; j < l; j++)
		{
		    if (Pone->Adens[j])
		    {
			Ysafe_free((char *) Pone->Adens[j]);
		    }
		}
		Ysafe_free((char *) Pone->Adens);
		Pone->Adens = Adens;

		r += 2;
		for (j = 0; j < r; j++)
		{
		    if (Ptwo->Adens[j])
		    {
			Ysafe_free((char *) Ptwo->Adens[j]);
		    }
		}
		Ysafe_free((char *) Ptwo->Adens);
		Ptwo->Adens = Adens;
	    }
	    else if (Pone->numpin)
	    {
		/*********************************************************
		* The channel Pone has pins.
		*********************************************************/
		Ptwo->Adens = Pone->Adens;
		Ptwo->numpin = Pone->numpin;
	    }
	    else if (Ptwo->numpin)
	    {
		/*********************************************************
		* The channel Ptwo has pins.
		*********************************************************/
		Pone->Adens = Ptwo->Adens;
		Pone->numpin = Ptwo->numpin;
	    }
	}
    }

    return;
  
} /* find_empty_room */
