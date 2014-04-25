/* ----------------------------------------------------------------- 
"@(#) main.h (Yale) version 2.8 12/8/89"
FILE:	    main.h                                       
DESCRIPTION:global definitions for Tomus Simulated Annealing par.s
CONTENTS:   
DATE:	    Sept. 1989 
REVISIONS:   
----------------------------------------------------------------- */
/* global variables defined for main */

#define remv_cell(tptr,p) \
     (tptr)->carray[(p)] = (tptr)->carray[(tptr)->cells]; \
     (tptr)->cells -- ; \

#ifdef MAIN_VARS
#define EXTERN 
#else
#define EXTERN extern 
#endif

EXTERN int doGraphicsG ;
EXTERN unsigned Yrandom_seed() ;
EXTERN unsigned randomSeed  ;
EXTERN unsigned randomSeed2 ;
EXTERN int tw_fast ;
EXTERN int tw_slow ;
EXTERN int attmax ;
EXTERN int iterationG ;
EXTERN int attprcel ;
EXTERN int costonly ;
EXTERN double TG ;
EXTERN BOOL resume_runG ;
EXTERN BOOL Endflag ;

EXTERN double total_wire_chg ;
EXTERN double sigma_wire_chg ;
EXTERN double mean_wire_chg ;
EXTERN int wire_chgs;
EXTERN int wire_chg;
EXTERN int earlyRej , Rej_error ;
EXTERN int potential_errors , error_count , P_limit ;
EXTERN int attempts;

EXTERN double avg_timeG ; /* average random time penalty */
EXTERN double avg_funcG ; /* average random time penalty */
#undef EXTERN
