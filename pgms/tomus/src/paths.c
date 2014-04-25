/* ----------------------------------------------------------------- 
FILE:	    paths.c
DESCRIPTION:output length of paths
CONTENTS:   print_paths.
	    INT calc_incr_time( cell ) 
		INT cell ;
	    update_time( cell ) 
		INT cell ;
	    INT calc_incr_time2( cella, cellb ) 
		INT cella, cellb ;
	    update_time2() 
	    init_path_set() 
	    add2path_set( path ) 
		INT  path ;
	    PSETPTR enum_path_set()
	    clear_path_set() 
	    init_net_set() 
	    add2net_set( net ) 
		INT  net ;
	    BOOL member_net_set( net )
	    clear_net_set() 
	    INT dcalc_full_penalty(newtimepenal)
	    INT dcalc_path_len(path_num)
		INT path_num ;
DATE:	    Oct	22, 1988 
REVISIONS:  Dec  3, 1988 - completed timing driven code.
	    Jan 29, 1989 - added \n's for pretty output.
	    Mar 11, 1989 - added statistics to print_paths.
			 - added wirelength to print_paths.
	    Mar 13, 1989 - now output penalty in print_paths.
	    Thu Dec 20 00:23:46 EST 1990 - removed += operator.
	    Fri Jan 18 18:33:25 PST 1991 - updated output format.
	    Thu Apr 18 01:52:21 EDT 1991 - added OOS for out of spec
		for easier searching.
	    Sun Apr 21 21:25:12 EDT 1991 - added ignore keyword for
		analyze nets.  Renamed for library stat function.
----------------------------------------------------------------- */
#ifndef lint
static char SccsId[] = "@(#) paths.c version 4.9 4/21/91" ;
#endif

/* #define ZERO_CHECK */

#include "standard.h"
#include "main.h"
#include <yalecad/debug.h>
#include "readnets.h"
#include <yalecad/message.h>
#include <yalecad/stat.h>
#include <yalecad/file.h>

/* global variables */
extern  DOUBLE avg_timeG ;/* average random time penalty */
extern  DOUBLE avg_funcG ;/* average random wirelength penalty */
INT dcalc_min_path_len() ;
INT dcalc_max_path_len() ;

static INT errorboundS = 0 ;

