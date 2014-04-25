/* ----------------------------------------------------------------- 
FILE:	    partition.c                                       
DESCRIPTION: draw_tiles()
CONTENTS:  draw_tiles()
	
DATE:	 November  , 1989 
REVISIONS: February 7th, 1990 
	   February 15th, 1990 : separated set_limits files from this
				    file and renamed to "partition.c";
                               Interactive line draw and tiles.
	   February 17th, 1990 : Modified the seg_x & y arrays to fit
				  in the core border segments too.
           March 1: tile->width and height calculated here.
	   partitions drawn as line of a differnt color.
----------------------------------------------------------------- */
#ifndef VMS
#ifndef lint
static char SccsId[] = "@(#) partition.c (Yale) version 1.11 5/18/91" ;
#endif
#endif

#include "standard.h"
#include "parser.h"
#include <yalecad/string.h>
#include <yalecad/message.h>
#include <yalecad/draw.h>
#include <yalecad/dialog.h>
#include <yalecad/debug.h>
#include <yalecad/rbtree.h>

#define NUMLINES 30
#define GREATER 1
#define LESS -1
#define EQUAL 0
#define LINES        "DO YOU WANT TO ADD MORE LINES?"
#define MORELINES    "DO YOU WANT TO ADD MORE LINES?"

extern BOOL drawLine ;
static CBOXPTR cptr;
static PTILEPTR ptr;
static CORNERS corptr1,corptr2;
INT *line_x ;
INT *line_y ;
INT num_prcor,num_y,num_x;
INT num_legal_tiles;

typedef struct interval{
       INT p1  ;
       INT p2  ;
       INT secp1  ;
       INT secp2  ;
}
*INTERPTR,
INTER;

YTREEPTR Tiletree,Tilealltree,Tilemacro1tree,Tilemacro2tree;
YTREEPTR XCornerTree, YCornerTree, XIntervalTree,YIntervalTree;
YTREEPTR X_Tree, Y_Tree;

BOOL test_point(x,y) /** returns false for false point and true for true point*/
INT x,y;
{
    if (x < core_x1G || x > core_x2G || y < core_y2G || y > core_y1G) {
	return (FALSE);
    } else {
	return (TRUE);
    }
}

BOOL within_intervalx(x,y1,y2)
INT x,y1,y2;
{
    static INTERPTR ptr;
    static CBOXPTR cptr;

    for ( ptr = (INTERPTR) Yrbtree_enumerate (XIntervalTree,TRUE); ptr;
	ptr = (INTERPTR) Yrbtree_enumerate (XIntervalTree,FALSE) ){
	    if (x > ptr->p1 && x < ptr->p2) {
		if ( y2 > ptr->secp1 && y1  < ptr->secp2 ) { 
			return(TRUE);	
		}	
	    }
    }
    return(FALSE);
}

BOOL within_intervaly(y,x1,x2)
INT y,x1,x2;
{
    static INTERPTR ptr;
    static CBOXPTR cptr;

    for ( ptr = (INTERPTR) Yrbtree_enumerate (YIntervalTree,TRUE); ptr;
	ptr = (INTERPTR) Yrbtree_enumerate (YIntervalTree,FALSE) ){
	    if (y > ptr->p1 && y < ptr->p2) {
		if ( x1 <  ptr->secp2 && x2  > ptr->secp1 ) { 
			return(TRUE);	
		}	
	    }
    }
    return(FALSE);
}


BOOL check_for_split_macro(x1,y1,x2,y2)
INT x1,y1,x2,y2;
{
    INT i,j;
    static CBOXPTR cptr, cptr2;
    static INTERPTR duminter_ptr, foundptr;

    /*** x1,y1 are for upper left point ***
    *** x2,y2 are for lower right point ***/

    if (!test_point(x1,y1)) return(TRUE); /*** outside core or not */
    if (!test_point(x2,y2)) return(TRUE);
    if ((x2 - x1) < delxG ) return(TRUE);
    if ((y2 - y1) < delyG ) return(TRUE);

    if  (within_intervalx(x1,y1,y2)) return(TRUE);	
    if  (within_intervalx(x2,y1,y2)) return(TRUE);	
    if  (within_intervaly(y1,x1,x2)) return(TRUE);	
    if  (within_intervaly(y2,x1,x2)) return(TRUE);	
    return(FALSE);	
}

INT comp_int(t1,t2)
INTERPTR t1,t2;
{
/*** ->p1 is the lower point 
***  ->p2 is the higher point  ***/

  if ( t1->p1 >= t2->p2) return (GREATER);
  else if ( t2->p1 >= t1->p2) return (LESS);
  else if (t1->p1 > t2->p1) return (GREATER);
  else if (t2->p1 > t1->p1) return (LESS);
  /*** t2->p1 = t1->p1 ***/
  else if (t1->p2 > t2->p2) return (GREATER);
  else if (t2->p2 > t1->p2) return (LESS);
  else return (EQUAL);
}

