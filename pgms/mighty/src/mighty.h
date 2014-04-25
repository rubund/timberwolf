/***********************************************************************
 *
 * This file contains things needed by all other files.  For example,
 * including <stdio.h>, and structure declarations.
 *
 **********************************************************************/
#ifndef MIGHTY_H

#define MIGHTY_H

#ifndef LINT
static char Mighty_hID[] = "@(#) mighty.h (Yale) version 6.2 10/14/90" ;
#endif


/***********************************************************************
 *
 * Include files
 *
 **********************************************************************/

#include <stdio.h>
#include <math.h>
#include <yalecad/base.h>

/***********************************************************************
 *
 * Defines
 *
 **********************************************************************/
/* added following definition to run memory management system WPS */
#define malloc(a)           (Ysafe_malloc(a) )
#define alloc(a,b)          (Ysafe_calloc(a,b) )
#define calloc(a,b)         (Ysafe_calloc(a,b) )
#define realloc(a,b)        (Ysafe_realloc(a,b) )
#define free(a)             (Ysafe_free(a) )
#define cfree(a)            (Ysafe_cfree(a) )

/* used in rectangle/path data structure */
#define THREE 3
#define HORIZ 2
#define VERT 1

#define NEVER 2
#define MAYBE 3

#define PERM 4
#define TEMP 5

/* possible input/output formats */
#define HUMAN 1
#define MACHINE 2

/* edges of the channel and search directions */
#define TOP 1
#define BOTTOM 2
#define LEFT 3
#define RIGHT 4
#define UP 5
#define DOWN 6
#define SWITCH 7

/* direction of the boundary paths */
#define CW  0   /* clockwise direction */
#define CCW 1   /* counter clockwise direction */

/* LOW MED HIGH and INFINITY are used for the cost matrix */
#define LOW 1
#define MED 100
#define HIGH 10000
#ifdef INFINITY
#undef INFINITY
#endif
#define INFINITY 1000000
#define MINFINITY -1000000

/* so we can run on machines that don't know what void means */
#define void int

/* used for testing just a random number */
#define USERGIVEN 298674980

/***********************************************************************
 *
 * Macro
 *
 **********************************************************************/

#define number_to_name(A) name_arrayG[A]


/***********************************************************************
 *
 * Data Structure Definitions
 *
 **********************************************************************/


typedef struct linked_list_of_ints
{
    struct linked_list_of_ints
	*next;			/* next element in the list */
    int net;			/* the net name */
    int priority;               /* priority in scheduling */
} SCHED_ELEMENT, *SCHED_PTR;



typedef struct linked_list_of_searchq
{
    struct linked_list_of_searchq
	*next;			/* next rectangle in the list */
    int layer;			/* which layer this rectangle goes on, either
				   HORIZ or VERT */
    int group;			/* group number to identify each component */
    int x,
	y;			/* point */
} SEARCH, *SEARCHPTR;



typedef struct linked_list_of_pins
{
    struct linked_list_of_pins
	*next;			/* next rectangle in the list */
    int layer;			/* which layer this rectangle goes on, either
				   HORIZ or VERT */
    int group;			/* group number to identify each component */
    int type;			/* permanent or temporary pin */
    int equiv;			/* class of equivalent pins */
    int x,
	y;			/* point */
    int x_given,
	y_given;		/* point given by user before gridding */
} PIN, *PINPTR;



typedef struct linked_list_of_links
{
    struct linked_list_of_links
    	*netnext;		/* next link of the net */
    int layer;			/* which layer this rectangle goes on, either
				   HORIZ or VERT */
    int net;
    int group;			/* group number to identify each component */
    union {
	BOOL user_given ;       /* flag used in output routine  */
	int  edge_direction ;   /* direction of macro edge */
    } p ; 
    int x1,
	x2,
	y1,
	y2;			/* two end points */
} LINK, *LINKPTR;

