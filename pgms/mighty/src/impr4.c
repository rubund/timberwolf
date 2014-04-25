#ifndef lint
static char SccsId[] = "@(#) impr4.c version 6.4 10/14/90" ;
#endif

#include "mighty.h"

int OVERHEAD = 10;      /*  cost to use second closest pins */

#define PINCOST 80    /*  cost if used by pin connection */
#define NETCOST 30    /*  cost per net */
#define SWCOST 30     /*  cost of switching layer */
#define PTCOST 4      /*  cost of occupied grid by other net */
#define SLCOST 6      /*  cost in S_singlecost */
#define OPTLIMIT 500  /*  Limit of trial  */
#define OVERSEARCH 3  /*  Extention of the search region */

LINKPTR optlink = (LINKPTR)NULL;
int optcost;

/*****************************************************************
 *
 *  Last modified  4/9'87
 *    if can not be connected by a single line, return, in S_singlecost
 *
 *****************************************************************/

int S_powerimprove( net, boundImproveTrys )
int net;
int boundImproveTrys;		/* limit # of fruitless powerimproves() */
{
    LINKPTR tmplink;
    int i;
    int x1,
	y1,
	x2,
	y2;
    int group1 = 1;
    int group2 = 2;
    void S_findpins();
    int S_findpath();
    void S_optpath1();
    void S_optpath2();
    void S_optpath3();
    void S_optpath4();
    void S_debugdumpsched();
    void S_markoptpath();
    void S_cleantrace();
    void S_clearhistory();
    void S_delschedq();
    void S_schedule();
    void S_writelink();
    void S_dellink();
    void S_retlink();
    void S_adjustlink();
    int S_findcomponents();
    int S_findpath();
    void S_trytmppath();
    void S_powerimprove();
static int thisFindComponents;	/* current value of findcomponents() */
static int lastFindComponents;	/* last value of findcomponents() */
if (boundImproveTrys >= 10 ||
    boundImproveTrys <= 0)	/* Handle parm not passed case to   */ 
  boundImproveTrys=10;		/*   make deltas transparents       */

    printf("*** power improve called : net %d netName:%d\n", net,
	number_to_name(net) );

    /*
     *  Not to hit obstacle
     */
    net_arrayG[num_netsG+1].difficulty = INFINITY;

    /*
     *  find closest unconnected pins
     */
    /* no better 4/2'86
    if( net_arrayG[net].difficulty <= 100 ||
        net_arrayG[net].difficulty > 200 )
	S_findpins( net, &x1, &y1, &x2, &y2, 1, 2 );
    else
	S_secondpins( net, &x1, &y1, &x2, &y2, 1, 2, OVERHEAD );
    */
    S_findpins( net, &x1, &y1, &x2, &y2, 1, 2 );

    /*
     *  To use the map : If we do not erase, we may skip it
     */
    S_findpath( net, NO );
if( debugG ) {
printf("power improve : net %d, pins(%d, %d) (%d, %d)\n",
net, x1, y1, x2, y2 );
print_debug ("power", "horiz", channelG->horiz_layer, num_rowsG, num_colsG, num_netsG);
print_debug ("power", "vert", channelG->vert_layer, num_rowsG, num_colsG, num_netsG);
print_channel (channelG, num_rowsG, num_colsG, num_netsG);
}


    /*
     *  find optimal path between (x1, y1) and (x2, y2)
     */
    /* Following two variables are global, and can change
       in S_optpath? */
    optcost = OPTLIMIT;

    if( x1 == x2 )
        S_optpath1( net, x1, y1, x2, y2, group1, group2 );
    else if( y1 == y2 )
        S_optpath2( net, x1, y1, x2, y2, group1, group2 );
    else if( x1 < x2 && y1 < y2 )
        S_optpath3( net, x1, y1, x2, y2, group1, group2 );
    else if( x1 > x2 && y1 > y2 )
        S_optpath3( net, x2, y2, x1, y1, group2, group1 );
    else if( x1 < x2 )
        S_optpath4( net, x1, y1, x2, y2, group1, group2 );
    else
        S_optpath4( net, x2, y2, x1, y1, group2, group1 );

    /*
     *  If optcost is too high, exit
     */
    if( optcost >= OPTLIMIT )
    {
	/*  If obstacle was the problem and can be modified, continue */
	if( obstacleG != (LINKPTR)NULL && S_obstacle( net, x1, y1, x2, y2 ) )
	    goto POWER;

	/* report failure and exit */
	for( i = 1; i <= num_netsG; i++ )
	    if( net_arrayG[i].difficulty > 100 )
		printf(" net %d  diff %d\n", i, net_arrayG[i].difficulty );
print_debug ("power", "horiz", channelG->horiz_layer, num_rowsG, num_colsG, num_netsG);
print_debug ("power", "vert", channelG->vert_layer, num_rowsG, num_colsG, num_netsG);
print_debug ("power", "horiz", channelG->hcomp, num_rowsG, num_colsG, num_netsG);
print_debug ("power", "vert", channelG->vcomp, num_rowsG, num_colsG, num_netsG);
/*
print_channel (channelG, num_rowsG, num_colsG, num_netsG);
*/
        return(NO);               /* try route other nets anyway */
    }
    else
    {
/*
printf("power : optcost = %d\n", optcost );
*/
POWER :
	S_markoptpath( net );
	S_cleantrace();

	/*  Update difficulties  & Reschedule queue */
	for( i = 1; i <= num_netsG; i++ )
	{
	    if( net_arrayG[i].marked == YES )
	    {
/*
printf("power : marked net = %d\n", i);
*/
S_clearhistory( i );
	        (net_arrayG[i].difficulty) += NETCOST;
		S_delschedq( i );
		S_schedule( i, 0 );
		while( (tmplink = net_arrayG[i].path) != (LINKPTR)NULL )
		{
		    S_writelink( tmplink, 0 );
		    S_dellink( tmplink );
		}
		while( (tmplink = net_arrayG[i].tmplist) != (LINKPTR)NULL )
		{
		    net_arrayG[i].tmplist = tmplink->netnext;
		    S_retlink( tmplink );
		}
	    }
	}
	S_adjustlink( net );  /* 4/21'86 */
 	while ( (thisFindComponents=S_findcomponents(net)) > 1 ) 
 	{
 	    if( S_findpath( net, YES ) )
 	        S_trytmppath( net );
 	    else {	/* break infinite loop by checking improvement */
		if (thisFindComponents >= lastFindComponents) 
		  if (--boundImproveTrys <= 0) {	/* bound calls */
                    return(NO);               /* try route other nets anyway */
		  }
		lastFindComponents=thisFindComponents;
 		S_powerimprove( net, boundImproveTrys );
		}
 	}
	S_clearhistory( net );
    }
    return( YES );
}


