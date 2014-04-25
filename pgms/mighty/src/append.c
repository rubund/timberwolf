#ifndef lint
static char SccsId[] = "@(#) append.c version 6.2 10/14/90" ;
#endif

#include "mighty.h"
// #define DEBUG
#include <yalecad/debug.h>
#include <yalecad/message.h>

void S_printstats()
/*
 *  print statistics - number of vias, total line length,
 *                     number of rows and columns.
 */
{
    LINKPTR tlink;
    LINKLISTPTR list;
    int i;  /* counter */
    int x,
	y;
    int hlink,
        vlink; 		/* To mark the existence of the links */
    int hlength = 0;
    int vlength = 0;
    int nvia = 0;

    /*
     *  find the wire length
     */
    for( i = 1; i <= num_netsG; i++ )
    {
	for( tlink = net_arrayG[i].path; tlink != (LINKPTR)NULL;
	     tlink = tlink->netnext )
	{
	    if( tlink->layer == HORIZ )
		hlength += tlink->x2 - tlink->x1 + tlink->y2 - tlink->y1;
	    else
		vlength += tlink->x2 - tlink->x1 + tlink->y2 - tlink->y1;
	}
    }

    /*
     *  count the vias
     */
    for( y = 1; y <= num_rowsG; y++ )
    {
	for( x = 1; x <= num_colsG; x++ )
	{
	    if( hlayerG[y][x] == vlayerG[y][x] && hlayerG[y][x] != 0 &&
		hlayerG[y][x] <= num_netsG )
	    {
		hlink = vlink = NO;
		for( list = linklayerG[y][x]; list != (LINKLISTPTR)NULL;
			list = list->next )
		{
		    tlink = list->link;
		    if( tlink->layer == HORIZ )
			hlink = YES;
		    else
			vlink = YES;

		}

		/*
		 *  To include vias on the boundary
		 */
		if( playerhG[y][x] > 0 )
		    hlink = YES;
		if( playervG[y][x] > 0 )
		    vlink = YES;

		if( hlink == YES && vlink == YES )
		{
		    nvia++;
		}
	    }
	}
    }
    printf(" There are %d vias\n", nvia );
    printf(" The total net_length is %d\n", hlength + vlength );
    printf(" ( hlength = %d,  vlength = %d )\n", hlength, vlength );
}

S_dumppins( net )
int net;
{
    PINPTR pin1;

    printf("*** pins of net %d ***\n", net );
    for( pin1 = net_arrayG[net].pin; pin1 != (PINPTR)NULL; pin1 = pin1->next )
    {
	printf("(%d %d) %s %s\n", pin1->x, pin1->y,
	    (pin1->layer == HORIZ ? "H":"V"),
	    (pin1->type == TEMP ? "T":"P") );
    }
}

S_dumppath( net )
int net;
/*
 *  dump all path of the net
 */
{
    LINKPTR tlink;
    printf(" path of net %d\n", net );
    printf(" net group = %d\n", number_to_name(net) );
    for( tlink = net_arrayG[net].path; tlink != (LINKPTR)NULL;
	tlink = tlink->netnext )
    {
	printf("%s (%d, %d) to (%d, %d)\n",
	  (tlink->layer == HORIZ ? "H" : (tlink->layer == VERT ? "V" : "N" )),
	  tlink->x1, tlink->y1, tlink->x2, tlink->y2 );
    }
    printf(" tmp of net %d\n", net );
    for( tlink = net_arrayG[net].tmplist; tlink != (LINKPTR)NULL;
	tlink = tlink->netnext )
    {
	printf("%s (%d, %d) to (%d, %d)\n",
	  (tlink->layer == HORIZ ? "H" : (tlink->layer == VERT ? "V" : "N" )),
	  tlink->x1, tlink->y1, tlink->x2, tlink->y2 );
    }
    printf(" oldpath of net %d\n", net );
    for( tlink = net_arrayG[net].oldpath; tlink != (LINKPTR)NULL;
	tlink = tlink->netnext )
    {
	printf("%s (%d, %d) to (%d, %d)\n",
	  (tlink->layer == HORIZ ? "H" : (tlink->layer == VERT ? "V" : "N" )),
	  tlink->x1, tlink->y1, tlink->x2, tlink->y2 );
    }
    printf(" oldtmp of net %d\n", net );
    for( tlink = net_arrayG[net].oldtmplist; tlink != (LINKPTR)NULL;
	tlink = tlink->netnext )
    {
	printf("%s (%d, %d) to (%d, %d)\n",
	  (tlink->layer == HORIZ ? "H" : (tlink->layer == VERT ? "V" : "N" )),
	  tlink->x1, tlink->y1, tlink->x2, tlink->y2 );
    }
    failed_route( net ) ;
}