print_paths( ) 
{

    char filename[LRECL] ;
    INT i, pathLength ;
    INT length, loLength, hiLength ;
    INT above, really_above, really_below, below, in ;
    INT check, way_above, way_below ; 
    INT really_way_above, really_way_below ;
    INT *stat ;
    INT xspan, yspan ;
    PATHPTR pptr, get_path_list() ;
    GLISTPTR net ;
    DBOXPTR nptr ;
    PINBOXPTR netptr ;
    FILE *fp ;
    DOUBLE mean ;
    DOUBLE paths ;
    INT num_paths ;
    INT penaltyS ;

    i = 0 ;
    above = 0 ;
    really_above = 0 ;
    way_above = 0 ;
    really_way_above = 0 ;
    below = 0 ;
    really_below = 0 ;
    way_below = 0 ;
    really_way_below = 0 ;
    in = 0 ;
    penaltyS = 0 ;
    /* get total number of paths in timing analysis */
    num_paths = get_total_paths() ;
    /* allocate the an array for calculating statistics */
    if( num_paths ){
	stat = (INT *) Ysafe_malloc( num_paths * sizeof(INT) ) ;
    }
    sprintf(filename, "%s.pth" , cktNameG ) ;
    fp = TWOPEN( filename , "w", ABORT ) ;
    /* first the lengths of the nets */
    fprintf( fp, "The paths:\n" ) ;
    fprintf( fp, "##############################################\n" ) ;
    for( pptr=get_path_list() ;pptr;pptr=pptr->next ){
	pathLength = 0 ;
	loLength = 0 ;
	hiLength = 0 ;
	xspan = 0 ;
	yspan = 0 ;
	/* get pathLength for path */
	fprintf( fp, "\npath %3d:\n",++i ) ;
	for( net = pptr->nets ; net ; net = net->next ){
	    nptr = netarrayG[net->p.net] ;
	    fprintf( fp, "\t\t%s\n", nptr->name ) ;
	    length = (INT)(horizontal_path_weightG * (DOUBLE) nptr->halfPx) +
		 (INT)(vertical_path_weightG * (DOUBLE) nptr->halfPy) ;
	    pathLength += length ;
	    xspan += nptr->halfPx ;
	    yspan += nptr->halfPy ;
	    loLength = loLength + (INT)
		(nptr->max_driver * (float) length + nptr->driveFactor ) ;
	    hiLength = hiLength + (INT)
		(nptr->min_driver * (float) length + nptr->driveFactor ) ;
	}
	fprintf( fp, "\tpriority:%d lower_bound:%d upper_bound:%d\n",
	    pptr->priority, pptr->lower_bound, pptr->upper_bound ) ;
	fprintf( fp,"\tweighted length:%d fast driver len:%d slow driver len:%d\n",
	    pathLength, loLength, hiLength ) ;
	fprintf( fp, "\txspan:%d yspan:%d length:%d ", xspan, yspan,
	    xspan+yspan ) ;
	if( pptr->priority ){
	    ASSERT( loLength == pptr->lo_path_len,"print_paths",
		"lo_pathLength does not equal incremental value " ) ;
	    ASSERT( hiLength == pptr->hi_path_len,"print_paths",
		"hi_pathLength does not equal incremental value " ) ;
	}

	if( loLength < pptr->lower_bound ){
	    penaltyS += pptr->lower_bound - loLength ;
	    fprintf( fp, "OOS\n" ) ;
	    if( loLength < (INT)( 0.90 * (DOUBLE) pptr->lower_bound) ){
		below++ ;

		check = 0 ;
		for( net = pptr->nets ; net ; net = net->next ){
		    netptr = netarrayG[net->p.net]->pins ;
		    for( ; netptr ; netptr = netptr->next ) {
			if( netptr->cell > numcellsG ) {
			    check = 1 ;
			    break ;
			}
		    }
		}
		if( !check ) {
		    really_below++ ;
		}
	    }
	    if( loLength < (INT)( 0.80 * (DOUBLE) pptr->lower_bound) ){
		way_below++ ;
		if( !check ) {
		    really_way_below++ ;
		}
	    }
	} else if( hiLength > pptr->upper_bound ){
	    penaltyS += hiLength - pptr->upper_bound ;
	    fprintf( fp, "OOS\n" ) ;
	    if( hiLength > (INT)( 1.10 * (DOUBLE) pptr->upper_bound) ){
		above++ ;

		check = 0 ;
		for( net = pptr->nets ; net ; net = net->next ){
		    netptr = netarrayG[net->p.net]->pins ;
		    for( ; netptr ; netptr = netptr->next ) {
			if( netptr->cell > numcellsG ) {
			    check = 1 ;
			    break ;
			}
		    }
		}
		if( !check ) {
		    really_above++ ;
		}
	    }
	    if( hiLength > (INT)( 1.20 * (DOUBLE) pptr->upper_bound) ){
		way_above++ ;
		if( !check ) {
		    really_way_above++ ;
		}
	    }
	} else {
	    fprintf( fp, "\n" ) ;
	    in++ ;
	}
	/* add pathlength to stat array */
	stat[i-1] = pathLength ;
	
    }
    /* first the lengths of the nets */
    fprintf( fp, "\nThe nets:\n" ) ;
    fprintf( fp, "##############################################\n" ) ;
    for( i=1;i<=numnetsG;i++ ){
	nptr = netarrayG[i] ;
	fprintf( fp, "net %3d:%s xspan:%d yspan:%d length:%d numpins:%d",
	    i, nptr->name, nptr->halfPx, nptr->halfPy, 
	    (INT)(horizontal_path_weightG * (DOUBLE) nptr->halfPx) +
		 (INT)(vertical_path_weightG * (DOUBLE) nptr->halfPy),
	    nptr->numpins ) ;
	if( nptr->ignore ){
	    fprintf( fp, " ignored\n" ) ;
	} else {
	    fprintf( fp, "\n" ) ;
	}
    }
    /* avoid a divide by zero */
    if( num_paths ){
	paths = (DOUBLE) num_paths ;
	fprintf( fp, "\nSummary:\n" ) ;
	fprintf( fp, "Total wirelength               :%5d\n", funccostG ) ;
	fprintf( fp, "Total time penalty             :%5d\n", penaltyS ) ;
	fprintf( fp, "Number of paths                :%5d\n", num_paths ) ;
	fprintf( fp, "Number of active paths         :%5d\n", numpathsG ) ;
	fprintf( fp, "Number of paths 10%% below spec :%5d - %4.2f%%\n",
	    below, 100.0 * (DOUBLE) below / paths ) ;
	fprintf( fp, "Number of paths 10%% above spec :%5d - %4.2f%%\n",
	    above, 100.0 * (DOUBLE) above / paths ) ;
	fprintf( fp, "Number of paths within  spec   :%5d - %4.2f%%\n",
	    in, 100.0 * (DOUBLE) in / paths ) ;
	fprintf( fp, "# of non-pad paths out of spec :%5d\n", really_above +
						really_below ) ;
	fprintf( fp, "Number of paths 20%% below spec :%5d - %4.2f%%\n",
	    way_below, 100.0 * (DOUBLE) way_below / paths ) ;
	fprintf( fp, "Number of paths 20%% above spec :%5d - %4.2f%%\n",
	    way_above, 100.0 * (DOUBLE) way_above / paths ) ;
	fprintf( fp, "# of non-pad paths out of spec :%5d\n", 
				really_way_above + really_way_below ) ;
	fprintf( fp, "Min  length                    :%4.2le\n",
	    Ystat_min( stat, num_paths, sizeof(INT) ) ) ;
	fprintf( fp, "Max  length                    :%4.2le\n",
	    Ystat_max( stat, num_paths, sizeof(INT) ) ) ;
	mean = Ystat_mean( stat, num_paths, sizeof(INT) ) ;
	fprintf( fp, "Mean length                    :%4.2le\n", mean ) ;
	fprintf( fp, "Standard Dev. length           :%4.2le\n",
	    sqrt( Ystat_var( stat, num_paths, sizeof(INT),mean) ) ) ;
	Ysafe_free( stat ) ;
    }
    TWCLOSE( fp ) ;

} /* end print_paths */

