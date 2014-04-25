
static char RCSinfo[]=
"$Header: gram.y,v 1.45 88/10/14 07:05:55 toml Exp $";

#include <stdio.h>
#include "twm.h"
#include "menus.h"
#include "list.h"
#include "util.h"

static char *Action = "";
static char *Name = "";
static MenuRoot	*root,
		*pull = NULL;


MenuRoot *GetRoot();

static char *ptr;
static int Button;
static int list;
static int mods = 0, cont = 0;
static int color;

extern int yylineno;

typedef union 
{
    int num;
    char *ptr;
} YYSTYPE;
# define LB 257
# define RB 258
# define MENUS 259
# define MENU 260
# define BUTTON 261
# define TBUTTON 262
# define DEFAULT_FUNCTION 263
# define F_MENU 264
# define F_UNFOCUS 265
# define F_REFRESH 266
# define F_FILE 267
# define F_TWMRC 268
# define F_CIRCLEUP 269
# define F_QUIT 270
# define F_NOP 271
# define F_TITLE 272
# define F_VERSION 273
# define F_EXEC 274
# define F_CUT 275
# define F_CIRCLEDOWN 276
# define F_SOURCE 277
# define F_CUTFILE 278
# define F_MOVE 279
# define F_ICONIFY 280
# define F_FOCUS 281
# define F_RESIZE 282
# define F_RAISE 283
# define F_LOWER 284
# define F_POPUP 285
# define F_DEICONIFY 286
# define F_FORCEMOVE 287
# define WINDOW_FUNCTION 288
# define F_DESTROY 289
# define F_WINREFRESH 290
# define F_BEEP 291
# define DONT_MOVE_OFF 292
# define ZOOM 293
# define F_SHOWLIST 294
# define F_HIDELIST 295
# define NO_BACKINGSTORE 296
# define NO_SAVEUNDER 297
# define F_ZOOM 298
# define F_FULLZOOM 299
# define ICONMGR_FOREGROUND 300
# define ICONMGR_BACKGROUND 301
# define ICONMGR_FONT 302
# define ICONMGR 303
# define ICONMGR_GEOMETRY 304
# define SHOW_ICONMGR 305
# define ICONMGR_NOSHOW 306
# define F_RAISELOWER 307
# define DECORATE_TRANSIENTS 308
# define RANDOM_PLACEMENT 309
# define ICONIFY_BY_UNMAPPING 310
# define DONT_ICONIFY_BY_UNMAPPING 311
# define WARPCURSOR 312
# define NUMBER 313
# define BORDERWIDTH 314
# define TITLE_FONT 315
# define REVERSE_VIDEO 316
# define RESIZE_FONT 317
# define NO_TITLE 318
# define AUTO_RAISE 319
# define FORCE_ICON 320
# define NO_HILITE 321
# define MENU_FONT 322
# define ICON_FONT 323
# define UNKNOWN_ICON 324
# define ICONS 325
# define ICON_DIRECTORY 326
# define META 327
# define SHIFT 328
# define CONTROL 329
# define WINDOW 330
# define TITLE 331
# define ICON 332
# define ROOT 333
# define FRAME 334
# define COLON 335
# define EQUALS 336
# define BORDER_COLOR 337
# define TITLE_FOREGROUND 338
# define TITLE_BACKGROUND 339
# define MENU_FOREGROUND 340
# define MENU_BACKGROUND 341
# define MENU_SHADOW_COLOR 342
# define MENU_TITLE_FOREGROUND 343
# define MENU_TITLE_BACKGROUND 344
# define ICON_FOREGROUND 345
# define ICON_BACKGROUND 346
# define ICON_BORDER_COLOR 347
# define NO_RAISE_ON_MOVE 348
# define NO_RAISE_ON_DEICONIFY 349
# define NO_RAISE_ON_RESIZE 350
# define COLOR 351
# define MONOCHROME 352
# define NO_TITLE_FOCUS 353
# define FUNCTION 354
# define F_FUNCTION 355
# define BORDER_TILE_FOREGROUND 356
# define BORDER_TILE_BACKGROUND 357
# define STRING 358
#define yyclearin yychar = -1
#define yyerrok yyerrflag = 0
extern int yychar;
extern short yyerrflag;
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 150
#endif
YYSTYPE yylval, yyval;
# define YYERRCODE 256