S_markborder()
/*
 *  Mark the boundary of the routing area and
 *  obstacles
 */
{
    LINKPTR blink;
    int **flayer;
    int border;
    int xout,
	yout,
	xpos,
	ypos;

    border = num_netsG + 1;

    /*
     *  Mark bounding box
     */
    for( blink = bounding_boxG; blink != (LINKPTR)NULL; blink = blink->netnext )
    {
/*
print_debug ("bb", "horiz", channel->horiz_layer, num_rowsG, num_colsG, num_netsG);
print_debug ("bb", "vert", channel->vert_layer, num_rowsG, num_colsG, num_netsG);
printf("bb (%d, %d) (%d, %d)\n", blink->x1, blink->y1, blink->x2, blink->y2 );
*/
	if( blink->x1 < blink->x2 )
	{
	    ypos = blink->y1;
	    yout = ypos - 1;
	    for( xpos = blink->x1; xpos <= blink->x2; xpos++ )
	    {
		hlayerG[ypos][xpos] = vlayerG[ypos][xpos] = border;
		hlayerG[yout][xpos] = vlayerG[yout][xpos] = border;
	    }
	}
	else if( blink->x2 < blink->x1 )
	{
	    ypos = blink->y1;
	    yout = ypos + 1;
	    for( xpos = blink->x2; xpos <= blink->x1; xpos++ )
	    {
		hlayerG[ypos][xpos] = vlayerG[ypos][xpos] = border;
		hlayerG[yout][xpos] = vlayerG[yout][xpos] = border;
	    }
	}
	else if( blink->y1 < blink->y2 )
	{
	    xpos = blink->x1;
	    xout = xpos + 1;
	    for( ypos = blink->y1; ypos <= blink->y2; ypos++ )
	    {
		hlayerG[ypos][xpos] = vlayerG[ypos][xpos] = border;
		hlayerG[ypos][xout] = vlayerG[ypos][xout] = border;
	    }
	}
	else if( blink->y2 < blink->y1 )
	{
	    xpos = blink->x1;
	    xout = xpos - 1;
	    for( ypos = blink->y2; ypos <= blink->y1; ypos++ )
	    {
		hlayerG[ypos][xpos] = vlayerG[ypos][xpos] = border;
		hlayerG[ypos][xout] = vlayerG[ypos][xout] = border;
	    }
	}
    }

    /*
     *  Mark obstacles
     */
    for( blink = obstacleG; blink != (LINKPTR)NULL; blink = blink->netnext )
    {
/*
print_debug ("bb", "horiz", channelG->horiz_layer, num_rowsG, num_colsG, num_netsG);
print_debug ("bb", "vert", channelG->vert_layer, num_rowsG, num_colsG, num_netsG);
printf("ob %d, ( %d, %d) (%d, %d)\n", blink->layer, blink->x1, blink->y1,
blink->x2, blink->y2 );
*/
	if( blink->layer == HORIZ )
	    flayer = hlayerG;
	else
	    flayer = vlayerG;

	if( blink->x1 < blink->x2 )
	{
	    ypos = blink->y1;
	    for( xpos = blink->x1; xpos <= blink->x2; xpos++ )
	    {
		flayer[ypos][xpos] = border;
	    }
	}
	else if( blink->x2 < blink->x1 )
	{
	    ypos = blink->y1;
	    for( xpos = blink->x2; xpos <= blink->x1; xpos++ )
	    {
		flayer[ypos][xpos] = border;
	    }
	}
	else if( blink->y1 < blink->y2 )
	{
	    xpos = blink->x1;
	    for( ypos = blink->y1; ypos <= blink->y2; ypos++ )
	    {
		flayer[ypos][xpos] = border;
	    }
	}
	else if( blink->y2 < blink->y1 )
	{
	    xpos = blink->x1;
	    for( ypos = blink->y2; ypos <= blink->y1; ypos++ )
	    {
		flayer[ypos][xpos] = border;
	    }
	}
	else
	{
	    flayer[blink->y1][blink->x1] = border;
	}
    }
}

