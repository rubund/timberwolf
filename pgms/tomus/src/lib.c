/* ----------------------------------------------------------------- 
FILE:	   library.c
DESCRIPTION:This file contains the utility functions for reading 
	    Silvar-Lisco bat library file.
CONTENTS:   
DATE:	     
REVISIONS:  
----------------------------------------------------------------- */
#ifndef lint
static char SccsId[] = "@(#) lib.c version 1.21 9/22/91" ;
#endif

#include <string.h>
#include "standard.h"
#include "main.h"
#include "parser.h" 
#include <yalecad/message.h> 
#include <yalecad/hash.h> 
#include <yalecad/debug.h> 
#include <yalecad/file.h>
#include <yalecad/rbtree.h>
#include <yalecad/string.h>

#define KROY_NSC
#define EXPECTEDNUMNETS  1000
#define EXPECTEDNUMCELLS  3500
#define EXPECTEDSWAPGROUPS  10
#define EXPECTEDNUMPADS     10
#define EXPECTEDNUMPINS  5000
#define LESS -1
#define GREATER 1
#define EQUAL 0
#define MMC 0

/* ##########################  STATIC definitions ###########################*/
static INT  netAllocS ;           /* current space in netarray */
static INT  cellAllocS ;          /* current space in cellarray */
static INT  curNetS ;             /* current net number */
static INT  totalCellS ;          /* current cell number and running
							total    */
static YHASHPTR net_hash_tableS ; /* hash table for cross
						referencing nets    */
static CBOXPTR ptrS ;
static PINBOXPTR pinptrS;
static PINBOXPTR lastpin;
static PADBOXPTR pptrS ;

extern YTREEPTR legal_part_tree;

FILE *fpl2;
char filename[LRECL];

static INT cell, num_parts;
static INT netx ;           /* current net being processed */
static INT pinctr,impinctr,netctr;
static INT cor_i ;   /**** counter for corners for pads and macros ***/
int padleft,padright,padtop,padbottom;
INT partclassG;



static get_stat_hints();



initialise_parser()
{
INT comp_strings();

    numcellsG = 0 ;
    numtermsG = 0 ;
    numMacroG = 0 ;
    TotRegPinsG = 0 ;
    numnetsG = 0 ;
    totalCellS = 0 ;
    mono_class_cellsG = 0;

    /* set the initial datastructure sizes */
    get_stat_hints() ;

    legal_part_tree = Yrbtree_init (comp_strings);
    partclassG = 0;
    net_hash_tableS = Yhash_table_create( 2 * netAllocS ) ;

    sprintf( filename , "%s:0.pl2" , cktNameG ) ;
    fpl2 = TWOPEN( filename , "w", ABORT ) ;
}

#ifdef OLDCODE
initialise_first()
{
cell= 0 ;
terms= 0 ;
pinctr= 0 ;
netctr= 0 ;
impinctr = 0;
mono_class_cellsG = 0;
maketabl( &net_hash_table , TW_PRIME ) ;
}

finalise_first()
{
 	DBOXPTR nptr ;
	static int i;
	numcellsG = cell;
	numtermsG = terms;
	padspace = (double *) Ysafe_malloc( (numtermsG + 1) *
		 sizeof(double) ) ;
	for( i = 1 ; i <= numtermsG ; i++ ) {
        padspace[i] = 0.0 ; /* initializing the ptr array padside  */
        }
        fixLRBTG  = (INT *) Ysafe_malloc( 4 * sizeof( INT ) ) ;
        fixLRBTG[0] = 0 ;
        fixLRBTG[1] = 0 ;
        fixLRBTG[2] = 0 ;
        fixLRBTG[3] = 0 ;
        if( total_row_length < celllenG ) total_row_length = celllenG ; 
netarrayG = (DBOXPTR *) 
	Ysafe_malloc( (netctr +1)* sizeof(DBOXPTR) ) ;
 for( i = 1 ; i <= netctr ; i++ ) {
   nptr = netarrayG[ i ] = (DBOXPTR) Ysafe_malloc( sizeof( DBOX ) ) ;
   nptr->pins    = PINNULL    ;
   nptr->name    = NULL    ;
   nptr->paths   = NULL    ;
   nptr->dflag   = 0       ;
   nptr->xmin    = 0       ;
   nptr->newxmin = 0       ;
   nptr->xmax    = 0       ;
   nptr->newxmax = 0       ;
   nptr->ymin    = 0       ;
   nptr->newymin = 0       ;
   nptr->ymax    = 0       ;
   nptr->newymax = 0       ;
   nptr->ignore   = 0      ; 
   nptr->numpins  = 0      ;
 }

numnetsG = netctr;
return;
}
#endif /* OLDCODE */

