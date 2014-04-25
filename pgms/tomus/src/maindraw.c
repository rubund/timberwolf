/* ----------------------------------------------------------------- 
FILE:	    maindraw.c                                       
DESCRIPTION:a graphic program using TW library calls.
CONTENTS:   main_draw()
DATE:	    Feb 14, 1990 
REVISIONS:  Sat Feb 23 01:08:39 EST 1991 - Renamed the dialog ptr.
----------------------------------------------------------------- */
#ifndef lint
static char SccsId[] = "@(#) maindraw.c (Yale) version 1.15 7/2/91" ;
#endif

#ifndef NOGRAPHICS

#include <string.h>
#include <yalecad/file.h>
#include <yalecad/message.h>
#include <yalecad/debug.h>
#include <yalecad/draw.h>
#include <yalecad/colors.h>
#include <yalecad/dialog.h>
#include <yalecad/rbtree.h>
#include "standard.h"

#define PCLS 8
#define FWIDTH 64
#define LARGELRECL 56
#define DEFAULTCLASS "default"
#define INVALIDCLASS "invalid"

/*#define DEVELOPMENU 
During development use TWread_menus in place of menuS */
/* to create menu record, ie.  TWread_menus(MENUP) */
#ifdef DEVELOPMENU
#define MENUP  "tomus_menu"
#define MENU   (TWMENUPTR) TWread_menus(MENUP)
#else
#define MENU   menuS
#endif

#include <menus.h>

/*#define DEVELOPDIALOG */

#ifndef DEVELOPDIALOG

#include <dialog.h> 

#else
static TWDIALOGPTR dialogS ;

#endif

/*#define DEVELOPDIALOG2 */ 

#ifndef DEVELOPDIALOG2
#include <dialogpart.h>

#else
static TWDIALOGPTR part_dialogS ;
#endif


BOOL drawCore,drawLine,drawMacro,drawPartition,drawStd,drawNet;
extern BOOL drawRow,output_timeG, doGraphicsG ;
extern YTREEPTR legal_part_tree;
extern int partclassG;
char *classG ;
char left[FWIDTH]; /* a scratch buffer for left of part */
char right[LRECL]; /* a scratch buffer for right of part */
char top[FWIDTH]; /* a scratch buffer for top of part */
char class[LRECL]; /* a scratch buffer for class of part */
char defclass[LRECL]; /* a scratch buffer for default class of part */
char bottom[LRECL] ;/* a scratch buffer for bottom of part */



static INT draw_data();



init_draw( argc, argv, windowid )
INT argc ; 
char *argv[] ;
INT windowid ;
{
    static int tx,ty;
    char *host, *Ygetenv() ;

    /* we need to find host for display */
    if(!(host = Ygetenv("DISPLAY"))) {
	M(WARNMSG,"init_draw","Can't get environment variable ");
	M(MSG,NULL, "for display.  Aborting graphics...\n\n" ) ;
	YexitPgm(PGMFAIL) ;
    }
    if( windowid ){
	/* init windows as a parasite */
	if(!(TWinitParasite(argc,argv,TWnumcolors(),TWstdcolors(),
	    FALSE,MENU, draw_data, windowid ))){
	    M(ERRMSG,"init_draw","Aborting graphics.");
	    YexitPgm(PGMFAIL) ;
	}
    } else {
	/* init window as a master */
	if(!(TWinitGraphics(argc,argv,TWnumcolors(),TWstdcolors(),FALSE,
	    MENU,draw_data ))){
	    M(ERRMSG,"init_draw","Aborting graphics.");
	    YexitPgm(PGMFAIL) ;
	}
    }

    tx = (core_x2G - core_x1G)*1.5;
    ty = (core_y1G - core_y2G)*1.5;
    TWsetwindow( -1000, -1000, tx,ty) ;
    sprintf( YmsgG,"Welcome to the Tomus program") ;
    drawCore = TRUE;
    drawLine = TRUE;
    drawPartition = FALSE;
    drawMacro = TRUE;
    draw_the_data(YmsgG) ;
}


