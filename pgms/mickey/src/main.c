#ifndef lint
static char SccsId[] = "@(#)main.c	Yale Version 3.3 5/23/91";
#endif
/* -----------------------------------------------------------------

	FILE:		main.c
	AUTHOR:		Dahe Chen
	DATE:		Fri Jan  4 16:46:30 EDT 1989
	CONTENTS:	main()
	REVISION:
		Tue Nov  6 10:56:34 EST 1990
	    Add graphics routines into Mickey.
		Mon Nov 12 11:09:02 EST 1990
	    Change the structure of using graphics.
		Fri Nov 16 14:20:40 EST 1990
	    The one-route nets are not stored in analog circuits.
		Tue Nov 20 18:03:29 EST 1990
	    Remove the functions for external storage.
		Fri Nov 23 20:40:15 EST 1990
	    Add graphics routine after all routes are generated for
	    all nets.
		Tue Nov 27 17:42:58 EST 1990
	    Change the code so that the specifications for matching
	    nets will be in a different file. Also, remove analog_
	    read_one_net from the program. Now use read_one_net for
	    both digital and analog circuits.
		Fri Dec  7 14:38:35 EST 1990
	    Rewrite the code for the match of analog nets.
		Tue Jan 29 17:30:07 EST 1991
	    Reset net type each time a net is read in.
		Thu Jan 31 10:41:24 EST 1991
	    Rearrange the code so that the function generating common
	    points is completely separated from the others.
		Tue Mar  5 11:01:40 EST 1991
	    Change fopen and fclose to TWOPEN and TWCLOSE,
	    respectively.
		Thu May 23 18:45:25 EDT 1991
	    Add function call to find_special_routes().

----------------------------------------------------------------- */

#include <define.h>
#define  MAIN_VARS
#include <gg_router.h>
#undef   MAIN_VARS
#include <dgraph.h>
#include <macros.h>
#include <analog.h>
#include <yalecad/file.h>
#include <yalecad/cleanup.h>

#define EXPECTEDMEMORY (4096*1024)

int mlen;
int Mlen;
int alen;
int iteration_limit;
int *Apins;
int *routes;

extern BOOLEAN init_info();
extern BOOLEAN read_one_net();
extern void store_route();
extern void assign_net_internal();
extern void output_route();
extern void random_interchange();
extern void analog_random_interchange();
extern void analog_common_point();
extern void analog_match();
extern void analog_func();
extern void find_special_routes();

