#ifndef lint
static char yysccsid[] = "@(#)yaccpar	1.8 (Berkeley) 01/20/90";
#endif
#define YYBYACC 1
/* ----------------------------------------------------------------- 
FILE:	    readcell.c <- readcell.y <- readcell.l
DESCRIPTION:This file contains the grammar (BNF) for the TimberWolfSC
	    input file parser. The rules for lex are in readcell.l.
	    The grammar for yacc is in readcell.y.
	    The output of yacc (y.tab.c) is renamed to readcell.c
CONTENTS:   
	    readcell( fp )
		FILE *fp ;
	    yyerror(s)
		char    *s;
	    yywrap()
	
	    Note:readcell.c will also include the yacc parser.
DATE:	    Jan 15, 1990 
REVISIONS: Feb. 21st : added orient rule (for hardcells and pads for
		       new .smcel file from BILL 
----------------------------------------------------------------- */
#ifndef lint
static char SccsId[] = "@(#) readcell.y (Yale) version 1.4 2/21/91" ;
#endif

#include <string.h>
#include <yalecad/message.h>
#include <yalecad/string.h>
#include <yalecad/debug.h>
#include "standard.h"
#include "readcell.h"       

#define PARSER_VARS
#include "parser.h"

#undef REJECT 
#define YYDEBUG  1          /* condition compile for yacc debug */
/* #define LEXDEBUG 1  */   /* conditional compile for lex debug */
#ifdef LEXDEBUG
/* two bugs in Yale version of lex */
#define allprint(x)    fprintf( stdout, "%c\n", x )
#define sprint(x)      fprintf( stdout, "%s\n", x )
#endif
static int parse_flag ;
static int  xpos,ypos,line_countS ;
static char bufferS[LRECL] ;

static BOOL hardpad_contextS = FALSE ;
/* switch allow us to have FIXED, NONFIXED as reserved words
in different contexts */

static BOOL hardsoft_contextS = FALSE ;
/* switch allow us to have FIXED, NONFIXED as reserved words 
in different contexts */

static BOOL pad_contextS = FALSE ;
/* switch allow us to have B,L,T */

static BOOL initially_contextF = FALSE ;
/* switch allow us to have
LEFT,RIGHT */ 

