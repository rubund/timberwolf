#ifndef lint
static char SccsId[] = "@(#)random_interchange.c	Yale Version 3.7 5/28/91";
#endif
/* -----------------------------------------------------------------

	FILE:		random_interchange.c
	AUTHOR:		Dahe Chen
	DATE:		Tue Aug 14 09:56:05 PDT 1990
	CONTENTS:	random_interchange()
			generate_index()
			generate_index2()
			find_feasible_nets()
	REVISION:
		Tue Mar  5 11:03:32 EST 1991
	    Change fopen and fclose to TWOPEN and TWCLOSE,
	    respectively.
		Tue May 14 15:52:20 EDT 1991
	    Change ABORT to NOABORT in reading the random seed file.
		Tue May 28 18:24:39 EDT 1991
	    Move casts from left to right.

----------------------------------------------------------------- */

#include	<define.h>
#include	<gg_router.h>
#include	<dgraph.h>
#include	<macros.h>
#include	<yalecad/file.h>

static	int	net_index	;
static	int	rte_index	;
static	int	number_nets	;
static	int	*Anets		;

/*=====================================================================
*   Print the number of iterations every 100 iterations.
=====================================================================*/
void print_iteration(iter)
    int iter;
{
    if (!(iter % 100))
    {
	if (!(iter % 1000))
	{
	    PRINT(stdout, "%5d\n", iter);
	}
	else
	{
	    PRINT(stdout, "%5d ", iter);
	}
	(void)fflush(stdout);
    }
} /* end of print_iteration */

/*=====================================================================
*   Print the number of iterations and the overflow every 500
* iterations.
=====================================================================*/
void print_overflow(iter, total_min)
    int iter;
    int total_min;
{
    if (!(iter % 500))
    {
	PRINT(fdat, "Iteration %4d:", iter);
	PRINT(fdat, "  overflow = %-7d\n", total_min);
	(void)fflush(fdat);
    }
} /* end of print_overflow */

