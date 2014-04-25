/* ----------------------------------------------------------------- 
FILE:	    macro.c 
DESCRIPTION:This file contains the functions for macro cells.
CONTENTS:   
DATE:	    Oct	29, 1988 
REVISIONS:  
----------------------------------------------------------------- */
#ifndef lint
static char SccsId[] = "@(#) macro.c version 6.2 12/27/90" ;
#endif

#include "mighty.h"
#include <yalecad/message.h>

#define E 0
#define U 1
#define L 2
#define R 3
#define D 4
#define S 5  /* start state */

static int nextStateS[5][5] = 
{
    /* ERROR state */  E, E, E, E, E,
    /* UP    state */  E, L, U, R, /* D */ E,
    /* LEFT  state */  E, D, L, U, /* R */ E,
    /* RIGHT state */  E, U, R, D, /* L */ E,
    /* DOWN  state */  E, R, D, L, /* U */ E
} ;

static int errorArrayS[6] =
{
    /* E - U - L - R - D - S */
       E,  D,  R,  L,  U,  S 
} ;

static BOOL abortFlagS = FALSE ;

S_process_macros() 
{

    MACROPTR curmacro ;

    /* determine side for each edge */
    for( curmacro = macroG; curmacro; curmacro = curmacro->next ){
        S_determine_sidesCW( curmacro->edges ) ;
    }

    if( abortFlagS ){
	YexitPgm(145) ;
    }

} /* end S_process_macros */

/* determine the side and check for consistency */
BOOL S_determine_sidesCW( link )
LINKPTR link ;
{
    int oldX, oldY ;
    int cur_state, next_state ;

    cur_state = S ;
    oldX = link->x1 ;
    oldY = link->y1 ;
    for( ; link; link = link->netnext ){
	if( link->x1 != oldX || link->y1 != oldY ){
	    sprintf( YmsgG, 
	    "Path is not continuous @(%d:%d)\n",oldX,oldY) ;
	    M( ERRMSG, "determine_sides", YmsgG ) ;
	    abortFlagS = TRUE ;
	    continue ;
	}
	/* determine direction */
	if( link->x2 == oldX && link->y2 == oldY ){
	    sprintf( YmsgG, 
	    "Redundant point @(%d:%d)\n",oldX,oldY) ;
	    M( ERRMSG, "determine_sides", YmsgG ) ;
	    abortFlagS = TRUE ;
	    continue ;
	} else if( link->x2 != oldX && link->y2 != oldY ){
	    sprintf( YmsgG, 
	    "Edge is not orthogonal @(%d:%d)\n",oldX,oldY) ;
	    M( ERRMSG, "determine_sides", YmsgG ) ;
	    abortFlagS = TRUE ;
	    continue ;
	} else if( link->x2 == oldX ){
	    if( link->y2 < oldY ){
		next_state = D ; 
	    } else {
		next_state = U ; 
	    }
	} else if( link->y2 == oldY ){
	    if( link->x2 < oldX ){
		next_state = L ; 
	    } else {
		next_state = R ; 
	    }
	}
	/* check to see if this is an error by looking in */
	/* error array */
	if( next_state == errorArrayS[cur_state] ){
	    sprintf( YmsgG, 
	    "Invalid point @(%d:%d)\n",link->x2,link->y2 ) ;
	    M( ERRMSG, "determine_sides", YmsgG ) ;
	    abortFlagS = TRUE ;
	    continue ;
	} 

	/* save side in link */
	link->p.edge_direction = next_state ;
	/* update state */
	cur_state = next_state ;

	oldX = link->x2 ;
	oldY = link->y2 ;

    }
    return( abortFlagS ) ;

} /* end S_determine_sides */


