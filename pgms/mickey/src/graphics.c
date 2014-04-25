#ifndef lint
static char SccsId[] = "@(#)graphics.c	Yale Version 2.5 5/16/91";
#endif
/* -----------------------------------------------------------------

	FILE:		graphics.c
	AUTHOR:		Bill Swartz & Dahe Chen
	DATE:		Tue Nov  6 11:06:37 EST 1990
	CONTENTS:	init_graphics()
			draw_the_data()
			setGraphicWindow() 
			process_graphics()
	REVISION:
		Fri Nov 23 19:28:19 EST 1990
	    Add code in the function draw_the_data() to plot a
	    route using the data structure of narray.
		Thu Jan  3 12:23:05 EST 1991
	    Add code to reset testing variable after each process_
	    graphics call.
		Wed Jan  9 14:45:31 EST 1991
	    Change the function from TWdrawRect to TWdrawLine.
		Thu Jan 10 10:46:37 EST 1991
	    Fix bugs in process_graphics() for drawing all the routes.
		Wed Feb  6 15:52:19 EST 1991
	    Change the varialbe names net_index and rte_index.
		Tue Mar  5 11:27:24 EST 1991
	    Change the size of pins to variable instead of constant.

----------------------------------------------------------------- */

#include <yalecad/base.h>
#include <yalecad/debug.h>
#include <define.h>
#include <gg_router.h>
#include <dgraph.h>
#include <ctype.h>

#ifndef NOGRAPHICS

#define MENUP "mickey_menu"

#include <yalecad/file.h>
#include <yalecad/draw.h>
#include <yalecad/colors.h>
#include <yalecad/message.h>

static BOOL auto_drawS = TRUE;
static BOOL drawLabelS = FALSE;
static BOOL drawRouteS = FALSE;
static BOOL net_and_route_S = FALSE;
static INT nodesizeS;
static INT routewidthS;
static INT gra_rte_index;
static INT gra_net_index;

/* #define DEVELOPMENU */
/* During development use TWread_menus in place of menuS */
/* to create menu record, ie.  TWread_menus(MENUP) */
#ifdef DEVELOPMENU
#define MENU TWread_menus(MENUP)
#else
#define MENU menuS
#endif

#include <menus.h>

void
init_graphics(argc, argv, windowId)
    INT argc;
    INT windowId;
    char *argv[];
{

    INT draw_the_data();

    if (!(graphicsG))
    {
	return;
    }

    /***********************************************************
    * We need to find host for display.
    ***********************************************************/
    if (!(TWcheckServer()))
    {
	M(MSG,NULL, "Aborting graphics...\n\n");
	graphicsG = FALSE;
	return;
    }

    if (windowId)
    {
	/***********************************************************
	* init windows as a parasite.
	***********************************************************/
	if (!(TWinitParasite(argc,
			     argv,
			     TWnumcolors(),
			     TWstdcolors(),
			     FALSE,
			     MENU,
			     draw_the_data,
			     windowId)))
	{
	    M(ERRMSG,"initgraphics","Aborting graphics.");
	    graphicsG = FALSE;
	    return;
	}
    }
    else
    {
	/***********************************************************
	* init window as a master
	***********************************************************/
	if (!(TWinitGraphics(argc,
			     argv,
			     TWnumcolors(),
			     TWstdcolors(),
			     FALSE,
			     MENU,
			     draw_the_data)))
	{
	    M(ERRMSG,"initgraphics","Aborting graphics.");
	    graphicsG = FALSE;
	    return;
	}
    }

    TWsetMode(0);
    TWsetwindow(0, 0, 10, 10);
    TWdrawMenus();
    TWflushFrame();

} /* end of init_graphics */

/* ==================================================================== */