yyerror(s) char *s;
{
    fprintf(stderr, "twm: syntax error, line %d\n", yylineno);
    ParseError = 1;
}
RemoveDQuote(str)
char *str;
{
    strcpy(str, &str[1]);
    str[strlen(str)-1] = '\0';
}

MenuRoot *
GetRoot(name)
char *name;
{
    MenuRoot *tmp;

    tmp = FindMenuRoot(name);
    if (tmp == NULL)
	tmp = NewMenuRoot(name);

    return tmp;
}

short yyexca[] ={
-1, 1,
	0, -1,
	-2, 0,
-1, 34,
	257, 39,
	-2, 41,
-1, 35,
	257, 42,
	-2, 44,
	};
# define YYNPROD 148
# define YYLAST 423
short yyact[]={

   4, 165,  45,  95,  37,  44,  46,  42, 183, 182,
 151, 152, 153, 154, 155, 132, 133, 134, 132, 133,
 134,  56, 140, 135, 184, 138, 130, 162, 128, 126,
 185, 157,  43, 118, 160, 127,  19,  22,  45, 115,
  20,  21, 188, 180, 181, 149,  11,  55,  12,  28,
  33, 161,  26,  25,  27,  32,  15, 163,  23,  10,
   6,   8,  35,  36,   5,  34,   9,   7,  13,  39,
  14,  57, 144, 145, 146, 147, 148, 141, 158, 136,
 167, 170, 171, 172, 173, 176, 174, 175, 177, 178,
 179, 166,  16,  18,  17,  40,  41,  24,  38, 168,
 169, 142,  45,  88,  72,  65,  89,  80,  83,  63,
  61,  82,  81,  90,  91,  84,  67,  85,  68,  70,
  64,  73,  76,  78,  45,  71,  69,  45,  79,  66,
  62,  45, 131,  86,  87, 116, 150,  74,  75, 143,
 106, 187, 129, 105, 125, 104,  77,  88,  72,  65,
  89,  80,  83,  63,  61,  82,  81,  90,  91,  84,
  67,  85,  68,  70,  64,  73,  76,  78, 139,  71,
  69, 124,  79,  66,  62,  93, 137,  86,  87, 123,
 101,  74,  75, 117, 100,  99,  98,  97,   3,   2,
  77,   1,  94,  60,  92,  31,  29,  45,  88,  72,
  65,  89,  80,  83,  63,  61,  82,  81,  90,  91,
  84,  67,  85,  68,  70,  64,  73,  76,  78,   0,
  71,  69,   0,  79,  66,  62,   0,   0,  86,  87,
   0,   0,  74,  75,  30,  59,   0,   0,  92,   0,
   0,  77,  47,  48,  49,  50,  51,  52,  53,  54,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,  58,   0,   0,  96,   0,   0,
   0,   0, 102, 103,   0,   0,   0,   0, 107, 108,
   0,   0, 119, 120, 121, 122,   0,   0,   0,  92,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0, 109,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0, 110, 111, 112, 113, 114,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
 156, 159,   0,   0,   0,   0, 164,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0, 186,   0, 189,   0, 190,
   0,   0, 191, 192, 193, 194, 195, 196, 197, 198,
 199, 200, 201, 202, 203, 204, 205,   0, 206, 207,
   0,   0, 208 };
