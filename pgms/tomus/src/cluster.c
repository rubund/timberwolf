/* ----------------------------------------------------------------- 
FILE:	    cluster.c                                       
DESCRIPTION: cluster()
CONTENTS:    cluster() 
	     grid_loc() 
             int point_xloc()	
             int point_yloc()	
DATE:	  February 13, 1990 
REVISIONS: February 15, 1990: Added lines to realloc memory to 
			      carrayG's of the tiles. 
           Feb. 23, 1990 : Added grid_loc() to have the cells have 
	     a relative position and their corresponding pins too.
           Feb. 27, 1990 : Added code to fill up the "part_tile" field
			  of the cell_ptr.
           Feb. 27, 1990 : Added point_xloc()and point_yloc() to find 
			 grid locations  of a point.
           March 5, 1990 : Added code to change coord's of cells to 
			  that of the center of the tile it belongs to
	   July 11, 1990 : Added a routine to sort the Segements  in order to find the min_con in X and min_con in y, i.e. the minimum congestion limits , needed to find the net penalty.
----------------------------------------------------------------- */
#ifndef VMS
#ifndef lint
static char SccsId[] = "@(#) cluster.c (Yale) version 1.7 2/23/91" ;
#endif
#endif

#include <string.h>
#include "standard.h"
#include "parser.h"
#include <yalecad/string.h>
#include <yalecad/debug.h>
#define NUMCELLS 800
extern int *line_y,*line_x;
int cellAlloc;
static xloc,yloc;
int tot_clen;

BOOL tile_found( tile, char_array )
INT tile; 
char **char_array;
{

	INT part, i ;
	char class[8] ;

	part = tarrayG[tile]->partition_id;
	if ( partarrayG[part] ) {
		strcpy ( class , partarrayG[part]->class ) ; 
	} else {
		return (FALSE);
	}
	if (!strcmp (class,"none")) return (TRUE);
	i = 1 ;
	while (char_array[i]) {
		if (strcmp(class , char_array[i]) == 0) return (TRUE);
		i++;
	}
return (FALSE);
} /* end tile_found */

cluster()
{
static PTILEPTR tlptr;
static CBOXPTR cptr;
static int clen,cell, cellcount;
static int j,i;
static BOOL invalid_cell, legal_tile;

     tot_clen = 0;
     cellcount = 0;
     for( i = 1 ; i <= numcellsG ; i++ ) {
        legal_tile = TRUE;
	while (legal_tile) {
     		j = PICK_INT ( 1, num_ptileG);
           	if (tarrayG[j]->legal || !tarrayG[j]->capacity) {
			/** do nothing */
			continue;
		}
                if (!partarrayG[tarrayG[j]->partition_id]->capacity){
	        	tarrayG[j]->capacity = 0;
			continue;
		}
		/* check for legal tile */
        	tlptr = tarrayG[ j ];
		if (strcmp ( carrayG[i]->cpclass[0], "none" ) == 0) {
			/** it has some legal class */
	           if ( tile_found(tlptr->id , carrayG[i]->cpclass )) {
     			legal_tile = FALSE;
	           } 
		} else {
                        legal_tile = FALSE;
                }

	}
	tlptr->cells++;
        if (!tlptr->carray){ 
	    	 tlptr->carray =  (INT* ) Ysafe_calloc( (tlptr->cells + 1) , 
					 sizeof( INT ) ) ;
	} else {
	         tlptr->carray =  (INT* ) Ysafe_realloc( tlptr->carray,
				( tlptr->cells + 1) * sizeof( INT ) ) ;
        }
        cptr = carrayG[ i ];
        cptr->cxcenter = tlptr->center_x;
        cptr->cycenter = tlptr->center_y;
	cptr->tile = tlptr->id;
	assign_pinpositions(cptr,tlptr);
	tlptr->carray[ tlptr->cells ] = i;
        tlptr->celllen += cptr->clength;
     }

} /** end cluster */

#ifdef OLDCODE