INT compare_x_points(p1,p2)
INT p1,p2;
{
  if ( (p1 - p2) > delxG ) return (GREATER);
  else if ( (p2 - p1) > delxG ) return (LESS);
  else return (EQUAL);
}

INT compare_y_points(p1,p2)
INT p1,p2;
{
  if ( (p1 - p2) > delyG ) return (GREATER);
  else if ( (p2 - p1) > delyG ) return (LESS);
  else return (EQUAL);
}

make_corner_and_intervaltrees()
{

    static int i,j;
    static INTERPTR inter_ptr;

    XCornerTree = Yrbtree_init(compare_x_points);
    YCornerTree = Yrbtree_init(compare_y_points);
    XIntervalTree = Yrbtree_init(comp_int);
    YIntervalTree = Yrbtree_init(comp_int);

    /*** upper right corner of core  ***/

    Yrbtree_insert(XCornerTree, (char*) core_x2G);
    Yrbtree_insert(YCornerTree, (char*) core_y1G);

    /*** lower left corner of core  ***/

    Yrbtree_insert(XCornerTree, (char*) core_x1G);
    Yrbtree_insert(YCornerTree, (char*) core_y2G);

    /**** next insert macro corners **/


    for ( i=1 ; i<= numMacroG ; i++) 
       {   
	   cptr = carrayG[numcellsG + i];
	   inter_ptr = (INTERPTR) Ysafe_malloc (sizeof(INTER));
	   inter_ptr->p1 = cptr->padptr->xpoints[1];
	   inter_ptr->p2 = cptr->padptr->xpoints[3];
	   inter_ptr->secp1 = cptr->padptr->ypoints[1];
	   inter_ptr->secp2 = cptr->padptr->ypoints[3];
	   Yrbtree_insert(XIntervalTree, (char*)inter_ptr);

	   inter_ptr = (INTERPTR) Ysafe_malloc (sizeof(INTER));
	   inter_ptr->p1 = cptr->padptr->ypoints[1];
	   inter_ptr->p2 = cptr->padptr->ypoints[3];
	   inter_ptr->secp1 = cptr->padptr->xpoints[1];
	   inter_ptr->secp2 = cptr->padptr->xpoints[3];
	   Yrbtree_insert(YIntervalTree, (char*)inter_ptr);

	   for ( j = 1; j <= cptr->padptr->corners ; j++ ){
	     Yrbtree_insert(XCornerTree, (char*)cptr->padptr->xpoints[j]);
	     Yrbtree_insert(YCornerTree, (char*)cptr->padptr->ypoints[j]);
	     j++;
	   }
       }

}

VOID
add_partition_corners(x1,y1,x2,y2)
INT x1,y1,x2,y2;
{
   static int i;
   static INTERPTR duminter_ptr, inter_ptr;
   static CBOXPTR cptr;
   static PADBOXPTR padptr;

   Yrbtree_insert(XCornerTree, (char*)x1);
   Yrbtree_insert(XCornerTree, (char*)x2);
   Yrbtree_insert(YCornerTree, (char*)y1);
   Yrbtree_insert(YCornerTree, (char*)y2);
   inter_ptr = (INTERPTR) Ysafe_malloc (sizeof(INTER));
   inter_ptr->p1 = x1;
   inter_ptr->p2 = x2;
   inter_ptr->secp1 = y1;
   inter_ptr->secp2 = y2;
   Yrbtree_insert(XIntervalTree, (char*)inter_ptr);
   inter_ptr = (INTERPTR) Ysafe_malloc (sizeof(INTER));
   inter_ptr->p1 = y1;
   inter_ptr->p2 = y2;
   inter_ptr->secp1 = x1;
   inter_ptr->secp2 = x2;
   Yrbtree_insert(YIntervalTree, (char*)inter_ptr);
}

INT partition_for_tile(x,y)
INT x,y;
{
static INT i;
static PARTNPTR partptr;

	for ( i = 1; i <= num_partnsG; i++) {
		partptr = partarrayG[i];
		if ( x > partptr->upper_left_x &&
				x < partptr->lower_right_x) {
			if ( y < partptr->upper_left_y &&
					y > partptr->lower_right_y) {
				return (i);
			}
		}
	}
	sprintf( YmsgG,"No partition found for tile \n") ;
	M(WARNMSG,"partition",YmsgG);
	return(0);
}

VOID
abut_point(newx, newy, x, y)
INT *newx, *newy, x, y;
{
    INT shiftx, shifty;

    shiftx = (INT)Yrbtree_search(XCornerTree, (char*)x);
    if (shiftx) {
	*newx = shiftx;
    }
    shifty = (INT)Yrbtree_search(YCornerTree, (char*)y);
    if (shifty) {
	*newy = shifty;
    }
}

