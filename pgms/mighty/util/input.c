
/* ----------------------------------------------------------------- 
FILE:	    input.c.c <- input_yacc <- input_lex
DESCRIPTION:This file contains the grammar (BNF) for the mighty
	    input file parser.
	    The rules for lex are in input_lex.
	    The grammar for yacc is in input_yacc
	    The output of yacc (y.tab.c) is renamed to input.c
CONTENTS:   NETPTR S_input ( num_nets, num_box, num_rows, 
		num_cols, num_obstacles, num_pins )
		int *num_nets,		total number of nets
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
REVISIONS:  
----------------------------------------------------------------- */
#ifndef lint
static char SccsId[] = "%Z% %M% version %I% %G%" ;
#endif

#include <yalecad/base.h>
#include <yalecad/message.h>
#include <yalecad/wgraphics.h>
#include <yalecad/colors.h>
#include <globals.h>

/* #define YYDEBUG  */ /* condition compile for yacc debug */
#undef REJECT

static int line_count ;
static int firstXS ;
static int firstYS ;
static int oldXS ;
static int oldYS ;
static BOOL firstPointS = TRUE ;
static int minxS = INT_MAX ;
static int minyS = INT_MAX ;
static int maxxS = INT_MIN ;
static int maxyS = INT_MIN ;
static int pinsizeS = 1 ;
static char bufferS[LRECL] ;


static int  colorS[] = {
    TWBLACK,
    TWBLUE,  /* layer1 - metal2 */
    TWGREEN, /* layer2 - metal1 */
    TWRED    /* layer3 - poly */
} ;


typedef union  {
    int ival ;
    char *string ;
    double fval ;
} YYSTYPE;
# define INTEGER 257
# define STRING 258
# define FLOAT 259
# define CHANNELDEF 260
# define LEFTLIST 261
# define NUMNETS 262
# define NUMPINS 263
# define OBSTACLES 264
# define RECTCORNERS 265
# define RIGHTLIST 266
# define SENSITIVE 267
# define MACRO 268
# define PSEUDOS 269
#define yyclearin yychar = -1
#define yyerrok yyerrflag = 0
extern int yychar;
extern short yyerrflag;
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 150
#endif
YYSTYPE yylval, yyval;
# define YYERRCODE 256



#include "input.h";


process_input( input_file )
FILE* input_file ;
{

#ifdef YYDEBUG
    extern int yydebug ;
    yydebug = TRUE ;
#endif

    yyin = input_file ;
    /* *********************************************************
     *  READ INPUT
     ************************************************************/
    yyparse();                      
} /* end process_input */

yyerror(s)
char    *s;
{
    M( ERRMSG, "input", "\nERROR reading input file\n" );
    sprintf( YmsgG,"  line %d " , line_count+1);
    M( MSG, NULL, YmsgG ) ;
    sprintf( YmsgG,"near '%s' : %s\n", yytext, s);
    M( MSG, NULL, YmsgG ) ;
}

yywrap()
{
    return(1);
}                      

#ifdef LADER_MON
set_pinsize(pin)
int pin ;
{
    pinsizeS=pin;
}
#endif

short yyexca[] ={
-1, 1,
	0, -1,
	-2, 0,
	};
# define YYNPROD 47
# define YYLAST 108
short yyact[]={

  57,  42,  47,  19,   5,  30,   8,   3,  12,  80,
  79,  78,  77,  76,  75,  74,  68,  72,  65,  70,
  69,  62,  54,  60,  51,  58,  55,  45,  33,  43,
  37,  26,  22,  34,  28,  16,  23,  13,   9,   6,
  67,  64,  53,  50,  40,  32,  25,  21,  15,  63,
  66,  49,  41,  39,  52,  31,  18,  20,  11,  24,
  14,  56,  46,  27,  38,  29,  17,  10,  35,   7,
   4,  36,   2,   1,   0,   0,   0,  44,   0,   0,
   0,   0,   0,   0,  48,   0,   0,   0,   0,   0,
   0,   0,   0,  59,   0,  61,   0,   0,   0,   0,
   0,   0,   0,   0,   0,  71,   0,  73 };
