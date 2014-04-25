#ifndef lint
static char SccsId[] = "@(#) path.c version 6.2 10/14/90" ;
#endif

#include "mighty.h"

extern int HCOST1;
extern int VCOST1;

extern int HCOST2;
extern int VCOST2;
extern int SWCOST;

extern int LIMCOST;
extern int MODCOST;

SEARCHPTR *searchq;

/*
 *  find min_cost path of net i
 *  return YES or NO
 */
int S_findpath( net, cleanup )
int net;
int cleanup;
{
    int	**hgp,     /* horiz_conn_components */
	**vgp;     /* vert_conn_components */
    SEARCHPTR tmpq;
    PINPTR tpin;
    LINKPTR tmplink;
    int i;         /* counter */
    int keycost,   /* cost to access searchq ( = cost % MODCOST) */
	cost;
    int group,
	layer;
    int x,
	y;
    void S_retlink();
    void S_searchnext();

    hgp = channelG->hcomp;
    vgp = channelG->vcomp;

    /*
     * clear tmppath
     */
    while( (tmplink = net_arrayG[net].tmplist) != (LINKPTR)NULL )
    {
	net_arrayG[net].tmplist = tmplink->netnext;
	S_retlink( tmplink );
    }

    /*
     *  mark all pins
     */
    for( i = 1; i <= num_netsG; i++ )
    {
	for( tpin = net_arrayG[i].pin; tpin != (PINPTR)NULL; tpin = tpin->next )
	{
	    if( tpin->layer == HORIZ )
		hlayerG[tpin->y][tpin->x] = i;
	    if( tpin->layer == VERT )
		vlayerG[tpin->y][tpin->x] = i;
	}
    }

/*
print_channel (channel, num_rowsG, num_colsG, num_netsG);
*/
    /*
     *  push current locations of routing
     */
    cost = 1;
    for( tpin = net_arrayG[net].pin; tpin != (PINPTR)NULL; tpin = tpin->next )
    {
	if( tpin->layer == VERT )
	    S_searchnext(vlayerG, hlayerG, HCOST2, VCOST1, SWCOST,
			 vgp, hgp, tpin->x, tpin->y, tpin->group, cost);

	if( tpin->layer == HORIZ )
	    S_searchnext(hlayerG, vlayerG, HCOST1, VCOST2, SWCOST,
			 hgp, vgp, tpin->x, tpin->y, tpin->group, cost);
    }
    for( tmplink = net_arrayG[net].path; tmplink != (LINKPTR)NULL;
	 tmplink = tmplink->netnext )
    {
	if( tmplink->layer == HORIZ )
	{
	    if( tmplink->x1 == tmplink->x2 )
	        for( y = tmplink->y1; y <= tmplink->y2; y++ )
	            S_searchnext(hlayerG, vlayerG, HCOST1, VCOST2, SWCOST,
			hgp, vgp, tmplink->x1, y, tmplink->group, cost);
	    else
	        for( x = tmplink->x1; x <= tmplink->x2; x++ )
	            S_searchnext(hlayerG, vlayerG, HCOST1, VCOST2, SWCOST,
			hgp, vgp, x, tmplink->y1, tmplink->group, cost);
	}
	else
	{
	    if( tmplink->x1 == tmplink->x2 )
	        for( y = tmplink->y1; y <= tmplink->y2; y++ )
	            S_searchnext(vlayerG, hlayerG, HCOST2, VCOST1, SWCOST,
			vgp, hgp, tmplink->x1, y, tmplink->group, cost);
	    else
	        for( x = tmplink->x1; x <= tmplink->x2; x++ )
	            S_searchnext(vlayerG, hlayerG, HCOST2, VCOST1, SWCOST,
			vgp, hgp, x, tmplink->y1, tmplink->group, cost);
	}
    }

    /*
     *  find the shortest link which can reduce the number of
     *  connected components
     */
    while( cost <= LIMCOST ) {
	keycost = cost % MODCOST;
	if( searchq[keycost] == (SEARCHPTR)NULL) {
	    cost++;
	    continue;
	}
	/*
	 *  pop the first job from searchq
	 */
	tmpq = searchq[keycost];
	x = tmpq->x;
	y = tmpq->y;
	group = tmpq->group;
	layer = tmpq->layer;
	searchq[keycost] = tmpq->next;
	S_retsearchq( tmpq );
	if( layer == HORIZ ){
	    if( S_searchnext(hlayerG, vlayerG, HCOST1, VCOST2, SWCOST,
		hgp, vgp, x, y, group, cost) == YES){
		break;
	    }
	} else if( layer == VERT ){
	    if( S_searchnext(vlayerG, hlayerG, HCOST2, VCOST1, SWCOST,
		vgp, hgp, x, y, group, cost) == YES){
		break;
	    }
	}
    }
    if( cost > LIMCOST ) {

	if( debugG ) {
	    printf("path search failed at cost %d\n", cost );
	    print_debug ("search failed", "horiz", 
	    channelG->horiz_layer, num_rowsG, num_colsG, num_netsG);
	    print_debug ("search failed", "vert",
	    channelG->vert_layer, num_rowsG, num_colsG, num_netsG);
	    print_debug ("search failed", "hcomp", 
	    channelG->hcomp, num_rowsG, num_colsG, num_netsG);
	    print_debug ("search failed", "vcomp", 
	    channelG->vcomp, num_rowsG, num_colsG, num_netsG);
	}

	net_arrayG[net].cost = INFINITY;
	S_cleansearchq();
	if( cleanup == YES )
	    S_cleantrace();
	return( NO );

    } else {
	net_arrayG[net].cost = cost;  /* zzz tmp */
	S_cleansearchq();
	S_backtrack( layer, x, y, group, net, cost );
	S_cleantrace();
        return( YES );  /* path found */
    }
}