S_equivpins( net )
int net;
/*
 *  Mark set of equivalent pins which are on one grid-point
 */
{
    PINPTR pin1,
	   pin2;
    int numequiv = 0;

    for( pin1 = net_arrayG[net].pin; pin1 != (PINPTR)NULL; pin1 = pin1->next )
    {
	pin1->equiv = 0;
    }

    if( net_arrayG[net].pin != (PINPTR)NULL )
    {
      for( pin1 = net_arrayG[net].pin; pin1->next != (PINPTR)NULL; pin1 = pin1->next )
      {
	for( pin2 = pin1->next; pin2 != (PINPTR)NULL; pin2 = pin2->next )
	{
	    if( pin1->x == pin2->x && pin1->y == pin2->y )
	    {
		numequiv++;
		pin1->equiv = numequiv;
		pin2->equiv = numequiv;
		pin1->group = numequiv+1;
		pin2->group = numequiv+1;
	    }
	}
      }
    }
    net_arrayG[net].numequiv = numequiv;
}

int S_compensateequiv( net )
int net;
/*
 *  equivalent pins and links must have the same group number
 */
{
    PINPTR pin1;
    LINKPTR link;
    int i;
    int mingp ;

    for( i = 1; i <= net_arrayG[net].numequiv; i++ )
    {
	mingp = INFINITY;
	/*
	 *  find minimum group number of class i
	 */
	for( pin1 = net_arrayG[net].pin; pin1 != (PINPTR)NULL; pin1 = pin1->next)
	{
	    if( pin1->equiv == i )
	        mingp = MIN( mingp, pin1->group );
	}
	/*
	 *  set group number
	 */
	for( pin1 = net_arrayG[net].pin; pin1 != (PINPTR)NULL; pin1 = pin1->next)
	{
	    if( pin1->equiv == i && pin1->group != mingp )
	    {
		for( link = net_arrayG[net].path; link != (LINKPTR)NULL;
			link = link->netnext )
		{
		    if( link->group == pin1->group )
			link->group = mingp;
		}
		pin1->group = mingp;
	    }
	}
    }

    mingp = INFINITY;
    for( pin1 = net_arrayG[net].pin; pin1 != (PINPTR)NULL; pin1 = pin1->next)
    {
	/* If mutiple components, return 2 */
	if( pin1->group > 1 )
	    mingp = MIN( mingp, pin1->group );
    }
    if( mingp == INFINITY )
	return( 1 );
    else if( mingp == 2 )
	return( 2 );
    else
    {
	/*
	 *  Shift the mingp to 2, so that group 1 and 2 exist
	 *  S_improve and S_powerimprove use groups 1 and 2
	 */
	for( pin1 = net_arrayG[net].pin; pin1 != (PINPTR)NULL; pin1 = pin1->next)
	{
	    if( pin1->group == mingp )
		pin1->group = 2;
	}
	for( link = net_arrayG[net].path; link != (LINKPTR)NULL; link = link->netnext )
	{
	    if( link->group == mingp )
		link->group = 2;
	}
    }
    return( 3 ); /* NOT EXACT */
}


