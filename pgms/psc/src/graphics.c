/* ----------------------------------------------------------------- 
FILE:	    graphics.c
DESCRIPTION:
CONTENTS:   
DATE:	    Mon Feb 18 00:08:29 EST 1991
REVISIONS:  Thu Mar  7 02:52:27 EST 1991 - moved job scheduler to
		jobs.c
	    Sun Apr 21 21:44:55 EDT 1991 - added remote graphics.
----------------------------------------------------------------- */
#ifndef lint
static char SccsId[] = "@(#) graphics.c (Yale) version 1.4 9/23/91" ;
#endif

#include <string.h>
#include <yalecad/base.h>
#include <yalecad/message.h>
#include <yalecad/draw.h>
#include <yalecad/colors.h>
#include <yalecad/debug.h>
#include <globals.h>

#ifndef NOGRAPHICS 

#define DATADIR       "./DATA"
#define MENUNAME      "psc_menu"
#define TOP           8000
#define NUMCOLS       80
#define COLUMN80      \
"12345678901234567890123456789012345678901234567890123456789012345678901234567890"

/* #define DEVELOPMENU */
/* During development use TWread_menus in place of menuS */
/* to create menu record, ie.  TWread_menus(COMPACTMENU) */
#ifdef DEVELOPMENU
#define MENU   TWread_menus(MENUNAME)
#else
#define MENU   menuS
#endif

#include <menus.h>

static BOOL auto_drawS  = TRUE ;
static INT  widthS ;               /* width of average character */
static INT  heightS ;              /* height of average character */

init_graphics( argc, argv, windowId )
INT argc, windowId ;
char *argv[] ;
{
    char *Ygetenv() ;
    INT draw_the_data() ;
    INT height ;

    remote_graphicsG = FALSE ;
    /* we need to find host for display */
    if(!(displayG = Ygetenv("DISPLAY"))) {
	M(WARNMSG,"init_graphics","Can't get environment variable ");
	M(MSG,NULL, "for display.  Aborting graphics...\n\n" ) ;
	graphicsG = FALSE ;
	return ;
    }
    if( strncmp( displayG, ":0", 2 ) == STRINGEQ ){
	M( WARNMSG, "init_graphics", "Display environment variable does not specify machine node name\n" ) ;
	M( WARNMSG, NULL, "Remote grahics cannot be performed\n\n" ) ;
	displayG = NIL(char *) ;
    }
    if( windowId ){
	/* init windows as a parasite */
	fprintf( stderr,"windowId:%d\n", windowId ) ;
	if( !( TWinitParasite(argc,argv,TWnumcolors(),TWstdcolors(),
	    FALSE, MENU, draw_the_data, windowId ))){
	    M(ERRMSG,"initgraphics","Aborting graphics.");
	    graphicsG = FALSE ;
	    return ;
	}
    } else {
	if(!(TWinitGraphics(argc,argv,TWnumcolors(),TWstdcolors(),
	    FALSE, MENU, draw_the_data ))){
	    M(ERRMSG,"init_graphics","Aborting graphics.");
	    graphicsG = FALSE ;
	    return ;
	}
    }
    TWsetwindow( 0, 0, TOP, TOP ) ;
    TWstringSize( COLUMN80, &widthS, &heightS ) ;
    height = (total_jobsG+total_nodesG+5) * heightS ;
    TWflushFrame() ;
    widthS /= NUMCOLS ;

} /* end init_graphics */

char *get_status(job)
JOBPTR job ;
{
    static char status_bufL[LRECL] ;
    switch( job->status ){
    case JOB_INIT:
	strcpy( status_bufL, "initialized" ) ;
	break ;
    case JOB_QUEUED:
	strcpy( status_bufL, "queued" ) ;
	break ;
    case JOB_SCHED:
	strcpy( status_bufL, "scheduled" ) ;
	break ;
    case JOB_RESCHED:
	strcpy( status_bufL, "rescheduled" ) ;
	break ;
    case JOB_LOADED:
	strcpy( status_bufL, "loaded" ) ;
	break ;
    case JOB_RUNNING:
	strcpy( status_bufL, "running" ) ;
	break ;
    case JOB_ERROR:
	strcpy( status_bufL, "error" ) ;
	break ;
    case JOB_COMPLETE:
	strcpy( status_bufL, "complete" ) ;
	break ;
    case JOB_UNKNOWN:
	strcpy( status_bufL, "unknown" ) ;
	break ;
    case JOB_SCHEDFAIL:
	strcpy( status_bufL, "schedule failure" ) ;
	break ;
    case JOB_CHECKFAIL:
	strcpy( status_bufL, "check failure" ) ;
	break ;
    } /* end switch */
    return( status_bufL ) ;

} /* end get_status */


