/* ----------------------------------------------------------------- 
FILE:	    ulp_util.c                                       
DESCRIPTION:inner loop of simulated annealing algorithm.
CONTENTS:   
	    save_control( fp )
		FILE *fp ;
	    read_control( fp )
		FILE *fp ;
	    int eval_ratio(t)
		double *t;
	    init_uloop()
	    init_control(first)
		int first;
	    pick_position(x,y,ox,oy,scale)
		int *x,*y,ox,oy;
		double scale ;
	    update_control(a)
		double a;
	    update_window_size( iternum )
		double iternum ;
DATE:	    Mar 09, 1990 
REVISIONS:  Mar 29, 1989 - 
----------------------------------------------------------------- */
#ifndef VMS
#ifndef lint
static char SccsId[] = "@(#) ulp_util.c (Yale) version 1.3 2/22/91" ;
#endif
#endif

#include "standard.h"
#include "main.h"

#define AC0 0.90
#define AC1 0.44
#define AC2 0.06
#define AC3 0.10
#define AC4 0.10

#define PT1 0.15
#define PT2 0.52
#define PT3 1.00

#define LAC1 (log(AC1))
#define LAC2 (log(AC2))

#define STEPSPERCEL 0.01

#define TABLIMIT 4096			/* simple table lookup for log. */
#define TABSHIFT 19
#define TABMASK 0xfff
#define TABOFFSET 0x40000
#define RANDFACT (1.0 / MAXINT)
#define CHANCE(n) (!(RAND % n))


/* Note: If you change definitions here, check newtemp.c */
#define ACCEPTDAMPFACTOR  0.025  /* damping factor for acceptance rate*/
#define ACCEPTDAMPFACTOR2  0.25  /* damping factor for low temp's */
#define HIGHTEMP  23.0   /* (15.0) end of high temperature regime */
#define MEDTEMP   81.0   /* (52.0) end of range limiter regime */
#define TURNOFFT 125.0    /* (100) iteration of negative 
						feedback turnoff */
#define LASTTEMP       155.00 /* last iteration */
#define NUMTUPDATES   400 /* maximum number of T updates per iteration */

extern double us,vs,S;
extern BOOL pairtestG;
extern INT not_doneG ;
extern INT first_caps  , f_cnt ;
extern INT acc_cnt ;
extern DOUBLE ratioG ;

static INT move_cntS = 0 ;
static DOUBLE log_tab[TABLIMIT];
static DOUBLE xadjustment,xal,min_xalpha,max_xalpha;	/* x control */
static DOUBLE yadjustment,yal,min_yalpha,max_yalpha;	/* y control */
static DOUBLE tauXS, tauYS ; /* exp. decay time constants for window */
static DOUBLE total_cost ;
static DOUBLE a_ratio;
static DOUBLE total_steps,steps;

save_control( fp )
FILE *fp ;
{
    fprintf(fp,"%d %d\n",pairtestG,not_doneG);
    fprintf(fp,"%d %d %d\n",acc_cnt,move_cntS,first_caps);
    fprintf(fp,"%f %f %f %f\n",steps,xal,yal,a_ratio);
    fprintf(fp,"%f %f\n",ratioG,total_cost);
    /*fprintf(fp,"%f %f\n",bin_cap,row_cap); */
    fprintf(fp,"%f %f %f\n",avg_timeG, avg_funcG, timeFactorG);
}

read_control( fp )
FILE *fp ;
{
    fscanf(fp,"%ld %ld\n",&pairtestG,&not_doneG);
    fscanf(fp,"%ld %ld %ld\n",&acc_cnt,&move_cntS,&first_caps);
    fscanf(fp,"%lf %lf %lf %lf\n",&steps,&xal,&yal,&a_ratio);
    fscanf(fp,"%lf %lf\n",&ratioG,&total_cost);
    fscanf(fp,"%lf %lf %lf\n",&avg_timeG, &avg_funcG, &timeFactorG);
}

/* new evaluate ratio is a linear function of iteration */
int eval_ratio( t )
double *t;
{
    if( iterationG >= TURNOFFT ){
	*t = 1.0 ;
    } else if( iterationG < 0 ){
	*t = 0.0 ;
    } else {
	*t = (DOUBLE) iterationG / TURNOFFT ;
    }
    return((ratioG < AC4) ? 0 : 1);
}

init_uloop()
{
    not_doneG = 1;
    acc_cnt =move_cntS = 0;
    ratioG = 1.0;
}

