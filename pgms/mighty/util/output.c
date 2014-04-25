/* ----------------------------------------------------------------- 
FILE:	    draw.c                                       
DESCRIPTION:Draw data to the screen and cif files.
CONTENTS:   translate2Draw( design, infoPtr )
		char *design ;
		infoRec *infoPtr ;
DATE:	    May 23, 1989 - added heading.
REVISIONS:  May 25, 1989 - removed extraneous code.
----------------------------------------------------------------- */
#ifndef lint
static char SccsId[] = "@(#) output.c version 1.1 12/16/89" ;
#endif

#include <stdio.h>
#include <yalecad/base.h>
#include <yalecad/wgraphics.h>
#include <yalecad/colors.h>
#include <yalecad/debug.h>
#include <globals.h>

#define LAYER1       1
#define LAYER2       2
#define LAYER3       3
#define LAYER1COLOR  TWBLUE
#define LAYER2COLOR  TWGREEN
#define LAYER3COLOR  TWRED
#define PINCOLOR     TWBLACK
#define PSEUDOCOLOR  TWORANGE
#define PINSIZE      1


process_output( out )
FILE *out ;
{

    int         x0, y0, x1, y1,
		net ,
		orient ,
		color,
		layer ;
    char        buffer[LRECL],
		*Yremove_lblanks(),
		*bufferptr ;
    char        netname[LRECL] ;
    TBOOL       viasFound,
		wiringFound ;



    /* perform initialization */
    wiringFound = FALSE ;
    viasFound = FALSE ;

    while( bufferptr=fgets(buffer,LRECL,out )){
	bufferptr = Yremove_lblanks( bufferptr ) ;
	if( strncmp(bufferptr,"vias",4) == STRINGEQ ){
	    viasFound = TRUE ;
	    continue ;
	}
	if( strncmp(bufferptr,"wires",5 ) == STRINGEQ ){
	    wiringFound = TRUE ;
	    viasFound = FALSE ;
	    continue ;
	}
	if( viasFound ){
	    if (sscanf(bufferptr,"%d%d%d%d",&net,&x0,&y0,&layer) == 4 ){
		if( layer == 1 ){ /* 1 -> 2 via  */
		    TWdrawPin( net,
			(int)(x0*maG) - PINSIZE ,
			(int)(y0*maG) - PINSIZE  ,
			(int)(x0*maG) + PINSIZE ,
			(int)(y0*maG) + PINSIZE  ,
			TWBLUE, NULL ) ;
		} else {          /* 2 -> 3 via  */
		    TWdrawPin( net,
			(int)(x0*maG) - PINSIZE ,
			(int)(y0*maG) - PINSIZE  ,
			(int)(x0*maG) + PINSIZE ,
			(int)(y0*maG) + PINSIZE  ,
			TWRED, NULL ) ;
		}
	    }
	}
	if( wiringFound ){
	    if (sscanf(bufferptr,"%d%d%d%d%d%d",&net,&x0,&y0,&x1,&y1,
	    &layer ) == 6 ){
		sprintf( netname, "N%d", net ) ;
		/* determine layer color */
		if( layer == LAYER1 ){
		    color = LAYER1COLOR ;
		} else if( layer == LAYER2 ){
		    color = LAYER2COLOR ;
		} else if( layer == LAYER3 ){
		    color = LAYER3COLOR ;
		} else {
		    color = TWBLACK ;
		} 
		TWdrawNet( net,
		    (int)(x0*maG) ,
		    (int)(y0*maG) ,
		    (int)(x1*maG) ,
		    (int)(y1*maG) ,
		    color, netname ) ;
	    }
	}
    } /* end while */


}
