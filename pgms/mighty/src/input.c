#ifndef lint
static char yysccsid[] = "@(#)yaccpar	1.8 (Berkeley) 01/20/90";
#endif
#define YYBYACC 1
/* ----------------------------------------------------------------- 
FILE:	    input.c.c <- input_yacc <- input_lex
DESCRIPTION:This file contains the grammar (BNF) for the mighty
	    input file parser.
	    The rules for lex are in input_lex.
	    The grammar for yacc is in input_yacc
	    The output of yacc (y.tab.c) is renamed to input.c
CONTENTS:   NETPTR S_input ( num_netsG, num_box, num_rows, 
		num_cols, num_obstacles, num_pins )
		int *num_netsG,		total number of nets
		    *num_box,           number of corners of box
		    *num_rows,		size of bounding box in y
		    *num_cols,		size of bounding box in x
		    *num_obstacles,	total number of obstacles
		    *num_pins;		total number of pins
	    yyerror(s)
		char    *s;
	    yywrap()
	    Note:input.c will also include the yacc parser.
DATE:	    Oct	 4, 1988 
REVISIONS:  Sep 19, 1989 - fixed missing obstacle number in grammar.
	    Sun Jan 20 21:29:11 PST 1991 - ported to AIX.
----------------------------------------------------------------- */
#ifndef lint
static char SccsId[] = "@(#) input.y version 6.5 4/6/92" ;
#endif

#include "mighty.h"
#include <yalecad/message.h>

#define STRINGEQ 0
#define E_EDGE 0
#define U_EDGE 1
#define L_EDGE 2
#define R_EDGE 3
#define D_EDGE 4
/* #define YYDEBUG  */ /* condition compile for yacc debug */
#undef REJECT

static int line_countS ;

/*
int Insidepin = FALSE;
*/
int xshift;
int yshift;
extern BOOL addguideG ;
static BOOL abortFlagS = FALSE ;
static PINPTR pinptrS ;              /* pointer to pin record */
static LINKPTR linkS ;               /* pointer to link record */
static LINKPTR slinkS ;              /* pointer to link record */
static LINKPTR edgePtrS ;            /* pointer to macro edge link */
static MACROPTR curmacroS ;          /* pointer to a macro record */
static int xminS, xmaxS, yminS, ymaxS ; /* find bounding box */
static int numNetS = 0 ;            /* number of nets in channel */
static int numColS = 0 ;            /* number of column in maze */
static int numRowS = 0 ;            /* number of rows in maze */
static int numCornerPtS = 0 ;       /* number of pts in bounding figure */
static int numPinS = 0 ;            /* number of pins given */
static int numSenS = 0;             /* number of sensitive nets */
static int numObstacleS = 0;        /* number of obstacles */
static int netnumS ;                 /* number of net in array */
static int invalidS ; /* hold number of invalid nets in l&r lists */
static int validLS ;  /* counter of valid left nets */
static int validRS ;  /* counter of valid right nets */
static int netS ;     /* counter for current net */
static int num3pinS ; /* number of third layer pins */
int *S_allocatevector();          /* allocate a vector of integers */
PINPTR S_getpin() ;               /* create a new pin record */
LINKPTR S_getlink();              /* create a new link */
NETPTR allocate_nets();           /* create the net array */


static S_check_pins();
static in_maze();




/*******************************************************************
 *
 *  This routine reads the input for swrt, and returns an array of
 *  NETs.  The array contains all of the net data structures.
 *  xminS is shifted to x = 1, yminS is shifted to y = 1.
 *  The input is returned to
 *  the main routine in the form of arrays of pointers to NET structures.
 *  Last modified: 8-6-86  for input error checking in S_onboundary
 *
 ********************************************************************/

