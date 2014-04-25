/* ----------------------------------------------------------------- 
FILE:	    uloop.c                                       
DESCRIPTION:inner loop of simulated annealing algorithm.
CONTENTS:   
	    uloop()
DATE:	    Mar 09,1990 
REVISIONS:  Mar 09, 1990 - 
----------------------------------------------------------------- */
#ifndef lint
static char SccsId[] = "@(#) uloop.c (Yale) version 1.8 2/22/91" ;
#endif

#define	LOOP_VARS
#include "standard.h"
#include "main.h"
#undef LOOP_VARS

#define INITRATIO 0.95
#define AC3 0.10

#define PT1 0.15
#define PT2 0.52

/* Note: If you change definitions here, check newtemp.c */
#define ACCEPTDAMPFACTOR  0.025  /* damping factor for acceptance rate*/
#define ACCEPTDAMPFACTOR2  0.25  /* damping factor for low temp's */
#define TURNOFFT 125.0  /* (100) iteration of negative feedback turnoff */
#define LASTTEMP       155.00 /* last iteration */
#define NUMTUPDATES   400 /* maximum number of T updates per iteration */


extern INT num_legal_tiles;
extern INT moveable_cells ; /* utemp.c */
extern BOOL pairtestG; /* utemp.c */
extern DOUBLE mean_width;
extern DOUBLE damp_factor ; /* utemp.c */
extern INT d_cost,truth; /* in accept.c */
extern DOUBLE Stats ; /* utemp.c */ 
extern DOUBLE ratioG ; /* utemp.c */
extern INT acc_cnt ; /* utemp.c */
extern INT InitTilePG ;
extern INT FinalTilePG ;
extern INT DiffTilePG ;

static DOUBLE avg_tilepenalS ;
static DOUBLE num_penalS ;
static DOUBLE fp_ratioS = 1.0 ;
static INT P_limit_setS = 0;
static DOUBLE fraction_doneS ;
static INT do_single_cell_moveS ;

INT not_doneG = 1, first_caps = 1 , f_cnt = 0;

static PTILEPTR atileptr, btileptr, dummytptr;
static CBOXPTR acellptr,bcellptr;
static INT acell,bcell,atile,btile,Apost,Bpost,atile_x,atile_y;
static INT btile_x,btile_y;
static DOUBLE target_tile_penalty,target_part_penalty, tilep_per,partp_per;
static INT flipsS , rejectsS  ;
static INT pairflipsS ;

