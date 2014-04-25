#ifndef lint
static char SccsId[] = "@(#) impr2.c version 6.1 6/19/90" ;
#endif

#include "mighty.h"

/*
 *  if possible, push a contact by unit distance, and return YES
 */
int S_pointpush( dir, x, y, net )
int dir;
int x,
    y;
int net;
{
    int x1,
	y1,
	x2,
	y2;
    int blockx,
	blocky,
	newx,
	newy;
    int blocklayer = 0;
    int blocknet = 0;
    int unitwidth = NO;
    int S_translink();
    int S_pointmove();
    int S_pointpush();
    void S_unitmove();

    x1 = x2 = x;
    y1 = y2 = y;

    if( dir == DOWN || dir == UP )
    {
	/*
	 *  find the interval to push
	 */
	while( hlayerG[y1][x1] == net || vlayerG[y1][x1] == net )
	    x1--;
	x1++;
	while( hlayerG[y2][x2] == net || vlayerG[y2][x2] == net )
	    x2++;
	x2--;
	/*
	 *  if possible, reduce the width to 1
	 *  if x2 - x1 == 2, there is ambiguity.
	 *  also no meaning dividing a small interval.
	 */
/*  4/10'86
	if( x2 - x1 >= 3 && (x1 == x -1 || x2 == x +1) )
	{
	    if( S_translink( dir, x, y, x1, x2, net ) )
	    {
	        unitwidth = YES;
		if( x1 == x -1 )
	            x2 = x;
		else
		    x1 = x;
	    }
	}
*/

	/*
	 *  there must not be a pin connected
	 */
	for( newx = x1; newx <= x2; newx++ )
	{
	    if( playerhG[y][newx] == net || playervG[y][newx] == net )
	        return( NO );
	}

	/*
	 *  check if there is available space
	 */
	if( dir == DOWN )
	    newy = y + 1;
	else
	    newy = y - 1;
	for( newx = x1; newx <= x2; newx++ )
	{
	    if( unitwidth == NO && hlayerG[y][newx] == net &&
		hlayerG[newy][newx] != 0 && hlayerG[newy][newx] != net )
	    {
		if( blocknet == 0 )
		{
		    blocklayer = HORIZ;
		    blockx = newx;
		    blocky = newy;
		    blocknet = hlayerG[newy][newx];
		}
		else
	    return( NO );
	    }
	    if( vlayerG[y][newx] == net &&
		vlayerG[newy][newx] != 0 && vlayerG[newy][newx] != net )
	    {
		if( blocknet == 0 )
		{
		    blocklayer = VERT;
		    blockx = newx;
		    blocky = newy;
		    blocknet = vlayerG[newy][newx];
		}
		else
	    return( NO );
	    }
	}
    }
    else /* LEFT or RIGHT */
    {
	/*
	 *  find the interval to push
	 */
	while( hlayerG[y1][x1] == net || vlayerG[y1][x1] == net )
	    y1--;
	y1++;
	while( hlayerG[y2][x2] == net || vlayerG[y2][x2] == net )
	    y2++;
	y2--;
	/*
	 *  if possible, reduce the width to 1
	 *  if y2 - y1 == 2, there is ambiguity.
	 *  also no meaning dividing a small interval.
	 */
/*
	if( y2 - y1 >= 3 && (y1 == y -1 || y2 == y +1) )
	{
	    if( S_translink( dir, x, y, y1, y2, net ) )
	    {
	        unitwidth = YES;
		if( y1 == y -1 )
	            y2 = y;
		else
		    y1 = y;
	    }
	}
*/

	/*
	 *  there must not be a pin connected
	 */
	for( newy = y1; newy <= y2; newy++ )
	{
	    if( playerhG[newy][x] == net || playervG[newy][x] == net )
	        return( NO );
	}

	/*
	 *  check if there is available space
	 */
	if( dir == RIGHT )
	    newx = x + 1;
	else
	    newx = x - 1;
	for( newy = y1; newy <= y2; newy++ )
	{
	    if( hlayerG[newy][x] == net &&
		hlayerG[newy][newx] != 0 && hlayerG[newy][newx] != net )
	    {
		if( blocknet == 0 )
		{
		    blocklayer = HORIZ;
		    blockx = newx;
		    blocky = newy;
		    blocknet = hlayerG[newy][newx];
		}
		else
	    return( NO );
	    }
	    if( unitwidth == NO && vlayerG[newy][x] == net &&
		vlayerG[newy][newx] != 0 && vlayerG[newy][newx] != net )
	    {
		if( blocknet == 0 )
		{
		    blocklayer = VERT;
		    blockx = newx;
		    blocky = newy;
		    blocknet = vlayerG[newy][newx];
		}
		else
	    return( NO );
	    }
	}
    }

    if( blocknet > num_netsG )
	return( NO );

    if(blocknet == 0 ||
	S_pointmove( dir, blockx, blocky, blocknet, blocklayer ) ||
	S_pointpush( dir, blockx, blocky, blocknet ))
    {
	S_unitmove( x1, y1, x2, y2, dir, net );
	return( YES );
    }
    return( NO );
}

/*
 *  push one unit by rerouting
 */
S_pointmove( dir, x, y, net, bklayer )
int dir;
int x,
    y;
