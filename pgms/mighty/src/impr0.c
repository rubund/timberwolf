#ifndef lint
static char SccsId[] = "@(#) impr0.c version 6.3 12/27/90" ;
#endif

#include "mighty.h"

extern int NUMGOOD;
extern int OVERHEAD;

#define UTCOST 0
#define JPCOST 60
#define PTCOST 50

#define PTLIMIT 5

#define UTDOWN 1
#define UTUP   2
#define UTLEFT 3
#define UTRIGHT 4
#define JPDOWN  5
#define JPUP    6
#define JPLEFT  7
#define JPRIGHT 8
#define PTDOWN  9
#define PTUP    10
#define PTLEFT  11
#define PTRIGHT 12

/*
 * historyG[i][j] keeps the lowest possibe modification
 * of net j for net i
 */


int S_improve( net, status )
int net;
int status; /* result of findpath  */
{
    int newstatus;
    int	type = 0;	/* type of improvement */
    int numfloat = INFINITY;
    int S_comparepath( );
    /*
     *  Prepare for modifications
     *  cp path to oldpath
     *  mv tmplist to oldtmplist
     *  cp cost = oldcost
     */

    S_prepare();

    /*
     * try to improve
     */
    S_resetmarked();

    while ( (type = S_modify( net )) > 0 )
    {
/*
printf("mod net %d type %d\n", net, type );
*/
	S_findcomponents( net );
        if( (newstatus = S_findpath( net, YES )) == YES )
	{
            numfloat = S_schedpriority( net );
/*
printf("net %d : numfloat = %d\n", net, numfloat);
*/
	    /*
	     *  If new path is better, update the status
	     */
	    if( S_comparepath( net, type ) )
		status = newstatus;
	    if( status == YES && numfloat < NUMGOOD )
		break;
	}
    }
    S_chooseopt( net );
/*
if( debugG )
{
printf("impr0 returns %d\n", status);
print_debug ("modify", "horiz", channel->horiz_layer, num_rows, num_cols, num_netsG);
print_debug ("modify", "vert", channel->vert_layer, num_rows, num_cols, num_netsG);
S_dumppath( net );
}
*/
    return( status );
}

int S_modify( net )
int net;
{
    int x,
	y;
    int x1,
	y1,
	x2,
	y2;
    /*
     *  find closest unconnected pins of group 1 and 2
     */

    /* no better 4/2'86
    if( net_arrayG[net].difficulty <= 100 ||
        net_arrayG[net].difficulty > 200 )
	S_findpins( net, &x1, &y1, &x2, &y2, 1, 2 );
    else
	S_secondpins( net, &x1, &y1, &x2, &y2, 1, 2, OVERHEAD );
    */
    S_findpins( net, &x1, &y1, &x2, &y2, 1, 2 );

    if( vlayerG[y1][x1] == net && vlayerG[y2][x2] == net )
    {
        if( y1 <= y2 && S_tryunitdown( x1, y1, net ) )
	    return( UTDOWN );
        if( y2 <= y1 && S_tryunitdown( x2, y2, net ) )
	    return( UTDOWN );

        if( y2 <= y1 && S_tryunitup( x1, y1, net ) )
	    return( UTUP );
        if( y1 <= y2 && S_tryunitup( x2, y2, net ) )
	    return( UTUP );
    }

    if( hlayerG[y1][x1] == net && hlayerG[y2][x2] == net )
    {
	if( x2 <= x1 && S_tryunitleft( x1, y1, net ) )
	    return( UTLEFT );
	if( x1 <= x2 && S_tryunitleft( x2, y2, net ) )
	    return( UTLEFT );

	if( x1 <= x2 && S_tryunitright( x1, y1, net ) )
	    return( UTRIGHT );
	if( x2 <= x1 && S_tryunitright( x2, y2, net ) )
	    return( UTRIGHT );
    }

    /*
     *  unitpush failed, now try jump
     */
    if( vlayerG[y1][x1] == net && vlayerG[y2][x2] == net )
    {
        if( S_tryjumpdown( x1, y1, net ) )
	    return( JPDOWN );
        if( S_tryjumpdown( x2, y2, net ) )
	    return( JPDOWN );

        if( S_tryjumpup( x1, y1, net ) )
	    return( JPUP );
        if( S_tryjumpup( x2, y2, net ) )
	    return( JPUP );
    }

    if( hlayerG[y1][x1] == net && hlayerG[y2][x2] == net )
    {
	if( S_tryjumpleft( x1, y1, net ) )
	    return( JPLEFT );
	if( S_tryjumpleft( x2, y2, net ) )
	    return( JPLEFT );

	if( S_tryjumpright( x1, y1, net ) )
	    return( JPRIGHT );
	if( S_tryjumpright( x2, y2, net ) )
	    return( JPRIGHT );
    }

    /*
     *  point push
     */
    if( ABS( x1 - x2 ) <= PTLIMIT || ABS( y1 - y2 ) <= PTLIMIT )
    {
      if( vlayerG[y1][x1] == net && vlayerG[y2][x2] == net )
      {
	if( y1 < y2 && S_trypointvert( x1, y1, x2, y2, net ) )
	    return( PTUP );
	else if( y2 < y1 && S_trypointvert( x2, y2, x1, y1, net ) )
	    return( PTUP );
      }
      if( hlayerG[y1][x1] == net && hlayerG[y2][x2] == net )
      {
	if( x1 < x2 && S_trypointhoriz( x1, y1, x2, y2, net ) )
	    return( PTRIGHT );
	else if( x2 < x1 && S_trypointhoriz( x2, y2, x1, y1, net ) )
	    return( PTRIGHT );
      }
    }

    /*
     *  All the attempts failed
     */
    return( NO );
}