S_optpath1( net, x1, y1, x2, y2, group1, group2 )
/*
 *   x1 == x2 : VERTical
 */
int net;
int x1,
    y1,
    x2,
    y2;
int group1,
    group2;
{
    int cost;
    int tmpx,
	tmpy;
    int low,
	high;
    void S_singlecost();
    int S_linecost();
    void S_resetoptlink();
    void S_addopt();

    /*  Order y1, y2  */
    if( y1 > y2 )
    {
	tmpy = y1;
	y1 = y2;
	y2 = tmpy;

	tmpy = group1;
	group1 = group2;
	group2 = tmpy;
    }

    /* Single line search */
    for( tmpx = 1; tmpx <= num_colsG; tmpx++ )
	S_singlecost( net, tmpx, y1, tmpx, y2, group1, group2 );

    /* Three line search */
    for( tmpx = 1; tmpx <= num_colsG; tmpx++ )
    {
	cost = S_linecost( VERT, net, tmpx, y1, tmpx, y2 );
	if( cost < optcost && tmpx != x1 )
	    cost += S_linecost( HORIZ, net, tmpx, y2, x1, y2 );
	if( cost < optcost && tmpx != x2 )
	    cost += S_linecost( HORIZ, net, tmpx, y1, x2, y1 );
	
	if( cost < optcost )
	{
	    S_resetoptlink();
	    optcost = cost;
/*
printf("power : optpath1 : %d\n", cost);
*/
	    S_addopt( HORIZ, tmpx, y1, x1, y1 );
	    S_addopt( HORIZ, tmpx, y2, x1, y2 );
	    S_addopt( VERT, tmpx, y1, tmpx, y2 );
	}
    }
}


S_optpath2( net, x1, y1, x2, y2, group1, group2 )
/*
 *   y1 == y2 : HORIZontal
 */
int net;
int x1,
    y1,
    x2,
    y2;
