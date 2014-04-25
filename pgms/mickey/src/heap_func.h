#ifndef lint
static char heap_funcId[] = "@(#)heap_func.h	Yale Version 2.2 5/16/91" ;
#endif
/* -----------------------------------------------------------------

	FILE:		heap_func.h
	AUTHOR:		Dahe Chen
	DATE:		Tue Feb 28 23:16:25 EDT 1989
	CONTENTS:	
	REVISION:	Thu Oct  4 20:22:26 EDT 1990
		Change the array name for SCCS.

----------------------------------------------------------------- */

typedef struct heap {
    char	*data	;
    int		key	;
} HEAPS ,
*HEAPSPTR ;

