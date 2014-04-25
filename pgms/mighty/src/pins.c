#ifndef lint
static char SccsId[] = "@(#) pins.c version 6.2 12/27/90" ;
#endif

#include "mighty.h"
#include <yalecad/message.h>
extern int Longch;

int bkcycleG = NO;
int LIMCOLS = 70;

int STEPSIZE = 35; 	/*  can be increased in S_guidepin  */
#define DELSTEP 5

#define INFINITELOOP  1000
/* zzz 3/18'86
#define BIAS 10
#define VSLOPE  50
#define VCGSLOPE 500
#define HSLOPE  50000
int PREASSIGN = 500000;
*/
#define BIAS 10
#define VSLOPE   50
#define VCGSLOPE 2000
#define CYCVCGSLOPE 5000
#define HSLOPE  50000
int PREASSIGN = 500000;

#define HALFCOL 2
#define FULLCOL 4

int left_start;
int left_numtr;
int right_start;
int right_numtr;
int *bother = NULL;
int *lftop = NULL;
int *lfbot = NULL;

/*
 *  Pseudo pins are made.
 *  This is to give guide in routing long channels
 *  or highly iregular shaped channels.
 *  Also used to route on third layer for 2.5 layer router
 */

extern int **costG;

/* layer3 is used to keep track of columns to add pseudos */
/* static PIN_LISTPTR *layer3G ;  changed to Global */

