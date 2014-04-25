/* ----------------------------------------------------------------- 
FILE:	    twsc.c                                       
DESCRIPTION:Main routine for drawing SC data.
CONTENTS:   drawSC( design, filename )
		char	*design;
		char *filename;
DATE:	    Jan 25, 1989 - major rewrite of version 1.0
REVISIONS:  Tue Mar 19 15:57:05 CST 1991 - removed color toggle.
----------------------------------------------------------------- */
#ifndef lint
static char SccsId[] = "@(#) twsc.c version 3.6 8/13/91" ;
#endif

#include <stdio.h>
#include "globals.h"


drawSC( design, filename )
char *design ;
char *filename ;
{

int         
	    x0,
	    y0,
	    x1,
	    y1,
	    xcenter,
	    ycenter,
	    segCount ,
	    i ,
	    curSize ,
	    orient,
	    pinloc,
	    groupNo,
	    blk,
	    rowHeight,
	    cellNum = 0,
	    firstCell = TRUE ;
char        buffer[LRECL],
	    cellName[LRECL],
	    color[LRECL],
	    message[LRECL],
	    netName[LRECL],
	    oldNetName[LRECL],
	    pinName[LRECL],
	    *bufferptr ;
void        checkPos();
FILE        *placeFile,
	    *pinFile ;
routeBoxPtr *segTable,
	    curSeg ;

/* begin graphics */
TWstartFrame() ;
if( placeFile = fopen(filename,"r" )){ 
    while( bufferptr=fgets(buffer,LRECL,placeFile )){
	if (sscanf(bufferptr,"%s%d%d%d%d%d%d",cellName,
	    &x0,&y0,&x1,&y1,&orient,&blk) == 7 ){

	    if( strncmp( cellName, "twfeed", 6 ) == STRINGEQ ){
		TWdrawCell( ++cellNum, x0,y0,x1,y1,
		    FEEDCOLOR, cellName ) ;
	    } else if( blk ){
		TWdrawCell( ++cellNum, x0,y0,x1,y1,
		    ROWCOLOR, cellName ) ;
	    } else {
		TWdrawCell( ++cellNum, x0,y0,x1,y1,
		    ROWCOLOR2, cellName ) ;
	    }
	    if( firstCell ){
		rowHeight = y1 - y0 ;
		firstCell = FALSE ;
	    }  
	}
    }
    fclose(placeFile) ;

} else {
    sprintf(message,"Could not open placement file:%s",filename) ;
    M(ERRMSG,"main",message);
    YexitPgm(PGMFAIL);
}


sprintf( filename, "%s.pin", design);
if( pinFile = fopen(filename,"r" )){ 
    /* read file first time to initialize linked list and oldNetName */
    while( bufferptr=fgets(buffer,LRECL,pinFile )){
	if (sscanf(bufferptr,"%s%d%s%s%d%d%d%d",netName,&groupNo,cellName,pinName, 
	    &x0,&y0,&blk,&pinloc) == 8 ){
	    sprintf(oldNetName,"%s",netName);
	    /* allocate array of pointers to segments */
	    segTable = (routeBoxPtr *) Ysafe_malloc(
			EXPECTEDNUMSEG*sizeof(routeBoxPtr)) ;
	    curSize = EXPECTEDNUMSEG ;
	    segCount = 1;
	    break ;
	}
    }   

    rewind(pinFile) ;
    while( bufferptr=fgets(buffer,LRECL,pinFile )){
	if (sscanf(bufferptr,"%s%d%s%s%d%d%d%d",netName,&groupNo,cellName,pinName, 
	    &x0,&y0,&blk,&pinloc) == 8 ){
	    if( strcmp(netName,oldNetName) != STRINGEQ ){
		outputNet(segTable,segCount-1,rowHeight,netName) ;
		/* free memory of last net  */
		for (i=1;i<segCount;i++){
		    free(segTable[i]);
		}
		segCount = 1 ;
		 
	    } 
	    /* make segTable larger if necessary */
	    if( segCount +1 >= curSize ){
		curSize += 10 ;  /* make array in increments of 10 */
		segTable = (routeBoxPtr *) 
			Ysafe_realloc(segTable,
			    curSize*sizeof(routeBoxPtr));
	    }
	    curSeg = segTable[segCount++] = (routeBoxPtr)
			     Ysafe_malloc(sizeof(routeBox)) ;
	    curSeg->groupNo = groupNo ;
	    curSeg->x0 = x0 ;
	    curSeg->y0 = y0 ;
	    curSeg->pinloc = pinloc ;

	    if( strcmp(cellName,"PSEUDO_CELL") == STRINGEQ ){
		curSeg->pseudoFlag = TRUE ;
	    } else {
		curSeg->pseudoFlag = FALSE ;
	    }
	}
	sprintf(oldNetName,"%s",netName);
    }
    fclose(pinFile) ;

    /* output the last net */
    outputNet(segTable,segCount-1,rowHeight,netName) ;
    /* free memory of last net  */
    for (i=1;i<segCount;i++){
	free(segTable[i]);
    }
    TWflushFrame() ;
}

} /* end drawSC */  

