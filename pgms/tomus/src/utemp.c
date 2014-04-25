/* ----------------------------------------------------------------- 
FILE:	    utemp.c                                       
DESCRIPTION:outer loop of simulated annealing algorithm.
CONTENTS:   utemp()
	    from_middle()
	    from_beginning()
	    int compute_attprcel(flag)
		int flag;
	    rm_overlapping_feeds()
	    refine_placement()
	    simple_refine_placement()
	    parametric_refine( k_max , k_limit )
		int k_max, k_limit ;
	    elim_nets()
DATE:	    Mar 27, 1989 
REVISIONS:  
----------------------------------------------------------------- */
#ifndef lint
static char SccsId[] = "@(#) utemp.c (Yale) version 1.6 2/22/91" ;
#endif


#include <yalecad/message.h>
#include "standard.h"
#include "main.h"

DOUBLE table1[1024] , table2[1024] , table3[1024] ; /* used in accept.c */
DOUBLE ratioG = 1.0; 
INT acc_cnt = 0; 
BOOL pairtestG;
DOUBLE Stats ;
DOUBLE damp_factor ; /* used in uloop.c */
INT moveable_cells ;
INT InitTilePG ;
INT FinalTilePG ;
INT DiffTilePG ;
BOOL noPairsG ;

extern INT num_legal_tiles;
extern DOUBLE mean_width;
extern DOUBLE Clust_mean_widthG;

static INT *cost_vectorS ;

utemp()
{

static INT checkL ;
static unsigned i2 ;
static INT i , freezeL ;
int newcost ;

damp_factor = 1.0;

cost_vectorS = (INT *) Ysafe_malloc( 13 * sizeof(int) ) ;
for( i = 0 ; i <= 12 ; i++ ) {
    cost_vectorS[i] = 0 ;
}


checkL = 0 ;
freezeL = 10000000 ;
 
table1[0] = 1.0 ;
table2[0] = 1.0 ;
table3[0] = 1.0 ;
for( i2 = 1 ; i2 <= 1023 ; i2++ ) {
    table1[ i2 ] = exp( -(double) i2 / 8.0 ) ;
    table2[ i2 ] = exp( -(double) i2 / 8192.0 ) ;
    table3[ i2 ] = exp( -(double) i2 / 8388608.0 ) ;
}


attprcel = compute_attprcel(1);

/* target tile penalty functions : limits */

InitTilePG = 0.5 * celllenG ;
FinalTilePG = mean_width * num_legal_tiles ;
DiffTilePG = InitTilePG - FinalTilePG ;

if( !pairtestG ) {
    attmax = attprcel * moveable_cells ;

    if( iterationG < 1 ) {
	resume_runG = 0 ;
    }
    if( !resume_runG ) {
	from_beginning() ;
    } else if( resume_runG ) {
	from_middle() ;
    }
}

for( ; ; ) {

    if( pairtestG == FALSE && TG >= 0.01 ) {
	uloop() ;
    } else {
	pairtestG = TRUE ;
	if( !checkL ) {
	    checkL = 1 ;
	    freezeL = iterationG ;
	    fprintf( fpoG, "\nTOTAL INTERCONNECT LENGTH: %d\n",funccostG);
	    fflush(fpoG);
	    attmax = 10 * numcellsG ;
	} else {
	}
	print_paths() ;
    }

    printf("%3d ", iterationG );
    if( iterationG % 15 == 0 ) {
	printf("\n");
    }
    ++iterationG;
    fflush( stdout ) ;

    if( iterationG >= freezeL + 3 ) {
	fprintf(fpoG,"FINAL TOTAL INTERCONNECT LENGTH: %d\n",funccostG);
	fprintf(fpoG,"FINAL PENALTY: %d    ", penaltyG );
	fprintf(fpoG, "FINAL VALUE OF TOTAL COST IS: %d\n", 
					    funccostG + penaltyG ) ;
	fprintf(fpoG,"MAX NUMBER OF ATTEMPTED FLIPS PER T:%8d\n",attmax);
	break ;
    } 
}
return ;
} /*** end utemp() ***/


from_middle()
{

    init_control(-1);		/* set move generation controller. */

    attmax = attprcel * moveable_cells ;
    fprintf(fpoG, "\nIter T         Wire     Penal tileP    partP  TileC PartC");
    fprintf(fpoG, "s/p  rej. Acc \n");
    fprintf(fpoG,"%3d: %6.2le %-8ld %-6ld %-6ld ",
	iterationG++,0.0,funccostG,penaltyG,tilepenalG);
    fprintf(fpoG,"%4.2lf %4.2lf %4.2lf %5.3lf\n",tilepenalC, 0.0, 0.0,ratioG);
    fflush(fpoG);
}


from_beginning()
{

    init_uloop(); 
    init_control(1);		/* set move generation controller. */
    attmax = attprcel * moveable_cells ;
    acc_cnt = 0;
    iterationG = -1 ;
    Stats = -1.0; TG = 1.0e10;	/* set to VERY HIGH temperature. */
    uloop(); 

    if( moveable_cells < 300 ) {
	attmax *= 2;
    }
    acc_cnt = 0;
    Stats = 0.0;			/* collect statistics */
    uloop();			/* discard old result and try again. */
    Stats = 1.0 / TG;		/* compute Stats */

    /* init_parameters(attmax,ratioG) ; */

    attmax = attprcel * moveable_cells ;
    fprintf(fpoG, "\nIter T         Wire     Penal tileP  TileC ");
    fprintf(fpoG, "s/p  rej. Acc \n");
    fprintf(fpoG,"%3d: %6.2le %-8ld %-6ld %-6ld  ",
	iterationG++,0.0,funccostG,penaltyG,tilepenalG);
    fprintf(fpoG,"%4.2lf %4.2lf %4.2lf %5.3lf\n",tilepenalC, 0.0, 0.0,ratioG);
    fflush(fpoG);
}

int compute_attprcel(flag)
int flag;
{
    int cell, n;

    moveable_cells = 0 ;

for( cell = 1 ; cell <= numcellsG ; cell++ ) {
	moveable_cells++ ;
}

    if( moveable_cells <= 500 ) {
	n = 25 ;
    } else {
	/*  n to the 4/3 power  */
	n = (int)(25.0 * 
		    pow( (double) moveable_cells / 500.0, 1.0 / 3.0 ) ) ;
    }

    if( flag && tw_fast ) {
	n /= tw_fast ;
    } else if( tw_slow ) {
	n *= tw_slow ;
    }

    return(n);
}


tw_frozen( cost )
INT cost ;
{

static DOUBLE diffL , avg_first_setL , avg_second_setL ;
static INT i ;

if( cost_vectorS[0] >= 12 ) {
    for( i = 2 ; i <= 12 ; i++ ) {
	cost_vectorS[i-1] = cost_vectorS[i] ;
    }
    cost_vectorS[12] = cost ;
    avg_first_setL = (double)(cost_vectorS[1] + cost_vectorS[2] + 
		    cost_vectorS[3] + cost_vectorS[4]) / 4.0 ;
    avg_second_setL = (double)(cost_vectorS[9] + cost_vectorS[10] + 
		    cost_vectorS[11] + cost_vectorS[12]) / 4.0 ;
    diffL = avg_first_setL - avg_second_setL ;
    if( diffL <= 0.0 ) {
	return(1) ;
    } else {
	if( diffL / avg_first_setL < 0.004 ) {
	    return(1) ;
	} else {
	    return(0) ;
	}
    }
} else {
    cost_vectorS[ ++(cost_vectorS[0]) ] = cost ;
    return(0) ;
}
}