short yypact[]={

-1000,-1000,-256,-1000,-1000,-1000,-1000,-356,-356,-356,
-356,-356,-356,-356,-356,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,-292,-292,-1000,-1000,-1000,-1000,-1000,-161,
-333, -66,-1000,-1000,-1000,-1000,-1000,-356,-356,-1000,
-1000,-1000, -66, -66,-1000,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,-1000,-1000,-356,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-356,-356,
-356,-356,-356,-1000,-1000,-1000,-1000,-224,-224,-224,
-224,-224,-1000,-1000,-228,-229,-229,-1000,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,-309,-312,-1000,-1000,-1000,
-1000,-1000,-1000,-232,-235,-1000,-1000,-1000,-1000,-1000,
-258,-1000,-1000,-1000,-1000,-320,-227,-1000,-1000,-1000,
-1000,-231,-257,-326,-1000,-1000,-1000,-1000,-1000,-1000,
-327,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
-234,-117,-1000,-1000,-356,-1000,-1000,-356,-356,-356,
-356,-356,-356,-356,-356,-356,-356,-356,-356,-356,
-356,-356, -66, -66,-1000,-1000, -66,-1000,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000 };
short yypgo[]={

   0, 234, 235, 196,  47, 195, 193, 192, 191, 189,
 188, 187, 183, 186, 185, 184, 180, 179, 176, 171,
 168, 145, 144, 143,  35, 140,  39, 139, 136, 132,
 101,  91,  79,  78,  77,  57,  51,  42,  34,  30 };
short yyr1[]={

   0,   8,   9,   9,  10,  10,  10,  10,  10,  10,
  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,
  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,
  10,  10,  10,  10,  10,  11,  10,  13,  10,  14,
  10,  10,  15,  10,  10,  16,  10,  17,  10,  19,
  10,  21,  10,  23,  10,  25,  10,  10,  10,   6,
   7,  26,  26,  29,  29,  29,  27,  27,  27,  27,
  27,  27,  28,  28,  28,  28,  28,  28,  24,  30,
  30,  31,  31,  31,  31,  31,  31,  31,  31,  31,
  31,  31,  31,  31,  31,  31,  12,  32,  32,  33,
  22,  34,  34,  35,  20,  36,  36,  37,  18,  38,
  38,  39,   2,   2,   2,   2,   2,   2,   2,   2,
   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
   2,   2,   2,   2,   3,   5,   1,   4 };
short yyr2[]={

   0,   1,   0,   2,   1,   1,   1,   2,   2,   2,
   2,   2,   2,   2,   2,   1,   1,   1,   1,   1,
   1,   1,   2,   1,   2,   1,   1,   1,   1,   1,
   2,   2,   2,   2,   2,   0,   3,   0,   3,   0,
   3,   1,   0,   3,   1,   0,   3,   0,   4,   0,
   4,   0,   3,   0,   3,   0,   3,   2,   2,   6,
   6,   0,   2,   1,   1,   1,   1,   1,   1,   1,
   1,   1,   1,   1,   1,   1,   1,   1,   3,   0,
   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
   2,   2,   2,   2,   2,   2,   3,   0,   2,   1,
   3,   0,   2,   2,   3,   0,   2,   1,   3,   0,
   2,   2,   1,   1,   1,   1,   1,   1,   2,   1,
   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
   1,   1,   1,   1,   1,   1,   1,   1,   1,   2,
   2,   2,   2,   2,   1,   1,   1,   1 };
