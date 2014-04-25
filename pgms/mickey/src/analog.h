#ifndef lint
static char analogId[] = "@(#)analog.h	Yale Version 2.10 5/16/91";
#endif
/* -----------------------------------------------------------------

	FILE:		analog.h
	AUTHOR:		Dahe Chen
	DATE:		Thu Mar  1 14:28:44 EDT 1990
	CONTENTS:	Header file for functions dealing with
			analog circuits.
	REVISION:
		Tue Nov 13 18:12:21 EST 1990
	    Remove the macros and add a structure definition.
		Thu Nov 15 10:09:41 EST 1990
	    Put the macros back.
		Thu Dec  6 17:07:05 EST 1990
	    Change the assignment statement for the width in the
	    macro assign_channel_width() to the comparison. This
	    guarantees that Asize[e] is not zero.
		Fri Dec  7 15:05:53 EST 1990
	    Remove the data structure NETLIST and Anarray.
		Fri Dec  7 19:46:06 EST 1990
	    Move the data structure for analog_match to that file.
		Tue Dec 18 12:10:23 EST 1990
	    Add more declarations.
		Fri Dec 21 11:30:10 EST 1990
	    Change net type values.
		Mon Jan 21 17:56:53 EST 1991
	    Add the variable max_volt_drop.
		Tue Jan 22 16:14:43 EST 1991
	    Add data structures for common points.

----------------------------------------------------------------- */

#define MIXED		1
#define NOISY		2
#define SENSITIVE	3
#define SHIELD		4

#ifdef ANALOG
#define AEXTERN
#else
#define AEXTERN extern
#endif /* ANALOG */

typedef struct _linked_list {
    int index;
    int node;
    int status;
    struct _linked_list *next;
} LINK,
*LINKPTR;

typedef struct leaf_stack {
    int index;
    struct leaf_stack *next;
} LSTACK,
*LSTACKPTR;

typedef struct _clist {
    int numpin;
    int cap_match;
    int res_match;
    struct _clist *next;
} C_LIST,
*C_LISTPTR;

#define assign_channel_width(ptr1, ptr2) \
	while (ptr2 != ptr1) \
	{ \
	    Pnode = garray[ptr2->vertex]->first; \
	    i = ptr2->order - 1; \
	    j = ptr2->parent; \
	    while (marray[i]->vertex != j) \
	    { \
		i--; \
	    } \
	    ptr2 = marray[i]; \
	    j = ptr2->vertex; \
	    while (Pnode->t_vertex != j) \
	    { \
		Pnode = Pnode->next; \
	    } \
	    Adens[Pnode->edge] = dens; \
	    Asize[Pnode->edge] = MAX(size, earray[Pnode->edge]->width); \
	}

#define calculate_parameters(ptr1, ptr2) \
	while (ptr2 != ptr1) \
	{ \
	    Pnode = garray[ptr2->vertex]->first; \
	    i = ptr2->order - 1; \
	    j = ptr2->parent; \
	    while (marray[i]->vertex != j) \
	    { \
		i--; \
	    } \
	    ptr2 = marray[i]; \
	    j = ptr2->vertex; \
	    while (Pnode->t_vertex != j) \
	    { \
		Pnode = Pnode->next; \
	    } \
	    cap += (float) earray[Pnode->edge]->length \
		 * (float) Asize[Pnode->edge]; \
	    res += (float) earray[Pnode->edge]->length \
		 / (float) Asize[Pnode->edge]; \
	    Adens[Pnode->edge] = 0; \
	    Asize[Pnode->edge] = 0; \
	}

#define count_node_degree(ptr, operator) \
	while (ptr != NIL(LIST)) \
	{ \
	    if (Asize[ptr->edge] operator FALSE \
	     && earray[ptr->edge]->intree & MIN_MASK) \
	    { \
		degree++; \
	    } \
	    ptr = ptr->next; \
	}

AEXTERN	float	C_SHEET		;
AEXTERN	float	R_SHEET		;
AEXTERN float	C_TOLERANCE	;
AEXTERN float	R_TOLERANCE	;
AEXTERN	float	cap_upper_bound	;
AEXTERN	float	res_upper_bound	;
AEXTERN float	max_volt_drop	;

AEXTERN int	total_penalty	;

AEXTERN int	net_type	;
AEXTERN int	CAP_MATCH	;
AEXTERN int	MIX_MATCH	;
AEXTERN int	RES_MATCH	;
AEXTERN int	COMMON_POINT	;
AEXTERN	int	numcomms	;
AEXTERN	int	*Adens		;
AEXTERN	int	*Asize		;

AEXTERN C_LISTPTR	Plist	;
