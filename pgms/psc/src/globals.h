/* ----------------------------------------------------------------- 
"@(#) globals.h version 1.3 4/21/91"
FILE:	    globals.h
DESCRIPTION:This file contains type declarations for the parallel
	    scheduler.
CONTENTS:   
DATE:	    Tue Feb 19 14:12:57 EST 1991
REVISIONS:  Thu Mar  7 02:53:29 EST 1991 - added node definitions.
	    Sun Apr 21 21:44:13 EDT 1991 - added flow directory
		and remote graphics.
----------------------------------------------------------------- */
#ifndef GLOBALS_H
#define GLOBALS_H

#ifndef GLOBALS_DEFS
#define EXTERN extern

#else
#define EXTERN
#endif

#include <yalecad/base.h>
#include <yalecad/rbtree.h>
#include <yalecad/deck.h>

/* remove graphics lines of code if compile switch is on */
#ifdef NOGRAPHICS
#define G(x_xz) 

#else 
#define G(x_xz)   x_xz

#endif /* NOGRAPHICS */

#define MAX_PARTS          1024 
#define LIMIT              10

/* JOB STATUS DEFINITIONS */
#define JOB_INIT      0
#define JOB_SCHED     1
#define JOB_RESCHED   2
#define JOB_RUNNING   3
#define JOB_ERROR     4
#define JOB_COMPLETE  5
#define JOB_UNKNOWN   6
#define JOB_SCHEDFAIL 7
#define JOB_LOADED    8
#define JOB_CHECKFAIL 9
#define JOB_QUEUED    10

/* NODE STATUS DEFINITIONS */
#define NODE_FREE     0
#define NODE_BUSY     1

/* JOB CONTROL DEFINITIONS */
#define EXECUTE_JOB   1
#define CHECK_JOB     2
#define ALLOC_JOB     3

typedef struct node {
    char *nodename ;
    char *directory ;
    INT  job ;
    INT  status ;
    INT  pid ;
    INT  errors ;
    INT  priority ;
} NODE, *NODEPTR, JOB, *JOBPTR ;

/* ******************** GLOBAL VARIABLES *********************** */
/* the user requests */
EXTERN BOOL graphicsG  ;  /* TRUE if graphics are desired */
EXTERN BOOL debugG ;      /* TRUE if debug is requested */
EXTERN BOOL verboseG ;    /* TRUE if verbose has been set */
EXTERN BOOL nopartitionsG ;/* TRUE if nopartitions are present */

/* data */
EXTERN char *cktNameG ;    /* the name of the circuit */
EXTERN char *flow_dirG ;   /* the name of the flow directory */
EXTERN INT  total_nodesG ; /* total available nodes */
EXTERN INT  num_nodesG ;   /* current number of nodes available */
EXTERN INT  total_jobsG ;  /* total number of jobs to run */
EXTERN INT  num_jobsG ;    /* current number of jobs to run */
EXTERN BOOL statusChangedG;/* when something changes we redraw */
EXTERN BOOL remote_graphicsG;/* true if we want to send back to machine */
EXTERN char *displayG ;    /* display name */

EXTERN YTREEPTR node_treeG ; /* tree of valid nodes */
EXTERN YDECKPTR job_queueG ; /* jobs to be queued */
EXTERN YDECKPTR job_schedG ; /* jobs currently scheduled */

#endif /* GLOBALS_H */
