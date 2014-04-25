#ifndef lint
static char SccsId[] = "@(#) link.c version 6.2 4/6/92" ;
#endif

#include "mighty.h"

/*
 *  find the number of the connected components of a net
 */
int S_findcomponents( i )
int i;  /* net number */
{
    PINPTR tpin;
    LINKPTR link;
    int num_comp;  /*  number of connected components */
    int j;
    int first;
    void S_searchtree();
    int S_linkgroup();
    int S_compensateequiv();

    /*
     *  set the group of every pin to 0
     */
    for(tpin = net_arrayG[i].pin; tpin != (PINPTR)NULL; tpin = tpin->next)
	tpin->group = 0;
    /*
     *  set the group of every link to 0
     */
    for( link = net_arrayG[i].path; link != (LINKPTR)NULL; link = link->netnext )
	link->group = 0;
    /*
     *  find connected components of links
     */
    num_comp = 0;
    /* for post-processing of left-pins  */
    if( net_arrayG[i].left == YES )
    {
	num_comp++;
        for(tpin = net_arrayG[i].pin; tpin != (PINPTR)NULL; tpin = tpin->next)
	{
	    if( tpin->x == 1 )
	    {
		tpin->group = num_comp;
	        S_searchtree( tpin->x, tpin->y, num_comp, i );
	    }
	}
    }
    /* for post-processing of right-pins  */
    if( net_arrayG[i].right == YES )
    {
	first = TRUE;
        for(tpin = net_arrayG[i].pin; tpin != (PINPTR)NULL; tpin = tpin->next)
	{
	    if( tpin->x == num_colsG )
	    {
	        tpin->group = S_linkgroup(tpin->x, tpin->y, i);
		if( tpin->group == 0 )
		{
		    if( first == TRUE )
		    {
			num_comp++;
			first = FALSE;
		    }
		    tpin->group = num_comp;
	            S_searchtree( tpin->x, tpin->y, num_comp, i );
		}
	    }
	}
    }
    for( link = net_arrayG[i].path; link != (LINKPTR)NULL; link = link->netnext )
    {
	if( link->group == 0 )
	{
	    num_comp++;

	    S_searchtree( link->x1, link->y1, num_comp, i );
	    S_searchtree( link->x2, link->y2, num_comp, i );
	}
    }
    /*
     *  find the group of the pins
     */
    for( tpin = net_arrayG[i].pin; tpin != (PINPTR)NULL; tpin = tpin->next )
    {
	if( tpin->group == 0 )
	{
	    tpin->group = S_linkgroup(tpin->x, tpin->y, i);
	    if( tpin->group == 0 )
	        tpin->group = ++num_comp;
	}
    }
    if( num_comp > 1 && net_arrayG[i].numequiv > 0 )
	num_comp = S_compensateequiv( i );

/*
printf(" %d findcomp : %d found\n", i, num_comp );
*/
    return( num_comp );
}

/*
 *  If there is a link at (x, y) return link->group
 *  else retun 0
 */
S_linkgroup(x, y, net)
int x,
    y;    /*  coordinates  */
int net;  /*  net number  */
{
    LINKLISTPTR linklist;

    for( linklist = linklayerG[y][x]; linklist != (LINKLISTPTR)NULL;
		linklist = linklist->next )
    {
	if( linklist->link->net == net )
	{
	    return( linklist->link->group );
	}
    }
    /*  not found  */
    return( 0 );
}

/*
 *  search all the connected tree
 */
S_searchtree( x, y, group, net )
int x,
    y;    /*  coordinates  */
int group;
int net;
{
    LINKPTR link;
    LINKLISTPTR linklist;
    void S_searchtree();

    for( linklist = linklayerG[y][x]; linklist != (LINKLISTPTR)NULL;
		linklist = linklist->next )
    {
	link = linklist->link;
	/*
	 *  process unscanned link of the net
	 */
	if( link->group == 0 && link->net == net )
	{
	    link->group = group;
	    if( link->x1 == x && link->y1 == y )
	        S_searchtree( link->x2, link->y2, group, net );
	    else
	        S_searchtree( link->x1, link->y1, group, net );
	}
    }
}