/*
 *  mark current point and search the next point.
 */
S_searchnext(flayer, slayer, hcost, vcost, swcost, fgp, sgp, x, y, group, cost)
int **flayer,   /* primary layer */
    **slayer;   /* secondary layer */
int hcost,
    vcost,
    swcost;
int **fgp,      /* group of primary layer */
    **sgp;      /* group of secondary layer */
int x,
    y,
    group,
    cost;
{
    int newx,
        newy;
    int touchcost;
    PIN_LISTPTR p;

    if( flayer[y][x] != 0 && fgp[y][x] != 0 )
    {
	if( fgp[y][x] == group )
	{
	    if( flayer[y][x] >= - cost )
	        return( NO );   /* already searched */
	    /*
	    else
	        flayer[y][x] = - cost;
	    */
	}
	else
	    return( YES );  /* found */
    }
    /*
     *  still flayer[y][x] == 0
     *  mark point [y][x] and check neighbors
     */
    if( flayer[y][x] <= 0 )
        flayer[y][x] = - cost;
    fgp[y][x] = group;
    /*
     *  check UP, DOWN, LEFT, RIGHT, and OTHER LAYER
     */
    newy = y + 1;
    {
	if(flayer[newy][x] == 0 )
	    S_pushsearchq( cost + vcost, x, newy, group, flayer[0][0]);
	else if(fgp[newy][x] > 0 && fgp[newy][x] != group)
	{
	    touchcost = (cost + vcost + MAX( 1, - flayer[newy][x]))/2;
	    S_pushsearchq( touchcost, x, newy, group, flayer[0][0]);
	}
    }
    newy = y - 1;
    {
	if( flayer[newy][x] == 0 )
	    S_pushsearchq( cost + vcost, x, newy, group, flayer[0][0] );
	else if (fgp[newy][x] > 0 && fgp[newy][x] != group)
	{
	    touchcost = (cost + vcost + MAX( 1, - flayer[newy][x]))/2;
	    S_pushsearchq( touchcost, x, newy, group, flayer[0][0]);
	}
    }
    newx = x + 1;
    {
	if(flayer[y][newx] == 0 )
	    S_pushsearchq( cost + hcost, newx, y, group, flayer[0][0] );
	else if (fgp[y][newx] > 0 && fgp[y][newx] != group)
	{
	    touchcost = (cost + hcost + MAX( 1, - flayer[y][newx]))/2;
	    S_pushsearchq( touchcost, newx, y, group, flayer[0][0]);
	}
    }
    newx = x - 1;
    {
	if(flayer[y][newx] == 0 )
	    S_pushsearchq( cost + hcost, newx, y, group, flayer[0][0] );
	else if(fgp[y][newx] > 0 && fgp[y][newx] != group)
	{
	    touchcost = (cost + hcost + MAX( 1, - flayer[y][newx]))/2;
	    S_pushsearchq( touchcost, newx, y, group, flayer[0][0]);
	}
    }

/* try passing thru to another level */
    for(p=layer3G[x]; p != (PIN_LISTPTR)NULL ; p=p->next ) {
      if( p->pin->y == y )	/* no vias allowed on .5 layer pins */
        break; 
      }
    if( slayer[y][x] == 0 ) {
	if ( p == (PIN_LISTPTR)NULL && !riverG ) /* p=NULL means ok to passthru */
	  S_pushsearchq( cost + swcost, x, y, group, slayer[0][0] );
	}
    else if (sgp[y][x] > 0 && sgp[y][x] != group)
      if ( p == (PIN_LISTPTR)NULL && !riverG ) {  /* p=NULL means ok to passthru */
	touchcost = (cost + swcost + MAX( 1, - slayer[y][x]))/2;
	S_pushsearchq( touchcost, x, y, group, slayer[0][0]);
	}
    return( NO );
}