/* ----------------------------------------------------------------- 
    The update path routines
    The incremental routines speed execution by looking at only those
    paths connected to the cells that are to be moved.  In addition,
    only those nets which are modified by the move are updated.  This
    gives us an incremental length which we add to old half perimeter
    to give us total lenght of this net.  The penalty is based on this
    length.  We calculate an incremental penalty based on the change
    in the penalty.
----------------------------------------------------------------- */
/* calculate the timing cost incrementally */
INT calc_incr_time( cell ) 
INT cell ;
{
    INT newpenal ;        /* proposed move's timing penalty delta */
    INT oldpenal ;        /* the old penalty of the nets that move */
    INT loLength ;        /* lo path length incremental */
    INT hiLength ;        /* hi path length incremental */
    INT path_num ;        /* name of path */
    INT net ;             /* net of path */
    INT length ;          /* path length incremental */
    GLISTPTR pptr ;       /* pointer to paths of a cell */
    GLISTPTR net_of_path ;
    PATHPTR path ;
    DBOXPTR dimptr ;

    newpenal = 0 ;
    oldpenal = 0 ;
    /* for all paths of the cell that has moved */
    for( pptr = carrayG[cell]->paths; pptr ; pptr = pptr->next ) {

	loLength = 0 ;
	hiLength = 0 ;
	path_num = pptr->p.path ;
	ASSERTNCONT( path_num > 0 && path_num <= numpathsG,
	    "calc_incr_time", "path is out of bounds" ) ;
	path = patharrayG[path_num] ;
	/* for all nets k of a path i */
	for( net_of_path=path->nets;net_of_path;
	    net_of_path=net_of_path->next ){
	    net = net_of_path->p.net ;

	    dimptr = netarrayG[net] ;

	    /* accumulate length of path */
	    if( member_net_set( net ) ){
		/* this half - perimeter has changed use update */
		/* calculate total change on path */
		length =  (INT) 
		    (horizontal_path_weightG * (DOUBLE) dimptr->newhalfPx ) ;
		length = length - (INT) 
		    (horizontal_path_weightG * (DOUBLE) dimptr->halfPx ) ;
		length = length + (INT) 
		    (vertical_path_weightG * (DOUBLE) dimptr->newhalfPy ) ;
		length = length - (INT) 
		    (vertical_path_weightG * (DOUBLE) dimptr->halfPy ) ;
		loLength = loLength + (INT) 
		    (dimptr->max_driver * (DOUBLE) length + dimptr->driveFactor ) ;
		hiLength = hiLength + (INT) 
		    (dimptr->min_driver * length + dimptr->driveFactor ) ;
	    } /* else this half - perimeter has not changed use old */
	}
	/* save total result - change to total length */
	path->new_lo_path_len = loLength += path->lo_path_len ;
	path->new_hi_path_len = hiLength += path->hi_path_len ;

	ASSERT( dcalc_min_path_len(path_num,loLength),"update_time",
	    "length mismatch" ) ;
	ASSERT( dcalc_max_path_len(path_num,hiLength),"update_time",
	    "length mismatch" ) ;

	/* calculate change in timing penalty */
	/* no penalty if within target window */
	/* lowerbound <= length <= upperbound */
	if( hiLength > path->upper_bound ){
	    newpenal += hiLength - path->upper_bound ; 
	} else if( loLength < path->lower_bound ){
	    newpenal += path->lower_bound - loLength ;
	}
	/* now the old penalty */
	if( path->hi_path_len > path->upper_bound ){
	    oldpenal += path->hi_path_len - path->upper_bound ; 
	} else if( path->lo_path_len < path->lower_bound ){
	    oldpenal += path->lower_bound - path->lo_path_len ;
	}
    } /* end loop on the paths of a cell */
    /* return the change in penalty */
    return( newpenal - oldpenal ) ;

} /* end function calc_incr_time */


