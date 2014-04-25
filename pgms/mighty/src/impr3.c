#ifndef lint
static char SccsId[] = "@(#) impr3.c version 6.2 10/14/90" ;
#endif

#include "mighty.h"

/*
 *  move a segment of a net by more than unit distance
 *  possibly over other nets
 */
int S_jumppush( dir, x, y, net )
int dir;
int x,
    y;
int net;
{
    LINKLISTPTR linklist;
    int jumpto;
    int x1,
	y1,
	x2,
	y2;
    int newx,
	newy;
    int S_wrongdir();
    int S_canjump();
    void S_makejump();
    int S_cansidejump();

    /*
     *  find interval to jump
     */
    x1 = x2 = x;
    y1 = y2 = y;
    for( linklist = linklayerG[y][x]; linklist != (LINKLISTPTR)NULL;
	linklist = linklist->next )
    {
	if( linklist->link->net == net )
	{
	    x1 = MIN( x1, linklist->link->x1 );
	    x2 = MAX( x2, linklist->link->x2 );
	    y1 = MIN( y1, linklist->link->y1 );
	    y2 = MAX( y2, linklist->link->y2 );
	}
    }
    /*
     *  If wrongdir, there may be no link on linklayer[y][x]
     *  Solution :
     *     if( x1 == x2 && y1 == y2 ) return NO
     *     if( x1 == x2 ) , NO jump UP/DOWN or sidejump LEFT/RIGHT
     *     if( y1 == y2 ) , NO sidejump UP/DOWN or jump LEFT/RIGHT
     */
    if( x1 == x2 && y1 == y2 ) return ( NO );

    if( dir == UP || dir == DOWN )
    {
	if( x1 == x2 ) goto SIDEJP1;
    	/*  No pins on the link  */
	for( newx = x1; newx <= x2; newx++ )
	{
	    /* Check playerhG only, since we do not jump if wrongdir */
	    if( playerhG[y][newx] == net )
	   	goto SIDEJP1;
	}

	if( S_wrongdir( x, y, net ) || S_wrongdir( x1, y, net ) ||
	    S_wrongdir( x2, y, net ) )
	    return( NO );
        if( (jumpto = S_canjump( dir, x, y, net, x1, x2 )) > 0 )
        {
            S_makejump( dir, x, y, net, x1, x2, jumpto );
	    return( YES );
        }
SIDEJP1:
	if( y1 == y2 ) return( NO );
	/*  No pins on the link  */
	for( newy = y1; newy <= y2; newy++ )
	{
	    /* Check playervG only, since we do not jump if wrongdir */
	    if( playervG[newy][x] == net )
        return( NO );
	}

	if( S_wrongdir( x, y1, net ) || S_wrongdir( x, y2, net ) )
	    return( NO );
        if( (jumpto = S_cansidejump( dir, x, y, net, y1, y2 )) > 0 )
	{
	    if( jumpto > x )
                S_makejump( RIGHT, x, y, net, y1, y2, jumpto );
	    else
                S_makejump( LEFT, x, y, net, y1, y2, jumpto );
	    return( YES );
	}
        return( NO );
    }
    else /* LEFT/RIGHT */
    {
	if( y1 == y2 ) goto SIDEJP2;
	/*  No pins on the link  */
	for( newy = y1; newy <= y2; newy++ )
	{
	    /* Check playervG only, since we do not jump if wrongdir */
	    if( playervG[newy][x] == net )
		goto SIDEJP2;
	}

	if( S_wrongdir( x, y, net ) || S_wrongdir( x, y1, net ) ||
	    S_wrongdir( x, y2, net ) )
	    return( NO );
        if( (jumpto = S_canjump( dir, x, y, net, y1, y2 )) > 0 )
        {
            S_makejump( dir, x, y, net, y1, y2, jumpto );
	    return( YES );
        }
SIDEJP2:
	if( x1 == x2 ) return( NO );
	/*  No pins on the link  */
	for( newx = x1; newx <= x2; newx++ )
	{
	    /* Check playerhG only, since we do not jump if wrongdir */
	    if( playerhG[y][newx] == net )
        return( NO );
	}

	if( S_wrongdir( x1, y, net ) || S_wrongdir( x2, y, net ) )
	    return( NO );
        if( (jumpto = S_cansidejump( dir, x, y, net, x1, x2 )) > 0 )
	{
	    if( jumpto > y )
                S_makejump( DOWN, x, y, net, x1, x2, jumpto );
	    else
                S_makejump( UP, x, y, net, x1, x2, jumpto );
	    return( YES );
	}
        return( NO );
    }
}