typedef struct macrobox {       /* keep a list of macro cells */
    LINKPTR edges ;
    struct macrobox *next ;
} MACROBOX, *MACROPTR ;


typedef struct linked_list_of_linklist
{
    struct linked_list_of_linklist
	*next;			/* next linklist */
    LINKPTR link;
} LINKLIST, *LINKLISTPTR;



typedef struct linked_list_of_int
{
    struct linked_list_of_int
	*next;			/* next element in the list */
    int value;			/* the value of this element */
} INT_LIST_ELEMENT, *INT_LIST,
  INT_STACK_ELEMENT, *INT_STACK;



typedef struct markable_linked_list_of_nets
{
    struct markable_linked_list_of_nets
	*next;			/* Next element in the list */
    struct a_net *net;		/* Pointer to a net in the list */
    int marked;			/* Flag used to traverse the vertical
				   constraint graph while calculating the
				   levels and breaking cycles */
    INT_LIST col_list;		/* list of columns that cause this edge */
    int break_value;		/* used when deciding which edge to remove to
				   break a cycle int the VCG */
} NET_LIST_ELEMENT_M, *NET_LIST_M;



typedef struct a_net
{
    int name;			/* Name of this net, used for input and
				   output only */
    PINPTR pin,			/* List of permanent pins */
	   tmppin;		/* List of temporary pins */
    LINKPTR path,		/* Can be merged with PATH structure */
            tmplist,		/* tmp path list */
	    oldpath,		/* Keep old path during improve */
	    oldtmplist;
    int numequiv;		/* Number of class of equivalent pins */

    int left;			/* mark left going net */
    int right;			/* mark right going net */
    int colleft;		/* left most column */
    int colright;		/* right most column */

    int sens;                   /* Sensitivity YES or NO */
    int cost;                   /* Cost of tmp path */
    int oldcost;                /* Cost of old tmp path - for comparison*/
    int difficulty,		/* How difficult to route this net */
	marked;			/* To see if it is on the rerouting
				   path */
    int level_from_top,		/* Number of rows which must be above this
				   net to avoid vertical constraint
				   violations */
	level_from_bottom;	/* Number of rows which must be below this
				   net */
    NET_LIST_M parents,		/* Pointer to first element in list of
				   parents of this net in the vertical
				   constraint graph */
	       children;	/* Pointer to first element in list of
				   children of this net in the vertical
				   constraint graph */
    int available;		/* used to find cycles in the vertical
				   constraint graph */
} NET, *NETPTR;


typedef struct a_channel
{
    int **vert_layer,		/* each element in the matrix is the number
				   of the net that occupies that rectangle in
				   the layer used primarily for vertical
				   routing.  Dimensions are:
				   [number of rows][number of columns + 2]
				    */
	**horiz_layer;		/* same as vert_layer, but for the layer used
				   primarily for horizontal routing */
    int **pin_layerh,		/* layer to mark pin locations */
        **pin_layerv,		/* layer to mark pin locations */
	**hcomp,                /* connected component_id during finding
				   path, for horiz_layer  */
	**vcomp;		/* for vert_layer */
} CHANNEL, *CHANNELPTR;



typedef struct linked_list_of_cycles
{
    struct linked_list_of_cycles
	*next;			/* next cycle in the list */
    int size;			/* number of nodes in the cycle */
    NETPTR *nets;		/* array of nets that form a cycle, nets[0]
				   tells how many nets in the cycle, nets[1]
				   through nets[nets[0]] are the nets,
				   nets[nets[0]+1] is the same as nets[1] to
				   make the algorithms simpler */
} CYCLE_ELEM, *CYCLE_LIST;


typedef struct list_of_net_pairs
{
    struct list_of_net_pairs
	*next;			/* next net_pair in the list */
    NETPTR upper_net,		/* the parent net */
	   lower_net;		/* the child net */
    int edge_cost;		/* the value associated with this pair of
				   nets */
    INT_LIST cols;		/* list of columns associated with this pair
				   of nets */
} EDGE_ELEM, *EDGE_LIST;