update_time( cell ) 
INT cell ;
{

    INT path_num ;        /* name of path */
    GLISTPTR pptr ;       /* pointer to paths of a cell */
    PATHPTR path ;

    /* for all paths of the cell that has moved */
    for( pptr = carrayG[cell]->paths; pptr ; pptr = pptr->next ) {

	path_num = pptr->p.path ;
	ASSERTNCONT( path_num > 0 && path_num <= numpathsG,
	    "update_time", "path is out of bounds" ) ;
	path = patharrayG[path_num] ;
	/* keep result */
	path->lo_path_len = path->new_lo_path_len ;
	path->hi_path_len = path->new_hi_path_len ;
    }

} /* end function update_time */

/* calculate the timing cost incrementally for two cells */
INT calc_incr_time2( cella, cellb ) 
INT cella ;
INT cellb ;
{
    INT newpenal ;        /* proposed move's timing penalty delta */
    INT oldpenal ;        /* the old penalty of the nets that move */
    INT loLength ;        /* lo path length incremental */
    INT hiLength ;        /* hi path length incremental */
    INT path_num ;        /* name of path */
    INT net ;             /* net of path */
    INT length ;          /* path length incremental */
    GLISTPTR pptr ;       /* pointer to paths of a cell */
    GLISTPTR net_of_path ;
    PATHPTR path ;
    PSETPTR pathlist, enum_path_set() ;
    DBOXPTR dimptr ;

    newpenal = 0 ;
    oldpenal = 0 ;
    clear_path_set() ;

    /* use add2path_set to get union of paths from cella and cellb */
    for( pptr = carrayG[cella]->paths; pptr ; pptr = pptr->next ) {
	add2path_set( pptr->p.path ) ;
    }
    for( pptr = carrayG[cellb]->paths; pptr ; pptr = pptr->next ) {
	add2path_set( pptr->p.path ) ;
    }


    /* now use UNIQUE list of the union of the two cell's paths */
    for( pathlist=enum_path_set(); pathlist; pathlist=pathlist->next){

	loLength = 0 ;
	hiLength = 0 ;
	path_num = pathlist->path ;
	ASSERTNCONT( path_num > 0 && path_num <= numpathsG,
	    "calc_incr_time2", "path is out of bounds" ) ;
	path = patharrayG[path_num] ;

	/* for all nets k of a path i */
	for( net_of_path=path->nets;net_of_path;
	    net_of_path=net_of_path->next ){
	    net = net_of_path->p.net ;

	    dimptr = netarrayG[net] ;

	    /* accumulate length of path */
	    if( member_net_set( net ) ){
		/* this half - perimeter has changed use update */
		/* calculate total change on path */
		length =  (INT) 
		    (horizontal_path_weightG * (DOUBLE) dimptr->newhalfPx ) ;
		length = length - (INT) 
		    (horizontal_path_weightG * (DOUBLE) dimptr->halfPx ) ;
		length = length + (INT) 
		    (vertical_path_weightG * (DOUBLE) dimptr->newhalfPy ) ;
		length = length - (INT) 
		    (vertical_path_weightG * (DOUBLE) dimptr->halfPy ) ;
		loLength = loLength + (INT) 
		    (dimptr->max_driver * (DOUBLE) length + dimptr->driveFactor ) ;
		hiLength = hiLength + (INT) 
		    (dimptr->min_driver * length + dimptr->driveFactor ) ;
	    } /* else this half - perimeter has not changed use old */
	}
	/* save total result - change to total length */
	path->new_lo_path_len = loLength += path->lo_path_len ;
	path->new_hi_path_len = hiLength += path->hi_path_len ;

	ASSERT( dcalc_min_path_len(path_num,loLength),"update_time",
	    "length mismatch" ) ;
	ASSERT( dcalc_max_path_len(path_num,hiLength),"update_time",
	    "length mismatch" ) ;

	/* calculate change in timing penalty */
	/* no penalty if within target window */
	/* lowerbound <= length <= upperbound */
	if( hiLength > path->upper_bound ){
	    newpenal += hiLength - path->upper_bound ; 
	} else if( loLength < path->lower_bound ){
	    newpenal += path->lower_bound - loLength ;
	}
	/* now the old penalty */
	if( path->hi_path_len > path->upper_bound ){
	    oldpenal += path->hi_path_len - path->upper_bound ; 
	} else if( path->lo_path_len < path->lower_bound ){
	    oldpenal += path->lower_bound - path->lo_path_len ;
	}
    } /* end loop on paths */
    /* return the change in penalty */
    return( newpenal - oldpenal ) ;

} /* end function calc_incr_time2 */