/*
 *  Jump a segment, if there is a space
 *
 *        |     |			|     |
 *        |     |			----------
 *        |     |			         |
 *        ----------			      ^
 *		^  |			      |
 *		|			      |
 */
S_canjump( dir, x, y, net, low, high )
int dir;
int x,
    y;
int net;
int low,
    high; /* interval to jump */
{
    int newx,
	newy;
    int tmpx,
	tmpy,
	jumpto;
    int pass; 		/* skip a row/column or not */
    int fitness,
        oldfitness;
    int S_linkgroup();

    if( dir == UP || dir == DOWN )
    {
	if( dir == DOWN )
	{
	    /*
	     *  see if there is a available row
	     */
	    oldfitness = 0;
	    jumpto = 0;
	    for( tmpy = y+1; tmpy <= num_rowsG; tmpy++ )
	    {
		if( vlayerG[tmpy][low] != 0 && vlayerG[tmpy][low] != net )
		    break; /* zzz recursion later */
		else if( vlayerG[tmpy][high] != 0 && vlayerG[tmpy][high] != net )
		    break;
		else if( vlayerG[tmpy][x] != 0 && vlayerG[tmpy][x] != net )
		    break;

		/*
		 *  don't block other pins
		 */
		pass = NO;
		for( tmpx = 1; tmpx <= num_colsG; tmpx++ )
		{
		    if( playerhG[tmpy][tmpx] > 0 &&
	         S_linkgroup( tmpx, tmpy, playerhG[tmpy][tmpx] ) == 0)
		    {
			pass = YES;
			break;
		    }
		}
		if( pass == YES )
	    continue;

		fitness = 0;
	        for( tmpx = low; tmpx <= high; tmpx++ )
		{
		    if( hlayerG[tmpy][tmpx] == net )
			fitness++;
		    else if( hlayerG[tmpy][tmpx] != 0 )
			break;
		}
		/* found - if same fitness go farther */
		if( tmpx > high && fitness >= oldfitness )
		{
		    jumpto = tmpy;
		    oldfitness = fitness;
		}
	    }
	    return( jumpto );
	}
	else  /* dir == UP */
	{
	    /*
	     *  see if there is a available row
	     */
	    oldfitness = 0;
	    jumpto = 0;
	    for( tmpy = y-1; tmpy >= 1; tmpy-- )
	    {
		if( vlayerG[tmpy][low] != 0 && vlayerG[tmpy][low] != net )
		    break; /* zzz recursion later */
		else if( vlayerG[tmpy][high] != 0 && vlayerG[tmpy][high] != net )
		    break;
		else if( vlayerG[tmpy][x] != 0 && vlayerG[tmpy][x] != net )
		    break;
		/*
		 *  don't block other pins
		 */
		pass = NO;
		for( tmpx = 1; tmpx <= num_colsG; tmpx++ )
		{
		    if( playerhG[tmpy][tmpx] > 0 &&
	         S_linkgroup( tmpx, tmpy, playerhG[tmpy][tmpx] ) == 0)
		    {
			pass = YES;
			break;
		    }
		}
		if( pass == YES )
	    continue;

		fitness = 0;
	        for( tmpx = low; tmpx <= high; tmpx++ )
		{
		    if( hlayerG[tmpy][tmpx] == net )
			fitness++;
		    else if( hlayerG[tmpy][tmpx] != 0 )
			break;
		}
		/* found - if same fitness go farther */
		if( tmpx > high && fitness >= oldfitness )
		{
		    jumpto = tmpy;
		    oldfitness = fitness;
		}
	    }
/*
if( jumpto > 0 )
{
print_debug ("canjump", "hlayerG", hlayerG, num_rows, num_cols, num_netsG);
print_debug ("canjump", "vlayerG", vlayerG, num_rows, num_cols, num_netsG);
}
*/
	    return( jumpto );
	}
    }
    else  /* LEFT or RIGHT */
    {
	if( dir == RIGHT )
	{
	    /*
	     *  see if there is a available row
	     */
	    oldfitness = 0;
	    jumpto = 0;
	    for( tmpx = x+1; tmpx <= num_colsG; tmpx++ )
	    {
		if( hlayerG[low][tmpx] != 0 && hlayerG[low][tmpx] != net )
		    break; /* zzz recursion later */
		else if( hlayerG[high][tmpx] != 0 && hlayerG[high][tmpx] != net )
		    break;
		else if( hlayerG[y][tmpx] != 0 && hlayerG[y][tmpx] != net )
		    break;

		/*
		 *  don't block other pins
		 */
		pass = NO;
		for( tmpy = 1; tmpy <= num_rowsG; tmpy++ )
		{
		    if( playervG[tmpy][tmpx] > 0 &&
	         S_linkgroup( tmpx, tmpy, playervG[tmpy][tmpx] ) == 0)
		    {
			pass = YES;
			break;
		    }
		}
		if( pass == YES )
	    continue;

		fitness = 0;
	        for( tmpy = low; tmpy <= high; tmpy++ )
		{
		    if( vlayerG[tmpy][tmpx] == net )
			fitness++;
		    else if( vlayerG[tmpy][tmpx] != 0 )
			break;
		}
		/* found - if same fitness go farther */
		if( tmpy > high && fitness >= oldfitness )
		{
		    jumpto = tmpx;
		    oldfitness = fitness;
		}
	    }
	    return( jumpto );
	}
	else  /* dir == LEFT */
	{
	    /*
	     *  see if there is a available col
	     */
	    oldfitness = 0;
	    jumpto = 0;
	    for( tmpx = x-1; tmpx >= 1; tmpx-- )
	    {
		if( hlayerG[low][tmpx] != 0 && hlayerG[low][tmpx] != net )
		    break; /* zzz recursion later */
		else if( hlayerG[high][tmpx] != 0 && hlayerG[high][tmpx] != net )
		    break;
		else if( hlayerG[y][tmpx] != 0 && hlayerG[y][tmpx] != net )
		    break;
		/*
		 *  don't block other pins
		 */
		pass = NO;
		for( tmpy = 1; tmpy <= num_rowsG; tmpy++ )
		{
		    if( playervG[tmpy][tmpx] > 0 &&
	         S_linkgroup( tmpx, tmpy, playervG[tmpy][tmpx] ) == 0)
		    {
			pass = YES;
			break;
		    }
		}
		if( pass == YES )
	    continue;

		fitness = 0;
	        for( tmpy = low; tmpy <= high; tmpy++ )
		{
		    if( vlayerG[tmpy][tmpx] == net )
			fitness++;
		    else if( vlayerG[tmpy][tmpx] != 0 )
			break;
		}
		/* found - if same fitness go farther */
		if( tmpy > high && fitness >= oldfitness )
		{
		    jumpto = tmpx;
		    oldfitness = fitness;
		}
	    }
	    return( jumpto );
	}
    }
}

