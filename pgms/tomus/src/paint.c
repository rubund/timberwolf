/* ----------------------------------------------------------------- 
FILE:	    paint.c                                       
DESCRIPTION: 
CONTENTS:  
	   The draw routines
	
DATE:	  August 6 , 1990 
REVISIONS:  
----------------------------------------------------------------- */
#ifndef VMS
#ifndef lint
static char SccsId[] = "@(#) paint.c (Yale) version 1.5 2/20/91" ;
#endif
#endif

#include "standard.h"
#include "parser.h"

#ifndef NOGRAPHICS

#include <yalecad/string.h>
#include <yalecad/message.h>
#include <yalecad/draw.h>
#include <yalecad/dialog.h>
#include <yalecad/colors.h>

#define NUMLINES 30

static PTILEPTR ptr;
static PARTNPTR partptr;
extern int *line_x ;
extern int *line_y ;
extern int num_prcor,num_y,num_x;
extern int *grid_x,*grid_y;


drawPartitions(flag)
BOOL flag;
{
static int i,tileS,xrS,yrS,lxS,lyS,lx,ly;
static int del = 50,color;
static char msg[10];

 for( tileS = 1 ; tileS <= num_partnsG; tileS++ ){ 
   partptr = partarrayG[ tileS ] ;
      if (!partptr->capacity) return;
      xrS = partptr->upper_left_x;
      yrS = partptr->lower_right_y;
      lxS = partptr->lower_right_x;
      lyS = partptr->upper_left_y;
      if (flag) {
      TWdrawCell(1,xrS,yrS,lxS,lyS,TWBLUE,NULL);
      color = TWYELLOW;
      } else color = TWBLUE;
      TWdrawLine(1,xrS,lyS,xrS,yrS,color,NULL) ;
      TWdrawLine(1,xrS+1,lyS,xrS+1,yrS,color,NULL) ;
      TWdrawLine(1,xrS-1,lyS,xrS-1,yrS,color,NULL) ;

      TWdrawLine(1,xrS,lyS,lxS,lyS,color,NULL) ;
      TWdrawLine(1,xrS,lyS+1,lxS,lyS+1,color,NULL) ;
      TWdrawLine(1,xrS,lyS-1,lxS,lyS-1,color,NULL) ;

      TWdrawLine(1,lxS,yrS,lxS,lyS,color,NULL) ;
      TWdrawLine(1,lxS+1,yrS,lxS+1,lyS,color,NULL) ;
      TWdrawLine(1,lxS-1,yrS,lxS-1,lyS,color,NULL) ;

      TWdrawLine(1,lxS,yrS,xrS,yrS,color,NULL) ; 
      TWdrawLine(1,lxS,yrS+1,xrS,yrS+1,color,NULL) ; 
      TWdrawLine(1,lxS,yrS-1,xrS,yrS-1,color,NULL) ; 
if (partptr->padlist){
for( i = 1;i<= partptr->numpads;i++ ){
    lx = partptr->padlist[i]->x;
    ly = partptr->padlist[i]->y;
    sprintf(msg,"%d",tileS);
    TWdrawPin(0,lx-del,ly-del,lx+del,ly+del,TWORANGE,NULL);
}
}        
  } /* for tileS loop */
TWflushFrame();
}

drawChannels(x1,y1,x2,y2,padx,pady)
int x1,y1,x2,y2,padx,pady;
{
static int del = 20;
TWstartFrame() ;
TWdrawCell(0,core_x1G,core_y2G,core_x2G,core_y1G,1,NULL);
if (numMacroG > 0) drawMacros();
 drawPads();
 drawLines();
 drawPartitions();
TWdrawLine(1,x1,y1,x2,y2,TWRED,NULL);
TWdrawPin(0,padx-del,pady-del,padx+del,pady+del,TWBROWN,NULL);

TWflushFrame();
}