void S_connectboundary()
/*
 *  connect boundary - connect the pins on the boundary( tmppin )
 */
{
    /* IMPORTANT a note on temporary and permanent pins :     */
    /* permanent pins is a misnomer - permanent pins have been */
    /* moved inside the boundary not temporary pins why??? WPS */
    PINPTR cpin;
    BOOL foundPin ;
    int i;  /* counter */
    int group ;   /* speed indirection */
    int x1,
	y1;       /* position of temporary pin */
    int usr_x1,
	usr_y1;   /* position of temporary pin according to usr coord. */
    int x2,
	y2;       /* expected position of permanent pin */
    int usr_x2,
	usr_y2;   /* expected position of perm. pin according to user. */
    PINPTR tpin;  /* position of permanent pin given by user */
    PIN_LISTPTR curpin ; /* current third layer pin */
    void S_addpathlink();
    extern xshift, yshift ;

    /*
     *  add link to connect tmppins
     */
    for( i = 1; i <= num_netsG; i++ ){
	for( cpin = net_arrayG[i].tmppin; cpin; cpin = cpin->next ){

	    foundPin = FALSE ;
	    /* use temp variables for speed */
	    /* x1 & y1 are not correct until +-1 correction below */
	    x1 = x2 = cpin->x;
	    y1 = y2 = cpin->y;
	    /* convert temporary pin to user coordinates */
	    usr_x2 = (x2 - 1) * xgridG + xshift ;
	    usr_y2 = (y2 - 1) * ygridG + yshift ;

	    /* four cases */
	    group = cpin->group ;
	    /*  *** VERTICAL CASE  *** */
	    if( group == DOWN || group == UP){
		if( group == DOWN ){
		    y1++;
		} else {  /* group == UP */
		    y1--;
		}
		usr_x1 = usr_x2 ;
		usr_y1 = (y1 - 1) * ygridG + yshift ;
		/* need to find corresponding shifted pin */
		for( tpin = net_arrayG[i].pin; tpin; tpin=tpin->next ){
		    if( tpin->type == THREE ){
			continue ;
		    }
		    if( tpin->x == x1 && tpin->y == y1 && 
			cpin->x_given == tpin->x_given &&
			cpin->y_given == tpin->y_given ){ 
			foundPin = TRUE ;
			break ;
		    }
		}
		if( foundPin ){
		    if( tpin->type == TEMP ){
			/* case of temporary pin process normally */
			S_addpathlink( cpin->layer, 
			    x1, y1,
			    x2, y2, i );
			continue ;
		    }
		    S_turn_user_given_on(x1,y1) ; 
		    if( tpin->x_given == usr_x2 ){ /* pin is on grid */
			/* at output time don't change pin position */
			/* only need to add single link to pin */
			S_addpathlink( cpin->layer, 
			    usr_x1, usr_y1,
			    usr_x2, tpin->y_given, i );
		    } else {
			/* need multiple links to permament pin */
			/* dogleg is performed here */
			S_addpathlink( cpin->layer, 
			    usr_x1, usr_y1, 
			    tpin->x_given, usr_y1, i );
			/* again turn on user given switch */
			S_turn_user_given_on(-1,-1) ; 
			S_addpathlink( cpin->layer, 
			    tpin->x_given, usr_y1, 
			    tpin->x_given, tpin->y_given, i );
		    }

		} else {
		    S_pin_match_error( x2, y2, i ) ;
		} 
		/*  *** END VERTICAL CASE  *** */


	    /*  *** HORIZONTAL CASE  *** */
	    } else if( group == LEFT || group == RIGHT){
		if( group == LEFT ){
		    x1--;
		} else {  /* group == RIGHT */
		    x1++;
		}
		usr_x1 = (x1 - 1) * xgridG + xshift ;
		usr_y1 = usr_y2 ;
		/* need to find corresponding shifted pin */
		for( tpin = net_arrayG[i].pin; tpin; tpin=tpin->next ){
		    if( tpin->type == THREE ){
			continue ;
		    }
		    if( tpin->x == x1 && tpin->y == y1 &&
			cpin->x_given == tpin->x_given &&
			cpin->y_given == tpin->y_given ){ 
			foundPin = TRUE ;
			break ;
		    }
		}
	       if( foundPin ){
		    if( tpin->type == TEMP ){
			/* case of temporary pin process normally */
			S_addpathlink( cpin->layer, 
			    x1, y1,
			    x2, y2, i );
			continue ;
		    }
		    S_turn_user_given_on(x1,y1) ; 
		    if( tpin->y_given == usr_y2 ){ /* pin is on grid */
			/* at output time don't change pin position */
			/* only need to add single link to pin */
			S_addpathlink( cpin->layer, 
			    usr_x1, usr_y1,
			    tpin->x_given, usr_y2, i );
		    } else {
			/* need multiple links to permament pin */
			/* dogleg is performed here */
			S_addpathlink( cpin->layer, 
			    usr_x1, usr_y1, 
			    usr_x1, tpin->y_given, i );
			/* again turn on user given switch */
			S_turn_user_given_on(-1,-1) ; 
			S_addpathlink( cpin->layer, 
			    usr_x1, tpin->y_given, 
			    tpin->x_given, tpin->y_given, i );
		    }

	       } else {
		  S_pin_match_error( x2, y2, i ) ;
	       } 
	    }
	    /*  *** END HORIZONTAL CASE  *** */
	}
    } /* end net loop */

    /* now add layer 3 connects */
    for( curpin = two5pinsG ; curpin ; curpin = curpin->next ){
	cpin = curpin->pin ;
	
	/* need to shift to user position */
	x1 = cpin->x;
	y1 = cpin->y;

	/* convert temporary pin to user coordinates */
	usr_x1 = (x1 - 1) * xgridG + xshift ;
	usr_y1 = (y1 - 1) * ygridG + yshift ;

	S_turn_user_given_on(x1,y1) ; 
	S_addpathlink( THREE, usr_x1, usr_y1, 
	    cpin->x_given, cpin->y_given, curpin->net );

    } /* end layer 3 for loop */
}

/*  this function outputs an error message to stderr when we */
/*  cannot crossreference a permanent pin to its temporary projection */
/*  pin */
S_pin_match_error( x, y, i )
int x,y ;  /* point of mismatch */
int i ;    /* net number */
{
    M( ERRMSG, "pin_match_error","couldn't find permanent\n"); 
    sprintf( YmsgG, "pin @ (%d,%d) for net:%d\n", x, y,
	number_to_name(i) );
    M( MSG, NULL, YmsgG ) ;
}
