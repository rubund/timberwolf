/* ----------------------------------------------------------------- 
FILE:	    readcell.h
DESCRIPTION:This file redefines global variable of yacc and lex so
	    that we can have more than one parser in TSMC.
CONTENTS:   macro redefinitions for parser in readcells.
DATE:	    Feb 9 , 1990 
REVISIONS:  
----------------------------------------------------------------- */
/* *****************************************************************
static char SccsId[] = "@(#) readcell.h version 1.3 3/4/91" ;
***************************************************************** */

#define yyact		CELL_yyact
#define yyback		CELL_yyback
#define yybgin		CELL_yybgin
#define yychar		CELL_yychar
#define yychk		CELL_yychk
#define yycrank		CELL_yycrank
#define yydebug		CELL_yydebug
#define yydef		CELL_yydef
#define yyerrflag	CELL_yyerrflag
#define yyerror	        CELL_yyerror
#define yyestate	CELL_yyestate
#define yyexca		CELL_yyexca
#define yyextra		CELL_yyextra
#define yyfnd		CELL_yyfnd
#define yyin		CELL_yyin
#define yyinput		CELL_yyinput
#define yyleng		CELL_yyleng
#define yylex		CELL_yylex
#define yylineno	CELL_yylineno
#define yylook		CELL_yylook
#define yylsp		CELL_yylsp
#define yylstate	CELL_yylstate
#define yylval		CELL_yylval
#define yymatch		CELL_yymatch
#define yymorfg		CELL_yymorfg
#define yynerrs		CELL_yynerrs
#define yyolsp		CELL_yyolsp
#define yyout		CELL_yyout
#define yyoutput	CELL_yyoutput
#define yypact		CELL_yypact
#define yyparse		CELL_yyparse
#define yypgo		CELL_yypgo
#define yyprevious	CELL_yyprevious
#define yyreds		CELL_yyreds
#define yyr1		CELL_yyr1
#define yyr2		CELL_yyr2
#define yysbuf		CELL_yysbuf
#define yysptr		CELL_yysptr
#define yysvec		CELL_yysvec
#define yytchar		CELL_yytchar
#define yytext		CELL_yytext
#define yytoks		CELL_yytoks
#define yytop		CELL_yytop
#define yyunput		CELL_yyunput
#define yyv		CELL_yyv
#define yyval		CELL_yyval
#define yyvstop		CELL_yyvstop
#define yywrap		CELL_yywrap
/* for byacc */
#define yyrule          CELL_yyrule
#define yyname          CELL_yyname
#define yytable         CELL_yytable
#define yycheck         CELL_yycheck
#define yydgoto         CELL_yydgoto
#define yydefred        CELL_yydefred
#define yygindex        CELL_yygindex
#define yyrindex        CELL_yyrindex
#define yysindex        CELL_yysindex
#define yylen           CELL_yylen
#define yylhs           CELL_yylhs