int group1,
    group2;
{
    int cost;
    int tmpx,
	tmpy;
    int low,
	high;
    void S_singlecost();
    int S_linecost();
    void S_resetoptlink();
    void S_addopt();

    /*  Order x1, x2  */
    if( x1 > x2 )
    {
	tmpx = x1;
	x1 = x2;
	x2 = tmpx;

	tmpy = group1;
	group1 = group2;
	group2 = tmpy;
    }

    /* Single line search */
    for( tmpy = 1; tmpy <= num_rowsG; tmpy++ )
	S_singlecost( net, x1, tmpy, x2, tmpy, group1, group2 );

    /* Three line search */
    for( tmpy = 1; tmpy <= num_rowsG; tmpy++ )
    {
	cost = S_linecost( HORIZ, net, x1, tmpy, x2, tmpy );
	/*  if not zero length  */
	if( cost < optcost && y1 != tmpy )
	    cost += S_linecost( VERT, net, x1, y1, x1, tmpy );
	if( cost < optcost && y2 != tmpy )
	    cost += S_linecost( VERT, net, x2, y2, x2, tmpy );
	
	if( cost < optcost )
	{
	    S_resetoptlink();
	    optcost = cost;
/*
printf("power : optpath2 : %d\n", cost);
*/
	    S_addopt( HORIZ, x1, tmpy, x2, tmpy );
	    S_addopt( VERT, x1, y1, x1, tmpy );
	    S_addopt( VERT, x2, y2, x2, tmpy );
	}
    }
}


S_optpath3( net, x1, y1, x2, y2, group1, group2 )
/*
 *  x1 < x2 && y1 < y2 
 */
int net;
int x1,
    y1,
    x2,
    y2;
int group1,
    group2;
{
    int cost;
    int tmpx,
	tmpy;
    int low,
	high;
    void S_singlecost();
    int S_linecost();
    void S_resetoptlink();
    void S_addopt();

    /* Single line search */
    for( tmpx = x1; tmpx <= x2; tmpx++ )
	S_singlecost( net, tmpx, y1, tmpx, y2, group1, group2 );

    for( tmpy = y1; tmpy <= y2; tmpy++ )
	S_singlecost( net, x1, tmpy, x2, tmpy, group1, group2 );

    /* Two line search */
    /*			|
     *		    ----|
     */
    cost = S_linecost( HORIZ, net, x1, y1, x2, y1 );
    if( cost < optcost )
	cost += S_linecost( VERT, net, x2, y1, x2, y2 );
    if( cost < optcost )
    {
	S_resetoptlink();
	optcost = cost;
/*
printf("power : optpath3 : %d\n", cost);
*/
	S_addopt( HORIZ, x1, y1, x2, y1 );
	S_addopt( VERT, x2, y1, x2, y2 );
    }

    /*		------
     *	        |
     */
    cost = S_linecost( HORIZ, net, x1, y2, x2, y2 );
    if( cost < optcost )
	cost += S_linecost( VERT, net, x1, y1, x1, y2 );
    if( cost < optcost )
    {
	S_resetoptlink();
	optcost = cost;
/*
printf("power : optpath3 : %d\n", cost);
*/
	S_addopt( HORIZ, x1, y2, x2, y2 );
	S_addopt( VERT, x1, y1, x1, y2 );
    }

    /* Three line search */
    /*		   |------
     *		   |
     *	       ____|
     */
    for( tmpx = x1 + 1; tmpx < x2; tmpx++ )
    {
	cost = S_linecost( HORIZ, net, tmpx, y1, x1, y1 );
	if( cost < optcost )
	    cost += S_linecost( HORIZ, net, tmpx, y2, x2, y2 );
	if( cost < optcost && y1 < y2 - 1 )
	    cost += S_linecost( VERT, net, tmpx, y1, tmpx, y2 );
	
	if( cost < optcost )
	{
	    S_resetoptlink();
	    optcost = cost;
/*
printf("power : optpath3 : %d\n", cost);
*/
	    S_addopt( HORIZ, tmpx, y1, x1, y1 );
	    S_addopt( HORIZ, tmpx, y2, x2, y2 );
	    S_addopt( VERT, tmpx, y1, tmpx, y2 );
	}
    }
    /*			|
     *		   |----|
     *	 	   |
     */
    for( tmpy = y1 + 1; tmpy < y2; tmpy++ )
    {
	cost = S_linecost( VERT, net, x1, y1, x1, tmpy );
	if( cost < optcost )
	    cost += S_linecost( VERT, net, x2, y2, x2, tmpy );
	if( cost < optcost && x1 < x2 - 1 )
	    cost += S_linecost( HORIZ, net, x1, tmpy, x2, tmpy );
	
	if( cost < optcost )
	{
	    S_resetoptlink();
	    optcost = cost;
/*
printf("power : optpath3 : %d\n", cost);
*/
	    S_addopt( HORIZ, x1, tmpy, x2, tmpy );
	    S_addopt( VERT, x1, y1, x1, tmpy );
	    S_addopt( VERT, x2, y2, x2, tmpy );
	}
    }
}


