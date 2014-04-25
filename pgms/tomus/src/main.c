/* ----------------------------------------------------------------- 
FILE:	    main.c                                       
DESCRIPTION:Partitioner's main function.
CONTENTS:   main( argc , argv )
		int argc ;
		char *argv[] ;
DATE:	    Jan 26 , 1990 
REVISIONS:  Sun Apr  7 03:08:45 EDT 1991 - no need to call genrows
		if partitioning is no performed.
	    Thu Apr 18 01:15:50 EDT 1991 - now state tomus must
		use graphics.
----------------------------------------------------------------- */
#ifndef lint
static char SccsId[] = "@(#) main.c (YALE) version 1.17 4/21/91" ;
#endif

#include <string.h>
#include <yalecad/cleanup.h>
#include <yalecad/file.h>
#include <yalecad/message.h>
#include <yalecad/string.h>

#define MAIN_VARS  
#include "standard.h"
#include "main.h"
#include "parser.h"

#define PROGRAM          "Tomus"
#define GENROWPROG       "genrows"
#define VERSION          "v2.0"
#define EXPECTEDMEMORY   (1024 * 1024)
#define DO_PARTITION    "DO YOU WISH TO PARTITION THE DESIGN?"
#define REDOPARTS       "DO YOU WISH TO RECONFIGURE PARTITIONS?"

extern int tot_clen ;