short yychk[]={

-1000,  -8,  -9, -10, 256, 320, 316, 323, 317, 322,
 315, 302, 304, 324, 326, 312, 348, 350, 349, 292,
 296, 297, 293, 314, 353, 309, 308, 310, 305,  -3,
  -1,  -5, 311, 306, 321, 318, 319, 260, 354, 325,
 351, 352, 263, 288, 261, 358, 262,  -1,  -1,  -1,
  -1,  -1,  -1,  -1,  -1,  -4, 313,  -4,  -1,  -2,
  -6, 271, 291, 270, 281, 266, 290, 277, 279, 287,
 280, 286, 265, 282, 298, 299, 283, 307, 284, 289,
 268, 273, 272, 269, 276, 278, 294, 295, 264, 267,
 274, 275, 355, 336,  -7, 336,  -2, -11, -13, -14,
 -15, -16,  -1,  -1, -21, -23, -25,  -2,  -2,  -1,
  -1,  -1,  -1,  -1,  -1, -26, -26, -12, 257, -12,
 -12, -12, -12, -17, -19, -22, 257, -24, 257, -24,
 335, -29, 327, 328, 329, 335, -32, -18, 257, -20,
 257, -34, -30, -27, 330, 331, 332, 333, 334, 303,
 -28, 330, 331, 332, 333, 334,  -1, 258, -33,  -1,
 -38, -36, 258, -35,  -1, 258, -31, 337, 356, 357,
 338, 339, 340, 341, 343, 344, 342, 345, 346, 347,
 300, 301, 335, 335, 258, -39,  -1, 258, -37,  -2,
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
  -1,  -1,  -1,  -1,  -1,  -1,  -2,  -2,  -2 };
short yydef[]={

   2,  -2,   1,   3,   4,   5,   6,   0,   0,   0,
   0,   0,   0,   0,   0,  15,  16,  17,  18,  19,
  20,  21,  23,   0,  25,  26,  27,  28,  29,   0,
   0,   0,  35,  37,  -2,  -2,  45,   0,   0,  51,
  53,  55,   0,   0, 144, 146, 145,   7,   8,   9,
  10,  11,  12,  13,  14,  22, 147,  24,  30,  31,
  33, 112, 113, 114, 115, 116, 117,   0, 119, 120,
 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
 131, 132, 133, 134, 135, 136, 137, 138,   0,   0,
   0,   0,   0,  61,  32,  61,  34,   0,   0,   0,
   0,   0,  47,  49,   0,   0,   0,  57,  58, 118,
 139, 140, 141, 142, 143,   0,   0,  36,  97,  38,
  40,  43,  46,   0,   0,  52, 101,  54,  79,  56,
   0,  62,  63,  64,  65,   0,   0,  48, 109,  50,
 105,   0,   0,   0,  66,  67,  68,  69,  70,  71,
   0,  72,  73,  74,  75,  76,  77,  96,  98,  99,
   0,   0, 100, 102,   0,  78,  80,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0, 108, 110,   0, 104, 106, 107,
 103,  81,  82,  83,  84,  85,  86,  87,  88,  89,
  90,  91,  92,  93,  94,  95,  59,  60, 111 };
#ifndef lint
static char yaccpar_sccsid[] = "@(#)yaccpar	4.1	(Berkeley)	2/11/83";
#endif

#
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
			
case 5:
{ if (FirstTime) ForceIcon = TRUE; } break;
case 6:
{ if (FirstTime) ReverseVideo = TRUE; } break;
case 7:
{ IconFont.name = yypvt[-0].ptr;
					  GetFont(&IconFont);
					} break;
case 8:
{ SizeFont.name = yypvt[-0].ptr;
					  GetFont(&SizeFont);
					} break;
case 9:
{ MenuFont.name = yypvt[-0].ptr;
					  GetFont(&MenuFont);
					} break;
case 10:
{ TitleBarFont.name = yypvt[-0].ptr;
					  GetFont(&TitleBarFont);
					} break;
case 11:
{ IconManagerFont.name=yypvt[-0].ptr;
					  GetFont(&IconManagerFont);
					} break;
case 12:
{ if (FirstTime) IconManagerGeometry=yypvt[-0].ptr;} break;
case 13:
{ if (FirstTime) GetUnknownIcon(yypvt[-0].ptr); } break;
case 14:
{ if (FirstTime)
					    IconDirectory = ExpandFilename(yypvt[-0].ptr);
					} break;
