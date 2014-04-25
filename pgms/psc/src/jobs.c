/* ----------------------------------------------------------------- 
FILE:	    jobs.c
DESCRIPTION:
CONTENTS:   
DATE:	    Mon Feb 18 00:08:29 EST 1991
REVISIONS:  Thu Mar  7 02:56:40 EST 1991 - first working version.
	    Tue Mar 12 17:00:23 CST 1991 - fixed problems when
		no node file is present.
	    Thu Apr 18 01:58:41 EDT 1991 - wait longer before starting
		programs.
	    Sun Apr 21 21:45:53 EDT 1991 - added remote graphics and
		flow directory passing to psc_sched.
----------------------------------------------------------------- */
#ifndef lint
static char SccsId[] = "@(#) jobs.c (Yale) version 1.11 5/22/92" ;
#endif

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <yalecad/message.h>
#include <yalecad/string.h>
#include <yalecad/debug.h>
#include <yalecad/file.h>
#include <globals.h>
#include <codes.h>

#define COMMENT           '#'
#define RSH               "rsh"
#define PSCHED            "psc_sched"
#define ARGS              "-lt"
#define NARGS             "-nlt"
#define OUTPUT            "/dev/null"
#define CHECK             "check_status"
#define RSHCHECK          "rsh"
#define TIMBERWOLF        "TimberWolf"
#define MSEC_PER_SEC      1000
#define WAIT_TO_SETTLE    20
#define UPDATE_TIME       (2 * MSEC_PER_SEC)
#define UNKNOWN           -10 /* just pick a negative number */

static INT last_timeS ;   /* keep track of time */
static INT update_timeS = UPDATE_TIME ;

#define ERROR    (-1)
#define STDOUT   1
#define READ     0
#define WRITE    1

extern INT check_job() ;

FILE *run_prog_with_pipe( argv )
char **argv ;
{
    int pid ;
    int pfd[2] ;
    FILE *fp = NIL(FILE *) ;

    if( pipe( pfd ) == ERROR ){
	perror( "run_prog_with_pipe") ;
    } else if( fp = fdopen(pfd[READ],"r") ){
	if( (pid = fork()) == ERROR ){
	    perror( "run_prog_with_pipe") ;
	    if( fclose(fp) == ERROR || close( pfd[WRITE]) == ERROR ){
		perror( "run_prog_with_pipe") ;
	    }
	} else if( pid == 0 ) {
	    /* this is the child process */
	    D( "psc/run_prog_with_pipe",
		{ 
		    INT i ;
		    fprintf( stderr,"Try to exec program:%s\n",argv[0] ) ;
		    for( i = 0 ; argv[i] ; i++ ){
			fprintf( stderr, "argv[%d]:%s\n", i, argv[i] ) ;
		    }
		}
	    ) ;
	    if( close(STDOUT) == ERROR || 
		dup( pfd[WRITE] ) == ERROR ||
		close( pfd[WRITE] ) == ERROR ||
		close( pfd[READ] ) == ERROR ||
		execvp( argv[0], argv ) == ERROR ){

		/* we don't reach this point unless an error occurs */
		perror( argv[0] ) ;
		D( "psc/run_prog_with_pipe",
		    fprintf( stderr, "Reached an error in pipe\n" ) ;
		) ;
		if( fp ){
		    fclose( fp ) ;
		    close( pfd[WRITE]) ;
		}
		fp = NIL(FILE *) ;
	    }
	} else { 
	    D( "psc/run_prog_with_pipe",
		fprintf( stderr, "Forked a process :%d\n", pid ) ;
	    ) ;
	    if( close( pfd[WRITE] ) == ERROR ){
		perror( "run_prog_with_pipe") ;
	    }
	}
    }
    return( fp ) ;
} /* end  run_prog_with_pipe */