int net;
int bklayer;
{
    LINKLISTPTR linklist;
    LINKPTR link;
    int origx,
	origy;
    int newx,
	newy;
    int numcomp,
	numfloat,
	status,
	priority;
    void S_retlink();
    void S_addlink();
    void S_dellink();
    int S_complayer();
    int S_trytmppath();
    void S_dumppath();
    void S_writelink();
    int S_findcomponents();
    int S_findpath();

    /*
     *  check possibility
     */
    newx = origx = x;
    newy = origy = y;
    if( dir == UP )
    {
	newy--;
	origy++;

        /*  If wrong dir link on the bklayer, can not push  */
        if( bklayer == HORIZ && (hlayerG[y][x+1] == net || hlayerG[y][x-1] == net )||
            bklayer == VERT && (vlayerG[y][x+1] == net || vlayerG[y][x-1] == net) )
	    return( NO );
    }
    else if ( dir == DOWN )
    {
	newy++;
	origy--;
        /*  If wrong dir link on the bklayer, can not push  */
        if( bklayer == HORIZ && (hlayerG[y][x+1] == net || hlayerG[y][x-1] == net )||
            bklayer == VERT && (vlayerG[y][x+1] == net || vlayerG[y][x-1] == net) )
	    return( NO );
    }
    else if ( dir == LEFT )
    {
	newx--;
	origx++;
        /*  If wrong dir link on the bklayer, can not push  */
        if( bklayer == HORIZ && (hlayerG[y+1][x] == net || hlayerG[y-1][x] == net )||
            bklayer == VERT && (vlayerG[y+1][x] == net || vlayerG[y-1][x] == net) )
	    return( NO );
    }
    else
    {
	newx++;
	origx--;
        /*  If wrong dir link on the bklayer, can not push  */
        if( bklayer == HORIZ && (hlayerG[y+1][x] == net || hlayerG[y-1][x] == net )||
            bklayer == VERT && (vlayerG[y+1][x] == net || vlayerG[y-1][x] == net) )
	    return( NO );
    }

    /*  Can not push a pin  */
    if( bklayer == HORIZ && playerhG[y][x] == net ||
        bklayer == VERT && playervG[y][x] == net )
	return( NO );

    /*  Can not push on both layers  */
    if( hlayerG[origy][origx] != 0 &&
        hlayerG[origy][origx] == vlayerG[origy][origx] )
	return( NO );

    /*  If no space, return NO  */
    if( hlayerG[y][x] != net ||
        vlayerG[y][x] != net ||
        hlayerG[newy][newx] != 0 && hlayerG[newy][newx] != net ||
        vlayerG[newy][newx] != 0 && vlayerG[newy][newx] != net )
	return( NO );

    /*
     *  actual move
     */
    while( (link = net_arrayG[net].tmplist) != (LINKPTR)NULL )
    {
        net_arrayG[net].tmplist = link->netnext;
        S_retlink( link );
    }

    for( linklist = linklayerG[y][x]; linklist != (LINKLISTPTR)NULL;
	linklist = linklist->next )
    {
	link = linklist->link;
	if( link->layer == bklayer && link->net == net )
	{
	    if( dir == DOWN && link->y2 > y )
	    {
		if( link->y2 > newy )
		    S_addlink( link->layer, link->x1, newy, link->x2, link->y2, net );
		S_addlink( S_complayer(link->layer), link->x1, y, link->x2, newy, net );
		S_dellink( link );
		break;
	    }
	    if( dir == UP && link->y1 < y )
	    {
		if( link->y1 < newy )
		    S_addlink( link->layer, link->x1, link->y1, link->x2, newy, net );
		S_addlink( S_complayer(link->layer), link->x1, y, link->x2, newy, net );
		S_dellink( link );
		break;
	    }
	    if( dir == RIGHT && link->x2 > x )
	    {
		if( link->x2 > newx )
		    S_addlink( link->layer, newx, link->y1, link->x2, link->y2, net );
		S_addlink( S_complayer(link->layer), x, link->y1, newx, link->y2, net );
		S_dellink( link );
		break;
	    }
	    if( dir == LEFT && link->x1 < x )
	    {
		if( link->x1 < newx )
		    S_addlink( link->layer, link->x1, link->y1, newx, link->y2, net );
		S_addlink( S_complayer(link->layer), x, link->y1, newx, link->y2, net );
		S_dellink( link );
		break;
	    }
	}
    }
    if( bklayer == HORIZ )
        hlayerG[y][x] = 0;
    else
        vlayerG[y][x] = 0;

    if( S_trytmppath( net ) == NO )
    {
	S_dumppath( net );
	return ;
    }
    for( link = net_arrayG[net].path; link != (LINKPTR)NULL; link = link->netnext)
	S_writelink( link, net );
    /*
     *  Set marked
     */
    net_arrayG[net].marked = YES;
    /*
     *  reschedule is done in S_improve
     *  LATER check any severe cost increase
     */
    if ( (numcomp = S_findcomponents( net )) > 1 )
    {
        if( S_findpath( net, YES ) == NO )
	{
	    printf("findpath2 not possible - must reroute\n");
	}
    }
    return( YES );
}