update_time2() 
{
    PATHPTR path ;
    PSETPTR pathlist, enum_path_set() ;

    /* now use UNIQUE list of the union of the two cell's paths */
    for( pathlist=enum_path_set(); pathlist; pathlist=pathlist->next){

	ASSERTNCONT( pathlist->path > 0 && pathlist->path <= numpathsG,
	    "update_time2", "path is out of bounds" ) ;
	path = patharrayG[pathlist->path] ;
	/* keep result */
	path->lo_path_len = path->new_lo_path_len ;
	path->hi_path_len = path->new_hi_path_len ;
    }

} /* end function update_time */
/* ----------------------------------------------------------------- 
   The set required in the update path routines needs the following
   operations done efficiently :
       membership - O(1)
       add to set if unique - O(1)
       clear set  - O(1)
       set enumeration - O( paths in set )
Below is a space hungry O( numpaths ) but time efficient implementation
We combine two data structures to accomplish this goal. We use array 
for testing membership and uniqueness but use list for enumeration.
By incrementing count we can reinitialize easily.
Note: PSETBOX, PSETPTR definitions are in custom.h
----------------------------------------------------------------- */
static PSETPTR path_set_listS ;   /* list is beginning of set as a list */
static PSETPTR *path_set_arrayS ; /* set is an array of path set boxes */
static INT path_set_countS ;      /* current set count */

/* initialize set */
init_path_set() 
{   
    INT i ;

    path_set_arrayS=(PSETPTR *)Ysafe_malloc((numpathsG+1)*sizeof(PSETPTR));
    for( i=0;i<=numpathsG;i++ ){
	path_set_arrayS[i] = (PSETPTR) Ysafe_calloc( 1, sizeof(PSETBOX) ) ;
    }
    path_set_countS = 1 ;
    path_set_listS = NULL ;
} /* end initset */

/* add a path to the set if not already in set */
add2path_set( path ) 
INT  path ;
{  
    PSETPTR temp, cpath ;

    if( path >= 1 && path <= numpathsG ){
	cpath = path_set_arrayS[path] ;
	/* something is a member in set is counts match */
	if( cpath->member != path_set_countS ){
	    /* new path to be added */
	    /* connect to the single linked list */
	    if( temp = path_set_listS ){
		/* hook to old list */
		path_set_listS = cpath ;
		cpath->next = temp ;
	    } else {
		path_set_listS = cpath ;
		/* terminate new list */
		cpath->next = NULL ;
	    }
	    cpath->path = path ; /* store data */
	    cpath->member = path_set_countS ; /* store membership */
	}

    } else {
	M( ERRMSG, "ADD2SET","value of path is out of bounds of set\n" ) ;
    }
} /* end add2path_set */

PSETPTR enum_path_set()
{
    return( path_set_listS ) ;
}

clear_path_set() 
{
    path_set_countS ++ ;
    path_set_listS = NULL ;
} /* end clear_path_set */