/* given a string return a argument vector */
char **create_argv( string )
char *string ;
{
    INT i ;            /* counter */
    INT start ;        /* start of the new tokens to be added */
    INT numtokens ;    /* number of tokens found */
    INT total_tokens ; /* total number of tokens */
    char *buffer ;     /* copy of array since Ystrparser is destructive */
    char **tokens ;    /* tokens is static in Ystrparser */
    char **argv ;      /* the tokenized string */
    char *quote ;      /* search for the quotes in string */

    /* make a copy since Ystrparser is destructive */
    buffer = Ystrclone( string ) ;
    start = 0 ;
    total_tokens = 0 ;
    argv = (char **) Yvector_alloc( 0, 1, sizeof(char *));
    while( quote = strchr( buffer, '\'' )){
	*quote = EOS ;
	tokens = Ystrparser( buffer, " \t\n", &numtokens ) ;
	total_tokens += numtokens ;
	argv = (char **) Yvector_realloc( argv, 0, 
	    total_tokens,sizeof(char *));
	for( i = start ; i < total_tokens ; i++ ){
	    argv[i] = tokens[i-start] ;
	}
	/* now find the ending quote */
	buffer = strchr( quote + 1, '\'' ) ;
	*buffer = EOS ;
	argv[total_tokens] = quote + 1 ;
	total_tokens++ ;
	start = total_tokens ;
	buffer++ ;
    }
    tokens = Ystrparser( buffer, " \t\n", &numtokens ) ;
    total_tokens += numtokens ;
    argv = (char **) Yvector_realloc( argv, 0, 
	total_tokens,sizeof(char *));
    for( i = start ; i < total_tokens ; i++ ){
	argv[i] = tokens[i-start] ;
    }
    argv[total_tokens] = NIL(char *) ;

    return( argv ) ;

} /* end create_argv */

static INT compare_nodes( node1, node2 )
NODEPTR node1, node2 ;
{
    if( node1->priority == node2->priority ||
	node1->priority == UNKNOWN || node2->priority == UNKNOWN ){
	return( strcmp( node1->nodename, node2->nodename ) ) ;
    } else {
	return( node1->priority - node2->priority ) ;
    }
} /* end compare_nodes */

build_node_tree()
{
    INT i ;
    char filename[LRECL] ;
    char buffer[LRECL], *bufferptr ;
    char **tokens ;     /* for parsing file */
    INT  numtokens, line ;
    BOOL abort ; /* whether to abort program */
    FILE *fp ;
    NODEPTR nptr ; /* current node */

    node_treeG = Yrbtree_init( compare_nodes ) ;
    total_nodesG = num_nodesG = 0 ;

    /* **************** READ node file ************/
    fp = TWOPEN( "nodes", "r", NOABORT ) ;

    if( fp ){

	/* parse file */
	line = 0 ;
	abort = FALSE ;
	while( bufferptr=fgets(buffer,LRECL,fp )){
	    /* parse file */
	    line ++ ; /* increment line number */

	    /* skip over commments */
	    if( *bufferptr == COMMENT ){
		continue ;
	    }
	    tokens = Ystrparser( bufferptr, " \t\n", &numtokens );

	    if( numtokens == 0 ){
		/* skip over empty lines */
		continue ;
	    } else {
		nptr = (NODEPTR) Ysafe_calloc( 1, sizeof(NODE) ) ;
		nptr->nodename = Ystrclone( tokens[0] ) ;
		Yrbtree_insert( node_treeG, nptr ) ;
		++num_nodesG ;
		nptr->priority = 0 ;
	    }
	}
	TWCLOSE( fp ) ;
    }
    total_nodesG = num_nodesG ;

    if( total_nodesG == 0 ){
	/* add ourself */
	gethostname( buffer, LRECL ) ;
	nptr = (NODEPTR) Ysafe_calloc( 1, sizeof(NODE) ) ;
	nptr->nodename = Ystrclone( buffer ) ;
	Yrbtree_insert( node_treeG, nptr ) ;
	total_nodesG = ++num_nodesG ;
    }


} /* end build_node_tree() */

find_partitions()
{
    INT i ;                 /* counter */
    JOBPTR job ;            /* current job */
    char filename[LRECL] ;

    for( i = 1 ; i <= MAX_PARTS ;i++ ){
	sprintf( filename, "%s:%d.scel", cktNameG, i ) ;
	if(!(YfileExists( filename ))){
	    break ;
	}
    }
    num_jobsG = i - 1 ;
    if( num_jobsG == 0 ){
	sprintf( filename, "%s.scel", cktNameG ) ;
	if(YfileExists( filename )){
	    nopartitionsG = TRUE ;
	    num_jobsG = 1 ;
	}
    } else {
	nopartitionsG = FALSE ;
    }
    total_jobsG = num_jobsG ;
    job_queueG = Ydeck_init() ;
    job_schedG = Ydeck_init() ;
    /* now get current working directory */
    getcwd( filename, LRECL ) ;
    for( i = 1; i <= num_jobsG ; i++ ){
	job = (JOBPTR) Ysafe_malloc( sizeof(JOB) ) ;
	job->job = i ;
	job->nodename = NIL(char *) ;
	job->directory = Ystrclone(filename) ;
	job->status = JOB_INIT ;
	job->errors = 0 ;
	job->priority = 1 ;
	Ydeck_enqueue( job_queueG, job ) ;
    }
    if( nopartitionsG ){
	/* this is a special job number for the no partition case */
	job->job = 0 ;
    }
} /* end find_partitions */