/*
 *  make a real jump
 */
S_makejump( dir, x, y, net, low, high, jumpto )
int dir,
    x,
    y,
    net;
int low,
    high,
    jumpto;
{
    LINKPTR link;
    int numfloat,
	numcomp,
	priority,
	status;
    int tmpx,
        tmpy;
    void S_retlink();
    void S_jumplinks();
    void S_writelink();
    int S_trytmppath();
    void S_dumppath();
    void S_adjustlink();
    int S_findcomponents();
    int S_findpath();

    while( (link = net_arrayG[net].tmplist) != (LINKPTR)NULL )
    {
        net_arrayG[net].tmplist = link->netnext;
        S_retlink( link );
    }

    if( dir == DOWN || dir == UP )
    {
	S_jumplinks( dir, x, y, jumpto, net, low, high );
	if( x != low )
	    S_jumplinks( dir, low, y, jumpto, net, low, high );
	if( x != high )
	    S_jumplinks( dir, high, y, jumpto, net, low, high );
	/*
	 *  clear the channel
	 */
	for( tmpx = low; tmpx <= high; tmpx++ )
	{
	    if( hlayerG[y][tmpx] == net )
	        hlayerG[y][tmpx] = 0;
	    if( vlayerG[y][tmpx] == net )
	        vlayerG[y][tmpx] = 0;
	}
	for( tmpy = MIN( y, jumpto ); tmpy <= MAX( y, jumpto ); tmpy++ )
	{
	    vlayerG[tmpy][x] = 0;
	    vlayerG[tmpy][low] = 0;
	    vlayerG[tmpy][high] = 0;
	}
    }
    else /* dir == LEFT || dir == RIGHT */
    {
	S_jumplinks( dir, x, y, jumpto, net, low, high );
	if( y != low )
	    S_jumplinks( dir, x, low, jumpto, net, low, high );
	if( y != high )
	    S_jumplinks( dir, x, high, jumpto, net, low, high );
	/*
	 *  clear the channel
	 */
	for( tmpy = low; tmpy <= high; tmpy++ )
	{
	    if( hlayerG[tmpy][x] == net )
	        hlayerG[tmpy][x] = 0;
	    if( vlayerG[tmpy][x] == net )
	        vlayerG[tmpy][x] = 0;
	}
	for( tmpx = MIN( x, jumpto ); tmpx <= MAX( x, jumpto ); tmpx++ )
	{
	    hlayerG[y][tmpx] = 0;
	    hlayerG[low][tmpx] = 0;
	    hlayerG[high][tmpx] = 0;
	}
    }
    for( link = net_arrayG[net].path; link != (LINKPTR)NULL; link = link->netnext )
	S_writelink( link, net );

    if( S_trytmppath( net ) == NO )
    {
	S_dumppath( net );
	return ;
    }

    /*  clean up links  */
    S_adjustlink( net );

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
 *   not complete, links may overlap
 */
S_jumplinks( dir, x, y, jumpto, net, low, high )
int dir,
    x,
    y,
    jumpto,
    net;
int low,
    high;
{
    LINKLISTPTR linklist;
    LINKPTR link,
            tmplink;
    int mark = NO;
    int tmp; /* for debugging */
    void S_addlink();
    void S_dellink();

    if( dir == UP || dir == DOWN )
    {
        linklist = linklayerG[y][x];
        while( linklist != (LINKLISTPTR)NULL )
        {
	    if( linklist->link->net != net )
	    {
	        linklist = linklist->next;
    	continue;
	    }
	    else
	        link = linklist->link;
	    if( link->layer == HORIZ )  /* horiz */
	    {
		if( low <= link->x1 && link->x2 <= high )
	            S_addlink( link->layer, link->x1, jumpto,
				 link->x2, jumpto, net );
		else
		{
	            S_addlink( link->layer, link->x1, link->y1,
				 link->x2, link->y2, net );
	            mark = YES;
		}
	    }
	    else if( link->y1 == y && link->y2 != jumpto )
	        S_addlink( link->layer, link->x1, jumpto, link->x2, link->y2, net );
	    else if( link->y2 == y && link->y1 != jumpto )
	        S_addlink( link->layer, link->x1, link->y1, link->x2, jumpto, net );
	    linklist = linklist->next;
	    S_dellink( link );
        }
	if( mark == YES || playervG[y][x] == net )
	    S_addlink( VERT, x, y, x, jumpto, net );
    }
    else /* dir == LEFT || dir == RIGHT */
    {
        linklist = linklayerG[y][x];
        while( linklist != (LINKLISTPTR)NULL )
        {
	    if( linklist->link->net != net )
	    {
	        linklist = linklist->next;
    	continue;
	    }
	    else
	        link = linklist->link;
	    if( link->layer == VERT )  /* VERT */
	    {
		if( low <= link->y1 && link->y2 <= high )
	            S_addlink( link->layer, jumpto, link->y1, 
				 jumpto, link->y2, net );
		else
		{
	            S_addlink( link->layer, link->x1, link->y1,
				 link->x2, link->y2, net );
	            mark = YES;
		}
	    }
	    else if( link->x1 == x && link->x2 != jumpto )
	        S_addlink( link->layer, jumpto, link->y1, link->x2, link->y2, net );
	    else if( link->x2 == x && link->x1 != jumpto )
	        S_addlink( link->layer, link->x1, link->y1, jumpto, link->y2, net );
	    linklist = linklist->next;
	    S_dellink( link );
        }
	if( mark == YES || playerhG[y][x] == net )
	    S_addlink( HORIZ, x, y, jumpto, y, net );
    }
}


/*
 *      ------                    -------------
 *           |                                |
 *           ------------                     ------
 *           ^                         ^
 *           |			       |
 */
S_cansidejump( dir, x, y, net, low, high )
int dir;
int x,
    y;
int net;
{
    int newx,
	newy;
    int tmpx,
	tmpy,
	jumpto;
    int pass;
    int fitness,
        oldfitness;
    int S_linkgroup();

    if( dir == LEFT || dir == RIGHT )
    {
	/*
	 *  see if there is a available row
	 */
	oldfitness = - INFINITY;
	jumpto = 0;
	for( tmpy = y+1; tmpy <= num_rowsG; tmpy++ )
	{
	    if( vlayerG[tmpy][low] != 0 && vlayerG[tmpy][low] != net )
		break; /* zzz recursion later */
	    else if( vlayerG[tmpy][high] != 0 && vlayerG[tmpy][high] != net )
		break;

	    /*
	     *  don't block other pins
	     */
	    pass = NO;
	    for( tmpx = 1; tmpx <= num_colsG; tmpx++ )
	    {
		if( playerhG[tmpy][tmpx] > 0 &&
	          S_linkgroup( tmpx, tmpy, playerhG[tmpy][tmpx] ) == 0)
		{
	  	    pass = YES;
		    break;
		}
	    }
	    if( pass == YES )
	continue;

	    fitness = y - tmpy;  /* to go less */
	    for( tmpx = low; tmpx <= high; tmpx++ )
	    {
		if( hlayerG[tmpy][tmpx] == net )
		    fitness += 10;
		else if( hlayerG[tmpy][tmpx] != 0 )
		    break;
	    }
	    /* found - if same fitness go less */
	    if( tmpx > high && fitness > oldfitness )
	    {
		jumpto = tmpy;
		oldfitness = fitness;
	    }
	}
	for( tmpy = y-1; tmpy >= 1; tmpy-- )
	{
	    if( vlayerG[tmpy][low] != 0 && vlayerG[tmpy][low] != net )
		break; /* zzz recursion later */
	    else if( vlayerG[tmpy][high] != 0 && vlayerG[tmpy][high] != net )
		break;

	    /*
	     *  don't block other pins
	     */
	    pass = NO;
	    for( tmpx = 1; tmpx <= num_colsG; tmpx++ )
	    {
		if( playerhG[tmpy][tmpx] > 0 &&
	         S_linkgroup( tmpx, tmpy, playerhG[tmpy][tmpx] ) == 0)
		{
	  	    pass = YES;
		    break;
		}
	    }
	    if( pass == YES )
	continue;

	    fitness = tmpy - y;  /* to go less */
	    for( tmpx = low; tmpx <= high; tmpx++ )
	    {
		if( hlayerG[tmpy][tmpx] == net )
		    fitness += 10;
		else if( hlayerG[tmpy][tmpx] != 0 )
		    break;
	    }
	    /* found - if same fitness go less */
	    if( tmpx > high && fitness > oldfitness )
	    {
		jumpto = tmpy;
		oldfitness = fitness;
	    }
	}
	return( jumpto );
    }
    else /* dir == UP || dir == DOWN */
    {
	/*
	 *  see if there is a available row
	 */
	oldfitness = - INFINITY;
	jumpto = 0;
	for( tmpx = x+1; tmpx <= num_colsG; tmpx++ )
	{
	    if( hlayerG[low][tmpx] != 0 && hlayerG[low][tmpx] != net )
		break; /* zzz recursion later */
	    else if( hlayerG[high][tmpx] != 0 && hlayerG[high][tmpx] != net )
		break;

	    /*
	     *  don't block other pins
	     */
	    pass = NO;
	    for( tmpy = 1; tmpy <= num_rowsG; tmpy++ )
	    {
		if( playervG[tmpy][tmpx] > 0 &&
	         S_linkgroup( tmpx, tmpy, playervG[tmpy][tmpx] ) == 0)
		{
	  	    pass = YES;
		    break;
		}
	    }
	    if( pass == YES )
	continue;

	    fitness = x - tmpx;  /* to go less */
	    for( tmpy = low; tmpy <= high; tmpy++ )
	    {
		if( vlayerG[tmpy][tmpx] == net )
		    fitness += 10;
		else if( vlayerG[tmpy][tmpx] != 0 )
		    break;
	    }
	    /* found - if same fitness go less */
	    if( tmpy > high && fitness > oldfitness )
	    {
		jumpto = tmpx;
		oldfitness = fitness;
	    }
	}
	for( tmpx = x-1; tmpx >= 1; tmpx-- )
	{
	    if( hlayerG[low][tmpx] != 0 && hlayerG[low][tmpx] != net )
		break; /* zzz recursion later */
	    else if( hlayerG[high][tmpx] != 0 && hlayerG[high][tmpx] != net )
		break;

	    /*
	     *  don't block other pins
	     */
	    pass = NO;
	    for( tmpy = 1; tmpy <= num_rowsG; tmpy++ )
	    {
		if( playervG[tmpy][tmpx] > 0 &&
	         S_linkgroup( tmpx, tmpy, playervG[tmpy][tmpx] ) == 0)
		{
	  	    pass = YES;
		    break;
		}
	    }
	    if( pass == YES )
	continue;

	    fitness = tmpx - x;  /* to go less */
	    for( tmpy = low; tmpy <= high; tmpy++ )
	    {
		if( vlayerG[tmpy][tmpx] == net )
		    fitness += 10;
		else if( vlayerG[tmpy][tmpx] != 0 )
		    break;
	    }
	    /* found - if same fitness go less */
	    if( tmpy > high && fitness > oldfitness )
	    {
		jumpto = tmpx;
		oldfitness = fitness;
	    }
	}
	return( jumpto );
    }
}

/*
 *  return YES, running vetically on horiz_layer or vice versa
 */
int S_wrongdir( x, y, net )
int x,
    y,
    net;
{
    LINKLISTPTR linklist;
    LINKPTR tmplink;

    for( linklist = linklayerG[y][x]; linklist != (LINKLISTPTR)NULL;
	linklist = linklist->next )
    {
	if( linklist->link->net == net )
	{
	    tmplink = linklist->link;
	    if( tmplink->layer == HORIZ && tmplink->y1 != tmplink->y2 )
		return( YES );
	    if( tmplink->layer == VERT && tmplink->x1 != tmplink->x2 )
		return( YES );
        }
    }
    return( NO );
}
