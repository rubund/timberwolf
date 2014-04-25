/* ----------------------------------------------------------------- 
FILE:	    set_limits.c                                       
DESCRIPTION: Sets the capacity limits of the tiles and the congestion
	     limits of the tile segments. 
CONTENTS:  set_capacity() (for the tiles ) 
           set_congest()  (for the segments)
	   part_capacity() (for the partitions)
	   tile_capacity() (for the tiles after partitions made)
DATE:	  February 14th, 1990
REVISIONS: February 16th, 1990:
		       Added set_congest() routine
		       Added a new field to tile structure: center
           Feb 28th : part_capacity added
	   March 1  : tile_capacity added, field "area" added to tile
     and partition, macro_clearance used to make short tiles over macros
     illegal.
----------------------------------------------------------------- */
#ifndef VMS
#ifndef lint
static char SccsId[] = "@(#) set_limits.c (Yale) version 1.6 2/23/91" ;
#endif
#endif
#include <math.h>
#include "standard.h"
#include "parser.h"

static int ux, uy ;
static int lx, ly ;

set_capacity(ptr)
PTILEPTR ptr;
{

PADBOXPTR padptr ;

/* the tiles which don't contain any macros are legally treated for cell
moves  and the capacity in terms of cell length */

static int i,tmp;
for( i = 1;i<= numMacroG; i++ ){
	 padptr = carrayG[numcellsG+i]->padptr ;
         ux = padptr->xpoints[2]; 
         uy = padptr->ypoints[2]; 
         lx = padptr->xpoints[4]; 
         ly = padptr->ypoints[4]; 

 if (( ptr->upper_left_x >= ux && ptr->lower_right_x <= lx) &&
	  (ptr->upper_left_y <= uy && ptr->lower_right_y >= ly)){
	      ptr->legal = i;
	      i = numMacroG;
	      break;
	      }
  else if (ptr->upper_left_y > uy) {
          if (((ptr->upper_left_y - uy) <= macro_clearance) &&
          (ptr->upper_left_x >= ux && ptr->lower_right_x <= lx)){ 
	      ptr->legal = -1;
	      i = numMacroG;
	      break;
	      }
         }
  else if (ptr->lower_right_y < ly) { 
	 if (((ly - ptr->lower_right_y) <= macro_clearance) &&
         (ptr->upper_left_x >= ux && ptr->lower_right_x <= lx)){
	      ptr->legal = -1;
	      i = numMacroG;
	      break;
	      }
       }
}
      if (!ptr->legal){
	   tmp = (double)ptr->area/(double)cell_area * (double)celllenG;
	   if (tmp>= mean_width && ( ptr->upper_left_y - ptr->lower_right_y) >= rowHeight)
	   ptr->capacity = tmp;
      }
}

part_capacity(partptr)
PARTNPTR partptr;
{
  int limit;

  partptr->capacity = (double)partptr->area/(double)cell_area * (double)celllenG;
  limit = (int) (0.05 * celllenG);
  if (partptr->capacity < limit){
	partptr->capacity = 0;
  }
}

tile_capacity(tileptr)
PTILEPTR tileptr;
{
static int i;
static PARTNPTR partptr;
i = tileptr->partition_id;
partptr = partarrayG[i];
tileptr->capacity = (int) ceil((double)tileptr->area/
  (double)partptr->area * (double)partptr->capacity);

/* tileptr->grid_loc's have to be updated according to the location 
			       of the center point of the tile */
grid_loc(tileptr);
}
