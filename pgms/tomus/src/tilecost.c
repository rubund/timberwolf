/* ----------------------------------------------------------------- 
FILE:	    tilecost.c                                       
DESCRIPTION:calculate total cost of placement.
CONTENTS:   tilecost()

DATE:	    Mar 27, 1989 
REVISIONS:  
----------------------------------------------------------------- */
#ifndef VMS
#ifndef lint
static char SccsId[] = "@(#) tilecost.c (Yale) version 1.2 10/31/90" ;
#endif
#endif

#define MAXNUMPINS    100		/* WPS */

#include "standard.h"
#include <yalecad/debug.h>

tilecost()
{
static int len,cells,cell,ppen,pen,tile,ile,part,temp,totc ;
static PTILEPTR tptr;
static PARTNPTR ptr;
totc = 0;
pen = 0;
ppen = 0;
for( tile = 1 ; tile <= num_ptileG ; tile++ ) {
 tptr = tarrayG[tile];
 cells = tptr->cells;
temp = 0;
 for( cell = 1 ; cell <= cells ; cell++ ) {
  temp += carrayG[tptr->carray[cell]]->clength;
 }
/*if (temp != tptr->celllen) printf("tile error\n");

 else */
pen += ABS(tptr->capacity - tptr->celllen);
 }
 if (newtilepenalG != pen) printf("tile2 error\n"); 

for( tile = 1 ; tile <= num_partnsG; tile++ ) {
 ptr = partarrayG[tile];
 len = 0;
for( ile = 1 ; ile <= num_ptileG ; ile++ ) {
 if (tarrayG[ile]->partition_id == tile) len += tarrayG[ile]->celllen;
}
 if (len != ptr->celllen) printf("part2 error\n");
 ppen += ABS(ptr->capacity - ptr->celllen);
 pen = ABS(ptr->capacity - len);
 }
 if (newpartpenalG!= ppen) printf("part error\n");
return(ppen);
}