INT draw_the_data()
{

    /***********************************************************
    * how to draw the data
    ***********************************************************/

    char label[LRECL]; /* make a label buffer */
    char *labelptr; /* pointer to current label */
    INT i;
    INT v1;
    INT v2;
    INT xlb;
    INT xub;
    INT ylb;
    INT yub;
    unsigned mask;

    OFSETPTR Pelist;

    if (!(graphicsG))
    {
	return;
    }

    /***********************************************************
    * initialize screen
    ***********************************************************/
    TWstartFrame();

    /***********************************************************
    * fill this in with you data structures
    ***********************************************************/
    nodesizeS = earray[1]->width;
    routewidthS = earray[1]->width;

    /***********************************************************
    * Draw the channels of the channel graph.
    ***********************************************************/
    for (i = 1; i <= numedges; i++)
    {
	if (drawLabelS)
	{
	    sprintf(label, "E:%d", i);
	    labelptr = label;
	}
	else
	{
	    labelptr = NIL(char);
	}

	v1 = carray[i]->node[0];
	v2 = carray[i]->node[1];
	xlb = sarray[v1]->xpos;
	ylb = sarray[v1]->ypos;
	xub = sarray[v2]->xpos;
	yub = sarray[v2]->ypos;
	TWdrawLine(i, xlb, ylb, xub, yub, TWBLUE, labelptr);
    }

    /***********************************************************
    * Draw the vertices of the channel graph.
    ***********************************************************/
    for (i = 1; i <= numnodes; i++)
    {
	xlb = sarray[i]->xpos;
	ylb = sarray[i]->ypos;

	if (drawLabelS)
	{
	    sprintf(label, "N:%d", i);
	    labelptr = label;
	}
	else 
	{
	    labelptr = NIL(char);
	}

	TWdrawRect(i,
	    	   xlb - nodesizeS,
	    	   ylb - nodesizeS,
	    	   xlb + nodesizeS, 
	    	   ylb + nodesizeS,
	    	   TWBLACK,
	    	   labelptr);
    }

    /***********************************************************
    * Draw a route from earray.
    ***********************************************************/
    if (drawRouteS != FALSE)
    {
	mask = get_mask(gra_rte_index-1);
	for (i = 1; i <= totedges; i++)
	{
	    if (earray[i]->intree & mask)
	    {
		v1 = earray[i]->node[0];
		v2 = earray[i]->node[1];
		xlb = garray[v1]->xpos;
		ylb = garray[v1]->ypos;
		xub = garray[v2]->xpos;
		yub = garray[v2]->ypos;

		if (drawLabelS)
		{
		    sprintf(label, "N:%d", i);
		    labelptr = label;
		}
		else 
		{
		    labelptr = NIL(char);
		}

		TWdrawLine(i,
		    	   xlb - routewidthS,
		           ylb - routewidthS,
		           xub + routewidthS,
		           yub + routewidthS,
		           TWRED,
		           labelptr);
	    }
	}

	for (i = numnodes+1; i <= totnodes; i++)
	{
	    xlb = garray[i]->xpos;
	    ylb = garray[i]->ypos;

	    if (drawLabelS)
	    {
		sprintf(label, "N:%d", i);
		labelptr = label;
	    }
	    else 
	    {
		labelptr = NIL(char);
	    }

	    if (parray[i-numnodes]->equiv)
	    {
		TWdrawRect(i,
		           xlb - nodesizeS,
			   ylb - nodesizeS,
		    	   xlb + nodesizeS, 
		    	   ylb + nodesizeS,
		    	   TWYELLOW,
		    	   labelptr);
	    }
	    else
	    {
		TWdrawRect(i,
		    	   xlb - nodesizeS,
		    	   ylb - nodesizeS,
		    	   xlb + nodesizeS, 
		    	   ylb + nodesizeS,
		    	   TWGREEN,
		    	   labelptr);
	    }
	}
	drawRouteS = FALSE;
    }

    if (net_and_route_S != FALSE)
    {
	labelptr = NIL(char);

	Pelist = narray[gra_net_index]->Aroute[gra_rte_index]->Pedge;
	while (Pelist)
	{
	    xlb = dearray[Pelist->edge]->f_xpos;
	    ylb = dearray[Pelist->edge]->f_ypos;
	    if (Pelist->l_off != FALSE)
	    {
		if (dearray[Pelist->edge]->direct == H)
		{
		    ylb += Pelist->l_off;
		}
		else
		{
		    xlb += Pelist->l_off;
		}
	    }
	    xub = dearray[Pelist->edge]->t_xpos;
	    yub = dearray[Pelist->edge]->t_ypos;
	    if (Pelist->r_off != FALSE)
	    {
		if (dearray[Pelist->edge]->direct == H)
		{
		    yub -= Pelist->l_off;
		}
		else
		{
		    xub -= Pelist->l_off;
		}
	    }

	    TWdrawLine(Pelist->edge,
		       xlb - routewidthS,
		       ylb - routewidthS,
		       xub + routewidthS,
		       yub + routewidthS,
		       TWRED,
		       labelptr);
	    Pelist = Pelist->next;
	}
	net_and_route_S = FALSE;
    }

    /***********************************************************
    * FLUSH OUTPUT BUFFER
    ***********************************************************/
    TWflushFrame();

} /* end of draw_the_data */

/* ==================================================================== */

void
setGraphicWindow() 
{

    /***********************************************************
    * set the size of the graphics window
    ***********************************************************/

    INT i;
    INT l;
    INT b;
    INT r;
    INT t;
    INT xlb;
    INT ylb;
    INT expand;

    l = INT_MAX;
    r = INT_MIN;
    b = INT_MAX;
    t = INT_MIN;
    for (i = 1; i <= numnodes; i++)
    {
	xlb = sarray[i]->xpos;
	ylb = sarray[i]->ypos;
	l = MIN(l, xlb);
	r = MAX(r, xlb);
	b = MIN(b, ylb);
	t = MAX(t, ylb);
    }
    expand = (INT) (0.10*(DOUBLE) (r - l));
    expand = MAX(expand, (INT) (0.10*(DOUBLE) (t-b)));
    l -= expand;
    r += expand;
    b -= expand;
    t += expand;
    TWsetwindow(l, b, r, t);
    
} /* end of setGraphicsWindow */