S_addguides()
/*
 *  This routine is called if num_colsG > LIMCOLS
 */
{
    int m, /* number of rows( crossing nets ) */
	n; /* number of cols( tracks ) */
    int *cross;
    int *distloc,  /* If there is less number of pins, more flexible */
	*distacc;  /* Lookup table of distances */
    int *density;
    int i,
	j,
	col,
	fromcol,
	tocol,
	prevcol;
    int maxlevel;
    int maxcol,    /* column with max density */
	starttr,   /* first available track */
	numpin;
    int loopCount ; /* protect against infinite loops */
    int left_pins = 0,
	right_pins = 0;
    int *S_allocatevector();
    int *S_finddensity();
    int **S_structure();
    void S_resetstructure();
    int *S_assign();
    BOOL *processed ;/* processed whether column has been processed */
    PIN_LISTPTR thirdpins ;
    PIN_LISTPTR curpin ;

    if( num_leftG > 0 ) left_pins = YES;
    if( num_rightG > 0 ) right_pins = YES;

    /*
     *  If wide channel, increase STEPSIZE
     */
    STEPSIZE = MAX(3*num_rowsG/2, STEPSIZE);
    LIMCOLS = MAX(LIMCOLS, 3*STEPSIZE/2);

    /*
     *  Compensate the distance according to the pin density
     *  allocate distance compensating vetor
     */
    distloc = S_allocatevector( num_colsG );
    distacc = S_allocatevector( num_colsG );

    for( i = 1; i <= num_colsG; i++ ) {
	/*
	 *  count number of pins on each column
	 */
	numpin = 0;
	for( j = 1; j <= num_rowsG; j++ ){
	    if( playerhG[j][i] > 0 ) numpin++;
	    if( playervG[j][i] > 0 ) numpin++;
	}
	if( numpin == 0 ){
	    distloc[i] = FULLCOL;
	} else if( numpin == 1 ){
	    distloc[i] = HALFCOL;
	} else {
	    distloc[i] = 0;
	}
    }


    /*
     *  allocate and find density
     */
    density = S_finddensity();

    /*  set defaults  */
    maxcol = 1;
    loopCount = 0 ;
    processed = (BOOL *) Ysafe_calloc( num_colsG+1,sizeof(BOOL) ) ;
    if( two5pinsG ){
	/* now note which columns have layer 3 pins and count number */
	prevcol = 0;
	for( thirdpins = two5pinsG; thirdpins; thirdpins = thirdpins->next ){
	    if( prevcol != thirdpins->pin->x ){
		/* save first pin at this column */
		/* remember thirdpins is ordered increasing x decreasing y */
		layer3G[thirdpins->pin->x] = thirdpins ;
	    }
	    prevcol = thirdpins->pin->x ;
	}
    }
    thirdpins = two5pinsG ; /* reinitialize */
    /*
     *  Main loop begins
     */
    col = 0;
    for( ;; ) {
	if( ++loopCount > INFINITELOOP ){
	    M( ERRMSG, "add_guides","Mighty couldn't resolve cycle.\n" ) ;
	    M( MSG, NULL,"You might try again with -maze option.\n") ;
	    YexitPgm(57) ;
	}
	prevcol = col;

	/*
	    this part of the code calculates what column to add pseudopins
	*/

	if( col == 0 && Longch ) {
	    maxcol = col = S_maxdencol( density, 1, num_colsG );

	} else if( col <= maxcol && col > LIMCOLS && Longch ) {
	    fromcol = col - STEPSIZE - DELSTEP;
	    tocol = col - STEPSIZE + DELSTEP;
	    col = S_maxdencol( density, fromcol, tocol );

	} else if( left_pins == YES ) {
	    left_pins = NO;
	    col = 1;
	} else if( col < num_colsG - LIMCOLS && 
	    maxcol + LIMCOLS < num_colsG&& Longch ) {
	    fromcol = MAX(maxcol, col) + STEPSIZE - DELSTEP;
	    tocol = fromcol + DELSTEP + DELSTEP;
	    col = S_maxdencol( density, fromcol, tocol );
	} else if( right_pins == YES ) {
	    right_pins = NO;
	    col = num_colsG;

	} else if( thirdpins ){
	    /* see if this column has been processed */
	    if( processed[thirdpins->pin->x] ){
		thirdpins = thirdpins->next ;
		continue ;
	    }
	    col = thirdpins->pin->x ; 
	} else {
	    break;
	}

	/* avoid processing column twice */
	if( processed[col] ){
	    continue ;
	}

	/*  calculate accumulated compensated distance  */
	distacc[col] = distloc[col]/2;
	for( i = col + 1; i <= num_colsG; i++ )
	    distacc[i] = distacc[i-1] + distloc[i] + 1;
	for( i = col - 1; i >= 1; i-- )
	    distacc[i] = distacc[i+1] + distloc[i] + 1;

	/*
	 *  find number m of nets crossing col, and
	 *  number n of available tracks on the column.
	 */
	if( col == 1 ) {
            S_resetmarked();
            m = num_leftG;
            n = S_findtracks( 2, &starttr );
	    col = 1;
	    left_pins = NO;

	    /*  save for post processing  */
	    left_start = starttr;
	    left_numtr = n;

            for( i = 1; i <= num_leftG; i++ ){
		net_arrayG[ leftG[i] ].marked = YES;
	    }
	} else if( col == num_colsG ) {
            S_resetmarked();
            m = num_rightG;
            n = S_findtracks( num_colsG-1, &starttr );
	    col = num_colsG;
	    right_pins = NO;

	    /*  save for post processing  */
	    right_start = starttr;
	    right_numtr = n;

            for( i = 1; i <= num_rightG; i++ ){
		net_arrayG[ rightG[i] ].marked = YES;
	    }
	} else {
            m = S_findnets( col );
	    /*
	     * If more crossing nets than tracks, exit.
	     */
	    if( m > num_rowsG - 2 ) {
		sprintf( YmsgG, "crossing nets = %d, tracks = %d\n",
		    m, num_rowsG );
		M( ERRMSG, "S_addguides", YmsgG ) ;
		fprintf(output_fileG, "failed\n");
		YexitPgm( 88 );
	    }

            n = S_findtracks( col, &starttr );
	    /*
	     *  If non convex(n=0), or blocked area on the col, continue
	     */
	    if( m > n ) {
		sprintf( YmsgG, "m = %d, n = %d at col = %d\n",m,n,col );
		M( MSG, "S_addguides", YmsgG ) ;
		processed[col] = TRUE ;
		continue;
	    }
	}


	/*
	 *  calculate level
	 */
        S_cleargraph();

        S_makegraph(1,num_colsG);


        level_graph(col);
	maxlevel = S_maplevels();

	/*
	 * allocate for linear assignments
	 */
	if( costG == (int **)NULL ){
            costG = S_structure(num_netsG, num_rowsG);
	} else {
	    S_resetstructure(num_netsG,num_rowsG);
	}

	if( col == maxcol ) {
            S_setcosts( distacc, starttr, m, n, 
		maxlevel, 1, num_colsG, col );
	} else if( col < prevcol ) {
            S_setcosts( distacc, starttr, m, n,
		maxlevel, 1, prevcol, col );
	} else if( col > prevcol ) {
            S_setcosts( distacc, starttr, m, n,
		maxlevel, MAX(prevcol, maxcol), num_colsG, col );
	} else {
	    YexitPgm( 85 );
	}


	cross= S_assign( m, n );

	 if( debugG ){
	    S_printresults( m, n );
	}
	

	/*
	 *  assign i-th crossing net on track cross[i]
	 */
	if( two5pinsG ){
	    if( layer3G[col] ){ 
		/* two and 1/2 layer column needs to update third layer pins */
		S_update_layer3( cross, col, starttr );
	    } else {
		/* normal case add all pins */
		S_addpins( cross, col, starttr, TEMP );
	    }
	} else {
	    S_addpins( cross, col, starttr, TEMP );
	}
	processed[col] = TRUE ;

    } /* end for loop */

    Ysafe_free( processed ) ;
} /* end S_addguides */


