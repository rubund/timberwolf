#ifndef lint
static char SccsId[] = "@(#) impr1.c version 6.3 12/27/90" ;
#endif

#include "mighty.h"

extern SCHED_PTR schedheadG;
/********************************************************
 *  Last modified 4/9'87
 *    NULL schedheadG handling in S_delschedq( )
 *
 *
 ********************************************************/

/*
 *  if possible, push a segment by one unit, and return YES
 */
int S_unitpush( dir, x, y, net )
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
    int blocknet = 0;
    int S_unitpush();
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
	 *  there must not be a pin connected
	 */
	for( newx = x1; newx <= x2; newx++ )
	    if( playerhG[y][newx] == net || playervG[y][newx] == net )
	        return( NO );

	/*
	 *  check if there is available space
	 */
	if( dir == DOWN )
	    newy = y + 1;
	else
	    newy = y - 1;
	for( newx = x1; newx <= x2; newx++ )
	{
	    if( hlayerG[y][newx] == net &&
		hlayerG[newy][newx] != 0 && hlayerG[newy][newx] != net )
	    {
		if( blocknet == 0 )
		{
		    blockx = newx;
		    blocky = newy;
		    blocknet = hlayerG[newy][newx];
		}
		else if( blocknet != hlayerG[newy][newx] )
	    return( NO );
	    }
	    if( vlayerG[y][newx] == net &&
		vlayerG[newy][newx] != 0 && vlayerG[newy][newx] != net )
	    {
		if( blocknet == 0 )
		{
		    blockx = newx;
		    blocky = newy;
		    blocknet = vlayerG[newy][newx];
		}
		else if( blocknet != vlayerG[newy][newx] )
	    return( NO );
	    }
	}
	if( blocknet > num_netsG )
    return( NO );
	if(blocknet == 0 || S_unitpush( dir, blockx, blocky, blocknet ))
	{
	    S_unitmove( x1, y1, x2, y2, dir, net );
	    return( YES );
	}
	return( NO );
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
	 *  there must not be a pin connected
	 */
	for( newy = y1; newy <= y2; newy++ )
	    if( playerhG[newy][x] == net || playervG[newy][x] == net )
	        return( NO );

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
		    blockx = newx;
		    blocky = newy;
		    blocknet = hlayerG[newy][newx];
		}
		else if( blocknet != hlayerG[newy][newx] )
	    return( NO );
	    }
	    if( vlayerG[newy][x] == net &&
		vlayerG[newy][newx] != 0 && vlayerG[newy][newx] != net )
	    {
		if( blocknet == 0 )
		{
		    blockx = newx;
		    blocky = newy;
		    blocknet = vlayerG[newy][newx];
		}
		else if( blocknet != vlayerG[newy][newx] )
	    return( NO );
	    }
	}
	if( blocknet > num_netsG )
    return( NO );
	if(blocknet == 0 || S_unitpush( dir, blockx, blocky, blocknet ))
	{
	    S_unitmove( x1, y1, x2, y2, dir, net );
	    return( YES );
	}
	return( NO );
    }
}

/*
 *  push one unit by rerouting
 */
S_unitmove( x1, y1, x2, y2, dir, net )
int x1,
    y1,
    x2,
    y2;
int dir;
int net;
{
    LINKPTR link;
    int numcomp,
	numfloat,
	status;
    int x,
	y;
    void S_retlink();
    LINKPTR S_picklink();
    void S_addlink();
    void S_writelink();
    void S_dellink();
    void S_trytmppath();
    void S_dumppath();
    int S_findcomponents();
    int S_findpath();

    /*
     *  actual move
     */
    while( (link = net_arrayG[net].tmplist) != (LINKPTR)NULL )
    {
	net_arrayG[net].tmplist = link->netnext;
	S_retlink( link );
    }

    if( (link = S_picklink( x1, y1, net )) == (LINKPTR)NULL ||
	(link = S_picklink( x2, y2, net )) == (LINKPTR)NULL )
    {
print_debug ("impr1", "horiz", channelG->horiz_layer, num_rowsG, num_colsG, num_netsG);
print_debug ("impr1", "vert", channelG->vert_layer, num_rowsG, num_colsG, num_netsG);
YexitPgm( 29 );
    }

    if( dir == DOWN || dir == UP )
    {
        if( dir == DOWN )
	    y2++;
        else
	    y2--;

	for( x = x1; x <= x2; x++ )
	{
	    while( (link = S_picklink( x, y1, net )) != (LINKPTR)NULL )
	    {
		if( link->y1 == y1 )
		{
		    if( link->y2 == y1 )
		        S_addlink( link->layer, link->x1, y2, link->x2, y2, net );
		    else if( link->x1 != link->x2 || link->y2 != y2 )
		        S_addlink( link->layer, link->x1, y2, link->x2, link->y2, net );
		}
		else  /* link->y2 == y1 */
		{
		    if( link->x1 != link->x2 || link->y1 != y2 )
		        S_addlink( link->layer, link->x1, link->y1, link->x2, y2, net );
		}
		S_writelink( link, 0 );
		S_dellink( link );
	    }
	}
    }
    else /* dir == LEFT || dir == RIGHT */
    {
        if( dir == RIGHT )
	    x2++;
        else
	    x2--;

	for( y = y1; y <= y2; y++ )
	{
	    while( (link = S_picklink( x1, y, net )) != (LINKPTR)NULL )
	    {
		if( link->x1 == x1 )
		{
		    if( link->x2 == x1 )
		        S_addlink( link->layer, x2, link->y1, x2, link->y2, net );
		    else if( link->y1 != link->y2 || link->x2 != x2 )
		        S_addlink( link->layer, x2, link->y1, link->x2, link->y2, net );
		}
		else  /* link->x2 == x1 */
		{
		    if( link->y1 != link->y2 || link->x1 != x2 )
		        S_addlink( link->layer, link->x1, link->y1, x2, link->y2, net );
		}
		S_writelink( link, 0 );
		S_dellink( link );
	    }
	}
    }
    for( link = net_arrayG[net].path; link != (LINKPTR)NULL; link = link->netnext)
	S_writelink( link, net );

    if( S_trytmppath( net ) == NO )
    {
print_debug ("impr1", "horiz", channelG->horiz_layer, num_rowsG, num_colsG, num_netsG);
print_debug ("impr1", "vert", channelG->vert_layer, num_rowsG, num_colsG, num_netsG);
	S_dumppath( net );
	return ;
    }
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
	    printf("findpath3 not possible - must reroute\n");
	}
    }
}

/*
 *  delete a job from schedule queue.
 */
S_delschedq( net )
int net;
{
    SCHED_PTR schedq ;
    SCHED_PTR prevq = (SCHED_PTR)NULL;
    LINKPTR link;
    void S_retschedq();

    if( schedheadG == (SCHED_PTR)NULL )
	return;

    for( schedq = schedheadG; schedq != (SCHED_PTR)NULL; schedq = schedq->next )
    {
	if( schedq->net == net )
	    break;
	prevq = schedq;
    }
    if( schedq ){
	if( schedq->net == net ){
	    if( prevq == (SCHED_PTR)NULL ){
		schedheadG = schedheadG->next;
	    } else {
		prevq->next = schedq->next;
	    }
	    S_retschedq( schedq );
	}
    }
}
