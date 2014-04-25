#ifndef lint
static char dgraphId[] = "@(#)dgraph.h	Yale Version 3.2 5/28/91" ;
#endif
/* -----------------------------------------------------------------

	FILE:		dgraph.h
	AUTHOR:		Dahe Chen
	DATE:		Mon Feb 20 23:13:58 EDT 1989
	CONTENTS:	General definitions and data structures for
		directed polar graphs and related channel graph that
		will be used for channel density calculation.
	REVISION:
		Mon Jun  4 21:09:58 EDT 1990
	    Add field net in data structure offset_record.
		Thu Oct  4 20:13:59 EDT 1990
	    Change the array name for SCCS.
		Wed Dec  5 12:47:33 EST 1990
	    Remove the declaratin of h_width and v_width. Also, add
	    a width field to the data structure for edge array.
		Tue Dec 18 12:11:10 EST 1990
	    Add a field in the data structure NETPTR to specify the
	    net type for an analog net.
		Tue May 28 15:30:54 EDT 1991
	    Add a new field in the list of channels for a route to
	    backup offsets.

----------------------------------------------------------------- */

#include	<stdio.h>
#include	<math.h>

#ifdef DG_MAIN
#define		DEXTERN
#else
#define		DEXTERN		extern
#endif

/*######################################################################*/
/*------------------------------------------------------------------------
		DATA STRUCTURES FOR DIRECTED GRAPH
------------------------------------------------------------------------*/
typedef struct dlist {		  /* a record for adjacent nodes	*/
    short	edge		; /* the index of edge			*/
    short	node		; /* the index of to_node		*/
    struct dlist *next		; /* pointer to next record		*/
} DLIST ,
*DLISTPTR ;

typedef struct dnode {
    struct dlist *Panode	; /* list of adjacent nodes		*/
} DNODE ,
*DNODEPTR ;

typedef struct nlist {
    int		net		; /* index for net			*/
    struct nlist *prev		;
    struct nlist *next		;
} NLIST ,
*NLISTPTR ;

typedef struct hlist {
    int		index		; /* self index				*/
    int		key		; /* local density			*/
    int		pin		; /* index to density array		*/
} HLIST ,
*HLISTPTR ;

typedef struct dens {
    int		density		; /* local density of channel		*/
    int		distance	; /* distance respect to from_node	*/
    int		net[2]		; /* index for net the pin belongs	*/
    int		channel[2]	; /* index for channel the pin belongs	*/
    struct hlist *Pheap		; /* pointer to the entry in the heap	*/
    struct nlist *Pnlist	; /* head of net list			*/
} DENS ,
*DENSPTR ;

typedef struct dedge {
    short	capacity	; /* capacity of channel		*/
    short	density		; /* channel density			*/
    short	direct		; /* direction of edge in polar graph	*/
    short	edge		; /* self-index				*/
    short	f_node		; /* from_node of the edge in dgraph	*/
    short	t_node		; /* to_node of the edge in dgraph	*/
    short	f_vertex	; /* from_node of the channel		*/
    short	t_vertex	; /* to_node of the channel		*/
    short	numpin		; /* number of pins on the channel	*/
    short	status		; /* indicator if channel is used	*/
    int		csize		; /* cell size				*/
    int		f_xpos		; /* x position of from_node		*/
    int		f_ypos		; /* y position of from_node		*/
    int		t_xpos		; /* x position of to_node		*/
    int		t_ypos		; /* y position of to_node		*/
    int		length		; /* length of channel			*/
    int		weight		; /* cell size plus channel density	*/
    int		width		; /* minimum width associated with edge	*/
    struct nlist *Pcnet		; /* list of nets crossing channel	*/
    struct hlist **Aindex	; /* priority tree to indicate density	*/
    struct dens  **Adens	; /* local density array		*/
    struct dedge *Pnext		; /* to edge opposite of empty room	*/
} DEDGE ,
*DEDGEPTR ;
/*######################################################################*/

/*######################################################################*/
/*------------------------------------------------------------------------
		DATA STRUCTURES FOR NETS OF CIRCUITS
------------------------------------------------------------------------*/
typedef struct offset_record {	 /* record for offset of net in channel */
    short       edge    	; /* edge index				*/
    short	width		; /* width of the route in the channel	*/
    unsigned	net		; /* index for subnet for common pins	*/
    int         l_off   	; /* offset to left side of channel	*/
    int         r_off   	; /* offset to right side of channel	*/
    int		*back		; /* backup for offsets			*/
    struct offset_record *next  ; /* pointer to next record		*/
} OFSET ,
*OFSETPTR ;

typedef struct rout_record {
    float	capacitance	; /* capacitance of this route		*/
    float	resistance	; /* resistance of this route		*/
    int		group		; /* indicator to match other nets	*/
    int         length  	; /* total length of this route 	*/
    struct offset_record *Pedge	; /* list of edges in the route 	*/
} ROUT ,
*ROUTPTR ;

typedef struct net_record {
    char	*name		; /* name of the net			*/
    short	net		; /* index of the net			*/
    short	net_type	; /* indicator of net type for analog	*/
    short	route		; /* index of using route		*/
    short	num_of_routes	; /* number of routes for this net	*/
    int		numpins		; /* number of pins in the net		*/
    struct rout_record **Aroute	;
    struct net_record  *next	;
} NETDR ,
*NETDRPTR ;

typedef struct route {
    short	net		; /* index of net			*/
    short	route		; /* index of chosen route		*/
    struct route *next		;
} ROUTE ,
*ROUTEPTR ;
/*######################################################################*/

/*######################################################################*/
/*------------------------------------------------------------------------
		DATA STRUCTURES FOR FEED-THROUGHS OF CIRCUITS
------------------------------------------------------------------------*/
typedef struct feed_through {
    short	chan[2]		; /* index for perpendicular channels	*/
    short	edge[2]		; /* index for parallel channels	*/
    short	node[2]		; /* index of nodes from them dist give	*/
    int		dist[2]		; /* distance from node[0|1]		*/
    short	net		; /* index of the net using the feed	*/
    short	route		; /* index of the router using the feed	*/
} FEED,
*FEEDPTR ;
/*######################################################################*/

extern	int	numedges	;
extern	int	numnets		;

DEXTERN char	*h_critical	;	/* horizontal critical channels	*/
DEXTERN char	*v_critical	;	/* vertical critical channels	*/
DEXTERN int	h_lpath		;	/* length of horizontal path	*/
DEXTERN int	v_lpath		;	/* length of vertical path	*/
DEXTERN	int	h_numnodes	;	/* number of nodes of HG	*/
DEXTERN	int	h_numedges	;	/* number of edges of HG	*/
DEXTERN	int	v_numnodes	;	/* number of nodes of VG	*/
DEXTERN	int	v_numedges	;	/* number of edges of VG	*/
DEXTERN	int	total_cost	;
DEXTERN	int	*h_parent	;	/* horizontal longest path	*/
DEXTERN	int	*v_parent	;	/* vertical longest path	*/

DEXTERN	DNODEPTR *h_narray	;	/* horizontal polar graph	*/
DEXTERN	DNODEPTR *v_narray	;	/* vertical polar graph		*/
DEXTERN	DEDGEPTR *dearray	;	/* edges of HG and VG		*/
DEXTERN	NETDRPTR netlist	;	/* header of routes of net list	*/
DEXTERN NETDRPTR *narray	;	/* routes of nets		*/
DEXTERN	FEEDPTR	 *farray	;	/* array of feed-throughs	*/
