/* ----------------------------------------------------------------- 
FILE:	    tilepenal.c                                       
DESCRIPTION: 
CONTENTS:   new_assgnto_old_tile(tile1,tile2,len)
            update_tilepen(tile1,tile2,diff)
            term_newpos( antrmptr , xcenter , ycenter )    
	
DATE:	  March 11, 1990 
REVISIONS: , 1990: 
            1990 :  
----------------------------------------------------------------- */
#ifndef VMS
#ifndef lint
static char SccsId[] = "@(#) tilepenal.c (Yale) version 1.3 2/15/91" ;
#endif
#endif

#include "standard.h"
#include "parser.h"


update_tilepen(aptr,bptr,diff)
PTILEPTR aptr,bptr;  
int diff;
 {
register int oldpenal,newpenal,apart,bpart;
static PARTNPTR apartptr,bpartptr;

aptr->nupenalty = ABS(aptr->celllen - diff  - aptr->capacity);
bptr->nupenalty = ABS(bptr->celllen + diff  - bptr->capacity);
oldpenal = aptr->penalty + bptr->penalty;
newpenal = aptr->nupenalty + bptr->nupenalty;
newtilepenalG += (newpenal - oldpenal); 

oldpenal = newpenal = 0;

apart = aptr->partition_id;
bpart = bptr->partition_id;
if (apart == bpart) {
return;
} else {
    apartptr = partarrayG[apart];
    apartptr->nupenalty = ABS(apartptr->celllen -
					    diff  - apartptr->capacity);
    oldpenal+=  apartptr->penalty;
    newpenal+=  apartptr->nupenalty;

    bpartptr = partarrayG[bpart];
    bpartptr->nupenalty = ABS(bpartptr->celllen +
					    diff  - bpartptr->capacity);
    oldpenal+=  bpartptr->penalty;
    newpenal+=  bpartptr->nupenalty;
}
newpartpenalG += (newpenal - oldpenal);
}


term_newpos( antrmptr , xcenter , ycenter )
PINBOXPTR antrmptr ;
int xcenter , ycenter ;
{
register PINBOXPTR pinptr ;

for( pinptr = antrmptr ; pinptr; pinptr = pinptr->nextpin ) {
   netarrayG[ pinptr->net ]->dflag = 1 ;
   pinptr->newx = xcenter ;
   pinptr->newy = ycenter ;
}
}



new_assgnto_old_tile(atileptr,btileptr,len)
PTILEPTR atileptr,btileptr;
int len;
{
 static int apart,bpart;
 static PARTNPTR apartptr,bpartptr;

 atileptr->penalty =  atileptr->nupenalty;
 atileptr->celllen -= len;
 btileptr->penalty =  btileptr->nupenalty;
 btileptr->celllen += len;

apart = atileptr->partition_id;
bpart = btileptr->partition_id;

   if (apart == bpart) {
   return;
   } else {
    if(apart!=0) {
           apartptr = partarrayG[apart];
           apartptr->penalty =  apartptr->nupenalty;
           apartptr->celllen -=  len;
    }
    if (bpart!=0){
           bpartptr = partarrayG[bpart];
	   bpartptr->penalty = bpartptr->nupenalty ;
           bpartptr->celllen +=  len;
    }
   } 
}