/* ----------------------------------------------------------------- 
   Below is a second set of set routines required in the update path
   routines which operate on nets instead of paths.  The following
   operations need to be done efficiently :
       membership - O(1)
       add to set if unique - O(1)
       clear set  - O(1)
   Since we don't need to enumerate set we only need array to implement
   this set.  
----------------------------------------------------------------- */
static INT *net_set_array ; /* set is an array of net set boxes */
static INT net_set_count ;      /* current set count */

/* initialize set */
init_net_set() 
{   
    net_set_array = (INT *) Ysafe_calloc((numnetsG+1), sizeof(INT) );
    net_set_count = 1 ;
} /* end initset */

/* add a net to the set if not already in set */
add2net_set( net ) 
INT  net ;
{  
    if( net >= 1 || net <= numnetsG ){
	/* current count make array member a valid member of set */
	net_set_array[net] = net_set_count ;

    } else {
	M( ERRMSG, "ADD2SET", "value of path is out of bounds of set" ) ;
    }
} /* end add2net_set */

BOOL member_net_set( net )
/* test for membership */
{
    if( net_set_array[net] == net_set_count ){
	return( TRUE ) ;
    } else {
	return( FALSE ) ;
    }
} /* end member_net_set */

clear_net_set() 
{
    /* to clear set we only need to increment net_set_count */
    /* we can use this set up to 2 Gig times without any problem */
    net_set_count ++ ;
} /* end clear_path_set */

/* *************** DEBUG FUNCTIONS *************************** */
/* debug function to make sure calculation is correct */
INT dcalc_full_penalty( newtimepenal )
INT newtimepenal ;
{
    INT timingpenal ;
    INT pathcount ;
    INT low_length ;      /* lo path length */
    INT high_length ;     /* hi path length */
    INT length ;          /* path length incremental */
    INT net ;             /* net of path */
    GLISTPTR net_of_path ;
    PATHPTR path ;
    DBOXPTR dimptr ;

    /* now calculate the penalties */
    /* first the timing penalty */
    timingpenal = 0 ;
    for( pathcount = 1 ; pathcount <= numpathsG ; pathcount++ ) {

	path = patharrayG[pathcount] ;
	ASSERTNCONT( path, "dcalc_full_penalty", 
	    "pointer to path is NULL" ) ;
	/* for all nets k of a path i */
	low_length = 0 ;
	high_length = 0 ;
	for( net_of_path=path->nets;net_of_path;
	    net_of_path=net_of_path->next ){
	    net = net_of_path->p.net ;
	    dimptr = netarrayG[net] ;

	    /* accumulate length of path */
	    if( member_net_set( net ) ){
		/* this half - perimeter has changed use update */
		/* calculate total change on path */
		length = (INT) 
		    (horizontal_path_weightG * (DOUBLE) dimptr->newhalfPx ) ;
		length = length + (INT) 
			 (vertical_path_weightG * (DOUBLE) dimptr->newhalfPy) ;
	    } else {
		/* old length */
		length = (INT) 
		    (horizontal_path_weightG * (DOUBLE) dimptr->halfPx) ;
		length = length + (INT) 
		    (vertical_path_weightG * (DOUBLE) dimptr->halfPy ) ;
	    }
	    low_length = low_length + (INT)
		(dimptr->max_driver * (DOUBLE) length + dimptr->driveFactor );
	    high_length = high_length + (INT)
		(dimptr->min_driver * (DOUBLE) length + dimptr->driveFactor );
	}
	/* calculate penalty */
	/* no penalty if within target window */
	/* lowerbound <= length <= upperbound */
	if( high_length > path->upper_bound ){
	    timingpenal += high_length - path->upper_bound ; 
	} else if( low_length < path->lower_bound ){
	    timingpenal += path->lower_bound - low_length ;
	}
    }
    if( ABS( timingpenal - newtimepenal ) > errorboundS ){
	errorboundS = ABS( timingpenal - newtimepenal ) ;
	return( FALSE ) ;
    } else {
	return( TRUE ) ;
    }
}

