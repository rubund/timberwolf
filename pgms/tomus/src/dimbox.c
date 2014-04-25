/* ----------------------------------------------------------------- 
FILE:	    dimbox.c                                       
DESCRIPTION:Incremental bounding box routines.
CONTENTS:   new_dbox( antrmptr , costptr )
		TEBOXPTR antrmptr ;
		int *costptr ;
	    new_dbox2( antrmptr , bntrmptr , costptr )
		TEBOXPTR antrmptr , bntrmptr ;
		int *costptr ;
	    dbox_pos( antrmptr ) 
		TEBOXPTR antrmptr ;
DATE:	    Mar 27, 1989 
REVISIONS:  May 19, 1989 by Carl --- for gate swaps
----------------------------------------------------------------- */
#ifndef VMS
#ifndef lint
static char SccsId[] = "@(#) dimbox.c (Yale) version 1.6 2/15/91" ;
#endif
#endif

#include "standard.h"
#define break_pt 5
int prev_net , curr_net , test_newnet ;
int k ;
extern int *grid_x,*grid_y;
static PINBOXPTR *memoptrS ;

init_dimbox()
{
    int maxpin, get_max_pin() ;

    maxpin = get_max_pin() ;
    memoptrS = (PINBOXPTR *)
	Ysafe_malloc( (++maxpin) * sizeof(PINBOXPTR) ) ;

} /* end init_dimbox */


new_dbox( antrmptr , costptr )
PINBOXPTR antrmptr ;
int *costptr ;
{

DBOXPTR  dimptr   ;
PINBOXPTR termptr , nextptr ;

for( termptr = antrmptr ; termptr ; termptr = termptr->nextpin ) {
    curr_net = termptr->net ;
    dimptr = netarrayG[ curr_net ] ;
    if (!dimptr->numpins || !dimptr->dflag 
         || dimptr->numpins == 1 || dimptr->ignore == 1) continue;
    dimptr->dflag = 0;
    if ( termptr->newx != termptr->xpos ){
	checkxgrid(dimptr,termptr);
	*costptr += ( dimptr->newhalfPx - dimptr->halfPx) ;
    }
    if ( termptr->newy != termptr->ypos ){
	checkygrid(dimptr,termptr);
	*costptr += ( 
        (int)(vertical_wire_weightG * (double)dimptr->newhalfPy) -
        (int)(vertical_wire_weightG * (double)dimptr->halfPy) );
    }
    add2net_set( curr_net );
}
}



checkxgrid(dptr,pinptr)
PINBOXPTR pinptr ;
DBOXPTR  dptr   ;
{

int x,xhopper;
int xmaxS , xminS ,oldx;


    x = pinptr->newx;
    xminS = dptr->xmin;
    xmaxS = dptr->xmax;
    oldx = pinptr->xpos;

    if ( x <= xminS ){ 
	dptr->newxmin = x;
        if (oldx == xmaxS && dptr->line_x[xmaxS] == 1){
  		xhopper = xmaxS -1;
  		while (dptr->line_x[xhopper] == 0 && xhopper != x){
     			xhopper--;             
  		}
	  	dptr->newxmax = xhopper;
	}
    } else if (x >= xmaxS){
	dptr->newxmax = x;
        if (oldx == xminS && dptr->line_x[xminS] == 1){
		xhopper = xminS +1;
	        while (dptr->line_x[xhopper] == 0 && xhopper != x){
	     		xhopper++;             
	        }
		dptr->newxmin = xhopper;
	}
    } else {
        if (xminS != 0 && oldx == xminS && dptr->line_x[xminS] == 1){
		xhopper = xminS +1;
	        while (dptr->line_x[xhopper] == 0 && xhopper != x){
	     		xhopper++;             
	        }
		dptr->newxmin = xhopper;
	}
        if (xmaxS != vlineG && oldx == xmaxS && dptr->line_x[xmaxS] == 1){
  		xhopper = xmaxS -1;
  		while (dptr->line_x[xhopper] == 0 && xhopper != x){
     			xhopper--;             
  		}
	  	dptr->newxmax = xhopper;
	}
    }
    	dptr->newhalfPx =  grid_x[dptr->newxmax] - grid_x[dptr->newxmin] ; 
} 
    
    
    
checkygrid(dptr,pinptr)
PINBOXPTR pinptr ;
DBOXPTR  dptr   ;
{

int y,yhopper;
int ymaxS , yminS ,oldy;

    y = pinptr->newy;
    yminS = dptr->ymin;
    ymaxS = dptr->ymax;
    oldy = pinptr->ypos;

    if ( y <= yminS ){ 
	dptr->newymin = y;
        if (oldy == ymaxS && dptr->line_y[ymaxS] == 1){
  		yhopper = ymaxS -1;
  		while (dptr->line_y[yhopper] == 0 && yhopper != y){
     			yhopper--;             
  		}
	  	dptr->newymax = yhopper;
	}
    } else if (y >= ymaxS){
	dptr->newymax = y;
        if (oldy == yminS && dptr->line_y[yminS] == 1){
		yhopper = yminS +1;
	        while (dptr->line_y[yhopper] == 0 && yhopper != y){
	     		yhopper++;             
	        }
		dptr->newymin = yhopper;
	}
    } else {
        if (yminS != 0 && oldy == yminS && dptr->line_y[yminS] == 1){
		yhopper = yminS +1;
	        while (dptr->line_y[yhopper] == 0 && yhopper != y){
	     		yhopper++;             
	        }
		dptr->newymin = yhopper;
	}
        if (ymaxS != hlineG && oldy == ymaxS && dptr->line_y[ymaxS] == 1){
  		yhopper = ymaxS -1;
  		while (dptr->line_y[yhopper] == 0 && yhopper != y){
     			yhopper--;             
  		}
	  	dptr->newymax = yhopper;
	}
    }
    	dptr->newhalfPy = grid_y[dptr->newymax] - grid_y[dptr->newymin] ; 
} 




