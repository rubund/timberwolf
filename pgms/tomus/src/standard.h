/* ----------------------------------------------------------------- 
"@(#) standard.h (Yale) version 1.6 2/20/91"
FILE:	    standard.h                                       
DESCRIPTION:Tomus main insert file.
CONTENTS:   
DATE:	    Mar 27, 1989 
REVISIONS: Added equiv. pins for cells for Tomus output June 14th /91
           Added legal_part_classes to .cel format, so added to part_array and
           cell_array  ( for national)
----------------------------------------------------------------- */
#ifdef VMS
#define lINT 
#endif
/*  a cheap way of avoiding the inclusions of the sccs
    stuff for VMS systems
    */

#include <yalecad/base.h>


#ifdef MAIN_VARS
#define EXTERN 
#else
#define EXTERN extern 
#endif

/* ***********LEAVE THE BELOW UNCHANGED *************************** */

#define MAXINT 0x7FFFFFFF

#define ALLOC(type)    (  (type *) Ysafe_malloc ( sizeof(type) )  )
#define SetBin(x) (( (Trybin=((x)-binOffst)/binWidth)<0 ) ? 0 : \
                  ((Trybin>numBins) ? numBins : Trybin )) 

#define CULLNULL (CBOXPTR) NULL
#define PINNULL (PINBOXPTR) NULL
#define DIMNULL (DBOXPTR) NULL
#define TILENULL (TIBOXPTR) NULL
#define TW_PRIME 49999
#define TW_PRIME2 1009
#define PICK_INT(l,u) (((l)<(u)) ? ((RAND % ((u)-(l)+1))+(l)) : (l))

typedef struct glistbox {  /* generic list */
    union {
	INT net ;      /* make code easier to read */
	INT path ;     
	INT cell ;     
    } p ; 
    struct glistbox *next ;
} GLISTBOX , *GLISTPTR ;

typedef struct pinbox {
    struct pinbox *next ;          /* next pin on this net */
    struct pinbox *nextpin ;       /* next pin on this cell */
    char *pinname     ;
    INT terminal      ;
    int absx          ;                    /* global positions */
    int absy          ;
    SHORT xpos        ;               
    SHORT ypos        ;
    INT newx          ;
    INT newy          ;
    SHORT layer       ;
    INT cell          ;
    INT net           ;
}
*PINBOXPTR ,
PINBOX ;

typedef struct pathbox {
    INT lo_path_len ;     /* lower bound on the calculated half perim */
    INT hi_path_len ;     /* upper bound on the calculated half perim */
    INT new_lo_path_len ; /* new low path */
    INT new_hi_path_len ; /* new upper path */
    INT priority ;
    INT upper_bound ;
    INT lower_bound ;
    GLISTPTR nets ;
    struct pathbox *next ;  /* build a list first then array for speed */
} PATHBOX , *PATHPTR ;

typedef struct corners {
    SHORT x_coord  ;
    SHORT y_coord  ;
}
*CORNERS,
CORBOX;

typedef struct pad_rec {
    INT    *xpoints         ;  /* xcoordinates of pad/macro */
    INT    *ypoints         ;  /* ycoordinates of pad/macro */
    SHORT  corners          ;  /* number of corners */
    SHORT  padside          ;  /* current side */
    BOOL   macroNotPad      ;  /* true if macro false if pad */
} PADBOX, *PADBOXPTR ;

typedef struct cellbox { 
    char *cname           ;
    INT cxcenter          ;
    INT cycenter          ;
    INT tile              ;
    INT id                ;
    char **cpclass        ; /* strings of all the classes 
				this cell is a member of */
    SHORT cheight     ;
    SHORT clength     ;
    GLISTPTR paths        ;  /* timing paths of a cell */
    PINBOXPTR pins        ;  /* the pins of the cell */
    struct pad_rec *padptr;
} *CBOXPTR, CBOX ;

typedef struct ptrtocell{
	CBOXPTR cellptr;
} *PCELLPTR, PCELL;

typedef struct tiles{
    SHORT id;
    SHORT partition_id;
    SHORT legal;
    INT upper_left_x;
    INT upper_left_y;
    INT lower_right_x;
    INT lower_right_y;
    INT area;
    INT grid_loc_x;
    INT grid_loc_y;
    INT center_x;
    INT center_y;
    INT capacity; /* allowable cell length */
    INT celllen; /*  */
    INT cells  ; /*  */
    INT penalty; /*  */
    INT nupenalty; /*  */
    INT *carray ; /** hold the  cell ids */
} *PTILEPTR, PTBOX;

