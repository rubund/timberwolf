/* ----------------------------------------------------------------- 
FILE:	    readmver.h
DESCRIPTION:This file redefines global variable of yacc and lex so
	    that we can have more than one parser in TSMC.
CONTENTS:   macro redefinitions for parser in readmver.
DATE:	    Feb 9 , 1990 
REVISIONS:  
----------------------------------------------------------------- */
/* *****************************************************************
   static char SccsId[] = "@(#) readmver.h version 4.4 9/14/89" ;
***************************************************************** */

#define yyact		MVER_yyact
#define yyback		MVER_yyback
#define yybgin		MVER_yybgin
#define yychar		MVER_yychar
#define yychk		MVER_yychk
#define yycrank		MVER_yycrank
#define yycnprs		MVER_yycnprs
#define yydebug		MVER_yydebug
#define yydef		MVER_yydef
#define yyerrflag	MVER_yyerrflag
#define yyerror	        MVER_yyerror
#define yyestate	MVER_yyestate
#define yyexca		MVER_yyexca
#define yyextra		MVER_yyextra
#define yyfnd		MVER_yyfnd
#define yyin		MVER_yyin
#define yyinput		MVER_yyinput
#define yyleng		MVER_yyleng
#define yylex		MVER_yylex
#define yylineno	MVER_yylineno
#define yylook		MVER_yylook
#define yylsp		MVER_yylsp
#define yylstate	MVER_yylstate
#define yylval		MVER_yylval
#define yymatch		MVER_yymatch
#define yymorfg		MVER_yymorfg
#define yynerrs		MVER_yynerrs
#define yyolsp		MVER_yyolsp
#define yyout		MVER_yyout
#define yyoutput	MVER_yyoutput
#define yypact		MVER_yypact
#define yyparse		MVER_yyparse
#define yypgo		MVER_yypgo
#define yyprevious	MVER_yyprevious
#define yyreds		MVER_yyreds
#define yyr1		MVER_yyr1
#define yyr2		MVER_yyr2
#define yysbuf		MVER_yysbuf
#define yysptr		MVER_yysptr
#define yysvec		MVER_yysvec
#define yytchar		MVER_yytchar
#define yytext		MVER_yytext
#define yytoks		MVER_yytoks
#define yytop		MVER_yytop
#define yyunput		MVER_yyunput
#define yyv		MVER_yyv
#define yyval		MVER_yyval
#define yyvstop		MVER_yyvstop
#define yywrap		MVER_yywrap
/* for byacc */
#define yyrule          MVER_yyrule
#define yyname          MVER_yyname
#define yytable         MVER_yytable
#define yycheck         MVER_yycheck
#define yydgoto         MVER_yydgoto
#define yydefred        MVER_yydefred
#define yygindex        MVER_yygindex
#define yyrindex        MVER_yyrindex
#define yysindex        MVER_yysindex
#define yylen           MVER_yylen
#define yylhs           MVER_yylhs