uloop()
{

static int i , j , t ;
static INT bcellsS ;

static DOUBLE tempS , percent_errorS ;
static DOUBLE dCp ;
static int m1,m2;
static INT num_accepts ;
static INT last_flipsS , delta_func , delta_time ;
static INT temp_timer,time_to_update;/* keeps track of when to update T */
static DOUBLE iter_timeS, accept_deviationS;
static DOUBLE num_timeS, num_funcS ;

DOUBLE calc_acceptance_ratio() ;
DOUBLE calc_time_factor() ; 

attempts  = 0 ;
flipsS     = 0 ;
rejectsS   = 0 ;
pairflipsS = 0 ;
earlyRej  = 0 ;
Rej_error = 0 ;
potential_errors = 0 ;
error_count = 0 ;

/* changed 
if( !P_limit_setS || S <= 1.0e-30) */
if( 1 || !P_limit_setS || Stats <= 1.0e-30) { 
    P_limit = 999999;
    if( Stats > 0 ) {
	P_limit_setS = 1 ;
    }
} else {
    if( wire_chgs > 0 ) {
	mean_wire_chg = total_wire_chg / (double) wire_chgs ;
	if( iterationG > 1 ) {
	    sigma_wire_chg = sqrt( sigma_wire_chg / (double) wire_chgs);
	} else {
	    sigma_wire_chg = 3.0 * mean_wire_chg ;
	}
    } else {
	mean_wire_chg  = 0.0 ;
	sigma_wire_chg = 0.0 ;
    }
    P_limit = mean_wire_chg + 3.0 * sigma_wire_chg + TG ;
    if (P_limit > 999999) P_limit = 999999;
}

sigma_wire_chg = 0.0 ;
total_wire_chg = 0.0 ;
wire_chgs = 0 ;
m1 = m2 = 1;
dCp = 0.0;


i = funccostG + penaltyG;

avg_tilepenalS = 0.0 ;
num_penalS = 0.0 ;
if( Stats < 0.0 ) {
    avg_timeG = 0.0 ;
    num_timeS = 0.0 ;
    avg_funcG = 0.0 ;
    num_funcS = 0.0 ;
}

/* number of moves before temperature update */
time_to_update = attmax / NUMTUPDATES ;
if( time_to_update <= 14 ) {
    time_to_update = 14 ;
}
temp_timer = 0 ; /* initialize timer */
num_accepts = 0 ;
last_flipsS = 0 ;

while( attempts < attmax ) {

    acell = PICK_INT( 1 , numcellsG ) ;

    acellptr = carrayG[ acell ] ;
    acell = acellptr->id ;
    atile   = acellptr->tile ;
    
Apost = 0;
    atileptr = tarrayG[ atile ] ;
    atile_x = atileptr->center_x;
    atile_y = atileptr->center_y;
    for( i = 1 ; i <= atileptr->cells; i++ ) {
	if( carrayG[atileptr->carray[i]] == acellptr ) {
	     Apost = i ;
	     break ;
	}
    }

    /* 
     *  select tile for cell a to be placed in 
     */
get_b:		pick_position(&btile_x,&btile_y,atile_x,atile_y);
                btile = search_legal_tile(btile_x,btile_y);
		if (btile==atile || btile ==0 || !tarrayG[btile]->capacity){
		       goto get_b ;
		}
		if (strcmp( acellptr->cpclass[0],"none" ) == 0){
		    if (!tile_found(btile, acellptr->cpclass)) goto get_b;
		}
		btileptr= tarrayG[btile];
		if ( 1.2* btileptr->capacity > btileptr->celllen) {
			do_single_cell_moveS = 1 ; 
	        } else if (flipsS < pairflipsS) {
			do_single_cell_moveS = 1 ; 
	        } else {
		    do_single_cell_moveS = 0 ;
		    bcellsS = btileptr->cells;
		    if( bcellsS > 0 ) {
		      Bpost = PICK_INT( 1 , bcellsS ) ;
		      bcellptr = carrayG[btileptr->carray[ Bpost ]];
		      bcell = bcellptr->id;
		      if (strcmp( bcellptr->cpclass[0],"none" ) == 0){
		         if (!tile_found(atile, bcellptr->cpclass))
				 goto get_b;
		      }
	            } else {
		      goto get_b ;
		    }
	        }

/* if the btile's capacity is more than its celllen, then cell a 
   is moved to the btile: single cell move,
   else a cell b from btile is randomly picked and exchanged with cell a
   : pair-wise interchanged */

    delta_func = funccostG ;
    delta_time = timingpenalG ;

    if( do_single_cell_moveS ) {
		t = ucxx1(acell,atile,btile,Apost) ;
		if( t != 1 ) {
		    rejectsS++ ;
		} else {  /* if( t == 1 ) */
		  flipsS++ ;
		    acc_cnt ++;
		}
    } else {
	/*   pairwise interchange */
		t = ucxx2(acell,bcell,atile,btile,Apost,Bpost) ;
		if( t != 1 ) {
		    rejectsS++ ;
		} else {  /* if( t == 1 ) */
		      pairflipsS++ ;
		      acc_cnt ++;
		}
    }

    num_penalS += 1.0 ;
    avg_tilepenalS = (avg_tilepenalS * (num_penalS - 1.0) + 
			(double) tilepenalG) / num_penalS ;
    
    attempts++ ;
    if (Stats <= 0.0) {

	if (Stats == 0.0)  continue;
	
	/* calculate a running average of (delta) timing penalty */
	delta_time = abs( delta_time - timingpenalG ) ;
	if( delta_time != 0 ) {
	    num_timeS += 1.0 ;
	    avg_timeG = (avg_timeG * (num_timeS - 1.0) + 
			    (double) delta_time) / num_timeS ;
	
    /* calculate a running average of (delta) wirelength penalty */
	    delta_func = abs( delta_func - funccostG ) ;
	    num_funcS += 1.0 ;
	    avg_funcG = (avg_funcG * (num_funcS - 1.0) + 
				(double) delta_func) / num_funcS ;
	}


if (d_cost > 0) m1 ++;	/* d_cost is the -ve of the actual d_cost */
	else {
	    dCp -= d_cost;
	    m2 ++;
	}
	tempS = (INITRATIO * attempts - m1) / m2;
	if (tempS <= 0.0) {
	    TG *= 0.9;
	} else {
	    TG = -dCp / (m2 * log(tempS));
	}
	continue;		/* initialization phase */
    }
    /* ----------------------------------------------------------------- 
       Update temperature using negative feedback to control the
       acceptance ratio in accordance to curve fit schedule.  
       Calc_acceptance_ratio returns desired acceptance ratio give
       the iteration.  The damped error term (deviation) is then applied 
       to correct the temperature T.  Update_window_size controls the 
       range limiter.  We avoid updating T during initialization, 
       we use exact schedule to compute starting T.  The temp_timer 
       allows us to update temperature inside the inner loop
       of the annealing algorithm. We use counter to avoid use of mod
       function for speed.
     ------------------------------------------------------------------ */
    num_accepts += pairflipsS + flipsS - last_flipsS ;
    last_flipsS = pairflipsS + flipsS ;

    if( ++temp_timer >= time_to_update || 
			(attempts >= attmax && temp_timer >= 50) ) {
	ratioG = ((double)(num_accepts)) / (double) temp_timer ;
	temp_timer = 0 ; /* reset counter */
	num_accepts = 0 ;
	iter_timeS = (DOUBLE) iterationG +
		    (DOUBLE) attempts / (DOUBLE) attmax ;
	accept_deviationS = 
	    (calc_acceptance_ratio( iter_timeS ) - ratioG ) ;
	if( (double) iterationG < TURNOFFT ) {
	    accept_deviationS *= ACCEPTDAMPFACTOR ; 
	} else {
	    accept_deviationS *= ACCEPTDAMPFACTOR2 ;
	}
	TG *= 1.0 + accept_deviationS ;
	update_window_size( (DOUBLE) iterationG +
			    (DOUBLE) attempts / (DOUBLE) attmax ) ;
    }
} /*** end of the while loop with attempt < attmax ****/


f_cnt = 0;

if( ratioG < AC3 ){
    if( iterationG >= LASTTEMP || (tw_frozen( funccostG )  &&
				(iterationG >= LASTTEMP - 5)) ) {
	/* printf("terminated by tw_frozen\n");
	fflush(stdout); */
	pairtestG = 1 ;
    }
}

if( potential_errors > 0 ) {
    percent_errorS = (double) error_count / (double) potential_errors ;
} else {
    percent_errorS = 0.0 ;
}
percent_errorS *= 100.0 ;

if( pairflipsS > 0.0001 ) {
    fp_ratioS = (double)flipsS/(double)pairflipsS ;
} else {
    fp_ratioS = 1.0 ;
}

ratioG = ((double)(pairflipsS+flipsS)) / attempts;
if(Stats > 0.0 ) {
	fprintf(fpoG,"%3d: %6.2le %-8ld %-6ld %-6ld ",
    		iterationG,TG,funccostG,penaltyG,tilepenalG);
	fprintf(fpoG," %4.2lf ",tilepenalC);
	fprintf(fpoG," %4.2lf %4.2lf %5.3lf\n", fp_ratioS,
	    ((double) earlyRej)/attempts,ratioG );
	fflush(fpoG);
}

/*  A Negative-Feedback Approach */
if( not_doneG ) {
    not_doneG = eval_ratio(&fraction_doneS);
    if (first_caps ) {
	first_caps = 0;
    }

    tilep_per = (double)tilepenalG;

/***** old way *********
_--------------------------------------------
    target_tile_penalty = (1.25- 0.25 * fraction_doneS) * num_legal_tiles *  mean_width ;
_--------------------------------------------
***********************/

    target_tile_penalty = ( ( 1 - fraction_doneS ) * DiffTilePG ) + FinalTilePG ;

    if (iterationG > 0 && iterationG < 50){
	    damp_factor = 1 + (double)iterationG/12.5;
    }

    /*** freeze the constant at iteration 120 ****/
    if ( iterationG < 125 ) {
	tilepenalC *= ( 1.0 + (double)((tilep_per - target_tile_penalty)/
			(double)(target_tile_penalty * damp_factor)));
	not_doneG = 1 ;
    }
    
    /*** don't let the Constant go less than 1.0 all thru out the annealing ****/
    if( tilepenalC < 1.0 ) { 
	tilepenalC = 1.0 ;
    }

    /*** don't let the Constant go more than 20 only in the beginning */
    if( iterationG < 125 && tilepenalC > 6 ) { 
	tilepenalC = 6 ;
    }

    penaltyG = (int)( tilepenalC * (double) tilepenalG ) ;
	

    timeFactorG = calc_time_factor() ;
    /* scale timing penalty */
    timingcostG = (int) ( timeFactorG * (DOUBLE) timingpenalG ) ;
}

return ;
}