init_draw2()
{
    static int tx,ty;

    tx = (core_x2G - core_x1G)*1.5;
    ty = (core_y1G - core_y2G)*1.5;
    TWsetwindow( -1000, -1000, tx,ty) ;
    drawPartition = TRUE;
    draw_data() ;
}


int main_draw(msg)
char msg[] ;
{

    int answer ;
    char *reply ;
    BOOL auto_draw ; 
    static INT x, y;
    static int tile,i,t[20] ;
    static char lineinfo[20];
    static PTILEPTR tileptrS;

    i = 0;
    auto_draw = TRUE ;
    answer = 1 ;
    TWmessage( msg ) ;
    draw_data();
    while( answer != CONTINUE_PROGRAM ){
	/* see if user has selected anything */
	answer = TWcheckMouse() ;
	switch( answer ){
	    case CANCEL:
		/* do nothing */
		break ;
	    case DUMP_GRAPHICS:
		dump_graphics();
		break;
	    case REDRAW:
		TWmessage( YmsgG ) ;
		draw_data() ;
		/* flush exposure events */
		TWcheckExposure() ;
		break ;
	    case ZOOM:
		TWzoom() ;
		break ;
	    case FULLVIEW:
		TWfullView() ;
		break ;
	    case CONTINUE_PROGRAM:
		TWmessage( YmsgG ) ;
	        draw_data();
		return(0);
		/* get a string from the user */
	    case TELL_POINT:
		TWmessage( "Pick a point" ) ;
		TWgetPt( &x, &y ) ;
		sprintf( YmsgG,"The point is (%d,%d)",x,y ) ;
		TWmessage( YmsgG ) ;
		break ;
            case DRAWNETS:
		 drawNet = 1;
		TWmessage( YmsgG ) ;
	         draw_data();
		 break;
            case IGNORENETS:
		 drawNet = 0;
		TWmessage( YmsgG ) ;
	         draw_data();
		 break;
            case IGNORESTDCELLS:
		 drawStd = 0;
		 break;
            case DRAWSTDCELLS:
		 if (!output_timeG)
		 drawStd = 1;
		 else draw_the_data("Stdcells can't be shown at output Stage");
		 break;
            case IGNORE_PARTITIONS:
		 drawPartition = 0;
		 break;
            case DRAWPARTITIONS:
		 drawPartition = 1;
		 break;
            case DRAWLINES:
		 drawLine= 1;
		TWmessage( YmsgG ) ;
	         draw_data();
		 break;
            case IGNORE_LINES:
		 drawLine= 0;
		TWmessage( YmsgG ) ;
	         draw_data();
		 break;
            case DRAWMACROS:
		 drawMacro =1;
		TWmessage( YmsgG ) ;
	         draw_data();
		 break;
            case IGNOREMACROS:
		 drawMacro =0;
		TWmessage( YmsgG ) ;
	         draw_data();
		 break;
#ifdef OLDCODE

case HORLINES:
	draw_data();
        TWmessage( "Click a point to draw a horizontal line" ) ;
	while(TRUE){
		TWmessage( "Click again for more Horizontal lines/else click outside the core" ) ;
        	TWgetPt2( &x, &y ) ;
        	if (( y < core_y2G || y > core_y1G )
              		|| ( x < core_x1G || x > core_x2G )){
               		TWmessage("Continuing ... Tomus program") ;
               		return(0) ;
		}
        	addhline (y);
        	sprintf( YmsgG,"An extra horizontal line thru (%d,%d)",
			x,y ) ;
		TWdrawLine(0,x,y,core_x1G,y,7,NULL);
		TWdrawLine(0,x,y,core_x2G,y,7,NULL);
        	TWmessage( YmsgG ) ;
		sleep(1);
	}
case VERLINES:
	draw_data();
	TWmessage( "Click a point to draw a vertical line" ) ;
	while(TRUE){
		TWmessage( "Click again for more Vertical lines/else click outside the core" ) ;
		TWgetPt2( &x, &y ) ;
        	if (( y < core_y2G || y > core_y1G )
              		|| ( x < core_x1G || x > core_x2G )){
               		TWmessage("Continuing ... Tomus program") ;
               		return(0) ;
		}
        	addvline (x);
        	sprintf( YmsgG,"An extra horizontal line thru (%d,%d)",
			x,y ) ;
		TWdrawLine(0,x,y,x,core_y1G,6,NULL);
		TWdrawLine(0,x,y,x,core_y2G,6,NULL);
		TWmessage( YmsgG ) ;
		sleep(1);
	}
#endif /* OLDCODE */

    case AUTO_REDRAW_ON:
	    auto_draw = TRUE ;
	    break ;
    case AUTO_REDRAW_OFF:
	auto_draw = FALSE ;
	break ;
    case COLORS:
	TWtoggleColors() ;
	break ;
	}
	if( auto_draw && TWcheckExposure() ){
	    TWmessage( YmsgG ) ;
	    draw_data() ;
	}
    } /* end graphics loop */
return(0);
} /* end maindraw program */