short yypact[]={

-255,-1000,-261,-218,-257,-219,-1000,-253,-220,-222,
-263,-225,-221,-226,-222,-1000,-223,-259,-229,-224,
-225,-1000,-1000,-1000,-226,-1000,-227,-1000,-1000,-267,
-228,-229,-1000,-1000,-1000,-1000,-1000,-230,-265,-267,
-1000,-233,-1000,-235,-1000,-231,-269,-232,-1000,-233,
-1000,-234,-235,-1000,-236,-1000,-1000,-239,-241,-1000,
-237,-1000,-238,-239,-1000,-240,-241,-1000,-1000,-242,
-243,-1000,-244,-1000,-245,-246,-247,-248,-1000,-1000,
-1000 };
short yypgo[]={

   0,  73,  72,  70,  69,  67,  66,  65,  64,  62,
  61,  60,  48,  59,  46,  58,  57,  47,  56,  55,
  45,  54,  42,  53,  44,  52,  51,  43,  50,  40,
  49,  41 };
short yyr1[]={

   0,   1,   2,   3,  11,  11,  12,   4,  13,  13,
  14,   5,   5,  15,  16,  16,  17,   6,   6,  18,
  19,  19,  20,   7,   7,  21,  21,  22,   8,   8,
  23,  23,  24,  25,  26,  26,  27,   9,   9,  28,
  28,  29,  10,  10,  30,  30,  31 };
short yyr2[]={

   0,   9,   2,   3,   1,   2,   2,   3,   1,   2,
   4,   0,   2,   2,   1,   2,   1,   0,   2,   2,
   1,   2,   1,   0,   3,   1,   2,   5,   0,   1,
   1,   2,   2,   1,   1,   2,   6,   0,   3,   1,
   2,   1,   0,   2,   1,   2,   4 };
short yychk[]={

-1000,  -1,  -2, 262,  -3, 265, 257,  -4, 263, 257,
  -5, -15, 261, 257, -11, -12, 257,  -6, -18, 266,
 -16, -17, 257, 257, -13, -14, 257, -12, 257,  -7,
 264, -19, -20, 257, 257, -17, -14, 257,  -8, -23,
 -24, -25, 268, 257, -20, 257,  -9, 267, -24, -26,
 -27, 257, -21, -22, 257, 257, -10, 269, 257, -27,
 257, -22, 257, -30, -31, 257, -28, -29, 257, 257,
 257, -31, 257, -29, 257, 257, 257, 257, 257, 257,
 257 };
short yydef[]={

   0,  -2,   0,   0,   0,   0,   2,  11,   0,   0,
  17,   0,   0,   0,   3,   4,   0,  23,   0,   0,
  12,  14,  16,  13,   7,   8,   0,   5,   6,  28,
   0,  18,  20,  22,  19,  15,   9,   0,  37,  29,
  30,   0,  33,   0,  21,   0,  42,   0,  31,  32,
  34,   0,  24,  25,   0,  10,   1,   0,   0,  35,
   0,  26,   0,  43,  44,   0,  38,  39,  41,   0,
   0,  45,   0,  40,   0,   0,   0,   0,  27,  46,
  36 };
#ifndef lint
static char yaccpar_sccsid[] = "@(#)yaccpar	4.1	(Berkeley)	2/11/83";
#endif not lint

# define YYFLAG -1000
# define YYERROR goto yyerrlab
# define YYACCEPT return(0)
# define YYABORT return(1)

/*	parser for yacc output	*/

#ifdef YYDEBUG
int yydebug = 0; /* 1 for debugging */
#endif
YYSTYPE yyv[YYMAXDEPTH]; /* where the values are stored */
int yychar = -1; /* current input token number */
int yynerrs = 0;  /* number of errors */
short yyerrflag = 0;  /* error recovery flag */