/* determine the side and check for consistency */
BOOL S_determine_sidesCCW( link )
LINKPTR link ;
{
    int oldX, oldY ;
    int cur_state, next_state ;

    cur_state = S ;
    oldX = link->x2 ;
    oldY = link->y2 ;
    for( ; link; link = link->netnext ){
	if( link->x2 != oldX || link->y2 != oldY ){
	    sprintf( YmsgG, 
	    "Path is not continuous @(%d:%d)\n",oldX,oldY) ;
	    M( ERRMSG, "determine_sides", YmsgG ) ;
	    abortFlagS = TRUE ;
	    continue ;
	}
	/* determine direction */
	if( link->x1 == oldX && link->y1 == oldY ){
	    sprintf( YmsgG, 
	    "Redundant point @(%d:%d)\n",oldX,oldY) ;
	    M( ERRMSG, "determine_sides", YmsgG ) ;
	    abortFlagS = TRUE ;
	    continue ;
	} else if( link->x1 != oldX && link->y1 != oldY ){
	    sprintf( YmsgG, 
	    "Edge is not orthogonal @(%d:%d)\n",oldX,oldY) ;
	    M( ERRMSG, "determine_sides", YmsgG ) ;
	    abortFlagS = TRUE ;
	    continue ;
	} else if( link->x1 == oldX ){
	    if( link->y1 < oldY ){
		next_state = D ; 
	    } else {
		next_state = U ; 
	    }
	} else if( link->y1 == oldY ){
	    if( link->x1 < oldX ){
		next_state = L ; 
	    } else {
		next_state = R ; 
	    }
	}
	/* check to see if this is an error by looking in */
	/* error array */
	if( next_state == errorArrayS[cur_state] ){
	    sprintf( YmsgG, 
	    "Invalid point @(%d:%d)\n",link->x2,link->y2 ) ;
	    M( ERRMSG, "determine_sides", YmsgG ) ;
	    abortFlagS = TRUE ;
	    continue ;
	} 

	/* save side in link */
	link->p.edge_direction = next_state ;
	/* update state */
	cur_state = next_state ;

	oldX = link->x1 ;
	oldY = link->y1 ;

    }
    return( abortFlagS ) ;

} /* end S_determine_sidesCCW */


S_grid_path( firstlink, direction )
LINKPTR firstlink ;
BOOL direction ;
{

    LINKPTR link ;
    LINKPTR nextlink ;
    LINKPTR lastlink ;
    extern xshift ;
    extern yshift ;

    if( direction == CW ){
	for( link = firstlink; link; link = link->netnext ){
	    /* now grid link by expanding outward */
	    switch( link->p.edge_direction ){
	    case U:
		Ygridx_down( &(link->x1) ) ;
		Ygridx_down( &(link->x2) ) ;
		break ;
	    case L:
		Ygridy_down( &(link->y1) ) ;
		Ygridy_down( &(link->y2) ) ;
		break ;
	    case R:
		Ygridy_up( &(link->y1) ) ;
		Ygridy_up( &(link->y2) ) ;
		break ;
	    case D:
		Ygridx_up( &(link->x1) ) ;
		Ygridx_up( &(link->x2) ) ;
		break ;
	    } /* end switch */
	}

	/* get last link */
	for( lastlink=firstlink;lastlink->netnext;lastlink=lastlink->netnext); 

	for( link = firstlink; link; link=link->netnext ){
	    /* now connect the paths of the links together again */
	    if(!(nextlink = link->netnext)){
		/* next link must be first edge */
		nextlink = firstlink ;
	    }
	    if(!(lastlink)){
		/* create a circular linked list */
		lastlink = firstlink ;
	    }

	    switch( link->p.edge_direction ){
	    case U:
		link->y1 = lastlink->y1 ;
		link->y2 = nextlink->y1 ;
		break ;
	    case L:
		link->x1 = lastlink->x1 ;
		link->x2 = nextlink->x1 ;
		break ;
	    case R:
		link->x1 = lastlink->x1 ;
		link->x2 = nextlink->x1 ;
		break ;
	    case D:
		link->y1 = lastlink->y1 ;
		link->y2 = nextlink->y1 ;
		break ;
	    } /* end switch */

	    lastlink = lastlink->netnext ;
	}
    } else {  /* Counter clockwise case */
	for( link = firstlink; link; link = link->netnext ){
	    /* now grid link by expanding outward */
	    switch( link->p.edge_direction ){
	    case U:
		Ygridx_up( &(link->x1) ) ;
		Ygridx_up( &(link->x2) ) ;
		break ;
	    case L:
		Ygridy_up( &(link->y1) ) ;
		Ygridy_up( &(link->y2) ) ;
		break ;
	    case R:
		Ygridy_down( &(link->y1) ) ;
		Ygridy_down( &(link->y2) ) ;
		break ;
	    case D:
		Ygridx_down( &(link->x1) ) ;
		Ygridx_down( &(link->x2) ) ;
		break ;
	    } /* end switch */
	}

	/* get last link */
	for( lastlink=firstlink;lastlink->netnext;
	    lastlink=lastlink->netnext) ; 

	for( link = firstlink; link; link = link->netnext ){
	    /* now connect the paths of the links together again */
	    if(!(nextlink = link->netnext)){
		/* next link must be first edge */
		nextlink = firstlink ;
	    }
	    if(!(lastlink)){
		/* create a circular linked list */
		lastlink = firstlink ;
	    }
	    switch( link->p.edge_direction ){
	    case U:
		link->y1 = nextlink->y1 ;
		link->y2 = lastlink->y1 ;
		break ;
	    case L:
		link->x1 = nextlink->x1 ;
		link->x2 = lastlink->x1 ;
		break ;
	    case R:
		link->x1 = nextlink->x1 ;
		link->x2 = lastlink->x1 ;
		break ;
	    case D:
		link->y1 = nextlink->y1 ;
		link->y2 = lastlink->y1 ;
		break ;
	    } /* end switch */

	    lastlink = lastlink->netnext ;
	}
    }

    /* now divide by grid as usual */
    for( link = firstlink; link; link = link->netnext ){
	/* shift to (0,0) */
	link->x1 -= xshift;
	link->x2 -= xshift;
	link->y1 -= yshift;
	link->y2 -= yshift;
	link->x1 /= xgridG ;
	link->x2 /= xgridG ;
	link->y1 /= ygridG ;
	link->y2 /= ygridG ;
	/* shift to (1,1) */
	link->x1++;
	link->x2++;
	link->y1++;
	link->y2++;
    }

} /* end grid path */