draw_the_data2(msg)
char *msg;
{
if (!doGraphicsG) return;
TWstartFrame() ;
TWmessage(msg) ;
if (drawLine) drawLines();
if (numMacroG && drawMacro) drawMacros();
if (drawStd) drawStd_cell();
if (drawCore) drawcore();
if (drawRow) drawrow();
if (drawNet) drawNets();
if (drawPartition) {
drawPartitions(TRUE);
}
drawPads();
TWflushFrame();
}

static INT draw_data()
{
    TWstartFrame() ;
    if (drawLine) drawLines();
    if (numMacroG && drawMacro) drawMacros();
    if (drawStd) drawStd_cell();
    if (drawCore) drawcore();
    if (drawRow) drawrow();
    if (drawNet) drawNets();
    if (drawPartition) {
	drawPartitions(FALSE);
    }
    drawPads();
    TWflushFrame();

} /* end draw_data */

draw_the_data(msg)
char *msg;
{
if (!doGraphicsG) return;
    TWmessage(msg) ;
    draw_data() ;
} /* end draw_the_data */


drawcore()
{
TWdrawLine(0,core_x1G,core_y2G,core_x1G,core_y1G,TWBLACK,NULL);
TWdrawLine(0,core_x2G,core_y2G,core_x2G,core_y1G,TWBLACK,NULL);
TWdrawLine(0,core_x1G,core_y1G,core_x2G,core_y1G,TWBLACK,NULL);
TWdrawLine(0,core_x1G,core_y2G,core_x2G,core_y2G,TWBLACK,NULL);
}

dump_graphics()
{
    /* now change mode to dump to file */
    TWsetMode(1) ;
    /* dump the data to a file now instead of screen */
    draw_data() ;
    /* restore the state to previous condition and set draw to screen */
    TWsetMode(0) ;
}

#define QUERY    2
#define LINECASE 3

BOOL query_dialog( query_string )
char *query_string ;
{
    TWDRETURNPTR answer ;  /* return from user */
    char query[LRECL] ;    /* buffer for string */

#ifdef DEVELOPDIALOG
    dialogS = TWread_dialog( "query.dialog" ) ;
    if( !(dialogS) ){
	return ; /* avoid crashes */
    }
#endif
    /* perform initialization */
    sprintf( query, "%s", query_string ) ;
    dialogS[QUERY].string = query ;
    dialogS[QUERY].len = strlen(query) ;

    if( answer = TWdialog( dialogS, "tomus_query", NIL(VOIDPTR) )){
	if( answer[LINECASE].bool ){
	    return( TRUE ) ;
	}
    }
    return( FALSE ) ;
} /* end query_lines */

