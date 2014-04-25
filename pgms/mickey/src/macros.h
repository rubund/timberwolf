#ifndef lint
static char macrosId[] = "@(#)macros.h	Yale Version 2.2 5/16/91" ;
#endif
/* -----------------------------------------------------------------

	FILE:		macros.h
	AUTHOR:		Dahe Chen
	DATE:		Wed May 16 23:17:43 EDT 1990
	CONTENTS:	
	REVISION:
		Thu Oct  4 20:15:30 EDT 1990
	    Change the array name for SCCS.
		Mon Nov 12 11:50:52 EST 1990
	    Add conditional compilation for graphics.
		Tue Nov 27 18:23:20 EST 1990
	    Change the length of the array cktName from 64 to 256.
		Tue Mar  5 11:18:45 EST 1991
	    Change fopen to TWOPEN.

----------------------------------------------------------------- */

#include <yalecad/file.h>

#define		EVEN		0
#define		ODD		1

#ifndef MAX
#define		MAX(x,y)		( (x) > (y) ? (x) : (y) )
#endif
#ifndef MIN
#define		MIN(x,y)		( (x) < (y) ? (x) : (y) )
#endif
#define		PRINT			(void) fprintf
#define		EVEN_ODD(x)		( (x) & 01 )
#define		SAVE(name,place,type)	{ type place = name ;
#define		RSTR(name,place)	name = place ; }
#define		ERROR1(x1)		PRINT(stderr, x1)
#define		ERROR2(x1,x2)		PRINT(stderr, x1, x2)
#define		ERROR3(x1,x2,x3)	PRINT(stderr, x1, x2, x3)
#define		ERROR4(x1,x2,x3,x4)	PRINT(stderr, x1, x2, x3, x4)
#define		ERROR5(x1,x2,x3,x4,x5)	PRINT(stderr, x1, x2, x3, x4,x5)
#define		OUT1(x1)		if( verboseG ) \
						PRINT(stdout, x1)
#define		OUT2(x1,x2)		if( verboseG ) \
						PRINT(stdout, x1, x2)
#define		OUT3(x1,x2,x3)		if( verboseG ) \
						PRINT(stdout, x1, x2, x3)
#define		OUT4(x1,x2,x3,x4)	if( verboseG ) \
					PRINT(stdout, x1, x2, x3, x4)
#define		OUT5(x1,x2,x3,x4,x5)	if( verboseG ) \
					PRINT(stdout, x1, x2, x3, x4,x5)
#define		OUT7(x1,x2,x3,x4,x5,x6,x7)\
					if( verboseG ) \
					PRINT(stdout,x1,x2,x3,x4,x5,x6,x7)

#define		ASSERT( ex ) \
	{   if( (ex) == 0 ) { \
		PRINT(stderr , "Error found in file %s at line %d\n" , \
			__FILE__ , __LINE__ ) ; \
	    } \
	}


/* formerly a macro.  See init_info.c */
extern FILE *FOPEN(const char *, const char *);

/* remove graphics lines of code if compile switch is on */
#ifdef NOGRAPHICS
#define G(x_xz) 

#else 
#define G(x_xz)   x_xz

#endif /* NOGRAPHICS */

extern int verboseG ;
