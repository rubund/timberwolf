/* ----------------------------------------------------------------- 
FILE:	    readpar.c                                       
DESCRIPTION:read parameter file.
CONTENTS:   readParFile()
	    yaleIntro(message) 
		char *message ;
DATE:	    Mar 27, 1989 
REVISIONS:  Sat Feb 23 01:07:25 EST 1991 - rewrote using library utility
		programs.
----------------------------------------------------------------- */
#ifndef lint
static char SccsId[] = "@(#) readpar.c (Yale) version 1.9 8/5/91" ;
#endif

#include "standard.h"
#include "main.h"
#include "parser.h"
#include <yalecad/file.h>
#include <yalecad/yreadpar.h>
#include <yalecad/message.h>


#define NOTSPECIFIED -1

/* static variables */
static BOOL abortS = FALSE ;
static BOOL readparamS = FALSE ;





static init_read_par();
static readparam();
static process_readpar();
static err_msg(); 





readParFile()
{
    init_read_par() ;
    readparam( PART ) ;
    readparam( USER ) ;
    process_readpar() ;
}

static init_read_par()
{
    vertical_wire_weightG = -1.0 ;
    vertical_path_weightG = -1.0 ;
    /* inialize variables */
    randomSeed  = (unsigned) Yrandom_seed() ;
    attprcel = 0 ;
    track_pitch = -1.0 ; 
    rowSep = -1.0 ;
    rowSepAbs = 0.0 ;
    tw_fast = 0 ;
    tw_slow = 0 ;
}

static readparam( parfile )
INT parfile ;
{

    INT test ;
    INT speed ;
    INT pins ;
    INT spacer_tmp ;
    INT line ;
    INT numtokens ;
    BOOL onNotOff ;
    BOOL wildcard ;
    char **tokens ;
    char *lineptr ;

    Yreadpar_init( cktNameG, parfile, PART, FALSE ) ;

    OUT1( "\n\n" ) ;
    while( tokens = Yreadpar_next( &lineptr, &line, &numtokens, &onNotOff,
	&wildcard )){
	readparamS = TRUE ;
	if( numtokens == 0 ){
	    /* skip over empty lines */
	    continue ;

	} else if( strcmp( tokens[0],"fast") == STRINGEQ ){
	    if( numtokens == 2 ) {
		tw_fast = atoi( tokens[1] ) ;
	    } else {
		err_msg("fast") ;
	    }
	} else if( strcmp( tokens[0],"slow") == STRINGEQ ){
	    if( numtokens == 2 ) {
		tw_slow = atoi( tokens[1] ) ;
	    } else {
		err_msg("slow") ;
	    }
	} else if( strcmp( tokens[0],"vertical_wire_weight") == STRINGEQ ){
	    if( numtokens == 2 ) {
		vertical_wire_weightG = atof( tokens[1] ) ;
	    } else {
		err_msg("vertical_wire_weight") ;
	    }
	} else if( strcmp( tokens[0],"vertical_path_weight") == STRINGEQ ){
	    if( numtokens == 2 ) {
		vertical_path_weightG = atof( tokens[1] ) ;
	    } else {
		err_msg("vertical_path_weight") ;
	    }
	} else if( strcmp( tokens[0],"vertical_path_weight") == STRINGEQ ){
	    if( numtokens == 2 ) {
		vertical_path_weightG = atof( tokens[1] ) ;
	    } else {
		err_msg("vertical_path_weight") ;
	    }
	} else if( strcmp( tokens[0],"random.seed") == STRINGEQ ){
	    if( numtokens == 2 ) {
		randomSeed = (UNSIGNED_INT) atoi( tokens[1] ) ; 
	    } else {
		err_msg("random.seed") ;
	    }
	} else if( strcmp( tokens[0],"rowSep") == STRINGEQ ){
	    if( numtokens == 2 ) {
		rowSep = atof( tokens[1] ) ; 
	    } else if( numtokens == 3 ) {
		rowSep = atof( tokens[1] ) ; 
		rowSepAbs = atof( tokens[2] ) ; 
	    } else {
		err_msg("rowSep") ;
	    }
	} else if(!(wildcard)){
	    if( parfile == USER ){
		OUT4("ERROR[readpar]:unexpected keyword in the %s.par file at line:%d\n\t%s\n", 
		cktNameG, line, lineptr );
	    } else {
		OUT4("ERROR[readpar]:Unexpected keyword in the %s.ppar file at line:%d\n\t%s\n", 
		cktNameG, line, lineptr );
	    }
	    Ymessage_error_count() ;
	    abortS = TRUE ;
	}
    }
} /* end  readparam */

static process_readpar()
{
char *layer ;             /* name of layer */
INT i ;                   /* counter */
INT pitch ;               /* the pitch of the layer */
INT numh_layers ;         /* number of horizontal layers */
INT num_layers ;          /* total number of layers */

if( abortS ){
    OUT1( "Errors found in the .par file.  Must exit\n\n" ) ;
    YexitPgm(PGMFAIL);
}
if( !(readparamS)){
    M( ERRMSG, "process_readpar", 
	"No parameter files found. Must exit\n\n") ;
    YexitPgm(PGMFAIL);
}

if( vertical_wire_weightG < 0 ) {
    fprintf( fpoG, "vertical_wire_weight ") ;
    fprintf( fpoG, "was NOT found in the .ppar file\n");
    YexitPgm(PGMFAIL);
}
if( vertical_path_weightG < 0 ) {
    fprintf( fpoG, "vertical_path_weight ") ;
    fprintf( fpoG, "was NOT found in the .ppar file\n");
    YexitPgm(PGMFAIL);
}

numh_layers = 0 ;
num_layers = Yreadpar_numlayers() ;
for( i = 1; i <= num_layers; i++ ){
    layer = Yreadpar_id2layer( i ) ;
    pitch = Yreadpar_pitch( layer ) ;
    if( Yreadpar_layer_HnotV( layer ) ){
	track_pitch += (DOUBLE) pitch ;
	numh_layers++ ;
    }
}
/* get the average pitch of all the layers */
if( numh_layers > 0 ){
    track_pitch++ ; /* to account for the -1 initialization */
    track_pitch /= numh_layers ;
    if( track_pitch < 1.0 ){
	track_pitch == 1.0 ;
    }
}

if( track_pitch == NOTSPECIFIED ) {
    M( ERRMSG, "readpar",
    "Track pitch could not be calculated from design rules\n");
    M( ERRMSG, NULL, "Check the design rules in parameter file\n\n") ;
    YexitPgm(PGMFAIL);
} else {
    sprintf( YmsgG, "\ntrack_pitch calculated:%4.2f\n\n", track_pitch ) ;
    M( MSG, NULL, YmsgG ) ;
}

macro_clearance = rowHeight;
rowSep = rowSep * rowHeight + rowSepAbs;
return ;
}

static err_msg( keyword ) 
char *keyword ;
{
    OUT2("The value for %s was", keyword );
    OUT1(" not properly entered in the .par file\n");
    abortS = TRUE ;
}/* end err_msg */