void
random_interchange(number_of_iterations)
int	number_of_iterations	;
{
    extern	void		Yset_random_seed()	;
    extern	char		*YcurTime()		;
    extern	int 		long_path()		;
    extern	int		update_weight1()	;
    extern	int		update_weight2()	;
    void			generate_index()	;
    void			generate_index2()	;
    void			print_lengths()		;
    void			print_wire_length()	;
    int				find_feasible_nets()	;

    char	*current_time	;
    char	input[128]	;
    int		iter		;
    int		seed		;
    int		route		;
    int		h_initial	;
    int		v_initial	;
    int		h_lmin		;
    int		v_lmin		;
    int		min_length	;
    int		tot_length	;
    int		length_this	;
    int		length_next	;
    int		total_min	;
    int		total_initial	;
    int		no_change_iter	;
    int		no_change_limit	;
    double	area_min	;
    double	area_now	;
    FILE	*fseed		;

    ROUTEPTR	Proute		;

#ifdef	DEBUG
    int		do_debug = 0	;
#endif	/* DEBUG */

    /***********************************************************
    * Check if the file storing a random seed exists. If such a
    * file exists, read the seed; otherwise, generate a random
    * seed. This is very useful for debugging since we can re-
    * produce the run when it causes a crash.
    ***********************************************************/
    sprintf( input, "%s.seed", cktName );
    if (fseed=TWOPEN(input, "r", NOABORT))
    {
	if (fgets(input, 128, fseed))
	{
	    seed = atoi(input);
	}
	TWCLOSE(fseed);
    }
    else
    {
	/***********************************************************
	* Get a random seed for the random number generator.
	***********************************************************/
	current_time = YcurTime(&seed);
    }

    Yset_random_seed(seed);

    /***********************************************************
    * Initialization.
    ***********************************************************/
    total_min = total_initial = 0;
    no_change_iter = 0;
    no_change_limit = 2 * numnets * NUMTREES;
    Proute = (ROUTEPTR)Ysafe_malloc(sizeof(ROUTE));
    Proute->next = NIL(ROUTE);
    Anets = (int *)Ysafe_calloc((numnets+1), sizeof(int));
    PRINT(fdat,"\n\nRandom seed = %d\n", seed);

    PRINT(stdout, "\n\n");
    PRINT(fdat, "\n\n");

    /***********************************************************
    * Find the nets which have multiple routes and save them in
    * Anets.
    ***********************************************************/
    if ((number_nets = find_multiple_route_nets()) == 0)
    {
	PRINT(stdout, "\n\nThe number of routes for all the nets is 1\n");
	PRINT(stdout, "No minimization can be performed.\n");

	init_assign();

	if (CASE == 1)
	{
	    make_arrays();

	    h_initial = h_lmin =
		long_path(h_narray, h_numnodes, h_parent, h_critical);
	    v_initial = v_lmin =
		long_path(v_narray, v_numnodes, v_parent, v_critical);
	    PRINT(stdout,"\n\n");
	    PRINT(stdout, "=========================================================\n");
	    PRINT(stdout, "      INITIAL CHIP AREA    |      MINIMUM CHIP AREA\n");
	    PRINT(stdout, "---------------------------|-----------------------------\n");
	    PRINT(stdout, "          %5dx%-5d      |         %5dx%-5d\n",
	       h_initial, v_initial, h_lmin, v_lmin);
	    PRINT(stdout, "=========================================================\n");
	    PRINT(fdat,"\n\n");
	    PRINT(fdat, "=========================================================\n");
	    PRINT(fdat, "      INITIAL CHIP AREA    |      MINIMUM CHIP AREA\n");
	    PRINT(fdat, "---------------------------|-----------------------------\n");
	    PRINT(fdat, "          %5dx%-5d      |         %5dx%-5d\n",
	       h_initial, v_initial, h_lmin, v_lmin);
	    PRINT(fdat, "=========================================================\n");
	}

	total_min = total_initial = total_cost;
	PRINT(stdout,"\n\n");
	PRINT(stdout,
	   "=========================================================\n");
	PRINT(stdout,
	   "      INITIAL OVERFLOW     |      MINIMUM OVERFLOW\n");
	PRINT(stdout,
	   "---------------------------|-----------------------------\n");
	PRINT(stdout,
	   "          %5d            |         %5d\n",
	   total_initial, total_min);
	PRINT(stdout,
	   "=========================================================\n");
	PRINT(fdat,"\n\n");
	PRINT(fdat,
	   "=========================================================\n");
	PRINT(fdat,
	   "      INITIAL OVERFLOW     |      MINIMUM OVERFLOW\n");
	PRINT(fdat,
	   "---------------------------|-----------------------------\n");
	PRINT(fdat,
	   "          %5d            |         %5d\n",
	   total_initial, total_min);
	PRINT(fdat,
	   "=========================================================\n");

	tot_length = 0;
	for (net_index = 1; net_index <= numnets; net_index++)
	{
	    rte_index = narray[net_index]->route;
	    tot_length += narray[net_index]->Aroute[rte_index]->length;
	}
	min_length = tot_length;

	PRINT(stdout,"\n\n");
	PRINT(stdout,
	   "=========================================================\n");
	PRINT(stdout,
	   " INITIAL TOTAL WIRE LENGTH |      FINAL WIRE LENGTH\n");
	PRINT(stdout,
	   "---------------------------|-----------------------------\n");
	PRINT(stdout,
	   "          %-9d        |         %-9d\n",
	   tot_length, min_length);
	PRINT(stdout,
	   "=========================================================\n");
	fflush(stdout);
	PRINT(fdat,"\n\n");
	PRINT(fdat,
	   "=========================================================\n");
	PRINT(fdat,
	   " INITIAL TOTAL WIRE LENGTH |      FINAL WIRE LENGTH\n");
	PRINT(fdat,
	   "---------------------------|-----------------------------\n");
	PRINT(fdat,
	   "          %-9d        |         %-9d\n",
	   tot_length, min_length);
	PRINT(fdat,
	   "=========================================================\n");
	fflush(fdat);

	Ysafe_free((char *) Anets);
	Ysafe_free((char *) Proute);
	return;
    }

    if (CASE==1)
    {
	init_assign();
	PRINT(stdout, "Iterating random interchange (Objective I)...\n");
	PRINT(fdat, "Iterating random interchange (Objective I)...\n");
	PRINT(stdout, "\nMinimizing the chip area...\n");
	PRINT(fdat, "\nMinimizing the chip area...\n");
#ifdef	DEBUG
	    if (do_debug)
	    {
		print_empty_room_list();
	    }
#endif	/* DEBUG */
	make_arrays();
	h_initial =
	h_lmin = long_path(h_narray, h_numnodes, h_parent, h_critical);
	v_initial =
	v_lmin = long_path(v_narray, v_numnodes, v_parent, v_critical);
	area_min = (double) h_lmin * (double) v_lmin;

	print_lengths(0, h_lmin, v_lmin);

	for (iter=1; iter<=number_of_iterations; iter++)
	{
	    generate_index();
	    Proute->net = (short) net_index;
	    Proute->route = (short) rte_index;
	    route = narray[net_index]->route;
	    update_route(Proute, update_weight1);
	    h_lpath =
		long_path(h_narray, h_numnodes, h_parent, h_critical);
	    v_lpath =
		long_path(v_narray, v_numnodes, v_parent, v_critical);
	    area_now = (double) h_lpath * (double) v_lpath;
	    if (area_now<=area_min)
	    {
		if (area_now<area_min)
		{
		    no_change_iter = 0;
		    h_lmin = h_lpath;
		    v_lmin = v_lpath;
		    area_min = area_now;
		}
		else
		{
		    no_change_iter++;
		}
	    }
	    else
	    {
		no_change_iter++;
		Proute->route = (short) route;
		update_route(Proute, update_weight1);
		h_lpath = long_path(h_narray, h_numnodes, h_parent,
			h_critical);
		v_lpath = long_path(v_narray, v_numnodes, v_parent,
			v_critical);
	    }

	    print_lengths(iter, h_lmin, v_lmin);
	    print_iteration(iter);

	    /***********************************************************
	    * If the number of non-improvement iterations is greater
	    * than the pre-set limit, then quit the iteration.
	    ***********************************************************/
	    if (no_change_iter>no_change_limit)
	    {
		break;
	    }
	}

	/***********************************************************
	* Now start another loop of random interchange algorithm to
	* reduce the total wire length. This time reduce the limit
	* of the non-change stop criterion to N*M.
	***********************************************************/
	PRINT(stdout, "\nMinimizing the total wire length...\n");
	PRINT(fdat, "\nMinimizing the total wire length...\n");
	no_change_iter = 0;
	no_change_limit /= 2;
	tot_length = 0;
	for (net_index=1; net_index<=numnets; net_index++)
	{
	    rte_index = narray[net_index]->route;
	    tot_length += narray[net_index]->Aroute[rte_index]->length;
	}
	min_length = tot_length;

	for (iter=1; iter<=number_of_iterations; iter++)
	{
	    /***********************************************************
	    * Find an index of a route which is less than that of the
	    * current route so that the total wire length will be less
	    * if the chip area dose not increase.
	    ***********************************************************/
	    if (!find_feasible_nets())
	    {
		break;
	    }
	    generate_index2();
	    Proute->net = (short) net_index;
	    Proute->route = (short) rte_index;
	    route = narray[net_index]->route;
	    update_route(Proute, update_weight1);
	    h_lpath = long_path(h_narray, h_numnodes, h_parent,
		    h_critical);
	    v_lpath = long_path(v_narray, v_numnodes, v_parent,
		    v_critical);
	    area_now = (double) h_lpath * (double) v_lpath;
	    if (area_now<=area_min)
	    {
		if (area_now<area_min)
		{
		    h_lmin = h_lpath;
		    v_lmin = v_lpath;
		    area_min = area_now;
		}
		length_this = narray[net_index]->Aroute[route]->length;
		length_next = narray[net_index]->Aroute[rte_index]->length;
		if (length_this>=length_next)
		{
		    min_length += (length_next-length_this);
		    no_change_iter = 0;
		}
		else
		{
		    no_change_iter++;
		    Proute->route = (short) route;
		    update_route(Proute, update_weight1);
		    h_lpath = long_path(h_narray, h_numnodes, h_parent,
			    h_critical);
		    v_lpath = long_path(v_narray, v_numnodes, v_parent,
			    v_critical);
		}
	    }
	    else
	    {
		no_change_iter++;
		Proute->route = (short) route;
		update_route(Proute, update_weight1);
		h_lpath = long_path(h_narray, h_numnodes, h_parent,
			h_critical);
		v_lpath = long_path(v_narray, v_numnodes, v_parent,
			v_critical);
	    }

	    print_wire_length(iter, min_length);
	    print_iteration(iter);

	    /***********************************************************
	    * If the number of non-improvement iterations is greater
	    * than the pre-set limit, then quit the iteration.
	    ***********************************************************/
	    if (no_change_iter > no_change_limit)
	    {
		break;
	    }

	}
	PRINT(stdout,"\n\n");
	PRINT(stdout, "=========================================================\n");
	PRINT(stdout, "      INITIAL CHIP AREA    |      MINIMUM CHIP AREA\n");
	PRINT(stdout, "---------------------------|-----------------------------\n");
	PRINT(stdout, "          %5dx%-5d      |         %5dx%-5d\n",
			    h_initial, v_initial, h_lmin, v_lmin);
	PRINT(stdout, "=========================================================\n");
	PRINT(fdat,"\n\n");
	PRINT(fdat, "=========================================================\n");
	PRINT(fdat, "      INITIAL CHIP AREA    |      MINIMUM CHIP AREA\n");
	PRINT(fdat, "---------------------------|-----------------------------\n");
	PRINT(fdat, "          %5dx%-5d      |         %5dx%-5d\n",
			    h_initial, v_initial, h_lmin, v_lmin);
	PRINT(fdat, "=========================================================\n");
	PRINT(stdout,"\n\n");
	PRINT(stdout, "=========================================================\n");
	PRINT(stdout, " INITIAL TOTAL WIRE LENGTH |      FINAL WIRE LENGTH\n");
	PRINT(stdout, "---------------------------|-----------------------------\n");
	PRINT(stdout, "          %-9d        |         %-9d\n", tot_length, min_length);
	PRINT(stdout, "=========================================================\n");
	fflush(stdout);
	PRINT(fdat,"\n\n");
	PRINT(fdat, "=========================================================\n");
	PRINT(fdat, " INITIAL TOTAL WIRE LENGTH |      FINAL WIRE LENGTH\n");
	PRINT(fdat, "---------------------------|-----------------------------\n");
	PRINT(fdat, "          %-9d        |         %-9d\n", tot_length, min_length);
	PRINT(fdat, "=========================================================\n");
	fflush(fdat);
    }
    else
    {
	PRINT(stdout, "Iterating random interchange (Objective II)...\n");
	PRINT(fdat, "Iterating random interchange (Objective II)...\n");
	if (init_assign())
	{
	    tot_length = 0;
	    for (net_index=1; net_index<=numnets; net_index++)
	    {
		rte_index = narray[net_index]->route;
		tot_length += narray[net_index]->Aroute[rte_index]->length;
	    }
	    min_length = tot_length;
	    /***********************************************************
	    * Very fortunately, we don't have any channel in which the
	    * density exceeds its capacity; and we don't have to do any
	    * thing except quit.
	    ***********************************************************/
	    PRINT(stdout, "No channel has its channel density exceeding its ");
	    PRINT(stdout, "capacity\n");
	    fflush(stdout);
	    PRINT(fdat, "No channel has its channel density ");
	    PRINT(fdat, "exceeding its capacity\n");
	    fflush(fdat);
	}
	else
	{
	    PRINT(stdout, "\nMinimizing the total density overflow...\n");
	    PRINT(fdat, "\nMinimizing the total density overflow...\n");
	    total_min = total_initial = total_cost;
	    PRINT(fdat, "Iteration    0:");
	    PRINT(fdat, "  overflow = %-7d\n", total_cost);
	    fflush(fdat);

	    for (iter=1; iter<=number_of_iterations; iter++)
	    {
		generate_index();
		Proute->net = (short) net_index;
		Proute->route = (short) rte_index;
		route = narray[net_index]->route;
		update_route( Proute, update_weight2 );
		if (total_cost<=total_min)
		{
		    if (total_cost==total_min)
		    {
			no_change_iter++;
		    }
		    else
		    {
			no_change_iter = 0;
			total_min = total_cost;
		    }
		    if (!total_min)
		    {
			print_iteration(iter);
			break;
		    }
		}
		else
		{
		    no_change_iter++;
		    Proute->route = route;
		    update_route(Proute, update_weight2);
		}

		print_overflow(iter, total_min);
		print_iteration(iter);

		/***********************************************************
		* If the number of non-improvement iterations is greater
		* than the pre-set limit, then quit the iteration.
		***********************************************************/
		if (no_change_iter>no_change_limit)
		{
		    break;
		}
	    }

	    /***********************************************************
	    * Now start another loop of random interchange algorithm to
	    * reduce the total wire length. This time reduce the limit
	    * of the non-change stop criterion to N*M.
	    ***********************************************************/
	    PRINT(stdout, "\nMinimizing the total wire length...\n");
	    PRINT(fdat, "\nMinimizing the total wire length...\n");
	    tot_length = 0;
	    no_change_iter = 0;
	    no_change_limit /= 2;
	    for (net_index=1; net_index<=numnets; net_index++)
	    {
		rte_index = narray[net_index]->route;
		tot_length += narray[net_index]->Aroute[rte_index]->length;
	    }
	    min_length = tot_length;

	    for (iter=1; iter<=number_of_iterations; iter++)
	    {
		/*********************************************************
		* Find an index of a route which is less than that of the
		* current route so that the total wire length will be less
		* if the chip area dose not increase.
		*********************************************************/
		if (!find_feasible_nets())
		{
		    break;
		}
		generate_index2();
		Proute->net = (short) net_index;
		Proute->route = (short) rte_index;
		route = narray[net_index]->route;
		update_route(Proute, update_weight2);
		if (total_cost<=total_min)
		{
		    if (total_cost<total_min)
		    {
			total_min = total_cost;
		    }
		    length_this = narray[net_index]->Aroute[route]->length;
		    length_next = narray[net_index]->Aroute[rte_index]->length;
		    if (length_this>=length_next)
		    {
			min_length += (length_next-length_this);
			no_change_iter = 0;
		    }
		    else
		    {
			no_change_iter++;
			Proute->route = route;
			update_route(Proute, update_weight2);
		    }
		}
		else
		{
		    no_change_iter++;
		    Proute->route = route;
		    update_route(Proute, update_weight2);
		}

		print_wire_length(iter, min_length);
		print_iteration(iter);

		/***********************************************************
		* If the number of non-improvement iterations is greater
		* than the pre-set limit, then quit the iteration.
		***********************************************************/
		if (no_change_iter > no_change_limit)
		{
		    break;
		}
	    }
	}
	PRINT(stdout,"\n\n");
	PRINT(stdout, "=========================================================\n");
	PRINT(stdout, "      INITIAL OVERFLOW     |      MINIMUM OVERFLOW\n");
	PRINT(stdout, "---------------------------|-----------------------------\n");
	PRINT(stdout, "          %5d            |         %5d\n",
			    total_initial, total_min);
	PRINT(stdout, "=========================================================\n");
	PRINT(fdat,"\n\n");
	PRINT(fdat, "=========================================================\n");
	PRINT(fdat, "      INITIAL OVERFLOW     |      MINIMUM OVERFLOW\n");
	PRINT(fdat, "---------------------------|-----------------------------\n");
	PRINT(fdat, "          %5d            |         %5d\n",
			    total_initial, total_min);
	PRINT(fdat, "=========================================================\n");
	PRINT(stdout,"\n\n");
	PRINT(stdout, "=========================================================\n");
	PRINT(stdout, " INITIAL TOTAL WIRE LENGTH |      FINAL WIRE LENGTH\n");
	PRINT(stdout, "---------------------------|-----------------------------\n");
	PRINT(stdout, "          %-9d        |         %-9d\n", tot_length, min_length);
	PRINT(stdout, "=========================================================\n");
	fflush(stdout);
	PRINT(fdat,"\n\n");
	PRINT(fdat, "=========================================================\n");
	PRINT(fdat, " INITIAL TOTAL WIRE LENGTH |      FINAL WIRE LENGTH\n");
	PRINT(fdat, "---------------------------|-----------------------------\n");
	PRINT(fdat, "          %-9d        |         %-9d\n", tot_length, min_length);
	PRINT(fdat, "=========================================================\n");
	fflush(fdat);
    }
    Ysafe_free((char *) Proute);
    Ysafe_cfree((char *) Anets);

    return;

} /* end of random_interchange */

