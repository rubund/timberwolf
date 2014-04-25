/* ----------------------------------------------------------------- 
FILE:	    quicksort.c                                       
DESCRIPTION:quicksort routines
CONTENTS:   quickSort( segTable,i,j,sortKey )
DATE:	    Jan 25, 1989 - major rewrite of version 1.0
REVISIONS:  
----------------------------------------------------------------- */
#ifndef lint
static char SccsId[] = "@(#) quick.c version 3.1 6/22/89" ;
#endif

#include <stdio.h>
#include "globals.h"

quickSort(segTable,i,j,sortKey)
routeBoxPtr *segTable ;
int i,
    j ,
    sortKey ;
{
    int  pivot ,
	 pivotIndex,
	 k ;

    pivotIndex = findPivot(segTable,i,j,sortKey) ;
    if( pivotIndex >= 0 ){
	if( sortKey == SORTBYGROUP ){
	    pivot = segTable[pivotIndex]->groupNo ;
	} else if( sortKey == SORTBYX ){
	    pivot = segTable[pivotIndex]->x0 ;
	}
	k = partition(segTable,i,j,pivot,sortKey) ;
	quickSort(segTable,i,k-1,sortKey) ;
	quickSort(segTable,k,j,sortKey) ;
    } 
} /* end quickSort */
     
int partition(segTable,i,j,pivot,sortKey) 
routeBoxPtr *segTable ;
int i,
    j,
    pivot,
    sortKey ;

{
    int 	   l,
		   r;
    routeBoxPtr    tempSeg;

    l = i;
    r = j;
    do {
	/* swap element in array */
	tempSeg = segTable[l] ;
	segTable[l] =  segTable[r] ;
	segTable[r] =  tempSeg ;
	if( sortKey == SORTBYGROUP ){
	    while( segTable[l]->groupNo < pivot ){
		l++;
	    }
	    while( segTable[r]->groupNo >= pivot ){
		r--;
	    }
	} else if( sortKey == SORTBYX ){
	    while( segTable[l]->x0 < pivot ){
		l++;
	    }
	    while( segTable[r]->x0 >= pivot ){
		r--;
	    }
	}
     } while(l <= r );
    return(l) ;
} /* end partition */

int findPivot(segTable,i,j,sortKey)
	routeBoxPtr *segTable ;
	int i, j , sortKey;
{
    int firstKey,
	k ;

    if( sortKey == SORTBYGROUP ){
	firstKey = segTable[i]->groupNo ;
    } else if( sortKey == SORTBYX ){
	firstKey = segTable[i]->x0 ;
    }
    for( k=i+1;k<=j;k++ ){
	if( sortKey == SORTBYGROUP ){
	    if (segTable[k]->groupNo > firstKey ){
		return(k) ;
	    } else if (segTable[k]->groupNo < firstKey ){
		return(i) ;
	    }
	} else if( sortKey == SORTBYX ){
	    if (segTable[k]->x0 > firstKey ){
		return(k) ;
	    } else if (segTable[k]->x0 < firstKey ){
		return(i) ;
	    }
	}
    }
    return(-1) ;
}