INT comp_numbers(a,b)
INT a,b;
{
 if (a < b) return (LESS);
 else if (a > b) return (GREATER);
 else return (EQUAL);
}

INT comp_strings(a,b)
char *a,*b;
{
 if (strcmp (a , b) < 0)  return (LESS);
 else if (strcmp(a , b) > 0)  return (GREATER);
 else return (EQUAL);
}

#ifdef OLDCODE

initialise()
{
static int i;
INT comp_strings();

    carrayG = (CBOXPTR *) 
	Ysafe_malloc(( 1 + numcellsG + numtermsG)  * sizeof( CBOXPTR ) ) ;
	 for( i = 1 ; i <= numcellsG + numtermsG ; i++ ) {

      ptrS = carrayG[ i ] = (CBOXPTR) Ysafe_malloc( sizeof(CBOX) ) ;

      ptrS->cxcenter = 0 ;
      ptrS->cycenter = 0 ;
      ptrS->cheight  = 0 ;
      ptrS->clength  = 0 ;
      ptrS->padptr->padside  = 0 ;
      ptrS->cpclass  = (char**) Ysafe_malloc (sizeof(char*));
      ptrS->cpclass[0] = (char*) Ysafe_malloc( 9 * sizeof(char));
      ptrS->paths    = NULL ;
      ptrS->pins    = PINNULL    ;
  }
cell = 0;
pinctr =  0 ;
impinctr = 0 ;
terms = 0;
legal_part_tree = Yrbtree_init (comp_strings);
partclassG = 0;
sprintf( filename , "%s:0.pl2" , cktNameG ) ;
fpl2 = TWOPEN( filename , "w", ABORT ) ;
}


addCell2()
{
cell++;
}
#endif /* OLDCODE */

addCell(cellname, celltype)
char *cellname;
INT celltype;
{

	totalCellS++;
cell++;
	if( totalCellS >= cellAllocS ){
       		 cellAllocS += EXPECTEDNUMCELLS ;
       		 carrayG = (CBOXPTR *) Ysafe_realloc( carrayG,
       		     cellAllocS * sizeof( CBOXPTR ) ) ;
    	}
        ptrS = carrayG[totalCellS] = (CBOXPTR) Ysafe_malloc( sizeof(CBOX) ) ;

    /* now initialize the data */
        ptrS->cname = cellname ; /* allocated previously in lex */
	ptrS->id = totalCellS ;
        ptrS->cxcenter = 0 ;
        ptrS->cycenter = 0 ;
        ptrS->cheight  = 0 ;
        ptrS->clength  = 0 ;
        ptrS->cpclass  = (char**) Ysafe_malloc (sizeof(char*));
        ptrS->cpclass[0] = (char*) Ysafe_malloc( 9 * sizeof(char));
        ptrS->paths    = NULL ;
        ptrS->pins     = NULL     ;
	ptrS->padptr  = NULL ;
	lastpin = NULL;

	if( celltype == STDCELLTYPE ){
        	numcellsG++ ;
		num_parts = 0 ; /** number of legal partitions this
				 cell can go to **/
        } else if( celltype == PADTYPE || celltype == HARDCELLTYPE ){
#ifdef NSC
			fprintf(fpl2,"%s ", ptrS->cname) ;
#endif /* NSC */
		numtermsG++ ;
		pptrS = ptrS->padptr = 
			(PADBOXPTR) Ysafe_calloc( 1, sizeof(PADBOX) ) ;
		pptrS->padside = 0 ;
		pptrS->corners = 0 ;
		pptrS->xpoints = NULL ;
		pptrS->ypoints = NULL ;
		pptrS->macroNotPad = FALSE ; /* assume a pad */
		if( celltype == HARDCELLTYPE ){
        	    /* set the padside to MMC */
            		pptrS->padside = MMC ;
            		pptrS->macroNotPad = TRUE ;
            		numMacroG++ ;
        	}

	}
} /* end addCell */

#ifdef OLDCODE