/*
 *  add pointers to the net_arrayG.tmplist
 */
S_addlink( layer, x1, y1, x2, y2, net )
int layer;  /*  which layer  */
int x1,
    x2,
    y1,
    y2;  /*  two end points,  x1 <= x2, y1 <= y2  */
int net; /*  net_num  */
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
printf("addlink called %s, net=%d (%d, %d), (%d,%d)\n",
    (layer == HORIZ ? "H" : "V"), net, x1, y1, x2, y2 );
*/
    link = S_getlink();
    link->x1 = x1;
    link->y1 = y1;
    link->x2 = x2;
    link->y2 = y2;
    link->net = net;
    link->layer = layer;
    link->group = 1;
    link->p.user_given = FALSE;
    /*
     *  add a pointer list on the net
     */
    link->netnext = net_arrayG[net].tmplist;
    net_arrayG[net].tmplist = link;
}

/* user_given switch allows us to add user_given to the list */
/* of arguments to addpathlink without having to add to all function */
/* calls.  It is only true when called from add pins to boundary call */
/* so this is not much of a penalty. Also need to add x,y value of via */
/* at point x1,y1 on connectotboundary function. If we don't add via, */
/* make xvia, yvia -1,-1 which can't occur in via array. */
static BOOL user_given_switch_on = FALSE ;
static int xvia, yvia ;
S_turn_user_given_on(x, y )
int x, y ;
{
    user_given_switch_on = TRUE ;
    xvia = x ;
    yvia = y ;
}

/*
 *  add pointers to the net_arrayG.path
 */
S_addpathlink( layer, x1, y1, x2, y2, net )
int layer;  /*  which layer  */
int x1,
    x2,
    y1,
    y2;  /*  two end points,  x1 <= x2, y1 <= y2  */
int net; /*  net_num  */
{
    LINKPTR link;
    int tmp;
    LINKPTR S_getlink();
    void S_addlklayer();

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
printf("addpathlink called %s, net=%d (%d, %d), (%d,%d)\n",
    (layer == HORIZ ? "H" : "V"), net, x1, y1, x2, y2 );
*/
    link = S_getlink();
    link->x1 = x1;
    link->y1 = y1;
    link->x2 = x2;
    link->y2 = y2;
    link->net = net;
    link->layer = layer;
    link->group = 1;
    if( user_given_switch_on ){
	link->p.user_given = USERGIVEN;
	/* avoid adding second via to this we must dogleg */
	/* in the case of adding a pin to boundary */
	if( xvia != -1 && yvia != -1 ){
	    S_addlklayer(link, xvia, yvia);
	}
    } else {
	link->p.user_given = FALSE;
	S_addlklayer(link, x1, y1);
	S_addlklayer(link, x2, y2);
    }
    /*
     *  add a pointer list on the net
     */
    /* turn switch off */
    user_given_switch_on = FALSE ;
    link->netnext = net_arrayG[net].path;
    net_arrayG[net].path = link;
}

/*
 *  make a link nice and clean : If modified return YES
 *  used to jump links in impr3.c
 */
void S_adjustlink( net )
int net; /*  net_num  */
{
    LINKPTR link;
    int S_dividelink();
    void S_writelink();
    int S_joinlink();

    while( S_dividelink( net ) )
	continue;
    for(link = net_arrayG[net].path; link != (LINKPTR)NULL; link = link->netnext )
	S_writelink( link, net );
    while( S_joinlink( net ) )
	continue;
    for(link = net_arrayG[net].path; link != (LINKPTR)NULL; link = link->netnext )
	S_writelink( link, net );
    return;
}

