/* ----------------------------------------------------------------- 
FILE:	    wirecosts.c                                       
DESCRIPTION:Examines wire cost more closely.  LimitNets is the wirelength
	    of nets which are in the cost function, that is their
	    skip field in NETBOXPTR is FALSE.  WithPads is the wirelength
	    including all connections and withOutPads is the wirelength
	    including the skip nets but neglecting pad connections.
CONTENTS:   
DATE:	    Apr  27, 1989 - added heading and added limitnets calc.
REVISIONS:  
----------------------------------------------------------------- */
#ifndef lint
static char SccsId[] = "@(#) wirecosts.c version 3.3 9/5/90" ;
#endif

#include <custom.h>
#include <yalecad/debug.h>


wirecosts()
{

NETBOXPTR dimptr ;
PINBOXPTR pinptr ;

INT limitNets, withPads , withOutPads ;
INT x , y , xmin , xmax , ymin , ymax , net ;
INT cell, celltype, bbox ;

withPads = 0 ;
withOutPads = 0 ;
limitNets = 0 ;

for( net = 1 ; net <= numnetsG ; net++ ) {
    dimptr =  netarrayG[net] ;

    xmin = 0 ;
    xmax = 0 ;
    ymin = 0 ;
    ymax = 0 ;
    for( pinptr = dimptr->pins ;pinptr;pinptr = pinptr->next ) {
	cell = pinptr->cell ;
	celltype = cellarrayG[cell]->celltype ;
	if( celltype == PADCELLTYPE || celltype == PADGROUPTYPE ){
	    continue ;
	}
	xmin = xmax = pinptr->xpos ;
	ymin = ymax = pinptr->ypos ;
	pinptr = pinptr->next ;
	break ;
    }
    for( ; pinptr ; pinptr = pinptr->next ) {
	cell = pinptr->cell ;
	celltype = cellarrayG[cell]->celltype ;
	if( celltype == PADCELLTYPE || celltype == PADGROUPTYPE ){
	    continue ;
	}
	x = pinptr->xpos ;
	y = pinptr->ypos ;

	if( x < xmin ) {
	    xmin = x ;
	} else if( x > xmax ) {
	    xmax = x ;
	}
	if( y < ymin ) {
	    ymin = y ;
	} else if( y > ymax ) {
	    ymax = y ;
	}
    }
    withOutPads += (xmax - xmin) + (ymax - ymin) ;

    dimptr =  netarrayG[net] ;
    pinptr = dimptr->pins ;
    xmin = 0 ;
    xmax = 0 ;
    ymin = 0 ;
    ymax = 0 ;
    if( pinptr ) {
	xmin = xmax = pinptr->xpos ;
	ymin = ymax = pinptr->ypos ;
	pinptr = pinptr->next ;
    }
    for( ; pinptr ; pinptr = pinptr->next ) {
	x = pinptr->xpos ;
	y = pinptr->ypos ;

	if( x < xmin ) {
	    xmin = x ;
	} else if( x > xmax ) {
	    xmax = x ;
	}
	if( y < ymin ) {
	    ymin = y ;
	} else if( y > ymax ) {
	    ymax = y ;
	}
    }
    withPads += bbox = (xmax - xmin) + (ymax - ymin) ;

    if(!(dimptr->skip)){
	limitNets += bbox ;
    }
}
OUT1("Wirelength:\n") ;
OUT2("\tAll nets             :%d\n", withPads ) ;
OUT2("\tLimited nets         :%d\n", limitNets ) ;
OUT2("\tAll nets without pads:%d\n", withOutPads ) ;
return ;

}
