#ifndef lint
static char SccsId[] = "@(#) sched.c version 6.5 2/15/91" ;
#endif

#include "mighty.h"
#include <yalecad/message.h>

#define PRIORSENS 10  /* priority of sensitive nets */
int NUMGOOD = 5;
int conncount = 0;
int debcount = 2;
extern int LIMCOLS;
extern int Densityonly;
int addguideG = NO;
int Longch = NO;
int num_impr = 0;
int num_power = 0;

int HCOST1 = 2;
int VCOST1 = 2;
int HCOST2 = 50;
int VCOST2 = 50;
int SWCOST = 30;

int LIMCOST = 2500;  /* path length <= 2 * LIMCOST */
int MODCOST = 55;

SCHED_PTR schedheadG;

void S_route()
{
    LINKPTR link;
    int status; /*  YES, NO, or DONE */
    int job;    /*  net_number currently being connected  */
    int numcomp,
	numfloat; /* number of floating links - that is links */
		  /* without pins on both sides */
    int i;     	/*  counter  */
 
    schedheadG = (SCHED_PTR)NULL;

    S_markpinlayer();

    /*
     *  If Densityonly, return modified maximum density.
     */
    if( Densityonly )
    {
	S_retdensity();
	YexitPgm( 0 );
    }

    /* if mazeOnly we avoid adding pseudo pins */
    if( !(mazeOnlyG ) ){
	/*
	 *  if channel is too long, add pseudo pins
	 *  ( later, when channel is irregular )
	 */
	if( num_colsG > LIMCOLS/2 && num_pinsG > 10 )
	    Longch = YES;

	if( Longch || num_leftG > 0 || num_rightG > 0 || addguideG )
	{
	    addguideG = YES;
	    S_addguides();
	    S_markpinlayer();
	}
    } else {
	if( num_rightG > 0 || num_leftG > 0 ){
	    sprintf( YmsgG,
	    "Bad luck - mighty can't route this channel without adding pseudo pins.\n" ) ;
	    M( ERRMSG, "S_route", YmsgG ) ;
	    M( MSG,NULL,"You cannot run -maze option for this channel\n");
	    YexitPgm(1) ;
	}
	LIMCOLS = INFINITY ;
    }

    /*
     *  classify equivalent set of pins
     */
    for( i = 1; i <= num_netsG; i++ )
        S_equivpins( i );

    for( i = 1; i <= num_netsG; i++ )
    {
	if( S_findcomponents( i ) > 1 )
	{
            if ( (status = S_findpath( i, YES )) == YES )
	    {
	       /* lookForDanglers(i); */
                numfloat = S_schedpriority( i );
	        S_schedule( i, net_arrayG[i].cost );
	    }
	    else if (status == NO)
	    {
		if( debugG ){
		    print_debug ("after preroute", "horiz", channelG->horiz_layer,
			num_rowsG, num_colsG, num_netsG);
		    print_debug ("after preroute", "vert", channelG->vert_layer,
		    num_rowsG, num_colsG, num_netsG);
		}
	        printf("findpath not possible - not DONE for net:%d name:%d\n",
		    i, number_to_name(i) ) ;
		S_debugdumpsched(i);
	    }
	}
    }
    while( (job = S_popschedule()) != 0 )
    {
	if( debugG ){
	    sprintf( YmsgG, "route before net %d (user net %d)",job,
		number_to_name(job) );
	    print_debug (YmsgG, "horiz", channelG->horiz_layer, num_rowsG,
		num_colsG, num_netsG);
	    print_debug (YmsgG, "vert", channelG->vert_layer, num_rowsG,
		num_colsG, num_netsG);
	    printf("popsched net %d\n", job );
	}
	if( failedRouteG ){
	    sprintf( YmsgG, "attempting to route remaining net:%d\n",
		number_to_name(job) ) ;
	    M( MSG, NULL, YmsgG ) ;
	}
	if( S_trytmppath( job ) ) {
	    S_clearhistory( job );
	    if( failedRouteG ){
		sprintf( YmsgG, "successfully routed net:%d\n",
		    number_to_name(job) ) ;
		M( MSG, NULL, YmsgG ) ;
	    }
	}
	if ( (numcomp = S_findcomponents( job )) > 1 ) {
            if( (status = S_findpath( job, YES )) == YES ) {
                numfloat = S_schedpriority( job );
		if( debugG ){
		    printf("job %d : numfloat = %d\n", job, numfloat);
		}
	    }
	    /*
	     *  if not near optimal, reroute other nets
	     */
	    if( status == NO || numfloat >= NUMGOOD ) {
	        status = S_improve( job, status );
		num_impr++;
	    }
	    if( status == YES ){ /* path found */
		S_schedule( job, net_arrayG[job].cost );
	    } else {
		num_power++;
		if( S_powerimprove( job, 20 ) == NO ){  /* 20=try bound */
	     	    printf("findpath2 not possible - must reroute %d\n", job);
		    S_debugdumpsched(job);
                    continue;
		}
	    }
	}
        lookForDanglers(job);
    }
    if( debugG ){
	print_debug ("after route", "horiz", channelG->horiz_layer, num_rowsG,
	    num_colsG, num_netsG);
	print_debug ("after route", "vert", channelG->vert_layer, num_rowsG,
	    num_colsG, num_netsG);
	printf("popsched net %d\n", job );
    }
    printf("nummod = %d    numpower = %d\n", num_impr, num_power );
}