INT dcalc_min_path_len(path_num,loPath)
INT path_num ;
INT loPath ;
{

    INT loLength ;        /* lo path length */
    INT net ;             /* net of path */
    INT length ;          /* path length incremental */
    GLISTPTR net_of_path ;
    PATHPTR path ;
    DBOXPTR dimptr ;

    path = patharrayG[path_num] ;
    /* for all nets k of a path i */
    loLength = 0 ;
    for( net_of_path=path->nets;net_of_path;
	net_of_path=net_of_path->next ){
	net = net_of_path->p.net ;
	dimptr = netarrayG[net] ;

	/* accumulate length of path */
	if( member_net_set( net ) ){
	    /* this half - perimeter has changed use update */
	    /* calculate total change on path */
	    length = (INT) 
		(horizontal_path_weightG * (DOUBLE) dimptr->newhalfPx);
	    length = length + (INT) 
		(vertical_path_weightG * (DOUBLE) dimptr->newhalfPy) ;
	} else {
	    /* old length */
	    length = (INT) 
		(horizontal_path_weightG * (DOUBLE) dimptr->halfPx ) ;
	    length = length + (INT) 
		(vertical_path_weightG * (DOUBLE) dimptr->halfPy ) ;
	}
	loLength = loLength + (INT)
	    (dimptr->max_driver * (DOUBLE) length + dimptr->driveFactor );
    }
    if( ABS( loPath - loLength ) > errorboundS ){
	errorboundS = ABS( loPath - loLength ) ;
	return( FALSE ) ;
    } else {
	return( TRUE ) ;
    }
}

INT dcalc_max_path_len(path_num,hiPath)
INT path_num ;
INT hiPath ;
{

    INT hiLength ;        /* lo path length */
    INT net ;             /* net of path */
    INT length ;          /* path length incremental */
    GLISTPTR net_of_path ;
    PATHPTR path ;
    DBOXPTR dimptr ;

    path = patharrayG[path_num] ;
    /* for all nets k of a path i */
    hiLength = 0 ;
    for( net_of_path=path->nets;net_of_path;
	net_of_path=net_of_path->next ){
	net = net_of_path->p.net ;
	dimptr = netarrayG[net] ;

	/* accumulate length of path */
	if( member_net_set( net ) ){
	    /* this half - perimeter has changed use update */
	    /* calculate total change on path */
	    length = (INT) 
		(horizontal_path_weightG * (DOUBLE) dimptr->newhalfPx);
	    length = length + (INT) 
		(vertical_path_weightG * (DOUBLE) dimptr->newhalfPy) ;
	} else {
	    /* old length */
	    length = (INT) 
		(horizontal_path_weightG * (DOUBLE) dimptr->halfPx ) ;
	    length = length + (INT) 
		(vertical_path_weightG * (DOUBLE) dimptr->halfPy ) ;
	}
	hiLength = hiLength + (INT)
	    (dimptr->min_driver * length + dimptr->driveFactor );
    }
    if( ABS( hiPath - hiLength ) > errorboundS ){
	errorboundS = ABS( hiPath - hiLength ) ;
	return( FALSE ) ;
    } else {
	return( TRUE ) ;
    }
}

INT dprint_error()
{
    sprintf( YmsgG, 
	"\n\nWe found that the timing error was bound by :%d\n\n", 
	errorboundS ) ;
    M( MSG, "dprint_error", YmsgG ) ;
    return( 0 ) ;
} /* end dprint_error() */

dverify_nets()
{

    INT net ;             /* net of path */
    INT per ;
    DBOXPTR dimptr ;

    for( net=1; net <= numnetsG; net++ ){
	dimptr = netarrayG[net] ;
	per = dimptr->xmax - dimptr->xmin ;
	ASSERTNCONT( per == dimptr->halfPx, "dverify_nets", "problem") ;
	per = dimptr->ymax - dimptr->ymin ;
	ASSERTNCONT( per == dimptr->halfPy, "dverify_nets", "problem") ;
    }
} /* end dverify_nets */



#define TIMEDAMPFACTOR   1.0     /* damping factor on time penalty */

DOUBLE calc_time_factor() 
{
    /* **** timing penalty controller **** */

#ifdef ZERO_CHECK
    timeFactorG = 0.0 ;
#else
    if( avg_timeG == 0.0 ) {
	timeFactorG = 3.0 ;
    } else {
	timeFactorG = 3.0 * (DOUBLE) avg_funcG / (DOUBLE) avg_timeG ;
    }
#endif
    return( timeFactorG ) ;

} /* end function calc_time_penalty */



calc_init_timeFactor() 
{

#ifdef ZERO_CHECK
    timeFactorG = 0.0 ;
#else
    timeFactorG = 4.0 ;
#endif
    fprintf(fpoG,"\n\nTIMING FACTOR (COMPUTED) : %f\n", timeFactorG ) ;

} /* end calc_init_timeFactor */
