#ifndef lint
static char SccsId[] = "@(#) post.c version 6.1 6/19/90" ;
#endif

#include "mighty.h"
#define OUTCOST 1000

extern int HCOST1;
extern int VCOST1;

extern int HCOST2;
extern int VCOST2;
extern int SWCOST;

extern int LIMCOST;
extern int LOWLIMIT;
extern int HIGHLIMIT;
extern int LEFTLIMIT;
extern int RIGHTLIMIT;

extern int left_start;
extern int left_numtr;
extern int right_start;
extern int right_numtr;

void
S_maxmetal()
/*
 *  maximize metal
 */
{
    LINKPTR tmplink;
    int i;  /* counter */
    int net,
	diff;
    int status;
    void S_writelink();
    void S_dellink();
    int S_findcomponents();
    int S_findpath();
    void S_trytmppath();

    LIMCOST = 3000;

    HCOST1 = 6;
    VCOST1 = 10;
    HCOST2 = 12;
    VCOST2 = 8;
    SWCOST = 30;

    for( i = 1; i <= num_netsG; i++ )
    {
        net_arrayG[i].difficulty = 0;
	for( tmplink = net_arrayG[i].path; tmplink != (LINKPTR)NULL;
			tmplink = tmplink->netnext )
            net_arrayG[i].difficulty += tmplink->x2 - tmplink->x1 +
				tmplink->y2 - tmplink->y1;
        if( net_arrayG[i].left == YES )
            net_arrayG[i].difficulty += OUTCOST;
        if( net_arrayG[i].right == YES )
            net_arrayG[i].difficulty += OUTCOST;
    }

    for( ; ; )
    {
	diff = 0;
        for( i = 1; i <= num_netsG; i++ )
        {
    	    if( diff < net_arrayG[i].difficulty )
	    {
		net = i;
		diff = net_arrayG[i].difficulty;
	    }
	}
	if( diff == 0 )
	    break;

	net_arrayG[net].difficulty = 0;

	while( (tmplink = net_arrayG[net].path) != (LINKPTR)NULL )
	{
	    S_writelink( tmplink, 0 );
	    S_dellink( tmplink );
	}
	/*
	 *  left/right pins
	 */
	if( net_arrayG[net].left == YES )
	    S_poststart( net, LEFT );
	if( net_arrayG[net].right == YES )
	    S_poststart( net, RIGHT );

	while( S_findcomponents( net ) > 1 )
	{
            if ( (status = S_findpath( net, YES )) == YES )
	    {
		if( net_arrayG[net].left == YES )
	    	    S_postend( net, LEFT );
		if( net_arrayG[net].right == YES )
	    	    S_postend( net, RIGHT );

		if( S_trytmppath( net ) == NO )
		{
S_dumppath( net );
print_debug ("routed", "horiz", channelG->horiz_layer, num_rowsG, num_colsG, num_netsG);
print_debug ("routed", "vert", channelG->vert_layer, num_rowsG, num_colsG, num_netsG);
		    YexitPgm( 5 );
		}
	    }
	    else if (status == NO)
	    {
		S_findpath( net, NO );
	        printf("findpath not possible - metal maximization %D\n", net);
		S_debugdumpsched( net );
	        YexitPgm( 10 );
	    }
	}
    }
}

S_poststart( net, side )
int net;
int side;
/*
 *  add pins on all available left/right column
 */
{
int r;
int c;
PINPTR newpin;
int start;
int stop;
PINPTR S_getpin();
int S_trytmppath();

    if( side == LEFT )
    {
	c = 1;
	start = left_start;
	stop = left_start + left_numtr - 1;
    }
    else
    {
	c = num_colsG;
	start = right_start;
	stop = right_start + right_numtr - 1;
    }

    for( r = start; r <= stop; r++ )
    {
	if( hlayerG[r][c] == 0 || hlayerG[r][c] > num_netsG )
	{
	    newpin = S_getpin();
	    newpin->type = TEMP;
	    newpin->x = c;
	    newpin->y = r;
	    newpin->layer = HORIZ;
            newpin->next = net_arrayG[net].pin;
	    net_arrayG[net].pin = newpin;
/*
printf("pin at %d %d for %d\n", newpin->x, newpin->y, number_to_name(i));
*/
            playerhG[r][c] = net;
            hlayerG[r][c] = net;
	    /*
	    if( playerhG[r-1][c] == net )
	    {
		S_addlink(HORIZ, c, r-1, c, r, net);
	    }
	    else if( playerhG[r+1][c] != 0 && playerhG[r+1][c] <= num_netsG )
	    {
		S_addlink(HORIZ, c, r, c, r, net);
	    }
	    */
	}
    }
    if( S_trytmppath(net) == NO )
	YexitPgm( 4 );
}

S_postend( net, side )
int net;
int side;
{
LINKPTR tmplink;
LINKPTR plink;
int row;
int col;

    if( side == LEFT )
	col = 1;
    else
	col = num_colsG;

    for( tmplink = net_arrayG[net].tmplist; tmplink != (LINKPTR)NULL;
	tmplink = tmplink->netnext )
    {
	if( (tmplink->x1 == col && tmplink->x2 != col) ||
	    (tmplink->x2 == col && tmplink->x1 != col) )
	{
    break;
	}
    }
    if( tmplink == (LINKPTR)NULL )
	return;
    else
	row = tmplink->y1;
    
    /*
     *  rm TEMP pins
     */
    S_rmsidepins( net, row, col );
    /*
    S_dumppath(net);
    S_dumppins(net);
    */

    /*
     *  rm connection on col
     */
    for( tmplink = net_arrayG[net].path; tmplink != (LINKPTR)NULL;
	tmplink = tmplink->netnext )
    {
SLOOP:
	if( tmplink->x1 == col && tmplink->x2 == col )
	{
	    if( tmplink == net_arrayG[net].path )
	    {
		net_arrayG[net].path = tmplink->netnext;
		S_retlink( tmplink );
		tmplink = net_arrayG[net].path;
	    }
	    else
	    {
	        plink->netnext = tmplink->netnext;
	        S_retlink( tmplink );
	        tmplink = plink->netnext;
	    }
	    if( tmplink != (LINKPTR)NULL )
	        goto SLOOP;
	    else
		break;
	}
	plink = tmplink;
    }
}