int S_dividelink( net )
int net; /*  net_num  */
{
    LINKPTR plink,
	    slink;
    int tmp,
	lay,
	val1,
	val2,
	val3,
	val4;
    void S_addpathlink();
    void S_writelink();
    void S_dellink();

    /*
     *  The two for loops are fine, since if S_dellink is
     *  called then return follows.
     */
    for( plink = net_arrayG[net].path; plink != (LINKPTR)NULL; plink = plink->netnext )
    {
	lay = plink->layer;
	/*  VERT */
	if( plink->x1 == plink->x2 )
	{
            for( slink = net_arrayG[net].path; slink != (LINKPTR)NULL;
		 slink = slink->netnext )
    	    {
		if( plink == slink )
	    continue;
		/* must be on the same column */
	        if( slink->x1 != slink->x2 || plink->x1 != slink->x1 )
	    continue;
	        /*  if solid intersection  */
	        if( lay == slink->layer &&
		    plink->y1 < slink->y2 && slink->y1 < plink->y2 )
	        {
	            val1 = MIN( plink->y1, slink->y1 );
		    val2 = MAX( plink->y1, slink->y1 );
		    val3 = MIN( plink->y2, slink->y2 );
		    val4 = MAX( plink->y2, slink->y2 );
		    tmp = plink->x1;
		    if( val1 != val2 )
                        S_addpathlink( lay, tmp, val1, tmp, val2, net );
		    if( val2 != val3 )
                        S_addpathlink( lay, tmp, val2, tmp, val3, net );
		    if( val3 != val4 )
                        S_addpathlink( lay, tmp, val3, tmp, val4, net );
/*
printf("adjust link of net %d, (%d, %d) (%d, %d)\n", net,
	plink->x1, plink->y1, plink->x2, plink->y2 );
printf("     and (%d, %d) (%d, %d)\n",
	slink->x1, slink->y1, slink->x2, slink->y2 );
*/
		    S_writelink( plink, 0 );
		    S_writelink( slink, 0 );
		    S_dellink( plink );
		    S_dellink( slink );
		    return( YES );
	        }
	    }
        }
	else /* HORIZ */
	{
            for( slink = net_arrayG[net].path; slink != (LINKPTR)NULL;
		 slink = slink->netnext )
    	    {
		if( plink == slink )
	    continue;
		/* must be on the same row */
	        if( slink->y1 != slink->y2 || plink->y1 != slink->y1 )
	    continue;
	        /*  if solid intersection  */
	        if( lay == slink->layer &&
		    plink->x1 < slink->x2 && slink->x1 < plink->x2 )
	        {
	            val1 = MIN( plink->x1, slink->x1 );
		    val2 = MAX( plink->x1, slink->x1 );
		    val3 = MIN( plink->x2, slink->x2 );
		    val4 = MAX( plink->x2, slink->x2 );
		    tmp = plink->y1;
		    if( val1 != val2 )
                        S_addpathlink( lay, val1, tmp, val2, tmp, net );
		    if( val2 != val3 )
                        S_addpathlink( lay, val2, tmp, val3, tmp, net );
		    if( val3 != val4 )
                        S_addpathlink( lay, val3, tmp, val4, tmp, net );
/*
printf("adjust link of net %d, (%d, %d) (%d, %d)\n", net,
	plink->x1, plink->y1, plink->x2, plink->y2 );
printf("     and (%d, %d) (%d, %d)\n",
	slink->x1, slink->y1, slink->x2, slink->y2 );
*/
		    S_writelink( plink, 0 );
		    S_writelink( slink, 0 );
		    S_dellink( plink );
		    S_dellink( slink );
		    return( YES );
	        }
	    }
        }
    }
    return( NO );
}