addPad_std_cell(input)/* the third string */
 char *input;
{
	terms++ ;
	ptrS = carrayG[ numcellsG + terms ] ;
	lastpin = NULL ;
	ptrS->cname = (char *) Ysafe_malloc( (strlen( input ) + 1 ) *
					    sizeof( char ) ) ;
	sprintf( ptrS->cname , "%s" , input ) ;
}

addPad_and_hard_cell(input,flag)/* the third string */
 char *input;
 BOOL flag ;
{
	terms++ ;
	if ( flag != TRUE ) macrosG++;
	ptrS = carrayG[ numcellsG + terms ] ;
	ptrS->id = numcellsG + terms ;
	lastpin = NULL ;
	ptrS->cname = (char *) Ysafe_malloc( (strlen( input ) + 1 ) *
					    sizeof( char ) ) ;
	sprintf( ptrS->cname , "%s" , input ) ;
        ptrS->cheight = 0 ;
        ptrS->clength = 0 ;

#ifdef NSC
	fprintf(fpl2,"%s ", ptrS->cname) ;
#endif NSC
}

#endif /* OLDCODE */


hard_positions(corners,pad_contextS)
int corners;
BOOL pad_contextS;
{
pptrS = ptrS->padptr ;
pptrS->xpoints = (INT*) Ysafe_calloc( ( corners +1 ) , sizeof(INT));
pptrS->ypoints = (INT*) Ysafe_calloc( ( corners +1 ) , sizeof(INT));
pptrS->corners = corners;
if (pad_contextS != TRUE) num_cornersG +=corners;
cor_i = 0;
}

add_corners(x_coord,y_coord)
int x_coord,y_coord;
{
 pptrS->xpoints[++cor_i] = x_coord;
 pptrS->ypoints[cor_i] = y_coord;
#ifdef NSC
 if (cor_i == 1 || cor_i == 3) fprintf(fpl2,"%d  %d ",x_coord, y_coord);
#endif /* NSC */

}

add_celllen(left,right) 
INT left,right;
{
 celllenG += (right - left) ;
}

add_positions_and_celllen(left,right,bottom,top) /* read the 4 values while parsing */
INT left,right,bottom,top;
{
/* this is for the current cell */
   ptrS->cheight = top - bottom ;
   ptrS->clength =  right - left ;
   celllenG += (right - left) ;
}

add_mono_cells()
{
	if (num_parts == 1) mono_class_cellsG ++;
}

add_legal_parts( part_class )
char *part_class;
{
	num_parts++;
	ptrS->cpclass = (char**) Ysafe_realloc ( ptrS->cpclass, (num_parts+2) * sizeof(char*));
	ptrS->cpclass[num_parts] = (char*) Ysafe_malloc( (strlen( part_class ) + 1 ) * sizeof(char));
	ptrS->cpclass[num_parts + 1] = (char*) Ysafe_malloc( 8  * sizeof(char));
	ptrS->cpclass[num_parts + 1] = NIL(char *); /* to terminate the end */
	sprintf( ptrS->cpclass[0] , "none" ); /* to flag from a no class cell */
	strncpy( ptrS->cpclass[num_parts] , part_class , 8) ;
	if ( strlen (part_class) > 8) {
		M(ERRMSG, "readcell", 
	"Part_class was more than 8 char. long. Tomus is truncating it\n");
	printf(" to : %s\n",  ptrS->cpclass[num_parts]);
	}
	if ( !Yrbtree_search(legal_part_tree, ptrS->cpclass[num_parts] )) {
		Yrbtree_insert( legal_part_tree, ptrS->cpclass[num_parts] );
		partclassG++;
	}
}/** end add_legal_parts **/

#ifdef OLDCODE
add_pin2(input,input2)
char *input,*input2;
{
 if( strcmp( input2 , "TW_PASS_THRU" ) == 0 ) {
            impinctr++ ;
 } else if( strcmp( input2 , "TW_SWAP_PASS_THRU" ) == 0 ) {
            addhash( net_hash_table , input2 , TW_PRIME , &netctr ) ;
            pinctr++ ;
            impinctr++ ;
 } else {
            addhash( net_hash_table , input2 , TW_PRIME , &netctr ) ;
            pinctr++ ;
 }
}