typedef union {
    INT ival ;
    char *string ;
    double fval ;
} YYSTYPE;
#define INTEGER 257
#define STRING 258
#define FLOAT 259
#define CHANNELDEF 260
#define LEFTLIST 261
#define NUMNETS 262
#define NUMPINS 263
#define OBSTACLES 264
#define RECTCORNERS 265
#define RIGHTLIST 266
#define SENSITIVE 267
#define MACRO 268
#define PSEUDOS 269
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    1,    2,   10,   10,   11,    3,   12,   12,   13,
    4,    4,   14,   15,   15,   16,    5,    5,   17,   18,
   18,   19,    6,    6,   20,   20,   21,    7,    7,   22,
   22,   23,   24,   25,   25,   26,    8,    8,   27,   27,
   28,    9,    9,   29,   29,   30,
};
short yylen[] = {                                         2,
    9,    2,    3,    1,    2,    2,    3,    1,    2,    4,
    0,    2,    2,    1,    2,    1,    0,    2,    2,    1,
    2,    1,    0,    3,    1,    2,    5,    0,    1,    1,
    2,    2,    1,    1,    2,    6,    0,    3,    1,    2,
    1,    0,    2,    1,    2,    4,
};
short yydefred[] = {                                      0,
    0,    0,    0,    2,    0,    0,    0,    0,    0,    0,
    0,    4,    0,    0,    0,    0,    6,    5,    0,    0,
    8,   13,    0,    0,    0,   16,    0,   14,    0,    9,
   19,    0,    0,   22,    0,   20,   15,    0,    0,   33,
    0,    0,   30,    0,   21,   10,    0,    0,   25,    0,
    0,   31,    0,    0,   34,    0,   26,    0,    0,    1,
    0,   35,    0,   41,    0,   39,    0,    0,   44,    0,
    0,   40,    0,   45,    0,   27,    0,    0,   46,   36,
};
short yydgoto[] = {                                       2,
    3,    6,    9,   15,   24,   33,   41,   51,   60,   11,
   12,   20,   21,   16,   27,   28,   25,   35,   36,   48,
   49,   42,   43,   44,   54,   55,   65,   66,   68,   69,
};
short yysindex[] = {                                   -262,
 -255,    0, -261,    0, -252, -257, -249, -247, -250, -245,
 -249,    0, -243, -242, -248, -241,    0,    0, -240, -243,
    0,    0, -237, -238, -236,    0, -241,    0, -235,    0,
    0, -234, -244,    0, -236,    0,    0, -230, -228,    0,
 -232, -244,    0, -227,    0,    0, -225, -228,    0, -224,
 -233,    0, -218, -227,    0, -217,    0, -216, -215,    0,
 -214,    0, -213,    0, -216,    0, -212, -215,    0, -211,
 -210,    0, -209,    0, -208,    0, -207, -206,    0,    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    7,    0,
 -205,    0,    0,    0,   19,    0,    0,    0,    0,    1,
    0,    0,    0,   28,    0,    0,   13,    0,    0,    0,
    0,    0,   37,    0,   25,    0,    0,    0,    0,    0,
    3,   38,    0,    0,    0,    0,    0,   31,    0,    0,
   52,    0,    0,   34,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    9,    0,    0,   53,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
};
short yygindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   43,    0,   35,    0,    0,   29,    0,    0,   22,    0,
   11,    0,   18,    0,    0,    8,    0,   -4,    0,   -5,
};
#define YYTABLESIZE 307
short yytable[] = {                                       1,
    7,    4,   37,    5,    7,    8,   11,   10,   38,   13,
   14,   17,   12,   19,   22,   26,   29,   23,   17,   31,
   34,   38,   39,   40,   18,   32,   46,   23,   47,   53,
   24,   56,   58,   32,   50,   59,   28,   29,   61,   63,
   64,   67,   70,   71,   73,   75,   76,   77,   78,   79,
   80,   42,   43,   18,   30,   37,   45,    3,   57,   52,
   72,   62,   74,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    7,    0,    0,    7,    0,    7,    7,    7,    7,
   11,   37,   11,   11,   11,   11,   12,   38,   12,   12,
   12,   12,   17,    0,    0,   17,   17,   17,   18,    0,
    0,   18,   18,   18,   23,   23,   23,   24,   24,   24,
   32,   32,   32,   28,   29,   28,   29,
};
short yycheck[] = {                                     262,
    0,  257,    0,  265,  257,  263,    0,  257,    0,  257,
  261,  257,    0,  257,  257,  257,  257,  266,    0,  257,
  257,  257,  257,  268,    0,  264,  257,    0,  257,  257,
    0,  257,  257,    0,  267,  269,    0,    0,  257,  257,
  257,  257,  257,  257,  257,  257,  257,  257,  257,  257,
  257,    0,    0,   11,   20,   27,   35,  263,   48,   42,
   65,   54,   68,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  261,   -1,   -1,  264,   -1,  266,  267,  268,  269,
  264,  269,  266,  267,  268,  269,  264,  269,  266,  267,
  268,  269,  264,   -1,   -1,  267,  268,  269,  264,   -1,
   -1,  267,  268,  269,  267,  268,  269,  267,  268,  269,
  267,  268,  269,  267,  267,  269,  269,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 269
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"INTEGER","STRING","FLOAT",
"CHANNELDEF","LEFTLIST","NUMNETS","NUMPINS","OBSTACLES","RECTCORNERS",
"RIGHTLIST","SENSITIVE","MACRO","PSEUDOS",
};
char *yyrule[] = {
"$accept : start_mighty",
"start_mighty : nets corners pins left right obstacle macros sens pseudos",
"nets : NUMNETS INTEGER",
"corners : RECTCORNERS INTEGER cornerlist",
"cornerlist : cornerpt",
"cornerlist : cornerlist cornerpt",
"cornerpt : INTEGER INTEGER",
"pins : NUMPINS INTEGER pinlist",
"pinlist : pin",
"pinlist : pinlist pin",
"pin : INTEGER INTEGER INTEGER INTEGER",
"left :",
"left : lkeyword leftlist",
"lkeyword : LEFTLIST INTEGER",
"leftlist : lnet",
"leftlist : leftlist lnet",
"lnet : INTEGER",
"right :",
"right : rkeyword rightlist",
"rkeyword : RIGHTLIST INTEGER",
"rightlist : rnet",
"rightlist : rightlist rnet",
"rnet : INTEGER",
"obstacle :",
"obstacle : OBSTACLES INTEGER obstaclelist",
"obstaclelist : obstaclecorner",
"obstaclelist : obstaclelist obstaclecorner",
"obstaclecorner : INTEGER INTEGER INTEGER INTEGER INTEGER",
"macros :",
"macros : cell_macros",
"cell_macros : macro",
"cell_macros : cell_macros macro",
"macro : macro_keyword macrolist",
"macro_keyword : MACRO",
"macrolist : edge",
"macrolist : macrolist edge",
"edge : INTEGER INTEGER INTEGER INTEGER INTEGER INTEGER",
"sens :",
"sens : SENSITIVE INTEGER senslist",
"senslist : snet",
"senslist : senslist snet",
"snet : INTEGER",
"pseudos :",
"pseudos : PSEUDOS pseudolist",
"pseudolist : pseudo",
"pseudolist : pseudolist pseudo",
"pseudo : INTEGER INTEGER INTEGER INTEGER",
};
#endif
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#ifdef YYSTACKSIZE
#ifndef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#endif
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH 500
#endif
#endif
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short yyss[YYSTACKSIZE];
YYSTYPE yyvs[YYSTACKSIZE];
#define yystacksize YYSTACKSIZE