S_tryunitdown( x1, y1, net )
int x1,
    y1;
int net;
/*
 *  If looks helpful, call unitmove.
 *  Update historyG.
 */
{
    int ydown;
    int blocknet ;

    /*  find blocking net  */
    for( ydown = y1; ydown < num_rowsG; ydown++ )
    {
        if( vlayerG[ydown][x1] != 0 && vlayerG[ydown][x1] != net )
 	    break;
    }
    blocknet = vlayerG[ydown][x1];

    /*  If out of routing area, return NO  */
    if( blocknet == 0 || blocknet > num_netsG )
	return( NO );

    /*  Keep within channel and prevent oscill.  */
    if( historyG[net][blocknet] <= UTDOWN )
    {
	if( S_unitpush( DOWN, x1, ydown, blocknet ) )
	{
	    historyG[net][blocknet] = UTDOWN;
	    return( YES );
	}
	else
            historyG[net][blocknet] = UTDOWN + 1;
    }
    return( NO );
}

S_tryunitup( x1, y1, net )
int x1,
    y1;
int net;
/*
 *  If looks helpful, call unitmove.
 *  Update historyG.
 */
{
    int yup;
    int blocknet ;

    /*  find blocking net  */
    for( yup = y1; yup > 1; yup-- )
    {
        if( vlayerG[yup][x1] != 0 && vlayerG[yup][x1] != net )
 	    break;
    }
    blocknet = vlayerG[yup][x1];

    /*  If out of routing area, return NO  */
    if( blocknet == 0 || blocknet > num_netsG )
	return( NO );

    /*  Keep within channel and prevent oscill.  */
    if( historyG[net][blocknet] <= UTUP )
    {
	if( S_unitpush( UP, x1, yup, blocknet ) )
	{
	    historyG[net][blocknet] = UTUP;
	    return( YES );
	}
	else
            historyG[net][blocknet] = UTUP + 1;
    }
    return( NO );
}

S_tryunitleft( x1, y1, net )
int x1,
    y1;
