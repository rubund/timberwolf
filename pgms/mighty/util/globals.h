/* ----------------------------------------------------------------- 
FILE:	    globals.h                                       
DESCRIPTION:global insert file for draw_route program.
CONTENTS:   typedefs, defines, and global variables.
DATE:	    July 10, 1989 
REVISIONS:  
----------------------------------------------------------------- */
#ifndef GLOBALS_H
#define GLOBALS_H

#ifndef lint
static char SccsGlobalsHId[] = "@(#) globals.h version 1.1 12/16/89" ;
#endif

#ifndef MAIN_VARS
#define EXTERN extern
#else
#define EXTERN
#endif

/* the programs */
#define ROUTETW     "RouteTW"
#define MIGHTY      "../mighty"
#define MIGHTYNAME  "mighty"
#define DRAW        "../draw"
#define DRAWNAME    "draw"

EXTERN double maG ;  /* magnification */

#endif /* GLOBALS_H */
