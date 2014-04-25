/* ----------------------------------------------------------------- 
FILE:	    acceptt.c                                       
DESCRIPTION:simulated annealing acceptance function.
CONTENTS:   int acceptt( delta_cost )
		int delta_cost ;
DATE:	    Mar 27, 1989 
REVISIONS:  
----------------------------------------------------------------- */
#ifndef VMS
#ifndef lint
static char SccsId[] = "@(#) acceptt.c (Yale) version 1.1 9/30/90" ;
#endif
#endif

#include <stdio.h>

#define RAND ( Yacm_random() )
#define MASK 0x3ff
extern double table1[] , table2[] , table3[] , TG ;

int d_cost, truth;

int acceptt( delta_cost )
int delta_cost ;
{

double fred ;
register unsigned fract ;

d_cost = delta_cost;	/* make it known to the world */
fred =  (double) delta_cost / TG ; 

if( fred >= 0.0 ) {
    truth = 1 ;
} else if( fred < -80.0 ) {
    truth = 0 ;
} else if( fred > -0.0001 ) {
    if( 1.0 + fred > ( (double) RAND / (double)0x7fffffff ) ) { 
	truth = 1 ;
    } else {
	truth = 0 ;
    }
} else {
    fract = (int)( -fred * 8388608.0 ) ;
    if( (table1[ (fract >> 20) & MASK ] * 
		    table2[ (fract >> 10) & MASK] * 
		    table3[ fract & MASK ]) > 
		    ( (double) RAND / (double)0x7fffffff ) ) {
	truth = 1 ;
    } else {
	truth = 0 ;
    }
}

return(truth) ; 
}