add_equiv(input,layer,xpos,ypos)
char *input;
INT layer,xpos,ypos;
{

 	if (!numMacroG) return;
	else {
		if (!xpos && !ypos) {
			printf("possible error with equiv pin positions\n");
		}
		if (layer != pinptrS->layer){
			printf("possible error with equiv pin layer\n");
		}
		if (!strcmp( input, pinptrS->pinname )) {
			pinptrS->equivx = xpos;
			pinptrS->equivy = ypos;
		} else {
			printf("equivalent pin name does not match pinname \n");
		}
	} /*** add equiv pin to pinptrS **/
}
#endif /* OLDCODE */

static char *add_net_func()
{
    INT *data ;   /* pointer to allocated space for net record in
			hashtable */

    /* how to add the data to the hash table */
    /* create space for data */
    data = (INT *) Ysafe_malloc( sizeof(INT) ) ;
    /* if data is not found in hash table update numnetsG */
    *data = ++numnetsG ;
    return( (char *) data ) ;

} /* end add_net_func */


add_pin( pin_name, signal, layer, xpos, ypos)
char *pin_name, *signal;
int layer, xpos, ypos;
{

    INT *netreturn ;          /* net number found in hash table */
    BOOL notInTable ;         /* net added to table if true */
    DBOXPTR nptr ;            /* the current net record */
    static PINBOXPTR botpinL = NULL ; /* save the last pinptr */


 if( strcmp( signal , "TW_PASS_THRU" ) == 0 ) {
     return;
 }  
 
 /* add to netlist */
 netreturn = (INT *)Yhash_add( net_hash_tableS, signal,
		add_net_func, &notInTable ) ;
 /* check to make sure all is well. notInTable is set if signal
		wasn't in hashtable */
 if(!(netreturn)){
        sprintf( YmsgG, "Trouble adding signal:%s to hash table\n",
			signal ) ;
        M(ERRMSG,"add_pin",YmsgG ) ;
        return ;
 }
 curNetS = *netreturn ;
 /* check memory of netarray */
 if( numnetsG >= netAllocS ){
        netAllocS += EXPECTEDNUMNETS ;
        netarrayG = (DBOXPTR *)
            Ysafe_realloc( netarrayG, netAllocS * sizeof(DBOX) ) ;
 }

 /* see if this is the first time for this signal */
 if( notInTable ){
        nptr = netarrayG[curNetS] = (DBOXPTR) Ysafe_malloc( sizeof(
							DBOX ) ) ;

        nptr->pins  = PINNULL ;
        nptr->name    = signal  ;
        nptr->paths   = NULL    ;
        nptr->dflag   = 0       ;
        nptr->xmin    = 0       ;
        nptr->newxmin = 0       ;
        nptr->xmax    = 0       ;
        nptr->newxmax = 0       ;
 	nptr->ymin    = 0       ;
        nptr->newymin = 0       ;
        nptr->ymax    = 0       ;
        nptr->newymax = 0       ;
        nptr->ignore   = 0      ;
        nptr->min_driver  = (FLOAT) 1.0 ;
        nptr->max_driver  = (FLOAT) 1.0 ;
        nptr->driveFactor = (FLOAT) 0.0 ;
 } else {
        Ysafe_free( signal ) ; /* no need to keep this copy */
        nptr = netarrayG[curNetS] ;
 }
 
 /* create list of pins on the net */
 pinptrS = (PINBOXPTR) Ysafe_malloc( sizeof(PINBOX) );
 pinptrS->next = nptr->pins ;
 nptr->pins = pinptrS ;

 /* create a list of pins for this cell in order as given */
 if( ptrS->pins ){ /* list has already been started */
        botpinL->nextpin = pinptrS ;
 } else {  /* start new list */
        ptrS->pins = pinptrS ;
 }
 pinptrS->nextpin = NULL ;
 botpinL = pinptrS ;

/* now initialize data */
    pinptrS->terminal = ++TotRegPinsG ;
    pinptrS->net      = curNetS ;
    pinptrS->layer    = layer ;
    pinptrS->cell = totalCellS ;
    pinptrS->pinname = pin_name ;
    pinptrS->newx = pinptrS->absx= pinptrS->xpos = xpos ;
    pinptrS->newy = pinptrS->absy= pinptrS->ypos = ypos ;

} /** end add_pin **/