S_findnets( col )
int col;
/*
 *  set marked for the nets crossing x = col or having a pin on x = col
 *  returns the number of such nets
 *  NOTE : Include the nets which start or stop at col.
 *         But nets with lateral distance <= 1 would be omitted.
 *  * Also mark pins on layer 3 if requested.
 */
{
    PIN_LISTPTR pin3 ;   /* pointer to third layer record */
    PINPTR cpin;
    int i, j;
    int xleft,
	xright;	/* flag indicating the existence of the pin of a net
		   on the left or right side of col */
    int numcross = 0;

    S_resetmarked();

    for( i = 1; i <= num_netsG; i++ ){
	if( (cpin = net_arrayG[i].pin) == (PINPTR)NULL ){
	    continue;
	}

	xleft = xright = cpin->x;
	for( cpin = cpin->next; cpin ; cpin = cpin->next ){
	    xleft = MIN( xleft, cpin->x );
	    xright = MAX( xright, cpin->x );

	    /* if a pin is on the col on hlayerG, add the net */
	    if( cpin->x == col && cpin->layer == HORIZ ) {
		/* fake */
		xleft = 1;
		xright = num_colsG;
	    }
	}
	/*  See if right or left nets  */
	if( net_arrayG[i].left == YES )
	    xleft = 1;
	if( net_arrayG[i].right == YES )
	    xright = num_colsG;

	if( xleft <= col && xright >= col && xright - xleft > 1 ) {
		net_arrayG[i].marked = YES;
		numcross++;
	}

    } /* end for loop on nets */

    /* we need to mark all nets that have a third layer in this column */
    if( two5pinsG && (pin3 = layer3G[col]) ){
	if( net_arrayG[pin3->net].marked == NO ){
	    net_arrayG[pin3->net].marked = YES;
	    numcross++;
	}
	/* now check possible second pin remember pins are sorted by col row */
	pin3 = pin3->next ;
	if( pin3 && pin3->pin->x == col ){
	    if( net_arrayG[pin3->net].marked == NO ){
		net_arrayG[pin3->net].marked = YES;
		numcross++;
	    }
	}
    }
    return( numcross );
}


S_findtracks( col, starttrp )
int col;
int *starttrp;
/*
 *  find the number of available tracks at x = col
 *  First implementation is for CONVEX channels
 */
{
    LINKPTR bound;
    int mintr;  /* first available track */
    int j;

    mintr = 0;
    for( bound = bounding_boxG; bound != (LINKPTR)NULL; bound = bound->netnext )
    {
	if( MIN(bound->x1, bound->x2) <= col &&
	    MAX(bound->x1, bound->x2) >= col )
	{
	    if( bound->x1 < bound->x2 )
	    {
    		/*  If non-convex routing area, no pseudo pins.  */
		if( mintr != 0 )
    		    return( 0 );
		mintr = bound->y1;
		break;
	    }
	}
    }

    while( (hlayerG[mintr][col] > num_netsG || vlayerG[mintr][col] > num_netsG) &&
	mintr < num_rowsG )
	mintr++;

    *starttrp = mintr;

    for( j = mintr; ; j++ )
    {
	if( hlayerG[j][col] > num_netsG || vlayerG[j][col] > num_netsG ||
	    j >= num_rowsG )
            break;
    }
    return( j - mintr );
}

debug_cross( cross )
int cross[];
{
    int i ; 

    /* print starting column */
    printf( "number of marked nets:\n" ) ;
    /* count number of marked pins */
    for( i = 1; i <= num_netsG; i++ ){
	if( net_arrayG[i].marked ){
	    printf( "%d ", i ) ;
	}
    }
    printf( "\n" ) ;

    printf( "cross array:\n" ) ;
    for( i = 1; i <= num_rowsG; i++ ){
	printf( "%d ", cross[i] ) ;
    }
    printf( "\n" ) ;
}


S_addpins( cross, col, starttr, pintype )
int cross[];
int col,
    starttr;
int pintype;
{
    PINPTR newpin;
    int i;
    int index = 0;
    PINPTR S_getpin();

    /* correct track is ( cross[index] + starttr - 1 ) */
    starttr--;

    if( debugG ){
	debug_cross( cross ) ;
    }

    for( i = 1; i <= num_netsG; i++ )
    {
	if( net_arrayG[i].marked == NO ){
	    continue;
	}
	
	index++;
	newpin = S_getpin();
	newpin->type = pintype;
	newpin->x = col;
	newpin->y = cross[index] + starttr;
	newpin->layer = HORIZ;
        newpin->next = net_arrayG[i].pin;
	net_arrayG[i].pin = newpin;
	if( debugG ){
	    printf("pin at %d %d for %d\n", 
		newpin->x, newpin->y, number_to_name(i));
	}
        playerhG[newpin->y][newpin->x] = i;
    }
} /* end S_addpins */