int net;
/*
 *  If looks helpful, call unitmove.
 *  Update historyG.
 */
{
    int xleft;
    int blocknet ;

    /*  find blocking net  */
    for( xleft = x1; xleft > 1; xleft-- )
    {
        if( hlayerG[y1][xleft] != 0 && hlayerG[y1][xleft] != net )
 	    break;
    }
    blocknet = hlayerG[y1][xleft];

    /*  If out of routing area, return NO  */
    if( blocknet == 0 || blocknet > num_netsG )
	return( NO );

    /*  Keep within channel and prevent oscill.  */
    if( xleft > 1 && historyG[net][blocknet] <= UTLEFT )
    {
	if( S_unitpush( LEFT, xleft, y1, blocknet ) )
	{
	    historyG[net][blocknet] = UTLEFT;
	    return( YES );
	}
	else
	    historyG[net][blocknet] = UTLEFT + 1;
    }
    return( NO );
}

S_tryunitright( x1, y1, net )
int x1,
    y1;
int net;
/*
 *  If looks helpful, call unitmove.
 *  Update historyG.
 */
{
    int xright;
    int blocknet ;

    /*  find blocking net  */
    for( xright = x1; xright < num_colsG; xright++ )
    {
        if( hlayerG[y1][xright] != 0 && hlayerG[y1][xright] != net )
 	    break;
    }
    blocknet = hlayerG[y1][xright];

    /*  If out of routing area, return NO  */
    if( blocknet == 0 || blocknet > num_netsG )
	return( NO );


    /*  Keep within channel and prevent oscill.  */
    if( xright < num_colsG && historyG[net][blocknet] <= UTRIGHT )
    {
	if( S_unitpush( RIGHT, xright, y1, blocknet ) )
	{
	    historyG[net][blocknet] = UTRIGHT;
	    return( YES );
	}
	else
            historyG[net][blocknet] = UTRIGHT + 1;
    }
    return( NO );
}

S_tryjumpdown( x1, y1, net )
int x1,
    y1;
int net;
/*
 *  If looks helpful, call jumpmove.
 *  Update historyG.
 */
{
    int ydown;
    int blocknet ;

    /*  find blocking net  */
    for( ydown = y1; ydown < num_rowsG; ydown++ )
    {
        if( vlayerG[ydown][x1] != 0 && vlayerG[ydown][x1] != net )
 	    break;
    }
    blocknet = vlayerG[ydown][x1];

    /*  If out of routing area, return NO  */
    if( blocknet == 0 || blocknet > num_netsG )
	return( NO );


    /*  Keep within channel and prevent oscill.  */
    if( ydown < num_rowsG && historyG[net][blocknet] <= JPDOWN )
    {
	if( S_jumppush( DOWN, x1, ydown, blocknet ) )
	{
	    historyG[net][blocknet] = JPDOWN;
	    return( YES );
	}
    }
    if( historyG[net][blocknet] <= JPDOWN )
        historyG[net][blocknet] = JPDOWN + 1;
    return( NO );
}

S_tryjumpup( x1, y1, net )
int x1,
    y1;
int net;
/*
 *  If looks helpful, call jumpmove.
 *  Update historyG.
 */
{
    int yup;
    int blocknet ;

    /*  find blocking net  */
    for( yup = y1; yup > 1; yup-- )
    {
        if( vlayerG[yup][x1] != 0 && vlayerG[yup][x1] != net )
 	    break;
    }
    blocknet = vlayerG[yup][x1];

    /*  If out of routing area, return NO  */
    if( blocknet == 0 || blocknet > num_netsG )
	return( NO );

    /*  Keep within channel and prevent oscill.  */
    if( yup > 1 && historyG[net][blocknet] <= JPUP )
    {
	if( S_jumppush( UP, x1, yup, blocknet ) )
	{
	    historyG[net][blocknet] = JPUP;
	    return( YES );
	}
    }
    if( historyG[net][blocknet] <= JPUP )
    historyG[net][blocknet] = JPUP + 1;
    return( NO );
}

S_tryjumpleft( x1, y1, net )
int x1,
    y1;