#ifdef OLDCODE

 if( strcmp( signal , "TW_PASS_THRU" ) != 0 ) {
     netx = hashfind( net_hash_table , signal , TW_PRIME ) ;
 if (netarrayG[netx]->dflag == ptrS->id && !macrosG) return;

     if( netarrayG[netx]->name == NULL ) {
        netarrayG[netx]->name = (char *) Ysafe_malloc(
                   (strlen(signal) + 1) * sizeof( char ) ) ;
        sprintf( netarrayG[netx]->name , "%s" ,signal) ;
     }

 pinptrG = (PINBOXPTR) Ysafe_malloc( sizeof( PINBOX ) ) ;
 pinptrG->terminal = ++pinctr ; 
 pinptrG->net      = netx ;
 if( terms == 0 ) {
    netarrayG[netx]->dflag = pinptrG->cell = cell ;
 } else {
    netarrayG[netx]->dflag = pinptrG->cell = numcellsG + terms ; 
 }
 pinptrG->next    = netarrayG[netx]->pins;
 netarrayG[netx]->pins = pinptrG ;
 netarrayG[netx]->numpins += 1 ;

  if( lastpin ){
      lastpin->nextpin = pinptrG ;
  } else {
      ptrS->pins = pinptrG ;
  }
  pinptrG->nextpin = NULL ;
  lastpin = pinptrG ;


pinptrG->pinname = (char *) Ysafe_malloc(
	   (strlen(pin_name) + 1 ) * sizeof( char ) ) ;
sprintf( pinptrG->pinname , "%s" ,pin_name) ;
pinptrG->newx = pinptrG->absx= pinptrG->xpos = xpos ;
pinptrG->newy = pinptrG->absy= pinptrG->ypos = ypos ;
}

addPad_first()
{
 terms++;
}

#endif /* OLDCODE */

add_orient(orient)
INT orient;
{
#ifdef NSC
	fprintf(fpl2," %d 0\n", orient);
#endif
}


add_padside(input)/* the letter followed by orient string */
char *input;
{
	if( strcmp( input , "L" ) == 0 ) {
	    pptrS->padside = 1 ;
	} else if( strcmp( input , "T" ) == 0 ) {
	    pptrS->padside = 2 ;
	} else if( strcmp( input , "R" ) == 0 ) {
	    pptrS->padside = 3 ;
	} else if( strcmp( input , "B" ) == 0 ) {
	    pptrS->padside = 4 ;
#ifdef OLDCODE
	} else if( strcmp( input , "MUL" ) == 0 ) {
	    pptrS->padside = 5 ;
	} else if( strcmp( input , "MUR" ) == 0 ) {
	    pptrS->padside = 6 ;
	} else if( strcmp( input , "MLL" ) == 0 ) {
	    pptrS->padside = 7 ;
	} else if( strcmp( input , "MLR" ) == 0 ) {
	    pptrS->padside = 8 ;
	} else if( strcmp( input , "ML" ) == 0 ) {
	    pptrS->padside = 9 ;
	} else if( strcmp( input , "MR" ) == 0 ) {
	    pptrS->padside = 10 ;
	} else if( strcmp( input , "MB" ) == 0 ) {
	    printf("macro at position MB is no longer supported -- sorry!\n");
	    YexitPgm( PGMFAIL ) ;
	} else if( strcmp( input , "MT" ) == 0 ) {
	    printf("macro at position MT is no longer supported -- sorry!\n");
	    YexitPgm( PGMFAIL ) ;
	} else if( strcmp( input , "MM" ) == 0 ) {
	    printf("macro at position MM is no longer supported -- sorry!\n");
	    YexitPgm( PGMFAIL ) ;
	} else if( strcmp( input , "MTT" ) == 0 ) {
	    pptrS->padside = 14 ;
	} else if( strcmp( input , "MBB" ) == 0 ) {
	    pptrS->padside = 15 ;
#endif /* OLDCODE */
	} else {
	    fprintf(fpoG,"padside not specified properly for ");
	    fprintf(fpoG,"pad: %s\n", ptrS->cname ) ;
	    YexitPgm(PGMFAIL);
	}
}

#ifdef OLDCODE

add_sidespace(space)
double space;
{
	if( pptrS->padside == 1 ) {
	    fixLRBTG[0] = 1 ;	
	} else if( pptrS->padside == 3 ) {
	    fixLRBTG[1] = 1 ;	
	} else if( pptrS->padside == 4 ) {
	    fixLRBTG[2] = 1 ;	
	} else if( pptrS->padside == 2 ) {
	    fixLRBTG[3] = 1 ;	
	} else {
	    macspace[ pptrS->padside ] = space ;
	}
 }