/* update the positions of layer 3 pins */
S_update_layer3( cross, col, starttr )
int cross[];
int col, starttr;
{
    PINPTR pin1, pin2 ;      /* pin record for two pins in column */
    PIN_LISTPTR  nextpin ;   /* top third layer pin in channel if exists*/
    PIN_LISTPTR  lay3 ;      /* pointer to current 3 pin */
    int net1, net2 ;         /* net name of pins */
    int y1, y2 ;             /* track locations of pin1 and pin2 */
    int index1, index2 ;     /* index into cross reference array */
    int i ;
    PINPTR S_getpin();

    /* correct track is ( cross[net] + starttr - 1 ) */
    starttr--;

    /* fix up cross index for nets - index is ordered by marked nets */
    /* marked field will now have correct index in cross for net */
    index1 = 0 ;
    for( i = 1; i <= num_netsG; i++ ){
	if( net_arrayG[i].marked == YES ){
	    net_arrayG[i].marked = ++index1 ;
	}
    }

    if( debugG ){
	debug_cross( cross ) ;
    }

    /* see if two third layer pins exist in this column */
    /* pins must be on correct side of channel - more important */
    /* than being on right track */
    lay3 = layer3G[col] ;
    pin1 = lay3->pin ;
    net1 = lay3->net ;
    index1 = net_arrayG[net1].marked ;
    nextpin = lay3->next ;
    if( nextpin && nextpin->pin->x == col ){
	/* need to worry about pins being on the correct side */
	net2 = nextpin->net ;
	pin2 = nextpin->pin ;
	index2 = net_arrayG[net2].marked ;
	if( cross[index1] > cross[index2] ){
	    /* need to reverse positions */
	    y1 = cross[index1] + starttr ;
	    y2 = cross[index2] + starttr ;
	} else {
	    y1 = cross[index2] + starttr ;
	    y2 = cross[index1] + starttr ;
	}

	/* now output 2nd pin into channel */
	pin2->type = THREE ;
	pin2->x = col;
	pin2->y = y2 ;
	pin2->layer = HORIZ;
	if( debugG ){
	    printf("pin at %d %d for %d\n", 
		pin2->x, pin2->y, number_to_name(net2));
	}
	playerhG[pin2->y][pin2->x] = net2 ;

    } else {
	y1 = cross[index1] + starttr ;
    }

    if( pin1->x != col || net_arrayG[net1].marked == NO ){
	printf( "Problem here \n" ) ;
	return;
    }
    pin1->type = THREE ;
    pin1->x = col;
    pin1->y = y1 ;
    pin1->layer = HORIZ;
    if( debugG ){
	printf("pin at %d %d for %d\n", 
	    pin1->x, pin1->y, number_to_name(net1));
    }
    playerhG[pin1->y][pin1->x] = net1 ;

} /* end S_update_layer3 */


int S_maplevels()
/*
 *  map levels ( 1 to maxlevel to 1 to n )
 */
{
    int *S_allocatevector();
    int fromtop;
    int frombot;
    int i;
    int maxlevel = 0;  /* max number of level */

    for( i = 1; i <= num_netsG; i++ )
	maxlevel = MAX( maxlevel, net_arrayG[i].level_from_top );

    if( lftop == NULL )
    {
        lftop = S_allocatevector( num_netsG );
        lfbot = S_allocatevector( num_netsG );
    }
    else
    {
	for( i = 1; i <= num_netsG; i++ )
	    lftop[i] = lfbot[i] = 0;
    }

    for( i = 1; i <= num_netsG; i++ )
    {
	if( net_arrayG[i].marked == NO )
    continue;
	fromtop = net_arrayG[i].level_from_top;
	frombot = net_arrayG[i].level_from_bottom;
	lftop[fromtop] = 1;
	lfbot[frombot] = 1;
    }
    for( i = 2; i <= maxlevel; i++ )
    {
	lftop[i] += lftop[i-1];
	lfbot[i] += lfbot[i-1];
    }
    return( maxlevel );
}


S_setcosts( distacc, starttr, m, n, maxlevel, fromcol, tocol, col )
int *distacc;
int starttr,
    m,
    n;
int maxlevel;
int fromcol,
    tocol,
    col;