pclass_dialog(xcheck1,ycheck1,xcheck2,ycheck2)
int xcheck1,ycheck1,xcheck2,ycheck2;
{

  INT num_class ;
  char *legal_class ;

/*** here is the place to introduce the code for dialog box for partitions */
#ifdef DEVELOPDIALOG2

    part_dialogS = TWread_dialog("tomus.dialog") ;
    if( !(part_dialogS) ){
        return ; /* avoid crashes */
    }
#endif

    sprintf( left,  "Left  : %d", xcheck1 ) ;
    part_dialogS[3].string = left ;
    part_dialogS[3].len = strlen( left ) ;
    sprintf( bottom,"Bottom :%d", ycheck1 ) ;
    part_dialogS[4].string = bottom ;
    part_dialogS[4].len = strlen( bottom ) ;
    sprintf( right, "Right : %d", xcheck2 ) ;
    part_dialogS[5].string = right ;
    part_dialogS[5].len = strlen( right ) ;
    sprintf( top,   "Top   : %d", ycheck2 ) ;
    part_dialogS[6].string = top ;
    part_dialogS[6].len = strlen( top ) ;

/* Now set the default part class and the actual class*/
    sprintf( defclass,   "Default Class   :  none") ;
    part_dialogS[7].string = defclass ;
    part_dialogS[7].len = strlen( defclass ) ;

/* Now set the title of the class list */
    sprintf( class,   "Class  :    " ) ;
    part_dialogS[PCLS].string = class ;
    part_dialogS[PCLS].len = strlen(class) ;

/* Now print the set of class names already available from .cel file 
   first field is "none" */

    num_class = 1;
    legal_class = NIL(char *) ;
    strcpy( part_dialogS[PCLS+num_class].string, "none");
    part_dialogS[PCLS+num_class].len = 8 ;
    legal_class = (char*) Yrbtree_enumerate( legal_part_tree , TRUE );
    while ( legal_class ) {
    	num_class++;
    	part_dialogS[PCLS+num_class].string = legal_class ;
    	part_dialogS[PCLS+num_class].len = 8 ;
    	legal_class = (char*) Yrbtree_enumerate( legal_part_tree , FALSE );
    }


} /* end of pclass_dialog */

static INT get_part_class( answer , field)
TWDRETURNPTR answer ;  /* return from user */
INT field ; /** which field was changed : offset */
{
    INT num_class;

    if (field == 9) {
    	strcpy( classG, "none" ) ; /* never executed */
    } else {

    num_class = 9;
    if ( field > num_class + partclassG ) strcpy( classG , INVALIDCLASS ); /* to
differentiate from nil in case of no change in field the default will be
nil=none */ 
    else {  /* else 2*/
	classG = (char*) Yrbtree_enumerate( legal_part_tree , TRUE );
    	while ( classG ) {
    		num_class++;
       	 if ( num_class != field ) {
    			classG = (char*) Yrbtree_enumerate( legal_part_tree , FALSE );
		} else {
			break;
		} 
        }
    } /* else 2*/ 
    } 
} /* end get_part_class */