/* ==================================================================== */

void
generate_index()
{

int	number_of_routes	;

/***********************************************************
* Select a net and a route to which the current route will
* be replaced by a new selected route. Before this function
* is called, function Yset_random_seed( seed ) must be
* called in order to get non-zero random numbers.
***********************************************************/
for (;;)
{
    net_index = Anets[Yacm_random() % number_nets];
    number_of_routes = narray[net_index]->num_of_routes;
    rte_index = Yacm_random() % number_of_routes + 1;
    if (narray[net_index]->route!=rte_index)
    {
	break;
    }
}

return;

} /* end of generate_index */

/* ==================================================================== */

void
generate_index2()
{

int	number_of_routes	;

/***********************************************************
* Select a net and a route to which the current route will
* be replaced by a new selected route. Before this function
* is called, function Yset_random_seed( seed ) must be
* called in order to get non-zero random numbers. This one
* will return an index for net and route such that the route
* index is less than that of the current route of the net.
***********************************************************/
for (;;)
{
    net_index = Anets[Yacm_random()%number_nets];
    number_of_routes = narray[net_index]->route;
    while ((rte_index=(Yacm_random()%number_of_routes))==0)
	;
    break;
}

return;

} /* end of generate_index2 */

/* ==================================================================== */

int
find_feasible_nets()
{

int	i	;
int	j	;

j = 0;
for (i=1; i<=numnets; i++)
{
    if (narray[i]->route>1)
    {
	Anets[j++] = i;
    }
}
number_nets = j - 1;

if (number_nets<=0)
{
    return(FALSE);
}
else
{
    return(TRUE);
}

}

void
print_lengths(iter, h_len, v_len)
    int iter;
    int h_len;
    int v_len;
{
    if (!(iter % 500))
    {
	PRINT(fdat,"Iteration %4d:", iter);
	PRINT(fdat,"  h_length = %-7d", h_len);
	PRINT(fdat,"  v_length = %-7d\n", v_len);
	fflush(fdat);
    }
}

void
print_wire_length(iter, len)
    int iter;
    int len;
{
    if (!(iter % 500))
    {
	PRINT(fdat, "Iteration %4d:", iter);
	PRINT(fdat, "  total wire length = %-7d\n", len);
	fflush(fdat);
    }
}

/*=====================================================================
* Find the nets which have multiple routes and save them in Anets.
=====================================================================*/
int
find_multiple_route_nets()
{
    register int i;
    register int j;

    j = 0;

    for (i = 1; i <= numnets; i++)
    {
	if (narray[i]->num_of_routes > 1)
	{
	    Anets[j++] = i;
	}
    }

    return(j);

} /* end of find_multiple_route_nets() */
