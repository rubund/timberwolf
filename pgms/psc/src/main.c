/* ----------------------------------------------------------------- 
FILE:	    main.c
DESCRIPTION:
CONTENTS:   
DATE:	    Mon Feb 18 00:08:29 EST 1991
REVISIONS:  Thu Mar  7 02:51:35 EST 1991 - added check_jobs_initially.
	    Sun Apr 21 21:46:44 EDT 1991 - changed arguments to program.
----------------------------------------------------------------- */
#ifndef lint
static char SccsId[] = "@(#) main.c (Yale) version 1.4 4/21/91" ;
#endif

#define GLOBALS_DEFS

#include <stdio.h>
#include <yalecad/base.h>
#include <yalecad/string.h>
#include <yalecad/debug.h>
#include <yalecad/cleanup.h>
#include <yalecad/message.h>
#include <globals.h>

#define EXPECTEDMEMORY   (128 * 1024)
#define VERSION          "v1.0"
#define PROGRAM          "PSC"

main( argc , argv )
INT argc ;
char *argv[] ;
{

    BOOL parasite ;         /* is it a parasite ??? */
    INT  windowId ;         /* parasite window id */
    INT  arg_count ;        /* count of arguments */
    char *ptr ;             /* current argument */
    VOID yaleIntro()  ;     /* the Yale intro */

    int status ;
    int j ;
    int pid, pid1, pid2 ;
    int count ;
    char **argv1 ;
    char **argv2 ;

/* #define DEBUGX */
#ifdef DEBUGX
    extern int _Xdebug ;
    _Xdebug = TRUE ;
#endif


    /* start up cleanup handler */
    YINITCLEANUP( argv[0], NULL, MAYBEDUMP ) ;

    Yinit_memsize( EXPECTEDMEMORY ) ;
    flow_dirG = NIL(char *) ;

    if( argc < 3 || argc > 5 ){
	syntax() ;
    } else {
	debugG    = FALSE ;
	verboseG  = FALSE ;
	parasite  = FALSE ;
	windowId  = 0 ;
#ifndef NOGRAPHICS
	graphicsG = TRUE ;
#else /* NOGRAPHICS case */
	graphicsG = FALSE ;
#endif /* NOGRAPHICS */
	arg_count = 1 ;
	if( *argv[1] == '-' ){
	    for( ptr = ++argv[1]; *ptr; ptr++ ){
		switch( *ptr ){
		case 'd':
		    debugG = TRUE ;
		    break ;
		case 'n':
		    graphicsG = FALSE ;
		    break ;
		case 'v':
		    verboseG = TRUE ;
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
	    YdebugMemory( debugG ) ;

	    cktNameG = Ystrclone( argv[++arg_count] );
	    Ymessage_mode( verboseG ) ;

	    YinitProgram( PROGRAM, VERSION, yaleIntro );

	    /* now tell the user what he picked */
	    M(MSG,NULL,"\n\nPSC switches:\n" ) ;
	    if( debugG ){
		YsetDebug( TRUE ) ;
		M(MSG,NULL,"\tdebug on\n" ) ;
	    } 
	    if( verboseG  ){
		M(MSG,NULL,"\tMessages will be redirected to screen\n" ) ;
	    }
	    if( graphicsG ){
		M(MSG,NULL,"\tGraphics mode on\n" ) ;
	    } else {
		M(MSG,NULL,"\tGraphics mode off\n" ) ;
	    }
	    if( parasite ){
		M(MSG,NULL,"\tPSC will inherit window\n" ) ;
		/* look for windowid */
		if(argc < 4){
		    M(ERRMSG,"main","Need to specify windowID\n" ) ;
		    syntax() ;
		} else {
		    G( windowId = atoi( argv[++arg_count] ) ) ;
		} 
	    }
	    M(MSG,NULL,"\n" ) ;
	} else if( argc == 3 ){
	    /* order is important here */
	    YdebugMemory( FALSE ) ;
	    cktNameG = Ystrclone( argv[arg_count] );
	    YinitProgram( PROGRAM, VERSION, yaleIntro );
	} else {
	    syntax() ;
	}
	if( ++arg_count < argc ){
	    /* this means we have the flow directory specified */
	    flow_dirG = Ystrclone( argv[arg_count] ) ;
	    sprintf( YmsgG, "\n\tFlow directory given:%s\n\n", flow_dirG );
	    M( MSG,NULL, YmsgG ) ;
	}
    }
    /* ********************** end initialization ********************* */
    build_node_tree() ;

    find_partitions() ;

    alloc_jobs() ;

    check_jobs_initially() ;

    G( init_graphics( argc, argv, windowId  ) ) ;
    G( process_graphics() ) ;

    closegraphics() ;
    YexitPgm( PGMOK ) ;

} /* end main */

/* give user correct syntax */
syntax()
{

   M(ERRMSG,NULL,"\n" ) ; 
   M(MSG,NULL,"Incorrect syntax.  Correct syntax:\n");
   sprintf( YmsgG, "\n%s [-dnvw] designName [windowId] flowDirectory\n",
       PROGRAM );
   M(MSG,NULL,YmsgG ) ; 
   M(MSG,NULL,"\twhose options are one or more of the following:\n");
   M(MSG,NULL,"\t\td - prints debug info and performs extensive\n");
   M(MSG,NULL,"\t\t    error checking\n");
   M(MSG,NULL,"\t\tn - no graphics - the default is to open the\n");
   M(MSG,NULL,"\t\t    display and output graphics to an Xwindow\n");
   M(MSG,NULL,"\t\tv - verbose mode - echos to the screen\n");
   M(MSG,NULL,"\t\tw - parasite mode will inherit a window. Requires\n");
   M(MSG,NULL,"\t\t    a valid windowId\n");
   YexitPgm(PGMFAIL);
} /* end syntax */

VOID yaleIntro() 
{
    int i ;

    M( MSG, NULL, "\n") ;
    M( MSG, NULL, YmsgG) ;
    M( MSG, NULL, "\nParallel SCheduler\n");
    M( MSG, NULL, "Authors: Carl Sechen, Bill Swartz,\n");
    M( MSG, NULL, "         Yale University\n");
    M( MSG, NULL, "\n");

} /* end yaleIntro */