yyparse() {

	short yys[YYMAXDEPTH];
	short yyj, yym;
	register YYSTYPE *yypvt;
	register short yystate, *yyps, yyn;
	register YYSTYPE *yypv;
	register short *yyxi;

	yystate = 0;
	yychar = -1;
	yynerrs = 0;
	yyerrflag = 0;
	yyps= &yys[-1];
	yypv= &yyv[-1];

 yystack:    /* put a state and value onto the stack */

#ifdef YYDEBUG
	if( yydebug  ) printf( "state %d, char 0%o\n", yystate, yychar );
#endif
		if( ++yyps> &yys[YYMAXDEPTH] ) { yyerror( "yacc stack overflow" ); return(1); }
		*yyps = yystate;
		++yypv;
		*yypv = yyval;

 yynewstate:

	yyn = yypact[yystate];

	if( yyn<= YYFLAG ) goto yydefault; /* simple state */

	if( yychar<0 ) if( (yychar=yylex())<0 ) yychar=0;
	if( (yyn += yychar)<0 || yyn >= YYLAST ) goto yydefault;

	if( yychk[ yyn=yyact[ yyn ] ] == yychar ){ /* valid shift */
		yychar = -1;
		yyval = yylval;
		yystate = yyn;
		if( yyerrflag > 0 ) --yyerrflag;
		goto yystack;
		}

 yydefault:
	/* default state action */

	if( (yyn=yydef[yystate]) == -2 ) {
		if( yychar<0 ) if( (yychar=yylex())<0 ) yychar = 0;
		/* look through exception table */

		for( yyxi=yyexca; (*yyxi!= (-1)) || (yyxi[1]!=yystate) ; yyxi += 2 ) ; /* VOID */

		while( *(yyxi+=2) >= 0 ){
			if( *yyxi == yychar ) break;
			}
		if( (yyn = yyxi[1]) < 0 ) return(0);   /* accept */
		}

	if( yyn == 0 ){ /* error */
		/* error ... attempt to resume parsing */

		switch( yyerrflag ){

		case 0:   /* brand new error */

			yyerror( "syntax error" );
		yyerrlab:
			++yynerrs;

		case 1:
		case 2: /* incompletely recovered error ... try again */

			yyerrflag = 3;

			/* find a state where "error" is a legal shift action */

			while ( yyps >= yys ) {
			   yyn = yypact[*yyps] + YYERRCODE;
			   if( yyn>= 0 && yyn < YYLAST && yychk[yyact[yyn]] == YYERRCODE ){
			      yystate = yyact[yyn];  /* simulate a shift of "error" */
			      goto yystack;
			      }
			   yyn = yypact[*yyps];

			   /* the current yyps has no shift onn "error", pop stack */

#ifdef YYDEBUG
			   if( yydebug ) printf( "error recovery pops state %d, uncovers %d\n", *yyps, yyps[-1] );
#endif
			   --yyps;
			   --yypv;
			   }

			/* there is no state on the stack with an error shift ... abort */

	yyabort:
			return(1);


		case 3:  /* no shift yet; clobber input char */

#ifdef YYDEBUG
			if( yydebug ) printf( "error recovery discards char %d\n", yychar );
#endif

			if( yychar == 0 ) goto yyabort; /* don't discard EOF, quit */
			yychar = -1;
			goto yynewstate;   /* try again in the same state */

			}

		}

	/* reduction by production yyn */

#ifdef YYDEBUG
		if( yydebug ) printf("reduce %d\n",yyn);
#endif
		yyps -= yyr2[yyn];
		yypvt = yypv;
		yypv -= yyr2[yyn];
		yyval = yypv[1];
		yym=yyn;
			/* consult goto table to find next state */
		yyn = yyr1[yyn];
		yyj = yypgo[yyn] + *yyps + 1;
		if( yyj>=YYLAST || yychk[ yystate = yyact[yyj] ] != -yyn ) yystate = yyact[yypgo[yyn]];
		switch(yym){
			
case 3:
{
			/* used to set window */
			{
			    int delta ;
			    delta = ABS( maxyS - minyS ) ;
			    delta = MAX( delta, ABS( maxxS - minxS ) ) ;
			/*     TWdrawCell( 0, minxS, minyS, 
				minxS + delta, maxyS + delta, 
				TWWHITE, NULL ) ;
				*/
			}
			TWdrawNet( 0, oldXS, oldYS, 
			    firstXS, firstYS, 
			    TWBLACK, NULL ) ;
		    } break;
case 6:
{
			yypvt[-1].ival = (int) (yypvt[-1].ival * maG) ;
			yypvt[-0].ival = (int) (yypvt[-0].ival * maG) ;
			if( firstPointS ){
			    firstXS = yypvt[-1].ival ;
			    firstYS = yypvt[-0].ival ;
			    firstPointS = FALSE ;
			} else {
			    TWdrawNet( 0, oldXS, oldYS, yypvt[-1].ival, yypvt[-0].ival, TWBLACK, NULL ) ;
			}
			oldXS = yypvt[-1].ival ;
			oldYS = yypvt[-0].ival ;
			minxS = MIN( minxS, yypvt[-1].ival ) ;
			maxxS = MAX( maxxS, yypvt[-1].ival ) ;
			minyS = MIN( minyS, yypvt[-0].ival ) ;
			maxyS = MAX( maxyS, yypvt[-0].ival ) ;

		    } break;
case 7:
{
		    } break;
case 10:
{
			/* netname x y layer */
			yypvt[-2].ival = (int) (yypvt[-2].ival * maG) ;
			yypvt[-1].ival = (int) (yypvt[-1].ival * maG) ;
			sprintf( bufferS, "N%d", yypvt[-3].ival ) ;
			TWdrawPin( yypvt[-3].ival, yypvt[-2].ival-pinsizeS, yypvt[-1].ival-pinsizeS,
			    yypvt[-2].ival+pinsizeS, yypvt[-1].ival+pinsizeS, colorS[yypvt[-0].ival], 
			    bufferS ) ;
		    } break;
case 12:
{
		    } break;
case 13:
{
		    } break;
case 16:
{
		    } break;
case 18:
{
		    } break;
case 19:
{
		    } break;
case 22:
{
		    } break;
case 27:
{
			/* x1, y1, x2, y2, layer */
			TWdrawNet( 0, (int)(yypvt[-4].ival*maG), (int)(yypvt[-3].ival*maG),
			    (int)(yypvt[-2].ival*maG), (int)(yypvt[-1].ival*maG),
			    colorS[yypvt[-0].ival], NULL ) ;
		    } break;
case 33:
{
		    } break;
case 36:
{
			/* x1 y1 x2 y2 layer1Flag layer2Flag */
			if( yypvt[-1].ival ){
			    TWdrawNet( 0, (int)(yypvt[-5].ival*maG), (int)(yypvt[-4].ival*maG),
			    (int)(yypvt[-3].ival*maG), (int)(yypvt[-2].ival*maG),
				colorS[1], NULL ) ;
			}
			if( yypvt[-0].ival ){
			    TWdrawNet( 0, (int)(yypvt[-5].ival*maG), (int)(yypvt[-4].ival*maG),
			    (int)(yypvt[-3].ival*maG), (int)(yypvt[-2].ival*maG),
				colorS[2], NULL ) ;
			}
		    } break;
case 38:
{
		    } break;
case 41:
{
		    } break;
case 46:
{
			/* netname x y layer */
			yypvt[-2].ival = (int) (yypvt[-2].ival * maG) ;
			yypvt[-1].ival = (int) (yypvt[-1].ival * maG) ;
			sprintf( bufferS, "N%d", yypvt[-3].ival ) ;
			TWdrawPin( yypvt[-3].ival, yypvt[-2].ival-pinsizeS, yypvt[-1].ival-pinsizeS,
			    yypvt[-2].ival+pinsizeS, yypvt[-1].ival+pinsizeS, TWVIOLET, 
			    bufferS ) ;
		    } break; 
		}
		goto yystack;  /* stack new state and value */

	}
