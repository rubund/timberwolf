/* ----------------------------------------------------------------- 
FILE:	    sortpin.c                                       
DESCRIPTION:pin sorting functions.
CONTENTS:   sortpin()
	    shellsort( term , n )
		TEBOXPTR term[] ;
		int n ;
DATE:	    Mar 27, 1989 
REVISIONS:  
----------------------------------------------------------------- */
#ifndef VMS
#ifndef lint
static char SccsId[] = "@(#) sortpin.c (Yale) version 1.4 2/15/91" ;
#endif
#endif

#include "standard.h"

sortpin()
{

    INT j , n , cell, maxpins ;
    INT pincount ;
    CBOXPTR ptr ;
    PINBOXPTR pinptr, *xpptr ;

    /* find the maximum number of pins on a cell for allocation */
    maxpins = INT_MIN ;
    for( cell = 1; cell <= numcellsG; cell++ ){
	ptr = carrayG[cell] ;
	pincount = 0 ;
	for( pinptr = ptr->pins; pinptr; pinptr = pinptr->nextpin ){
	    pincount++ ;
	}
	maxpins = MAX( pincount, maxpins ) ;
    }

    xpptr = (PINBOXPTR *) Ysafe_malloc( (maxpins+2)*sizeof(PINBOXPTR));

    for( cell = 1 ; cell <= numcellsG ; cell++ ) {
	ptr = carrayG[ cell ] ;
	n = 0 ;
	for( pinptr = ptr->pins ; pinptr; pinptr = pinptr->nextpin ) {
	    xpptr[ ++n ] = pinptr ;
	}
	shellsort( xpptr , n ) ;
	xpptr[ n + 1 ] = PINNULL ;
	ptr->pins = xpptr[ 1 ] ;
	for( j = 1 ; j <= n ; j++ ) {
	    xpptr[j]->nextpin = xpptr[j+1] ;
	}
    }
    Ysafe_free( xpptr ) ;
}


shellsort( term , n )
PINBOXPTR term[] ;
int n ;
{

PINBOXPTR ptr ;
int incr , i , j ;

for( incr = n / 2 ; incr > 0 ; incr /= 2 ) {
    for( i = incr + 1 ; i <= n ; i++ ) {
	for( j = i - incr ; j > 0 && 
	(term[j]->net >
	 term[j+incr]->net) ; j -= incr ) {
	    ptr = term[j] ;
	    term[j] = term[j+incr] ;
	    term[j+incr] = ptr ;
	}
    }
}
}
