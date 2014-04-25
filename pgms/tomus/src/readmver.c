#ifndef lint
static char yysccsid[] = "@(#)yaccpar	1.8 (Berkeley) 01/20/90";
#endif
#define YYBYACC 1
/* ----------------------------------------------------------------- 
FILE:	    readmver.c <- readmver.y <- readmver.l
DESCRIPTION:This file contains the grammar (BNF) for the TimberWolfSC
	    input file parser. The rules for lex are in readmver.l.
	    The grammar for yacc is in readmver.y.
	    The output of yacc (y.tab.c) is renamed to readmver.c
CONTENTS:   
	    readmver( fp )
		FILE *fp ;
	    yyerror(s)
		char    *s;
	    yywrap()
	
	    Note:readmver.c will also include the yacc parser.
DATE:	    Jan 15, 1990 
REVISIONS:  Added the keywords in the "parser.h" file 
----------------------------------------------------------------- */
#ifndef lint
static char SccsId[] = "@(#) readmver.y version 1.4 2/21/91" ;
#endif

#include <string.h>
#include <yalecad/message.h>
#include <yalecad/string.h>
#include "readmver.h"

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
extern int core_y1G,core_y2G,core_x1G,core_x2G;
extern char *cktNameG ;
static int line_countS ;
static char bufferS[LRECL] ;
typedef union {
    INT ival ;
    char *string ;
    double fval ;
} YYSTYPE;
#define INTEGER 257
#define STRING 258
#define FLOAT 259
#define ACT_ROW_HT 260
#define CORE 261
#define CHAN_SEP 262
#define GRID 263
#define MIN_LEN 264
#define TOT_ROW_LEN 265
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    2,    7,    8,    3,    9,   10,    4,    5,    6,
    6,    1,    1,    1,
};
short yylen[] = {                                         2,
    5,    2,    2,    2,    2,    2,    2,    5,    3,    1,
    2,    1,    1,    1,
};
short yydefred[] = {                                      0,
    0,    0,    0,    0,    3,    0,    0,    0,    0,    2,
    6,    0,    0,    0,    5,    4,    0,    0,    0,    7,
    0,    0,   13,   12,   14,   10,    0,    0,    9,   11,
    8,
};
short yydgoto[] = {                                       2,
   26,    3,    7,   13,   19,   27,    4,   10,    8,   15,
};
short yysindex[] = {                                   -262,
 -253,    0, -256, -255,    0, -250, -252, -254, -249,    0,
    0, -246, -251, -244,    0,    0, -243, -242, -257,    0,
 -241, -240,    0,    0,    0,    0, -257, -239,    0,    0,
    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   19,    0,    0,    0,
    0,
};
short yygindex[] = {                                      0,
   -7,    0,    0,    0,    0,    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 20
short yytable[] = {                                      23,
   24,   25,    1,    5,    9,    6,   11,   16,   12,   14,
   17,   18,   20,   21,   22,   28,   29,   31,    1,   30,
};
short yycheck[] = {                                     257,
  258,  259,  265,  257,  260,  262,  257,  257,  261,  264,
  257,  263,  257,  257,  257,  257,  257,  257,    0,   27,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 265
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"INTEGER","STRING","FLOAT",
"ACT_ROW_HT","CORE","CHAN_SEP","GRID","MIN_LEN","TOT_ROW_LEN",
};
char *yyrule[] = {
"$accept : start_file",
"start_file : row_parameters chan_parameters core grid misc",
"row_parameters : row_len row_height",
"row_len : TOT_ROW_LEN INTEGER",
"row_height : ACT_ROW_HT INTEGER",
"chan_parameters : chan_sep chan_min_len",
"chan_sep : CHAN_SEP INTEGER",
"chan_min_len : MIN_LEN INTEGER",
"core : CORE INTEGER INTEGER INTEGER INTEGER",
"grid : GRID INTEGER INTEGER",
"misc : string",
"misc : misc string",
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

#include "readmver_l.h"
/* add readmver_l.h for debug purposes */
/* ********************* #include "readmver_l.h" *******************/
/* ********************* #include "readmver_l.h" *******************/

readmver( fp )
FILE *fp ;
{ 
#ifdef YYDEBUG
    extern int yydebug ;
    yydebug = FALSE ;
#endif

    yyin = fp ;
    line_countS = 0 ;
    yyparse();  
} /* end readmvers */

yyerror(s)
char    *s;
{
    sprintf(YmsgG,"problem reading %s.mver\n", cktNameG ); 
    M( ERRMSG, "readmver", YmsgG ) ;
    sprintf(YmsgG, "  line %d near '%s' : %s\n" ,
	line_countS+1, yytext, s );
    M( MSG,"readmver", YmsgG ) ;
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
case 3:
{
		     /*total_row_length = $2; */
		    }
break;
case 4:
{
		     /*actual_row_height = $2; */
		     rowHeight = yyvsp[0].ival;
                    }
break;
case 6:
{
		     /*channel_separation = $2; */
		     rowSep = yyvsp[0].ival;
                    }
break;
case 7:
{
		     /*min_length = $2; */ 
		    }
break;
case 8:
{
		     core_x1G = yyvsp[-3].ival; 
		     core_x2G = yyvsp[-1].ival; 
		     core_y2G = yyvsp[-2].ival; 
		     core_y1G = yyvsp[0].ival; 
		    }
break;
case 9:
{
		    }
break;
case 12:
{ 
			yyval.string = yyvsp[0].string ;	
		    }
break;
case 13:
{
			/* convert integer to string */
			/* this allows integers to be used as strings */
			sprintf( bufferS,"%d", yyvsp[0].ival ) ;
			/* now clone string */
			yyval.string = Ystrclone( bufferS ) ;
		    }
break;
case 14:
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
