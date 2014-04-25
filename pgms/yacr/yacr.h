/************************************************************************
 *
 * Include files
 *
 ************************************************************************/

#include <stdio.h>

#define ALLOC(a, b) 	malloc(b * sizeof(a))
#define FREE(a)		free(a)
#define MAX(a, b)	(((a) > (b)) ? (a) : (b))
#define MIN(a, b)	(((a) > (b)) ? (b) : (a))

/************************************************************************
 *
 * Defines
 *
 ************************************************************************/

#define IN
#define OUT
#define INOUT

#define YES 1
#define NO 0
#define NEVER 2
#define MAYBE 3

#define TRUE 1
#define FALSE 0

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
#define BOTH 8

/* LOW MED HIGH and INFINITY are used for the cost matrix */
#define LOW 1
#define MED 100
#define HIGH 10000
#define INFINITY 1000000

/* marker for indented border in channel data structure */
#define BORDER (-2)

/* used in rectangle/path data structure */
#define HORIZ 1
#define VERT 2

/* for the implementation of partial boundary constraints */
#define ALPHA 2

/***********************************************************************
 *
 * Macro
 *
 ***********************************************************************/

#define number_to_name(A) name_array[A]

/***********************************************************************
 *
 * Data Structure Definitions
 *
 ***********************************************************************/


typedef struct doubly_linked_list_of_columns
{
    int col;			/* Column number where a pin appears.
				   If col = 0, pin is on left edge,
				   if col > num_cols, pin is on right edge. */
    int edge;			/* edge where the pin enters the channel */
    struct doubly_linked_list_of_columns
	*right_list,		/* The list of pins to the right of this
				   column */
	*left_list;		/* The list of pins to the left of this
				   column */
} PIN_LIST_ELEMENT, *PIN_LIST;



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



typedef struct stack_of_nets	/* also used as a list of nets */
{
    struct stack_of_nets
	*next;			/* Next element in the list */
    struct a_net *net;		/* Pointer to a net in the list */
    int available_rows;		/* number of rows that have enough room to
				   contain this net */
} NET_STACK_ELEMENT, *NET_STACK,
  NET_LIST_ELEMENT, *NET_LIST;



typedef struct a_net
{
    int name;			/* Name of this net, used for input and
				   output only */
    int level_from_top,		/* Number of rows which must be above this
				   net to avoid vertical constraint
				   violations */
	level_from_bottom;	/* Number of rows which must be below this
				   net */
    int top_free_row,
	bottom_free_row;	/* First and last row where net can be
				   placed without hitting the irregular
				   border. */
    int top_preferred,		/* row in preferred ranges nearest top of
				   channel */
	bottom_preferred;	/* row in preferred range nearest bottom of
				   channel */
    int pin_placement;		/* indicates whether most of this nets pins
				   connect to the top edge ( > 0 ), or the
				   bottom edge ( < 0 ), or equal numbers to
				   both edges ( == 0 ) */
    int num_bot, num_top;       /* number of pins in net connected to the
				   bottom and top edges, respectively. */
    int row;			/* Primary row containing this net */
    PIN_LIST leftmost,		/* The left end of the list of pins that this
				   net is connected to */
	     rightmost;		/* The right end of the list of pins that
				   this net is connected to */
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
    int left_column;		/* column number of the leftmost column in
				   the channel, initially 0, but will be
				   decremented once for each column added to
				   the left edge of the channel */
} CHANNEL, *CHANNELPTR;



typedef struct linked_list_of_rectangles
{
    struct linked_list_of_rectangles
	*next;			/* next rectangle in the list */
    int layer;			/* which layer this rectangle goes on, either
				   HORIZ or VERT */
    int orientation;		/* does this rectangle go HORIZ or VERT? */
    int num1, num2;		/* endpoints of rectangle, num1 < num2 */
    int num3;			/* row or column rectangle is in */
} PATH, *PATHPTR;


typedef struct linked_list_of_paths
{
    struct linked_list_of_paths
	*next;			/* next path in the list */
    PATHPTR path;		/* one path in the list */
    int cost;			/* the cost of using this path */
} PATH_LIST_ELEMENT, *PATH_LIST;


typedef struct max_density_list
{
    struct max_density_list
	*next;			/* next column in the list */
    int column;			/* this columns number */
    int col_value;		/* sum of the number of nets that this column
				   shares with other max_density columns, if
				   a net is shared with two other columns it
				   adds two to col_value */
} DENSITY_COLUMN, *DENSITY_LIST;


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