/***********************************************************/
/*****			USER INTERFACE		       *****/
/***********************************************************/
void
process_graphics()
{

    char *inputS;
    char stringS[LRECL];

    /***********************************************************
    * heart of the graphic syskem processes user input
    ***********************************************************/
    INT selection; /* the users pick */

    if (!(graphicsG))
    {
	return;
    }

    /***********************************************************
    * data might have changed so show user current config any
    * function other that the draw controls need to worry about
    * this concurrency problem -  show user current config. 
    ***********************************************************/
    setGraphicWindow();
    draw_the_data();

    /***********************************************************
    * use TWcheckExposure to flush exposure events since we just
    * drew the data
    ***********************************************************/
    TWcheckExposure();
    TWmessage("Mickey is waiting for your response...");

    selection  = CANCEL;
    while (selection != CONTINUE_PROG)
    {
	/***********************************************************
	* loop until exit
	***********************************************************/
	selection = TWcheckMouse();
	switch (selection)
	{

	    case CANCEL:
		/*********************************************************
		* do nothing
		*********************************************************/
		break;

	    case REDRAW:
		draw_the_data();
		/*********************************************************
		* use TWcheckExposure to flush exposure events since
		* we just drew the data
		*********************************************************/
		TWcheckExposure();
		break;

	    case ZOOM:
		TWzoom();
		break;

	    case FULLVIEW:
		TWfullView();
		break;

	    case CONTINUE_PROG:
		break;

	    case AUTO_REDRAW_ON:
		auto_drawS = TRUE;
		break;

	    case AUTO_REDRAW_OFF:
		auto_drawS = FALSE;
		break;

	    case DUMP_GRAPHICS:
		/*********************************************************
		* graphics_dump();
		*********************************************************/
		break;

	    case CLOSE_GRAPHICS:
		TWcloseGraphics();
		return;

	    case DRAW_LABELS:
		drawLabelS = TRUE;
		break;

	    case IGNORE_LABELS:
		drawLabelS = FALSE;
		break;

	    case DRAW_ROUTE:
		gra_rte_index = atoi(TWgetString("Which route?"));
		drawRouteS = TRUE;
		draw_the_data();
		break;

	    case IGNORE_ROUTE:
		drawRouteS = FALSE;
		break;

	    case NET_ROUTE:
		gra_net_index = atoi(TWgetString("Which net?"));
		gra_rte_index = atoi(TWgetString("Which route?"));
		net_and_route_S = TRUE;
		draw_the_data();
		break;

	    case IGNORE_NET_ROUTE:
		net_and_route_S = FALSE;
		break;

	    case ALL_ROUTES:
		gra_rte_index = 1;
		drawRouteS = TRUE;
		draw_the_data();
		while (1)
		{
		    sprintf(stringS, "Next route (%d)?", gra_rte_index+1);
		    inputS = TWgetString(stringS);
		    if (isdigit(inputS[0]))
		    {
			gra_rte_index = atoi(inputS);
			if (1 <= gra_rte_index && gra_rte_index <= numtrees)
			{
			    drawRouteS = TRUE;
			    draw_the_data();
			}
		    }
		    else
		    {
			if (strncmp(inputS, "y", 1) == STRINGEQ
			 || strncmp(inputS, "Y", 1) == STRINGEQ)
			{
			    gra_rte_index++;
			    if (gra_rte_index <= numtrees)
			    {
				drawRouteS = TRUE;
				draw_the_data();
			    }
			    else
			    {
				break;
			    }
			}
			else if (strncmp(inputS, "p", 1) == STRINGEQ
			      || strncmp(inputS, "P", 1) == STRINGEQ)
			{
			    drawRouteS = TRUE;
			    gra_rte_index--;
			    draw_the_data();
			}
			else
			{
			    break;
			}
		    }
		}
		break;

	    case IGNORE_ALL_ROUTES:
		drawRouteS = FALSE;
		break;

	} /*********************** end graphics SWITCH *****************/

	if (auto_drawS && TWcheckExposure())
	{
	    draw_the_data();
	}
    } 
    TWmessage("Continuing: to interupt program click on top menu window");

} /* end process_graphics */

/* ==================================================================== */

#ifdef LATER
/* dumps the data to a file for future study */
static graphics_dump() 
{
    /* now change mode to dump to file */
    TWsetMode(1);
    TWsetFrame(0);
    /* dump the data to a file now instead of screen */
    draw_the_data();
    /* restore the state to previous condition and set draw to screen */
    TWsetMode(0);
}
#endif

#else /* NOGRAPHICS */
/* dummy routines to resolve globals */
#endif