int S_joinlink( net )
int net; /*  net_num  */
{
    LINKPTR plink,
	    slink;
    void S_writelink();
    void S_dellink();
    void S_addlink();

    for( plink = net_arrayG[net].path; plink != (LINKPTR)NULL; plink = plink->netnext )
    {
        for( slink = net_arrayG[net].path; slink != (LINKPTR)NULL;
	    slink = slink->netnext )
    	{
	    if( plink == slink )
	continue;
	    if( plink->x1 == slink->x1 &&
	        plink->x2 == slink->x2 &&
	        plink->y1 == slink->y1 &&
	        plink->y2 == slink->y2 )
	    {
		if( plink->x1 < plink->x2 - 1 && plink->layer == VERT )
		{
		    S_writelink( plink, 0 );
		    S_dellink( plink );
		}
		else
		{
		    S_writelink( slink, 0 );
		    S_dellink( slink );
		}
		return( YES );
	    }

	    /* join */
	    if( plink->x1 == slink->x1 &&
	        plink->x2 == slink->x1 &&
		slink->x2 == slink->x1 &&
		plink->layer == slink->layer )
	    {
		if( plink->y2 == slink->y1 &&
		    hlayerG[slink->y1][slink->x1 + 1] != net &&
		    hlayerG[slink->y1][slink->x1 - 1] != net &&
		    vlayerG[slink->y1][slink->x1 + 1] != net &&
		    vlayerG[slink->y1][slink->x1 - 1] != net &&
		    playerhG[slink->y1][slink->x1] != net &&
		    playervG[slink->y1][slink->x1] != net )
		{
                    S_addlink( slink->layer, slink->x1, plink->y1, slink->x2, slink->y2, net );
		    S_writelink( plink, 0 );
		    S_writelink( slink, 0 );
		    S_dellink( plink );
		    S_dellink( slink );
		    return( YES );
		}
		if( plink->y1 == slink->y2 &&
		    hlayerG[plink->y1][plink->x1 + 1] != net &&
		    hlayerG[plink->y1][plink->x1 - 1] != net &&
		    vlayerG[plink->y1][plink->x1 + 1] != net &&
		    vlayerG[plink->y1][plink->x1 - 1] != net &&
		    playerhG[plink->y1][plink->x1] != net &&
		    playervG[plink->y1][plink->x1] != net )
		{
                    S_addlink( slink->layer, slink->x1, slink->y1, slink->x2, plink->y2, net );
		    S_writelink( plink, 0 );
		    S_writelink( slink, 0 );
		    S_dellink( plink );
		    S_dellink( slink );
		    return( YES );
		}
	    }
	    if( plink->y1 == slink->y1 &&
	        plink->y2 == slink->y1 &&
		slink->y2 == slink->y1 &&
		plink->layer == slink->layer )
	    {
		if( plink->x2 == slink->x1 &&
		    hlayerG[slink->y1 - 1][slink->x1] != net &&
		    hlayerG[slink->y1 + 1][slink->x1] != net &&
		    vlayerG[slink->y1 - 1][slink->x1] != net &&
		    vlayerG[slink->y1 + 1][slink->x1] != net &&
		    playerhG[slink->y1][slink->x1] != net &&
		    playervG[slink->y1][slink->x1] != net )
		{
                    S_addlink( slink->layer, plink->x1, slink->y1, slink->x2, slink->y2, net );
		    S_writelink( plink, 0 );
		    S_writelink( slink, 0 );
		    S_dellink( plink );
		    S_dellink( slink );
		    return( YES );
		}
		if( plink->x1 == slink->x2 &&
		    hlayerG[plink->y1 - 1][plink->x1] != net &&
		    hlayerG[plink->y1 + 1][plink->x1] != net &&
		    vlayerG[plink->y1 - 1][plink->x1] != net &&
		    vlayerG[plink->y1 + 1][plink->x1] != net &&
		    playerhG[plink->y1][plink->x1] != net &&
		    playervG[plink->y1][plink->x1] != net )
		{
                    S_addlink( slink->layer, slink->x1, slink->y1, plink->x2, slink->y2, net );
		    S_writelink( plink, 0 );
		    S_writelink( slink, 0 );
		    S_dellink( plink );
		    S_dellink( slink );
		    return( YES );
		}
	    }
	}
    }
    return( NO );
}


/*
 *  delete link, when undo previous routing - rerouting
 */