#include "input_l.h"

NETPTR S_input ( num_netsG, num_box, num_rows, num_cols,
num_obstacles, num_pins )

int *num_netsG,		/* total number of nets */
    *num_box,           /* number of corners of box */
    *num_rows,		/* size of bounding box in y */
    *num_cols,		/* size of bounding box in x */
    *num_obstacles,	/* total number of obstacles */
    *num_pins;		/* total number of pins */

{
    int i ;                                 /* counter */
    int leftcol, rightcol ;           /* markers for routing region */
    int x, y ;                        /* temporary variables for pins */
    int dir ;                               /* pin side */
    PINPTR newpin ;                   /* pointer to copy of pin */
    PIN_LISTPTR *sortarray ;          /* used to sort third layer pins */
    int S_sortbyxy() ;                /* sort routine */
    BOOL process ;                    /* if we should check S_onboundary*/
    PIN_LISTPTR curpin ;              /* pointer to current third layer pin */

#ifdef YYDEBUG
    extern int yydebug ;
    yydebug = TRUE ;
#endif

    yyin = input_fileG ;
    /*
     *  initialize variables
     */
    bounding_boxG = (LINKPTR)NULL;
    num_leftG = num_rightG = 0;
    leftG = rightG = NULL;
    line_countS = 0;
    xminS = INFINITY;
    yminS = INFINITY;
    xmaxS = - INFINITY;
    ymaxS = - INFINITY;
    obstacleG = (LINKPTR)NULL;
    macroG = (MACROPTR)NULL ;
    two5pinsG = (PIN_LISTPTR)NULL ;
    num3pinS = 0 ;
    addpseudoG = FALSE ;

    /* *********************************************************
     *  READ INPUT
     ************************************************************/
    yyparse();                      

    /* now set the grid */
    Ygrid_setx( xgridG, xshift ) ;
    Ygrid_setx( ygridG, yshift ) ;


    if( two5pinsG ){
	addguideG = TRUE ;

	/* sort pins according to increasing x and decreasing y for use */
	/* in vertical constraint graph */
	sortarray = (PIN_LISTPTR *)Ysafe_malloc((num3pinS+1)*sizeof(PIN_LISTPTR));
	i = 0 ;
	for( curpin = two5pinsG; curpin; curpin = curpin->next ){
	    sortarray[i++] = curpin ;
	}
	Yquicksort( (char *) sortarray,num3pinS,sizeof(PIN_LISTPTR),S_sortbyxy ) ;

	/* relink list now in sorted order */
	for( i= 0 ; i < num3pinS-1; i++ ){
	    sortarray[i]->next = sortarray[i+1] ;
	}
	/* fix last member of array */
	sortarray[num3pinS-1]->next = (PIN_LISTPTR)NULL ;
	two5pinsG = sortarray[0] ;
	Ysafe_free( sortarray ) ;
	i = 0 ;
	/* 
	for( curpin = two5pinsG; curpin; curpin = curpin->next ){
	    printf( "pin[%d]=%d,%d\n",++i, curpin->pin->x, curpin->pin->y ) ;
	}
	*/
    }

    /* determine the side of the macros if they exist */
    S_process_macros() ;

    /* determine the side of the bounding box for expansion */
    if( S_determine_sidesCCW( bounding_boxG ) ){
	abortFlagS = TRUE ;
    }

    /*
     *  UPDATE PIN LOCATIONS.
     *  If pin is on the boundary, move the pin
     *  one unit inside the routing area,
     *  and mark the direction of the movement
     */
    for( i = 1; i <= numNetS; i++ ){
	/* To find bounds */
	if( net_arrayG[i].left == YES ){
	    leftcol = 1;
	} else {
	    leftcol = numColS;
	}
	if( net_arrayG[i].right == YES ){
	    rightcol = numColS;
	} else {
	    rightcol = 1;
	}

	for( pinptrS = net_arrayG[i].pin; pinptrS ; pinptrS = pinptrS->next ){

	    /* don't move pins inside boundary for pins on layer three */
	    /* and pseudo pins but do move them to the grid */
	    if( pinptrS->type == THREE || pinptrS->type == TEMP ){
		process = FALSE ;
	    } else {
		process = TRUE ;
	    }
	    if( process && (dir = S_onboundary( i, pinptrS ) ) ){

		/* MOVE THE PINS OFF THE BOUNDARY */
		switch( dir ){
		case DOWN : /* (pinptrS->y)++ */
		   /* first round to closest grid upwards */
		   Ygridy_up( &(pinptrS->y) ) ;
		   y = pinptrS->y ;  /* save boundary point */
		   /* next move pin outwards one grid up */
		   pinptrS->y += ygridG ;

		   /* for other direction grid to nearest grid point */
		   Ygridx( &(pinptrS->x) ) ;
		   x = pinptrS->x;

		   break;
		case UP   : /* (pinptrS->y)-- */
		   /* first round to closest grid downwards */
		   Ygridy_down( &(pinptrS->y) ) ;
		   y = pinptrS->y;  /* save boundary point */
		   /* next move pin outwards one grid down */
		   pinptrS->y -= ygridG ;

		   /* for other direction grid to nearest grid point */
		   Ygridx( &(pinptrS->x) ) ;
		   x = pinptrS->x;

		   break;
		case LEFT : /* (pinptrS->x)-- */
		   /* first round to closest grid downwards */
		   Ygridx_down( &(pinptrS->x) ) ;
		   x = pinptrS->x;  /* save boundary point */
		   /* next move pin outwards one grid down */
		   pinptrS->x -= xgridG ;

		   /* for other direction grid to nearest grid point */
		   Ygridy( &(pinptrS->y) ) ;
		   y = pinptrS->y ;

		   break;
		case RIGHT :/* (pinptrS->x)++ */
		   /* first round to closest grid upwards */
		   Ygridx_up( &(pinptrS->x) ) ;
		   x = pinptrS->x;  /* save boundary point */
		   /* next move pin outwards one grid up */
		   pinptrS->x += xgridG ;

		   /* for other direction grid to nearest grid point */
		   Ygridy( &(pinptrS->y) ) ;
		   y = pinptrS->y ;

		   break;
		}
		/*
		 *  Shift xminS to 0 and yminS to 0.
		 *  Use given grid and divide by grid 
		 *  Shift to (1,1)
		 *  
		 */
	        /* shift to (0,0) */
		x -= xshift ;
		y -= yshift ;
		/* divide by grid */
		x /= xgridG ;
		y /= ygridG ;
	        /* shift to (1,1) */
		x++ ;
		y++ ;


		newpin = S_getpin();
		newpin->type = PERM;
		newpin->next = net_arrayG[i].tmppin;
		net_arrayG[i].tmppin = newpin;
		newpin->layer = pinptrS->layer;
	        newpin->x = x;
		newpin->y = y;
		newpin->x_given = pinptrS->x_given ;
		newpin->y_given = pinptrS->y_given ;
		newpin->group = dir;

	    }

	    /*
	     *  Shift xminS to 0 and yminS to 0.
	     *  Use given grid and divide by grid 
	     *  Shift to (1,1)
	     *  
	     */
	    /* shift to (0,0) */
	    pinptrS->x -= xshift;
	    pinptrS->y -= yshift ;
	    /* divide by grid */
	    pinptrS->x /= xgridG ;
	    pinptrS->y /= ygridG ;
	    /* shift to (1,1) */
	    pinptrS->x++;
	    pinptrS->y++ ;

	    leftcol = MIN( pinptrS->x, leftcol );
	    rightcol = MAX( pinptrS->x, rightcol );

	}
	if( leftcol <= rightcol ){
	    net_arrayG[i].colleft = leftcol;
	    net_arrayG[i].colright = rightcol;
	} else {
	    net_arrayG[i].colleft = 0;
	    net_arrayG[i].colright = 0;
	}
    } /* end update pin locations */

    /* now grid bounding box and macros */
    S_grid_path( bounding_boxG, CCW ) ;

    /* side were determined in process_macros */
    for( curmacroS = macroG; curmacroS; curmacroS = curmacroS->next ){
	S_grid_path( curmacroS->edges, CW ) ;
    }

    for( linkS = obstacleG; linkS; linkS = linkS->netnext ){
	/* shift to (0,0) */
	linkS->x1 -= xshift;
	linkS->x2 -= xshift;
	linkS->y1 -= yshift;
	linkS->y2 -= yshift;
	/* go to nearest grid points */
	Ygridx( &(linkS->x1) ) ;
	Ygridx( &(linkS->x2) ) ;
	Ygridy( &(linkS->y1) ) ;
	Ygridy( &(linkS->y2) ) ;
	linkS->x1 /= xgridG;
	linkS->x2 /= xgridG;
	linkS->y1 /= ygridG;
	linkS->y2 /= ygridG;
	/* shift to (1,1) */
	linkS->x1++;
	linkS->x2++;
	linkS->y1++;
	linkS->y2++;
    }

    /* add macro obstacles */
    S_add_macro_obstacles() ;

    S_check_pins() ;

    if( abortFlagS ){
	YexitPgm(145) ;
    }
    /* allocate space for processed third layer pins all the time */
    layer3G = (PIN_LISTPTR *) 
	Ysafe_calloc( numColS+1,sizeof(PIN_LISTPTR) ) ;

    /* return variables to calling routine */
    *num_netsG = numNetS ;
    *num_box = numCornerPtS;
    *num_obstacles = numObstacleS ;
    *num_pins = numPinS ;
    *num_rows = numRowS ;
    *num_cols = numColS ;
    return (net_arrayG);
}