S_optpath4( net, x1, y1, x2, y2, group1, group2 )
/*
 *  x1 < x2 && y2 < y1 
 */
int net;
int x1,
    y1,
    x2,
    y2;
int group1,
    group2;
{
    int cost;
    int tmpx,
	tmpy;
    int low,
	high;
    void S_singlecost();
    int S_linecost();
    void S_resetoptlink();
    void S_addopt();

    /* Single line search */
    for( tmpx = x1; tmpx <= x2; tmpx++ )
	S_singlecost( net, tmpx, y2, tmpx, y1, group2, group1 ); /* y2 < y1 */

    for( tmpy = y1; tmpy <= y2; tmpy++ )
	S_singlecost( net, x1, tmpy, x2, tmpy, group1, group2 );

    /* Two line search */
    /*	       ----|
     *		   |
     */
    cost = S_linecost( HORIZ, net, x1, y1, x2, y1 );
    if( cost < optcost )
	cost += S_linecost( VERT, net, x2, y2, x2, y1 );
    if( cost < optcost )
    {
	S_resetoptlink();
	optcost = cost;
/*
printf("power : optpath4 : %d\n", cost);
*/
	S_addopt( HORIZ, x1, y1, x2, y1 );
	S_addopt( VERT, x2, y2, x2, y1 );
    }

    /*		|
     *	        |
     *	        --------
     */
    cost = S_linecost( HORIZ, net, x1, y2, x2, y2 );
    if( cost < optcost )
	cost += S_linecost( VERT, net, x1, y1, x1, y2 );
    if( cost < optcost )
    {
	S_resetoptlink();
	optcost = cost;
/*
printf("power : optpath4 : %d\n", cost);
*/
	S_addopt( HORIZ, x1, y2, x2, y2 );
	S_addopt( VERT, x1, y1, x1, y2 );
    }

    /* Three line search */
    /*	       ----|
     *		   |
     *	           |-----
     */
    for( tmpx = x1 + 1; tmpx < x2; tmpx++ )
    {
	cost = S_linecost( HORIZ, net, tmpx, y1, x1, y1 );
	if( cost < optcost )
	    cost += S_linecost( HORIZ, net, tmpx, y2, x2, y2 );
	if( cost < optcost && y2 < y1 - 1 )
	    cost += S_linecost( VERT, net, tmpx, y1, tmpx, y2 );
	
	if( cost < optcost )
	{
	    S_resetoptlink();
	    optcost = cost;
/*
printf("power : optpath4 : %d\n", cost);
*/
	    S_addopt( HORIZ, tmpx, y1, x1, y1 );
	    S_addopt( HORIZ, tmpx, y2, x2, y2 );
	    S_addopt( VERT, tmpx, y1, tmpx, y2 );
	}
    }
    /*		   |
     *		   |----|
     *	 	        |
     */
    for( tmpy = y2 + 1; tmpy < y1; tmpy++ )
    {
	    cost = S_linecost( VERT, net, x1, y1, x1, tmpy );
	if( cost < optcost )
	    cost += S_linecost( VERT, net, x2, y2, x2, tmpy );
	if( cost < optcost && x1 < x2 - 1 )
	    cost += S_linecost( HORIZ, net, x1, tmpy, x2, tmpy );
	
	if( cost < optcost )
	{
	    S_resetoptlink();
	    optcost = cost;
/*
printf("power : optpath4 : %d\n", cost);
*/
	    S_addopt( HORIZ, x1, tmpy, x2, tmpy );
	    S_addopt( VERT, x1, y1, x1, tmpy );
	    S_addopt( VERT, x2, y2, x2, tmpy );
	}
    }
}


S_resetmarked()
{
    int i;

    for( i = 1; i <= num_netsG; i++ )
    {
	net_arrayG[i].marked = NO;
    }

    /*
     *  To avoid obstacles, reset num_netsG + 1
     */
    net_arrayG[num_netsG+1].marked = NO;
}


S_resetoptlink()
{
    LINKPTR tmplink;
    void S_retlink();

    while( (tmplink = optlink) != (LINKPTR)NULL )
    {
	optlink = optlink->netnext;
	S_retlink( tmplink );
    }
}