int net;
/*
 *  If looks helpful, call jumpmove.
 *  Update historyG.
 */
{
    int xleft;
    int blocknet ;

    /*  find blocking net  */
    for( xleft = x1; xleft > 1; xleft-- )
    {
        if( hlayerG[y1][xleft] != 0 && hlayerG[y1][xleft] != net )
 	    break;
    }
    blocknet = hlayerG[y1][xleft];

    /*  If out of routing area, return NO  */
    if( blocknet == 0 || blocknet > num_netsG )
	return( NO );

    /*  Keep within channel and prevent oscill.  */
    if( xleft > 1 && historyG[net][blocknet] <= JPLEFT )
    {
	if( S_jumppush( LEFT, xleft, y1, blocknet ) )
	{
	    historyG[net][blocknet] = JPLEFT;
	    return( YES );
	}
    }
    if( historyG[net][blocknet] <= JPLEFT )
        historyG[net][blocknet] = JPLEFT + 1;
    return( NO );
}

S_tryjumpright( x1, y1, net )
int x1,
    y1;
int net;
/*
 *  If looks helpful, call jumpmove.
 *  Update historyG.
 */
{
    int xright;
    int blocknet ;

    /*  find blocking net  */
    for( xright = x1; xright < num_colsG; xright++ )
    {
        if( hlayerG[y1][xright] != 0 && hlayerG[y1][xright] != net )
 	    break;
    }
    blocknet = hlayerG[y1][xright];

    /*  If out of routing area, return NO  */
    if( blocknet == 0 || blocknet > num_netsG )
	return( NO );

    /*  Keep within channel and prevent oscill.  */
    if( xright < num_colsG && historyG[net][blocknet] <= JPRIGHT )
    {
	if( S_jumppush( RIGHT, xright, y1, blocknet ) )
	{
	    historyG[net][blocknet] = JPRIGHT;
	    return( YES );
	}
    }
    if( historyG[net][blocknet] <= JPRIGHT )
        historyG[net][blocknet] = JPRIGHT + 1;
    return( NO );
}

S_clearhistory( i )
int i;  /* net number */
/*
 *  clear historyG
 *  count = 0 is included to clear histacc and histtype - CANCEL
 */
{
    int count;

    for( count = 1; count <= num_netsG; count++ )
	historyG[count][i] = 0;
    for( count = 1; count <= num_netsG; count++ )
	historyG[i][count] = 0;
}

S_prepare()
/*
 *  Prepare for modifications
 *  cp path to oldpath
 *  mv tmplist to oldtmplist
 *  cp cost = oldcost
 */
{
    LINKPTR tlink,
	    newlink;
    int i;
    LINKPTR S_getlink();

    for( i = 1; i <= num_netsG; i++ )
    {
	while( (tlink = net_arrayG[i].oldpath) != (LINKPTR)NULL )
	{
	    net_arrayG[i].oldpath = tlink->netnext;
	    S_retlink( tlink );
	}
	while( (tlink = net_arrayG[i].oldtmplist) != (LINKPTR)NULL )
	{
	    net_arrayG[i].oldtmplist = tlink->netnext;
	    S_retlink( tlink );
	}
    }
    for( i = 1; i <= num_netsG; i++ )
    {
        if( net_arrayG[i].path != (LINKPTR)NULL )
        {
	    for( tlink = net_arrayG[i].path; tlink != (LINKPTR)NULL;
			tlink = tlink->netnext )
	    {
	        newlink = S_getlink();
		*(newlink) = *(tlink);
		newlink->netnext = net_arrayG[i].oldpath;
		net_arrayG[i].oldpath = newlink;
	    }
	}
        if( net_arrayG[i].tmplist != (LINKPTR)NULL )
        {
	    net_arrayG[i].oldtmplist = net_arrayG[i].tmplist;
	    net_arrayG[i].tmplist = (LINKPTR)NULL;
	}
	net_arrayG[i].oldcost = net_arrayG[i].cost;
    }
}