new_dbox2( antrmptr , bntrmptr , costptr )
PINBOXPTR antrmptr , bntrmptr ;
int *costptr ;
{

DBOXPTR  dimptr,netptr   ;
PINBOXPTR termptr , nextptr ;
int anet,bnet;


label:
if( antrmptr == PINNULL ) {
    new_dbox( bntrmptr , costptr ) ;
    return ;
} 
if( bntrmptr == PINNULL ) {
    new_dbox( antrmptr , costptr ) ;
    return ;
}
/** the case where both the pointers are not NULL ***/
if ( antrmptr->net < bntrmptr->net ) {
     termptr = antrmptr ;
     antrmptr = antrmptr->nextpin ;
} else if ( antrmptr->net > bntrmptr->net ) {
     termptr = bntrmptr ;
     bntrmptr = bntrmptr->nextpin ;
} else {
     antrmptr = antrmptr->nextpin ;
     bntrmptr = bntrmptr->nextpin ;
     goto label;
}

for( ; termptr ; termptr = nextptr ) {
     curr_net = termptr->net ;
     dimptr = netarrayG[ curr_net ] ;
label_loop:
     if( antrmptr && bntrmptr ) {
         if( (anet = antrmptr->net)
             < (bnet = bntrmptr->net) ) {
             nextptr = antrmptr ;
             antrmptr = antrmptr->nextpin ;
         } else if( anet > bnet ) {
             nextptr = bntrmptr ;
             bntrmptr = bntrmptr->nextpin ;
         } else {  /* anet is equal to bnet */
		 antrmptr = antrmptr->nextpin; 
		 bntrmptr = bntrmptr->nextpin; 
		 goto label_loop;
         }
     } else if( antrmptr == PINNULL && bntrmptr) {
         nextptr = bntrmptr ;
         bntrmptr = bntrmptr->nextpin ;
     } else if( antrmptr && bntrmptr == PINNULL ) {
            nextptr = antrmptr ;
            antrmptr = antrmptr->nextpin ;
     } else {
            nextptr = PINNULL ;
     }
if (!dimptr->numpins || !dimptr->dflag 
|| dimptr->numpins == 1 || dimptr->ignore == 1) continue;
if( nextptr && curr_net == nextptr->net ) {
            continue ;
}
dimptr->dflag = 0;
    if ( termptr->newx != termptr->xpos ){
	checkxgrid(dimptr,termptr);
	*costptr += ( dimptr->newhalfPx - dimptr->halfPx) ;
    }
    if ( termptr->newy != termptr->ypos ){
	checkygrid(dimptr,termptr);
	*costptr += ( 
        (int)(vertical_wire_weightG * (double)dimptr->newhalfPy) -
        (int)(vertical_wire_weightG * (double)dimptr->halfPy) );
    }
    add2net_set( curr_net );
}
}


dbox_pos( antrmptr ) 
PINBOXPTR antrmptr ;
{

DBOXPTR dimptr ;
PINBOXPTR termptr ;

for( termptr = antrmptr ; termptr ;termptr=termptr->nextpin ) {
    dimptr = netarrayG[ termptr->net ] ;
    dimptr->xmin = dimptr->newxmin ;
    dimptr->xmax = dimptr->newxmax ;
    dimptr->ymin = dimptr->newymin ;
    dimptr->ymax = dimptr->newymax ;
    dimptr->halfPx = dimptr->newhalfPx ;
    dimptr->halfPy = dimptr->newhalfPy ;
    dimptr->line_x[termptr->xpos]--;
    dimptr->line_y[termptr->ypos]--;
    dimptr->line_x[termptr->newx]++;
    dimptr->line_y[termptr->newy]++;
    termptr->xpos = termptr->newx ;
    termptr->ypos = termptr->newy ;
}
}

dbox_old( antrmptr ) 
PINBOXPTR antrmptr ;
{

DBOXPTR dimptr ;
PINBOXPTR termptr ;
for( termptr = antrmptr ; termptr ;termptr=termptr->nextpin ) {
    dimptr = netarrayG[ termptr->net ] ;
    dimptr->newxmin = dimptr->xmin ;
    dimptr->newxmax = dimptr->xmax ;
    dimptr->newymin = dimptr->ymin ;
    dimptr->newymax = dimptr->ymax ;
    dimptr->newhalfPx = dimptr->halfPx ;
    dimptr->newhalfPy = dimptr->halfPy ;
}
}

