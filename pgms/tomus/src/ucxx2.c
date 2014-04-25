/* ----------------------------------------------------------------- 
FILE:	    ucxx2.c                                       
DESCRIPTION:pairwise exchange.
CONTENTS:   ucxx2( )
	    add_cell() 
DATE:	    Mar 27, 1989 
REVISIONS:  
----------------------------------------------------------------- */
#ifndef VMS
#ifndef lint
static char SccsId[] = "@(#) ucxx2.c (Yale) version 1.5 2/15/91" ;
#endif
#endif

#include <yalecad/debug.h>
#include "standard.h"
#include "main.h"

extern int cellAlloc;
int newtimepenalty, newtimepenal ;


ucxx2(cell1,cell2,tile1,tile2,post1,post2 )
int cell1,cell2,tile1,tile2,post1,post2;
{
static PINBOXPTR atermptr , btermptr ;
static PTILEPTR tileptr1,tileptr2;
static CBOXPTR cellptr1,cellptr2;
static int error_light_is_on ;
static int cost,cost1 ;
static int truth,len ;
static double temp ;
static int btxcenter,btycenter,atxcenter,atycenter;
static int cost_true;

tileptr1 = tarrayG[tile1];
tileptr2 = tarrayG[tile2];
cellptr1 = carrayG[cell1];
cellptr2 = carrayG[cell2];

atermptr = cellptr1->pins ; 
btermptr = cellptr2->pins ; 

newtilepenalG = tilepenalG ;
newpartpenalG = partpenalG ;
newpenalG    = penaltyG  ;
len = cellptr1->clength - cellptr2->clength;
  update_tilepen(tileptr1,tileptr2,len);
/* takes care of both tile and partition
                             penalties */


newpenalG =  (int)( tilepenalC * (double) newtilepenalG +
	  partpenalC * (double) newpartpenalG);

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
atxcenter = tileptr1->grid_loc_x;
atycenter = tileptr1->grid_loc_y;

term_newpos( atermptr , btxcenter , btycenter ) ;
term_newpos( btermptr , atxcenter , atycenter ) ;


cost =  funccostG ; 
clear_net_set() ; /* reset set to mark nets that have changed position */
/* dimbox routines mark the nets that have changed */

new_dbox2( atermptr , btermptr , &cost ) ;

newtimepenal = timingpenalG ;
newtimepenal += calc_incr_time2( cell1, cell2 ) ;

ASSERT( newtimepenal == dcalc_full_penalty(),"ucxx2","time problem") ;
D( "ucxx2", newtimepenal = dcalc_full_penalty() ) ;

/* scale new timing penalty */
newtimepenalty = (int) ( timeFactorG * (DOUBLE) newtimepenal ) ;

wire_chg = cost - funccostG ;

truth =  acceptt( funccostG + penaltyG + timingcostG
	    - cost - newpenalG - newtimepenalty ) ;

if( truth == 1 ) {

    if( error_light_is_on ) {
	error_count++ ;
    }

    new_assgnto_old_tile(tileptr1,tileptr2,len);
    dbox_pos( atermptr ) ;
    dbox_pos( btermptr ) ;

    update_time2() ;
    remv_cell(tileptr1,post1) ;
    remv_cell(tileptr2,post2) ;
    add_cell(tileptr1,cellptr2) ;
    add_cell(tileptr2,cellptr1) ; 

    if( wire_chg < 0 ) {
	temp = (double) - wire_chg ;
	total_wire_chg += temp ;
	sigma_wire_chg += (temp - mean_wire_chg) * 
					(temp - mean_wire_chg) ;
	wire_chgs++ ;
    }
    funccostG = cost ; 
    tilepenalG = newtilepenalG ;
    partpenalG = newpartpenalG ;
    penaltyG  = newpenalG ;
    timingcostG  = newtimepenalty ;
    timingpenalG  = newtimepenal ;

    return( 1 ) ;
} else {
    dbox_old( atermptr ) ;
    dbox_old( btermptr ) ;
    return( 0 ) ;
}
}

add_cell(tileptr,cellptr)
PTILEPTR tileptr ;
CBOXPTR cellptr;
{

tileptr->cells++;
if ( tileptr->cells > cellAlloc ) {
	tileptr->carray = (INT*) Ysafe_realloc (tileptr->carray , (tileptr->cells
		+1) * sizeof(INT));
}

cellptr->cxcenter = tileptr->center_x;
cellptr->cycenter = tileptr->center_y;
cellptr->tile = tileptr->id;
tileptr->carray[ tileptr->cells ] = cellptr->id;
}

celln()
{
static int tile,temp,tpen,ppen;
static PARTNPTR partptr;
static PTILEPTR tptr;
temp = tpen = ppen= 0;
for( tile = 1 ; tile <= num_partnsG; tile++ ) {
  partptr = partarrayG[tile];
  temp += partptr->celllen;
  tpen += partptr->penalty;
  }
if (temp != celllenG) printf("part3 error\n");
if (tpen != partpenalG) printf("part4 error\n");
temp = tpen = ppen= 0;
for( tile = 1 ; tile <= num_ptileG; tile++ ) {
  tptr = tarrayG[tile];
  temp += tptr->celllen;
  ppen += tptr->penalty;
  }
if (temp != celllenG) printf("tile3 error\n");
if (ppen != tilepenalG) printf("tile4 error\n");
}