/* find a node that is not busy */
NODEPTR next_node()
{
    NODEPTR node ;             /* current node */

    /* try to start at beginning of the list nodes */
    /* first have higher priority */
    node = (NODEPTR) Yrbtree_enumerate( node_treeG, TRUE ) ;
    if( node && node->status == NODE_FREE ){
	return( node ) ;
    }
    while( node = (NODEPTR) Yrbtree_enumerate( node_treeG, FALSE ) ){
	if( node && node->status == NODE_FREE ){
	    return( node ) ;
	}
    }
    /* no available nodes */
    return( NIL(NODE *) ) ;
    
} /* end next_node */


/* return a  if work still needs to be done */
BOOL alloc_jobs()
{
    JOBPTR job ;               /* current job */
    NODEPTR node ;             /* current node */

    /* cases 
    CASE I - num_nodesG = 0 - no free nodes must wait 

    CASE II - num_jobs <= num_nodesG - easy case take 1st num_jobs nodes.

    CASE III - num_jobs > num_nodesG - schedule as many as possible.

    */
    if( num_jobsG <= 0 ){
	return(FALSE) ;
    }
    if( num_nodesG == 0 ){
	/* CASE I */
	return( TRUE ) ;

    } else if( num_jobsG <= num_nodesG ){
	/* CASE II */
	/* we are guaranteed at least one job */
	job = (JOBPTR) Ydeck_pop( job_queueG ) ;
	if(!(node = next_node() )){
	    /* no more available nodes */
	    return( TRUE ) ;
	}
	job->nodename = node->nodename ;
	job->status = node->status = JOB_SCHED ;
	node->job = job->job ;
	node->status = NODE_BUSY ;
	num_jobsG-- ;
	num_nodesG-- ;
	Ydeck_enqueue( job_schedG, job ) ;

	while( job = (JOBPTR) Ydeck_pop( job_queueG ) ){
	    if(!(node = next_node() )){
		/* no more available nodes */
		return( TRUE ) ;
	    }
	    job->nodename = node->nodename ;
	    job->status = node->status = JOB_SCHED ;
	    node->job = job->job ;
	    node->status = NODE_BUSY ;
	    num_jobsG-- ;
	    num_nodesG-- ;
	    Ydeck_enqueue( job_schedG, job ) ;
	}
    } else if( num_jobsG > num_nodesG ){
	/* do as many as we can */
	if(!(node = next_node() )){
	    /* no more available nodes */
	    return( TRUE ) ;
	}
	job = (JOBPTR) Ydeck_pop( job_queueG ) ;
	job->nodename = node->nodename ;
	job->status = node->status = JOB_SCHED ;
	node->job = job->job ;
	node->status = NODE_BUSY ;
	num_jobsG-- ;
	num_nodesG-- ;
	Ydeck_enqueue( job_schedG, job ) ;
	while( node = next_node() ){
	    job = (JOBPTR) Ydeck_pop( job_queueG ) ;
	    job->nodename = node->nodename ;
	    job->status = node->status = JOB_SCHED ;
	    node->job = job->job ;
	    node->status = NODE_BUSY ;
	    num_jobsG-- ;
	    num_nodesG-- ;
	    Ydeck_enqueue( job_schedG, job ) ;
	}
    }
    statusChangedG = TRUE ; /* need to redraw */
    return(TRUE) ;
} /* end alloc_jobs() */