yyerror(s)
char    *s;
{
    M( ERRMSG, "input", "\nERROR reading input file\n" );
    sprintf( YmsgG,"  line %d " , line_countS+1);
    M( MSG, NULL, YmsgG ) ;
    sprintf( YmsgG,"near '%s' : %s\n", yytext, s);
    M( MSG, NULL, YmsgG ) ;
    abortFlagS = TRUE ;
}

yywrap()
{
    return(1);
}                      

int S_onboundary( i, pinptr )
int i ; /* net */
PINPTR pinptr;
{
    LINKPTR linkS;
    int indir = 0;
    int outdir = 0;
    int px, py ;

    px = pinptr->x;
    py = pinptr->y;

    /* check for pins on the boundary */
    for( linkS = bounding_boxG; linkS; linkS = linkS->netnext ){
	if( linkS->y1 == py && linkS->x1 < px && px < linkS->x2 )
	    return( DOWN );
	if( linkS->y1 == py && linkS->x2 < px && px < linkS->x1 )
	    return( UP );
	if( linkS->x1 == px && linkS->y1 < py && py < linkS->y2 )
	    return( LEFT );
	if( linkS->x1 == px && linkS->y2 < py && py < linkS->y1 )
	    return( RIGHT );
    }

    /* check for pins on the core obstacle boundary if they exist */
    /* note that direction is opposite of boundary. */
    for( curmacroS = macroG; curmacroS; curmacroS = curmacroS->next ){
	for( linkS = curmacroS->edges; linkS; linkS = linkS->netnext ){
	    /* edge_direction is the direction of the cell edge */
	    /* using point 1 as tail and point 2 as head of vector */
	    /* the return direction is where to place the pin */
	    /* relative to this edge */
	    switch( linkS->p.edge_direction ){
	    case R_EDGE:
		if( linkS->y1 == py && linkS->x1 < px && px < linkS->x2 )
		    return( DOWN );
	    case L_EDGE:
		if( linkS->y1 == py && linkS->x2 < px && px < linkS->x1 )
		    return( UP );
	    case U_EDGE:
		if( linkS->x1 == px && linkS->y1 < py && py < linkS->y2 )
		    return( LEFT );
	    case D_EDGE:
		if( linkS->x1 == px && linkS->y2 < py && py < linkS->y1 )
		    return( RIGHT );
	    } /* end switch */
	}
    }

    /*  Now check if there is a pin on a convex corner, for which
	routing is impossible  */
    for( linkS = bounding_boxG; linkS; linkS = linkS->netnext ){
        if( linkS->y1 == py && linkS->x1 == px && px < linkS->x2 )
	    outdir = RIGHT;
        else if( linkS->y1 == py && linkS->x1 == px && py < linkS->y2 )
	    outdir = DOWN;
        else if( linkS->y1 == py && linkS->x1 == px && px > linkS->x2 )
    	    outdir = LEFT;
        else if( linkS->y1 == py && linkS->x1 == px && py > linkS->y2 )
	    outdir = UP;

        if( linkS->y2 == py && linkS->x2 == px && px > linkS->x1 )
	    indir = RIGHT;
        else if( linkS->y2 == py && linkS->x2 == px && py > linkS->y1 )
	    indir = DOWN;
        else if( linkS->y2 == py && linkS->x2 == px && px < linkS->x1 )
	    indir = LEFT;
        else if( linkS->y2 == py && linkS->x2 == px && py < linkS->y1 )
	    indir = UP;
    }

    if( indir == UP && outdir == RIGHT ||
	indir == RIGHT && outdir == DOWN ||
	indir == DOWN && outdir == LEFT ||
	indir == LEFT && outdir == UP ){
	/*
	 *  Report the erroneous pin and exit -
	 *  Note that the direction of linkSs are reversed
	 */
	sprintf(YmsgG, "Isolated pin for net:%d @(%d, %d)\n", 
	    number_to_name(i), pinptr->x_given, pinptr->y_given);
	M( ERRMSG, "S_onboundary", YmsgG ) ;
	abortFlagS = TRUE ;
    }
    return( 0 );
} /* end S_onboundary */

