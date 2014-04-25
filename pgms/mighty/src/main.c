#ifndef lint
static char SccsId[] = "@(#) main.c version 6.2 10/14/90" ;
#endif


#define MAIN
#include "mighty.h"
#include <yalecad/cleanup.h>
#include <yalecad/message.h>
#include <signal.h>
#undef MAIN
extern SEARCHPTR *searchq;
extern int MODCOST;
extern int addguideG ;

/************************************************************************
 *
 * This is the main routine for mighty 
 *
 ************************************************************************/


main (argc, argv)
int argc;			/* argc and argv are used to get
				   information from the command line */
char *argv[];
{
    int num_box;
    NETPTR S_input();
    void S_markborder();
    void S_route();
    void S_rmpins();
    void S_maxmetal();
    void S_connectboundary();
    void S_printstandard();
    void print_channel ();
    void S_printsq();
    void S_printstats();
    CHANNELPTR allocate_channel ();
    LINKLISTPTR **allocate_linklayer ();
    int **allocate_hist ();
    int yaleIntro() ;
    SEARCHPTR *allocate_searchq ();

    YINITCLEANUP( argv[0], FALSE, MAYBEDUMP ) ;
    /*
     *  process command line
     */
    command_line(argc, argv) ;
    if( debugG ){
	YdebugMemory( TRUE ) ;
    }
    YinitProgram("TimberWolfDR : detailed router","2.0", yaleIntro ) ;
    failedRouteG = FALSE ;

    /*
     * See if there was a problem opening files
     */
    
    if (input_fileG== (FILE *)NULL || output_fileG== (FILE *)NULL
		|| result_fileG== (FILE *)NULL)
    {
	fprintf(output_fileG,"Problem opening files!\n");
	YexitPgm(1);
    }

    /*
     *  read input
     */

    net_arrayG = S_input ( &num_netsG, &num_box, &num_rowsG, &num_colsG,
			&num_obstaclesG, &num_pinsG );
    
    /*
     * Check for bogus input
     */
    if (num_netsG==0 || num_colsG==0)
    {
	fprintf(output_fileG,"Bogus input: No nets or no cols!\n");
	YexitPgm(1);
    }


    /*
     *  allocate memory for the channel and cost matrix
     */

    channelG = allocate_channel (num_rowsG, num_colsG);
    hlayerG = channelG->horiz_layer;
    vlayerG = channelG->vert_layer;
    playerhG = channelG->pin_layerh;
    playervG = channelG->pin_layerv;

    /*
     *  allocate memory for the link layer
     */

    linklayerG = allocate_linklayer (num_rowsG, num_colsG);

    /*
     *  allocate memory for the seachq
     */

    searchq = allocate_searchq (MODCOST);

    /*
     *  allocate memory for the history
     */

    historyG = allocate_hist (num_netsG);

    /*
     *  Mark obstacles before routing
     */
    S_markborder();

    /*
     *  switch box routing
     */
    S_route() ;

    if( addguideG || addpseudoG ) S_rmpins();

    if (maximize_metalG)
    {
	S_maxmetal();
    }
    S_output_routing() ;

    if( failedRouteG ){
	YexitPgm( 1 );
    } else {
	YexitPgm( 0 );
    }
}


yaleIntro()
{

    M( MSG, NULL, YmsgG ) ;
    M( MSG, NULL, "\nYale University version\n");
    M( MSG, NULL, "Original Authors:");
    M( MSG, NULL, " H. Shin and A. Sangiovanni-Vincentelli - UCB\n");

} /* end yaleIntro */

S_output_routing()
{
    /*
     *  connect to the pins on the boundary
     */
    S_connectboundary();

    if (stats_onlyG == FALSE) {
	S_printstandard();
	if( debugG ){
	    print_channel (channelG, num_rowsG, num_colsG, num_netsG);
	}
    } else {
	S_printstats();
    }
} /* end S_output_routing */
