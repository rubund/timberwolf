/* ----------------------------------------------------------------- 
FILE:	    main.c                                       
DESCRIPTION:Main routine for drawing program.
CONTENTS:   main( argc, argv )
		int	argc;
		char *argv[];
DATE:	    Jan 25, 1989 - major rewrite of version 1.0
REVISIONS:  Mon May  6 22:39:16 EDT 1991 - added TWsetFrame to 
		add to end of frames rather than start.
----------------------------------------------------------------- */
#ifndef lint
static char SccsId[] = "@(#) main.c version 3.5 5/6/91" ;
#endif

#include <stdio.h>
#include "globals.h"
#include <yalecad/program.h>
#include <yalecad/cleanup.h>
#include <yalecad/file.h>

#define DRAW  "draw"
#define EXPECTEDMEMORY  256 * 1024

main( argc , argv )
int argc ;
char *argv[] ;
{

    char design[LRECL] ;
    char filename[LRECL] ;
    char *twdir ;
    char *Ygetenv() ;

    /* start up cleanup handler */
    YINITCLEANUP( "config", NULL, MAYBEDUMP ) ;

    Yinit_memsize( EXPECTEDMEMORY ) ;

    fprintf( stdout, "%s\n\n",YinitProgram("drawTW","v1.0",NULL ) ) ;

    if( argc < 2 ){
       M(ERRMSG,"main","Incorrect syntax.  Correct syntax:\n");
       M(MSG,NULL,"             drawTW [-pl2] designName\n\n");
       YexitPgm( PGMFAIL ) ;
    }

    if( *argv[1] == '-' ){
	sprintf( design,"%s",argv[2] );
	sprintf( filename, "%s.pl2", design);
    } else {
	sprintf( design,"%s",argv[1] );
	sprintf( filename, "%s.pl1", design);
    }
    if(!(twdir = Ygetenv( "TWDIR" ) )){
	M( ERRMSG,"main","ERROR:TWDIR environment variable not set.\n" );
	M( MSG, NULL, "Please set it to the TimberWolf root directory\n");
	YexitPgm( PGMFAIL ) ;
    }

    if(!(TWinitGraphics(argc,argv,TWnumcolors(),TWstdcolors(),
	MENU, draw_the_data ))){
	M(ERRMSG,"main","Problem with graphics. FATAL\n\n");
	YexitPgm( PGMFAIL ) ;
    }
    TWsetFrame( 0 ) ;

    /* determine whether we have an SC run or MC */
    /* SC has priority */
    if( YfileExists(filename) ){
	drawSC(design,filename) ;

    } else {
	sprintf( filename, "%s.dat", design);
	if( YfileExists(filename) ){
	    drawMC(design) ;
	}
    }

    TWcloseGraphics() ;


    /* call draw program */
    sprintf( filename, "%s/bin/draw", twdir ) ;
    Ysystem( "draw", ABORT, filename, NULL ) ;

    YexitPgm( PGMOK ) ;

}  