add_obstacle( x1, y1, x2, y2, layer ) 
int x1, y1, x2, y2, layer ;
{
    linkS = S_getlink();
    linkS->netnext = obstacleG;
    obstacleG = linkS;
    linkS->p.user_given = FALSE;
    linkS->x1 = MIN( x1,x2 );
    linkS->y1 = MIN( y1,y2 );
    linkS->x2 = MAX( x1,x2 );
    linkS->y2 = MAX( y1,y2 );
    linkS->layer = layer ;
    numObstacleS++ ;
}

static S_check_pins()
{
    int i, j ;
    PINPTR pinptr ;
    int matchX, matchY, matchL ;

    for( i = 1; i <= numNetS; i++ ){

	for( pinptrS = net_arrayG[i].pin;pinptrS;pinptrS=pinptrS->next ){
	    in_maze( pinptrS, i ) ;
	}
	for( pinptrS=net_arrayG[i].tmppin;pinptrS;pinptrS=pinptrS->next ){
	    in_maze( pinptrS, i ) ;
	}
    }
    /* check for two pins at same location */
    for( i = 1; i <= numNetS; i++ ){

	for( pinptrS = net_arrayG[i].pin;pinptrS;pinptrS=pinptrS->next ){
	    matchX = pinptrS->x ;
	    matchY = pinptrS->y ;
	    matchL = pinptrS->layer ;

	    for( j = i; j <= numNetS; j++ ){
		if( i == j ){
		    continue ;
		}
		for( pinptr=net_arrayG[j].pin;pinptr;pinptr=pinptr->next){
		    if( pinptr == pinptrS ){
			continue ;
		    }
		    if( pinptr->x == matchX && pinptr->y == matchY && 
			pinptr->layer == matchL ){
			sprintf( YmsgG, 
			"Found two pins at (%d,%d) name#1:%d @(%d,%d) name#2:%d @(%d,%d)\n",
			matchX, matchY,
			number_to_name(i), 
			pinptrS->x_given,
			pinptrS->y_given,
			number_to_name(j), 
			pinptr->x_given,
			pinptr->y_given ) ;
			M(ERRMSG,"S_check_pins", YmsgG ) ;
			abortFlagS = TRUE ;
		    }
		}
		for( pinptr=net_arrayG[j].tmppin;pinptr;pinptr=pinptr->next){
		    if( pinptr == pinptrS ){
			continue ;
		    }
		    if( pinptr->x == matchX && pinptr->y == matchY && 
			pinptr->layer == matchL ){
			sprintf( YmsgG, 
			"Found two pins at (%d,%d) name#1:%d @(%d,%d) name#2:%d @(%d,%d)\n",
			matchX, matchY,
			number_to_name(i), 
			pinptrS->x_given,
			pinptrS->y_given,
			number_to_name(j), 
			pinptr->x_given,
			pinptr->y_given ) ;
			M(ERRMSG,"S_check_pins", YmsgG ) ;
			abortFlagS = TRUE ;
		    }
		}
	    }
		
	}
    }
}