INT compint(t1,t2)
INT t1,t2;
{
    if (t1 > t2 ) return(GREATER);
    else if (t1 < t2 ) return(LESS);
    return(EQUAL);
}

draw_tiles()
{
    static INT x, y;
    char line_info[20],ans[2];
    static int p,i,j;
    BOOL lines ;
    BOOL more_lines ;

/* calculate the number of part_tiles : (number of vertical lines -1)
    * (number of horizontal lines -1)
    number of vertical lines = 2 * # of macros + 2(side walls) - 
    possible overlaps
    number of horizontal lines = 2 * # of macros + 2(side walls) - 
    possible overlaps

    dump all x's and core_x1G and cor_x2 into a single array line_x and sort 
    and dump all y's and core_y1G and cor_y2 into a single array line_y and
       sort  */


    line_x = (INT *) Ysafe_malloc (NUMLINES * sizeof(INT));
    line_y = (INT *) Ysafe_malloc (NUMLINES * sizeof(INT));

    /*** need new tree for new comparison function*/
    X_Tree = Yrbtree_init(compint);
    Y_Tree = Yrbtree_init(compint); 
    i = 0;

    for ( x = (INT) Yrbtree_enumerate (XCornerTree,TRUE); x;
	x = (INT) Yrbtree_enumerate (XCornerTree,FALSE) ){
	Yrbtree_insert(X_Tree, (char*)x);
	line_x[++i] = x;
    }
    num_x = i;
    i = 0;

    for ( y = (INT) Yrbtree_enumerate (YCornerTree,TRUE); y;
	y = (INT) Yrbtree_enumerate (YCornerTree,FALSE) ){
	Yrbtree_insert(Y_Tree, (char*)y);
	line_y[++i] = y;
    }
    num_y = i;

    add_auto_lines();

    bubble_sort(line_x,num_x) ;
    bubble_sort(line_y,num_y) ;

    vlineG = clean_red(line_x,num_x);
    hlineG = clean_red(line_y,num_y);
    num_x = vlineG;
    num_y = hlineG;

    num_ptileG = (vlineG - 1) * (hlineG - 1) ;
    make_tiles();

}

add_auto_lines()
{

    static INT mid_x,first_x,sec_x;
    static INT virtual_first_x,virtual_sec_x ;
    static INT virtual_third_x,virtual_frth_x,x;
    static INT mid_y,first_y,sec_y;
    static INT virtual_first_y,virtual_sec_y ;
    static INT virtual_third_y,virtual_frth_y,y;

    /**** add more lines in sparse regions automatically ****
    first find the mid point; labels indicate the labels in my notes  */

    mid_x = (core_x2G + core_x1G)/2; /* 2 */
    first_x = (mid_x + core_x1G)/2; /* 1 */
    sec_x = (core_x2G + mid_x)/2; /* 3 */

    virtual_first_x = (first_x + core_x1G)/2;  /* a */
    virtual_sec_x = (mid_x + first_x)/2; /* b */
    virtual_third_x = (sec_x + mid_x)/2; /* c */
    virtual_frth_x = (core_x2G + sec_x)/2; /* d */
    x = 0;
    if (!(x = (INT) Yrbtree_interval (X_Tree,(char*)virtual_first_x,
		(char*)virtual_sec_x,TRUE))){
	/* introduce 1 */
	line_x[++num_x] = first_x;
    }
    x = 0;
    if (!(x = (INT) Yrbtree_interval (X_Tree,(char*)virtual_sec_x,
		(char*)virtual_third_x,TRUE))){
	/* introduce 2 */
	line_x[++num_x] = mid_x;
    }
    x = 0;
    if (!(x = (INT) Yrbtree_interval (X_Tree,(char*)virtual_third_x,
		(char*) virtual_frth_x,TRUE))){
	/* introduce 3 */
	line_x[++num_x] = sec_x;
    }

    mid_y = (core_y1G + core_y2G)/2; /* 2 */
    first_y = (mid_y + core_y2G)/2; /* 1 */
    sec_y = (core_y1G + mid_y)/2; /* 3 */

    virtual_first_y = (first_y + core_y2G)/2;  /* a */
    virtual_sec_y = (mid_y + first_y)/2; /* b */
    virtual_third_y = (sec_y + mid_y)/2; /* c */
    virtual_frth_y = (core_y1G + sec_y)/2; /* d */

    y = 0;
    if (!(y = (INT) Yrbtree_interval (Y_Tree,(char*)virtual_first_y,
		(char*)virtual_sec_y,TRUE))){
	/* introduce 1 */
	line_y[++num_y] = first_y;
    }
    y = 0;
    if (!(y = (INT) Yrbtree_interval (Y_Tree,(char*)virtual_sec_y,
		(char*)virtual_third_y,TRUE))){
	/* introduce 2 */
	line_y[++num_y] = mid_y;
    }
    y = 0;
    if (!(y = (INT) Yrbtree_interval (Y_Tree,(char*)virtual_third_y,
		(char*) virtual_frth_y,TRUE))){
	/* introduce 3 */
	line_y[++num_y] = sec_y;
    }

}