/*
 *  if tmppath of net i has not been blocked, route the path
 *  if routing is successful, append tmplist to list, set pointers
 *                  on linklayer and return YES
 *		    Also clear the history.
 *  else remove every thing done here and free the tmplist, return NO
 */
int S_trytmppath( i )
int i;
{
    int **tmplayer,
	**gplayer;
    int blocked = FALSE;
    LINKPTR link;
    int x,
        y;

/*
printf("trytmppath of net %d\n", i);
*/
    /*
     *  mark the path
     */
    for( link = net_arrayG[i].tmplist; link != (LINKPTR)NULL;
	 link = link->netnext)
    {
/*
printf("try link %s net = %d (%d, %d), (%d, %d)\n",
( link->layer == HORIZ ? "H" : "V" ),
link->net, link->x1, link->y1, link->x2, link->y2);
 */
	if( link->layer == 0 )
    continue;
	if( link->layer == HORIZ )
	{
	    tmplayer = channelG->horiz_layer;
	    gplayer = channelG->hcomp;
	}
	else
	{
	    tmplayer = channelG->vert_layer;
	    gplayer = channelG->vcomp;
	}
	if( link->x1 == link->x2 )
	{
	    for( y = link->y1; y <= link->y2; y++ )
	    {
		if( tmplayer[y][link->x1] == 0 )
		{
		    tmplayer[y][link->x1] = i;
		    gplayer[y][link->x1] = -1;
		}
		else if( tmplayer[y][link->x1] != i )
		{
		    blocked = TRUE;
		    break;
		}
	    }
	}
	else
	{
	    for( x = link->x1; x <= link->x2; x++ )
	    {
		if( tmplayer[link->y1][x] == 0 )
		{
		    tmplayer[link->y1][x] = i;
		    gplayer[link->y1][x] = -1;
		}
		else if( tmplayer[link->y1][x] != i )
		{
		    blocked = TRUE;
		    break;
		}
	    }
	}
    }
    if ( blocked == FALSE )
    {
	/*
	 *  clean up component layer
	 */
        for( link = net_arrayG[i].tmplist; link != (LINKPTR)NULL;
	     link = link->netnext)
        {
	    if( link->layer == 0 )
	continue;
	    if( link->layer == HORIZ )
	        gplayer = channelG->hcomp;
	    else
	        gplayer = channelG->vcomp;
	    if( link->x1 == link->x2 )
	        for( y = link->y1; y <= link->y2; y++ )
		    gplayer[y][link->x1] = 0;
	    else
	        for( x = link->x1; x <= link->x2; x++ )
		    gplayer[link->y1][x] = 0;
	}
	/*
	 *  move tmppath to path
	 */
	while( (link = net_arrayG[i].tmplist) != (LINKPTR)NULL )
	{
            net_arrayG[i].tmplist = link->netnext;
	    if( link->layer == 0 )
	    {
		S_divlink( link->x1, link->y1, i );
		S_retlink( link );
	    }
	    else
	    {
   	        S_addlklayer(link, link->x1, link->y1);
	        S_addlklayer(link, link->x2, link->y2);
                link->netnext = net_arrayG[i].path;
                net_arrayG[i].path = link;
	    }
	}
        return( YES );
    }
    else
    {
/*
print_debug ("tmppath failed", "horiz", channel->horiz_layer, num_rowsG, num_colsG, num_netsG);
print_debug ("tmppath failed", "vert", channel->vert_layer, num_rowsG, num_colsG, num_netsG);
print_debug ("tmppath failed", "hcomp", channel->hcomp, num_rowsG, num_colsG, num_netsG);
print_debug ("tmppath failed", "vcomp", channel->vcomp, num_rowsG, num_colsG, num_netsG);
*/
	/*
	 *  remove all the marks made here
	 */
        for( link = net_arrayG[i].tmplist; link != (LINKPTR)NULL;
	     link = link->netnext)
        {
	    if( link->layer == HORIZ )
	    {
	        tmplayer = channelG->horiz_layer;
	        gplayer = channelG->hcomp;
	    }
	    else
	    {
	        tmplayer = channelG->vert_layer;
	        gplayer = channelG->vcomp;
	    }
	    if( link->x1 == link->x2 )
	    {
	        for( y = link->y1; y <= link->y2; y++ )
	        {
		    if( gplayer[y][link->x1] == -1 )
		    {
			gplayer[y][link->x1] = 0;
			tmplayer[y][link->x1] = 0;
		    }
		}
	    }
	    else
	    {
	        for( x = link->x1; x <= link->x2; x++ )
	        {
		    if( gplayer[link->y1][x] == -1 )
		    {
			gplayer[link->y1][x] = 0;
			tmplayer[link->y1][x] = 0;
		    }
		}
	    }
	}
	/*
	 *  return tmplist
	 */
	/*  delete at the beginning of findpath
	while( (link = net_arrayG[i].tmplist) != NULL )
	{
	    net_arrayG[i].tmplist = net_arrayG[i].tmplist->netnext;
	    S_retlink( link );
	}
	*/
    }
    return( NO );
}

