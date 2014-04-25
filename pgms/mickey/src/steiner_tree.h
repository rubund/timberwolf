#ifndef lint
static char steiner_treeId[] = "@(#)steiner_tree.h	Yale Version 2.3 5/16/91" ;
#endif
/* -----------------------------------------------------------------

	FILE:		steiner_tree.h
	AUTHOR:		Dahe Chen
	DATE:		Thu Mar 30 23:18:56 EDT 1989
	CONTENTS:	
	REVISION:
		Thu Oct  4 20:16:09 EDT 1990
	    Change the array name for SCCS.
		Tue Oct  9 12:04:39 EDT 1990
	    Change the variable status in the structure mdata from
	    short to int.
		Wed Feb  6 14:42:44 EST 1991
	    Add voltage in MDATA.

----------------------------------------------------------------- */

#ifdef	STEINER_VARS
#define		STEINER_EXTERN
#else
#define		STEINER_EXTERN		extern
#endif

typedef	struct mdata {
    short		equiv	;	/* indicator of equivalent pin	*/
    short		leaf	;	/* indicator of a leaf		*/
    short		order	;	/* rank in the tree		*/
    short		parent	;	/* index of parent vertex	*/
    short		vertex	;	/* index of this vertex 	*/
    int			status	;
    int			dist	;	/* distance from root		*/
    double		voltage	;
    struct mdata	*f_node	;	/* low rank Steiner point	*/
    struct mdata 	*prev	;
    struct mdata 	*next	;
} MDATA ,
*MDATAPTR ;

typedef	struct	pdata {
    short	edge		;
    short	mark[2]		;
    short	node[2]		;
    short	pin[2]		;
    int		key		;
} PDATA ,
*PDATAPTR ;

#define	    DELETE_SEGMENT_TREE( Phead , Proot ) \
		{ \
		    MDATAPTR Ptmp ; \
		    if( !Phead ) { \
			Phead = Proot ; \
		    } else { \
			Ptmp = Phead ; \
			while( Ptmp->next ) { \
			    Ptmp = Ptmp->next ; \
			} \
			Ptmp->next = Proot ; \
		    } \
		}

STEINER_EXTERN	short	 STATE		;
STEINER_EXTERN	short	 *iarray	;
STEINER_EXTERN	short	 *jarray	;
STEINER_EXTERN	unsigned MIN_MASK	;
STEINER_EXTERN	int	 steiner_label	;
STEINER_EXTERN	int	 numtree_e	;

STEINER_EXTERN	MDATAPTR Phead		;
STEINER_EXTERN	MDATAPTR Proot		;
STEINER_EXTERN	MDATAPTR *marray	;

STEINER_EXTERN	HEAPSPTR *harray	;