S_dellink( link )
LINKPTR link;
{
    LINKPTR tmplink;
    LINKLISTPTR lklist,
		tmplklist;
    int net;
    int x1,
	x2,
	y1,
	y2;
    void S_retlklist();
    void S_retlink();

    x1 = link->x1;
    y1 = link->y1;
    x2 = link->x2;
    y2 = link->y2;
    net = link->net;
/*
printf("  dellink : net %d, (%d, %d), (%d, %d)",net, x1, y1, x2, y2 );
*/

    /*
     *  delete from net_arrayG.path
     */
    if( net_arrayG[net].path == link )
	net_arrayG[net].path = link->netnext;
    else
    {
        for( tmplink = net_arrayG[net].path; tmplink != (LINKPTR)NULL;
	     tmplink = tmplink->netnext )
        {
	    if( tmplink->netnext == link )
	       break;
        }
        if( tmplink == (LINKPTR)NULL )
	{
	    printf("ERROR try to del nil of net %d\n", link->net);
	    return;
	}
        tmplink->netnext = link->netnext;
    }
/*
printf(" from net");
*/
    /*
     *  delete from linklayer
     */
    if( (linklayerG[y1][x1])->link == link )
    {
	tmplklist = linklayerG[y1][x1];
	linklayerG[y1][x1] = linklayerG[y1][x1]->next;
    }
    else
    {
        for( lklist = linklayerG[y1][x1]; lklist != (LINKLISTPTR)NULL;
			lklist = lklist->next )
	    if( lklist->next->link == link )
		break;
	if( lklist == (LINKLISTPTR)NULL ) YexitPgm( 16 );
	tmplklist = lklist->next;
	lklist->next = tmplklist->next;
    }
    S_retlklist( tmplklist );

    if( (linklayerG[y2][x2])->link == link )
    {
	tmplklist = linklayerG[y2][x2];
	linklayerG[y2][x2] = linklayerG[y2][x2]->next;
    }
    else
    {
        for( lklist = linklayerG[y2][x2]; lklist != (LINKLISTPTR)NULL;
			lklist = lklist->next )
	    if( lklist->next->link == link )
		break;
	if( lklist == (LINKLISTPTR)NULL ) YexitPgm( 17 );
	tmplklist = lklist->next;
	lklist->next = tmplklist->next;
    }
    S_retlklist( tmplklist );
    S_retlink( link );
/*
printf(" from lklayer\n");
*/
}

/*
 *  backtrack the path
 */
S_backtrack( layer, x, y, group1, net, cost1 )
int layer,
    x,
    y,
    group1;
