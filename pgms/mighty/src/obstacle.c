#ifndef lint
static char SccsId[] = "@(#) obstacle.c version 6.1 6/19/90" ;
#endif

#include "mighty.h"

#define LIMSEARCH 5

int
S_obstacle(net, x1, y1, x2, y2)
int net;
int x1, y1, x2, y2;
/*
 *  If more than one pin is on obstacle, lead the pin(s)
 *  up to the free routing area where both layers are available
 *  for routing.
 */
{
    int done = NO;
    int S_leadpin();

    if( hlayerG[y1][x1] > num_netsG )
    {
	if( S_leadpin( net, vlayerG, hlayerG, x1, y1, playervG, playerhG) )
	    done = YES;
    }
    else if( vlayerG[y1][x1] > num_netsG )
    {
	if( S_leadpin( net, hlayerG, vlayerG, x1, y1, playerhG, playervG) )
	    done = YES;
    }
    if( hlayerG[y2][x2] > num_netsG )
    {
	if( S_leadpin( net, vlayerG, hlayerG, x2, y2, playervG, playerhG) )
	    done = YES;
    }
    else if( vlayerG[y2][x2] > num_netsG )
    {
	if( S_leadpin( net, hlayerG, vlayerG, x2, y2, playerhG, playervG) )
	    done = YES;
    }

    if( done )
	return( YES );
    else
        return( NO );
}

int
S_leadpin( net, player, obslayer, x0, y0, ppin, obspin )
int net;
int **player;  /* layer on which there is a pin */
int **obslayer;  /* layer on which there is an obstacle */
int x0, y0;      /* pin position */
int **ppin;  /*  pin marks on player */
int **obspin;  /*  pin marks on obslayer  */
{
    int numlayer;
    int limit;  /* search limit  */
    int xp; /* used to search in positive direction */
    int xn; /* used to search in negative direction */
    int yp; /* used to search in positive direction */
    int yn; /* used to search in negative direction */
    void S_makelead();

    numlayer = player[0][0];
    limit = MIN( num_colsG, x0 + LIMSEARCH );
    for( xp = x0 + 1; xp <= limit; xp++ )
    {
	/*
	 *  If there is an obstacle or other pin, no hope
	 */
	if( player[y0][xp] == net || player[y0][xp] > num_netsG || ppin[y0][xp] > 0 )
	    xp = INFINITY;
	/*
	 *  If both layer is routable, break
	 */
	else if( obslayer[y0][xp] <= num_netsG && obspin[y0][xp] == 0 )
	    break;
	/*
	 *  Else continue search
	 */
    }
    limit = MAX( 1, x0 - LIMSEARCH );
    for( xn = x0 - 1; xn >= limit; xn-- )
    {
	/*
	 *  If there is an obstacle or other pin, no hope
	 */
	if( player[y0][xn] == net || player[y0][xn] > num_netsG || ppin[y0][xn] > 0 )
	    xn = MINFINITY;
	/*
	 *  If both layer is routable, break
	 */
	else if( obslayer[y0][xn] <= num_netsG && obspin[y0][xn] == 0 )
	    break;
	/*
	 *  Else continue search
	 */
    }

    limit = MIN( num_rowsG, y0 + LIMSEARCH );
    for( yp = y0 + 1; yp <= limit; yp++ )
    {
	/*
	 *  If there is an obstacle or other pin, no hope
	 */
	if( player[yp][x0] == net || player[yp][x0] > num_netsG || ppin[yp][x0] > 0 )
	    yp = INFINITY;
	/*
	 *  If both layer is routable, break
	 */
	else if( obslayer[yp][x0] <= num_netsG && obspin[yp][x0] == 0 )
	    break;
	/*
	 *  Else continue search
	 */
    }

    limit = MAX( 1, y0 - LIMSEARCH );
    for( yn = y0 - 1; yn >= limit; yn-- )
    {
	/*
	 *  If there is an obstacle or other pin, no hope
	 */
	if( player[yn][x0] == net || player[yn][x0] > num_netsG || ppin[yn][x0] > 0 )
	    yn = MINFINITY;
	/*
	 *  If both layer is routable, break
	 */
	else if( obslayer[yn][x0] <= num_netsG && obspin[yn][x0] == 0 )
	    break;
	/*
	 *  Else continue search
	 */
    }
    /*  Now find the best direction to lead the pin */
    if( xp - x0 < x0 - xn )
    {
        if( yp - y0 < y0 - yn )
	{
	    if( xp - x0 < yp - y0 && xp - x0 < LIMSEARCH )
	    {
	        S_makelead( net, x0 + 1, y0, xp, y0, numlayer );
	        return( YES );
	    }
	    else if( yp - y0 < LIMSEARCH )
	    {
	        S_makelead( net, x0, y0 + 1, x0, yp, numlayer );
		return( YES );
	    }
	}
	else
	{
	    if( xp - x0 < y0 - yn && xp - x0 < LIMSEARCH )
	    {
	        S_makelead( net, x0 + 1, y0, xp, y0, numlayer );
	        return( YES );
	    }
	    else if( y0 - yn < LIMSEARCH )
	    {
	        S_makelead( net, x0, yn, x0, y0 - 1, numlayer );
		return( YES );
	    }
	}
    }
    else
    {
        if( yp - y0 < y0 - yn )
	{
	    if( x0 - xn < yp - y0 && x0 - xn < LIMSEARCH )
	    {
	        S_makelead( net, xn, y0, x0 - 1, y0, numlayer );
	        return( YES );
	    }
	    else if( yp - y0 < LIMSEARCH )
	    {
	        S_makelead( net, x0, y0 + 1, x0, yp, numlayer );
		return( YES );
	    }
	}
	else
	{
	    if( x0 - xn < y0 - yn && x0 - xn < LIMSEARCH )
	    {
	        S_makelead( net, xn, y0, x0 - 1, y0, numlayer );
	        return( YES );
	    }
	    else if( y0 - yn < LIMSEARCH )
	    {
	        S_makelead( net, x0, yn, x0, y0 - 1, numlayer );
		return( YES );
	    }
	}
    }
    return( NO );
}

void
S_makelead( net, x1, y1, x2, y2, layer )
int net;
int x1, y1;
int x2, y2;
int layer;
{
    PINPTR pinptr;
    int tmp;
    PINPTR S_getpin();
    void S_addopt();

    S_addopt( layer, x1, y1, x2, y2 );
    if( x1 < x2 )
    {
	for( tmp = x1; tmp <= x2; tmp++ )
	{
	    pinptr = S_getpin();
	    pinptr->type = TEMP;
	    pinptr->next = net_arrayG[net].pin;
	    net_arrayG[net].pin = pinptr;
	    pinptr->layer = layer;
	    pinptr->x = tmp;
	    pinptr->y = y1;
	    /*
	    if( layer == HORIZ )
		playerhG[y1][tmp] = net;
	    else
		playervG[y1][tmp] = net;
	    */
	}
    }
    else
    {
	for( tmp = y1; tmp <= y2; tmp++ )
	{
	    pinptr = S_getpin();
	    pinptr->type = TEMP;
	    pinptr->next = net_arrayG[net].pin;
	    net_arrayG[net].pin = pinptr;
	    pinptr->layer = layer;
	    pinptr->x = x1;
	    pinptr->y = tmp;
	    /*
	    if( layer == HORIZ )
		playerhG[tmp][x1] = net;
	    else
		playervG[tmp][x1] = net;
	    */
	}
    }
}