int
S_comparepath( net, type )
int net;
int type;  /* type of improvement */
/*
 *  compare oldpath's with current paths
 */
{
    LINKPTR tlink,
	    newlink;
    LINKPTR S_getlink();
    int i;
    int sumold = 0;
    int sumcost = 0;

    /*
     *  Find old and new cost
     */
    for( i = 1; i <= num_netsG; i++ )
    {
	if( net_arrayG[i].marked || i == net )
	{
	    sumold += net_arrayG[i].oldcost;
	    sumcost += net_arrayG[i].cost;
	}
    }
    if( type <= UTRIGHT )
	sumcost += UTCOST/2;
    else if ( type <= JPRIGHT )
	sumcost += JPCOST/2;
    else
	sumcost += PTCOST/2;

    if( sumcost >= sumold )
    {
	return( NO );
    }
    else
    {
    /*
     *  cp path to oldpath
     *  cp tmppath to oldtmppath
     *  cp cost = oldcost
     */
/*
print_debug ("opt", "horiz", channel->horiz_layer, num_rows, num_cols, num_netsG);
print_debug ("opt", "vert", channel->vert_layer, num_rows, num_cols, num_netsG);
*/
      for( i = 1; i <= num_netsG; i++ )
      {
	if( net_arrayG[i].marked == NO && i != net )
    continue;
        if( net_arrayG[i].path != (LINKPTR)NULL )
        {
	    while( (tlink = net_arrayG[i].oldpath) != (LINKPTR)NULL )
	    {
		net_arrayG[i].oldpath = tlink->netnext;
		S_retlink( tlink );
	    }
	    for( tlink = net_arrayG[i].path; tlink != (LINKPTR)NULL;
			tlink = tlink->netnext )
	    {
	        newlink = S_getlink();
		*(newlink) = *(tlink);
		newlink->netnext = net_arrayG[i].oldpath;
		net_arrayG[i].oldpath = newlink;
	    }
	}
        if( net_arrayG[i].tmplist != (LINKPTR)NULL )
        {
	    while( (tlink = net_arrayG[i].oldtmplist) != (LINKPTR)NULL )
	    {
		net_arrayG[i].oldtmplist = tlink->netnext;
		S_retlink( tlink );
	    }
	    net_arrayG[i].oldtmplist = net_arrayG[i].tmplist;
	    net_arrayG[i].tmplist = (LINKPTR)NULL;
	}
	net_arrayG[i].oldcost = net_arrayG[i].cost;
      }
    }
    return( YES );
}


S_chooseopt( net )
int net;
/*
 *  Reschedule
 *  Choose the best solution found so far.
 *  cp oldpath to path
 *  cp oldtmppath to tmppath
 *  cp oldcost = cost
 */
{
    LINKPTR tlink;
    int i;

    /*
     *  To make trytmppath successful, del precedes add link
     */
    for( i = 1; i <= num_netsG; i++ )
    {
	if( net_arrayG[i].marked == YES || i == net )
	{
	    while( (tlink = net_arrayG[i].tmplist) != (LINKPTR)NULL )
	    {
	        net_arrayG[i].tmplist = tlink->netnext;
	        S_retlink( tlink );
	    }
	    while( (tlink = net_arrayG[i].path) != (LINKPTR)NULL )
	    {
	        S_writelink( tlink, 0 );
	        S_dellink( tlink );
	    }
	}
    }
    for( i = 1; i <= num_netsG; i++ )
    {
	if( net_arrayG[i].marked == YES || i == net )
	{
	    if( net_arrayG[i].oldpath != (LINKPTR)NULL )
	    {
	        net_arrayG[i].tmplist = net_arrayG[i].oldpath;
	        net_arrayG[i].oldpath = (LINKPTR)NULL;
	        if( S_trytmppath( i ) == NO )
		{
print_debug ("optout", "horiz", channelG->horiz_layer, num_rowsG, num_colsG, num_netsG);
print_debug ("optout", "vert", channelG->vert_layer, num_rowsG, num_colsG, num_netsG);
		    S_dumppath( i );
		    return ;
		}
	    }
	}
	net_arrayG[i].tmplist = net_arrayG[i].oldtmplist;
	net_arrayG[i].oldtmplist = (LINKPTR)NULL;
	net_arrayG[i].cost = net_arrayG[i].oldcost;
    }
    /*
     *  Reschedule the jobs for marked nets
     */
    for( i = 1; i <= num_netsG; i++ )
    {
	if( net_arrayG[i].marked == NO || i == net )
    continue;
	S_delschedq( i );
	S_schedule( i, net_arrayG[i].cost );
    }
}