int net,
    cost1;
{
    int dir1,
	dir2;  /* directions of the backtracking */
    int x1,
	x2,
	x3,
	x4,
	y1,
	y2,
	y3,
	y4;    /*  coordinates */
    int group2,
	cost2;
    int layer1, layer2;
    void S_addlink();
    int S_backlink();
    int S_complayer();

    x1 = x2 = x3 = x4 = x;
    y1 = y2 = y3 = y4 = y;
    layer1 = layer2 = layer;
    /*
     *  scale cost1 and find cost2
     */
    if( layer == HORIZ )
    {
	cost2 = - channelG->horiz_layer[y][x];
	group2 = channelG->hcomp[y][x];
    }
    else
    {
	cost2 = - channelG->vert_layer[y][x];
	group2 = channelG->vcomp[y][x];
    }
    cost1 = (cost1 - MAX(1, cost2)) * 2 + MAX(1, cost2);
    /*
     *  when the cost is negative, it may be the case of layer-changing
     */
    if( cost2 < 0 )
    {
        if( cost2 == - net )
        {
/*
printf(" === divlink : net %d at (%d, %d)\n", net, x, y );
*/
	    S_addlink( NULL, x, y, x, y, net ); /* to call S_divlink */
	    goto GROUP1_ONLY;
        }
	else
        {
print_debug ("divlink nec", "horiz", channelG->horiz_layer, num_rowsG, num_colsG, num_netsG);
print_debug ("divlink nec", "vert", channelG->vert_layer, num_rowsG, num_colsG, num_netsG);
print_debug ("divlink nec", "hcomp", channelG->hcomp, num_rowsG, num_colsG, num_netsG);
print_debug ("divlink nec", "vcomp", channelG->vcomp, num_rowsG, num_colsG, num_netsG);
	    YexitPgm( 7 );
	}
    }
    dir1 = S_backlink( &x1, &y1, &x2, &y2, group1, &cost1, net, layer );
    dir2 = S_backlink( &x3, &y3, &x4, &y4, group2, &cost2, net, layer );
    if( dir1 == dir2 )
    {
	if( dir1 == HORIZ )
	{
	    if( x2 != x4 )
		S_addlink( layer, x2, y, x4, y, net );
	}
	else
	{  /* VERT */
	    if( y2 != y4 )
		S_addlink( layer, x, y2, x, y4, net );
	}
    }
    else
    {
	if( x1 != x2 || y1 != y2 )
            S_addlink( layer, x1, y1, x2, y2, net );
	if( x3 != x4 || y3 != y4 )
            S_addlink( layer, x3, y3, x4, y4, net );
    }
    /*
     *  find the starting points
     */
    x1 = x2;
    y1 = y2;
    x3 = x4;
    y3 = y4;
    if( dir1 == SWITCH )
	layer1 = S_complayer( layer1 );
    else if( dir2 == SWITCH )
	layer2 = S_complayer( layer2 );
    /*
     *  backtrack group2
     */
    while( (dir2 = S_backlink( &x3, &y3, &x4, &y4, group2, &cost2, net, layer2 )) != NO )
    {
	if( dir2 == SWITCH )
	    layer2 = S_complayer( layer2 );
	else
	{
            S_addlink( layer2, x3, y3, x4, y4, net );
	    /*  next starting point */
	    x3 = x4;
	    y3 = y4;
	}
    }
    if( (x != x3 || y != y3) && playerhG[y3][x3] != net &&
    				playervG[y3][x3] != net )
    {
/*
printf(" === divlink : net %d at (%d, %d)\n", net, x3, y3 );
*/
	S_addlink( NULL, x3, y3, x3, y3, net ); /* to call S_divlink */
    }
GROUP1_ONLY :
    /*
     *  backtrack group1
     */
    while( (dir1 = S_backlink( &x1, &y1, &x2, &y2, group1, &cost1, net, layer1 )) != NO )
    {
	if( dir1 == SWITCH )
	    layer1 = S_complayer( layer1 );
	else
	{
            S_addlink( layer1, x1, y1, x2, y2, net );
	    /*  next starting point */
	    x1 = x2;
	    y1 = y2;
	}
    }
    if( (x != x1 || y != y1) && playerhG[y1][x1] != net &&
				playervG[y1][x1] != net )
    {
/*
printf(" === divlink : net %d at (%d, %d)\n", net, x1, y1 );
*/
	S_addlink( NULL, x1, y1, x1, y1, net ); /* to call S_divlink */
    }
}

int S_complayer( layer )
int layer;
{
    if( layer == HORIZ )
	return( VERT );
    else
	return( HORIZ );
}

/*
 *  find one link
 */
int S_backlink( xp1, yp1, xp2, yp2, group, costp, net, layer )
int *xp1,
    *xp2,
    *yp1,
    *yp2;
int group;
int *costp;
int net,
    layer;
{
    int dir;
    int cost;
    int x2,
	y2;
    int S_backnext();


    x2 = *xp1;
    y2 = *yp1;
    if( (dir = S_backnext( &x2 , &y2, group, costp, layer, net )) == NO )
    {
	return( NO );
    }
    else if( dir == SWITCH )
    {
	return( SWITCH );
    }
    else
    {
	*xp2 = x2;
	*yp2 = y2;
	cost = *costp;
	while( dir == S_backnext( &x2, &y2, group, &cost, layer, net ) )
	{
	    *xp2 = x2;
	    *yp2 = y2;
	    *costp = cost;
	}
    }
    /*
     *  order x1, x2 and y1, y2
     */
    /*
    if( *xp1 > *xp2 )
    {
	x2 = *xp2;
	*xp2 = *xp1;
	*xp1 = x2;
    }
    if( *yp1 > *yp2 )
    {
	y2 = *yp2;
	*yp2 = *yp1;
	*yp1 = y2;
    }
    */
    return( dir );
}


/*
 *  add link in the list of linklayer[y][x]
 */
S_addlklayer(link, x, y)
LINKPTR link;
int x,
    y;
{
    LINKLISTPTR lklist;
    LINKLISTPTR S_getlklist();

    lklist = S_getlklist();
    lklist->link = link;
    lklist->next = linklayerG[y][x];
    linklayerG[y][x] = lklist;
}