outputNet(segTable,segCount,rowHeight,netName)
routeBoxPtr  *segTable;
int 	     segCount ; 
int          rowHeight ;
char         *netName ;
{

routeBoxPtr  nextSeg ,
	     curSeg ;
int          separation ,
	     factor ,
	     i,
	     k,
	     upBound,
	     lowBound,
	     groupNo,
	     net ; 

static int   netCount ;
 
/* if netname is not numeric use a net counter */
if (!(net = atoi(netName))){
    net = ++netCount ;
}

#ifdef DEBUG
D( "outputNet",printf("Before sort for net %s\n",netName) );
for (i=1;i<=segCount;i++){
    D( "outputNet", printf("segCount:%d groupNo:%d\n",
	i,segTable[i]->groupNo )) ;
}
#endif

/* sort the segTable with a quick sort */
quickSort(segTable,1,segCount,SORTBYGROUP); 

#ifdef DEBUG
D(  "outputNet", printf("After sort for net %s\n",netName) );
for (i=1;i<=segCount;i++){
    D( "outputNet", printf("segCount:%d groupNo:%d\n",
	i,segTable[i]->groupNo )) ;
}
#endif

separation = rowHeight / 4 ;
for (i=1;i<=segCount;){
    /* find boundary of group */
    groupNo = segTable[i]->groupNo ; 
    for( lowBound=i;i<=segCount;i++){
	if (segTable[i]->groupNo != groupNo){
	    break ;
	} 
    }
    upBound = i - 1;  /* i now stores the beginning of next group */

    /* sort the segTable by x to get pretty picture */
    quickSort(segTable,lowBound,upBound,SORTBYX); 

    /* do all of one groupNumber */
    for (k=lowBound;k<=upBound;k++){
	curSeg = segTable[k] ;
	if( k < upBound ){
	    nextSeg = segTable[k+1] ; 
	    if( curSeg->y0 != nextSeg->y0 ||
		curSeg->x0 == nextSeg->x0 ){  /* no need to bend */
		TWdrawNet( net,
			curSeg->x0,
			curSeg->y0,
			nextSeg->x0,
			nextSeg->y0,
			NETCOLOR, NULL ) ;
		D( "outputNet", printf("%d, %d, %d, %d, %d, color: %s\n", 
			net,
			curSeg->x0,
			curSeg->y0,
			nextSeg->x0,
			nextSeg->y0,
			NETCOLOR, NULL )) ;
	    } else { /* we need to bend the net */
		if( curSeg->pinloc == -1){ /* bottom of channel*/ 
		    factor = 1;   /* bend upwards */
		} else {
		    factor = -1;  /* bend downwards */
		}
		TWdrawNet( net,
			curSeg->x0,
			curSeg->y0,
			(curSeg->x0 + nextSeg->x0)/2,
			curSeg->y0 + factor * separation,
			NETCOLOR, NULL ) ;
		TWdrawNet( net,
			(curSeg->x0 + nextSeg->x0)/2,
			curSeg->y0 + factor * separation,
			nextSeg->x0,
			nextSeg->y0,
			NETCOLOR, NULL ) ;
		D(  "outputNet", printf("%d, %d, %d, %d, %d, color: %s\n", 
			net,
			curSeg->x0,
			curSeg->y0,
			(curSeg->x0 + nextSeg->x0)/2,
			curSeg->y0 + factor * separation,
			NETCOLOR) ) ;
		D(  "outputNet", printf("%d, %d, %d, %d, %d, color: %s\n", 
			net,
			(curSeg->x0 + nextSeg->x0)/2,
			curSeg->y0 + factor * separation,
			nextSeg->x0,
			nextSeg->y0,
			NETCOLOR) ) ;
	    }
	}

	/* now output the pins */ 
	if( curSeg->pseudoFlag ){
	    TWdrawPin( net,
		    curSeg->x0 - 1,
		    curSeg->y0 - 1,
		    curSeg->x0 + 1,
		    curSeg->y0 + 1,
		    PSEUDOCOLOR, NULL ) ;
	    D( "outputNet",  printf("%d, %d, %d, %d, %d, color: %s\n", 
		    net,
		    curSeg->x0 - 1,
		    curSeg->y0 - 1,
		    curSeg->x0 + 1,
		    curSeg->y0 + 1,
		    PSEUDOCOLOR, NULL ) ) ;

	} else { /* its a normal pin */
	    TWdrawPin( net,
		    curSeg->x0 - 1,
		    curSeg->y0 - 1, curSeg->x0 + 1,
		    curSeg->y0 + 1,
		    PINCOLOR, NULL ) ;
	    D(  "outputNet", printf("%d, %d, %d, %d, %d, color: %s\n", 
		    net,
		    curSeg->x0 - 1,
		    curSeg->y0 - 1,
		    curSeg->x0 + 1,
		    curSeg->y0 + 1,
		    PINCOLOR, NULL ) ) ;

	}

    } /* end inner for loop */
} /* end outer for */

} /* end outputNet */


