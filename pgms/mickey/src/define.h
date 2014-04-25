#ifndef lint
static char defineId[] = "@(#)define.h	Yale Version 2.4 11/23/91" ;
#endif
/* -----------------------------------------------------------------

	FILE:		define.h
	AUTHOR:		Dahe Chen
	DATE:		Tue Jan 16 23:12:48 EDT 1990
	CONTENTS:	
	REVISION:
		Thu Oct  4 20:12:56 EDT 1990
	    Change the array name for SCCS.
		Mon Oct 22 16:33:39 EDT 1990
	    Add the include file yalecad/base.h and remove the
	    definitions NIL(), TRUE, and FALSE.
		Mon Nov  5 21:57:32 EST 1990
	    Change NUMTREES from 20 to 32.
		Mon Dec  3 17:09:19 EST 1990
	    Remove NUMTREES and set it as a user-defined variable.

----------------------------------------------------------------- */
#include	<yalecad/base.h>
#define		BOOLEAN         char
#define		LABEL           4273
#ifdef		INFINITY
#undef		INFINITY
#endif
#define		INFINITY        INT_MAX
#define		GP_FAIL         1
#define		GP_OK           0
#define		H               1
#define		V               0
#define		UNVISITED       0
#define		VISITED         1
#undef NIL
#define NIL( type )		     (type *) NULL
