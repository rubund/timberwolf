/* ----------------------------------------------------------------- 
FILE:	    main.c
DESCRIPTION:This file contains main control routine for the mighty  
	    draw input and output program.
CONTENTS:   
DATE:	    July 4, 1989 
REVISIONS:  
----------------------------------------------------------------- */
#ifndef lint
static char SccsId[] = "@(#) main.c (Yale) version 1.1 12/16/89" ;
#endif

#define MAIN_VARS

#include <stdio.h>
#include <signal.h>
#include <yalecad/base.h>
#include <yalecad/cleanup.h>
#include <yalecad/file.h>
#include <yalecad/message.h>
#include <yalecad/string.h>
#include <yalecad/debug.h>
#include <yalecad/wgraphics.h>
#include <globals.h>

#define EXPECTEDMEMORY  (1024 * 1024)  /* 1M should be enough */
#define UTIL  "draw_input"
#define VERSION  "v1.0"

main( argc , argv )
int argc ;
char *argv[] ;
{

    char *YinitProgram(), *Ystrclone() ;
    char filename[LRECL] ;
    int  yaleIntro() ;
    FILE *in, *out ;
    BOOL debug ;
    BOOL magnify ;
    char *ptr ;

    /* start up cleanup handler */
    YINITCLEANUP( argv[0], NULL, MAYBEDUMP ) ;

    Yinit_memsize( EXPECTEDMEMORY ) ;

    if( argc < 2 || argc > 6 ){
	syntax() ;
    } else {
	debug       = FALSE ;
	magnify     = FALSE ;
	maG = 10.0 ;
	out = NULL ;
	if( *argv[1] == '-' ){
	    for( ptr = ++argv[1]; *ptr; ptr++ ){
		switch( *ptr ){
		case 'd':
		    debug = TRUE ;
		    break ;
		case 'm':
		    magnify = TRUE ;
		    break ;
		default:
		    sprintf( YmsgG,"Unknown option:%c\n", *ptr ) ;
		    M(ERRMSG,"main",YmsgG);
		    syntax() ;
		}
	    }
	    YdebugMemory( debug ) ;
	    YinitProgram( "draw_route", VERSION, yaleIntro );

	    /* now tell the user what he picked */
	    M(MSG,NULL,"\n\nTimberWolfMC switches:\n" ) ;
	    if( debug ){
		YsetDebug( TRUE ) ;
		M(MSG,NULL,"\tdebug on\n" ) ;
	    } 
	    if( magnify ){
		M(MSG,NULL,"\tTimberWolfMC will magnify window\n" ) ;
		/* look for windowid */
		if( argc == 4 ){
		    maG = atof( argv[3] ) ;
		} else if( argc == 5 ){
		    maG = atof( argv[4] ) ;
		    out = TWOPEN( argv[3], "r", ABORT ) ;
		} else {
		    M(ERRMSG,"main","Need to specify magnification\n" ) ;
		    syntax() ;
		} 
		fprintf( stderr,"Magnification set to %f\n", maG ) ;
	    }
	    M(MSG,NULL,"\n" ) ;
	   
	    /* mighty input file name */
	    in = TWOPEN( argv[2], "r", ABORT ) ;
	    
	} else if( argc == 2 ){
	    /* order is important here */
	    YdebugMemory( FALSE ) ;
	    YinitProgram( "draw_route", VERSION, yaleIntro );
	    
	    /* mighty input file name */
	    in = TWOPEN( argv[1], "r", ABORT ) ;

	} else if( argc == 3 ){
	    /* order is important here */
	    YdebugMemory( FALSE ) ;
	    YinitProgram( "draw_route", VERSION, yaleIntro );
	    
	    /* mighty input file name */
	    in = TWOPEN( argv[1], "r", ABORT ) ;
	    out = TWOPEN( argv[2], "r", ABORT ) ;

	} else {
	    syntax() ;
	}
    }
    /* ********************** end initialization ************************* */

    /* we can change this value in the debugger */
    YdebugMemory( FALSE ) ;

    TWinitGraphics( NULL,TWstdcolors(),TWnumcolors(), 1,"./DATA",NULL) ;
    TWstartFrame() ;

    process_input( in ) ;
    if( out ){
	process_output( out ) ;
	TWCLOSE( out ) ;
    }

    TWCLOSE( in ) ;
    TWflushFrame() ;
    TWcloseGraphics() ;

    system( "draw" ) ;

    YexitPgm( PGMOK ) ;

} /* end main */

/* give user correct syntax */
syntax()
{
   M(ERRMSG,NULL,"\n" ) ; 
   M(MSG,NULL,"Incorrect syntax.  Correct syntax:\n");
   sprintf( YmsgG, 
       "\n%s [-dm] mightyInputFile [mightyOutputFile] [magnification]\n\n", UTIL );
   M(MSG,NULL,YmsgG ) ; 
   YexitPgm(PGMFAIL);
} /* end syntax */

yaleIntro() 
{
    int i ;

    M( MSG, NULL, YmsgG) ;
    M( MSG, NULL, "         Mighty Draw Utility\n");
    M( MSG, NULL, "         Yale University\n");
    M( MSG, NULL, "\n");

} /* end yaleIntro */