case 15:
{ if (FirstTime) WarpCursor = TRUE; } break;
case 16:
{ if (FirstTime) NoRaiseMove = TRUE; } break;
case 17:
{ if (FirstTime) NoRaiseResize = TRUE; } break;
case 18:
{ if (FirstTime) NoRaiseDeicon = TRUE; } break;
case 19:
{ if (FirstTime) DontMoveOff = TRUE; } break;
case 20:
{ if (FirstTime) BackingStore = FALSE; } break;
case 21:
{ if (FirstTime) SaveUnder = FALSE; } break;
case 22:
{ if (FirstTime)
					  {
						DoZoom = TRUE;
						ZoomCount = yypvt[-0].num;
					  }
					} break;
case 23:
{ if (FirstTime) DoZoom = TRUE; } break;
case 24:
{ if (FirstTime) BorderWidth = yypvt[-0].num; } break;
case 25:
{ if (FirstTime) TitleFocus = FALSE; } break;
case 26:
{ if (FirstTime) RandomPlacement=TRUE; } break;
case 27:
{ if (FirstTime) DecorateTransients =
					    TRUE; } break;
case 28:
{ if (FirstTime) IconifyByUnmapping =
					    TRUE; } break;
case 29:
{ if (FirstTime) ShowIconManager =
					    TRUE; } break;
case 30:
{ root = GetRoot(yypvt[-0].ptr);
					  Mouse[yypvt[-1].num][C_ROOT][0].func = F_MENU;
					  Mouse[yypvt[-1].num][C_ROOT][0].menu = root;
					} break;
case 31:
{ Mouse[yypvt[-1].num][C_ROOT][0].func = yypvt[-0].num;
					  if (yypvt[-0].num == F_MENU)
					  {
					    pull->prev = NULL;
					    Mouse[yypvt[-1].num][C_ROOT][0].menu = pull;
					  }
					  else
					  {
					    root = GetRoot(TWM_ROOT);
					    Mouse[yypvt[-1].num][C_ROOT][0].item = 
					    AddToMenu(root,"x",Action,0,yypvt[-0].num);
					  }
					  Action = "";
					  pull = NULL;
					} break;
case 32:
{ AddFuncKey(yypvt[-1].ptr, cont, mods,
						yypvt[-0].num, Name, Action);
					  Action = "";
					  pull = NULL;
					  cont = 0;
					  mods = 0;
					} break;
case 33:
{ Mouse[yypvt[-1].num][cont][mods].func = yypvt[-0].num;
					  if (yypvt[-0].num == F_MENU)
					  {
					    pull->prev = NULL;
					    Mouse[yypvt[-1].num][cont][mods].menu = pull;
					  }
					  else
					  {
					    root = GetRoot(TWM_ROOT);
					    Mouse[yypvt[-1].num][cont][mods].item = 
					    AddToMenu(root,"x",Action,0,yypvt[-0].num);
					  }
					  Action = "";
					  pull = NULL;
					  cont = 0;
					  mods = 0;
					} break;
case 34:
{ Mouse[yypvt[-1].num][C_TITLE][0].func = yypvt[-0].num;
					  Mouse[yypvt[-1].num][C_ICON][0].func = yypvt[-0].num;
					  if (yypvt[-0].num == F_MENU)
					  {
					    pull->prev = NULL;
					    Mouse[yypvt[-1].num][C_TITLE][0].menu = pull;
					    Mouse[yypvt[-1].num][C_ICON][0].menu = pull;
					  }
					  else
					  {
					    root = GetRoot(TWM_ROOT);
					    Mouse[yypvt[-1].num][C_TITLE][0].item = 
					    AddToMenu(root,"x",Action,0,yypvt[-0].num);
					    Mouse[yypvt[-1].num][C_ICON][0].item =
						Mouse[yypvt[-1].num][C_TITLE][0].item;
					  }
					  Action = "";
					  pull = NULL;
					} break;