/* add macro obstacles */
S_add_macro_obstacles() 
{

    BOOL layer1, layer2 ;
    LINKPTR link ;
    MACROPTR curmacro ;

    /* add obstacle for each edge */
    for( curmacro = macroG; curmacro; curmacro = curmacro->next ){
	for( link = curmacro->edges; link; link = link->netnext ){
	    /* determine need layers */
	    if( link->layer / 2 ){
		layer1 = TRUE ;
	    } 
	    if( link->layer % 2 ){
		layer2 = TRUE ;
	    } else {
		layer2 = FALSE ;
	    }
	    switch( link->p.edge_direction ){
	    case U:
		/* cell edge is up - left side of cell */
		/* check layers we wish to add obstacles */
		if( layer1 ){
		    add_obstacle( link->x1, link->y1,
			link->x2, link->y2, 1 ) ;
		    /* blocking layer */
		    add_obstacle( link->x1 + 1, link->y1,
			link->x2 + 1, link->y2, 1 ) ;
		}
		if( layer2 ){
		    add_obstacle( link->x1, link->y1,
			link->x2, link->y2, 2 ) ;
		    /* blocking layer */
		    add_obstacle( link->x1 + 1, link->y1,
			link->x2 + 1, link->y2, 2 ) ;
		}
		break ;
	    case L:
		/* cell edge is left - bottom side of cell */
		if( layer1 ){
		    add_obstacle( link->x1, link->y1,
			link->x2, link->y2, 1 ) ;
		    add_obstacle( link->x1, link->y1 + 1,
			link->x2, link->y2 + 1, 1 ) ;
		}
		if( layer2 ){
		    add_obstacle( link->x1, link->y1,
			link->x2, link->y2, 2 ) ;
		    add_obstacle( link->x1, link->y1 + 1,
			link->x2, link->y2 + 1, 2 ) ;
		}
		break ;
	    case R:
		/* cell edge is right - top side of cell */
		if( layer1 ){
		    add_obstacle( link->x1, link->y1,
			link->x2, link->y2, 1 ) ;
		    add_obstacle( link->x1, link->y1 - 1,
			link->x2, link->y2 - 1, 1 ) ;
		}
		if( layer2 ){
		    add_obstacle( link->x1, link->y1,
			link->x2, link->y2, 2 ) ;
		    add_obstacle( link->x1, link->y1 - 1,
			link->x2, link->y2 - 1, 2 ) ;
		}
		break ;
	    case D:
		/* cell edge is down - right side of cell */
		if( layer1 ){
		    add_obstacle( link->x1, link->y1,
			link->x2, link->y2, 1 ) ;
		    add_obstacle( link->x1 - 1, link->y1,
			link->x2 - 1, link->y2, 1 ) ;
		}
		if( layer2 ){
		    add_obstacle( link->x1, link->y1,
			link->x2, link->y2, 2 ) ;
		    add_obstacle( link->x1 - 1, link->y1,
			link->x2 - 1, link->y2, 2 ) ;
		}
		break ;

	    } /* end switch */

	} /* end link loop */

    } /* end macro loop */

} /* end adding core obstacles */