S_pushsearchq( totalcost, x, y, group, layer)
int totalcost,  /* cost to reach (x, y) */
    x,
    y,          /* coordinates */
    group,
    layer;
{
    int keycost;
    SEARCHPTR newq;
    SEARCHPTR S_getsearchq();

    /*  push in the queue  */
    keycost = totalcost % MODCOST;
    newq = S_getsearchq();
    newq->x = x;
    newq->y = y;
    newq->group = group;
    newq->layer = layer;
    newq->next = searchq[keycost];
    searchq[keycost] = newq;
}

/*
 *   clean the trace
 */
S_cleantrace()
{

#ifdef THEOLDWAY
    PINPTR tpin;
    int	**hcomp,
	**vcomp;
    int i;
    int x,
	y;

    hcomp = channel->hcomp;
    vcomp = channel->vcomp;
    for( x = 1; x <= num_colsG; x++ )
    {
	for( y = 1; y <= num_rowsG; y++ )
	{
	    if( hlayerG[y][x] < 0 /* && playerhG[y][x] == 0 */)
	    {
		hlayerG[y][x] = 0;
	    }
	    hcomp[y][x] = 0;
	    if( vlayerG[y][x] < 0 /* && playervG[y][x] == 0 */)
	    {
		vlayerG[y][x] = 0;
	    }
	    vcomp[y][x] = 0;
	}
    }

    /*
     *  mark all pins
     */
    for( i = 1; i <= num_netsG; i++ )
    {
	for( tpin = net_arrayG[i].pin; tpin != NULL; tpin = tpin->next )
	{
	    if( tpin->layer == HORIZ )
		hlayerG[tpin->y][tpin->x] = i;
	    if( tpin->layer == VERT )
		vlayerG[tpin->y][tpin->x] = i;
	}
    }
}
#else
    register PINPTR tpin;
    int	**hcomp,
	**vcomp;
    int i;
    int x,
	y;
    register int *hlayX ;
    register int *vlayX ;
    register int *hcompX ;
    register int *vcompX ;

    /* rewritten for speedup WPS */
    hcomp = channelG->hcomp;
    vcomp = channelG->vcomp;
    for( x = 1; x <= num_rowsG; x++ )
    {
	hlayX = hlayerG[x] ;
	vlayX = vlayerG[x] ;
	hcompX = hcomp[x] ;
	vcompX = vcomp[x] ;

	for( y = 1; y <= num_colsG; y++ )
	{
	    if( hlayX[y] < 0 /* && playerhG[x][y] == 0 */)
	    {
		hlayX[y] = 0;
	    }
	    hcompX[y] = 0;
	    if( vlayX[y] < 0 /* && playervG[x][y] == 0 */)
	    {
		vlayX[y] = 0;
	    }
	    vcompX[y] = 0;
	}
    }

    /*
     *  mark all pins
     */
    for( i = 1; i <= num_netsG; i++ )
    {
	for( tpin = net_arrayG[i].pin; tpin != (PINPTR)NULL; tpin = tpin->next )
	{
	    if( tpin->layer == HORIZ )
		hlayerG[tpin->y][tpin->x] = i;
	    if( tpin->layer == VERT )
		vlayerG[tpin->y][tpin->x] = i;
	}
    }
}
#endif
	    