INT execute_jobs()
{

    JOBPTR job ;               /* current job */
    char design[LRECL] ;       /* name of the design */
    char command[LRECL] ;      /* build the command to execute job */
    char **argv1 ;             /* argument vector for job */
    char *args ;               /* arguments for TimberWolf */
    char *disp ;               /* display for graphics */
    INT status ;               /* the job status */

    for( Ydeck_top(job_schedG);
	Ydeck_notEnd(job_schedG);Ydeck_down(job_schedG) ){
	job = (JOBPTR) Ydeck_getData( job_schedG ) ;
	if( job->status == JOB_RUNNING || job->status == JOB_COMPLETE ){
	    continue ;
	}
/* may need to add here */
	if( job->errors >= LIMIT ){
	    continue ;
	}
	/* now check the status of this job first */
	(VOID) check_job( job ) ;
	if( job->status == JOB_RUNNING || job->status == JOB_COMPLETE ){
	    continue ;
	}

	if( job->job == 0 ){
	    run_twsc_flat() ;
	    YexitPgm(PGMOK) ;
	} else {
	    sprintf( design, "%s:%d", cktNameG, job->job ) ;
	}
	if( remote_graphicsG && displayG ){
	    args = ARGS ;
	    disp = displayG ;
	} else {
	    args = NARGS ;
	    disp = ":0" ;
	}
	sprintf( command, "%s %s \\( %s %s %s %s %s %s %s %s \\) \\> %s \\&",
	    RSH, job->nodename, PSCHED, job->directory, job->nodename, 
	    TIMBERWOLF, args, design, flow_dirG, disp, OUTPUT ) ;
	D( "psc/execute_jobs", fprintf( stderr, "%s\n", command ) ) ;
	status = Ysystem( "rsh", NOABORT, command, NIL(char *) ) ;

	if( status == 0 ){
	    job->status = JOB_LOADED ;
	} else {
	    job->status = JOB_SCHEDFAIL;
	}
	statusChangedG = TRUE ; /* need to redraw */
    }
    return( CHECK_JOB ) ;
    
} /* execute_jobs */


/* when check finds a job has finished or one dies */
/* it sets status to ALLOC_JOB to allocate more jobs */
INT check_job( job )
JOBPTR job ;                   /* current job */
{

    char design[LRECL] ;       /* name of the design */
    char command[LRECL] ;      /* build the command to execute job */
    char buffer[LRECL]  ;      /* used to read the pipe channel */
    char **argv1 ;             /* argument vector for job */
    INT  status ;              /* return code of run_with_pipe */
    FILE *fp ;                 /* the pipe to read */
    INT numtokens ;            /* number of tokens found */
    char **tokens ;            /* tokens is static in Ystrparser */
    NODEPTR node ;             /* current node */
    NODE noderec ;             /* for searching for name */

    if(!(job)){
	return( CHECK_JOB ) ;
    }

    if( job->status == JOB_COMPLETE ){
	if( job->priority == 1 ){ /* this means job just finished */
	    /* we are done with a job try to allocate more */
	    /* free this node */
	    noderec.nodename = job->nodename ;
	    noderec.priority = UNKNOWN ;
	    node = (NODEPTR) Yrbtree_search( node_treeG, &noderec ) ;
	    if( node ){
		node->status = NODE_FREE ;
	    } else {
		M( ERRMSG, "check_job", "Can't find node in tree\n" ) ;
	    }
	    job->priority = 0 ;
	    num_nodesG++ ;
	}
	return( ALLOC_JOB ) ;
    }
    if( job->errors >= LIMIT ){
	return( CHECK_JOB ) ;
    }
    /* if we get here we want to check the status of a job */
    if( job->job == 0 ){
	sprintf( design, "%s", cktNameG ) ;
    } else {
	sprintf( design, "%s:%d", cktNameG, job->job ) ;
    }
    sprintf( command, "%s %s '%s %s %s %s'",
	RSHCHECK,job->nodename, CHECK, job->directory, job->nodename, design ) ;
    D( "psc/check_job", fprintf( stderr, "%s\n", command ) ) ;
    argv1 = create_argv( command ) ;
    if( fp = run_prog_with_pipe( argv1 ) ){
	while( fscanf( fp, "%s\n", buffer ) != EOF ){
	    D( "psc/check_job",
		fprintf( stderr, "check_status:We got:%s\n", buffer ) ;
	    ) ;
	    tokens = Ystrparser( buffer, " \t\n", &numtokens ) ;
	    if( numtokens == 1 ){
		if( strcmp( tokens[0], PROGRAM_OK ) == STRINGEQ ){
		    job->status = JOB_COMPLETE ;
		} else if( strcmp( tokens[0], EXEC_ERROR ) == STRINGEQ ){
		    job->status = JOB_SCHEDFAIL ;
		    job->errors++ ;
		} else if( strcmp( tokens[0], STATUS_ERROR )== STRINGEQ ){
		    job->status = JOB_CHECKFAIL ;
		    job->errors++ ;
		} else if( strcmp( tokens[0],PROGRAM_RUNNING)==STRINGEQ){
		    job->status = JOB_RUNNING ;
		} else if( strcmp( tokens[0],PROGRAM_ERROR) == STRINGEQ ){
		    job->status = JOB_ERROR ;
		    job->errors++ ;
		} else if( strcmp( tokens[0], STATUS_ERROR )== STRINGEQ ){
		    job->errors++ ;
		}
	    }
	}
	fclose( fp ) ;
	wait( &status ) ;
	statusChangedG = TRUE ; /* need to redraw */
    } else {
	job->status = JOB_CHECKFAIL ;
	G( TWmessage( "COULD NOT RUN CHECKER " ) ) ;
    }
    return( CHECK_JOB ) ;
} /* check_job */


