/* ----------------------------------------------------------------- 
FILE:	    ucxx1.c                                       
DESCRIPTION:single cell move.
CONTENTS:   ucxx1()
DATE:	    Mar 10, 1990 
REVISIONS:  
----------------------------------------------------------------- */
#ifndef VMS
#ifndef lint
static char SccsId[] = "@(#) ucxx1.c (Yale) version 1.5 2/15/91" ;
#endif
#endif

#include <yalecad/debug.h>
#include "standard.h"
#include "main.h"

ucxx1(cell1,tile1,tile2,post1)
int cell1,tile1,tile2,post1;
{

static PTILEPTR tileptr1,tileptr2;
static PINBOXPTR atermptr ;
static CBOXPTR cellptr;

static int cost, cost1, error_light_is_on ;
static int btxcenter,btycenter ;
static int truth,len ;
static int newtimepenalty, newtimepenal;

tileptr1 = tarrayG[tile1];
tileptr2 = tarrayG[tile2];

cellptr = carrayG[cell1];
atermptr = cellptr->pins ; 
 
newtilepenalG = tilepenalG ;
newpartpenalG = partpenalG ;
newpenalG    = penaltyG ;

len = cellptr->clength;
update_tilepen(tileptr1,tileptr2,len);/* takes care of both tile and partition 
			               penalties */

newpenalG = (int)(partpenalC * (double) newpartpenalG +
	tilepenalC * (double) newtilepenalG);
error_light_is_on = 0 ;
if( newpenalG - penaltyG > P_limit ) {
    if( potential_errors < 100 ) {
	++potential_errors ;
        error_light_is_on = 1 ;
    } else {
	earlyRej++ ;
	return( -1 ) ;
    }
}
btxcenter = tileptr2->grid_loc_x;
btycenter = tileptr2->grid_loc_y;
term_newpos( atermptr ,btxcenter,btycenter);
cost = funccostG ; 

clear_net_set() ; /* reset set to mark nets that have changed position */
/* dimbox routines mark the nets that have changed */
new_dbox( atermptr , &cost ) ;

newtimepenal = timingpenalG ;
newtimepenal += calc_incr_time( cell1 ) ;

ASSERT( newtimepenal == dcalc_full_penalty(),"ucxx1","time problem") ;
D( "ucxx1", newtimepenal = dcalc_full_penalty() ) ;

/* scale new timing penalty */
newtimepenalty = (INT) ( timeFactorG * (DOUBLE) newtimepenal ) ;

truth = acceptt( funccostG + penaltyG + timingcostG 
	    - cost - newpenalG - newtimepenalty ) ; 
if( truth == 1 ) {
    if( error_light_is_on ) {
	error_count++ ;
    }
    new_assgnto_old_tile(tileptr1,tileptr2,len);
    dbox_pos( atermptr ) ;
    update_time( cell1 ) ;
    /* ****************************************************** */
    remv_cell(tileptr1,post1);
    add_cell(tileptr2,cellptr);
    /* ****************************************************** */
    funccostG = cost ; 
    tilepenalG = newtilepenalG ;
    partpenalG = newpartpenalG ;
    penaltyG  = newpenalG ;
    timingcostG  = newtimepenalty ;
    timingpenalG  = newtimepenal ;

    return( 1 ) ;
} else {
    dbox_old(atermptr);
    return( 0 ) ;
}
}