init_control(first)
int first;
{
    int i;
#define FRACTION  0.10

    /* initialize move generation parameters */
    
    /* average min. window size */
    min_xalpha =  ave_xspan();
    min_yalpha =  ave_yspan();
   
   /* average max. window size */
    max_xalpha = (double)(core_x2G - core_x1G);
    max_yalpha = (double)(core_y1G - core_y2G);

    min_xalpha = MIN( min_xalpha, FRACTION * (DOUBLE) max_xalpha ) ;
    min_yalpha = MIN( min_yalpha, FRACTION * (DOUBLE) max_yalpha ) ;

/* commented as suggested by Carl 
    total_steps = STEPSPERCEL * (numcellsG) ;
    xadjustment = (max_xalpha - min_xalpha) / total_steps;
    yadjustment = (max_yalpha - min_yalpha) / total_steps;*/

    if( first == 1 ) {
	xal = max_xalpha;
	yal = max_yalpha;
    }
    /* determine tauXS & tauYS - exponential decay of range limiter */
    tauXS = - log( (min_xalpha/max_xalpha) ) / (MEDTEMP - HIGHTEMP) ;
    tauYS = - log( (min_yalpha/max_yalpha) ) / (MEDTEMP - HIGHTEMP) ;

    /* prepare lookup table */
    for (i=0; i<TABLIMIT; i++)
	log_tab[i] = log(((i << TABSHIFT) + TABOFFSET) * RANDFACT);
}


pick_position(x,y,ox,oy)
int *y,oy,*x,ox;
{
    register int i,m,n;
    double tmp ;

 /* get exponentially distributed random number around old x */
 for (i=0; i<2; i++) {
    m = RAND;
    n = -xal * log_tab[(m >> TABSHIFT) & TABMASK];
    if (m & 0x10000){
          n = -n;
    }
    n += ox;
    /* check for inside core */
    if (n >= core_x1G && n <= core_x2G){
 /* hate to use a goto here but it saves another test */
         goto DONEX ;
      }
}
    /* by default -we have failed. Use boundary */
  if (n < core_x1G) {
       if (ox > core_x2G){
             ox = core_x2G;
       } else if (ox < core_x1G){
              ox = core_x1G;
       }
       n = PICK_INT(core_x1G,ox);
  } else if (n > core_x2G) {
     if (ox < core_x1G){
        ox = core_x1G;
     } else if (ox > core_x2G){
            ox = core_x2G;
     }
        n = PICK_INT(ox,core_x2G);
  }
DONEX:  *x = n;

     /* get exponentially distributed random number around old y */
for (i=0; i<2; i++) {
    m = RAND;
    n = -yal * log_tab[(m >> TABSHIFT) & TABMASK] + 0.5;
    if (m & 0x10000) n = -n;
    n += oy;
    /* check for inside core */
    if (n >= core_y2G && n <= core_y1G){
	 *y = n;
         return;
   }
}
 /* if fail use boundary */
 if (n < core_y2G) {
       if (oy > core_y1G){
         oy = core_y1G;
      } else if (oy < core_y2G){
        oy = core_y2G;
      }
      n = PICK_INT(core_y2G,oy);
 } else if (n > core_y1G) {
      if (oy < core_y2G){
             oy = core_y2G;
      } else if (oy > core_y1G){
             oy = core_y1G;
      }
      n = PICK_INT(oy,core_y1G);
 }
 *y = n;

}

update_control(a)
double a;
{
    /* adjust move generation parameters */
    steps -= (a - 0.44) / total_steps;
    if (steps < 0.0) steps = 0.0;
    else if (steps > 1.0) steps = 1.0;
    xal += (a - 0.44) * xadjustment;
    if (xal < min_xalpha) xal = min_xalpha;
    else if (xal > max_xalpha) xal = max_xalpha;
    yal += (a - 0.44) * yadjustment;
    if (yal < min_yalpha) yal = min_yalpha;
    else if (yal > max_yalpha) yal = max_yalpha;
}

/* change range limiter according to iteration number */
update_window_size( iternum )
double iternum ;
{
    if( iternum <= HIGHTEMP ){
	xal = max_xalpha ;
	yal = max_yalpha ;
    } else if( iternum <= MEDTEMP ){
	/* exponential decay xal and yal */
	/* -------------------------------------------------------- 
	    xal = max_xalpha * exp( - tauXS * ( iternum - HIGHTEMP ))
	    yal = max_yalpha * exp( - tauYS * ( iternum - HIGHTEMP ))
	   -------------------------------------------------------- */
	xal = yal = iternum - HIGHTEMP ;
	xal *= - tauXS ;
	xal = max_xalpha * exp( xal ) ;

	yal *= - tauYS ;
	yal = max_yalpha * exp( yal ) ;

    } else {  /* low temp */
	xal = min_xalpha ;
	yal = min_yalpha ;
    }
}