typedef struct pad{
	SHORT padside;
	BOOL lone;
	INT id;
	INT net;
	INT x;
	INT y;
	PTILEPTR tileptr;
} *PADPTR, PDBOX;

typedef struct partitions{
    SHORT id;
    char class[8];            /* legal class number */
    INT upper_left_x;
    INT upper_left_y;
    INT lower_right_x;
    INT lower_right_y;
    INT area;
    INT capacity             ; /* allowable cell length */
    INT celllen              ; /*  */
    INT cells  ; /*  */
    INT penalty; /*  */
    INT nupenalty; /*  */
    PADPTR *padlist;
    SHORT numpads;
}
*PARTNPTR,
PARTNBOX;

typedef struct dimbox {
    PINBOXPTR pins ;         /* pins of the net */
    char *name   ;
    char ignore  ;
    INT xmin     ; /* can be made short */
    INT newxmin  ;
    INT xmax     ;
    INT newxmax  ;
    INT ymin     ;
    INT newymin  ;
    INT ymax     ;
    INT newymax  ;
    INT *line_x  ;
    INT *line_y  ;
    SHORT numpins  ;
    GLISTPTR paths ;     /* paths which this net belongs */
    INT halfPx ;        /* current half perimeter bounding box */
    INT newhalfPx ;     /* new half perimeter bounding box */
    INT halfPy ;        /* current half perimeter: y portion */
    INT newhalfPy ;     /* new half perimeter: y portion */
    INT dflag    ;
    DOUBLE driveFactor ; /* drive constant for this net */
    DOUBLE max_driver ;   /* largest driver on this net */
    DOUBLE min_driver ;   /* smallest driver on this net */
} *DBOXPTR, DBOX ;

typedef struct hash {
    char *hname ;
    INT hnum ;
    struct hash *hnext ;
} HASHBOX, *HASHPTR ;


/* ****************** GLOBALS ************************** */
/* THE MAJOR PARTS OF THE DATA STRUCTURES */
EXTERN CBOXPTR *carrayG  ;
EXTERN DBOXPTR *netarrayG   ;
EXTERN PATHPTR *patharrayG ;  /* array of timing paths */
EXTERN PTILEPTR *tarrayG;
EXTERN PARTNPTR *partarrayG;

/**** the main file ptrs ***/
EXTERN FILE *fpoG;
EXTERN char *cktNameG;

EXTERN DOUBLE vertical_path_weightG ;
EXTERN DOUBLE horizontal_path_weightG ;
EXTERN DOUBLE vertical_wire_weightG ;

/* control factors **/
EXTERN int resume_run;

/* the configuration */
EXTERN INT celllenG;
EXTERN INT core_y1G ;
EXTERN INT core_y2G ;
EXTERN INT core_x1G ;
EXTERN INT core_x2G;
EXTERN INT lastpadG ;
EXTERN INT numcellsG ; /* number od stdcells and macros */
EXTERN INT numMacroG ; /* number of macros */
EXTERN INT numtermsG ;
EXTERN INT numnetsG ;  /* number of nets */
EXTERN INT TotRegPinsG ;
EXTERN INT numpadgrpsG ;
EXTERN INT numpathsG ;
EXTERN INT total_tile_areaG ;
EXTERN INT total_part_areaG ;

/* for the penalties */
EXTERN INT funccostG ;
EXTERN INT penaltyG  ;
EXTERN INT newtilepenalG ;
EXTERN INT newpartpenalG ;
EXTERN INT newpenalG ;
EXTERN INT partpenalG ;
EXTERN INT tilepenalG ;
EXTERN INT timingcostG ;
EXTERN INT timingpenalG ;
EXTERN DOUBLE timeFactorG ;
EXTERN DOUBLE tilepenalC ;
EXTERN DOUBLE partpenalC ;


EXTERN INT vlineG; 
EXTERN INT hlineG; 
EXTERN INT num_ptileG; 
EXTERN INT num_cornersG ;
EXTERN INT num_partnsG;

EXTERN PADPTR *padlistG;

#undef EXTERN  