drawLines()
{
static int i,xr,yr,j;

for( i = 1;i<= num_x;i++ ) /* because vlineG =0 initially*/
 {
      xr = line_x[i] ;
      TWdrawLine(i,xr,core_y2G,xr,core_y1G,TWBLACK,NULL) ;
 }

for( j = 1;j<= num_y;j++ )
  {
      yr = line_y[j] ;
      TWdrawLine(i,core_x1G,yr,core_x2G,yr,TWBLACK,NULL) ;
  }
}


drawMacroPadPins()
{
static CBOXPTR cptr;
static int j,lx,ly,del;
static PINBOXPTR pinptr;

for (j = numcellsG+1; j <= numcellsG + numtermsG ; j++)
{
   cptr = carrayG[j];
   if (cptr->pins){
for (pinptr = cptr->pins;pinptr;
                            pinptr = pinptr->nextpin){
        lx = pinptr->xpos;
        ly = pinptr->ypos;
        del = 0.001 * core_y1G;
        TWdrawPin(0,lx-del,ly-del,lx+del,ly+del,TWBLACK,NULL);
   }
}
}
}

drawNets()
{
int i;
 for (i=1;i<=numnetsG;i++){
      drawMST(netarrayG[i]);
 }
}

drawMST(netptr)
DBOXPTR netptr;
{
 static PINBOXPTR pinptr;
 static int lx,ly,del;
 del = 10;
 Ymst_init(netptr->numpins);
  for(pinptr = netptr->pins; pinptr; pinptr = pinptr->next){
    lx = grid_x[pinptr->xpos];
    ly = grid_y[pinptr->ypos];
    Ymst_addpt(lx,ly);
    TWdrawPin(0,lx-del,ly-del,lx+del,ly+del,TWBROWN,NULL);
  }
Ymst_draw();
Ymst_free();
}

drawTile_cells(tptr)
PTILEPTR tptr;
{
static CBOXPTR cptr;
static int i,lx,ly,ux,uy;
for (i = 1; i <= tptr->cells ; i++){
   cptr = carrayG[tptr->carray[i]];
   lx = cptr->cxcenter - cptr->clength/2; 
   ly = cptr->cycenter - cptr->cheight/2; 
   ux = cptr->cxcenter + cptr->clength/2; 
   uy = cptr->cycenter + cptr->cheight/2; 
   TWdrawCell(0,lx,ly,ux,uy,TWLIGHTBLUE,NULL);
}
}


drawStd_cell()
{
static CBOXPTR cptr;
static int i,lx,ly,ux,uy,tile;
for (i = 1; i <= numcellsG ; i++){
   cptr = carrayG[i];
   lx = cptr->cxcenter - cptr->clength/2; 
   ly = cptr->cycenter - cptr->cheight/2; 
   ux = cptr->cxcenter + cptr->clength/2; 
   uy = cptr->cycenter + cptr->cheight/2; 
   TWdrawCell(0,lx,ly,ux,uy,TWVIOLET,NULL);
 }
}


drawMacros()
{
static int i,lx,ly,del,ux,uy;
static CBOXPTR cptr;
for( i = 1;i<= numMacroG; i++ ){
   cptr = carrayG[numcellsG+i];
     	lx = cptr->padptr->xpoints[1] ;
   	ly = cptr->padptr->ypoints[1]; 
   	ux = cptr->padptr->xpoints[3];
   	uy = cptr->padptr->ypoints[3];
   TWdrawCell(0,lx,ly,ux,uy,TWCYAN,"macro");
}
}

drawPads()
{
static int j,lx,ly,ux,uy,del;
static int widthS,heightS;
static CBOXPTR cptr;

for (j = numcellsG+numMacroG+1; j <= numcellsG + numtermsG ; j++)
{
   cptr = carrayG[j];
     	lx = cptr->padptr->xpoints[1] ;
   	ly = cptr->padptr->ypoints[1]; 
   	ux = cptr->padptr->xpoints[3];
   	uy = cptr->padptr->ypoints[3];
   TWdrawCell(0,lx,ly,ux,uy,TWGREEN,NULL);
}
}

#endif /* NOGRAPHICS */
