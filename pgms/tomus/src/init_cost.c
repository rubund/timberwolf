/* ----------------------------------------------------------------- 
FILE:	    init_cost.c                                       
DESCRIPTION:.
CONTENTS:   init_cost()
DATE:	    Mar 19, 1990 
REVISIONS:  
----------------------------------------------------------------- */
#ifndef VMS
#ifndef lint
static char SccsId[] = "@(#) init_cost.c (Yale) version 1.5 2/22/91" ;
#endif
#endif

#define MAXNUMPINS    100		/* WPS */

#include "standard.h"
/* #include "globals.h" */
#include <yalecad/debug.h>
#include <yalecad/file.h>
static int maxpinS = 0 ;
int *grid_x;
int *grid_y;
extern int padleft,padright,padtop,padbottom;

transform_line_grid()
{
static int count,i;
grid_x = (int*) Ysafe_calloc (vlineG+2 , sizeof(int));
grid_y = (int*) Ysafe_calloc (hlineG+2 , sizeof(int));

grid_x[0] = padleft;
grid_y[0] = padbottom;
grid_x[vlineG] = padright;
grid_y[hlineG] = padtop;

for (i = 1; i<vlineG; i++){
   grid_x[i] = tarrayG[i]->center_x;
}
for (count = 0; count<hlineG-1; count++){
   grid_y[count+1] = tarrayG[count*(vlineG-1) +1]->center_y;
}
}

int distx(p1,p2)
int p1,p2;
{
return (grid_x[p1] - grid_x[p2]);
}

int disty(p1,p2)
int p1,p2;
{
return (grid_y[p1] - grid_y[p2]);
}

init_cost()
{
FILE *fp ;
static int net ,cell;
static int x , y , t , cost=0 ;
static int n , k;
static int xgrid,ygrid,xpos,ypos;
static DBOXPTR dimptr ;
static CBOXPTR cptr ;
static PTILEPTR tileptr;
static PINBOXPTR netptr;
static int net_pin_num[ MAXNUMPINS + 1 ];
static int npins,sum ;

transform_line_grid();

init_net_set();
sortpin() ;
 /* @@@ calculate the initial wire cost  */
  for( net = 1 ; net <= numnetsG ; net++ ) {
    dimptr =  netarrayG[ net ] ;
    n = 0;
    if(!dimptr->pins){
         continue ;
    }
    dimptr->line_x = (INT*) Ysafe_calloc (vlineG+2 , sizeof(INT));
    dimptr->line_y = (INT*) Ysafe_calloc (hlineG+2 , sizeof(INT));
    dimptr->xmax = dimptr->ymax = 0; /*** trick ***/
    dimptr->xmin = vlineG + 1;
    dimptr->ymin = hlineG + 1;
    if( dimptr->ignore == 1 ){
          continue ;
    }

/**** xmax, xmin etc hold the grid loc.
	    instead of the actual units *****/

    for(netptr = dimptr->pins ; netptr ; netptr = netptr->next ) {
	      cell = netptr->cell;
	      cptr = carrayG[cell];
	      if (cell <= numcellsG) {
	      	xgrid = netptr->xpos;
	      	ygrid = netptr->ypos;
	      } else if (cell > numcellsG + numMacroG) {
		if( cptr->padptr->padside == 0 ){
		    /* then we calculate padside */
		    if (netptr->xpos <= core_x1G ){
			cptr->padptr->padside = 1;
		    } else if (netptr->xpos >= core_x2G ) {
			cptr->padptr->padside = 3;
		    } else if (netptr->ypos >= core_y1G ) {
			cptr->padptr->padside = 2;
		    } else if (netptr->ypos <= core_y2G ) {
			cptr->padptr->padside = 4;
		    } 
		}
	      	switch (cptr->padptr->padside){
			case 1:
			  xgrid = netptr->xpos =netptr->newx= 0;
			  ygrid = netptr->ypos = netptr->newy = 
					point_yloc(netptr->ypos);
			  break;
			case 2:
			  ygrid = netptr->ypos = netptr->newy =
							hlineG ;
			  xgrid = netptr->xpos =netptr->newx =
					point_xloc(netptr->xpos);
			  break;
			case 3:
			  xgrid = netptr->xpos =netptr->newx= 
			  				vlineG ;
			  ygrid = netptr->ypos = netptr->newy = 
					point_yloc(netptr->ypos);
			  break;
			case 4:
			  ygrid = netptr->ypos=netptr->newy =0; 
			  xgrid = netptr->xpos =netptr->newx= 
					point_xloc(netptr->xpos);
			  break;
			default:
			  break;

	      	}
	      } else { /* macro case **/
               if (netptr->xpos ==
                      cptr->padptr->xpoints[1])
                  xpos = netptr->xpos +1;
               else if (netptr->xpos ==
			cptr->padptr->xpoints[3])
                  xpos = netptr->xpos -1;
               else xpos = netptr->xpos;
	       xgrid = netptr->xpos = netptr->newx =
						point_xloc(xpos);
               if (netptr->ypos ==
                            cptr->padptr->ypoints[1])
                  ypos = netptr->ypos +1;
               else if (netptr->ypos ==
                            cptr->padptr->ypoints[3])
                  ypos = netptr->ypos -1;
               else ypos = netptr->ypos;
	       ygrid = netptr->ypos = netptr->newy =
						point_yloc(ypos);

	      }
              dimptr->line_x[xgrid]++;
	      dimptr->line_y[ygrid]++;
	      if (xgrid < dimptr->xmin ) dimptr->xmin = xgrid;
	      if (xgrid > dimptr->xmax)  dimptr->xmax = xgrid;
              if (ygrid < dimptr->ymin ) dimptr->ymin = ygrid;
              if (ygrid > dimptr->ymax)  dimptr->ymax = ygrid;
              n++;
    }
    dimptr->numpins = n;
    dimptr->newxmin = dimptr->xmin;
    dimptr->newxmax = dimptr->xmax;
    dimptr->newymin = dimptr->ymin;
    dimptr->newymax = dimptr->ymax;
    cost += dimptr->halfPx = dimptr->newhalfPx =
                           grid_x[dimptr->xmax] - grid_x[dimptr->xmin] ;
    dimptr->halfPy = dimptr->newhalfPy = grid_y[dimptr->ymax] -
                           grid_y[dimptr->ymin] ;
    cost += (int)( vertical_wire_weightG * (double) dimptr->halfPy ) ;
}

  fprintf( fpoG, "\n\n\nTHIS IS THE ROUTE COST OF THE ");
  fprintf( fpoG, "ORIGINAL PLACEMENT: %d\n" , cost ) ;
 
   for( n = 1 ; n <= MAXNUMPINS ; n++ ) {
         net_pin_num[ n ] = 0 ;
   }
  for( net = 1 ; net <= numnetsG ; net++ ) {
     dimptr =  netarrayG[ net ] ;
     maxpinS = MAX( maxpinS, dimptr->numpins ) ;
     if( dimptr->numpins >= MAXNUMPINS ) {
                   net_pin_num[ MAXNUMPINS ]++ ;
     } else {
                   net_pin_num[ dimptr->numpins]++ ;
     }
  }
 sum = npins = 0 ;
  for( n = 1 ; n < MAXNUMPINS ; n++ ) {
    if( net_pin_num[ n ] ){
        fprintf( fpoG, "The number of nets with %d pins is %d\n",
                   n , net_pin_num[ n ] ) ;
     }
     sum += n * net_pin_num[ n ] ;
     npins += net_pin_num[ n ] ;
   }
fprintf( fpoG, "The number of nets with %d pins or more is %d\n",
             MAXNUMPINS, net_pin_num[ MAXNUMPINS ] ) ;
fprintf( fpoG, "Average number of pins per net = %f\n",
             (double) sum / (double) npins ) ;
fprintf( fpoG, "The maximum number of pins on a single net is:%d\n",
          maxpinS ) ;
find_net_sizes();
init_dimbox();
return(cost);
} 

