/* ----------------------------------------------------------------- 
FILE:	    findcost.c                                       
DESCRIPTION:calculate total cost of placement.
CONTENTS:   findcost()
	    create_cell( )
	    find_net_sizes()
DATE:	    Mar 27, 1989 
REVISIONS:  
----------------------------------------------------------------- */
#ifndef VMS
#ifndef lint
static char SccsId[] = "@(#) findcost.c (Yale) version 1.5 3/4/91" ;
#endif
#endif


#include "standard.h"
#include <yalecad/debug.h>
static int maxpinS = 0 ;

findcost()
{
static int tile,part ;
static PTILEPTR tptr ;
static DBOXPTR dimptr ;
static PINBOXPTR netptr;
static int net ;
static int length, pathcount,count;
INT high_length, low_length ;
static PATHPTR path ;
static GLISTPTR net_of_path ;


tilepenalG = 0 ;
partpenalG = 0 ;
penaltyG = 0 ;

for( tile = 1 ; tile <= num_ptileG ; tile++ ) {
  tptr = tarrayG[tile];
  if (tptr->legal || tptr->capacity == 0) continue;
  if (!partarrayG[tptr->partition_id]->capacity) continue;
  tptr->penalty = ABS(- tptr->capacity +  tptr->celllen);
  part = tptr->partition_id;
  partarrayG[part]->celllen +=  tptr->celllen; 
  tilepenalG +=  tptr->penalty;
}
newtilepenalG = tilepenalG;

for( part = 1 ; part <= num_partnsG ; part++ ) {
  partarrayG[part]->penalty = ABS( - partarrayG[part]->capacity +
				partarrayG[part]->celllen);
  partpenalG += partarrayG[part]->penalty;
}
/*tilecost(); */

penaltyG = (int)(tilepenalC  * (double)tilepenalG ) ;

/* ************* now calculate the timing penalty ************** */
timingpenalG = 0 ;
for( pathcount = 1 ; pathcount <= numpathsG ; pathcount++ ) {

    path = patharrayG[pathcount] ;
    low_length = 0 ;
    high_length = 0 ;
    ASSERTNCONT( path, "findcost", "pointer to path is NULL" ) ;
    /* for all nets k of a path i */
    /* -----------------------------------------------------------------
        For all nets k of a path i:
            We use the minimum strength driver for each net to calculate
            the lower bound on the length and the maximum strength driver
            for the upper bound on the length.  The user must take false
            paths into account when specifying the driver strengths.
    ------------------------------------------------------------------ */
    for( net_of_path=path->nets;net_of_path;
	net_of_path=net_of_path->next ){
	net = net_of_path->p.net ;
	dimptr = netarrayG[net] ;
	/* accumulate length of path */
	length = (INT)
            (horizontal_path_weightG * (DOUBLE) dimptr->halfPx);
        length = length + (INT)
            (vertical_path_weightG * (DOUBLE) dimptr->halfPy ) ;

        low_length = low_length + (INT)
            (dimptr->max_driver * (DOUBLE) length + dimptr->driveFactor );
        high_length = high_length + (INT)
            (dimptr->min_driver * (DOUBLE) length + dimptr->driveFactor );
    }
    /* save result */
    path->lo_path_len = path->new_lo_path_len = low_length ;
    path->hi_path_len = path->new_hi_path_len = high_length ;

    /* calculate penalty */
    /* no penalty if within target window */
    /* lowerbound <= length <= upperbound */
    if( length > path->upper_bound ){
	timingpenalG += length - path->upper_bound ; 
    } else if( length < path->lower_bound ){
	timingpenalG += path->lower_bound - length ;
    }
}
/* scale timing penalty */
timingcostG = (int) ( timeFactorG * (DOUBLE) timingpenalG ) ;

}


find_net_sizes()
{

PINBOXPTR netptr ;
DBOXPTR dimptr ;
static int i , net , *net_size , limit , *num_nets_of_size , num_nets ;
static int j , total , cell ;

limit = 6 ;
num_nets = 0 ;
net_size = (int *) Ysafe_malloc( (limit + 2) * sizeof(int) ) ;
num_nets_of_size = (int *) Ysafe_malloc( (limit + 1) * sizeof(int) ) ;
for( i = 0 ; i <= limit ; i++ ) {
    num_nets_of_size[i] = 0 ;
}
for( net = 1 ; net <= numnetsG ; net++ ) {
    dimptr = netarrayG[net] ;
    for( i = 1 ; i <= limit + 1 ; i++ ) {
	net_size[i] = 0 ;
    }
    for( netptr = dimptr->pins ; netptr ; netptr = netptr->next ){
	cell = netptr->cell ;
	if( cell > numcellsG ) {
	    continue ;
	}
	for( i = 1 ; i <= limit ; i++ ) {
	    if( cell == net_size[i] || net_size[i] == 0 ) {
		break ;
	    }
	}
	if( i > limit ) {
	    break ;
	} else {
	    net_size[i] = cell ;
	}
    }
    for( i = 1 ; i <= limit ; i++ ) {
	if( net_size[i+1] == 0 ) {
	    break ;
	}
    }
    if( i >= 2 ) {
	num_nets++ ;
	num_nets_of_size[i]++ ; 
    }
}
fprintf(fpoG,"\n");
for( i = 2 ; i <= limit ; i++ ) {
    total = 0 ;
    for( j = i ; j <= limit ; j++ ) {
	total += num_nets_of_size[j] ;
    }
    fprintf(fpoG,
	"Percentage of Nets Connecting to at least %d cells:%4.2f\n",
			    i , (double) total / (double) num_nets ) ;
}
fprintf(fpoG,"\n");
fflush(fpoG) ;

Ysafe_free( net_size ) ;
Ysafe_free(  num_nets_of_size ) ;

return ;
}

get_max_pin()
{
    return( maxpinS ) ;
} /* end get_max_pin */