/*
 *  schedule the jobs in the order of priority to connect them
 */
S_schedule( i, value )
int i;  /* net number */
int value; /* priority */
{
    SCHED_PTR tmpq;
    SCHED_PTR prevq = (SCHED_PTR)NULL;
    SCHED_PTR newsched;
    SCHED_PTR S_getschedq();

    newsched = S_getschedq();
    newsched->net = i;    /* net_num */

    /* if sensitive net, give priority  */
    if( net_arrayG[i].sens == YES )
	value = value/PRIORSENS;

    newsched->priority = value;
/*
printf("*** net %d with priority %d\n", i, newsched->priority );
*/
    if( schedheadG == (SCHED_PTR)NULL )
    {
	newsched->next = (SCHED_PTR)NULL;
	schedheadG = newsched;
	return;
    }
    for( tmpq = schedheadG; tmpq != (SCHED_PTR)NULL; tmpq = tmpq->next )
    {
	if( newsched->priority <= tmpq->priority )
	    break;
	prevq = tmpq;
    }
    if( prevq == (SCHED_PTR)NULL )
    {
	/*  insert before schedheadG  */
        newsched->next = schedheadG;
	schedheadG = newsched;
    }
    else
    {
	/*  insert after prevq  */
        newsched->next = prevq->next;
	prevq->next = newsched;
    }
}

/*
 *  returns the first netnum
 *  if NULL return 0
 */
S_popschedule()
{
    SCHED_PTR tmpq;
    int net;  /* the net_num to be returned */

    if( schedheadG == (SCHED_PTR)NULL )
	return( 0 );
    net = schedheadG->net;
    tmpq = schedheadG;
    schedheadG = schedheadG->next;
    S_retschedq ( tmpq );
/*
printf("   popschedule %d ***\n", net );
*/
    return( net );
}


S_debugdumpsched(net)
int net ;
{
    SCHED_PTR tmpq;
    int count = 0;

    fprintf( stderr,
	"\nProblem encountered while routing net:%d username:%d\n",
	net, number_to_name(net) ) ;

    if( tmpq = schedheadG ){
	while( tmpq ){
	    printf("dump sched %d : net=%d, groupNo=%d, cost=%d\n",
		++count, tmpq->net, number_to_name(tmpq->net), 
		    tmpq->priority);
	    tmpq = tmpq->next ;
	}
    } else {
	printf("dump sched : NULL\n");
    }
    failed_route( net ) ;
} /* end S_debugdumpsched */


/*
 *  find numfloat in net.tmplist
 */
int S_schedpriority( net )
int net;
{
    LINKPTR tmplk;
    int numdiv ;
    int numfloat = 0;

    /*
     *  count each type of links
     */
    for( tmplk = net_arrayG[net].tmplist; tmplk != (LINKPTR)NULL;
		tmplk = tmplk->netnext )
    {
	if( tmplk->layer == 0 ){
	    /* numdiv++; */
	} else if( playerhG[tmplk->y1][tmplk->x1] != net &&
		 playervG[tmplk->y1][tmplk->x1] != net &&
	 	 playerhG[tmplk->y2][tmplk->x2] != net &&
	 	 playervG[tmplk->y2][tmplk->x2] != net )
	    numfloat++;
    }
    return( numfloat );
}

S_markpinlayer()
/*
 *  Mark the location of pins on player
 */
{
    PINPTR ppin;
    int i;

    for( i = 1; i <= num_netsG; i++ )
    {
	for( ppin = net_arrayG[i].pin; ppin != (PINPTR)NULL; ppin = ppin->next )
	{
	    if( ppin->layer == HORIZ )
	    {
	        playerhG[ppin->y][ppin->x] = i;
	        hlayerG[ppin->y][ppin->x] = i;
	    }
	    if( ppin->layer == VERT )
	    {
	        playervG[ppin->y][ppin->x] = i;
	        vlayerG[ppin->y][ppin->x] = i;
	    }
	}
    }
} /* end S_markpinlayer */

failed_route( net )
int net ;
{
    failedRouteG = TRUE ;
    fprintf(output_fileG, "failed net:%d\n", net );
    Ymessage_error_count() ;
} /* end failed_route */
