/* ----------------------------------------------------------------- 
FILE:	    twmc.c                                       
DESCRIPTION:Main routine for drawing MC data program.
CONTENTS:   drawMC( design )
		char *design ;
DATE:	    Jan 25, 1989 - major rewrite of version 1.0
REVISIONS:  
----------------------------------------------------------------- */
#ifndef lint
static char SccsId[] = "@(#) twmc.c version 3.3 6/19/90" ;
#endif

#include <stdio.h>
#include "globals.h"

drawMC( design )
char *design ;
{

int         x0,
	    y0,
	    x1,
	    y1,
	    segCount ,
	    i ,
	    curSize ,
	    orient,
	    net = 0 ,
	    cellCount = 0 ,
	    pinloc,
	    groupNo,
	    blk,
	    rowHeight,
	    toggle = TRUE ,
	    firstCell = TRUE ;
INT	    numtokens;
char        buffer[LRECL],
	    cellName[LRECL],
	    input[LRECL],
	    color[LRECL],
	    message[LRECL],
	    vertices[LRECL],
	    netName[LRECL],
	    oldNetName[LRECL],
	    pinName[LRECL],
	    pin[LRECL],
	    filename[LRECL],
	    *bufferptr ,
	    **tokens ;
void        checkPos();
FILE        *placeFile ,
	    *pinFile ;
routeBoxPtr *segTable,
	    curSeg ;

int         k , Pk[2] , Pl[2] , Pm[2] ,
	    x, y, count,
	    xmin , ymin , maxx, minx, maxy, miny, kmin , found ;

typedef struct bustbox {
    int xc ;
    int yc ;
} BUSTBOX ;

BUSTBOX     A[31] ,
	    R[5] ;

if(!( YdirectoryExists("DATA") )){
    system("mkdir DATA") ;
}

sprintf( filename, "%s.dat", design);
if( placeFile = fopen(filename,"r" )){ 
    while( bufferptr=fgets(buffer,LRECL,placeFile )){
	if( strncmp(bufferptr,"vertices",8 ) == STRINGEQ){
	    count = 0 ;
	    /* delimiters are spaces newlines and tabs */
	    tokens = Ystrparser(bufferptr," \n\t",&numtokens) ;

	    for( k=1;k<numtokens;k++ ){
		A[ ++count ].xc = atoi(tokens[k]) ;
		A[ count ].yc = atoi(tokens[++k]) ;
	    }

	    for( k = 1 ; k <= count ; k++ ) {
		x = A[k].xc ;
		y = A[k].yc ;
		if( k == 1 ) {
		    minx = x ;
		    miny = y ;
		    maxx = x ;
		    maxy = y ;
		} else {
		    if( x < minx ) {
			minx = x ;
		    }
		    if( x > maxx ) {
			maxx = x ;
		    }
		    if( y < miny ) {
			miny = y ;
		    }
		    if( y > maxy ) {
			maxy = y ;
		    }
		}
	    }
	    do {
		/*  find Pk  */
		ymin = INT_MAX ;
		for( k = 1 ; k <= count ; k++ ) {
		    if( A[k].yc < ymin ) {
			ymin = A[k].yc ;
		    }
		}  /* we have the lowest y coordinate  */
		xmin = INT_MAX ;
		for( k = 1 ; k <= count ; k++ ) {
		    if( A[k].yc == ymin ) {
			if( A[k].xc < xmin ) {
			    xmin = A[k].xc ;
			    kmin = k ;
			}
		    }
		}  /*  we have the leftmost lowest corner  */
		Pk[0] = xmin ;
		Pk[1] = ymin ;
		xmin = INT_MAX ;
		for( k = 1 ; k <= count ; k++ ) {
		    if( k == kmin ) {
			continue ;
		    }
		    if( A[k].yc == ymin ) {
			if( A[k].xc < xmin ) {
			    xmin = A[k].xc ;
			}
		    }
		}   /*  we have the next leftmost lowest corner  */
		Pl[0] = xmin ;
		Pl[1] = ymin ;
		ymin = INT_MAX ;
		for( k = 1 ; k <= count ; k++ ) {
		    if( A[k].yc == Pk[1] ) {
			continue ;
		    }
		    if( A[k].yc < ymin ) {
			ymin = A[k].yc ;
		    }
		}  /* we have the next lowest y coordinate  */
		xmin = INT_MAX ;
		for( k = 1 ; k <= count ; k++ ) {
		    if( A[k].yc == ymin ) {
			if( A[k].xc < Pk[0] || A[k].xc > Pl[0] ) {
			    continue ;
			}
			if( A[k].xc < xmin ) {
			    xmin = A[k].xc ;
			}
		    }
		}  /*  we have the leftmost next lowest corner  */
		Pm[0] = xmin ;
		Pm[1] = ymin ;

		/*
		 *  According to the instruction sheet I read, we can
		 *  output the bounding rectangle of Pk , Pl , Pm.
		 */
		R[1].xc = Pk[0] ;
		R[1].yc = Pk[1] ;
		R[2].xc = Pk[0] ;
		R[2].yc = Pm[1] ;
		R[3].xc = Pl[0] ;
		R[3].yc = Pm[1] ;
		R[4].xc = Pl[0] ;
		R[4].yc = Pk[1] ;

		/*  
		 *  Now weed out those elements of R which are in A and
		 *  add those elements of R which are not in A.
		 *  Note that index 1 and 4 are necessarily in A, and thus
		 *  have to be removed from A.
		 */
		for( k = 1 ; k <= count ; k++ ) {
		    if( R[1].xc == A[k].xc && R[1].yc == A[k].yc ) {
			A[k].xc = A[ count ].xc ;
			A[k].yc = A[ count-- ].yc ;
			break ;
		    }
		}
		for( k = 1 ; k <= count ; k++ ) {
		    if( R[4].xc == A[k].xc && R[4].yc == A[k].yc ) {
			A[k].xc = A[ count ].xc ;
			A[k].yc = A[ count-- ].yc ;
			break ;
		    }
		}
		found = 0 ;
		for( k = 1 ; k <= count ; k++ ) {
		    if( R[2].xc == A[k].xc && R[2].yc == A[k].yc ) {
			A[k].xc = A[ count ].xc ;
			A[k].yc = A[ count-- ].yc ;
			found = 1 ;
			break ;
		    }
		}
		if( found == 0 ) {
		    /*
		     *  Add the thing to the list A
		     */
		    A[ ++count ].xc = R[2].xc ;
		    A[ count ].yc = R[2].yc ;
		}
		found = 0 ;
		for( k = 1 ; k <= count ; k++ ) {
		    if( R[3].xc == A[k].xc && R[3].yc == A[k].yc ) {
			A[k].xc = A[ count ].xc ;
			A[k].yc = A[ count-- ].yc ;
			found = 1 ;
			break ;
		    }
		}
		if( found == 0 ) {
		    /*
		     *  Add the thing to the list A
		     */
		    A[ ++count ].xc = R[3].xc ;
		    A[ count ].yc = R[3].yc ;
		}

		if( toggle ){
		    TWdrawCell( ++cellCount, 
			    R[1].xc ,
			    R[1].yc ,
			    R[4].xc ,
			    R[2].yc ,
			    ROWCOLOR ,
			    cellCount ) ;
		} else {
		    TWdrawCell( ++cellCount,
			    R[1].xc ,
			    R[1].yc ,
			    R[4].xc ,
			    R[2].yc ,
			    ROWCOLOR2 ,
			    cellCount ) ;
		}
	    } while( count > 0 ) ;

	    if( toggle ){
		toggle = FALSE ;
	    } else {
		toggle = TRUE ;
	    }
	}
    }
    fclose(placeFile) ;

} else {
    sprintf(message,"Could not open placement file:%s",filename) ;
    M(ERRMSG,"main",message);
    YexitPgm(PGMFAIL);
}


sprintf( filename, "%s.dat", design);
if( placeFile = fopen(filename,"r" )){ 
    while( bufferptr=fgets(buffer,LRECL,placeFile )){
	if( strncmp(bufferptr,"pin",3 ) == STRINGEQ){

	    if( sscanf(bufferptr,"%s%s%s%d%d",pin,pinName,netName,&x,&y) 
		== 5 ){

		TWdrawPin( ++net,
			x - 1 ,
			y - 1 , 
			x + 1 ,
			y + 1 ,
			PINCOLOR, 
			NULL ) ;
	    }
	}
    }
    fclose(placeFile) ;
}

sprintf( filename, "%s.rte", design);
if( placeFile = fopen(filename,"r" )){ 
    net = 0 ;
    while( bufferptr=fgets(buffer,LRECL,placeFile )){
	tokens = Ystrparser(bufferptr," \n\t",&numtokens) ;

#ifdef LATER
	TWdrawNet( ++net,
		    tokens[4] ,
		    tokens[6] ,
		    tokens[4] ,
		    tokens[12] ,
		    NETCOLOR) ;
	TWdrawNet( ++net,
		    tokens[4] ,
		    tokens[12] ,
		    tokens[10] ,
		    tokens[12] ,
		    NETCOLOR) ;
	TWdrawNet( ++net,
		    tokens[10] ,
		    tokens[12] ,
		    tokens[10] ,
		    tokens[6] ,
		    NETCOLOR) ;
	TWdrawNet( ++net,
		    tokens[10] ,
		    tokens[6] ,
		    tokens[4] ,
		    tokens[6] ,
		    NETCOLOR) ;
#endif
    }
    fclose(placeFile) ;
}


#ifdef TRY
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
		outputNet(segTable,segCount-1,fp,fpp,rowHeight,netName) ;
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
    outputNet(segTable,segCount-1,fp,fpp,rowHeight,netName) ;
    /* free memory of last net  */
    for (i=1;i<segCount;i++){
	free(segTable[i]);
    }
}
#endif
}  