#endif /* OLDCODE */

fixup_configure()
{
static int cells,pin,xFlag,yFlag;
static CBOXPTR cptrS;
static PINBOXPTR pinptrGS;

TWCLOSE( fpl2);
/*
    NOW WE HAVE TO LOAD IN THE OTHER CONFIGURATIONS
*/
for( cells = 1 ; cells <= numcellsG ; cells++ ) {

    cptrS = carrayG[ cells ] ;
    if( cptrS->clength %2 != 0 ) {
	xFlag = 1 ;
    } else {
	xFlag = 0 ;
    }
    if( cptrS->cheight %2 != 0 ) {
	yFlag = 1 ;
    } else {
	yFlag = 0 ;
    }
}
/* 
 *   Configure the blocks, place the macro blocks and pads.
 *   Also generate an initial placement of the standard cells
 */
core_area = ( core_x2G - core_x1G ) * ( core_y1G - core_y2G ) ;
/*macro_and_pad_fix(); */
cell_area = core_area - macro_area;

cell_width();
return ;
}



cell_width()
{
static int shortest_cell,count,temp,cell;
static double deviation ;

for( cell = 1 ; cell <= numcellsG ; cell++ )
 {
      temp += carrayG[ cell ]->clength ;
  }
 mean_width = temp / (numcellsG) ;
 fprintf(fpoG,"Original Average Cell Width:%f\n", mean_width ) ;

  /* modification by Carl 10/5/89 */
  /* an attempt to rectify a large cell problem */
shortest_cell = 10000000 ;
count = 0 ;
temp = 0 ;
for( cell = 1 ; cell <= numcellsG ; cell++ )
 {
    count++ ;
    if( carrayG[cell]->clength <= 2.0 * mean_width ) {
         temp += carrayG[ cell ]->clength ;
    }
    if( carrayG[cell]->clength < shortest_cell ) {
         shortest_cell = carrayG[cell]->clength ;
    }
}
    if( count > 0 ) {
         mean_width = temp / count ;
    } else {
 /* this is only used if all cells are fixed */
     count = 0 ;
     temp = 0 ;
     for(cell= 1 ; cell <= numcellsG ; cell++ ) {
         count++ ;
         temp += carrayG[ cell ]->clength ;
     }
     mean_width = temp / count ;
 }
 fprintf(fpoG,"Adjusted Average Cell Width:%f\n", mean_width ) ;
}