S_trypointvert( x1, y1, x2, y2, net )
int x1,
    y1,
    x2,
    y2;
int net;
/*
 *  y1 < y2
 *  If looks helpful, call pointtmove.
 *  Update historyG.
 */
{
    int ydown ;
    int yup ;
    int block1 = 0;
    int block2 = 0;

    /*  find blocking net 1  */
    for( ydown = y1; ydown < num_rowsG; ydown++ )
    {
        if( vlayerG[ydown][x1] != 0 && vlayerG[ydown][x1] != net )
 	    break;
    }
    if( ydown < num_rowsG )
        block1 = vlayerG[ydown][x1];

    /*  find blocking net 2  */
    for( yup = y2; yup > 1; yup-- )
    {
        if( vlayerG[yup][x2] != 0 && vlayerG[yup][x2] != net )
 	    break;
    }
    if( yup > 1 )
        block2 = vlayerG[yup][x2];

    if( ABS( yup - ydown ) > PTLIMIT )
	return( NO );

    /*  Keep within channel and prevent oscill.  */
    if( block1 > 0 &&
	block1 <= num_netsG && historyG[net][block1] <= PTDOWN )
    {
	if( S_pointmove( DOWN, x1, ydown, block1, VERT ) ||
	    S_pointpush( DOWN, x1, ydown, block1 ))
	{
	    historyG[net][block1] = PTDOWN;
	    return( YES );
	}
	else
            historyG[net][block1] = PTDOWN + 1;
    }

    /*  Keep within channel and prevent oscill.  */
    if( block2 > 0 &&
	block2 <= num_netsG && historyG[net][block2] <= PTUP )
    {
	if( S_pointmove( UP, x2, yup, block2, VERT ) ||
	    S_pointpush( UP, x2, yup, block2 ))
	{
	    historyG[net][block2] = PTUP;
	    return( YES );
	}
	else
            historyG[net][block2] = PTUP + 1;
    }
    return( NO );
}


S_trypointhoriz( x1, y1, x2, y2, net )
int x1,
    y1,
    x2,
    y2;
int net;
/*
 *  x1 < x2
 *  If looks helpful, call pointtmove.
 *  Update historyG.
 */
{
    int xright ;
    int xleft ;
    int block1 = 0;
    int block2 = 0;

    /*  find blocking net 1  */
    for( xright = x1; xright < num_colsG; xright++ )
    {
        if( hlayerG[y1][xright] != 0 && hlayerG[y1][xright] != net )
 	    break;
    }
    if( xright < num_colsG )
        block1 = hlayerG[y1][xright];

    /*  find blocking net 2  */
    for( xleft = x2; xleft > 1; xleft-- )
    {
        if( hlayerG[y2][xleft] != 0 && hlayerG[y2][xleft] != net )
 	    break;
    }
    if( xleft > 1 )
        block2 = hlayerG[y2][xleft];

    if( ABS( xleft - xright ) >= PTLIMIT )
	return( NO );

    /*  Keep within channel and prevent oscill.  */
    if( block2 > 0 && block2 <= num_netsG &&
	historyG[net][block2] <= PTLEFT )
    {
	if( S_pointmove( LEFT, xleft, y2, block2, HORIZ ) ||
	    S_pointpush( LEFT, xleft, y2, block2 ))
	{
	    historyG[net][block2] = PTLEFT;
	    return( YES );
	}
	else
            historyG[net][block2] = PTLEFT + 1;
    }

    /*  Keep within channel and prevent oscill.  */
    if( block1 > 0 && block1 <= num_netsG &&
	historyG[net][block1] <= PTRIGHT )
    {
	if( S_pointmove( RIGHT, xright, y1, block1, HORIZ ) ||
	    S_pointpush( RIGHT, xright, y1, block1 ))
	{
	    historyG[net][block1] = PTRIGHT;
	    return( YES );
	}
	else
            historyG[net][block1] = PTRIGHT + 1;
    }

    return( NO );
}