/*
 *  fill the costG matrix
 *  try not to assign any pins on the first and last two tracks
 *  by giving high costG.
 */
{
    PINPTR cpin;
    int *S_allocatevector();
    int lateraldist,
        slope,
	track;
    int toplevel,
	botlevel;  		/* top/bot most track to avoid VCV  */
    int vcgslope;
    int ideal;
    int i;
    int j = 0;
    int k;
    int tmp;
    int tmpcol,
	row;

    /*  set parameter  */
    if( bkcycleG )
        vcgslope = CYCVCGSLOPE;
    else
        vcgslope = VCGSLOPE;

    /*
     *  HIGH costs due to level graph
     */
    for( i = 1; i <= num_netsG; i++ )
    {
	if( net_arrayG[i].marked == NO )
    continue;
	j++;

        toplevel = lftop[net_arrayG[i].level_from_top];
        botlevel = lftop[net_arrayG[i].level_from_bottom];
	if( maxlevel > 1 )
	{
	  k= net_arrayG[i].pin->y;
	  ideal=k - starttr +1;
  	  for( cpin = net_arrayG[i].pin; cpin; cpin = cpin->next ) {
	    if (cpin->type==THREE)
	      continue;
	    if ( ABS( k - cpin->y ) > 1 ) {
	       ideal =n/2;
	       break;
	       }
	    else {
	       ideal=cpin->y -starttr + 1;
	       }
	    }
          if (debugG) {
            for(cpin=net_arrayG[i].pin;cpin!=(PINPTR)NULL;cpin=cpin->next)
              printf("%d pin %d at %d,%d \n",
		cpin->type,i,cpin->x,cpin->y);
	      printf("ideal=%d\n",ideal);
	       } 

	/* This has the effect of putting psuedos in first track */
	/*    so comment it out for now (2.5's in vcg ?) */
	/* 1 to maxlevel is mapped on 1 to n */
	/*       ideal = ((n - 1) * (net_arrayG[i].level_from_top
	           - net_arrayG[i].level_from_bottom + maxlevel)/2
	           + maxlevel - n)/(maxlevel - 1);*/
	}
	else
	  {
	  k= net_arrayG[i].pin->y;
	  ideal=k - starttr +1;
  	  for( cpin = net_arrayG[i].pin; cpin; cpin = cpin->next ) {
	    if (cpin->type==THREE)
	      continue;
	    if ( ABS( k - cpin->y ) > 1 ) {
	       ideal =n/2;
	       break;
	       }
	    else {
	       ideal=cpin->y -starttr + 1;
	       }
	    }
          if (debugG) {
            for(cpin=net_arrayG[i].pin;cpin!=(PINPTR)NULL;cpin=cpin->next)
              printf("%d pin %d at %d,%d \n",
		cpin->type,i,cpin->x,cpin->y);
	      printf("ideal=%d\n",ideal);
	       }
          }

	
        /* 1 to maxlevel is mapped on 1 to n */
	if( toplevel + botlevel <= n + 1 )
	{
	    slope = 5 * vcgslope/BIAS;

	    if( ideal < toplevel )
	        ideal = toplevel;
	    if( ideal > n + 1 - botlevel )
	        ideal = n + 1 - botlevel;
            if(debugG)
	      printf("n-%d top-%d bot-%d newideal=%d\n",
	        n,toplevel,botlevel,ideal);

	    for( k = toplevel - 1; k >= 1; k-- )
	        costG[j][k] += slope;

	    for( k = 1; k < botlevel; k++ )
	        costG[j][n-k+1] += slope;

	}

	slope = vcgslope/BIAS;
	for( k = 1; k <= n; k++ )
	{
	    costG[j][k] += ABS(ideal - k) * slope;
	}

	/* Not to use the topmost and botmost tracks */
	/* add HIGHSOLPE/BIAS */
        (costG[j][2]) += slope;
        (costG[j][n-1]) += slope;
	/* add two times HIGHSOLPE/BIAS */ 
	slope += slope;
        (costG[j][1]) += slope;
        (costG[j][n]) += slope; 
    }


    if( bother == NULL )
	bother = S_allocatevector( num_rowsG );
    else
	for( k = 1; k <= num_rowsG; k++ )
	    bother[k] = 0;

    /*
     *  penalize horizontal violation - like channel routers
     *  fromcol != 1      => check leftward
     *  tocol != num_colsG => check rightward
     *  If near the edges, it may be better to check in both dir.
     */

    if( fromcol != 1 )
    {
        for( k = 1; k <= n; k++ )
        {
	    row = starttr + k - 1;
	    for( tmpcol = col-1; tmpcol >= fromcol; tmpcol-- )
	    {
	        if( (tmp = hlayerG[row][tmpcol]) != 0 )
		break;
	    }
	   if( tmp == 0 )
	        tmp = playerhG[row][fromcol];
	    bother[k] = tmp;
        }
    }
    else if( tocol != num_colsG )
    {
        for( k = 1; k <= n; k++ )
        {
	    row = starttr + k - 1;
	    for( tmpcol = col+1; tmpcol <= tocol; tmpcol++ )
	    {
	        if( (tmp = hlayerG[row][tmpcol]) != 0 )
		break;
	    }
	    if( tmp == 0 )
	        tmp = playerhG[row][fromcol];
	    bother[k] = tmp;
        }
    }

/*
    if (debugG) {
      printf("col = %d\n", col );
      for( k = 1; k <= n; k ++ )
	printf("%d bother %d\n", k, bother[k]);
      }
*/

/*
 if (debugG) {
      printf("high costs\n");
      for (k=1; k<=m ; k++) {
        for (j=1; j<=n ; j++) {
          printf("%6d ",costG[k][j]);
          }
	printf("\n");
        }
      }
 */

    /*
     *  MID and LOW costGs due to distance
     */
    j = 0;
    for( i = 1; i <= num_netsG; i++ )
    {
	if( net_arrayG[i].marked == NO )
    continue;
	j++;
	for( cpin = net_arrayG[i].pin; cpin != (PINPTR)NULL; cpin = cpin->next )
	{
	    /*  consider only the pins inside proper area */
	    if( cpin->x < fromcol || cpin->x > tocol )
	continue;

	    lateraldist = distacc[cpin->x];

	    if( cpin->layer == HORIZ &&
	        starttr <= cpin->y && cpin->y <= starttr + n - 1 )
	    {
		/* intersection : high slope */
		slope = HSLOPE/( BIAS + lateraldist);
	    }
	    else
	    {
		slope = VSLOPE/( BIAS + lateraldist);
	    }

	    for( k = 1; k <= n; k++ )
	    {
	    	track = starttr + k - 1;
		costG[j][k] +=  slope *(1+ ABS(track - cpin->y));
	    }
	}
        
/*
  if (debugG) {
    printf("distan costs\n");
    for (k=1; k<=m ; k++) {
      for (debugG=1; debugG<=n ; debugG++) {
	printf("%6d ",costG[k][debugG]);
        }
	printf("\n");
      }
    }
 */

	/*
         *  To avoid partial overlap, add costG
         */
	slope = 5 * vcgslope/ BIAS;
        if( fromcol != 1 && net_arrayG[i].colleft > fromcol )
	{
	  for( k = 1; k <= n; k++ )
	  {
	    if( bother[k] > num_netsG )
	    	    costG[j][k] += slope;
	    else if( bother[k] > 0 && net_arrayG[bother[k]].marked == NO &&
		net_arrayG[i].colleft <= net_arrayG[bother[k]].colright )
	      costG[j][k] += slope;
	  }
	}
        else if( tocol != num_colsG && net_arrayG[i].colright < tocol )
	{
	  for( k = 1; k <= n; k++ )
	  {
	    if( bother[k] > num_netsG )
	    	    costG[j][k] += slope;
	    else if( bother[k] > 0 && net_arrayG[bother[k]].marked == NO &&
		net_arrayG[i].colright >= net_arrayG[bother[k]].colleft )
	      costG[j][k] += slope;
	  }
        }

/*
  if (debugG) {
    printf("overlap costs\n");
    for (k=1; k<=m ; k++) {
      for (debugG=1; debugG<=n ; debugG++) {
	printf("%6d ",costG[k][debugG]);
        }
	printf("\n");
      }
    }
 */

	/*
	 *  if there is a pin on the col on HORIZ layer,
	 *  preassign the net on the track.
	 */
	if( (cpin = net_arrayG[i].pin) == (PINPTR)NULL )
    continue;
	for( cpin = cpin->next; cpin != (PINPTR)NULL; cpin = cpin->next )
	{
	    if( cpin->x == col && cpin->layer == HORIZ )
	    {
		/* penalize using k-th col except net i (j)  */
	    	k = cpin->y - starttr + 1;
		for( tmp = 1; tmp < j; tmp++ )
		    costG[tmp][k] += PREASSIGN;
		for( tmp = j+1; tmp <= m; tmp++ )
		    costG[tmp][k] += PREASSIGN;
	    }
	}
    }

/*
  if (debugG) {
    printf("final costs\n");
    for (k=1; k<=m ; k++) {
      for (j=1; j<=n ; j++) {
	printf("%6d ",costG[k][j]);
        }
	printf("\n");
      }
    }
 */

}