case 35:
{ list = DONT_ICONIFY_BY_UNMAPPING;} break;
case 37:
{ list = ICONMGR_NOSHOW; } break;
case 39:
{ list = NO_HILITE; } break;
case 41:
{ if (FirstTime) Highlight = FALSE; } break;
case 42:
{ list = NO_TITLE; } break;
case 44:
{ if (FirstTime) NoTitlebar = TRUE; } break;
case 45:
{ list = AUTO_RAISE; } break;
case 47:
{ root = GetRoot(yypvt[-0].ptr); } break;
case 49:
{ root = GetRoot(yypvt[-0].ptr); } break;
case 51:
{ list = ICONS; } break;
case 53:
{ color = COLOR; } break;
case 55:
{ color = MONOCHROME; } break;
case 57:
{ DefaultFunction.func = yypvt[-0].num;
					  if (yypvt[-0].num == F_MENU)
					  {
					    pull->prev = NULL;
					    DefaultFunction.menu = pull;
					  }
					  else
					  {
					    root = GetRoot(TWM_ROOT);
					    DefaultFunction.item = 
					    AddToMenu(root,"x",Action,0,yypvt[-0].num);
					  }
					  Action = "";
					  pull = NULL;
					} break;
case 58:
{ WindowFunction.func = yypvt[-0].num;
					   root = GetRoot(TWM_ROOT);
					   WindowFunction.item = 
					   AddToMenu(root,"x",Action,0,yypvt[-0].num);
					   Action = "";
					   pull = NULL;
					} break;
case 59:
{ yyval.num = yypvt[-0].num; } break;
case 60:
{ yyval.num = yypvt[-0].num; } break;
case 63:
{ mods |= Mod1Mask; } break;
case 64:
{ mods |= ShiftMask; } break;
case 65:
{ mods |= ControlMask; } break;
case 66:
{ cont = C_WINDOW; } break;
case 67:
{ cont = C_TITLE; } break;
case 68:
{ cont = C_ICON; } break;
case 69:
{ cont = C_ROOT; } break;
case 70:
{ cont = C_FRAME; } break;
case 71:
{ cont = C_ICONMGR; } break;
case 72:
{ cont = C_WINDOW; } break;
case 73:
{ cont = C_TITLE; } break;
case 74:
{ cont = C_ICON; } break;
case 75:
{ cont = C_ROOT; } break;
case 76:
{ cont = C_FRAME; } break;
case 77:
{ Name = yypvt[-0].ptr; cont = C_NAME; } break;
case 81:
{ GetColor(color, &BorderColor, yypvt[-0].ptr); } break;
case 82:
{ GetColor(color,
						&BorderTileC.fore, yypvt[-0].ptr); } break;
case 83:
{ GetColor(color,
						&BorderTileC.back, yypvt[-0].ptr); } break;
case 84:
{ GetColor(color,
						&TitleC.fore, yypvt[-0].ptr); } break;
case 85:
{ GetColor(color,
						&TitleC.back, yypvt[-0].ptr); } break;
case 86:
{ GetColor(color,
						&MenuC.fore, yypvt[-0].ptr); } break;
case 87:
{ GetColor(color,
						&MenuC.back, yypvt[-0].ptr); } break;
case 88:
{ GetColor(color,
						    &MenuTitleC.fore, yypvt[-0].ptr); } break;
case 89:
{ GetColor(color,
						    &MenuTitleC.back, yypvt[-0].ptr); } break;
case 90:
{ GetColor(color,
						    &MenuShadowColor, yypvt[-0].ptr); } break;
case 91:
{ GetColor(color,
						&IconC.fore, yypvt[-0].ptr); } break;
case 92:
{ GetColor(color,
						&IconC.back, yypvt[-0].ptr); } break;
case 93:
{ GetColor(color,
						&IconBorderColor, yypvt[-0].ptr); } break;
case 94:
{ GetColor(color,
						&IconManagerC.fore, yypvt[-0].ptr); } break;
case 95:
{ GetColor(color,
						&IconManagerC.back, yypvt[-0].ptr); } break;