static in_maze( pinptr, net )
PINPTR pinptr ;
int net ;
{
    /* perform error check to make sure within */
    /* memory allocated */
    if( pinptr->x < 1 || pinptr->x > numColS ){
	sprintf( YmsgG, "pin @(%d,%d) net:%d outside maze\n",
	    pinptr->x, pinptr->y,
	    number_to_name(net) );
	M( ERRMSG, "in_maze", YmsgG ) ;
	abortFlagS = TRUE ;
    } else if( pinptr->y < 1 || pinptr->y > numRowS ){
	sprintf( YmsgG, "pin @(%d,%d) net:%d outside maze\n",
	    pinptr->x, pinptr->y,
	    number_to_name(net) );
	M( ERRMSG, "in_maze", YmsgG ) ;
	abortFlagS = TRUE ;
    }
} /* end in_maze */
#define YYABORT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse()
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;
    extern char *getenv();

    if (yys = getenv("YYDEBUG"))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if (yyn = yydefred[yystate]) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("yydebug: state %d, reading %d (%s)\n", yystate,
                    yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("yydebug: state %d, shifting to state %d\n",
                    yystate, yytable[yyn]);
#endif
        if (yyssp >= yyss + yystacksize - 1)
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#ifdef lint
    goto yynewerror;
#endif
yynewerror:
#if YYDEBUG
    {
        int test_state, i, expect, two_or_more ;
        char err_msg[BUFSIZ] ;
        if( yyname[yychar] ){
            sprintf( err_msg, "\nsyntax error - found:%s expected:",
                yyname[yychar] ) ;
            two_or_more = 0 ;
            if( test_state = yysindex[yystate] ){
                for( i = YYERRCODE+1; i <= YYMAXTOKEN; i++ ){
                    expect = test_state + i ;
                    if( expect <= YYTABLESIZE && yycheck[expect] == i ){
                        if( two_or_more ){
                            strcat( err_msg, " | " ) ;
                        } else {
                            two_or_more = 1 ;
                        }
                        strcat( err_msg, yyname[i] ) ;
                     }
                 }
             }
            if( test_state = yyrindex[yystate] ){
                for( i = YYERRCODE+1; i <= YYMAXTOKEN; i++ ){
                    expect = test_state + i ;
                    if( expect <= YYTABLESIZE && yycheck[expect] == i ){
                        if( two_or_more ){
                            strcat( err_msg, " | " ) ;
                        } else {
                            two_or_more = 1 ;
                        }
                        strcat( err_msg, yyname[i] ) ;
                     }
                 }
             }
             strcat( err_msg, "\n" ) ;
             yyerror( err_msg ) ;
        } else {
            yyerror("syntax error");
        }
     }
#else
     yyerror("syntax error");
#endif
#ifdef lint
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("yydebug: state %d, error recovery shifting\
 to state %d\n", *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yyss + yystacksize - 1)
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("yydebug: error recovery discarding state %d\n",
                            *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("yydebug: state %d, error recovery discards token %d (%s)\n",
                    yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("yydebug: state %d, reducing by rule %d (%s)\n",
                yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 2:
{
			numNetS = yyvsp[0].ival ;
			net_arrayG = allocate_nets (numNetS + 2);
			init_name_translation (numNetS);
		    }
break;
case 3:
{
			slinkS->x1 = bounding_boxG->x2;
			slinkS->y1 = bounding_boxG->y2;
			slinkS->p.user_given = FALSE;
			/*
			 *  To shift (xminS, yminS) to (1, 1)
			 *  Now use three stage process
			 *   1. shift to (0,0).
			 *   2. divide by grid given (see below)
			 *   3. shift to (1,1).
			 */
			xshift = xminS ;
			yshift = yminS ;
			numColS = (xmaxS - xshift) / xgridG + 1 ;
			numRowS = (ymaxS - yshift) / ygridG + 1 ;
			if( numColS < 3 ){
			    M( ERRMSG, "input",
			    "problem too small. Insufficient number of columns. Try finer grid.\n" ) ;
			    abortFlagS = TRUE ;
			}
			if( numRowS < 2 ){
			    M( ERRMSG,"input", 
			    "problem too small. Insufficient number of rows. Try finer grid.\n" ) ;
			    abortFlagS = TRUE ;
			}
			if( numCornerPtS != yyvsp[-1].ival ){
			    M( ERRMSG, "input",
			    "ERROR:number of rectagonal corners incorrect\n" ) ;
			    abortFlagS = TRUE ;
			}
		    }
break;
case 6:
{
			/* x y */
			xminS = MIN( xminS, yyvsp[-1].ival );
			xmaxS = MAX( xmaxS, yyvsp[-1].ival );
			yminS = MIN( yminS, yyvsp[0].ival );
			ymaxS = MAX( ymaxS, yyvsp[0].ival );
			linkS = S_getlink();
			if( bounding_boxG != (LINKPTR)NULL ){
			    linkS->x1 = bounding_boxG->x2;
			    linkS->y1 = bounding_boxG->y2;
			} else {
			    slinkS = linkS;
			}
			linkS->netnext = bounding_boxG;
		        bounding_boxG = linkS;
			linkS->x2 = yyvsp[-1].ival;
			linkS->y2 = yyvsp[0].ival;
			linkS->p.user_given = FALSE;
			numCornerPtS++ ;
		    }
break;
case 7:
{
			if( numPinS != yyvsp[-1].ival ){
			    M( WARNMSG, "input", 
			    "number of pins incorrect-" ) ;
			    sprintf( YmsgG, 
			    "will use %d pins instead of %d\n",
				numPinS, yyvsp[-1].ival ) ;
			    M( MSG, NULL, YmsgG ) ;
			}
		    }
break;
case 10:
{
			/* netname x y layer */
			netnumS = name_to_number( yyvsp[-3].ival );
			pinptrS = S_getpin();
			pinptrS->x = pinptrS->x_given = yyvsp[-2].ival;
			pinptrS->y = pinptrS->y_given = yyvsp[-1].ival;
			pinptrS->next = net_arrayG[netnumS].pin;
			net_arrayG[netnumS].pin = pinptrS;
			if( yyvsp[0].ival == 1 || yyvsp[0].ival == 2 ){
			    pinptrS->layer = yyvsp[0].ival;
			    pinptrS->type = PERM;
			} else if( yyvsp[0].ival == 3 ){
			    pinptrS->layer = yyvsp[0].ival;
			    pinptrS->type = THREE ;
			    num3pinS++ ;
			    {
				/* allocate list of 1/2 level pins */
				PIN_LISTPTR tempin ;
				if( tempin = two5pinsG ){
				    two5pinsG = (PIN_LISTPTR) 
					Ysafe_malloc( sizeof(PIN_LIST) ) ;
				    two5pinsG->next = tempin ;
				} else {
				    two5pinsG = (PIN_LISTPTR) 
					Ysafe_malloc( sizeof(PIN_LIST) ) ;
				    two5pinsG->next = (PIN_LISTPTR)NULL ;
				}
				two5pinsG->pin = pinptrS ;
				two5pinsG->net = netnumS ; /* need net number */
			    }
			} else {
			    sprintf( YmsgG,
				"layer incorrect for pin @(%d,%d) ",
				yyvsp[-2].ival, yyvsp[-1].ival ) ;
			    M( ERRMSG, "input", YmsgG ) ;
			    sprintf( YmsgG,
			        "net:%d - must be 1, 2, or 3.\n", yyvsp[-3].ival ) ;
			    M( MSG, NULL, YmsgG ) ;
			    abortFlagS = TRUE ;
			}
			numPinS++ ;
		    }
break;
case 12:
{
			if( invalidS ){
			    M( WARNMSG, "input","left list incorrect-" ) ;
			    sprintf( YmsgG, 
				"will use %d pins instead of %d\n",
				num_leftG - invalidS, num_leftG ) ;
			    M( MSG, NULL, YmsgG ) ;
			    /* update num of valid left signals */
			    num_leftG -= invalidS ;
			}
		    }
break;
case 13:
{
			num_leftG = yyvsp[0].ival ;
			leftG = S_allocatevector(num_leftG);
			validLS = 1 ;
			invalidS = 0 ;
		    }
break;
case 16:
{
			netS = leftG[validLS++] = name_to_number( yyvsp[0].ival );
			if( netS <= 0 || netS > numNetS ){
			    sprintf( YmsgG,
				"Netname for left net:%d ", yyvsp[0].ival) ;
			    M( ERRMSG, "input", YmsgG ) ;
			    M( MSG, NULL, 
				"could not be crossreferenced.\n" ) ;
			    abortFlagS = TRUE ;
			} else {
			    net_arrayG[netS].left = YES;
			}
			if(!( net_arrayG[netS].pin)  ){
			    sprintf( YmsgG,
				"No fixed pin for left net:%d\n", yyvsp[0].ival) ;
			    M( WARNMSG, "input", YmsgG ) ; 
			    net_arrayG[netS].pin = NO ;
			    /* this was not valid subtract from array */
			    validLS-- ;
			    invalidS++ ;
			}
		    }
break;
case 18:
{
			if( invalidS ){
			    M( WARNMSG, "input",
			    "right list incorrect-" ) ;
			    sprintf( YmsgG, 
			    "will use %d pins instead of %d\n",
				num_rightG - invalidS, num_rightG ) ;
			    M( MSG, NULL, YmsgG ) ;
			    /* update num of valid right signals */
			    num_rightG -= invalidS ;
			}
		    }
break;
case 19:
{
			num_rightG = yyvsp[0].ival ;
			rightG = S_allocatevector(num_rightG);
			validRS = 1 ;
			invalidS = 0 ;
		    }
break;
case 22:
{

			netS = rightG[validRS++] = name_to_number( yyvsp[0].ival );
			if( netS <= 0 || netS > numNetS ){
			    sprintf( YmsgG,
			    "Netname for right net:%d ",yyvsp[0].ival) ;
			    M( ERRMSG, "input", YmsgG ) ;
			    M( MSG, NULL, 
				"could not be crossreferenced.\n" ) ;
			    abortFlagS = TRUE ;
			} else {
			    net_arrayG[netS].right = YES;
			}
			if(!( net_arrayG[netS].pin)  ){
			    sprintf( YmsgG,
				"No fixed pin for right net:%d\n", yyvsp[0].ival) ;
			    M( WARNMSG, "input", YmsgG ) ;
			    net_arrayG[netS].pin = NO ;
			    /* this was not valid subtract from array */
			    validRS-- ;
			    invalidS++ ;
			}
		    }
break;
case 27:
{
			/* x1, y1, x2, y2, layer */
			if( yyvsp[-4].ival != yyvsp[-2].ival && yyvsp[-3].ival != yyvsp[-1].ival ){
			    sprintf(YmsgG,"Problem with obstacle:%d ",
				numObstacleS+1 );
			    M( ERRMSG, "input", YmsgG ) ;
			    M( MSG, NULL,
			        "obstacle must be rectilinear\n");
			    abortFlagS = TRUE ;
			}
			if( yyvsp[0].ival != 1 && yyvsp[0].ival != 2 ){
			    sprintf( YmsgG, 
				"layer incorrect for obstacle %d ",
				numObstacleS+1 ) ;
			    M( ERRMSG, "input", YmsgG ) ;
			    M( MSG, NULL, "- must be 1 or 2.\n" ) ;
			    abortFlagS = TRUE ;
			}
			add_obstacle( yyvsp[-4].ival, yyvsp[-3].ival, yyvsp[-2].ival, yyvsp[-1].ival, yyvsp[0].ival ) ;
		    }
break;
case 33:
{
			if( curmacroS = macroG ){
			    macroG = (MACROPTR) 
				Ysafe_malloc( sizeof(MACROBOX) ) ;
			    macroG->next = curmacroS ;
			} else {
			    macroG = (MACROPTR) 
				Ysafe_malloc( sizeof(MACROBOX) ) ;
			    macroG->next = (MACROPTR)NULL ;
			}
			macroG->edges = (LINKPTR)NULL ;
			numCornerPtS = 0 ;
		    }
break;
case 36:
{
			/* x1 y1 x2 y2 layer1Flag layer2Flag */
			if( edgePtrS = macroG->edges ){
			    edgePtrS = slinkS->netnext = S_getlink() ;
			} else {
			    edgePtrS = macroG->edges = S_getlink() ;
			}
			slinkS = edgePtrS ;
			edgePtrS->netnext = (LINKPTR)NULL ;
			edgePtrS->p.user_given = FALSE;
			edgePtrS->x1 = yyvsp[-5].ival ;
			edgePtrS->y1 = yyvsp[-4].ival ;
			edgePtrS->x2 = yyvsp[-3].ival ;
			edgePtrS->y2 = yyvsp[-2].ival ;
			/* ----------------------------------------
			    store layer as integer in following way 
			    layer 1     layer 2      layer 
			        0          0            0 
				0          1            1
				1          0            2
				1          1            3
			   ---------------------------------------- */
			if( yyvsp[-1].ival != 0 && yyvsp[-1].ival != 1 ){
			    M( ERRMSG,"input", 
				"layer1 flag must be 0 or 1\n" ) ;
			} else if( yyvsp[0].ival != 0 && yyvsp[0].ival != 1 ){
			    M( ERRMSG, "input",
				"layer2 flag must be 0 or 1\n" ) ;
			} else {
			    edgePtrS->layer = 2 * yyvsp[-1].ival + yyvsp[0].ival ;
			}
			numCornerPtS++ ;
		    }
break;
case 38:
{
			if( numSenS != yyvsp[-1].ival ){
			    M( WARNMSG, "input",
			    "number of sensitive nets incorrect-" ) ;
			    sprintf( YmsgG, 
			    "will use %d nets instead of %d\n",
				numSenS, yyvsp[-1].ival ) ;
			    M( MSG, NULL, YmsgG ) ;
			}
		    }
break;
case 41:
{
			netS = name_to_number( yyvsp[0].ival );
			if( netS <= 0 || netS > numNetS ){
			    sprintf( YmsgG,
				"Netname for sensitive net:%d ",yyvsp[0].ival) ;
			    M( ERRMSG, "input", YmsgG ) ;
			    M( MSG, NULL, 
			    "could not be crossreferenced.\n" ) ;
			    abortFlagS = TRUE ;
			} else {
			    net_arrayG[netS].sens = YES;
			}
			numSenS++ ;
		    }
break;
case 43:
{
			addpseudoG = TRUE ;
		    }
break;
case 46:
{
			/* netname x y layer */
			netnumS = name_to_number( yyvsp[-3].ival );
			pinptrS = S_getpin();
			pinptrS->x = pinptrS->x_given = yyvsp[-2].ival;
			pinptrS->y = pinptrS->y_given = yyvsp[-1].ival;
			pinptrS->next = net_arrayG[netnumS].pin;
			net_arrayG[netnumS].pin = pinptrS;
			if( yyvsp[0].ival == 1 || yyvsp[0].ival == 2 ){
			    pinptrS->layer = yyvsp[0].ival;
			    pinptrS->type = TEMP;
			} else {
			    sprintf( YmsgG,
				"layer incorrect for pseudopin @(%d,%d) ",
				yyvsp[-2].ival, yyvsp[-1].ival ) ;
			    M( ERRMSG, "input", YmsgG ) ;
			    sprintf( YmsgG,
			        "net:%d - must be 1 or 2.\n", yyvsp[-3].ival ) ;
			    M( MSG, NULL, YmsgG ) ;
			    abortFlagS = TRUE ;
			}
			numPinS++ ;
		    }
break;
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("yydebug: after reduction, shifting from state 0 to\
 state %d\n", YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("yydebug: state %d, reading %d (%s)\n",
                        YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("yydebug: after reduction, shifting from state %d \
to state %d\n", *yyssp, yystate);
#endif
    if (yyssp >= yyss + yystacksize - 1)
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