/************************************************************************
 *
 * Global Variables
 *
 ************************************************************************/

#ifdef MAIN
#define YACR_EXTERN
#else
#define YACR_EXTERN extern
#endif

YACR_EXTERN FILE *input_file,	/* file from which input is read */
             *output_file,	/* file to which output is written */
             *result_file;	/* file to which actual routing is written,
			           if the -O flag is specified. */

YACR_EXTERN INT_LIST Vcv_cols;	/* list of columns with vertical constraint
			           violations.  Elements are added to the
			           list in place_one_net. */

YACR_EXTERN int ioform;		/* set to HUMAN or MACHINE depending on the
			           command line input, if -H is specified */

YACR_EXTERN int outform;		/* set to MACHINE if the -O is specified
			           then the result is printed
				   in machine format. */

YACR_EXTERN int cyclecount;		/* No. of cycles detected */

YACR_EXTERN int printcycles;		/* Whether the cycle info should be printed */

YACR_EXTERN int initial_column;	/* column where nets are first placed */

YACR_EXTERN int debug;		/* YES if much intermediate output is
			           desired, NO otherwise.  Set to YES with -d
			           flag in command line. */

YACR_EXTERN int stats_only; 		/* YES if actial routing is
			           desired, NO otherwise.  Set to YES with -s
			           flag in command line. */

YACR_EXTERN int place_relative;	/* LEFT if the pins on the left edge are to
			           exit the channel with the order specified
			           in the input, RIGHT if the pins on the
			           right edge are ordered, NO if the order
			           does not matter on either edge of the
			           channel */

YACR_EXTERN int place_partial;       /* LEFT if the pins on the left edge are to
				   be placed with partial constraints on 
				   track positioning, RIGHT if the pins in the
				   right edge are partially constrained, NO
				   if neither edge, and BOTH if both edges. */

YACR_EXTERN int place_fixed;		/* Similar to place_relative above, except
			           for fixed end pins. At least one of the
			           two must be NO. */

YACR_EXTERN INT_LIST Cycle_cols;	/* list of columns corresponding to the edges
			           removed from the vertical constraint graph
			           in while removing cycles from the graph */

YACR_EXTERN int maximize_metal;	/* YES if metal maximization is to be
			           performed, NO otherwise */

YACR_EXTERN int can_add_columns;	/* YES if user has declared it okay to add
			           columns to the ends of the channel, NO
			           otherwise */

YACR_EXTERN int *name_array;		/* array of external net names */

YACR_EXTERN NETPTR *top,		/* array of pointers to nets on
 				   top of channel */
              *bottom,		/* nets on bottom of channel */
              *left,		/* nets entering from left */
              *right,		/* nets entering from right */
              *up,              /* up and down are lists of nets that should */
              *down;            /* be placed near the top and bottom edges
                                   of the channel, repectively, if possible. */

YACR_EXTERN int *top_offset,
           *bottom_offset;	/* arrays of the vertical offsets
				   of each pin. */

YACR_EXTERN int max_top_offset,
	   max_bottom_offset;   /* The greatest offset (after scaling)*/

YACR_EXTERN NETPTR net_array;	/* array of all the net data structures */

YACR_EXTERN int num_nets,		/* size of net_array */
	   num_cols,		/* number of columns (size of top[] and
				   bottom[]) */
	   num_left_nets,	/* number of nets entering from left (size of
				   left[]) */
	   num_right_nets,	/* number of nets entering from right (size
				   of right[]) */
           num_up_nets,         /* number of nets with partial upward
				   constraints */
           num_down_nets;       /* number of nets with partial downward 
				   constraints */

YACR_EXTERN int num_rows;		/* number of horizontal tracks used to route
				   the nets */

YACR_EXTERN int *density;		/* density of each column */

YACR_EXTERN CHANNELPTR channel;	/* the channel where the results are stored */

YACR_EXTERN NET_LIST placeable_nets;	/* list of nets that have entered the
				   channel, but have not been assigned to
				   rows */

YACR_EXTERN int **cost;		/* the cost matrix used to find "best"
				   placement of nets in rows */

#undef YACR_EXTERN

/*********************************************************************
 *
 *  Include declaration of function types.
 *
 *********************************************************************/

#include "yacr.typ"