macro_and_pad_fix()    /*** cxcenter and length and height fix ***/
{
static CBOXPTR cptr,cptr2;
static int i,j,delta,cor;
static PINBOXPTR pinptr;
static int a1L,a2L,b1L,b2L,x1L,x2L,y1L,y2L;

/* also translate macros to align to edge of core */

delxG = .05 * ( core_x2G - core_x1G ) ;
delyG = .05 * ( core_y1G - core_y2G ) ;

 for( i = 1;i<= numMacroG; i++ ){
     cptr = carrayG[numcellsG+i];
     cptr->clength =  ABS(cptr->padptr->xpoints[1] -
			cptr->padptr->xpoints[3]);
     cptr->cxcenter =  cptr->padptr->xpoints[1] + cptr->clength/2;

     cptr->cheight =  ABS(cptr->padptr->ypoints[1] -
			cptr->padptr->ypoints[3]);
     cptr->cycenter =  cptr->padptr->ypoints[1] + cptr->cheight/2;
     macro_area += cptr->clength * cptr->cheight;
     if ((cptr->padptr->xpoints[1] - core_x1G) < delxG ){
	delta = cptr->padptr->xpoints[1] - core_x1G;
	cptr->padptr->xpoints[0] = -delta ;
	for (cor = 1; cor <= cptr->padptr->corners ; cor++){
		cptr->padptr->xpoints[cor] -= delta;
	}
	for(pinptr = cptr->pins ; pinptr ; pinptr = pinptr->nextpin ) {
		pinptr->xpos -= delta;
		pinptr->absx = pinptr->newx = pinptr->xpos;
	}
     }
     if ((core_x2G - cptr->padptr->xpoints[3] ) < delxG ){
	delta = core_x2G - cptr->padptr->xpoints[3];
	cptr->padptr->xpoints[0] += delta ;
	for (cor = 1; cor <= 4; cor++){
		cptr->padptr->xpoints[cor] += delta;
	}
	for(pinptr = cptr->pins ; pinptr ; pinptr = pinptr->nextpin ) {
		pinptr->xpos += delta;
		pinptr->absx = pinptr->newx = pinptr->xpos;
	}
     }
     if ((core_y1G - cptr->padptr->ypoints[3] ) < delyG){
	delta = core_y1G - cptr->padptr->ypoints[3];
	cptr->padptr->ypoints[0] = delta ;
	for (cor = 1; cor <= 4; cor++){
		cptr->padptr->ypoints[cor] += delta;
	}
	for(pinptr = cptr->pins ; pinptr ; pinptr = pinptr->nextpin ) {
		pinptr->ypos += delta;
		pinptr->absy = pinptr->newy = pinptr->ypos;
	}
     }
     if ((cptr->padptr->ypoints[1] - core_y2G) < delyG ){
	delta = cptr->padptr->ypoints[1] - core_y2G;
	cptr->padptr->ypoints[0] -= delta ;
	for (cor = 1; cor <= 4; cor++){
		cptr->padptr->ypoints[cor] -= delta;
	}
	for(pinptr = cptr->pins ; pinptr ; pinptr = pinptr->nextpin ) {
		pinptr->ypos -= delta;
		pinptr->absy = pinptr->newy = pinptr->ypos;
	}
     }
}

 for( i = 1;i<= numMacroG; i++ ){
     cptr = carrayG[numcellsG+i];
     x1L = cptr->padptr->xpoints[1];
     x2L = cptr->padptr->xpoints[3];
     y1L = cptr->padptr->ypoints[1];
     y2L = cptr->padptr->ypoints[3];
 	for( j = 1;j<= numMacroG; j++ ){
		if ( i == j) continue;
     		cptr2 = carrayG[numcellsG+j];
     		a1L = cptr2->padptr->xpoints[1];
     		a2L = cptr2->padptr->xpoints[3];
     		b1L = cptr2->padptr->ypoints[1];
     		b2L = cptr2->padptr->ypoints[3];
		/***** X ******/
		if (ABS(x1L - a1L) < delxG ) {
			delta = x1L - a1L;
			shift_cornerx(cptr,delta);
		}
		if (ABS(x1L - a2L) < delxG ) {
			delta = x1L - a2L;
			shift_cornerx(cptr,delta);
		}
		if (ABS(x2L - a1L) < delxG ) {
			delta = x2L - a1L;
			shift_cornerx(cptr,delta);
		}
		if (ABS(x2L - a2L) < delxG ) {
			delta = x2L - a2L;
			shift_cornerx(cptr,delta);
		}
		/***** Y ******/
		if (ABS(y1L - b1L) < delyG ) {
			delta = y1L - b1L;
			shift_cornery(cptr,delta);
		}
		if (ABS(y1L - b2L) < delyG ) {
			delta = y1L - b2L;
			shift_cornery(cptr,delta);
		}
		if (ABS(y2L - b1L) < delyG ) {
			delta = y2L - b1L;
			shift_cornery(cptr,delta);
		}
		if (ABS(y2L - b2L) < delyG ) {
			delta = y2L - b2L;
			shift_cornery(cptr,delta);
		}
	}
 }

 for(;i<= numtermsG; i++ ){
     cptr = carrayG[numcellsG+i];
     cptr->clength =  ABS(cptr->padptr->xpoints[1] -
			cptr->padptr->xpoints[3]);
     cptr->cxcenter =  cptr->padptr->xpoints[1] + cptr->clength/2;

     cptr->cheight =  ABS(cptr->padptr->ypoints[1] -
			cptr->padptr->ypoints[3]);
     cptr->cycenter =  cptr->padptr->ypoints[1] + cptr->cheight/2;
     if (cptr->padptr->padside == 1) {
       if (!padleft) padleft = cptr->cxcenter;
     } else if (cptr->padptr->padside == 3){
       if (!padright) padright = cptr->cxcenter;
     } else if (cptr->padptr->padside == 2){
       if (!padtop) padtop = cptr->cycenter;
     } else if (cptr->padptr->padside == 4){
       if (!padbottom) padbottom = cptr->cycenter;
     }
}
}


