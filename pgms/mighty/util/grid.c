/* ----------------------------------------------------------------- 
FILE:	    main.c
DESCRIPTION:This file contains main control routine for the utility  
	    program.
CONTENTS:   
DATE:	    May 11, 1989 
REVISIONS:  
----------------------------------------------------------------- */
#ifndef lint
static char SccsId[] = "@(#) grid.c (YALE) version 1.1 12/16/89" ;
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

#define EXPECTEDMEMORY  (1024 * 1024)  /* 1M should be enough */
#define UTIL  "mighty.util"
#define XOFFSET  51
#define GRIDX    2 

main( argc , argv )
int argc ;
char *argv[] ;
{

    char *YinitProgram(), *Ystrclone() ;
    char filename[LRECL] ;
    int  yaleIntro() ;
    FILE *in, *out ;

    /* start up cleanup handler */
    YINITCLEANUP( argv[0], NULL, MAYBEDUMP ) ;

    Yinit_memsize( EXPECTEDMEMORY ) ;

    if( argc != 2 ){
	syntax() ;
    }

    sprintf( filename, "%s", argv[1] ) ;
    in = TWOPEN( filename, "r", ABORT ) ;

    sprintf( filename, "%s.new", argv[1] ) ;
    out = TWOPEN( filename, "w", ABORT ) ;

    /* we can change this value in the debugger */
    YdebugMemory( FALSE ) ;
    YinitProgram( UTIL,"v1.0",yaleIntro) ;

    process_data( in, out ) ;

    TWCLOSE( in ) ;
    TWCLOSE( out ) ;

    YexitPgm( PGMOK ) ;

} /* end main */


/* give user correct syntax */
syntax()
{
   M(ERRMSG,NULL,"\n" ) ; 
   M(MSG,NULL,"Incorrect syntax.  Correct syntax:\n");
   sprintf( YmsgG, 
       "\n%s circuitName\n\n", UTIL );
   M(MSG,NULL,YmsgG ) ; 
   YexitPgm(PGMFAIL);
} /* end syntax */

yaleIntro() 
{
    int i ;

    M( MSG, NULL, YmsgG) ;
    M( MSG, NULL, "         Mighty Utility\n");
    M( MSG, NULL, "         Yale University\n");
    M( MSG, NULL, "\n");

} /* end yaleIntro */
	
#define	RECTKEYWORD   "rectagoncorners"
#define	RECTLEN        15
#define	PINKEYWORD    "number_of_pins"
#define PINLEN         14

process_data( in, out )
FILE *in, *out ;
{
    int i ;                        /* loop counter */
    int x, y ;                     /* position */
    int numcorners ;               /* number of points for figure */
    int numpins ;                  /* number pins */
    char filename[LRECL] ;         /* name of the file */
    char buffer[LRECL] ;           /* character buffer */
    char *bufferptr ;              /* character pointer */
    char **tokens ;                /* used for parsing mdat file */
    int numtokens ;                /* number of tokens found on the line*/

    while( bufferptr=fgets(buffer,LRECL,in )){

	if( strncmp( bufferptr, RECTKEYWORD, RECTLEN) == STRINGEQ ){
	    tokens = Ystrparser( bufferptr, " \t\n", &numtokens );
	    ASSERTNCONT( numtokens == 2, NULL, "unexpected numtokens\n");
	    numcorners = atoi( tokens[1] ) ;
	    fprintf( out, "%s %d\n", RECTKEYWORD, numcorners ) ;

	    /* now process all the points of the figure */
	    for( i=1; i <= numcorners ; i++ ){
		bufferptr=fgets(buffer,LRECL,in ) ;
		ASSERTNCONT( bufferptr, "process_data", "ptr NULL\n");
		tokens = Ystrparser( bufferptr," \t\n", &numtokens );
		ASSERTNCONT( numtokens == 2,"process_data","prblm\n");

		x = atoi( tokens[0] ) ;
		y = atoi( tokens[1] ) ;
		fprintf( out, "%d %d\n", opX( x ), opY( y ) ) ;

	    } /* end for loop */

	} else if( strncmp( bufferptr, PINKEYWORD, PINLEN ) == STRINGEQ){
	    tokens = Ystrparser( bufferptr, " \t\n", &numtokens );
	    ASSERTNCONT( numtokens == 2, NULL, "unexpected numtokens\n");
	    numpins = atoi( tokens[1] ) ;

	    fprintf( out, "%s %d\n", PINKEYWORD, numpins ) ;

	    /* now process all the points of the figure */
	    for( i=1; i <= numpins ; i++ ){
		bufferptr=fgets(buffer,LRECL, in ) ;
		ASSERTNCONT( bufferptr, "process_data", "ptr NULL\n");
		tokens = Ystrparser( bufferptr," \t\n", &numtokens );
		ASSERTNCONT( numtokens == 4,"process_data","prblm\n");

		x = atoi( tokens[1] ) ;
		y = atoi( tokens[2] ) ;
		fprintf( out, "%s %d %d %s\n", tokens[0],
		    opX( x ), opY( y ), tokens[3] ) ;


	    } /* end for loop */

	}  else {
	   /* echo to output */
	   fprintf( out, "%s", bufferptr ) ;
	}

    } /* end while loop */
		
} /* end process_data */

int opX( x )
int x ;
{
    x -= XOFFSET ;
    x /= GRIDX ;
    x++ ;
    return( x ) ;

} /* opX */

int opY( y )
int y ;
{
    return( y ) ;
} /* opY */