typedef struct stack_of_nets	/* also used as a list of nets */
{
    struct stack_of_nets
	*next;			/* Next element in the list */
    struct a_net *net;		/* Pointer to a net in the list */
    int available_rows;		/* number of rows that have enough room to
				   contain this net */
} NET_STACK_ELEMENT, *NET_STACK,
  NET_LIST_ELEMENT, *NET_LIST;

typedef struct list_of_pins	/* 2.5 layer list of pins */
{

    int    net ;                /* pin connected to net */
    PINPTR pin ;                /* pin data record */
    struct list_of_pins
	*next;			/* Next element in the list */
} PIN_LIST, *PIN_LISTPTR ;



/***********************************************************************
 *
 * Global Variables
 *
 **********************************************************************/

#ifdef MAIN
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN FILE *input_fileG,	/* file from which input is read */
             *output_fileG,	/* file to which output is written */
             *result_fileG;	/* file to which actual routing is written,
			           if the -O flag is specified. */

EXTERN int ioformG;		/* set to HUMAN or MACHINE depending on the
			           command line input, if -H is specified */

EXTERN int outformG;		/* set to MACHINE if the -O is specified
			           then the result is printed
				   in machine format. */

EXTERN int riverG;		/* YES if river routing is desired
			           , NO otherwise.  Set to YES with -r
			           flag in command line. */
EXTERN int debugG;		/* YES if much intermediate output is
			           desired, NO otherwise.  Set to YES with -d
			           flag in command line. */

EXTERN int stats_onlyG;		/* YES if actial routing is
			           desired, NO otherwise.  Set to YES with -s
			           flag in command line. */

EXTERN int maximize_metalG;	/* YES if metal maximization is to be
			           performed, NO otherwise */

EXTERN int *name_arrayG;	/* array of external net names */


EXTERN NETPTR net_arrayG;	/* array of all the net data structures */

EXTERN int num_netsG,		/* size of net_array */
	   num_colsG;		/* number of columns */

EXTERN int num_rowsG;		/* number of horizontal tracks used to route
				   the nets */
EXTERN int *leftG;		/* list of left going nets */
EXTERN int *rightG;		/* list of right going nets */
EXTERN int num_leftG;
EXTERN int num_rightG;

EXTERN LINKPTR obstacleG;        /* List of obstacles */
EXTERN LINKPTR bounding_boxG;    /* Routing area */

EXTERN int num_obstaclesG;	/* number of obstacle links */
EXTERN int num_pinsG;		/* number of pins */

EXTERN CHANNELPTR channelG;	/* the channel where the results are stored */
EXTERN int **hlayerG,
	   **vlayerG;           /* H & V layers of the channel */
EXTERN int **playerhG,		/* To mark pin locations */
	   **playervG;		/* To mark pin locations */

EXTERN LINKLISTPTR **linklayerG; /* layer containing link pointers */

EXTERN int **historyG; /* To prevent oscillation, keep history
				 of improvements */
EXTERN INT_LIST Cycle_colsG;	/* list of columns corresponding to the edges
			           removed from the vertical constraint graph
			           in while removing cycles from the graph */

EXTERN int xgridG;		/* grid given by user in xdirection */
EXTERN int ygridG;		/* grid given by user in ydirection */
EXTERN BOOL mazeOnlyG;		/* avoid adding pseudo pins to layout */
EXTERN BOOL addpseudoG;		/* TRUE if user add pseudos */
EXTERN BOOL failedRouteG;	/* TRUE if the routing has failed */
EXTERN MACROPTR macroG;		/* head of a list of cell macros */

EXTERN PIN_LISTPTR two5pinsG ;  /* list of pins on the 1/2 level */
EXTERN PIN_LISTPTR *layer3G; 	/* used to keep track of columns to add pseudos */
#undef EXTERN




#endif /* MIGHTY_H */