shift_cornerx(cellptr,change)
CBOXPTR cellptr;
INT change;
{
static int cor;
static PINBOXPTR pinptr;

	/**** test if the change will cause violation of exceeding core ****/
	if (change < 0) {
		if ((cellptr->padptr->xpoints[3] - change) > core_x2G ){
			return;
		}
	} else {
		if ((cellptr->padptr->xpoints[1] - change) < core_x1G ){
			return;
		}
	}
	for (cor = 1; cor <= 4; cor++){
		cellptr->padptr->xpoints[cor] -= change;
	}
	for(pinptr = cellptr->pins ; pinptr ; pinptr = pinptr->nextpin ) {
		pinptr->xpos -= change;
		pinptr->absx = pinptr->newx = pinptr->xpos;
	}
}

shift_cornery(cellptr,change)
CBOXPTR cellptr;
INT change;
{
static int cor;
static PINBOXPTR pinptr;

	/**** test if the change will cause violation of exceeding core ****/
	if (change < 0) {
		if ((cellptr->padptr->ypoints[3] - change) > core_y1G ){
			return;
		}
	} else {
		if ((cellptr->padptr->ypoints[1] - change) < core_y2G ){
			return;
		}
	}
	for (cor = 1; cor <= 4; cor++){
		cellptr->padptr->ypoints[cor] -= change;
	}
	for(pinptr = cellptr->pins ; pinptr ; pinptr = pinptr->nextpin ) {
		pinptr->ypos -= change;
		pinptr->absy = pinptr->newy = pinptr->ypos;
	}
}

static get_stat_hints()
{
    FILE *fp ;           /* current file */
    char buffer[LRECL] ; /* temp storage */
    char *bufferptr ;    /* pointer to start of the line */
    char **tokens ;      /* tokenized line */
    INT numtokens ;      /* number of tokens on the line */


    sprintf( buffer, "%s.stat", cktNameG ) ;
    if( fp = TWOPEN( buffer, "r", NOABORT ) ){
        /* parse the hints */
        cellAllocS = 0 ;
        while( bufferptr = fgets( buffer, LRECL, fp )){
            tokens = Ystrparser( bufferptr, ":\t\n", &numtokens ) ;
            if( numtokens != 2 ){
                continue ;
            } else if( strcmp( tokens[0],"num_stdcells") == STRINGEQ ){
                cellAllocS += atoi( tokens[1] ) ;
                if( cellAllocS <= 0 ){
                    /* reset if bogus */
                    cellAllocS = EXPECTEDNUMCELLS ;
                }
            } else if( strcmp( tokens[0],"num_nets") == STRINGEQ ){
                netAllocS = atoi( tokens[1] ) ;
                if( netAllocS <= 0 ){
                    /* reset if bogus */
                    netAllocS = EXPECTEDNUMNETS ;
                }
            /* look for macros and pads normally - ports if new format */
            } else if( strcmp( tokens[0],"num_macros") == STRINGEQ ){
                    cellAllocS += atoi( tokens[1] ) ;
            } else if( strcmp( tokens[0],"num_pads") == STRINGEQ ){
                    cellAllocS += atoi( tokens[1] ) ;
            } else if( strcmp( tokens[0],"num_ports") == STRINGEQ ){
            }
        }
        M( MSG, NULL, "\n" ) ;
        sprintf( YmsgG, "Found hints in <%s.stat> file\n", cktNameG ) ;
        M( MSG, "get_stat_hints", YmsgG ) ;
        /* add +1 afterward to account for the 0 record */
        sprintf( YmsgG, "Total cells:%d Number of nets:%d\n\n",
cellAllocS++,netAllocS++) ;
        M( MSG, "get_stat_hints", YmsgG ) ;
    } else {
        cellAllocS = EXPECTEDNUMCELLS ;

       netAllocS = EXPECTEDNUMNETS ;
    }
    /* now allocate the data structures */
    netarrayG = (DBOXPTR *) Ysafe_malloc( netAllocS * sizeof( DBOXPTR ) ) ;
    carrayG = (CBOXPTR *) Ysafe_malloc( cellAllocS * sizeof( CBOXPTR ) ) ;

} /* end get_stat_hints */

YHASHPTR get_net_table()
{
    return( net_hash_tableS ) ;
} /* end get_net_table */

