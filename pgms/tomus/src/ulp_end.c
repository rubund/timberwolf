/* ----------------------------------------------------------------- 
FILE:	    uloop.c                                       
DESCRIPTION:inner loop of simulated annealing algorithm.
CONTENTS:   
	    double partition( C_initial,k_initial,p_initial,R_initial )
		int C_initial , k_initial , p_initial , R_initial ;
	    double expected_value(C_initial,k_initial,p_initial,R_initial)
		int C_initial , k_initial , p_initial , R_initial ;
	    double expected_svalue(C_initial,k_initial,
		p_initial,R_initial ) 
	    int C_initial , k_initial , p_initial , R_initial ; 
	    double compute_and_combination( C , k , p , R )
		int C , k , p , R ;
	    double combination( numerator , denominator )
		int numerator , denominator ;
	    sanity_check()
	    sanity_check2()
	    sanity_check3()
DATE:	    Mar 27, 1989 
REVISIONS:  Mar 29, 1989 - removed vertical / horz wire weighting.
----------------------------------------------------------------- */
#ifndef VMS
#ifndef lint
static char SccsId[] = "@(#) ulp_end.c (Yale) version 1.1 9/30/90" ;
#endif
#endif

#include "standard.h"


/* Note: If you change definitions here, check newtemp.c */

extern INT moveable_cells ;
DOUBLE compute_and_combination();
DOUBLE combination();


DOUBLE partition( C_initial , k_initial , p_initial , R_initial )
int C_initial , k_initial , p_initial , R_initial ;
{

int R , C , k , p , k_limit , p_limit ;
double states , equivs ;

states = 0.0 ;
R = k_limit = R_initial - k_initial ;
C = C_initial - p_initial * k_initial ;

for( k = 1 ; k <= k_limit ; k++ ) {
    equivs = combination( R , k ) ;
    p_limit = C / k ;
    for( p = p_initial ; p <= p_limit ; p++ ) {
	if( C - (p-1)*R > k ) { ;
	    continue ;
	}
	states += equivs * (compute_and_combination( C , k , p , R ) -
					partition( C , k , p , R ) ) ;
	continue ;
    }
}

return( states ) ;
}


DOUBLE expected_value( C_initial , k_initial , p_initial , R_initial )
int C_initial , k_initial , p_initial , R_initial ;
{

int R , C , k , p , k_limit , p_limit ;
double value , equivs ;

value = 0.0 ;
R = k_limit = R_initial - k_initial ;
C = C_initial - p_initial * k_initial ;

for( k = 1 ; k <= k_limit ; k++ ) {
    equivs = combination( R , k ) ;
    p_limit = C / k ;
    for( p = p_initial ; p <= p_limit ; p++ ) {
	if( C - (p-1)*R > k ) { ;
	    continue ;
	}
	value += (double) p * equivs *
			(compute_and_combination( C , k , p , R ) -
				    partition( C , k , p , R ) ) ;
    }
}

return( value ) ;
}


DOUBLE expected_svalue( C_initial , k_initial , p_initial , R_initial )
int C_initial , k_initial , p_initial , R_initial ;
{

int R , C , k , p , k_limit , p_limit ;
double value , equivs ;

value = 0.0 ;
R = k_limit = R_initial - k_initial ;
C = C_initial - p_initial * k_initial ;

for( k = 1 ; k <= k_limit ; k++ ) {
    equivs = combination( R , k ) ;
    p_limit = C / k ;
    for( p = p_initial ; p <= p_limit ; p++ ) {
	if( C - (p-1)*R > k ) { ;
	    continue ;
	}
	value += (double)(p * p) * equivs *
			(compute_and_combination( C , k , p , R ) -
				    partition( C , k , p , R ) ) ;
    }
}

return( value ) ;
}


DOUBLE compute_and_combination( C , k , p , R )
int C , k , p , R ;
{

int numerator , denom1 , denom2 , temp ;
double states ;

states = 1.0  ;
numerator = C - k*p + R - k - 1 ;
denom1 = C - k*p ;
denom2 = R - k - 1 ;
if( denom1 > denom2 ) {
    temp = denom1 ;
    denom1 = denom2 ;
    denom2 = temp ;
}
for( ; numerator > denom2 ; numerator-- , denom1-- ) {
    states *= (double) numerator ;
    states /= (double) denom1 ;
}

return( states ) ;
}


DOUBLE combination( numerator , denominator )
int numerator , denominator ;
{

double states ;
int temp , denom1 , denom2 ;

states = 1.0  ;

denom1 = denominator ;
denom2 = numerator - denominator ;
if( denom1 > denom2 ) {
    temp = denom1 ;
    denom1 = denom2 ;
    denom2 = temp ;
}
for( ; numerator > denom2 ; numerator-- , denom1-- ) {
    states *= (double) numerator ;
    states /= (double) denom1 ;
}

return( states ) ;
}