S_addopt( layer, x1, y1, x2, y2 )
int layer;  /*  which layer  */
int x1,
    x2,
    y1,
    y2;  /*  two end points,  x1 <= x2, y1 <= y2  */
{
    LINKPTR link;
    int tmp;
    LINKPTR S_getlink();

    /*
     *  Order x1 and x2, y1, y2
     */
    if( x1 > x2 )
    {
	tmp = x1;
	x1 = x2;
	x2 = tmp;
    }
    else if( y1 > y2 )
    {
	tmp = y1;
	y1 = y2;
	y2 = tmp;
    }
    /*
     *  add a link structure on the linklayer
     */
/*
printf("addopt called %s, (%d, %d), (%d,%d)\n",
    (layer == HORIZ ? "H" : "V"), x1, y1, x2, y2 );
*/
    link = S_getlink();
    link->x1 = x1;
    link->y1 = y1;
    link->x2 = x2;
    link->y2 = y2;
    link->layer = layer;
    link->p.user_given = FALSE;
    /*
     *  add a pointer list on the net
     */
    link->netnext = optlink;
    optlink = link;
}


S_singlecost( net, ox1, oy1, ox2, oy2, group1, group2 )
/*
 *  find min cost single line path
 *  ox1, ox2 ; oy1, oy2 already ordered
 */
int net;
int ox1,
    oy1,
    ox2,
    oy2;
int group1,
    group2;
{
    int x1,
        y1,
	x2,
	y2;
    int xgp1,
	ygp1,
	xgp2,
	ygp2;
    int tmpx,
	tmpy;
    int tmpcost;
    int **hcomp,
	**vcomp;
    int cost;   /* temporary cost */
    int cost1 = INFINITY;
    int cost2 = INFINITY;
    int S_linecost();
    void S_resetoptlink();
    void S_addopt();

    xgp1 = ox1;
    ygp1 = oy1;
    xgp2 = ox2;
    ygp2 = oy2;
    hcomp = channelG->hcomp;
    vcomp = channelG->vcomp;

    if( ox1 == ox2 )  /* VERT */
    {
        /*  search bound */
	x1 = x2 = ox1;
        y1 = MAX( 1, oy1 - OVERSEARCH );
        y2 = MIN( num_rowsG, oy2 + OVERSEARCH );

	for( tmpy = y1; tmpy <= y2; tmpy++ )
	{
	    if( vcomp[tmpy][x1] == group1 )
	    {
		if( vlayerG[tmpy][x1] == net &&
		   (cost = SLCOST * ABS(oy2 - tmpy)) < cost1 )
		{
		    cost1 = cost;
		    ygp1 = tmpy;
		}
	        else if( (cost = -vlayerG[tmpy][x1] + SLCOST * ABS(oy2 - tmpy)) < cost1 )
		{
		    cost1 = cost;
		    ygp1 = tmpy;
		}
	    }
	    else if( hcomp[tmpy][x1] == group1 )
	    {
		if( hlayerG[tmpy][x1] == net &&
		   (cost = SLCOST * ABS(oy2 - tmpy) + SWCOST) < cost1 )
		    {
			cost1 = cost;
			ygp1 = tmpy;
		    }
	        else if( (cost = -hlayerG[tmpy][x1] + SLCOST * ABS(oy2 - tmpy) + SWCOST) < cost1 )
		{
		    cost1 = cost;
		    ygp1 = tmpy;
		}
	    }
	    if( vcomp[tmpy][x2] == group2 )
	    {
		if( vlayerG[tmpy][x2] == net &&
		   (cost = SLCOST * ABS(oy1 - tmpy)) < cost2 )
		{
		    cost2 = cost;
		    ygp2 = tmpy;
		}
	        else if( (cost = -vlayerG[tmpy][x2] + SLCOST * ABS(oy1 - tmpy)) < cost2 )
		{
		    cost2 = cost;
		    ygp2 = tmpy;
		}
	    }
	    else if( hcomp[tmpy][x2] == group2 )
	    {
		if( hlayerG[tmpy][x2] == net &&
		   (cost = SLCOST * ABS(oy1 - tmpy) + SWCOST) < cost2 )
		    {
			cost2 = cost;
			ygp2 = tmpy;
		    }
	        else if( (cost = -hlayerG[tmpy][x2] + SLCOST * ABS(oy1 - tmpy) + SWCOST) < cost2 )
		{
		    cost2 = cost;
		    ygp2 = tmpy;
		}
	    }
	}

	cost1 += - SLCOST * ABS( oy2 - ygp1 );
	cost2 += - SLCOST * ABS( oy1 - ygp2 );
	if( cost1 + cost2 >= optcost )
	    return;  /* FAIL */
	tmpcost = S_linecost( VERT, net, x1, ygp1, x2, ygp2 ) + cost1 + cost2;
	if( tmpcost < optcost )
	{
	    S_resetoptlink();
	    optcost = tmpcost;
/*
printf("power : optpath0 : %d\n", tmpcost);
*/
	    S_addopt( VERT, x1, ygp1, x2, ygp2 );
	}
    }
    else  /* HORIZ */
    {
        /*  search bound */
	y1 = y2 = oy1;
        x1 = MAX( 1, ox1 - OVERSEARCH );
        x2 = MIN( num_colsG, ox2 + OVERSEARCH );

	for( tmpx = x1; tmpx <= x2; tmpx++ )
	{
	    if( hcomp[y1][tmpx] == group1 )
	    {
		if( hlayerG[y1][tmpx] == net &&
		   (cost = SLCOST * ABS(ox2 - tmpx)) < cost1 )
		{
		    cost1 = cost;
		    xgp1 = tmpx;
		}
	        else if( (cost = -hlayerG[y1][tmpx] + SLCOST * ABS(ox2 - tmpx)) < cost1 )
		{
		    cost1 = cost;
		    xgp1 = tmpx;
		}
	    }
	    else if( vcomp[y1][tmpx] == group1 )
	    {
		if( vlayerG[y1][tmpx] == net &&
		   (cost = SLCOST * ABS(ox2 - tmpx) + SWCOST) < cost1 )
		{
		    cost1 = cost;
		    xgp1 = tmpx;
		}
	        else if( (cost = -vlayerG[y1][tmpx] + SLCOST * ABS(ox2 - tmpx) + SWCOST ) < cost1 )
		{
		    cost1 = cost;
		    xgp1 = tmpx;
		}
	    }
	    if( hcomp[y2][tmpx] == group2 )
	    {
		if( hlayerG[y2][tmpx] == net &&
		   (cost = SLCOST * ABS(ox1 - tmpx)) < cost2 )
		{
		    cost2 = cost;
		    xgp2 = tmpx;
		}
	        else if( (cost = -hlayerG[y2][tmpx] + SLCOST * ABS(ox1 - tmpx)) < cost2 )
		{
		    cost2 = cost;
		    xgp2 = tmpx;
		}
	    }
	    else if( vcomp[y2][tmpx] == group2 )
	    {
		if( vlayerG[y2][tmpx] == net &&
		   (cost = SLCOST * ABS(ox1 - tmpx) + SWCOST ) < cost2 )
		{
		    cost2 = cost;
		    xgp2 = tmpx;
		}
	        else if( (cost = -vlayerG[y2][tmpx] + SLCOST * ABS(ox1 - tmpx) + SWCOST ) < cost2 )
		{
		    cost2 = cost;
		    xgp2 = tmpx;
		}
	    }
	}

	cost1 += - SLCOST * ABS( ox2 - xgp1 );
	cost2 += - SLCOST * ABS( ox1 - xgp2 );
	if( cost1 + cost2 >= optcost )
	    return;  /* FAIL */
	tmpcost = S_linecost( VERT, net, xgp1, y1, xgp2, y2 ) + cost1 + cost2;
	if( tmpcost < optcost )
	{
	    S_resetoptlink();
	    optcost = tmpcost;
/*
printf("power : optpath0 : %d\n", tmpcost);
*/
	    S_addopt( VERT, xgp1, y1, xgp2, y2 );
	}
    }
}