/* ***************************************************************** 
translate rotation of cells
----------------------------------------------------------------- */
translate(l,b,r,t, orient) 
int *l, *b, *r, *t, orient ;
{

int temp ;

switch( orient ){
    case 0 :
	    break ;
    case 1 :
	    /* mirror around x - axis */
	    temp   = *t ;
	    *t = - *b ;
	    *b = - temp   ;
	    break ;
    case 2 :
	    /* mirror around y - axis */
	    temp   = *r ;
	    *r = - *l ;
	    *l = - temp   ;
	    break ;
    case 3 :
	    /* rotate 180 */
	    temp   = *t ;
	    *t = - *b ;
	    *b = - temp   ;
	    temp   = *r ;
	    *r = - *l ;
	    *l = - temp   ;
	    break ;
    case 4 :
	    /* mirror x and then rot 90 */
	    temp   = *l ;
	    *l = - *t ;
	    *t = - temp   ;
	    temp   = *r ;
	    *r = - *b ;
	    *b = - temp   ;
	    break ;
    case 5 :
	    /* mirror x and then rot -90 */
	    temp   = *r ;
	    *r = *t ;
	    *t = temp   ;
	    temp   = *l ;
	    *l = *b ;
	    *b = temp   ;
	    break ;
    case 6 :
	    /* rotate 90 degrees */
	    temp   = *l ;
	    *l = - *t ;
	    *t = *r ;
	    *r = - *b ;
	    *b = temp   ;
	    break ;
    case 7 :
	    /* rotate - 90 degrees */
	    temp   = *t ;
	    *t = - *l ;
	    *l = *b ;
	    *b = - *r ;
	    *r = temp   ;
	    break ;
} /* end switch */
} /* end function translate */

#ifdef NEEDED
void   checkPos(pin,pos,llx,lly,urx,ury) 
NBOXPTR pin ;
int pos ;
int llx ;
int lly ;
int urx ;
int ury ;
{

if( pos == NEWPOS){
    if( pin->xpos > urx ){
	printf("ERROR:pin xpos > urx ; set to urx ;");
	pin->xpos = urx ;
    }

    if( pin->xpos < llx ){
	printf("ERROR:pin xpos < llx ; set to llx ;");
	pin->xpos = llx ;
    }

    if( pin->ypos > ury ){
	printf("ERROR:pin ypos > ury ; set to ury ;");
	pin->ypos =ury ;
    }
    if( pin->ypos < lly ){
	printf("ERROR:pin ypos < lly ; set to lly ;");
	pin->ypos =ury ;
    }
} else {
    if( pin->newx > urx ){
	printf("ERROR:pin newx > urx ; set to urx ;");
	pin->newx = urx ;
    }

    if( pin->newx < llx ){
	printf("ERROR:pin newx < llx ; set to llx ;");
	pin->newx = llx ;
    }

    if( pin->newy > ury ){
	printf("ERROR:pin newy > ury ; set to ury ;");
	pin->newy =ury ;
    }
    if( pin->newy < lly ){
	printf("ERROR:pin newy < lly ; set to lly ;");
	pin->newy =ury ;
    }
}

} 
#endif