case 99:
{ if (FirstTime) AddToList(list, yypvt[-0].ptr, 0); } break;
case 103:
{   if (FirstTime)
					    { 
						Pixmap pm;
						
						pm = GetBitmap(yypvt[-0].ptr);
						if (pm != NULL)
						    AddToList(list, yypvt[-1].ptr, pm);
					    }
					} break;
case 107:
{ AddToMenu(root, "", Action, NULL, yypvt[-0].num);
					  Action = "";
					} break;
case 111:
{ AddToMenu(root, yypvt[-1].ptr, Action, pull, yypvt[-0].num);
					  Action = "";
					  pull = NULL;
					} break;
case 112:
{ yyval.num = F_NOP; } break;
case 113:
{ yyval.num = F_BEEP; } break;
case 114:
{ yyval.num = F_QUIT; } break;
case 115:
{ yyval.num = F_FOCUS; } break;
case 116:
{ yyval.num = F_REFRESH; } break;
case 117:
{ yyval.num = F_WINREFRESH; } break;
case 118:
{ Action = yypvt[-0].ptr; yyval.num = F_TWMRC; } break;
case 119:
{ yyval.num = F_MOVE; } break;
case 120:
{ yyval.num = F_FORCEMOVE; } break;
case 121:
{ yyval.num = F_ICONIFY; } break;
case 122:
{ yyval.num = F_DEICONIFY; } break;
case 123:
{ yyval.num = F_UNFOCUS; } break;
case 124:
{ yyval.num = F_RESIZE; } break;
case 125:
{ yyval.num = F_ZOOM; } break;
case 126:
{ yyval.num = F_FULLZOOM; } break;
case 127:
{ yyval.num = F_RAISE; } break;
case 128:
{ yyval.num = F_RAISELOWER; } break;
case 129:
{ yyval.num = F_LOWER; } break;
case 130:
{ yyval.num = F_DESTROY; } break;
case 131:
{ yyval.num = F_TWMRC; } break;
case 132:
{ yyval.num = F_VERSION; } break;
case 133:
{ yyval.num = F_TITLE; } break;
case 134:
{ yyval.num = F_CIRCLEUP; } break;
case 135:
{ yyval.num = F_CIRCLEDOWN; } break;
case 136:
{ yyval.num = F_CUTFILE; } break;
case 137:
{ yyval.num = F_SHOWLIST; } break;
case 138:
{ yyval.num = F_HIDELIST; } break;
case 139:
{ pull = GetRoot(yypvt[-0].ptr);
					  pull->prev = root;
					  yyval.num = F_MENU;
					} break;
case 140:
{ Action = yypvt[-0].ptr; yyval.num = F_FILE; } break;
case 141:
{ Action = yypvt[-0].ptr; yyval.num = F_EXEC; } break;
case 142:
{ Action = yypvt[-0].ptr; yyval.num = F_CUT; } break;
case 143:
{ Action = yypvt[-0].ptr; yyval.num = F_FUNCTION; } break;
case 144:
{ yyval.num = yypvt[-0].num;
					  if (yypvt[-0].num == 0)
						yyerror();

					  if (yypvt[-0].num > MAX_BUTTONS)
					  {
						yyval.num = 0;
						yyerror();
					  }
					} break;
case 145:
{ yyval.num = yypvt[-0].num;
					  if (yypvt[-0].num == 0)
						yyerror();

					  if (yypvt[-0].num > MAX_BUTTONS)
					  {
						yyval.num = 0;
						yyerror();
					  }
					} break;
case 146:
{ ptr = (char *)malloc(strlen(yypvt[-0].ptr)+1);
					  strcpy(ptr, yypvt[-0].ptr);
					  RemoveDQuote(ptr);
					  yyval.ptr = ptr;
					} break;
case 147:
{ yyval.num = yypvt[-0].num; } break; 
		}
		goto yystack;  /* stack new state and value */

	}