addhline(y)
int y;
{
   line_y[++num_y] = y;
}

addvline(x)
int x;
{
   line_x[++num_x] = x;
}


make_tiles()
{
    static int count_y,count_x, t_width, t_height;
    static int i,j,tile,segm,num;

/*  Allocate memory for tile structure ****/

    tarrayG = (PTILEPTR *) Ysafe_calloc (( num_ptileG +1) , sizeof (PTILEPTR));
    for( tile = 1 ; tile <= num_ptileG; tile++ ) 
         ptr = tarrayG[ tile ] = (PTILEPTR) Ysafe_calloc(1, sizeof(PTBOX) ) ;

/*  form the tile datastructure ****/
    tile = 1 ; 
      count_y = count_x = 0;
      for (j=1;j<= hlineG-1;j++)
      {
         count_y++;
         count_x = 0;
         if ( line_y[j] == line_y[j+1] ) j++;
         for (i=1;i<= vlineG-1;i++)
          {
           ptr = tarrayG[ tile] ;
           ptr->id = tile;

           ptr->upper_left_y = line_y[j+1];
           ptr->upper_left_x = line_x[i];

           if ( line_x[i] == line_x[i+1]) i++;
           ptr->lower_right_x = line_x[i+1];
           ptr->lower_right_y = line_y[j];
           ptr->partition_id = partition_for_tile((ptr->lower_right_x-1),
			(ptr->lower_right_y+1)); 
           t_height = ptr->upper_left_y - ptr->lower_right_y;
           t_width = ( - ptr->upper_left_x + ptr->lower_right_x);
           ptr->area = (t_height) * (t_width);

           count_x++;
           ptr->grid_loc_x = count_x ;
           ptr->grid_loc_y = count_y;
           ptr->center_x = ptr->upper_left_x + (t_width/2);
           ptr->center_y = ptr->lower_right_y + (t_height/2);
           set_capacity(ptr); 
	   if (ptr->legal) {
 	   /** decrement area of partptr involved for the macro case and 
			thus partptr->capacity */
		if (ptr->partition_id ) {
		    partarrayG[ptr->partition_id]->area -= ptr->area ;
		    part_capacity(partarrayG[ptr->partition_id]) ;
		}
	   }
	   if (!ptr->partition_id) ptr->capacity = 0;
           if (++tile > num_ptileG)
         	break;
          }
        if (tile > num_ptileG)
         	break;
     }
     makeallTiletree();
     makemacroTiletree();
}

INT comparemacroTiles(t1,t2)
PTILEPTR t1,t2;
{
    if (t1->legal > t2->legal ) return(GREATER);
    else if (t1->legal < t2->legal ) return(LESS);
    return(EQUAL);
}


INT comparelegalTiles(t1,t2)
PTILEPTR t1,t2;
{
  if ( t1->lower_right_y >= t2->upper_left_y) return (GREATER);
  else if ( t2->lower_right_y > t1->upper_left_y) 
						return (LESS);
  else if ( t1->upper_left_x >= t2->lower_right_x)
					return (GREATER);
  else if ( t2->upper_left_x > t1->lower_right_x)
						return (LESS);
  else return (EQUAL);
}


makeallTiletree()
{
    static int tile;
    static PTILEPTR tptr;
    Tilealltree = Yrbtree_init(comparelegalTiles);
    for (tile = 1; tile<= num_ptileG; tile++){
	tptr = tarrayG[tile];
	Yrbtree_insert(Tilealltree, (char*)tptr);
    }
}

makemacroTiletree()
{
    static int tile;
    static PTILEPTR tptr;
    Tilemacro1tree = Yrbtree_init(comparemacroTiles);
    Tilemacro2tree = Yrbtree_init(comparelegalTiles);
    for (tile = 1; tile<= num_ptileG; tile++){
	tptr = tarrayG[tile];
	if (tptr->legal)
	Yrbtree_insert(Tilemacro1tree, (char*)tptr);
	Yrbtree_insert(Tilemacro2tree, (char*)tptr);
    }
}


makelegalTiletree()
{
    static int tile;
    static PTILEPTR tptr;

    Tiletree = Yrbtree_init(comparelegalTiles);
    for (tile = 1; tile<= num_ptileG; tile++){
	tptr = tarrayG[tile];
	if (tptr->capacity == 0 || tptr->legal) continue;
	Yrbtree_insert(Tiletree, (char*)tptr);
    }
    num_legal_tiles = Yrbtree_size(Tiletree);
}