S_addedges(col)
int col;
/*
 *  insert edges to VCG to represent new constraints due to new pins
 */
{
    int lowernet;
    int uppernet;
    int row;
    /*
     *  insert graph edges caused by pins on hlayerG
     */
	uppernet = 0;

	for( row = 1; row <= num_rowsG; row++ )
	{
	    /* if outside of channel, reset */
	    if( hlayerG[row][col] > num_netsG )
	    {
		uppernet = 0;
	    }
	    if( playerhG[row][col] > 0 )
	    {
		if( uppernet != 0 )
		{
		    lowernet = playerhG[row][col];
	            insert_edge (uppernet, lowernet, num_netsG, col);
		    uppernet = lowernet;
		}
		else
		    uppernet = playerhG[row][col];
	    }
	}
}


S_rmpins()
/*
 *  Before metal maximization, remove pseudo pins
 */
{
    PINPTR cpin;
    PINPTR ppin;
    int i;

    for( i = 1; i <= num_netsG; i++ )
    {
    	while( (cpin = net_arrayG[i].pin) != (PINPTR)NULL && cpin->type == TEMP )
    	{
	    net_arrayG[i].pin = cpin->next;

	    if( cpin->layer == HORIZ )
		playerhG[cpin->y][cpin->x] = 0;
	    else
		playervG[cpin->y][cpin->x] = 0;
	    S_retpin( cpin );
	}

if(!( net_arrayG[i].pin ) ){
    sprintf(YmsgG,"i = %d net = %d has no fixed pin\n", i, 
	number_to_name(i));
    M( WARNMSG, "rmpins", YmsgG ) ;

}
if(!( net_arrayG[i].pin ) )
    continue;
	ppin = net_arrayG[i].pin;

        for( cpin = ppin->next; cpin != (PINPTR)NULL;
	     cpin = cpin->next )
	{
	    if( cpin->type == TEMP )
	    {
		ppin->next = cpin->next;

	        if( cpin->layer == HORIZ )
		    playerhG[cpin->y][cpin->x] = 0;
	        else
		    playervG[cpin->y][cpin->x] = 0;

	sprintf(YmsgG, "tmppin rmed at (%d, %d)\n", cpin->x, cpin->y);
	M( MSG, NULL, YmsgG ) ;
		S_retpin( cpin );
		cpin = ppin;
	    }
	    else
	        ppin = cpin;
	}
    }
}

