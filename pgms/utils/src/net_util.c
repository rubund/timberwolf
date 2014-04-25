/* ----------------------------------------------------------------- 
FILE:	    net_util.c                                       
DESCRIPTION:Program for converting the output of the circuitName.pth
    file to the input format of the circuitName.net file.  It is useful
    when the user wants each net in the netlist to be a path.
CONTENTS: 
DATE:	    Mar 31, 1989 - Original coding.
REVISIONS:  Wed Mar 13 16:07:32 CST 1991 - updated for new
		.pth format.
	    Sun Apr 21 21:42:27 EDT 1991 - updated directions and
		now use library. Also accept ignore keyword.
----------------------------------------------------------------- */
#ifndef lint
static char SccsId[] = "@(#) net_util.c (Yale) version 1.3 4/21/91" ;
#endif

#include <yalecad/base.h>
#include <yalecad/file.h>
#include <yalecad/string.h>

#define  NETKEYWORD "net"

main( argc , argv )
int argc ;
char *argv[] ;
{
    FILE *fin, *fout ;
    char buffer[LRECL], *bufferptr = buffer ;
    char **tokens ;     /* for parsing menu file */
    char filename[LRECL] ;
    char filename2[LRECL] ;
    int  numtokens ;
    int lowerBound, upperBound ;
    int line = 0 ;
    int onOrOff ;

    if( argc != 5 ) {
	fprintf( stderr, "net_util usage:\n\tnet_util circuitName " ) ;
	fprintf( stderr, "lowerBound upperBound {1|0}<CR>\n") ;
	fprintf( stderr, "\nwhere\n\tlowerBound and upperBound are " ) ;
	fprintf( stderr, "integers indicating\n\tpathlength and ") ;
	fprintf( stderr, "1 and 0 denote whether paths are on (1)\n\tor ") ;
	fprintf( stderr, "whether they are just measured (0).\n\n" ) ;
	fprintf( stderr, "Example:\n" ) ;
	fprintf( stderr, "\tnet_util stdcell 0 100 0\n\n\n" ) ;
	exit(1);
    }

    lowerBound = atoi( argv[2] ) ;
    upperBound = atoi( argv[3] ) ;
    onOrOff = atoi( argv[4] ) ;
    if( onOrOff !=0 && onOrOff != 1 ){
	fprintf( stderr, "Bogus value for on/off value:%d\n", onOrOff ) ;
	exit(1);
    }

    /* read path file to get net information */
    sprintf( filename, "%s.pth", argv[1] ) ;
    fin = TWOPEN( filename, "r", ABORT ) ;

    /* open net.new file for writing */
    sprintf( filename, "%s.net", argv[1] ) ;
    if( YfileExists( filename ) ){
	sprintf( filename2, "%s.net.old", argv[1] ) ;
	YmoveFile( filename, filename2 ) ;
    }
    fout = TWOPEN( filename, "w", ABORT ) ;

    while( bufferptr=fgets(buffer,LRECL,fin )){
	line++ ; 
	tokens = Ystrparser( bufferptr, " :\t\n", &numtokens ); 
	if( numtokens == 0 ){ 
	    /* skip over empty lines */ 
	    continue ; 
	} else if( strcmp( tokens[0], NETKEYWORD ) == STRINGEQ){ 
	    /* look at first field for menu keyword */ 
	    /* there better be only eleven tokens on this line */ 
	    if( numtokens != 11 && numtokens != 12 ){ 
		fprintf( stderr, "Syntax error on line:%d\n", line ) ;
		continue ;
	    } 
	    if( numtokens == 11 ){
		fprintf( fout, "path %s : %d %d %d\n",
		    tokens[2], lowerBound, upperBound, onOrOff ) ;
	    }
	}
    }
    TWCLOSE( fin ) ;
    TWCLOSE( fout ) ;
} /* end main */