/*
 *  divide a link
 *  delete a long link and add two links to path
 */
S_divlink( x, y, net )
int x,
    y;
int net;
{
    LINKPTR link,
	    nextlink;
    int layer;
    int x1,
	y1,
	x2,
	y2;
    void S_addpathlink();
    void S_dellink();

/*
printf("  divlink called : net %d, (%d, %d)\n", net, x, y);
*/
    /*
     *  special case : corner point - add an zero length edge
     *  e.g. if top[1] and left[1] are to be connected.
     */
/* 4/18'86
    if( (x == 1 || x == num_cols) && ( y == 1 || y == num_rows ) )
    {
	if( channel->horiz_layer[y][x] == net )
            S_addpathlink( HORIZ, x, y, x, y, net );
	else
            S_addpathlink( VERT, x, y, x, y, net );
	return;
    }
*/
    /*
     *  normal case
     */
    for( link = net_arrayG[net].path; link != (LINKPTR)NULL; link = nextlink )
    {
	nextlink = link->netnext;
	if( link->x1 == x && link->x2 == x &&
	    link->y1 < y && y < link->y2 )
	{
	    layer = link->layer;
	    y1 = link->y1;
	    y2 = link->y2;

	    S_dellink( link );
            S_addpathlink( layer, x, y1, x, y, net );
            S_addpathlink( layer, x, y, x, y2, net );
	    return( YES );
	}
	else if( link->y1 == y && link->y2 == y &&
	         link->x1 < x && x < link->x2 )
	{
	    layer = link->layer;
	    x1 = link->x1;
	    x2 = link->x2;

	    S_dellink( link );
            S_addpathlink( layer, x1, y, x, y, net );
            S_addpathlink( layer, x, y, x2, y, net );
	    return( YES );
	}
    }
    return( NO );
}


/*
 *  return the link of net terminating at (x, y)
 */
LINKPTR S_picklink( x, y, net )
int x,
    y;
int net;
{
    LINKLISTPTR linklist;

    for( linklist = linklayerG[y][x]; linklist != (LINKLISTPTR)NULL;
		linklist = linklist->next )
    {
	if( linklist->link->net == net )
	    return( linklist->link );
    }
    return( (LINKPTR)NULL );
}

/*
 * tranform normal layer to the other one
 */