int S_linecost( layer, net, x1, y1, x2, y2 )
int layer;  /*  which layer  */
int net;
int x1,
    y1,
    x2,
    y2;  /*  two end points  */
{
    int other;  /* other net */
    int **flayer;
    int cost = 0;
    int tmpx,
	tmpy;
    void S_resetmarked();

    /*  if zero length, zero cost  */
    if( x1 == x2 && y1 == y2 )
	return( cost );

    /*  Order the coordinates  */
    if( x1 > x2 )
    {
	tmpx = x1;
	x1 = x2;
	x2 = tmpx;
    }
    else if( y1 > y2 )
    {
	tmpy = y1;
	y1 = y2;
	y2 = tmpy;
    }

    if( layer == HORIZ )
	flayer = hlayerG;
    else
	flayer = vlayerG;

    /*
     *  can not block other pins
     */
    if( layer == HORIZ )
    {
	for( tmpx = x1; tmpx <= x2; tmpx++ )
	    if( playerhG[y1][tmpx] > 0 && playerhG[y1][tmpx] != net /*||
	        playervG[y1][tmpx] > 0 && playervG[y1][tmpx] != net */)
		return( INFINITY );
    }
    else
    {
	for( tmpy = y1; tmpy <= y2; tmpy++ )
	    if( /* playerhG[tmpy][x1] > 0 && playerhG[tmpy][x1] != net || */
	        playervG[tmpy][x1] > 0 && playervG[tmpy][x1] != net )
		return( INFINITY );
    }

    S_resetmarked();
    
    /*
     *  calculate cost of the line
     */
    if( x1 == x2 )  /* VERT */
    {
	for( tmpy = y1; tmpy <= y2; tmpy++ )
	{
	    if( (other = flayer[tmpy][x1]) > 0 && other != net )
	    {
		if( net_arrayG[other].marked == YES )
		    cost += PTCOST;
		else
		{
		    cost += NETCOST + net_arrayG[other].difficulty;
		    net_arrayG[other].marked = YES;
		}
	    }
	}
    }
    else  /* HORIZ */
    {
	for( tmpx = x1; tmpx <= x2; tmpx++ )
	{
	    if( (other = flayer[y1][tmpx]) > 0 && other != net )
	    {
		if( net_arrayG[other].marked == YES )
		    cost += PTCOST;
		else
		{
		    cost += NETCOST + net_arrayG[other].difficulty;
		    net_arrayG[other].marked = YES;
		}
	    }
	}
    }
    return( cost );
}