/*
 *  backtrack the path one step
 */
S_backnext( xp, yp, group, costp, layer, net )
int *xp,
    *yp;
int group;
int *costp;
int layer,
    net;
{
    int **flayer,
	**slayer,
	**fgp,
	**sgp;
    int hcost,
	vcost;
    int newx,
	newy;
     PIN_LISTPTR p;

/*
printf("back : x= %d, y=%d, net= %d group=%d %s cost=%d\n", *xp, *yp,
net, group, (layer == HORIZ ? "H" : "V"), *costp );
 */
    if( layer == HORIZ )
    /*
     *  set environment
     */
    {
	flayer = hlayerG;
	slayer = vlayerG;
	fgp = channelG->hcomp;
	sgp = channelG->vcomp;
	hcost = HCOST1;
	vcost = VCOST2;
    }
    else
    {
	slayer = hlayerG;
	flayer = vlayerG;
	sgp = channelG->hcomp;
	fgp = channelG->vcomp;
	hcost = HCOST2;
	vcost = VCOST1;
    }
    if( fgp[*yp][*xp] == group && flayer[*yp][*xp] == net )
    {
	return( NO );  /* finished at a link: no more path */
    }
#ifdef WDEBUG
    else if( fgp[*yp][*xp] == group && flayer[*yp][*xp] == -1 &&
	(playerhG[*yp][*xp] == net || playervG[*yp][*xp] == net) )
    {
	return( NO );  /* finished at a pin: no more path */
    }
#endif
    /*
     *  On HORIZ layer check HORIZ direction first
     *  Else VERT first
     */
    if( layer == HORIZ )
    {
        if( fgp[*yp][(newx = *xp + 1)] == group &&
	      flayer[*yp][newx] == net )
        {
	    *xp = newx;
	    (*costp) -= hcost;
	    return( HORIZ );
        }
        else if( fgp[*yp][(newx = *xp - 1)] == group &&
	      flayer[*yp][newx] == net )
        {
	    *xp = newx;
	    (*costp) -= hcost;
	    return( HORIZ );
        }
        else if( fgp[(newy = *yp + 1)][*xp] == group &&
	      flayer[newy][*xp] == net )
        {
	    *yp = newy;
	    (*costp) -= vcost;
	    return( VERT );
        }
        else if( fgp[(newy = *yp - 1)][*xp] == group &&
	      flayer[newy][*xp] == net )
        {
	    *yp = newy;
	    (*costp) -= vcost;
	    return( VERT );
        }
        else if( sgp[*yp][*xp] == group &&
	      slayer[*yp][*xp] == net )
	{			/* try passing thru to another level */
	    for(p=layer3G[*xp]; p != (PIN_LISTPTR)NULL ; p=p->next ) {
	      if( p->pin->y==*yp )  /* no vias allowed on .5 layer pins */
	        break; 
	      }
	    if ( p == (PIN_LISTPTR)NULL ) {	/* p=NULL means ok to passthru */
	      (*costp) -= SWCOST;
	       return( SWITCH );
	       }
        }

        if( fgp[*yp][(newx = *xp + 1)] == group &&
	      flayer[*yp][newx] == - *costp + hcost )
        {
	    *xp = newx;
	    (*costp) -= hcost;
	    return( HORIZ );
        }
        else if( fgp[*yp][(newx = *xp - 1)] == group &&
	      flayer[*yp][newx] == - *costp + hcost )
        {
	    *xp = newx;
	    (*costp) -= hcost;
	    return( HORIZ );
        }
        else if( fgp[(newy = *yp + 1)][*xp] == group &&
	      flayer[newy][*xp] == - *costp + vcost )
        {
	    *yp = newy;
	    (*costp) -= vcost;
	    return( VERT );
        }
        else if( fgp[(newy = *yp - 1)][*xp] == group &&
	      flayer[newy][*xp] == - *costp + vcost )
        {
	    *yp = newy;
	    (*costp) -= vcost;
	    return( VERT );
        }
    }
    else /* VERT first */
    {
        if( fgp[(newy = *yp + 1)][*xp] == group &&
	      flayer[newy][*xp] == net )
        {
	    *yp = newy;
	    (*costp) -= vcost;
	    return( VERT );
        }
        else if( fgp[(newy = *yp - 1)][*xp] == group &&
	      flayer[newy][*xp] == net )
        {
	    *yp = newy;
	    (*costp) -= vcost;
	    return( VERT );
        }
        else if( fgp[*yp][(newx = *xp + 1)] == group &&
	      flayer[*yp][newx] == net )
        {
	    *xp = newx;
	    (*costp) -= hcost;
	    return( HORIZ );
        }
        else if( fgp[*yp][(newx = *xp - 1)] == group &&
	      flayer[*yp][newx] == net )
        {
	    *xp = newx;
	    (*costp) -= hcost;
	    return( HORIZ );
        }
        else if( sgp[*yp][*xp] == group &&
	      slayer[*yp][*xp] == net )
	{			/* try passing thru to another level */
	    for(p=layer3G[*xp]; p != (PIN_LISTPTR)NULL ; p=p->next ) {
	      if( p->pin->y==*yp )  /* no vias allowed on .5 layer pins */
	        break; 
	      }
	    if ( p == (PIN_LISTPTR)NULL ) {	/* p=NULL means ok to passthru */
	      (*costp) -= SWCOST;
	      return( SWITCH );
	      }
        }

        if( fgp[(newy = *yp + 1)][*xp] == group &&
	      flayer[newy][*xp] == - *costp + vcost )
        {
	    *yp = newy;
	    (*costp) -= vcost;
	    return( VERT );
        }
        else if( fgp[(newy = *yp - 1)][*xp] == group &&
	      flayer[newy][*xp] == - *costp + vcost )
        {
	    *yp = newy;
	    (*costp) -= vcost;
	    return( VERT );
        }
        else if( fgp[*yp][(newx = *xp + 1)] == group &&
	      flayer[*yp][newx] == - *costp + hcost )
        {
	    *xp = newx;
	    (*costp) -= hcost;
	    return( HORIZ );
        }
        else if( fgp[*yp][(newx = *xp - 1)] == group &&
	      flayer[*yp][newx] == - *costp + hcost )
        {
	    *xp = newx;
	    (*costp) -= hcost;
	    return( HORIZ );
        }
    }
    if( sgp[*yp][*xp] == group &&
	slayer[*yp][*xp] == - *costp + SWCOST )
    {			/* try passing thru to another level */
	for(p=layer3G[*xp]; p != (PIN_LISTPTR)NULL ; p=p->next ) {
	  if( p->pin->y==*yp )  /* no vias allowed on .5 layer pins */
	    break; 
	    }
	if ( p == (PIN_LISTPTR)NULL ) {		/* p=NULL means ok to passthru */
	  (*costp) -= SWCOST;
	  return( SWITCH );
	  }
    }
    else
    {
print_debug ("backnext failed", "horiz", channelG->horiz_layer, num_rowsG, num_colsG, num_netsG);
print_debug ("backnext failed", "vert", channelG->vert_layer, num_rowsG, num_colsG, num_netsG);
print_debug ("backnext failed", "hcomp", channelG->hcomp, num_rowsG, num_colsG, num_netsG);
print_debug ("backnext failed", "vcomp", channelG->vcomp, num_rowsG, num_colsG, num_netsG);
	S_dumppath( net );
	S_output_routing() ;
	YexitPgm( 136 );
    }
}


/*
 *  clean up seachq
 */
S_cleansearchq()
{
    int count;
    SEARCHPTR tmpq;

    for( count = 0; count < MODCOST; count++ )
    {
	while( (tmpq = searchq[count]) != (SEARCHPTR)NULL )
	{
	    searchq[count] = tmpq->next;
	    S_retsearchq( tmpq );
	}
    }
}
