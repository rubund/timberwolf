/* ----------------------------------------------------------------- 
FILE:	    parser.h                                       
DESCRIPTION:definitions for parsing for .cel, .mver, 
            .par files.
CONTENTS:   
DATE:	    Dec  8, 1989 
	    "@(#) parser.h (Yale) version 1.3 2/21/91"
REVISIONS:  July 19th , 1990 : Introduced keywords used in readmver.c and readpar.c specific to the partitioner. 
----------------------------------------------------------------- */
#include <yalecad/base.h>

#ifndef PARSER_H

#define PARSER_H

#ifdef PARSER_VARS
#define EXTERN 
#else
#define EXTERN extern 
#endif

/* cell types */
#define STDCELLTYPE       1
#define PADTYPE           2
#define HARDCELLTYPE      3

EXTERN DOUBLE rowSep;
EXTERN DOUBLE rowSepAbs; 
EXTERN DOUBLE mean_width;
EXTERN DOUBLE track_pitch;
EXTERN INT rowHeight ;
EXTERN INT macro_clearance;
EXTERN INT cell_area,macro_area,core_area;
EXTERN INT delxG,delyG;
EXTERN INT mono_class_cellsG ;

#endif /* PARSER_H */