typedef union {
    INT ival ;
    char *string ;
    double fval ;
} YYSTYPE;
#define INTEGER 257
#define STRING 258
#define FLOAT 259
#define APPROXIMATELY_FIXED 260
#define RIGIDFIXED 261
#define FIXED 262
#define NONFIXED 263
#define LEFT 264
#define RIGHT 265
#define BOTTOM 266
#define TOP 267
#define ASPLB 268
#define ASPUB 269
#define AT 270
#define BLOCK 271
#define CELL 272
#define CELLGROUP 273
#define CLASS 274
#define CORNERS 275
#define ENDPINGROUP 276
#define EQUIV 277
#define FROM 278
#define GROUP 279
#define HARDCELL 280
#define INITIALLY 281
#define INSTANCE 282
#define LAYER 283
#define LEGALBLKCLASS 284
#define LEGALPRTCLASS 285
#define NAME 286
#define NEIGHBORHOOD 287
#define NOMIRROR 288
#define NOPERMUTE 289
#define OF 290
#define ORIENT 291
#define ONLY 292
#define ORIENTATIONS 293
#define PAD 294
#define PADGROUP 295
#define PADSIDE 296
#define PERMUTE 297
#define PIN 298
#define PINGROUP 299
#define PORT 300
#define RESTRICT 301
#define SIDE 302
#define SIDESPACE 303
#define SIGNAL 304
#define STDCELL 305
#define SUPERGROUP 306
#define SWAPGROUP 307
#define UNEQUIV 308
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    0,    0,    6,    6,    9,    9,   11,   11,    7,
    7,   14,   14,   15,   15,   10,   10,   13,   13,   12,
   12,   29,   29,   31,   31,   32,   16,   16,   16,   16,
   17,   18,   18,   28,   19,   50,   50,   30,   30,   52,
   21,   21,   25,   25,   26,   20,   20,   20,   55,   56,
   56,   57,   57,   58,   59,   53,   53,   53,   53,   54,
   54,   22,   22,   43,   23,   60,   61,   62,   63,    2,
    3,   38,   41,   42,    5,   44,   44,   47,   49,   33,
   64,   65,   65,   66,   34,   36,   36,   35,   35,   67,
   67,   37,   37,   27,   27,   24,   24,   69,   69,   69,
   69,   70,   70,   70,   68,   68,   74,   75,   71,   71,
   72,   72,   76,   76,   73,   73,   77,   77,    8,    8,
   78,   78,   40,   40,   40,   39,   39,   46,   46,    4,
   45,   45,   79,   79,   48,   48,   51,   51,    1,    1,
    1,
};
short yylen[] = {                                         2,
    2,    2,    1,    1,    2,    1,    2,    1,    1,    1,
    2,    1,    2,    1,    2,    1,    2,    6,    8,    2,
    3,    1,    3,    5,    4,    2,    6,    5,    5,    4,
    4,    4,    3,    4,    3,   13,   14,    8,   14,    1,
    0,    8,    0,    2,    3,    0,    2,    3,    1,    1,
    2,    1,    2,    1,    1,    1,    1,    1,    1,    1,
    1,    0,    1,    8,    8,    1,    1,    1,    1,    1,
    1,    4,    5,    2,    1,    3,    3,    4,    4,    2,
    2,    1,    2,    2,    2,    0,    2,    3,    2,    1,
    2,    1,    2,    1,    2,    1,    2,    1,    2,    2,
    3,    1,    2,    2,    1,    2,    1,    1,    9,    7,
    1,    2,    7,    5,    1,    2,    7,    5,    1,    2,
    9,    7,    0,    3,    2,    0,    3,    0,    3,    1,
    1,    2,    2,    2,    1,    2,    1,    2,    1,    1,
    1,
};
short yydefred[] = {                                      0,
    0,    0,    0,    0,    0,    6,    8,    9,    0,    0,
  140,  139,  141,    0,    0,    0,    0,    1,    0,    0,
   12,    0,    0,  119,    0,    0,    0,    7,   16,    0,
    0,    0,    0,   40,    0,    0,    0,   22,    0,    0,
    0,   35,    0,    0,    0,  120,    0,    0,   13,   14,
    0,    0,    0,    0,    0,    0,   17,  135,    0,    0,
    0,   55,    0,   52,    0,    0,    0,    0,   81,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   82,   34,
    0,    0,    0,    0,   15,    0,    0,  131,    0,    0,
   75,   74,   66,    0,    0,    0,    0,  136,    0,    0,
    0,  137,    0,   48,   53,   59,   58,   56,   57,    0,
   44,   63,    0,    0,    0,   26,   23,   85,    0,    0,
    0,    0,    0,   84,   83,   72,    0,    0,   77,   76,
  133,  134,    0,    0,  132,   87,    0,    0,    0,    0,
    0,   79,   78,   32,    0,    0,  138,    0,    0,    0,
   49,    0,    0,    0,   90,    0,    0,    0,    0,   73,
    0,    0,   31,    0,    0,    0,    0,    0,   92,    0,
   67,    0,   70,    0,    0,    0,    0,   96,    0,    0,
   54,    0,   50,    0,    0,   91,    0,    0,    0,    0,
    0,  130,  129,  127,    0,  124,    0,   93,    0,    0,
  111,    0,    0,    0,   60,   61,    0,   97,    0,    0,
    0,  115,    0,   51,    0,    0,    0,  122,    0,    0,
    0,  112,   68,    0,    0,    0,    0,    0,  116,    0,
  107,    0,   94,    0,    0,    0,    0,    0,    0,    0,
    0,   71,    0,    0,    0,    0,    0,   95,    0,    0,
    0,   38,    0,  121,    0,    0,    0,   69,    0,    0,
    0,   42,    0,    0,    0,  108,  101,    0,    0,    0,
  114,    0,   64,    0,    0,  118,    0,    0,    0,  110,
    0,    0,    0,    0,    0,   65,    0,    0,  113,    0,
    0,  117,    0,  109,    0,    0,    0,   36,    0,   39,
   37,
};
short yydgoto[] = {                                       3,
  173,  174,  243,  193,   92,    4,   18,   19,    5,   27,
    6,    7,    8,   20,   48,   21,   50,   29,    9,   33,
   67,  113,  149,  177,   68,  115,  232,   10,   36,   37,
   38,   71,   39,   74,  121,   90,  168,   22,  138,  140,
   23,   54,   94,   51,   87,  134,   30,   59,   31,   61,
  103,   40,  110,  207,  152,  182,   63,  183,   64,  150,
  172,  224,  259,   41,   78,   79,  156,  169,  233,  178,
  170,  200,  211,  235,  267,  201,  212,   24,   88,
};
short yysindex[] = {                                   -172,
 -130, -130,    0, -260, -189,    0,    0,    0, -262, -180,
    0,    0,    0, -130, -227, -130, -200,    0, -182, -197,
    0, -137, -153,    0, -130, -130, -258,    0,    0, -130,
 -143, -130, -270,    0, -112, -136, -137,    0, -124, -252,
 -109,    0, -130, -192, -130,    0, -130, -146,    0,    0,
 -130, -140, -130, -111, -134, -131,    0,    0, -148, -141,
 -130,    0, -204,    0, -129, -130, -127, -122,    0, -130,
 -137, -136, -100, -241,  -99,  -98,  -94, -109,    0,    0,
 -130, -123, -139, -175,    0, -126, -229,    0,  -93, -135,
    0,    0,    0, -133,  -90, -130, -130,    0, -241, -106,
  -88,    0, -130,    0,    0,    0,    0,    0,    0,  -84,
    0,    0, -111,  -83, -105,    0,    0,    0, -116,  -82,
 -140,  -97,  -96,    0,    0,    0,  -79, -130,    0,    0,
    0,    0, -119, -133,    0,    0, -117, -133,  -80, -114,
  -85,    0,    0,    0, -130,  -92,    0,  -91, -114,  -69,
    0,  -68, -127,  -82,    0,  -66, -114, -130, -130,    0,
 -219, -130,    0, -130, -114,  -67,  -89, -114,    0,  -81,
    0,  -63,    0,  -59, -130, -125, -114,    0, -250,  -85,
    0,  -68,    0, -111,  -66,    0, -114,  -58,  -56,  -55,
  -54,    0,    0,    0, -114,    0, -130,    0,  -78,  -81,
    0,  -73,  -72,  -52,    0,    0,  -77,    0,  -75,  -81,
 -101,    0,  -48,    0, -157,  -62,  -61,    0,  -45,  -86,
 -130,    0,    0,  -43, -130,  -57,  -51, -130,    0,  -73,
    0, -157,    0, -250, -114, -130, -130,  -42, -130, -194,
  -44,    0,  -38, -130,  -35, -179,  -33,    0,  -81, -101,
 -196,    0,  -32,    0, -176,  -31,  -30,    0,  -29,  -49,
  -27,    0,  -26,  -25,  -44,    0,    0,  -41,  -24,  -23,
    0,  -22,    0, -130,  -40,    0,  -21,  -18, -130,    0,
  -17,  -16,  -14, -130,  -13,    0,  -12,  -11,    0,  -36,
  -10,    0,  -28,    0, -130,  -20, -130,    0, -130,    0,
    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,  248,    6,    0,    0,    0, -245,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  249,  251,
    0,    0,    0,    0,    0,    0,   21,    0,    0,    0,
    0,    0, -185,    0,    0,  171,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  252,    0,    0,
    0,  154,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, -239,    0,    0,    0,   -9,    0,    0,    0,
    0,  195,    0,    0,    0,    0,    0,  190,    0,    0,
    0,    0,    0,    0,    0,    0,    2,    0,    0,  204,
    0,    0,    0,   85,    0,    0,    0,    0,    0,    0,
    0,    0,   57,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, -242,    0,    0,    0,    0,    0,
   61,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    3,    0,    0,    0,   85,    0,   24,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   -9,    0,    0,    1,  156,    0,    0,    0,
    0,    0,    0,    0,   33,  112,    0,   41,    0,   14,
    0,    0,    0,    0,    0,    0,  200,    0,   76,    0,
    0, -168,    0,    0,   31,    0,  160,    0,    0,    0,
    0,    0,    0,    0,   51,    0,    0,    0,    0,   44,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   92,
  105,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  210,    0,  115,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  124,  147,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,
};
short yygindex[] = {                                      0,
  495, -149, -224,   89,    0,    0,    0,    0,    0,    0,
  254,    0,    0,    0,    0,  234,  208,  230,    0,    0,
  145,  108,   78,   28,    0,    0,    0,    0,  227,    0,
  194,    0,  244,  209,  168,  148,  -64,    0,    0,  -15,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   88,  212,  217,
   96,   42,   12,    0,    0,  201,  126, -118,   46, -177,
 -145, -174,   48,    0,    0, -193, -203,  265,  198,
};
#define YYTABLESIZE 794
short yytable[] = {                                     208,
   89,  128,  123,  179,  210,    4,  222,  229,  188,  189,
   65,  252,  253,  105,   25,  119,  222,   75,   46,  261,
    5,   41,   32,   30,   47,  204,  199,   11,   12,   13,
   88,  179,   28,   16,   76,   46,   66,  190,   46,   17,
   29,   47,   46,  106,   47,   41,  229,   26,   47,  198,
   27,  120,   11,   12,   13,  222,   33,  209,   43,  249,
   86,   46,  256,  191,   11,   12,   13,   47,  198,  234,
  298,  133,  300,  208,  301,  102,  198,  263,   41,  266,
  269,   34,    1,   25,  123,   45,  234,  104,  257,  179,
    2,  103,  187,   81,   35,   45,   16,   47,   43,    1,
  195,  167,   41,  264,  104,  179,  270,    2,   11,   12,
   13,  125,   45,  129,   98,  100,   26,   17,  163,   45,
  101,  130,  165,   99,  283,   73,   11,   12,   13,  287,
  106,  107,  108,  109,  291,  131,  132,   35,  205,  206,
  167,  231,   53,   60,   69,   70,  100,   77,   47,   73,
   89,   96,   93,   86,   97,   25,  118,  122,  123,   24,
  112,  114,  124,  136,  128,  137,  141,  127,  146,  139,
   20,  145,  148,  151,  155,   65,  154,  160,  166,  171,
  158,  159,  162,  167,  164,  175,  176,  180,  181,   80,
  186,  196,  223,  202,   21,  199,  197,  203,  216,   18,
  217,  218,  219,  126,  226,  225,  209,  221,  230,   19,
  228,  238,  227,  241,  254,  236,  237,  239,  260,  245,
  244,  262,  258,  265,  268,  271,  272,  273,  274,  275,
  276,  277,  280,  281,  282,  285,  279,  284,  286,  288,
  289,  295,  290,  292,  293,  294,  296,    3,    2,  297,
   10,   11,  194,   49,   62,   85,   57,  299,   28,  153,
  184,  215,  251,   72,  117,   52,  144,   99,  157,  214,
   95,  247,   89,   89,  105,  213,  278,  248,  125,  185,
   89,  250,   89,   46,  135,  105,  105,    0,    0,    0,
    0,   89,    0,  105,   89,  105,  128,  123,   89,    4,
   89,    0,   88,   88,  128,    4,   89,  105,  105,    0,
   88,  105,   88,  105,    5,  106,  106,   30,   30,  105,
    5,   88,    0,  106,   88,  106,   28,   28,   88,   33,
   88,    0,   86,   86,   29,   29,   88,  106,  106,    0,
   86,  106,   86,  106,   27,   27,    0,  102,  102,  106,
   33,  102,    0,    0,   86,  102,   33,    0,   86,    0,
   86,    0,   33,  103,  103,    0,   86,  103,    0,  102,
    0,  103,    0,  102,    0,  102,  104,  104,  123,  123,
  104,  102,  123,    0,  104,  103,   98,   98,    0,  103,
    0,  103,    0,    0,   98,   99,   99,  103,  104,    0,
    0,    0,  104,   99,  104,  125,  125,    0,   98,  125,
  104,    0,   98,   98,   98,    0,    0,   99,  100,  100,
   98,   99,   99,   99,    0,    0,  100,   25,   25,   99,
    0,   24,   24,    0,    0,   25,    0,   25,    0,   24,
  100,   24,   20,   20,  100,  100,  100,   86,   86,   25,
   20,   86,  100,   24,   86,   25,   86,    0,    0,   24,
    0,   25,    0,   80,   20,   24,   21,   21,    0,    0,
   20,   18,   18,    0,   21,    0,   20,    0,    0,   18,
   80,   19,   19,   80,   80,    0,    0,   80,   21,   19,
   80,    0,   80,   18,   21,   14,   15,  126,  126,   18,
   21,  126,    0,   19,    0,   18,  126,    0,   42,   19,
   44,    0,    0,    0,    0,   19,    0,    0,    0,   55,
   56,    0,    0,    0,   58,    0,   62,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   80,   82,   83,
    0,   84,    0,    0,    0,   86,    0,   91,    0,    0,
    0,    0,    0,   98,    0,  102,    0,   62,    0,    0,
  111,    0,    0,    0,  116,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  126,    0,    0,    0,    0,
    0,   86,    0,    0,    0,    0,    0,    0,    0,    0,
  142,  143,    0,    0,    0,    0,    0,  147,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  161,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  192,    0,  192,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  220,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  240,    0,    0,    0,  242,
    0,    0,  246,    0,    0,    0,    0,    0,    0,    0,
  242,  242,    0,  255,    0,    0,    0,    0,  242,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  242,
    0,  242,    0,  242,
};
short yycheck[] = {                                     177,
    0,    0,    0,  149,  179,    0,  200,  211,  158,  159,
  281,  236,  237,    0,  273,  257,  210,  270,  264,  244,
    0,  264,  285,    0,  264,  175,  277,  257,  258,  259,
    0,  177,    0,  294,  287,  281,  307,  257,  284,  300,
    0,  281,  288,    0,  284,  288,  250,  306,  288,  168,
    0,  293,  257,  258,  259,  249,    0,  308,  286,  234,
    0,  307,  257,  283,  257,  258,  259,  307,  187,  215,
  295,  301,  297,  251,  299,    0,  195,  257,  264,  276,
  257,  262,  272,  273,    0,  286,  232,  292,  283,  235,
  280,    0,  157,  286,  275,  264,  294,  295,  284,  272,
  165,  298,  288,  283,    0,  251,  283,  280,  257,  258,
  259,    0,  281,  289,    0,  257,  306,  300,  134,  288,
  262,  297,  138,    0,  274,  274,  257,  258,  259,  279,
  260,  261,  262,  263,  284,  262,  263,  275,  264,  265,
  298,  299,  296,  287,  257,  282,    0,  257,  295,  274,
  291,  286,  264,    0,  286,    0,  257,  257,  257,    0,
  288,  284,  257,  257,  304,  301,  257,  291,  257,  303,
    0,  278,  257,  257,  257,  281,  293,  257,  259,  265,
  278,  278,  302,  298,  302,  278,  278,  257,  257,    0,
  257,  259,  266,  257,    0,  277,  286,  257,  257,    0,
  257,  257,  257,    0,  257,  278,  308,  286,  257,    0,
  286,  257,  290,  257,  257,  278,  278,  304,  257,  271,
  278,  257,  267,  257,  257,  257,  257,  257,  278,  257,
  257,  257,  257,  257,  257,  257,  278,  278,  257,  257,
  257,  278,  257,  257,  257,  257,  257,    0,    0,  278,
    0,    0,  164,   20,  264,   48,   27,  278,    5,  115,
  153,  184,  235,   37,   71,   22,   99,   59,  121,  182,
   54,  230,  272,  273,   63,  180,  265,  232,   78,  154,
  280,  234,  282,   19,   87,  272,  273,   -1,   -1,   -1,
   -1,  291,   -1,  280,  294,  282,  295,  295,  298,  294,
  300,   -1,  272,  273,  303,  300,  306,  294,  295,   -1,
  280,  298,  282,  300,  294,  272,  273,  294,  295,  306,
  300,  291,   -1,  280,  294,  282,  294,  295,  298,  273,
  300,   -1,  272,  273,  294,  295,  306,  294,  295,   -1,
  280,  298,  282,  300,  294,  295,   -1,  272,  273,  306,
  294,  276,   -1,   -1,  294,  280,  300,   -1,  298,   -1,
  300,   -1,  306,  272,  273,   -1,  306,  276,   -1,  294,
   -1,  280,   -1,  298,   -1,  300,  272,  273,  294,  295,
  276,  306,  298,   -1,  280,  294,  272,  273,   -1,  298,
   -1,  300,   -1,   -1,  280,  272,  273,  306,  294,   -1,
   -1,   -1,  298,  280,  300,  294,  295,   -1,  294,  298,
  306,   -1,  298,  299,  300,   -1,   -1,  294,  272,  273,
  306,  298,  299,  300,   -1,   -1,  280,  272,  273,  306,
   -1,  272,  273,   -1,   -1,  280,   -1,  282,   -1,  280,
  294,  282,  272,  273,  298,  299,  300,  294,  295,  294,
  280,  298,  306,  294,  301,  300,  303,   -1,   -1,  300,
   -1,  306,   -1,  274,  294,  306,  272,  273,   -1,   -1,
  300,  272,  273,   -1,  280,   -1,  306,   -1,   -1,  280,
  291,  272,  273,  294,  295,   -1,   -1,  298,  294,  280,
  301,   -1,  303,  294,  300,    1,    2,  294,  295,  300,
  306,  298,   -1,  294,   -1,  306,  303,   -1,   14,  300,
   16,   -1,   -1,   -1,   -1,  306,   -1,   -1,   -1,   25,
   26,   -1,   -1,   -1,   30,   -1,   32,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   43,   44,   45,
   -1,   47,   -1,   -1,   -1,   51,   -1,   53,   -1,   -1,
   -1,   -1,   -1,   59,   -1,   61,   -1,   63,   -1,   -1,
   66,   -1,   -1,   -1,   70,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   81,   -1,   -1,   -1,   -1,
   -1,   87,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   96,   97,   -1,   -1,   -1,   -1,   -1,  103,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  128,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  162,   -1,  164,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  197,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  221,   -1,   -1,   -1,  225,
   -1,   -1,  228,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  236,  237,   -1,  239,   -1,   -1,   -1,   -1,  244,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  295,
   -1,  297,   -1,  299,
};
#define YYFINAL 3
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 308
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"INTEGER","STRING","FLOAT",
"APPROXIMATELY_FIXED","RIGIDFIXED","FIXED","NONFIXED","LEFT","RIGHT","BOTTOM",
"TOP","ASPLB","ASPUB","AT","BLOCK","CELL","CELLGROUP","CLASS","CORNERS",
"ENDPINGROUP","EQUIV","FROM","GROUP","HARDCELL","INITIALLY","INSTANCE","LAYER",
"LEGALBLKCLASS","LEGALPRTCLASS","NAME","NEIGHBORHOOD","NOMIRROR","NOPERMUTE",
"OF","ORIENT","ONLY","ORIENTATIONS","PAD","PADGROUP","PADSIDE","PERMUTE","PIN",
"PINGROUP","PORT","RESTRICT","SIDE","SIDESPACE","SIGNAL","STDCELL","SUPERGROUP",
"SWAPGROUP","UNEQUIV",
};
char *yyrule[] = {
"$accept : start_file",
"start_file : core pads",
"start_file : core ports",
"start_file : core",
"core : corecells",
"core : corecells cellgroups",
"corecells : coretype",
"corecells : corecells coretype",
"coretype : hardcell",
"coretype : stdcell",
"pads : padcells",
"pads : padcells padgroups",
"padcells : padcell",
"padcells : padcells padcell",
"padgroups : padgroup",
"padgroups : padgroups padgroup",
"cellgroups : cellgroup",
"cellgroups : cellgroups cellgroup",
"stdcell : cellname legal_part_classes std_fixed mirror bbox stdpins",
"stdcell : cellname legal_part_classes swap_group legal_block_classes std_fixed mirror bbox stdgrppins",
"hardcell : hardcellname custom_instance_list",
"hardcell : hardcellname fixed custom_instance_list",
"custom_instance_list : custom_instance",
"custom_instance_list : custom_instance_list instance custom_instance",
"custom_instance : corners class orient actual_orient hardpins",
"custom_instance : corners class orient actual_orient",
"instance : INSTANCE string",
"padcell : padname corners actual_orient restriction_pad sidespace hardpins",
"padcell : padname corners actual_orient restriction_pad sidespace",
"padcell : padname_std padside bbox_pins sidespace hardpins",
"padcell : padname_std padside bbox_pins sidespace",
"padgroup : padgroupname padgrouplist restriction_pdgrp sidespace",
"cellgroup : supergroupname supergrouplist class orient",
"cellgroup : cellgroupname neighborhood cellgrouplist",
"hardcellname : HARDCELL string NAME string",
"cellname : CELL string string",
"neighborhood : NEIGHBORHOOD INTEGER FROM xloc INTEGER FROM yloc INTEGER FROM xloc INTEGER FROM yloc",
"neighborhood : NEIGHBORHOOD FIXED INTEGER FROM xloc INTEGER FROM yloc INTEGER FROM xloc INTEGER FROM yloc",
"fixed : fixedcontext AT INTEGER FROM xloc INTEGER FROM yloc",
"fixed : fixedcontext NEIGHBORHOOD INTEGER FROM xloc INTEGER FROM yloc INTEGER FROM xloc INTEGER FROM yloc",
"fixedcontext : FIXED",
"std_fixed :",
"std_fixed : INITIALLY fixed_type INTEGER FROM fixed_loc OF BLOCK INTEGER",
"swap_group :",
"swap_group : SWAPGROUP string",
"legal_block_classes : LEGALBLKCLASS num_block_classes block_classes",
"legal_part_classes :",
"legal_part_classes : LEGALPRTCLASS part_classes",
"legal_part_classes : LEGALPRTCLASS part_classes ONLY",
"num_block_classes : INTEGER",
"block_classes : block_class",
"block_classes : block_classes block_class",
"part_classes : part_class",
"part_classes : part_classes part_class",
"block_class : INTEGER",
"part_class : string",
"fixed_type : FIXED",
"fixed_type : NONFIXED",
"fixed_type : RIGIDFIXED",
"fixed_type : APPROXIMATELY_FIXED",
"fixed_loc : LEFT",
"fixed_loc : RIGHT",
"mirror :",
"mirror : NOMIRROR",
"bbox_pins : left INTEGER right INTEGER bottom INTEGER top INTEGER",
"bbox : left INTEGER right INTEGER bottom INTEGER top INTEGER",
"left : LEFT",
"right : RIGHT",
"bottom : BOTTOM",
"top : TOP",
"xloc : string",
"yloc : string",
"padname : PAD string NAME string",
"padname_std : PAD string string ORIENT INTEGER",
"padside : PADSIDE pad_pos",
"pad_pos : string",
"padgroupname : PADGROUP string PERMUTE",
"padgroupname : PADGROUP string NOPERMUTE",
"supergroupname : SUPERGROUP string NAME string",
"cellgroupname : CELLGROUP string NAME string",
"corners : num_corners cornerpts",
"num_corners : CORNERS INTEGER",
"cornerpts : cornerpt",
"cornerpts : cornerpts cornerpt",
"cornerpt : INTEGER INTEGER",
"class : CLASS INTEGER",
"actual_orient :",
"actual_orient : ORIENT INTEGER",
"orient : INTEGER ORIENTATIONS orientlist",
"orient : ORIENTATIONS orientlist",
"orientlist : INTEGER",
"orientlist : orientlist INTEGER",
"hardpins : pintype",
"hardpins : hardpins pintype",
"stdgrppins : std_grppintype",
"stdgrppins : stdgrppins std_grppintype",
"stdpins : std_pintype",
"stdpins : stdpins std_pintype",
"std_grppintype : pinrecord",
"std_grppintype : pinrecord equiv_list",
"std_grppintype : pinrecord unequiv_list",
"std_grppintype : pingroup stdpins endpingroup",
"std_pintype : pinrecord",
"std_pintype : pinrecord equiv_list",
"std_pintype : pinrecord unequiv_list",
"pintype : pinrecord",
"pintype : pinrecord equiv_list",
"pingroup : PINGROUP",
"endpingroup : ENDPINGROUP",
"pinrecord : PIN NAME string SIGNAL string LAYER INTEGER INTEGER INTEGER",
"pinrecord : PIN NAME string SIGNAL string INTEGER INTEGER",
"equiv_list : equiv",
"equiv_list : equiv_list equiv",
"equiv : EQUIV NAME string LAYER INTEGER INTEGER INTEGER",
"equiv : EQUIV NAME string INTEGER INTEGER",
"unequiv_list : unequiv",
"unequiv_list : unequiv_list unequiv",
"unequiv : UNEQUIV NAME string LAYER INTEGER INTEGER INTEGER",
"unequiv : UNEQUIV NAME string INTEGER INTEGER",
"ports : port",
"ports : ports port",
"port : PORT NAME string SIGNAL string LAYER INTEGER INTEGER INTEGER",
"port : PORT NAME string SIGNAL string INTEGER INTEGER",
"sidespace :",
"sidespace : SIDESPACE FLOAT FLOAT",
"sidespace : SIDESPACE FLOAT",
"restriction_pad :",
"restriction_pad : RESTRICT SIDE sideplace",
"restriction_pdgrp :",
"restriction_pdgrp : RESTRICT SIDE sideplace",
"sideplace : string",
"padgrouplist : padset",
"padgrouplist : padgrouplist padset",
"padset : string FIXED",
"padset : string NONFIXED",
"supergrouplist : string",
"supergrouplist : supergrouplist string",
"cellgrouplist : string",
"cellgrouplist : cellgrouplist string",
"string : STRING",
"string : INTEGER",
"string : FLOAT",
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
int yycnprs = 0;
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

#include "readcell_l.h"
/* add readcell_l.h for debug purposes */
/* ********************* #include "readcell_l.h" *******************/
/* ********************* #include "readcell_l.h" *******************/

readcell( fp )
FILE *fp ;
{ 
#ifdef YYDEBUG
    extern int yydebug ;
    yydebug = FALSE ;
#endif

    yyin = fp ;
    line_countS = 0 ;
    /*  first parse input file using yacc */
    initialise_parser();
    yyparse();  
    fixup_configure();
} /* end readcell */

yyerror(s)
char    *s;
{
    sprintf(YmsgG,"problem reading %s.pcel:\n", cktNameG ); 
    M( ERRMSG, "readcell", YmsgG ) ;
    sprintf(YmsgG, "  line %d near '%s' : %s\n" ,
	line_countS+1, yytext, s );
    M( ERRMSG,"readcell", YmsgG ) ;
    YexitPgm(PGMFAIL);
} /* end yyerror */

yywrap()
{
    return(1);
}                      
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
            sprintf( err_msg, "Found %s.\nExpected ",
                yyname[yychar] ) ;
            two_or_more = 0 ;
            if( test_state = yysindex[yystate] ){
                for( i = 1; i <= YYMAXTOKEN; i++ ){
                    expect = test_state + i ;
                if((expect <= YYTABLESIZE) &&
                   (yycheck[expect] == i) &&
                   yyname[i]){
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
                for( i = 1; i <= YYMAXTOKEN; i++ ){
                    expect = test_state + i ;
                if((expect <= YYTABLESIZE) &&
                   (yycheck[expect] == i) &&
                   yyname[i]){
                        if( two_or_more ){
                            strcat( err_msg, " | " ) ;
                        } else {
                            two_or_more = 1 ;
                        }
                        strcat( err_msg, yyname[i] ) ;
                     }
                 }
             }
             yyerror( err_msg ) ;
             if (yycnprs) {
                 yychar = (-1);
                 if (yyerrflag > 0)  --yyerrflag;
                 goto yyloop;
             }
        } else {
            sprintf( err_msg, "Found unknown token.\nExpected ");
            two_or_more = 0 ;
            if( test_state = yysindex[yystate] ){
                for( i = 1; i <= YYMAXTOKEN; i++ ){
                    expect = test_state + i ;
                if((expect <= YYTABLESIZE) &&
                   (yycheck[expect] == i) &&
                   yyname[i]){
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
                for( i = 1; i <= YYMAXTOKEN; i++ ){
                    expect = test_state + i ;
                if((expect <= YYTABLESIZE) &&
                   (yycheck[expect] == i) &&
                   yyname[i]){
                        if( two_or_more ){
                            strcat( err_msg, " | " ) ;
                        } else {
                            two_or_more = 1 ;
                        }
                        strcat( err_msg, yyname[i] ) ;
                     }
                 }
             }
             yyerror( err_msg ) ;
             if (yycnprs) {
                 yychar = (-1);
                 if (yyerrflag > 0)  --yyerrflag;
                 goto yyloop;
             }
        }
     }
#else
     yyerror("syntax error");
     if (yycnprs) {
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
     }
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
case 26:
{
			Ysafe_free( yyvsp[0].string ) ;
		    }
break;
case 34:
{
			addCell(yyvsp[0].string,HARDCELLTYPE);
		    }
break;
case 35:
{
			addCell(yyvsp[0].string,STDCELLTYPE);
		    }
break;
case 36:
{
			/* TRUE for L,B etc. in pads */
			pad_contextS = FALSE ;
			
		    }
break;
case 37:
{
			/* TRUE for xloc L,B etc. in pads */
		        pad_contextS = FALSE ;
		    }
break;
case 38:
{
			/* TRUE for xloc L,B etc. in pads */
			pad_contextS = FALSE ;
		    }
break;
case 39:
{
			/* TRUE for xloc L,B etc. in pads */
			pad_contextS = FALSE ;
		    }
break;
case 40:
{
			/* fixed locations same as pad context */
		    }
break;
case 42:
{
		    }
break;
case 44:
{
			Ysafe_free( yyvsp[0].string );
		    }
break;
case 48:
{
			add_mono_cells();
                      }
break;
case 55:
{
			add_legal_parts(yyvsp[0].string);
                    }
break;
case 56:
{
                     }
break;
case 57:
{
                     }
break;
case 58:
{
                     }
break;
case 59:
{
                     }
break;
case 60:
{
		    }
break;
case 61:
{
		    }
break;
case 64:
{
		     initially_contextF = FALSE;
		     add_positions_and_celllen(yyvsp[-6].ival,yyvsp[-4].ival,yyvsp[-2].ival,yyvsp[0].ival); 
		    }
break;
case 65:
{
		     initially_contextF = FALSE;
		     add_positions_and_celllen(yyvsp[-6].ival,yyvsp[-4].ival,yyvsp[-2].ival,yyvsp[0].ival);
		    }
break;
case 66:
{
		    }
break;
case 67:
{
		    }
break;
case 68:
{
		    }
break;
case 69:
{
		    }
break;
case 70:
{
			Ysafe_free( yyvsp[0].string ) ;
                    }
break;
case 71:
{
			Ysafe_free( yyvsp[0].string ) ;
                    }
break;
case 72:
{ 
	                pad_contextS = TRUE ;
		     	addCell(yyvsp[0].string,PADTYPE);
		    }
break;
case 73:
{
			Ysafe_free( yyvsp[-2].string ) ;
		    }
break;
case 74:
{
		      add_padside(yyvsp[0].string);
		    }
break;
case 75:
{
			yyval.string = yyvsp[0].string ;
		    }
break;
case 76:
{
			Ysafe_free( yyvsp[-1].string ) ;
		    }
break;
case 77:
{
			Ysafe_free( yyvsp[-1].string ) ;
		    }
break;
case 78:
{
			Ysafe_free( yyvsp[0].string ) ;
		    }
break;
case 79:
{
			/* fixed locations same as pad context */
			Ysafe_free( yyvsp[0].string ) ;
		    }
break;
case 81:
{
		     hard_positions(yyvsp[0].ival,pad_contextS);
		    }
break;
case 84:
{
		       add_corners(yyvsp[-1].ival,yyvsp[0].ival);
                    }
break;
case 87:
{
		      add_orient(yyvsp[0].ival);
                    }
break;
case 109:
{
			add_pin(yyvsp[-6].string,yyvsp[-4].string,yyvsp[-2].ival,yyvsp[-1].ival,yyvsp[0].ival);
			xpos = yyvsp[-1].ival;
			ypos = yyvsp[0].ival;
		    }
break;
case 110:
{
			add_pin(yyvsp[-4].string,yyvsp[-2].string,7,yyvsp[-1].ival,yyvsp[0].ival);
			xpos = yyvsp[-1].ival;
			ypos = yyvsp[0].ival;
		    }
break;
case 113:
{
			Ysafe_free(yyvsp[-4].string);
		    }
break;
case 114:
{
			Ysafe_free(yyvsp[-2].string);
		    }
break;
case 117:
{
			Ysafe_free(yyvsp[-4].string);
		    }
break;
case 118:
{
			Ysafe_free(yyvsp[-2].string);
		    }
break;
case 121:
{
			Ysafe_free(yyvsp[-6].string);
			Ysafe_free(yyvsp[-4].string);
		    }
break;
case 122:
{
			Ysafe_free(yyvsp[-4].string);
			Ysafe_free(yyvsp[-2].string);
		    }
break;
case 126:
{
			pad_contextS = FALSE ;
		    }
break;
case 127:
{
			pad_contextS = FALSE ;
		        add_padside(yyvsp[0].string);
		    }
break;
case 128:
{
			pad_contextS = FALSE ;
		    }
break;
case 129:
{
			pad_contextS = FALSE ;
		    }
break;
case 130:
{
		     yyval.string = yyvsp[0].string;
                    }
break;
case 137:
{
			Ysafe_free( yyvsp[0].string ) ;
		    }
break;
case 138:
{
			Ysafe_free( yyvsp[0].string ) ;
		    }
break;
case 139:
{ 
			yyval.string = yyvsp[0].string ;	
		    }
break;
case 140:
{
			/* convert integer to string */
			/* this allows integers to be used as strings */
			sprintf( bufferS,"%d", yyvsp[0].ival ) ;
			/* now clone string */
			yyval.string = Ystrclone( bufferS ) ;
		    }
break;
case 141:
{
			/* convert float to string */
			/* this allows floats to be used as strings */
			sprintf( bufferS,"%f", yyvsp[0].fval ) ;
			/* now clone string */
			yyval.string = Ystrclone( bufferS ) ;
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