outputNetMC(segTable,segCount,netFile,pinFile,rowHeight,netName)
routeBoxPtr  *segTable;
int 	     segCount ; 
FILE         *netFile ;
FILE         *pinFile ;
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
D( "outputNetMC", printf("Before sort for net %s\n",netName) );
for (i=1;i<=segCount;i++){
    D( "outputNetMC", printf("segCount:%d groupNo:%d\n",
	i,segTable[i]->groupNo )) ;
}
#endif

/* sort the segTable with a quick sort */
quickSort(segTable,1,segCount,SORTBYGROUP); 

#ifdef DEBUG
D(  "outputNetMC", printf("After sort for net %s\n",netName) );
for (i=1;i<=segCount;i++){
    D( "outputNetMC", printf("segCount:%d groupNo:%d\n",
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
		fprintf(netFile,"%d, %d, %d, %d, %d, color: %s\n", 
			net,
			curSeg->x0 ,
			curSeg->y0 ,
			nextSeg->x0 ,
			nextSeg->y0 ,
			NETCOLOR) ;
		D( "outputNetMC", printf("%d, %d, %d, %d, %d, color: %s\n", 
			net,
			curSeg->x0 ,
			curSeg->y0 ,
			nextSeg->x0 ,
			nextSeg->y0 ,
			NETCOLOR)) ;
	    } else { /* we need to bend the net */
		if( curSeg->pinloc == -1){ /* bottom of channel*/ 
		    factor = 1;   /* bend upwards */
		} else {
		    factor = -1;  /* bend downwards */
		}
		fprintf(netFile,"%d, %d, %d, %d, %d, color: %s\n", 
			net,
			curSeg->x0 ,
			curSeg->y0 ,
			(curSeg->x0 + nextSeg->x0)/2 ,
			curSeg->y0 + factor * separation ,
			NETCOLOR) ;
		fprintf(netFile,"%d, %d, %d, %d, %d, color: %s\n", 
			net,
			(curSeg->x0 + nextSeg->x0)/2 ,
			curSeg->y0 + factor * separation ,
			nextSeg->x0 ,
			nextSeg->y0 ,
			NETCOLOR) ;
		D(  "outputNetMC", printf("%d, %d, %d, %d, %d, color: %s\n", 
			net,
			curSeg->x0 ,
			curSeg->y0 ,
			(curSeg->x0 + nextSeg->x0)/2 ,
			curSeg->y0 + factor * separation ,
			NETCOLOR) ) ;
		D(  "outputNetMC", printf("%d, %d, %d, %d, %d, color: %s\n", 
			net,
			(curSeg->x0 + nextSeg->x0)/2 ,
			curSeg->y0 + factor * separation ,
			nextSeg->x0 ,
			nextSeg->y0 ,
			NETCOLOR) ) ;
	    }
	}

	/* now output the pins */ 
	if( curSeg->pseudoFlag ){
	    fprintf(pinFile,"%d, %d, %d, %d, %d, color: %s\n", 
		    net,
		    curSeg->x0 - 1 ,
		    curSeg->y0 - 1 ,
		    curSeg->x0 + 1 ,
		    curSeg->y0 + 1 ,
		    PSEUDOCOLOR) ;
	    D(  "outputNetMC", printf("%d, %d, %d, %d, %d, color: %s\n", 
		    net,
		    curSeg->x0 - 1 ,
		    curSeg->y0 - 1 ,
		    curSeg->x0 + 1 ,
		    curSeg->y0 + 1 ,
		    PSEUDOCOLOR) ) ;

	} else { /* its a normal pin */
	    fprintf(pinFile,"%d, %d, %d, %d, %d, color: %s\n", 
		    net,
		    curSeg->x0 - 1 ,
		    curSeg->y0 - 1 , curSeg->x0 + 1 ,
		    curSeg->y0 + 1 ,
		    PINCOLOR) ;
	    D(  "outputNetMC", printf("%d, %d, %d, %d, %d, color: %s\n", 
		    net,
		    curSeg->x0 - 1 ,
		    curSeg->y0 - 1 ,
		    curSeg->x0 + 1 ,
		    curSeg->y0 + 1 ,
		    PINCOLOR) ) ;

	}

    } /* end inner for loop */
} /* end outer for */

} /* end outputNet */