wire_cost()
{
static int net ;
static int cost_2 ;
static int xgrid,ygrid;
static int xmin,xmax,ymin,ymax,halfPx,halfPy;
static DBOXPTR dimptr ;
static PINBOXPTR netptr;

cost_2=0 ;
  for( net = 1 ; net <= numnetsG ; net++ ) {
    dimptr =  netarrayG[ net ] ;
    if(!dimptr->pins){
         continue ;
    }
    xmax = ymax = 0; /*** trick ***/
    xmin = vlineG + 1;
    ymin = hlineG + 1;

/**** xmax, xmin etc hold the grid loc.
	    instead of the actual units *****/

    for(netptr = dimptr->pins ; netptr ; netptr = netptr->next ) {
	     	xgrid = netptr->xpos;
	      	ygrid = netptr->ypos;
	      if (xgrid < xmin ) xmin = xgrid;
	      if (xgrid > xmax)  xmax = xgrid;
              if (ygrid < ymin ) ymin = ygrid;
              if (ygrid > ymax)  ymax = ygrid;
    }

    if (dimptr->xmax!= xmax)
    printf("max_net:%d \n ", net);
    if (dimptr->xmin!= xmin) 
    printf("min_net:%d \n ", net);
    dimptr->xmax =  xmax;
    dimptr->xmin =  xmin;
    dimptr->ymax =  ymax;
    dimptr->ymin =  ymin;
    cost_2 += halfPx = 
                           grid_x[dimptr->xmax] - grid_x[dimptr->xmin] ;
    if (dimptr->halfPx!= halfPx) 
    printf("Hx_net:%d \n ", net);
    dimptr->halfPx = halfPx; 
    halfPy = grid_y[dimptr->ymax] -
                           grid_y[dimptr->ymin] ;
    if (dimptr->halfPy!= halfPy)
    printf("Hy_net:%d \n ", net);
    dimptr->halfPy = halfPy;
    cost_2 += (int)( vertical_wire_weightG * (double) dimptr->halfPy ) ;
}
return(cost_2);
}

assign_pins_to_cells()
{
static PINBOXPTR pinptr;
static DBOXPTR netptr;
static int i,cell;

for ( i = 1 ; i <= numnetsG ; i++ ) {
	netptr = netarrayG[i];
	if(!(netptr->pins)) continue ;
	for(pinptr = netptr->pins ; pinptr ; pinptr = pinptr->next ) {

		cell = pinptr->cell;
		if ( cell <= numcellsG ) {
        		pinptr->xpos = carrayG[cell]->cxcenter;
        		pinptr->ypos = carrayG[cell]->cycenter;
                }
	}
}
}