S_rmsidepins(i, row, col)
int i; /* net */
/*
 *  same as S_rmpins, but for only one net
 *  rm except the one at row
 *  mark as X after removal of pins
 */
{
    PINPTR cpin;
    PINPTR ppin;

    	while( (cpin = net_arrayG[i].pin) != (PINPTR)NULL && cpin->type == TEMP &&
	    cpin->x == col && cpin->y != row )
    	{
	    net_arrayG[i].pin = cpin->next;

	    if( cpin->layer == HORIZ )
		playerhG[cpin->y][cpin->x] = 0;
	    else
		playervG[cpin->y][cpin->x] = 0;

	    hlayerG[cpin->y][cpin->x] = num_netsG+1;

	    S_retpin( cpin );
	}

if(!( net_arrayG[i].pin ) ){
    sprintf(YmsgG,"i = %d net = %d has no fixed pin\n", i, 
	number_to_name(i));
    M( WARNMSG, "rmsidepins", YmsgG ) ;
}

if(!( net_arrayG[i].pin ) )
    return;

	ppin = net_arrayG[i].pin;

        for( cpin = ppin->next; cpin != (PINPTR)NULL;
	     cpin = cpin->next )
	{
	    if( cpin->type == TEMP && cpin->x == col && cpin->y != row )
	    {
		ppin->next = cpin->next;

	        if( cpin->layer == HORIZ )
		    playerhG[cpin->y][cpin->x] = 0;
	        else
		    playervG[cpin->y][cpin->x] = 0;

	        hlayerG[cpin->y][cpin->x] = num_netsG+1;

		S_retpin( cpin );
		cpin = ppin;
	    }
	    else
	        ppin = cpin;
	}
}

/* sort by x first then y */
S_sortbyxy( pinA , pinB )
PIN_LISTPTR *pinA , *pinB ;

{
    /* sort by increasing x */
    if( (*pinA)->pin->x != (*pinB)->pin->x ){
	return( (*pinA)->pin->x - (*pinB)->pin->x ) ;
    } else {
	/* if xs are equal sort by decreasing ys */
	return( (*pinB)->pin->y - (*pinA)->pin->y ) ;
    }
} /* end S_sortbyxy */


/* Look for dangling nets.  If the net is dangling because of a 
  normal psuedo pin then, toss out that psuedo pin and link.
  10/89 R.A.Weier
 */