/* draw_the_data routine draws scheduling */
INT draw_the_data()
{
    INT cur_height ;         /* keep track of where we are from top */
    INT tab2 ;               /* tab2 position */
    INT tab3 ;               /* tab3 pos.*/
    INT tab4 ;               /* tab4 pos.*/
    NODEPTR node ;           /* current node */
    JOBPTR job ;             /* current job */
    char jobname[LRECL] ;    /* the current jobname */

    /* graphics is turned off */
    if( !graphicsG ){
	return ;
    }

    tab2 = 2 * widthS ;
    tab3 = tab2 + 15 * widthS ;
    tab4 = tab3 + 15 * widthS ;

    TWstartFrame() ;

    /* first write out the nodes */
    cur_height = TOP - heightS ;
    TWdrawString( widthS, cur_height, TWRED, "Nodes available" ) ;
    for( node = (NODEPTR) Yrbtree_enumerate( node_treeG, TRUE ); node;
	 node = (NODEPTR) Yrbtree_enumerate( node_treeG, FALSE ) ){
	cur_height -= heightS ;
	TWdrawString( tab2, cur_height, TWBLUE, node->nodename ) ;
    }

    /* now write out the scheduled jobs */
    cur_height -= 2 * heightS ;
    TWdrawString( widthS, cur_height, TWRED, "Scheduled jobs" ) ;
    TWdrawString( tab3, cur_height, TWRED, "Node" ) ;
    TWdrawString( tab4, cur_height, TWRED, "Status" ) ;
    for( Ydeck_top(job_schedG);
	Ydeck_notEnd(job_schedG);Ydeck_down(job_schedG) ) {
	job = (JOBPTR) Ydeck_getData( job_schedG ) ;
	if( job->job ){
	    sprintf( jobname, "%s:%d", cktNameG, job->job ) ;
	} else {
	    strcpy( jobname, cktNameG ) ;
	}
	cur_height -= heightS ;
	TWdrawString( tab2, cur_height, TWBLUE, jobname ) ;
	TWdrawString( tab3, cur_height, TWBLUE, job->nodename ) ;
	TWdrawString( tab4, cur_height, TWBLUE, get_status(job) ) ;
    }

    cur_height -= 2 * heightS ;
    TWdrawString( widthS, cur_height, TWRED, "Queued jobs" ) ;
    for( Ydeck_top(job_queueG);
	Ydeck_notEnd(job_queueG);Ydeck_down(job_queueG) ){
	job = (JOBPTR) Ydeck_getData( job_queueG ) ;
	sprintf( jobname, "%s:%d", cktNameG, job->job ) ;
	cur_height -= heightS ;
	TWdrawString( tab2, cur_height, TWBLUE, jobname ) ;
	TWdrawString( tab4, cur_height, TWBLUE, get_status(job) ) ;
    }

    TWflushFrame() ;

} /* end draw_the_data */

/* heart of the graphic system processes user input */
process_graphics()
{

    INT x, y ;           /* coordinates from pointer */
    INT i ;            /* temp variable */
    INT selection ;     /* the users pick */
    BOOL execute ;      /* whether we have more work to do */
    char *reply ;       /* user reply to a querry */

    if(!(graphicsG)){
	return ;
    }
    /* data might have changed so show user current config */
    /* any function other that the draw controls need to worry about */
    /* this concurrency problem -  show user current config */
    draw_the_data() ;
    /* use TWcheckExposure to flush exposure events since we just */
    /* drew the data */
    TWcheckExposure() ;
    TWmessage( "PSC is waiting for your response..." ) ;
    execute = FALSE ;
    statusChangedG = FALSE ; /* when to redraw */

    selection  = CANCEL ;
    while( selection != EXIT_PROGRAM ){ /* loop until exit */
	selection = TWcheckMouse() ;
	switch( selection ){
	case CANCEL:
	    /* do nothing */
	    break ;
	case REDRAW:
	    draw_the_data() ;
	    /* use TWcheckExposure to flush exposure events since */
	    /* we just drew the data */
	    TWcheckExposure() ;
	    break ;
	case ZOOM:
	    TWzoom() ;
	    break ;
	case FULLVIEW:
	    TWfullView() ;
	    break ;
	case EXIT_PROGRAM:
	    break ;
	case AUTO_REDRAW_ON:
	    auto_drawS = TRUE ;
	    break ;
	case AUTO_REDRAW_OFF:
	    auto_drawS = FALSE ;
	    break ;
	case CLOSE_GRAPHICS:
	    TWcloseGraphics() ;
	    /* update all costs and reload cells */
	    graphicsG = FALSE ;
	    return ;
	case COLORS:
	    TWtoggleColors() ;
	    break ;
	case TRANSLATE:
	    TWtranslate() ;
	    break ;
	case DUMP_GRAPHICS:
	    /* now change mode to dump to file */
	    TWsetMode(1) ;
	    /* dump the data to a file now instead of screen */
	    draw_the_data() ;
	    /* restore the state to draw to screen */
	    TWsetMode(0) ;
	    break ;
	case TELL_POINT:
	    TWmessage( "Pick a point" ) ;
	    TWgetPt( &x, &y ) ;
	    sprintf( YmsgG,"The point is (%d,%d)",x,y ) ;
	    TWmessage( YmsgG ) ;
	    break ;
	case EXECUTE_PGMS:
	    execute = TRUE ;
	    break ;
	case REMOTE_GRAPHICS_ON:
	    remote_graphicsG = TRUE ;
	    if( displayG ){
		TWmessage( "Remote graphics have been activated" ) ;
	    } else {
		TWmessage( "Remote graphics cannot be activated" ) ;
	    }
	    break ;
	case REMOTE_GRAPHICS_OFF:
	    remote_graphicsG = FALSE ;
	    TWmessage( "Remote graphics have been deactivated" ) ;
	    break ;
	}
	if( auto_drawS && TWcheckExposure() || statusChangedG ){
	    draw_the_data() ;
	    statusChangedG = FALSE ;
	}

	if( execute ){
	    auto_flow() ;
	}
    } 

    TWmessage("Continuing - to interupt program click on top menu window") ;

} /* end process_graphics */


#endif /* NOGRAPHICS */

closegraphics()
{
    if( graphicsG ){
	G( TWcloseGraphics() ) ;
    }
} /* end closegraphics */
