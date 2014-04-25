/* ----------------------------------------------------------------- 
FILE:	    check_status.c
DESCRIPTION:main program for checking running of program.
CONTENTS:   
DATE:	    Mon Feb 18 00:08:29 EST 1991
REVISIONS:  
----------------------------------------------------------------- */
#ifndef lint
static char SccsId[] = "@(#) check_status.c (Yale) version 1.2 3/7/91" ;
#endif

#include <stdio.h>
#include <stdlib.h>
#include "codes.h"

main( argc, argv )
int argc ;
char *argv[] ;
{
    char *directory ;       /* find the directory name */
    char *node ;            /* find the node name */
    char *design ;          /* the design name */
    char filename[BUFSIZ] ; /* scratch for making filenames */

    if( argc != 4 ){
	/* problem with arguments tell caller */
	fprintf( stdout, STATUS_ERROR ) ;
	fprintf( stdout, "\n" ) ;
	fprintf( stdout, "Argument problem\n" ) ;
	fflush( stdout ) ;
	exit(0) ;
    } else {
	directory = argv[1] ;
	node = argv[2] ;
	design = argv[3] ;
    }

    /* now see if we can change directory */
    if( chdir( directory )){
	/* we encounter an error tell caller */
	fprintf( stdout, STATUS_ERROR ) ;
	fprintf( stdout, "\n" ) ;
	fprintf( stdout, "Directory problem\n" ) ;
	fflush( stdout ) ;
	exit(0) ;
    }


    /* now see if error log files exist */
    sprintf( filename, "%s.%s.errlog", design, node ) ;
    if( YfileExists( filename ) ){
	/* the program has failed - tell caller */
	fprintf( stdout, PROGRAM_ERROR ) ;
	fprintf( stdout, "\n" ) ;
	fflush( stdout ) ;
	exit(0) ;
    }


    /* now see if completion log files exist */
    sprintf( filename, "%s.%s.ok", design, node ) ;
    if( YfileExists( filename ) ){
	/* the program has completed - tell caller */
	fprintf( stdout, PROGRAM_OK ) ;
	fprintf( stdout, "\n" ) ;
	fflush( stdout ) ;
	exit(0) ;
    }

    /* now see if lock file exists */
    sprintf( filename, "/tmp/twsc.%s", design ) ;
    if(!(YfileExists( filename ) )){
	/* the program has not been executed tell caller */
	fprintf( stdout, EXEC_ERROR ) ;
	fprintf( stdout, "\n" ) ;
	fflush( stdout ) ;
	exit(0) ;
    }

    /* test lock file to see if program is running */
    sprintf( filename, "/tmp/twsc.%s", design ) ;
    if(!(Yfile_test_lock( filename ))){
	/* the program has completed - tell caller */
	fprintf( stdout, PROGRAM_ERROR ) ;
	fprintf( stdout, "\n" ) ;
	fflush( stdout ) ;
	exit(0) ;
    }

    /* at this point we know the program is running we could */
    /* read the output file to see the exact location */
    fprintf( stdout, PROGRAM_RUNNING ) ;
    fprintf( stdout, "\n" ) ;
    fflush( stdout ) ;
    exit(0) ;

} /* end main */