S_markoptpath( net )
int net;
/*
 *  Mark the nets in optpath
 */
{
    LINKPTR link;
    int **flayer;
    int other;  /* other net */
    int tmpx,
	tmpy;
    void S_resetmarked();
    void S_retlink();

    S_resetmarked();

    while( (link = optlink) != (LINKPTR)NULL )
    {
/*
printf("power : optlink (%d, %d) (%d, %d)\n", link->x1, link->y1,
link->x2, link->y2 );
*/
	if( link->layer == HORIZ )
	    flayer = hlayerG;
	else
	    flayer = vlayerG;

        if( link->x1 == link->x2 )  /* VERT */
        {
	    for( tmpy = link->y1; tmpy <= link->y2; tmpy++ )
	    {
	        if( (other = flayer[tmpy][link->x1]) > 0 && other != net )
		    net_arrayG[other].marked = YES;
	    }
        }
        else  /* HORIZ */
        {
	    for( tmpx = link->x1; tmpx <= link->x2; tmpx++ )
	    {
	        if( (other = flayer[link->y1][tmpx]) > 0 && other != net )
		    net_arrayG[other].marked = YES;
	    }
        }
        optlink = optlink->netnext;
        S_retlink( link );
    }
}


void S_findpins( net, xp1, yp1, xp2, yp2, gp1, gp2 )
/*
 *  find closest unconnected pins
 */
int net;
int *xp1,
    *yp1,
    *xp2,
    *yp2;
int gp1,
    gp2;  /* groups */
{
    PINPTR pin1,
	   pin2;
    int x1,
	y1,
	x2,
	y2;
    int dist = INFINITY;
    int S_findcomponents();
    /*
     *  find unconnected components
     */
    S_findcomponents( net );

    /*
     *  find closest unconnected pins ( among group 1 or 2 )
     */
    for( pin1 = net_arrayG[net].pin; pin1 != (PINPTR)NULL; pin1 = pin1->next )
    {
	if( pin1->group != gp1 )
    continue;
	x1 = pin1->x;
	y1 = pin1->y;

        for( pin2 = net_arrayG[net].pin; pin2 != (PINPTR)NULL; pin2 = pin2->next )
	{
	    if( pin2->group != gp2 )
	continue;
	    x2 = pin2->x;
	    y2 = pin2->y;

	    if( dist > ABS( x1 - x2 ) + ABS( y1 - y2 ) )
	    {
	        dist = ABS( x1 - x2 ) + ABS( y1 - y2 );
		*xp1 = x1;
		*xp2 = x2;
		*yp1 = y1;
		*yp2 = y2;
	    }
	}
    }
}


void S_secondpins( net, xp1, yp1, xp2, yp2, gp1, gp2, overhead )
/*
 *  find second closest unconnected pins
 */
int net;
int *xp1,
    *yp1,
    *xp2,
    *yp2;
int gp1,
    gp2; 	 /* groups */