#ifdef WDEBUG
/* Too complicated 4/18'86 */
#endif
int S_translink( dir, x, y, low, high, net )
int dir;
int x,
    y,
    low,
    high,
    net;
{
    LINKLISTPTR linklist;
    LINKPTR link;
    LINKPTR lowlink = (LINKPTR)NULL;
    LINKPTR highlink = (LINKPTR)NULL;
    void S_dellink();
    void S_addpathlink();
    void S_addlink();

    if( dir == DOWN || dir == UP )
    {
	/*
	 * if already transformed return YES
	 */
	if( low == x - 1 )
	{
	    if( hlayerG[y][low] != 0 && hlayerG[y][low] != net ||
	        hlayerG[y][x] != 0 && hlayerG[y][x] != net )
		return( YES );
	}
	else if( high == x + 1 )
	{
	    if( hlayerG[y][high] != 0 && hlayerG[y][high] != net ||
	        hlayerG[y][x] != 0 && hlayerG[y][x] != net )
		return( YES );
	}
	else
	    return( NO );
	/*
	 *  if already unit width, change layer
	 */
	if( low == high - 1 )
	{
            for( linklist = linklayerG[y][x]; linklist != (LINKLISTPTR)NULL;
	         linklist = linklist->next )
            {
	        link = linklist->link;
	        if( link->y1 == y && link->y2 == y )
	        {
	    	    if( link->x1 == low && link->x2 == high )
		        if( lowlink == (LINKPTR)NULL )
			    lowlink = link;
			else
			    highlink = link;
		}
	    }
	    if( lowlink != (LINKPTR)NULL )
		S_dellink( lowlink );
	    if( highlink != (LINKPTR)NULL )
		S_dellink( highlink );
            S_addpathlink( VERT, low, y, high, y, net );
	    return( YES );
	}
	
	/*
	 *  general case
	 */
        for( linklist = linklayerG[y][x]; linklist != (LINKLISTPTR)NULL;
	     linklist = linklist->next )
        {
	    link = linklist->link;
	    if( link->y1 == y && link->y2 == y )
	    {
		if( link->x1 == low && link->x2 == x )
		    lowlink = link;
		else if( link->x1 == x && link->x2 == high )
		    highlink = link;
	    }
	}
	if( lowlink != (LINKPTR)NULL && highlink != (LINKPTR)NULL )
	{
	    if( x - low == 1 )
	    {
		lowlink->layer = VERT;
                S_addlink( HORIZ, low, y, high, y, net );
		S_dellink( highlink );
	    }
	    else
	    {
		highlink->layer = VERT;
                S_addlink( HORIZ, low, y, high, y, net );
		S_dellink( lowlink );
	    }
	    return( YES );
	}
    }
    else /* L/R */
    {
	/*
	 * if already transformed return YES
	 */
	if( low == y - 1 )
	{
	    if( vlayerG[y][low] != 0 && vlayerG[y][low] != net ||
	        vlayerG[y][x] != 0 && vlayerG[y][x] != net )
		return( YES );
	}
	else if( high == y + 1 )
	{
	    if( vlayerG[y][high] != 0 && vlayerG[y][high] != net ||
	        vlayerG[y][x] != 0 && vlayerG[y][x] != net )
		return( YES );
	}
	else
	    return( NO );
	/*
	 *  if already unit width, change layer
	 */
	if( low == high - 1 )
	{
            for( linklist = linklayerG[y][x]; linklist != (LINKLISTPTR)NULL;
	         linklist = linklist->next )
            {
	        link = linklist->link;
	        if( link->x1 == x && link->x2 == x )
	        {
	    	    if( link->y1 == low && link->y2 == high )
		        if( lowlink == (LINKPTR)NULL )
			    lowlink = link;
			else
			    highlink = link;
		}
	    }
	    if( lowlink != (LINKPTR)NULL )
		S_dellink( lowlink );
	    if( highlink != (LINKPTR)NULL )
		S_dellink( highlink );
            S_addpathlink( HORIZ, x, low, x, high, net );
	    return( YES );
	}
	
	/*
	 *  general case
	 */
        for( linklist = linklayerG[y][x]; linklist != (LINKLISTPTR)NULL;
	     linklist = linklist->next )
        {
	    link = linklist->link;
	    if( link->x1 == x && link->x2 == x )
	    {
		if( link->y1 == low && link->y2 == y )
		    lowlink = link;
		else if( link->y1 == y && link->y2 == high )
		    highlink = link;
	    }
	}
	if( lowlink != (LINKPTR)NULL && highlink != (LINKPTR)NULL )
	{
	    if( y - low == 1 )
	    {
		lowlink->layer = HORIZ;
                S_addlink( VERT, x, low, x, high, net );
		S_dellink( highlink );
	    }
	    else
	    {
		highlink->layer = HORIZ;
                S_addlink( VERT, x, low, x, high, net );
		S_dellink( lowlink );
	    }
	    return( YES );
	}
    }
    return( NO );
}

S_writelink( link, num )
LINKPTR link;
int num;
{
    int x,
	y;

    if( link->layer == HORIZ )
    {
	if( link->x1 == link->x2 )
	{
	    x = link->x1;
	    for( y = link->y1; y <= link->y2; y++ )
		hlayerG[y][x] = num;
	}
	else
	{
	    y = link->y1;
	    for( x = link->x1; x <= link->x2; x++ )
		hlayerG[y][x] = num;
	}
    }
    else
    {
	if( link->x1 == link->x2 )
	{
	    x = link->x1;
	    for( y = link->y1; y <= link->y2; y++ )
		vlayerG[y][x] = num;
	}
	else
	{
	    y = link->y1;
	    for( x = link->x1; x <= link->x2; x++ )
		vlayerG[y][x] = num;
	}
    }
}