main( argc , argv )
int argc; 
char *argv[] ;
{


FILE *fp ;
double old_cpu , Ycpu_time();
char filename[LRECL],ans[2],command[LRECL] ;
char filename2[LRECL] ;
char *twdir, *Ygetenv() ; 
char *ptr ;               /* parse the options */
int i;
INT windowId ;            /* the window id if its a parasite */
INT arg_count ;           /* used to parse input command line */
INT yaleIntro() ;
BOOL debug ;              /* TRUE if debug is on */
BOOL verbose ;            /* send messages to screen */
BOOL parasite ;           /* TRUE if we are to take over the graphics */
BOOL more_parts;          /** TRUE if the user need to refine merged
				partitions**/


/* ********************** start initialization *********************** */
/* start up cleanup handler */
YINITCLEANUP( argv[0], NULL, MAYBEDUMP ) ;

Yinit_memsize( EXPECTEDMEMORY ) ;

if( argc < 2 || argc > 4 ){
    syntax() ;
} else {
    debug      = FALSE ;
    parasite   = FALSE ;
    verbose    = FALSE ;
    windowId   = 0 ;
    arg_count = 1 ;
#ifndef NOGRAPHICS
   doGraphicsG = TRUE ;
#else /* NOGRAPHICS case */
   doGraphicsG = FALSE ;
#endif /* NOGRAPHICS */

    if( *argv[1] == '-' ){
	for( ptr = ++argv[1]; *ptr; ptr++ ){
	    switch( *ptr ){
	    case 'd':
		debug = TRUE ;
	        break ;
	    case 'n':
	        doGraphicsG = FALSE ;
	        break ;
	    case 'v':
	        verbose = TRUE ;
	        break ;
	    case 'w':
	        parasite = TRUE ;
	        break ;
	    default:
		sprintf( YmsgG,"Unknown option:%c\n", *ptr ) ;
		M(ERRMSG,"main",YmsgG);
		syntax() ;
	    }
	}
	YdebugMemory( debug ) ;

	cktNameG = Ystrclone( argv[++arg_count] );

	/* now tell the user what he picked */
	M(MSG,NULL,"\n\nTomus switches:\n" ) ;
	if( debug ){
	    YsetDebug( TRUE ) ;
	    M(MSG,NULL,"\tdebug on\n" ) ;
	} 
	if( doGraphicsG ){
	    M(MSG,NULL,"\tGraphics mode on\n" ) ;
	} else {
	    M(MSG,NULL,"\tGraphics mode off; Batch mode\n" ) ;
	    sprintf( filename , "%s.part" , cktNameG ) ;
	    if (!YfileExists(filename)){
	    sprintf( YmsgG,".part file not found for batch mode. Must Exit\n") ;
	    M(ERRMSG,"main",YmsgG);
	    YexitPgm( PGMFAIL ) ;
            }
	   /* sprintf( YmsgG,"Tomus can't operate without graphics; Must Exit\n") ;
	    M(ERRMSG,"main",YmsgG);
	    YexitPgm( PGMFAIL ) ;*/
	}
	if( parasite ){
	    M(MSG,NULL,"\tTomus will inherit window\n" ) ;
	    /* look for windowid */
	    if(argc != 4){
		M(ERRMSG,"main","Need to specify windowID\n" ) ;
		syntax() ;

	    } else {
		windowId = atoi( argv[++arg_count] ) ;
	    } 
	}
	if( verbose ){
	    M(MSG,NULL,"\tVerbose mode on\n" ) ;
	    Ymessage_mode( M_VERBOSE ) ;
	}
	M(MSG,NULL,"\n" ) ;
    } else if( argc == 2 ){
	/* order is important here */
	YdebugMemory( FALSE ) ;
	M(MSG,NULL,"\tGraphics mode on\n" ) ;
	cktNameG = Ystrclone( argv[1] );

    } else {
	syntax() ;
    }
}

/************ The Output file of Partitioner .pout ******************/
sprintf( filename , "%s.pout" , cktNameG ) ;
fpoG = TWOPEN( filename, "w", ABORT ) ;

Ymessage_init( fpoG ) ;  /* send all the messages to a file normally */
YinitProgram( PROGRAM, VERSION, yaleIntro ) ;

/************ The Parameter file of Partitioner .ppar ******************/
readParFile();
/* ********************** end initialization ************************* */

/* inialize variables */
Yset_random_seed( (int) randomSeed ) ; 
fprintf( fpoG, "\nThe random number generator seed is: %u\n\n\n", 
						randomSeed ) ;
fflush( fpoG ) ;

/* clean out partition files */ 
sprintf( filename, "%s:*", cktNameG ) ;
Yrm_files( filename ) ;

/** READing .mver file and awking output from MC  ***/

	sprintf( filename , "%s.mver" , cktNameG ) ;
	fp = TWOPEN( filename , "r" , ABORT ) ;
	readmver( fp ) ;
	TWCLOSE( fp ) ;
	fprintf( fpoG, "\nRead .mver file ");

/*	**** awk the .mdat and .cel file to make .pcel *****/

	if( twdir = Ygetenv( "TWDIR" )){
	    sprintf( command, "awk -f %s/bin/union.a %s.cel", twdir,
		cktNameG ) ;
	} else {
	   M( ERRMSG,NULL,"TWDIR environment variable not set.\n");
	   M( ERRMSG,NULL,"Please set it to TimberWolf root directory\n");
	   YexitPgm( PGMFAIL ) ;
	}
	Ysystem(NULL, ABORT, command, NULL ) ;
	sprintf(command, "awk -f %s/bin/union2.a %s.mdat", twdir,
	    cktNameG ) ;
	Ysystem(NULL, ABORT, command, NULL ) ;

/********************************************************************/
sprintf( filename , "%s.pcel" , cktNameG ) ;
fp = TWOPEN( filename , "r" , ABORT ) ;
readcell( fp ) ;
TWCLOSE( fp ) ;
fprintf( fpoG, "\nRead .pcel file ");

macro_and_pad_fix();

if (doGraphicsG) {

init_draw(argc,argv,windowId) ;

  if(!(query_dialog( DO_PARTITION ))){
    sprintf( filename , "%s.pcel" , cktNameG ) ;
    sprintf( filename2, "%s.scel" , cktNameG ) ;
    YmoveFile( filename, filename2 ) ;
    Yprint_stats(fpoG);
    /* TWCLOSE(fpoG) ; */  /* Handled by Ymessage_close() in YexitPgm() */
    TWcloseGraphics() ;
    YexitPgm( PGMOK ) ;
  }

}

/************ The Net file of Partitioner .net ******************/

sprintf( filename , "%s.net" , cktNameG ) ;
if( fp = TWOPEN( filename , "r" , NOABORT ) ){
    readnets( fp ) ;
    TWCLOSE( fp ) ;
    fprintf( fpoG, "\nRead .net file ");
}
/********************************************************************/

fprintf( fpoG , "\nStatistics:\n");
fprintf( fpoG , "Number of Cells: %d\n", numcellsG );
fprintf( fpoG , "Number of Pads: %d \n", numtermsG );
fprintf( fpoG , "Number of Nets: %d \n", numnetsG ) ;

newmerge();


if (doGraphicsG) {
   draw_the_data("These Are The Partitions You made");
   more_parts = TRUE;
   while (more_parts){
         	more_parts = query_dialog( REDOPARTS );
         	if (more_parts){
         		free_parts(); 
         		newmerge();
         		draw_the_data("These Are The Partitions You made");
         	}
   }
}

draw_tiles();

draw_the_data("These Are The Partition Cut Lines Tomus introduced");


makelegalTiletree();

cluster();

total_tile_areaG = total_part_areaG = tot_clen;

tilepenalC = 5.0;
partpenalC = 0.0;
iterationG = 0 ;

calc_init_timeFactor() ;
funccostG = init_cost();
findcost() ;

if (mono_class_cellsG != numcellsG) {
	strcpy(YmsgG,"Click DRAW Menu for Nets,Cell Clusters etc. and Continue");

if (doGraphicsG){
	init_draw2();
	main_draw( YmsgG ) ;
	TWmessage("Simulated Annealing in Progress...");
}

	printf("\n%s\n",YmsgG);

	fprintf( fpoG, "\n\n\nTHIS IS THE ROUTE COST OF THE ");
	fprintf( fpoG, "INITIAL STATE OF PARTITIONS: %d\n" , funccostG ) ;
	fprintf( fpoG, "\n\n\nTHIS IS THE INITIAL PENALTY: %d\n" , penaltyG ) ;
	fflush( fpoG ) ;

	init_acceptance_rate() ; /* initialize heuristic annealing schedule */

	fflush(fpoG);
	fflush(stdout);

	old_cpu = Ycpu_time();

	utemp() ;
	fflush(stdout);
} else {
	fprintf( fpoG, "\n\n\nANNEALING BEING BYPASSED\n");
	fprintf( fpoG, "AS ALL CELLS HAVE ONE RESTRICTED CLASS ONLY\n") ;
	fflush( fpoG ) ;
}

strcpy(YmsgG,"Global Router in Progress ; Tomus will create PseudoPads");
printf("\n\nPartitioning done and Tomus is ready to split Partitions. \n\n ");

if (doGraphicsG){
	printf("(Select Continue Pgms, when you are ready)\n\n ");
	init_draw2(); 
	main_draw("Partitioning done and Tomus is ready to split Partitions : (Continue) ");
}

printf("\n\n\n%s...\n",YmsgG);
global_route() ;

strcpy(YmsgG,"Tomus will create inputs for Genrows,TimberWolfSC next.");
printf("\n%s\n\n\n\n",YmsgG);

if (doGraphicsG) {
	strcpy(YmsgG,"Select \"Continue Pgms\" from \"CONTROL\" menu when you are ready.");
	printf("\n%s\n\n\n\n",YmsgG);
	init_draw2();  
	main_draw("This shows PseudoPads on the Partition Core Edges (Continue to Create Rows)");
}

output();


if (doGraphicsG) TWcloseGraphics() ;


Yprint_stats(fpoG);
TWCLOSE(fpoG) ;
YexitPgm(PGMOK);
}