run_twsc_flat()
{
    BOOL stateSaved ;
    char *twdir, *Ygetenv() ;
    char pathname[LRECL] ;
    INT  closegraphics() ;

    stateSaved = FALSE ;
    if( twdir = Ygetenv( "TWDIR" ) ){
	sprintf( pathname, "%s/bin/%s", twdir, TIMBERWOLF ) ;
    }
    if( graphicsG ){
	G( sprintf( YmsgG, "%s -wlt %s %d", 
	    pathname, cktNameG, TWsaveState() ) ) ;
	stateSaved = TRUE ;
    } else {  /* no graphics case */
	sprintf( YmsgG, "%s -nlt %s", pathname, cktNameG ) ;
    }
    M( MSG, NULL, YmsgG ) ;
    M( MSG, NULL, "\n" ) ;
    /* Ysystem will kill program if catastrophe occurred */
    Ysystem( TIMBERWOLF, ABORT, YmsgG, closegraphics ) ;
    /* ############# end of genrows execution ############# */

    if( stateSaved ){
	/* if we save the graphics state we need to restore it */
	G( TWrestoreState() ) ;
    }
} /* end run_twsc_flat */

check_jobs_initially()
{
    JOBPTR job ;                   /* current job */

    /* first check the scheduled jobs */
    for( Ydeck_top(job_schedG);
	Ydeck_notEnd(job_schedG);Ydeck_down(job_schedG) ) {
	job = (JOBPTR) Ydeck_getData( job_schedG ) ;
	check_job(job) ;
	/* if we find a schedule failure reshedule initially */
	if( job->status == JOB_SCHEDFAIL ){
	    job->status = JOB_SCHED ;
	}
    }
    /* now set the timer */
    Ytimer_elapsed( &last_timeS ) ;
    /* wait wait_to_settle amount of time before updating */
    last_timeS += WAIT_TO_SETTLE * MSEC_PER_SEC ;

} /* end check_jobs_initially */

/* get the next job in the circular queue */
JOBPTR next_job()
{
    JOBPTR job ;                   /* current job */
    INT i ;                        /* job counter */

#ifdef LATER
    for( i = 0 ; i <= total_jobsG; i++ ){
	/* circulate one more in the queue */
	job = (JOBPTR) Ydeck_pop( job_schedG ) ;
	/* put it back in the queue at the bottom */
	Ydeck_enqueue( job_schedG, job ) ;
	if( job->status != JOB_COMPLETE ){
	    return( job ) ;
	}
    }
#else
    job = (JOBPTR) Ydeck_pop( job_schedG ) ;
    /* put it back in the queue at the bottom */
    Ydeck_enqueue( job_schedG, job ) ;
#endif
    return( job ) ;

} /* next_job */

BOOL auto_flow()
{
    BOOL execute ;                     /* whether to keep executing */
    INT  cur_time ;                    /* check the time */
    static INT statusL = EXECUTE_JOB ; /* current step in algorithm */

    switch( statusL ){

	case EXECUTE_JOB:
	    /* when execute job is done it sets status to CHECK_JOB */
	    statusL = execute_jobs() ;
	    break ;

	case CHECK_JOB:
	    /* when check finds a job has finished or one dies */
	    /* it sets status to ALLOC_JOB to allocate more jobs */
	    /* only checks one job each time thru the loop */
	    Ytimer_elapsed( &cur_time ) ;
	    if( cur_time - last_timeS > update_timeS ){
		statusL = check_job( next_job() ) ;
		if( statusChangedG ){
		    last_timeS = cur_time ;
		}
	    }
	    break ;

	case ALLOC_JOB:
	    /* only alloc jobs can stop the cycle */
	    execute = alloc_jobs() ;
	    statusL = EXECUTE_JOB ;
	    break ;
    } /* end switch */

    return( execute ) ;
} /* auto_flow */
