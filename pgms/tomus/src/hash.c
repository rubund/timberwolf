/* ----------------------------------------------------------------- 
FILE:	    hash.c                                       
DESCRIPTION:hash function code.

CONTENTS:   maketabl( hashtab , size )
		HASHPTR **hashtab ;
		int size ;

	    delHtab( hashtab , size )
		HASHPTR *hashtab ;
		int size ;

	    addhash( hashtab , hname , size )
		HASHPTR *hashtab ;
		char hname[] ;
		int size ;

	    hashfind( hashtab , hname , size )
		HASHPTR *hashtab ;
		char hname[] ;
		int size ;

DATE:	    Mar 27, 1989 
REVISIONS:  May 19, 1989  --- made it more general (Carl)
----------------------------------------------------------------- */
#ifndef VMS
#ifndef lint
static char SccsId[] = "@(#) hash.c (Yale) version 1.1 9/30/90" ;
#endif
#endif

#include <string.h>
#include "standard.h"


maketabl( hashtab , size )
HASHPTR **hashtab ;
int size ;
{

int i ;

(*hashtab) = ( HASHPTR * ) Ysafe_malloc( size * sizeof( HASHPTR ));
for( i = 0 ; i < size ; i++ ) {
    (*hashtab)[i] = ( HASHPTR ) NULL ;
}
return ;
}


delHtab( hashtab , size )
HASHPTR *hashtab ;
int size ;
{

int i ;
HASHPTR hptr , zapptr ;

for( i = 0 ; i < size ; i++ ) {
    hptr = hashtab[i] ;
    if( hptr != (HASHPTR) NULL ) {
	zapptr = hptr ;
	while( hptr->hnext != (HASHPTR) NULL ) {
	    hptr = hptr->hnext ;
	    Ysafe_free( zapptr ) ;
	    zapptr = hptr ;
	}
	Ysafe_free( hptr ) ;
    }
}
Ysafe_free( hashtab ) ;
return ;
}


addhash( hashtab , hname , size , value )
HASHPTR *hashtab ;
char hname[] ;
int size , *value ;
{

int i ;
HASHPTR hptr ;
unsigned int hsum = 0 ;

for( i = 0 ; i < strlen( hname ) ; i++ ) {
    hsum += ( unsigned int ) hname[i] ;
}
hsum %= size ;
if( (hptr = hashtab[hsum]) == (HASHPTR) NULL ) {
    hptr = hashtab[hsum] = (HASHPTR) Ysafe_malloc( sizeof(HASHBOX)) ;
    hptr->hnext = (HASHPTR) NULL ;
    hptr->hnum = ++(*value) ;
    hptr->hname = (char *) Ysafe_malloc( (strlen( hname ) + 1) * 
					    sizeof( char ) ) ;
    sprintf( hptr->hname , "%s" , hname ) ;
    return(1) ;
} else {
    for( ; ; ) {
	if( strcmp( hname , hptr->hname ) == 0 ) {
	    return(0) ;
	}
	if( hptr->hnext == (HASHPTR) NULL ) {
	    hptr = hptr->hnext = (HASHPTR) Ysafe_malloc(sizeof(HASHBOX));
	    hptr->hnext = (HASHPTR) NULL ;
	    hptr->hnum = ++(*value) ;
	    hptr->hname = (char *) Ysafe_malloc( (strlen( hname ) + 1) * 
					    sizeof( char ) ) ;
	    sprintf( hptr->hname , "%s" , hname ) ;
	    return(1) ;
	} else {
	    hptr = hptr->hnext ;
	}
    }
}
}


hashfind( hashtab , hname , size )
HASHPTR *hashtab ;
char hname[] ;
int size ;
{

int i ;
HASHPTR hptr ;
unsigned int hsum = 0 ;

for( i = 0 ; i < strlen( hname ) ; i++ ) {
    hsum += ( unsigned int ) hname[i] ;
}
hsum %= size ;
if( (hptr = hashtab[hsum]) == (HASHPTR) NULL ) {
    return(0) ;
} else {
    for( ; ; ) {
	if( strcmp( hname , hptr->hname ) == 0 ) {
	    return( hptr->hnum ) ;
	}
	if( hptr->hnext == (HASHPTR) NULL ) {
	    return(0) ;
	} else {
	    hptr = hptr->hnext ;
	}
    }
}
}