/* give user correct syntax */
syntax()
{
   M(ERRMSG,NULL,"\n" ) ; 
   M(MSG,NULL,"Incorrect syntax.  Correct syntax:\n");
   sprintf( YmsgG, 
       "\n%s [-dvw] designName [windowId] \n", PROGRAM ) ;
   M(MSG,NULL,YmsgG ) ; 
   M(MSG,NULL,"\twhose options is zero or more of the following:\n");
   M(MSG,NULL,"\t\td - prints debug info and performs extensive\n");
   M(MSG,NULL,"\t\t    error checking\n");
   M(MSG,NULL,"\t\tv - verbose mode - echo output to the screen\n");
   M(MSG,NULL,"\t\tw - parasite mode - user must specify windowId\n");
   YexitPgm(PGMFAIL);
} /* end syntax */

INT yaleIntro() 
{
    fprintf(fpoG,"\n%s\n",YmsgG) ;
    fprintf(fpoG,"Authors: Kalapi Roy, Carl Sechen\n");
    fprintf(fpoG,"         Yale University\n");

    fprintf(stdout,"\n%s\n",YmsgG) ;
    fprintf(stdout,"Authors: Kalapi Roy, Carl Sechen\n");
    fprintf(stdout,"         Yale University\n");

} /* end yaleIntro */