cluster()
{
static PTILEPTR tlptr;
static CBOXPTR cptr;
static int clen,cell, cellcount;
static int j,i;
static BOOL invalid_cell;

     cellAlloc = NUMCELLS;
     tot_clen = 0;
     cellcount = 0;
     i = PICK_INT ( 1, numcellsG);
     for( j = 1 ; j <= num_ptileG ; j++ ) {
           if (tarrayG[j]->legal || !tarrayG[j]->capacity) continue; 
           if (!partarrayG[tarrayG[j]->partition_id]->capacity){
	   	tarrayG[j]->capacity = 0;
	   	continue; 
	   }
           tlptr = tarrayG[ j ];
              if (!tlptr->carray){ 
	     	 tlptr->carray =  (CBOXPTR *)  Ysafe_calloc( cellAlloc  , 
					 sizeof( CBOXPTR ) ) ;
	      }
              clen = 0;
	      cell = 0;
	      while (tlptr->capacity > clen) {
		 cellcount++;
	         if (cellcount > numcellsG) break;
                 cptr = carrayG[ i ];
	         if (++cell>=cellAlloc) {
		    cellAlloc += cellAlloc;
	            tlptr->carray =  (CBOXPTR *) Ysafe_realloc( tlptr->carray,
					 cellAlloc * sizeof( CBOXPTR ) ) ;
		 }
                 if (!tlptr->carray[ cell ]) 
                 tlptr->carray[ cell ] =
			  (CBOXPTR) Ysafe_malloc( sizeof(CBOX) ) ;
                 cptr->cxcenter = tlptr->center_x;
                 cptr->cycenter = tlptr->center_y;
		 cptr->tile = tlptr->id;
		 assign_pinpositions(cptr,tlptr);
		 clen += cptr->clength;
		 tlptr->carray[cell] = cptr;
		 if ( cellcount < numcellsG ) invalid_cell = TRUE;
		 else break;
		while (invalid_cell){
		 	i = PICK_INT ( 1, numcellsG);
			if (carrayG[ i ]->tile) {
				invalid_cell = TRUE;
			} else {
			/* check for legal tile */
				if (strcmp ( carrayG[i]->cpclass[0], "none" )
== 0){
				/** it has some legal class */
				    if ( tile_found(tlptr->id , carrayG[i]->cpclass )) {
				        	invalid_cell = FALSE;
				    } 
				} else {
					invalid_cell = FALSE;
				}
			}
		}
	      }
            tlptr->celllen = clen;
            tlptr->cells = cell;
	    tot_clen += clen ;
	    if (i > numcellsG) break;
     }
   /*  printf("The Total Cell Length of this circuit is %d\n",celllenG);
     printf("And I could fit a Total Cell Length of %d\n",tot_clen);
     printf("The Total Number of Cells of this circuit is %d\n",numcellsG);
     printf("And I could fit %d Cells\n",i-1);

     **** If the cells are more than the core capacity, the extra cells 
     are dumped into the last tile , hoping the partitioner is going to
     take care of it **/
     while (numcellsG > i-1){
           cptr = carrayG[ i ];

	   /**** tlptr will have the last legal tile assigned *****/

	   if (++cell>=cellAlloc) {
	    cellAlloc += cellAlloc;
	    tlptr->carray =  (CBOXPTR *) Ysafe_realloc( tlptr->carray,
				 cellAlloc * sizeof( CBOXPTR ) ) ;
	   }
           if (!tlptr->carray[ cell ]) 
              tlptr->carray[ cell ] =
			  (CBOXPTR) Ysafe_malloc( sizeof(CBOX) ) ;
           cptr->cxcenter = tlptr->center_x;
           cptr->cycenter = tlptr->center_y;
	   cptr->tile = tlptr->id;
	   assign_pinpositions(cptr,tlptr);
	   tlptr->celllen += cptr->clength;
           tlptr->carray[cell] = cptr;
           i++;
     }

}

#endif /* OLDCODE */


assign_pinpositions(cptrS,tptrS)
CBOXPTR cptrS;
PTILEPTR tptrS;
{
static PINBOXPTR pinptr;
for (pinptr= cptrS->pins; pinptr; pinptr=pinptr->nextpin){
  pinptr->xpos = tptrS->grid_loc_x;
  pinptr->ypos = tptrS->grid_loc_y;
}

}




grid_loc(tptr)
PTILEPTR tptr;
{ 
  static int i;
    xloc = tptr->center_x;
    yloc = tptr->center_y;
  for (i=1;i<=vlineG;i++) {
     if ( xloc <= line_x[i] ){
       tptr->grid_loc_x = i-1;
       break;
       }
   }
  for (i=1;i<=hlineG;i++) {
     if ( yloc <= line_y[i] ){
       tptr->grid_loc_y = i-1;
       break;
       }
   }

}

int point_xloc(x)
int x;
{
  static int i,val;
  for (i=1;i<=vlineG;i++) {
     if ( x <= line_x[i] ) {
       val = i-1;
       return (val);
     }
   }
   return (vlineG);
}

int point_yloc(y)
int y;
{
  static int i,val;
  for (i=1;i<=hlineG;i++) {
     if ( y <= line_y[i] ){
       val = i-1;
       return (val);
     }
  }
   return (hlineG);
}

int ave_xspan()
{
static PTILEPTR tileptr1,tileptr2;
static int i,temp,sum;

for (i=1;i<=num_ptileG-1;i++){

 tileptr1 = tarrayG[i];
 tileptr2 = tarrayG[i+1];
 temp = (tileptr2->center_x - tileptr1->center_x);
 if (temp < 0 ) break;
 sum += temp;
}
return ((DOUBLE)sum/(vlineG-1));
}

int ave_yspan()
{
static PTILEPTR tileptr1,tileptr2;
static int i,temp,sum;

for (i=1;i<=num_ptileG-1;i++){

 tileptr1 = tarrayG[i];
 tileptr2 = tarrayG[i+vlineG -1];
 if(i+vlineG-1>num_ptileG) break;
 temp = (tileptr2->center_y - tileptr1->center_y);
 sum += temp;
 i += vlineG -2;
}
return ((double)sum/(hlineG-1));
}