get_partitions()
{
    static INT x1, y1 ,x2, y2 ;
    static INT newx1, newy1 ,newx2, newy2 ;
    static INT xcheck1,ycheck1,xcheck2,ycheck2;
    static int indexS;
    static BOOL firstpoint, secondpoint, dialog_not_done;
    TWDRETURNPTR answer ;  /* return from user */
    char *pclass ; /* class of the current partition **/

    drawPartition = 1;
    TWmessage( "Create partitions by clicking at its diagonal points" ) ;

    firstpoint = secondpoint = TRUE;

    TWmessage( "The first point should be lower left corner");
 while (firstpoint){

    xcheck1 =  ycheck1 =  xcheck2 =  ycheck2 = 0 ;
    newx1 =  newy1 =  newx2 =  newy2 = 0 ;
    x1 =  y1 =  x2 =  y2 = 0 ;

    TWgetPt2( &x1, &y1 ) ;
    abut_point(&newx1,&newy1,x1,y1);
    if (!newx1) xcheck1 = x1;
    else xcheck1 = newx1;
    if (!newy1) ycheck1 = y1;
    else ycheck1 = newy1;

    TWmessage( "The second point should be upper right corner");
    TWgetPt2( &x2, &y2 ) ;
    abut_point(&newx2,&newy2,x2,y2);
    if (!newx2) xcheck2 = x2;
    else xcheck2 = newx2;
    if (!newy2) ycheck2 = y2;
    else ycheck2 = newy2;
    if (!test_point(xcheck1,ycheck1) || !test_point(xcheck2,ycheck2)) {
       firstpoint = FALSE;
       continue;
    }
    if (check_for_split_macro(xcheck1,ycheck1,xcheck2,ycheck2)){
	sprintf(YmsgG, "Invalid partition/Can't split macros: Start with first point again");
	firstpoint = TRUE;
    } else {
	firstpoint = FALSE;
	sprintf(YmsgG, "Go for the next partition;Start with first point again");
    }
    TWmessage( YmsgG);
 }

   classG = (char*) Ysafe_calloc ( 8 , sizeof (char));

if ( partclassG > 0 ) {
   dialog_not_done = TRUE ;
   while ( dialog_not_done ){

   	strcpy (classG, DEFAULTCLASS); /* initialize */
	pclass_dialog(xcheck1,ycheck1,xcheck2,ycheck2);

/*** initialization complete */

	if( answer = TWdialog( part_dialogS, "Edit_Partition", get_part_class )){
	/*if( answer[PCLS+1].bool ){
    		 means the user change the field 
    		pclass = get_part_class( answer , indexS ) ;
    	} */
	}
	if ( !strcmp (classG , DEFAULTCLASS) ) {
		strcpy (classG , "none");
		break;
	}
	if ( !strcmp (classG , INVALIDCLASS) ) dialog_not_done = TRUE ;
	else {
		dialog_not_done = FALSE ;
	}
   }
} /* if there are any part_classes */
	add_partition_corners(xcheck1,ycheck1,xcheck2,ycheck2);
	if ( !strcmp (classG , DEFAULTCLASS) ) {
		strcpy (classG , "none");
	}
	make_partition(classG,xcheck1,ycheck1,xcheck2,ycheck2);
        draw_the_data2(YmsgG);
} /* end get_partitions */

#ifdef OLDCODE

process_merge_tile()
{
    static CORNERS corptr1S,corptr3S;
    static int x, y,tile,i,t[20] ;
    static PTILEPTR tileptrS;

    draw_the_data2(YmsgG);
    drawPartition = 1;
    TWmessage( "Create partitions by clicking in the middle of a tile" ) ;

    for( ; ; ){

	TWgetPt2( &x, &y ) ;
	tile = search_all_tile(x,y);
	if (tile == -2){
	  sprintf( YmsgG,"Cannot merge this tile again. Try again!") ;
	  TWmessage( YmsgG ) ;
	  continue ;
	} else if (tile == 0){
	  sprintf( YmsgG,"Continuing ... Tomus program") ;
	  TWmessage( YmsgG ) ;
	  break ;
	} else {
	  sprintf( YmsgG,"This tile is id  %d",tile ) ;
	  tileptrS = tarrayG[tile];
	  if (tileptrS->legal) {

	      /***paint the macro ***/
		corptr1S = carrayG[numcellsG + tileptrS->legal]->cor_array[1];
		corptr3S = carrayG[numcellsG + tileptrS->legal]->cor_array[3];
		TWdrawCell(0,corptr1S->x_coord,corptr1S->y_coord,
		corptr3S->x_coord,corptr3S->y_coord,TWRED,"macro");
	  } else {

	      /***paint the tile ***/
	      TWdrawCell(0,tileptrS->upper_left_x,tileptrS->lower_right_y,
		  tileptrS->lower_right_x,tileptrS->upper_left_y,TWRED,NULL);
	  }
	  TWmessage( YmsgG ) ;
	}

	TWmessage( "Click again for more tiles/else click outside the core" ) ;
    } /* end for loop */
} /* end process_merge_tile */
#endif /* OLDCODE */

INT pick_partition()
{
    INT x, y ;
    INT tile ;

    drawLine = FALSE ;
    draw_data();
    TWmessage( "Click in the middle of the partition to configure rows") ;
    TWgetPt2( &x, &y ) ;
    tile = search_all_tile_list(x,y);
    if (tile){
	return(tarrayG[tile]->partition_id);
    } 
    return( 0 ) ;
}
#endif /* NOGRAPHICS */