main(argc, argv)
    int argc;
    char **argv;
{

    int i;
    int status;

    /* ********************** start initialization ******************* */
    /* start up the cleanup handler */
    YINITCLEANUP(argv[0], NULL, MAYBEDUMP);

    Yinit_memsize(EXPECTEDMEMORY);

#ifdef DEBUG
    YdebugMemory(TRUE);
#endif

    verboseG = FALSE;
    if (init_info(argc, argv, routes, Apins) == FALSE)
    {
	YexitPgm(GP_FAIL);
    }

    /***********************************************************
    * Initialize parameters:
    * 	numnets --- the number of nets in the circuit
    * 	mlen --- the minimum length of the routes of a net
    *	Mlen --- the maximum length of the routes of a net
    *	alen --- the average length of the routes of a net
    ***********************************************************/
    numnets =
    mlen =
    Mlen =
    alen = 0;

    /***********************************************************
    * Read the channel graph from cktName.mgph and cktName.mrte
    ***********************************************************/
    read_graph();

    /***********************************************************
    * Generate a shortest path tree for each of the vertices in
    * the channel graph.
    ***********************************************************/
    generate_path_tree();

    /***********************************************************
    * Make a copy of the channel graph and the shortest path
    * trees for fast retrieve.
    ***********************************************************/
    duplicate_node_edge();

    /***********************************************************
    * Initialize graphics setup.
    ***********************************************************/
    if (graphicsG)
    {
	G(init_graphics(argc, argv, 0));
    }

    /***********************************************************
    * Read a net at one time and find NUMROUTES(= 32) shortest
    * routes for it.
    ***********************************************************/
    status = DIGITAL;
    fin = FOPEN("mtwf","r");
    while (read_one_net(fin))
    {
	/***********************************************************
	* Collect the pin distribution of the net.
	***********************************************************/
	if (numpins < 50)
	{
	    Apins[numpins]++;
	}
	else
	{
	    Apins[50]++;
	}

	numnets++;
	if (COMMON_POINT != FALSE)
	{
	    /*****************************************************
	    * The net requires one or more common points. Its
	    * routes are found by calling the function
	    * analog_common_point.
	    *****************************************************/
	    analog_common_point();
	}
	else
	{
	    generate_pin_graph();
	    if (one_channel_net() == FALSE)
	    {
		if (numpins == 2)
		{
		    two_pin_tree();
		}
		else
		{
		    steiner_tree();
		}
	    }
	    store_route();
	    /*********************************************************
	    * Check parasitic constrains for analog circuits.
	    *********************************************************/
	    if (DIGITAL == FALSE && COMMON_POINT == FALSE)
	    {
		analog_func();
	    }
	}
	routes[numtrees]++;
	restore_node_edge();
    }
    TWCLOSE(fin);

    DIGITAL = status;

    /***********************************************************
    * Print the final statistics on routes of all nets.
    ***********************************************************/
    output(routes, Apins);

    /***********************************************************
    * Read the directed polar graphs.
    ***********************************************************/
    read_dgraph();

    /***********************************************************
    * Read pin information from cktName.mtwf.
    ***********************************************************/
    read_pin_list();

    /***********************************************************
    * Find empty rooms and make lists of them.
    ***********************************************************/
    find_empty_room();

    /***********************************************************
    * Free the memory used in generating multiple routes for the
    * nets.
    ***********************************************************/
    free_mem();

    /***********************************************************
    * Make an array for the net list which is a linked list for
    * quick access.
    ***********************************************************/
    assign_net_internal();

    /***********************************************************
    * Check routes for constraints if it is an analog circuit.
    ***********************************************************/
    if (DIGITAL == FALSE)
    {
	char fname[256];

	/***********************************************************
	* Check if the file ckt.mtch exists. If so, there exist nets
	* to be matched.
	***********************************************************/
	(void) sprintf(fname, "%255s.mtch", cktName);
	if ((fin = TWOPEN(fname, "r", ABORT)) != NULL)
	{
	    analog_match();
	    TWCLOSE(fin);
	}
    }

    /***********************************************************
    * Scan through all the routes to find and process special
    * routes.
    ***********************************************************/
    find_special_routes();

    /***********************************************************
    * Stage II: Minimization of the chip area or the overflow of
    * channel densities.
    *	CASE = 1 --- first objective function, minimization
    * 		of the chip area.
    *	CASE = 2 --- second objective function, minimization
    * 		of the overflow of channel densities.
    ***********************************************************/
    if (DIGITAL != FALSE)
    {
	random_interchange(iteration_limit);
    }
    else
    {
	analog_random_interchange(iteration_limit);
    }

    /***********************************************************
    * Write the final solution to file ckt.gpyt.
    ***********************************************************/
    output_route();

    if (CASE == 2 && total_cost > 0)
    {

	fprintf(fdat, "\nResidual overlap by channel\n");
	fprintf(fdat, "---------------------------\n");
	/***********************************************************
	* dump the overflow
	***********************************************************/
	for (i = 1; i <= numedges; i++)
	{
	    if (dearray[i]->weight > 0)
	    {
		fprintf(fdat, "channel: %d %d overflow %d\n",
			dearray[i]->f_vertex,
			dearray[i]->t_vertex,
			dearray[i]->weight);
	    }
	}
	fflush(fdat);
    }

    if (verboseG)
    {
	Yprint_stats(stdout);
    }
    Yprint_stats(fdat);


    PRINT(stdout, "\n\n");
    fflush(stdout);
    fprintf(fdat, "\n\n");
    fflush(fdat);
    TWCLOSE(fdat);
    Ysafe_free((char *) routes);
    Ysafe_free((char *) Apins);

    YexitPgm(GP_OK);

} /* end of main */
