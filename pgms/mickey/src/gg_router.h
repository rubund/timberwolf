#ifndef lint
static char gg_routerId[] = "@(#)gg_router.h	Yale Version 3.2 5/23/91" ;
#endif
/* -----------------------------------------------------------------

	FILE:		gg_router.h
	AUTHOR:		Dahe Chen
	DATE:		Thu Feb 2 23:15:13 EDT 1989
	CONTENTS:	
	REVISION:
		Thu Oct  4 20:11:25 EDT 1990
	    Change the array name for SCCS.
		Tue Oct 23 00:30:59 EDT 1990
	    Deleted reference to limits.h and strings.h
	    since they cause problems on the SUN.
		Mon Nov 12 11:23:57 EST 1990
	    Add the parameter graphicsG to control graphics.
		Thu Nov 29 15:49:08 EST 1990
	    Remove x/y fields from the data structure for pins.
		Wed Dec  5 12:49:52 EST 1990
	    Add width field in the data structure for channels
	    in the edge array of a channel graph.
		Thu May 23 17:55:03 EDT 1991
	    Add a new field "empty" in earray.

----------------------------------------------------------------- */

#include	<stdio.h>
#include	<assert.h>

#ifdef	MAIN_VARS
#define	GEXTERN
#else
#define	GEXTERN	extern
#endif

/*######################################################################*/
/*------------------------------------------------------------------------
	DATA STRUCTURES FOR A CHANNEL GRAPH AND SHORTEST PATH TREE
------------------------------------------------------------------------*/
typedef struct node {		/* record for one of the vertices	*/
    short	vertex	   ;	/* self index				*/
    short	status	   ;	/* used to check feasible path		*/
    short	set	   ;	/* index for components			*/
    int		xpos	   ;	/* x coordinate of the vertex		*/
    int		ypos	   ;	/* y coordinate of the vertex		*/
    struct list *first	   ;	/* list of adjacent nodes		*/
    struct tree **tree	   ;	/* shortest path tree among vertices	*/
} NODE,
*NODEPTR;

typedef struct list {		/* record an adjacent node		*/
    short     edge	;	/* self index				*/
    short     f_vertex	;	/* the from_vertex index		*/
    short     t_vertex	;	/* the to_vertex index			*/
    int       length	;	/* the length of the edge		*/
    struct list *next	;
} LIST,
*LISTPTR;

typedef struct edge {
    short	edge	;	/* self index				*/
    short	group	;	/* index for equivalent group		*/
    short	node[2]	;	/* two endpoints of edge --- channel	*/
    int		numpins	;	/* number of pins on edge --- channel	*/
    int  	length	;	/* length of edge --- channel		*/
    int		width	;	/* minimum width associated with edge	*/
    unsigned	intree	;	/* indicator for minimum Steiner trees	*/
    int		empty	;	/* indicator of adjacent empty room	*/
} EDGE ,
*EDGEPTR ;

/*------------------------------------------------------------------------
	DATA STRUCTURES FOR SHORTEST PATH TREES
------------------------------------------------------------------------*/
typedef struct tree {		/* shortest path tree			*/
    short	parent	;	/* parent vertex of this vertex in tree */
    short	root	;	/* root of path tree			*/
    short	self	;	/* self index				*/
    short	edge	;	/* edge index				*/
    short	status	;	/* used for finding shortest path tree	*/
    int		dist	;	/* distance from root			*/
} TREE ,
*TREEPTR ;
/*######################################################################*/


/*######################################################################*/
/*------------------------------------------------------------------------
	    DATA STRUCTURES FOR NET INFORMATION
------------------------------------------------------------------------*/
typedef struct pin {		/* pin array				*/
    short	node[2]	;	/* index of two adjacent vertices	*/
    short	edge	;	/* edge index on wich the pin locates	*/
    short	numpin	;
    short	pin[2]	;	/* indicator of pin on same channel	*/
    short	vertex	;	/* pin index				*/
    short	shifted	;	/* indicate pin is shifted from node	*/
    short	equiv	;	/* indicate it is an equivalent pin	*/
    short	density	;	/* current density at this pin		*/
    int		dist[2]	;	/* distance to adjcent vertices or pins */
    int		key	;	/* used to sort parray			*/
    struct pin *next	;
} PIN ,
*PINPTR ;
/*######################################################################*/

GEXTERN char cktName[64] ;
GEXTERN char netName[64] ;

GEXTERN	int  DIGITAL	;	/* Indicator for circuit style		*/
GEXTERN	int  EXTERNAL	;	/* Indicator for route storage		*/
GEXTERN	int  EQUIVAL	;	/* Indicator for equivalent pins	*/
GEXTERN	int  CASE	;	/* Indicator for objective function	*/
GEXTERN	int  SHIFTED	;	/* Indicator for pins shifted		*/
GEXTERN	int  THRESHOLD	;	/* Threshold for restoring g(e)array	*/

GEXTERN int  xmin	;
GEXTERN int  ymin	;
GEXTERN int  xmax	;
GEXTERN int  ymax	;

GEXTERN int  maxpins	;
GEXTERN int  maxedges	;

GEXTERN int  NUMTREES	;	/* number of routes generated for a net	*/
GEXTERN int  numedges	;	/* number of edges in graph		*/
GEXTERN int  numnets	;	/* number of nets in circuit		*/
GEXTERN int  numnodes	;	/* number of nodes in graph		*/
GEXTERN int  numpins	;	/* number of pins in a net		*/
GEXTERN int  numtrees	;	/* number of paths for a net		*/
GEXTERN int  numcomps	;	/* number of components in 1st tree	*/
GEXTERN int  numsets	;	/* number of sets of equivalent pins	*/
GEXTERN int  totnodes	;	/* numnodes plus number of pins		*/
GEXTERN int  totedges	;	/* numedges plus number of pins		*/
GEXTERN int  totroutes	;	/* number of total routes for all nets	*/

GEXTERN int  graphicsG	;

GEXTERN int    **darray	;
GEXTERN int     *dad	;
GEXTERN int     *val	;

GEXTERN FILE	*fdat	;
GEXTERN FILE	*fin	;
GEXTERN FILE	*fout	;

GEXTERN NODEPTR	*garray	;
GEXTERN NODEPTR	*sarray	;
GEXTERN EDGEPTR	*earray	;
GEXTERN EDGEPTR	*carray	;
GEXTERN PINPTR	*parray	;