int overhead;    /* Max allowable overhead to use 2nd closest */
{
    PINPTR pin1,
	   pin2;
    int x1,
	y1,
	x2,
	y2;
    int xs1,
	ys1,
	xs2,
	ys2;
    int distp = INFINITY;	/* primary distance */
    int dists = INFINITY;	/* secondary distance */
    int S_findcomponents();

    *xp1 = 0;
    *yp1 = 0;
    *xp2 = 0;
    *yp2 = 0;

    /*
     *  find unconnected components
     */
    S_findcomponents( net );

    /*
     *  find closest unconnected pins ( among group 1 or 2 )
     */
    for( pin1 = net_arrayG[net].pin; pin1 != (PINPTR)NULL; pin1 = pin1->next )
    {
	if( pin1->group != gp1 )
    continue;
	x1 = pin1->x;
	y1 = pin1->y;

        for( pin2 = net_arrayG[net].pin; pin2 != (PINPTR)NULL; pin2 = pin2->next )
	{
	    if( pin2->group != gp2 )
	continue;
	    x2 = pin2->x;
	    y2 = pin2->y;

	    if( distp > ABS( x1 - x2 ) + ABS( y1 - y2 ) )
	    {
		dists = distp;
		xs1 = *xp1;
		ys1 = *yp1;
		xs2 = *xp2;
		ys2 = *yp2;

	        distp = ABS( x1 - x2 ) + ABS( y1 - y2 );
		*xp1 = x1;
		*xp2 = x2;
		*yp1 = y1;
		*yp2 = y2;
	    }
	    else if( dists > ABS( x1 - x2 ) + ABS( y1 - y2 ) )
	    {
	        dists = ABS( x1 - x2 ) + ABS( y1 - y2 );
		xs1 = x1;
		xs2 = x2;
		ys1 = y1;
		ys2 = y2;
	    }
	}
        for( pin2 = net_arrayG[net].tmppin; pin2 != (PINPTR)NULL;
	     pin2 = pin2->next )
	{
	    if( pin2->group != gp2 )
	continue;
	    x2 = pin2->x;
	    y2 = pin2->y;

	    if( distp > ABS( x1 - x2 ) + ABS( y1 - y2 ) )
	    {
		dists = distp;
		xs1 = *xp1;
		ys1 = *yp1;
		xs2 = *xp2;
		ys2 = *yp2;

	        distp = ABS( x1 - x2 ) + ABS( y1 - y2 );
		*xp1 = x1;
		*xp2 = x2;
		*yp1 = y1;
		*yp2 = y2;
	    }
	    else if( dists > ABS( x1 - x2 ) + ABS( y1 - y2 ) )
	    {
	        dists = ABS( x1 - x2 ) + ABS( y1 - y2 );
		xs1 = x1;
		xs2 = x2;
		ys1 = y1;
		ys2 = y2;
	    }
	}
    }
    for( pin1 = net_arrayG[net].tmppin; pin1 != (PINPTR)NULL; pin1 = pin1->next )
    {
	if( pin1->group != gp1 )
    continue;
	x1 = pin1->x;
	y1 = pin1->y;

        for( pin2 = net_arrayG[net].pin; pin2 != (PINPTR)NULL;
	     pin2 = pin2->next )
	{
	    if( pin2->group != gp2 )
	continue;
	    x2 = pin2->x;
	    y2 = pin2->y;

	    if( distp > ABS( x1 - x2 ) + ABS( y1 - y2 ) )
	    {
		dists = distp;
		xs1 = *xp1;
		ys1 = *yp1;
		xs2 = *xp2;
		ys2 = *yp2;

	        distp = ABS( x1 - x2 ) + ABS( y1 - y2 );
		*xp1 = x1;
		*xp2 = x2;
		*yp1 = y1;
		*yp2 = y2;
	    }
	    else if( dists > ABS( x1 - x2 ) + ABS( y1 - y2 ) )
	    {
	        dists = ABS( x1 - x2 ) + ABS( y1 - y2 );
		xs1 = x1;
		xs2 = x2;
		ys1 = y1;
		ys2 = y2;
	    }
	}
        for( pin2 = net_arrayG[net].tmppin; pin2 != (PINPTR)NULL;
	     pin2 = pin2->next )
	{
	    if( pin2->group != gp2 )
	continue;
	    x2 = pin2->x;
	    y2 = pin2->y;

	    if( distp > ABS( x1 - x2 ) + ABS( y1 - y2 ) )
	    {
		dists = distp;
		xs1 = *xp1;
		ys1 = *yp1;
		xs2 = *xp2;
		ys2 = *yp2;

	        distp = ABS( x1 - x2 ) + ABS( y1 - y2 );
		*xp1 = x1;
		*xp2 = x2;
		*yp1 = y1;
		*yp2 = y2;
	    }
	    else if( dists > ABS( x1 - x2 ) + ABS( y1 - y2 ) )
	    {
	        dists = ABS( x1 - x2 ) + ABS( y1 - y2 );
		xs1 = x1;
		xs2 = x2;
		ys1 = y1;
		ys2 = y2;
	    }
	}
    }
    if( dists < distp + overhead && xs1 != 0 )
    {
	/*
	 *  return second closest
	 */
	*xp1 = xs1;
	*xp2 = xs2;
	*yp1 = ys1;
	*yp2 = ys2;
printf("Use second closest pins\n");
    }
}