lookForDanglers(net) 
int net;
 {
  int x;
  int y;
  PINPTR tpin;
  PINPTR tpindel;	/* pin to delete */
  PINPTR *tpinHdl;   	/* pin handle in case we need to change list */
  LINKPTR link;
  LINKPTR *linkHdl;	/* link handle */
  LINKPTR *linkHdldel;	/* handle to predecessor of link to delete */
  LINKPTR linkdel;	/* link is the one to delete */
  LINKPTR isDanglingPoint();
if (net_arrayG[net].tmplist != (LINKPTR)NULL)
   return;

/* print list of pins, psudopins, temp links, and path */
/**/
  if (debugG ) {
    for(tpin=net_arrayG[net].pin; tpin; tpin=tpin->next)
      printf("%d pin %d at %d,%d \n",
        tpin->type,net,tpin->x,tpin->y);
    for(link=net_arrayG[net].tmplist; link; link=link->netnext)
      printf("tmplnk %d,%d  %d,%d\n",link->x1,link->y1,link->x2,link->y2);
    for(link=net_arrayG[net].path; link ;link=link->netnext)
      printf("pthlnk %d,%d  %d,%d\n",link->x1,link->y1,link->x2,link->y2);
    }
 /**/
  
tpinHdl = &net_arrayG[net].pin;
for( tpin=net_arrayG[net].pin; tpin ;  ) {	
  if (tpin->type != TEMP) 	/* psuedos (temp) always first in list */ 
    break;
  x=tpin->x;
  y=tpin->y;
  if (x == net_arrayG[net].colleft) {	/* left edge looks like dangler */
    tpinHdl = &tpin->next;		/* prepare for next pass */
    tpin=tpin->next;
    continue;				/* dont kill left edge pins */
    }
  if (x == net_arrayG[net].colright) {	/* right edge looks like dngler */
    tpinHdl = &tpin->next;		/* prepare for next pass */
    tpin=tpin->next;
    continue;				/* dont kill right edge pins */
    }
  linkdel=isDanglingPoint(net,x,y);	/* check link */
  if ( linkdel ) {		/* if linkdel not NIL, its a dangler */
    printf("Dangler, removing psuedo %d @ %d,%d\n",net,x,y);
    if( tpin->layer == HORIZ )
      playerhG[tpin->y][tpin->x] = 0;
    else
      playervG[tpin->y][tpin->x] = 0;
    tpindel=tpin;
    *tpinHdl=tpin->next;	/* remove bogus psuedo pin */
    tpin=tpin->next;
    S_retpin( tpindel );	/* free pin memory */
    while(linkdel) {		/* may be a long chain of danglers */
      printf("Dangler, removing link %d,%d %d,%d\n",
	linkdel->x1,linkdel->y1,linkdel->x2,linkdel->y2);
      if(x==linkdel->x1 && y==linkdel->y1) {
	x=linkdel->x2;
	y=linkdel->y2; 
	}
      else {
	x=linkdel->x1;
	y=linkdel->y1;
	}
      S_dellink(linkdel);	/* delete bogus link */

      linkdel=isDanglingPoint(net,x,y);		/* check next link */
      }
    }
  else {
    tpinHdl = &tpin->next;		/* prepare for next pass */
    tpin=tpin->next;
    }
  }


 }

/* check point for number of nets terminating or passing through */
/* if only one net terminates there, returns pointer to dangling link */
LINKPTR isDanglingPoint(net,x,y)
int net;
int x;
int y;
{
LINKPTR link;
LINKPTR linkdel;
PINPTR tpin;
int k;

  for(tpin=net_arrayG[net].pin; tpin; tpin=tpin->next)
    if (tpin->type != TEMP)    /* stop if we have reached a perm pin */
      if(tpin->x==x && tpin->y==y)
	return((LINKPTR)NULL);
  k=0;
  link = net_arrayG[net].path;
  while( link != (LINKPTR)NULL && k<=1 ) {
    if( ( link->x1 == x && y == link->y1 )  ||
        ( link->x2 == x && y == link->y2 )  ) {
        k++;			/* net ends on point */
        linkdel=link;		/* save possible dangler */
        }
    else if( ( link->x1 == x && link->y1 < y && y < link->y2 )  ||
        ( link->y1 == y && link->x1 < x && x < link->x2 )  )
	return((LINKPTR)NULL);	/* net goes through point */
    link=link->netnext;		/* check next link */
    }
  if (k==1)
    return(linkdel);		/* it was a dangler. return link ptr */
  else 
    return((LINKPTR)NULL);	/* not a dangler, return null */

}
