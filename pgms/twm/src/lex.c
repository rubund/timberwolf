# include "stdio.h"
# define U(x) ((x)&0377)
# define NLSTATE yyprevious=YYNEWLINE
# define BEGIN yybgin = yysvec + 1 +
# define INITIAL 0
# define YYLERR yysvec
# define YYSTATE (yyestate-yysvec-1)
# define YYOPTIM 1
# define YYLMAX 200
# define output(c) putc(c,yyout)
# define input() (((yytchar=yysptr>yysbuf?U(*--yysptr):getc(yyin))==10?(yylineno++,yytchar):yytchar)==EOF?0:yytchar)
# define unput(c) {yytchar= (c);if(yytchar=='\n')yylineno--;*yysptr++=yytchar;}
# define yymore() (yymorfg=1)
# define ECHO fprintf(yyout, "%s",yytext)
# define REJECT { nstr = yyreject(); goto yyfussy;}
int yyleng; extern char yytext[];
int yymorfg;
extern char *yysptr, yysbuf[];
int yytchar;
FILE *yyin ={stdin}, *yyout ={stdout};
extern int yylineno;
struct yysvf { 
	struct yywork *yystoff;
	struct yysvf *yyother;
	int *yystops;};
struct yysvf *yyestate;
extern struct yysvf yysvec[], *yybgin;
/*****************************************************************************/
/**       Copyright 1988 by Evans & Sutherland Computer Corporation,        **/
/**                          Salt Lake City, Utah                           **/
/**                                                                         **/
/**                           All Rights Reserved                           **/
/**                                                                         **/
/**    Permission to use, copy, modify, and distribute this software and    **/
/**    its documentation  for  any  purpose  and  without  fee is hereby    **/
/**    granted, provided that the above copyright notice appear  in  all    **/
/**    copies and that both  that  copyright  notice  and  this  permis-    **/
/**    sion  notice appear in supporting  documentation,  and  that  the    **/
/**    name  of Evans & Sutherland  not be used in advertising or publi-    **/
/**    city pertaining to distribution  of the software without  specif-    **/
/**    ic, written prior permission.                                        **/
/**                                                                         **/
/**    EVANS  & SUTHERLAND  DISCLAIMS  ALL  WARRANTIES  WITH  REGARD  TO    **/
/**    THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILI-    **/
/**    TY AND FITNESS, IN NO EVENT SHALL EVANS &  SUTHERLAND  BE  LIABLE    **/
/**    FOR  ANY  SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY  DAM-    **/
/**    AGES  WHATSOEVER RESULTING FROM  LOSS OF USE,  DATA  OR  PROFITS,    **/
/**    WHETHER   IN  AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS    **/
/**    ACTION, ARISING OUT OF OR IN  CONNECTION  WITH  THE  USE  OR PER-    **/
/**    FORMANCE OF THIS SOFTWARE.                                           **/
/*****************************************************************************/

/***********************************************************************
 *
 * $Header: lex.l,v 1.43 88/10/14 07:05:48 toml Exp $
 *
 * .twmrc lex file
 *
 * 12-Nov-87 Thomas E. LaStrange		File created
 *
 ***********************************************************************/

static char RCSinfo[]=
"$Header: lex.l,v 1.43 88/10/14 07:05:48 toml Exp $";

#include <stdio.h>
#include "gram.h"

extern int ParseError;

# define YYNEWLINE 10
yylex(){
int nstr; extern int yyprevious;
while((nstr = yylook()) >= 0)
yyfussy: switch(nstr){
case 0:
if(yywrap()) return(0); break;
case 1:
			{ return (LB); }
break;
case 2:
			{ return (RB); }
break;
case 3:
			{ return (EQUALS); }
break;
case 4:
			{ return (COLON); }
break;
case 5:
	{ (void)sscanf(&yytext[6], "%d", &yylval.num);
				  return (BUTTON);
				}
break;
case 6:
	{ (void)sscanf(&yytext[11], "%d", &yylval.num);
				  return (TBUTTON);
				}
break;
case 7:
	{ return MENU; }
break;
case 8:
 { return FUNCTION; }
break;
case 9:
			{ return (META); }
break;
case 10:
			{ return (SHIFT); }
break;
case 11:
			{ return (CONTROL); }
break;
case 12:
			{ return (WINDOW); }
break;
case 13:
			{ return (ICON); }
break;
case 14:
			{ return (TITLE); }
break;
case 15:
			{ return (ROOT); }
break;
case 16:
			{ return (FRAME); }
break;
case 17:
			{ return (ICONMGR); }
break;
case 18:
			{ return F_NOP; }
break;
case 19:
			{ return F_BEEP; }
break;
case 20:
			{ return F_QUIT; }
break;
case 21:
			{ return F_TITLE ; }
break;
case 22:
			{ return F_MENU; }
break;
case 23:
		{ return F_UNFOCUS; }
break;
case 24:
		{ return F_REFRESH; }
break;
case 25:
		{ return F_WINREFRESH; }
break;
case 26:
			{ return F_FILE; }
break;
case 27:
			{ return F_TWMRC; }
break;
case 28:
		{ return F_VERSION; }
break;
case 29:
		{ return F_CIRCLEUP; }
break;
case 30:
		{ return F_CIRCLEDOWN; }
break;
case 31:
		{ return F_SOURCE; }
break;
case 32:
		{ return F_CUTFILE; }
break;
case 33:
		{ return F_FUNCTION; }
break;
case 34:
		{ return F_SHOWLIST; }
break;
case 35:
		{ return F_HIDELIST; }
break;
case 36:
			{ return F_EXEC; }
break;
case 37:
			{ return F_CUT; }
break;
case 38:
			{ return F_MOVE; }
break;
case 39:
		{ return F_FORCEMOVE; }
break;
case 40:
		{ return F_ICONIFY; }
break;
case 41:
		{ return F_DEICONIFY; }
break;
case 42:
			{ return F_FOCUS; }
break;
case 43:
		{ return F_RESIZE; }
break;
case 44:
			{ return F_RAISE; }
break;
case 45:
		{ return F_RAISELOWER; }
break;
case 46:
			{ return F_LOWER; }
break;
case 47:
		{ return F_DESTROY; }
break;
case 48:
			{ return F_ZOOM; }
break;
case 49:
		{ return F_FULLZOOM; }
break;
case 50:
			{ return F_NOP; }
break;
case 51:
			{ return F_RAISE; }
break;
case 52:
			{ return F_LOWER; }
break;
case 53:
			{ return F_MOVE; }
break;
case 54:
{ return NO_RAISE_ON_MOVE; }
break;
case 55:
{ return NO_RAISE_ON_DEICONIFY; }
break;
case 56:
{ return NO_RAISE_ON_RESIZE; }
break;
case 57:
	{ return (COLOR); }
break;
case 58:
{ return (MONOCHROME); }
break;
case 59:
{ return (NO_TITLE_FOCUS); }
break;
case 60:
{ return (NO_HILITE); }
break;
case 61:
	{ return (ZOOM); }
break;
case 62:
{ return UNKNOWN_ICON; }
break;
case 63:
{ return WARPCURSOR; }
break;
case 64:
{ return BORDERWIDTH; }
break;
case 65:
{ return (TITLE_FONT); }
break;
case 66:
{ return (MENU_FONT); }
break;
case 67:
{ return (ICON_FONT); }
break;
case 68:
{ return (RESIZE_FONT); }
break;
case 69:
{ return (REVERSE_VIDEO); }
break;
case 70:
{ return (NO_TITLE); }
break;
case 71:
{ return (AUTO_RAISE); }
break;
case 72:
{ return (FORCE_ICON); }
break;
case 73:
{
			       return (DEFAULT_FUNCTION); }
break;
case 74:
{
			       return (WINDOW_FUNCTION); }
break;
case 75:
		{ return (ICONS); }
break;
case 76:
{return (ICON_DIRECTORY);}
break;
case 77:
{ return (BORDER_COLOR); }
break;
case 78:
{
				return (TITLE_FOREGROUND); }
break;
case 79:
{
				return (TITLE_BACKGROUND); }
break;
case 80:
{
				return (BORDER_TILE_FOREGROUND); }
break;
case 81:
{
				return (BORDER_TILE_BACKGROUND); }
break;
case 82:
{
				return (MENU_FOREGROUND); }
break;
case 83:
{
				return (MENU_BACKGROUND); }
break;
case 84:
{
				return (MENU_TITLE_FOREGROUND); }
break;
case 85:
{
				return (MENU_TITLE_BACKGROUND); }
break;
case 86:
{
				return (MENU_SHADOW_COLOR); }
break;
case 87:
{
				return (ICON_FOREGROUND); }
break;
case 88:
{
				return (ICON_BACKGROUND); }
break;
case 89:
{
				return (ICON_BORDER_COLOR); }
break;
case 90:
return (DONT_MOVE_OFF);
break;
case 91:
{
				return (DECORATE_TRANSIENTS); }
break;
case 92:
{ return (ICONIFY_BY_UNMAPPING); }
break;
case 93:
{ return (DONT_ICONIFY_BY_UNMAPPING); }
break;
case 94:
{ return (ICONMGR_FOREGROUND); }
break;
case 95:
{ return (ICONMGR_BACKGROUND); }
break;
case 96:
{ return (ICONMGR_FONT); }
break;
case 97:
{ return (ICONMGR_GEOMETRY); }
break;
case 98:
{ return (SHOW_ICONMGR); }
break;
case 99:
{ return ICONMGR_NOSHOW; }
break;
case 100:
{ return NO_BACKINGSTORE; }
break;
case 101:
{ return NO_SAVEUNDER; }
break;
case 102:
{ return RANDOM_PLACEMENT; }
break;
case 103:
		{ yylval.ptr = yytext; return STRING; }
break;
case 104:
		{ (void)sscanf(yytext, "%d", &yylval.num);
				  return (NUMBER);
				}
break;
case 105:
		{;}
break;
case 106:
			{;}
break;
case 107:
			{
				  fprintf(stderr,
					"twm: bad character `%s', line %d\n",
					yytext, yylineno);
				  ParseError = 1;
				}
break;
case -1:
break;
default:
fprintf(yyout,"bad switch yylook %d",nstr);
} return(0); }
/* end of yylex */
yywrap() { return(1);}

#define unput(c)	TwmUnput(c)
#define input()		TwmInput()
#define output(c)	TwmOutput(c)
int yyvstop[] ={
0,

107,
0,

106,
107,
0,

106,
0,

36,
107,
0,

107,
0,

107,
0,

104,
107,
0,

4,
107,
0,

3,
107,
0,

107,
0,

107,
0,

107,
0,

107,
0,

107,
0,

107,
0,

107,
0,

107,
0,

107,
0,

107,
0,

107,
0,

107,
0,

107,
0,

107,
0,

37,
107,
0,

11,
107,
0,

107,
0,

107,
0,

9,
107,
0,

107,
0,

10,
107,
0,

107,
0,

107,
0,

1,
107,
0,

2,
107,
0,

103,
0,

105,
0,

104,
0,

7,
0,

61,
0,

13,
0,

15,
0,

57,
0,

75,
0,

18,
0,

16,
0,

50,
0,

14,
0,

19,
0,

26,
0,

22,
0,

38,
0,

20,
0,

48,
0,

53,
0,

12,
0,

5,
0,

70,
0,

42,
0,

46,
0,

44,
0,

21,
0,

27,
0,

17,
0,

52,
0,

51,
0,

8,
0,

67,
0,

66,
0,

43,
0,

31,
0,

71,
0,

65,
0,

32,
0,

47,
0,

40,
0,

24,
0,

23,
0,

28,
0,

72,
0,

58,
0,

68,
0,

63,
0,

29,
0,

49,
0,

33,
0,

77,
0,

64,
0,

90,
0,

60,
0,

101,
0,

62,
0,

41,
0,

39,
0,

59,
0,

69,
0,

6,
0,

30,
0,

45,
0,

25,
0,

76,
0,

54,
0,

35,
0,

34,
0,

88,
0,

87,
0,

83,
0,

82,
0,

100,
0,

74,
0,

73,
0,

89,
0,

96,
0,

86,
0,

56,
0,

102,
0,

98,
0,

79,
0,

78,
0,

91,
0,

92,
0,

55,
0,

99,
0,

97,
0,

85,
0,

84,
0,

81,
0,

80,
0,

95,
0,

94,
0,

93,
0,
0};
# define YYTYPE int
struct yywork { YYTYPE verify, advance; } yycrank[] ={
0,0,	0,0,	1,3,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	1,4,	1,5,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	1,6,	1,7,	
1,8,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	1,9,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	1,10,	
0,0,	0,0,	1,11,	0,0,	
0,0,	0,0,	1,12,	1,13,	
1,14,	1,15,	1,3,	1,16,	
1,3,	1,3,	1,17,	17,50,	
1,3,	1,3,	1,18,	1,19,	
1,3,	1,3,	14,45,	1,20,	
1,21,	1,22,	1,23,	1,3,	
1,24,	12,42,	1,3,	1,25,	
0,0,	0,0,	2,6,	1,26,	
2,8,	19,53,	21,56,	22,57,	
1,27,	29,66,	0,0,	1,28,	
0,0,	0,0,	1,29,	17,50,	
34,71,	0,0,	1,30,	0,0,	
0,0,	23,58,	14,45,	1,31,	
1,32,	1,33,	25,61,	2,10,	
1,34,	12,42,	2,11,	31,67,	
1,35,	7,37,	1,36,	42,72,	
65,117,	19,53,	21,56,	22,57,	
43,73,	7,37,	7,37,	9,41,	
9,41,	9,41,	9,41,	9,41,	
9,41,	9,41,	9,41,	9,41,	
9,41,	23,58,	15,46,	13,43,	
66,118,	44,74,	25,61,	67,119,	
71,125,	13,44,	98,152,	2,26,	
15,47,	99,153,	7,38,	42,72,	
2,27,	100,155,	102,159,	2,28,	
43,73,	8,39,	2,29,	103,160,	
104,161,	99,154,	2,30,	106,164,	
7,37,	8,39,	8,40,	2,31,	
2,32,	2,33,	15,46,	13,43,	
2,34,	44,74,	107,165,	20,54,	
2,35,	13,44,	2,36,	20,55,	
15,47,	7,37,	7,37,	7,37,	
7,37,	7,37,	7,37,	7,37,	
7,37,	7,37,	8,39,	7,37,	
7,37,	7,37,	7,37,	7,37,	
7,37,	111,172,	7,37,	7,37,	
7,37,	7,37,	7,37,	7,37,	
8,39,	7,37,	7,37,	20,54,	
68,120,	68,121,	68,122,	20,55,	
16,48,	112,173,	68,123,	113,174,	
114,175,	45,75,	16,49,	47,78,	
18,51,	8,39,	8,39,	8,39,	
8,39,	8,39,	8,39,	8,39,	
8,39,	8,39,	18,52,	8,39,	
8,39,	8,39,	8,39,	8,39,	
8,39,	48,79,	8,39,	8,39,	
8,39,	8,39,	8,39,	8,39,	
16,48,	8,39,	8,39,	24,59,	
28,62,	45,75,	16,49,	47,78,	
18,51,	49,80,	50,81,	24,60,	
28,62,	28,0,	46,76,	51,82,	
52,83,	46,77,	18,52,	116,164,	
54,89,	55,90,	56,92,	57,93,	
55,91,	48,79,	58,94,	59,95,	
60,96,	61,97,	33,68,	110,170,	
63,79,	64,80,	69,93,	24,59,	
117,176,	28,62,	33,68,	33,0,	
105,162,	49,80,	50,81,	24,60,	
118,177,	110,171,	46,76,	51,82,	
52,83,	46,77,	105,163,	28,62,	
54,89,	55,90,	56,92,	57,93,	
55,91,	119,178,	58,94,	59,95,	
60,96,	61,97,	120,179,	33,68,	
63,115,	64,116,	69,93,	121,180,	
28,62,	28,62,	28,62,	28,62,	
28,62,	28,62,	28,62,	28,62,	
28,62,	33,68,	28,62,	28,62,	
28,62,	28,62,	28,63,	28,62,	
122,181,	28,62,	28,62,	28,62,	
28,64,	28,62,	28,62,	70,93,	
28,62,	28,62,	33,68,	33,68,	
33,68,	33,68,	33,68,	33,68,	
33,68,	33,68,	33,69,	72,126,	
33,68,	33,68,	33,68,	33,68,	
33,68,	33,68,	73,127,	33,68,	
33,68,	33,68,	33,68,	33,68,	
33,68,	28,65,	33,68,	33,68,	
53,84,	74,128,	75,129,	70,124,	
76,130,	77,131,	53,85,	78,132,	
79,133,	80,134,	81,135,	82,136,	
83,137,	84,138,	33,70,	72,126,	
53,86,	53,87,	53,88,	101,156,	
123,182,	124,183,	73,127,	125,184,	
85,139,	101,157,	108,166,	86,140,	
87,141,	152,219,	108,167,	101,158,	
53,84,	74,128,	75,129,	153,220,	
76,130,	77,131,	53,85,	78,132,	
79,133,	80,134,	81,135,	82,136,	
83,137,	84,138,	88,142,	89,143,	
53,86,	53,87,	53,88,	62,98,	
62,99,	62,100,	90,144,	62,101,	
85,139,	62,102,	62,103,	86,140,	
87,141,	62,104,	62,105,	62,106,	
91,145,	92,146,	62,107,	62,108,	
62,109,	62,110,	62,111,	62,112,	
62,113,	93,147,	94,148,	62,114,	
95,149,	96,150,	88,142,	89,143,	
97,151,	109,168,	126,185,	115,133,	
127,186,	154,221,	90,144,	128,187,	
109,169,	129,188,	130,189,	131,190,	
133,193,	134,194,	132,191,	156,224,	
91,145,	92,146,	132,192,	159,229,	
158,227,	137,205,	158,228,	138,206,	
139,207,	93,147,	94,148,	140,208,	
95,149,	96,150,	141,209,	142,210,	
97,151,	115,166,	126,185,	115,133,	
127,186,	115,167,	143,211,	128,187,	
144,212,	129,188,	130,189,	131,190,	
133,193,	134,194,	132,191,	135,195,	
136,201,	135,196,	132,192,	135,197,	
136,202,	137,205,	135,198,	138,206,	
139,207,	145,213,	135,199,	140,208,	
146,214,	147,215,	141,209,	142,210,	
135,200,	136,203,	136,204,	148,216,	
149,217,	150,218,	143,211,	160,230,	
144,212,	157,225,	161,231,	155,222,	
162,232,	163,233,	164,234,	135,195,	
136,201,	135,196,	165,235,	135,197,	
136,202,	155,223,	135,198,	166,236,	
157,226,	145,213,	135,199,	167,237,	
146,214,	147,215,	168,239,	169,240,	
135,200,	136,203,	136,204,	148,216,	
149,217,	150,218,	170,241,	171,242,	
167,238,	172,243,	173,244,	174,245,	
175,246,	176,247,	177,248,	179,249,	
180,250,	181,251,	182,252,	183,253,	
184,254,	185,255,	186,256,	187,257,	
189,258,	190,259,	191,260,	192,261,	
193,262,	194,263,	195,264,	196,266,	
197,267,	198,268,	199,269,	201,270,	
202,271,	203,272,	204,273,	205,274,	
206,275,	207,276,	208,277,	209,278,	
195,265,	210,279,	211,280,	212,281,	
213,282,	214,283,	219,289,	216,286,	
217,287,	185,255,	186,256,	187,257,	
189,258,	190,259,	191,260,	192,261,	
193,262,	194,263,	195,264,	196,266,	
197,267,	198,268,	199,269,	201,270,	
202,271,	203,272,	204,273,	205,274,	
206,275,	207,276,	208,277,	209,278,	
195,265,	210,279,	211,280,	212,281,	
213,282,	214,283,	215,284,	216,286,	
217,287,	218,288,	215,285,	220,290,	
221,291,	222,292,	223,293,	224,294,	
225,295,	226,296,	227,297,	228,298,	
229,299,	230,300,	231,301,	232,302,	
233,303,	235,304,	236,305,	237,306,	
238,307,	239,308,	240,309,	241,310,	
242,311,	243,312,	244,313,	245,314,	
246,315,	248,316,	215,284,	249,317,	
250,318,	218,288,	215,285,	252,319,	
254,320,	255,321,	256,322,	257,325,	
257,325,	257,325,	257,325,	257,325,	
257,325,	257,325,	257,325,	257,325,	
257,325,	258,326,	259,327,	260,328,	
261,329,	262,330,	263,331,	256,323,	
264,332,	265,333,	256,324,	266,334,	
267,335,	268,337,	269,338,	270,339,	
267,336,	272,342,	273,343,	271,340,	
274,344,	255,321,	256,322,	271,341,	
275,345,	276,346,	277,347,	278,348,	
279,349,	280,350,	281,351,	282,352,	
283,353,	258,326,	259,327,	260,328,	
261,329,	262,330,	263,331,	256,323,	
264,332,	265,333,	256,324,	266,334,	
267,335,	268,337,	269,338,	270,339,	
267,336,	272,342,	273,343,	271,340,	
274,344,	284,354,	285,356,	271,341,	
275,345,	276,346,	277,347,	278,348,	
279,349,	280,350,	281,351,	282,352,	
283,353,	286,357,	287,358,	288,359,	
290,360,	291,361,	292,362,	293,363,	
295,364,	284,355,	296,365,	297,366,	
298,367,	299,368,	300,369,	301,370,	
305,371,	306,372,	307,373,	308,374,	
309,375,	284,354,	285,356,	310,376,	
311,377,	312,378,	313,379,	314,380,	
316,381,	317,382,	319,383,	321,384,	
322,385,	286,357,	287,358,	288,359,	
323,386,	324,387,	326,388,	327,389,	
328,390,	284,355,	329,391,	330,392,	
331,393,	332,394,	333,395,	334,396,	
335,397,	336,398,	337,399,	338,400,	
339,401,	340,402,	341,403,	342,404,	
343,405,	344,406,	345,407,	346,408,	
347,409,	348,410,	349,411,	321,384,	
322,385,	350,412,	351,413,	352,414,	
323,386,	324,387,	326,388,	327,389,	
328,390,	353,415,	329,391,	330,392,	
331,393,	332,394,	333,395,	334,396,	
335,397,	336,398,	337,399,	338,400,	
339,401,	340,402,	341,403,	342,404,	
343,405,	344,406,	345,407,	346,408,	
347,409,	348,410,	349,411,	354,416,	
355,417,	350,412,	351,413,	352,414,	
356,418,	357,420,	358,421,	359,422,	
356,419,	353,415,	360,423,	361,424,	
362,425,	363,426,	365,427,	366,428,	
367,429,	368,430,	369,431,	371,432,	
372,433,	373,434,	374,435,	375,436,	
378,437,	379,438,	380,439,	384,440,	
385,441,	386,442,	387,443,	354,416,	
355,417,	388,444,	389,445,	390,446,	
356,418,	357,420,	358,421,	359,422,	
356,419,	391,447,	392,448,	394,449,	
395,450,	396,451,	398,452,	399,453,	
400,454,	401,455,	403,456,	404,457,	
405,458,	406,459,	407,460,	408,461,	
409,462,	410,463,	411,464,	384,440,	
385,441,	386,442,	387,443,	412,465,	
413,466,	388,444,	389,445,	390,446,	
414,467,	415,468,	416,469,	417,470,	
418,471,	391,447,	392,448,	394,449,	
395,450,	396,451,	398,452,	399,453,	
400,454,	401,455,	403,456,	404,457,	
405,458,	406,459,	407,460,	408,461,	
409,462,	410,463,	411,464,	419,472,	
420,473,	421,474,	422,475,	412,465,	
413,466,	423,476,	424,478,	425,479,	
414,467,	415,468,	416,469,	417,470,	
418,471,	426,480,	427,481,	428,482,	
429,483,	430,484,	431,485,	432,486,	
433,487,	435,488,	423,477,	437,489,	
438,490,	439,491,	441,492,	442,493,	
443,494,	444,495,	445,496,	419,472,	
420,473,	421,474,	422,475,	446,497,	
447,498,	448,499,	449,500,	450,501,	
451,502,	452,503,	453,504,	454,505,	
455,506,	456,507,	457,508,	458,509,	
459,511,	460,512,	461,513,	458,510,	
476,529,	463,517,	464,518,	465,519,	
466,520,	467,521,	441,492,	442,493,	
443,494,	444,495,	445,496,	468,522,	
469,523,	470,524,	477,530,	446,497,	
447,498,	448,499,	449,500,	450,501,	
451,502,	452,503,	453,504,	454,505,	
455,506,	456,507,	457,508,	458,509,	
459,511,	460,512,	461,513,	458,510,	
462,514,	463,517,	464,518,	465,519,	
466,520,	467,521,	472,525,	473,526,	
474,527,	462,515,	475,528,	468,522,	
469,523,	470,524,	462,516,	479,531,	
481,532,	482,533,	483,534,	484,535,	
486,536,	488,537,	491,538,	492,539,	
493,540,	494,542,	495,543,	496,544,	
493,541,	497,545,	498,546,	500,547,	
462,514,	501,548,	502,549,	503,550,	
504,551,	505,552,	472,525,	473,526,	
474,527,	462,515,	475,528,	506,553,	
507,554,	508,555,	462,516,	509,556,	
510,557,	512,558,	513,559,	514,560,	
515,561,	516,562,	517,563,	492,539,	
493,540,	494,542,	495,543,	496,544,	
493,541,	497,545,	498,546,	500,547,	
518,564,	501,548,	502,549,	503,550,	
504,551,	505,552,	519,565,	521,566,	
522,567,	523,568,	524,569,	506,553,	
507,554,	508,555,	525,570,	509,556,	
510,557,	512,558,	513,559,	514,560,	
515,561,	516,562,	517,563,	526,571,	
528,572,	529,573,	531,574,	532,575,	
535,576,	536,577,	537,578,	538,579,	
518,564,	540,580,	541,581,	543,582,	
544,583,	545,584,	519,565,	521,566,	
522,567,	523,568,	524,569,	547,585,	
548,586,	549,587,	525,570,	550,588,	
551,589,	552,590,	553,594,	552,591,	
554,595,	552,592,	552,593,	526,571,	
528,572,	555,596,	556,597,	557,598,	
558,599,	560,600,	561,601,	562,602,	
564,603,	540,580,	541,581,	543,582,	
544,583,	545,584,	565,604,	566,605,	
567,606,	568,607,	573,611,	547,585,	
548,586,	549,587,	576,612,	550,588,	
551,589,	552,590,	553,594,	552,591,	
554,595,	552,592,	552,593,	570,609,	
572,610,	555,596,	556,597,	557,598,	
558,599,	560,600,	561,601,	562,602,	
564,603,	577,613,	578,614,	579,615,	
580,616,	581,617,	565,604,	566,605,	
567,606,	568,607,	569,608,	569,608,	
569,608,	569,608,	569,608,	569,608,	
569,608,	569,608,	569,608,	569,608,	
582,618,	583,619,	584,620,	570,609,	
572,610,	585,621,	586,622,	587,623,	
588,624,	589,625,	590,626,	591,627,	
592,628,	593,629,	594,630,	595,631,	
580,616,	581,617,	596,632,	597,633,	
598,634,	599,635,	600,636,	601,637,	
602,638,	604,639,	606,640,	607,641,	
609,642,	610,643,	612,644,	614,645,	
582,618,	583,619,	584,620,	616,646,	
617,647,	585,621,	586,622,	587,623,	
588,624,	589,625,	590,626,	591,627,	
592,628,	593,629,	594,630,	595,631,	
618,648,	619,649,	596,632,	597,633,	
598,634,	599,635,	600,636,	601,637,	
602,638,	604,639,	606,640,	607,641,	
609,642,	610,643,	620,650,	621,651,	
622,652,	624,653,	625,654,	616,646,	
617,647,	626,655,	627,656,	628,657,	
629,659,	630,660,	631,661,	628,658,	
632,662,	633,663,	634,664,	635,665,	
618,648,	619,649,	636,666,	638,667,	
639,668,	640,669,	641,670,	642,671,	
643,672,	646,673,	647,674,	648,675,	
649,676,	650,677,	620,650,	621,651,	
622,652,	624,653,	625,654,	652,678,	
654,679,	626,655,	627,656,	628,657,	
629,659,	630,660,	631,661,	628,658,	
632,662,	633,663,	634,664,	635,665,	
655,680,	656,681,	636,666,	638,667,	
639,668,	640,669,	641,670,	642,671,	
643,672,	646,673,	647,674,	648,675,	
649,676,	650,677,	657,682,	658,683,	
659,684,	662,685,	663,686,	652,678,	
654,679,	664,687,	666,688,	667,689,	
668,690,	669,691,	670,692,	671,693,	
673,694,	674,695,	675,696,	677,697,	
655,680,	656,681,	679,698,	680,699,	
681,700,	683,701,	684,702,	686,703,	
687,704,	688,705,	694,706,	695,707,	
696,708,	697,709,	657,682,	658,683,	
659,684,	662,685,	663,686,	698,710,	
699,711,	664,687,	666,688,	667,689,	
668,690,	669,691,	670,692,	671,693,	
673,694,	674,695,	675,696,	677,697,	
700,712,	701,713,	679,698,	680,699,	
681,700,	683,701,	684,702,	686,703,	
687,704,	688,705,	694,706,	695,707,	
696,708,	697,709,	702,714,	703,715,	
704,716,	705,717,	706,718,	698,710,	
699,711,	707,719,	708,720,	709,721,	
710,722,	711,723,	712,724,	713,725,	
714,726,	715,727,	716,728,	717,729,	
700,712,	701,713,	718,730,	719,731,	
721,732,	723,733,	724,734,	725,735,	
726,736,	727,737,	728,738,	730,739,	
731,740,	732,741,	702,714,	703,715,	
704,716,	705,717,	706,718,	733,742,	
735,743,	707,719,	708,720,	709,721,	
710,722,	711,723,	712,724,	713,725,	
714,726,	715,727,	716,728,	717,729,	
741,744,	742,745,	718,730,	719,731,	
721,732,	723,733,	724,734,	725,735,	
726,736,	727,737,	728,738,	730,739,	
731,740,	732,741,	743,746,	744,747,	
0,0,	0,0,	0,0,	733,742,	
735,743,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
741,744,	742,745,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	743,746,	744,747,	
0,0};
struct yysvf yysvec[] ={
0,	0,	0,
yycrank+-1,	0,		0,	
yycrank+-61,	yysvec+1,	0,	
yycrank+0,	0,		yyvstop+1,
yycrank+0,	0,		yyvstop+3,
yycrank+0,	0,		yyvstop+6,
yycrank+0,	0,		yyvstop+8,
yycrank+-124,	0,		yyvstop+11,
yycrank+-164,	0,		yyvstop+13,
yycrank+87,	0,		yyvstop+15,
yycrank+0,	0,		yyvstop+18,
yycrank+0,	0,		yyvstop+21,
yycrank+4,	0,		yyvstop+24,
yycrank+68,	0,		yyvstop+26,
yycrank+3,	0,		yyvstop+28,
yycrank+77,	0,		yyvstop+30,
yycrank+141,	0,		yyvstop+32,
yycrank+8,	0,		yyvstop+34,
yycrank+159,	0,		yyvstop+36,
yycrank+18,	0,		yyvstop+38,
yycrank+118,	0,		yyvstop+40,
yycrank+26,	0,		yyvstop+42,
yycrank+26,	0,		yyvstop+44,
yycrank+35,	0,		yyvstop+46,
yycrank+190,	0,		yyvstop+48,
yycrank+39,	0,		yyvstop+50,
yycrank+0,	0,		yyvstop+52,
yycrank+0,	yysvec+14,	yyvstop+55,
yycrank+-255,	0,		yyvstop+58,
yycrank+2,	yysvec+17,	yyvstop+60,
yycrank+0,	yysvec+18,	yyvstop+62,
yycrank+12,	yysvec+20,	yyvstop+65,
yycrank+0,	yysvec+21,	yyvstop+67,
yycrank+-281,	0,		yyvstop+70,
yycrank+3,	yysvec+24,	yyvstop+72,
yycrank+0,	0,		yyvstop+74,
yycrank+0,	0,		yyvstop+77,
yycrank+0,	yysvec+7,	0,	
yycrank+0,	0,		yyvstop+80,
yycrank+0,	yysvec+8,	0,	
yycrank+0,	0,		yyvstop+82,
yycrank+0,	yysvec+9,	yyvstop+84,
yycrank+43,	0,		0,	
yycrank+50,	0,		0,	
yycrank+65,	0,		0,	
yycrank+149,	0,		0,	
yycrank+199,	0,		0,	
yycrank+149,	0,		0,	
yycrank+163,	0,		0,	
yycrank+183,	0,		0,	
yycrank+183,	0,		0,	
yycrank+189,	0,		0,	
yycrank+190,	0,		0,	
yycrank+306,	0,		0,	
yycrank+194,	0,		0,	
yycrank+190,	0,		0,	
yycrank+195,	0,		0,	
yycrank+191,	0,		0,	
yycrank+203,	0,		0,	
yycrank+197,	0,		0,	
yycrank+202,	0,		0,	
yycrank+202,	0,		0,	
yycrank+325,	0,		0,	
yycrank+202,	yysvec+62,	0,	
yycrank+207,	yysvec+62,	0,	
yycrank+31,	yysvec+62,	0,	
yycrank+37,	yysvec+50,	0,	
yycrank+40,	0,		0,	
yycrank+108,	0,		0,	
yycrank+202,	yysvec+68,	0,	
yycrank+259,	yysvec+68,	0,	
yycrank+42,	yysvec+60,	0,	
yycrank+276,	0,		0,	
yycrank+294,	0,		0,	
yycrank+289,	0,		0,	
yycrank+295,	0,		0,	
yycrank+297,	0,		0,	
yycrank+312,	0,		0,	
yycrank+295,	0,		0,	
yycrank+313,	0,		0,	
yycrank+314,	0,		0,	
yycrank+304,	0,		0,	
yycrank+298,	0,		0,	
yycrank+305,	0,		0,	
yycrank+320,	0,		0,	
yycrank+323,	0,		0,	
yycrank+334,	0,		0,	
yycrank+335,	0,		0,	
yycrank+345,	0,		0,	
yycrank+351,	0,		0,	
yycrank+353,	0,		0,	
yycrank+367,	0,		0,	
yycrank+350,	0,		0,	
yycrank+369,	0,		0,	
yycrank+368,	0,		0,	
yycrank+368,	0,		0,	
yycrank+381,	0,		0,	
yycrank+375,	0,		0,	
yycrank+53,	0,		0,	
yycrank+52,	0,		0,	
yycrank+60,	0,		0,	
yycrank+286,	0,		0,	
yycrank+57,	0,		0,	
yycrank+68,	0,		0,	
yycrank+57,	0,		0,	
yycrank+191,	0,		0,	
yycrank+60,	0,		0,	
yycrank+65,	0,		0,	
yycrank+301,	0,		0,	
yycrank+349,	0,		0,	
yycrank+178,	0,		0,	
yycrank+95,	0,		0,	
yycrank+120,	0,		0,	
yycrank+118,	0,		0,	
yycrank+113,	0,		0,	
yycrank+388,	0,		0,	
yycrank+160,	yysvec+80,	0,	
yycrank+179,	0,		0,	
yycrank+186,	yysvec+81,	0,	
yycrank+193,	0,		0,	
yycrank+203,	0,		0,	
yycrank+208,	0,		0,	
yycrank+225,	0,		0,	
yycrank+295,	0,		0,	
yycrank+285,	yysvec+93,	0,	
yycrank+295,	yysvec+96,	0,	
yycrank+372,	0,		0,	
yycrank+387,	0,		0,	
yycrank+380,	0,		0,	
yycrank+379,	0,		0,	
yycrank+380,	0,		0,	
yycrank+378,	0,		0,	
yycrank+393,	0,		0,	
yycrank+395,	0,		0,	
yycrank+381,	0,		0,	
yycrank+433,	0,		0,	
yycrank+434,	0,		yyvstop+86,
yycrank+406,	0,		0,	
yycrank+408,	0,		0,	
yycrank+405,	0,		0,	
yycrank+406,	0,		0,	
yycrank+396,	0,		0,	
yycrank+399,	0,		0,	
yycrank+411,	0,		0,	
yycrank+402,	0,		0,	
yycrank+427,	0,		0,	
yycrank+439,	0,		0,	
yycrank+444,	0,		0,	
yycrank+440,	0,		0,	
yycrank+453,	0,		0,	
yycrank+442,	0,		0,	
yycrank+0,	0,		yyvstop+88,
yycrank+300,	0,		0,	
yycrank+293,	0,		0,	
yycrank+341,	0,		0,	
yycrank+422,	0,		0,	
yycrank+359,	0,		0,	
yycrank+426,	0,		0,	
yycrank+364,	0,		0,	
yycrank+371,	0,		0,	
yycrank+412,	0,		0,	
yycrank+407,	0,		0,	
yycrank+418,	0,		0,	
yycrank+411,	0,		0,	
yycrank+418,	0,		0,	
yycrank+429,	0,		0,	
yycrank+434,	0,		0,	
yycrank+441,	0,		0,	
yycrank+435,	0,		0,	
yycrank+430,	0,		0,	
yycrank+438,	0,		0,	
yycrank+446,	0,		0,	
yycrank+455,	0,		0,	
yycrank+444,	0,		0,	
yycrank+449,	0,		0,	
yycrank+449,	0,		0,	
yycrank+460,	0,		0,	
yycrank+453,	yysvec+135,	yyvstop+90,
yycrank+0,	0,		yyvstop+92,
yycrank+444,	0,		0,	
yycrank+446,	0,		0,	
yycrank+453,	0,		0,	
yycrank+461,	0,		0,	
yycrank+466,	yysvec+147,	0,	
yycrank+457,	yysvec+150,	0,	
yycrank+504,	0,		0,	
yycrank+488,	0,		0,	
yycrank+493,	0,		0,	
yycrank+0,	0,		yyvstop+94,
yycrank+507,	0,		0,	
yycrank+497,	0,		0,	
yycrank+507,	0,		0,	
yycrank+496,	0,		0,	
yycrank+503,	0,		0,	
yycrank+504,	0,		0,	
yycrank+513,	0,		0,	
yycrank+506,	0,		0,	
yycrank+501,	0,		0,	
yycrank+511,	0,		0,	
yycrank+517,	0,		0,	
yycrank+0,	0,		yyvstop+96,
yycrank+518,	0,		0,	
yycrank+505,	0,		0,	
yycrank+513,	0,		0,	
yycrank+513,	0,		0,	
yycrank+515,	0,		0,	
yycrank+513,	0,		0,	
yycrank+517,	0,		0,	
yycrank+507,	0,		0,	
yycrank+522,	0,		0,	
yycrank+517,	0,		0,	
yycrank+517,	0,		0,	
yycrank+526,	0,		0,	
yycrank+513,	0,		0,	
yycrank+530,	0,		0,	
yycrank+564,	0,		0,	
yycrank+512,	0,		0,	
yycrank+515,	0,		0,	
yycrank+546,	0,		0,	
yycrank+486,	0,		0,	
yycrank+536,	0,		0,	
yycrank+534,	0,		0,	
yycrank+538,	0,		0,	
yycrank+522,	0,		0,	
yycrank+538,	0,		0,	
yycrank+523,	0,		0,	
yycrank+542,	0,		0,	
yycrank+534,	0,		0,	
yycrank+544,	0,		0,	
yycrank+543,	0,		0,	
yycrank+535,	0,		0,	
yycrank+545,	0,		0,	
yycrank+530,	0,		0,	
yycrank+547,	0,		0,	
yycrank+0,	0,		yyvstop+98,
yycrank+533,	0,		0,	
yycrank+535,	0,		0,	
yycrank+537,	0,		0,	
yycrank+547,	0,		0,	
yycrank+534,	0,		0,	
yycrank+540,	0,		0,	
yycrank+547,	0,		0,	
yycrank+542,	0,		0,	
yycrank+546,	0,		0,	
yycrank+543,	0,		0,	
yycrank+545,	0,		0,	
yycrank+551,	0,		0,	
yycrank+0,	0,		yyvstop+100,
yycrank+558,	yysvec+199,	0,	
yycrank+562,	0,		0,	
yycrank+563,	0,		0,	
yycrank+0,	0,		yyvstop+102,
yycrank+552,	0,		0,	
yycrank+0,	yysvec+215,	yyvstop+104,
yycrank+549,	yysvec+218,	0,	
yycrank+596,	0,		0,	
yycrank+603,	0,		0,	
yycrank+623,	0,		0,	
yycrank+597,	0,		0,	
yycrank+598,	0,		0,	
yycrank+604,	0,		0,	
yycrank+598,	0,		0,	
yycrank+618,	0,		0,	
yycrank+607,	0,		0,	
yycrank+621,	0,		0,	
yycrank+607,	0,		0,	
yycrank+609,	0,		0,	
yycrank+614,	0,		0,	
yycrank+604,	0,		0,	
yycrank+616,	0,		0,	
yycrank+628,	0,		0,	
yycrank+621,	0,		0,	
yycrank+632,	0,		0,	
yycrank+614,	0,		0,	
yycrank+618,	0,		0,	
yycrank+631,	0,		0,	
yycrank+629,	0,		0,	
yycrank+637,	0,		0,	
yycrank+622,	0,		0,	
yycrank+639,	0,		0,	
yycrank+629,	0,		0,	
yycrank+640,	0,		0,	
yycrank+642,	0,		0,	
yycrank+633,	0,		0,	
yycrank+668,	0,		0,	
yycrank+655,	0,		0,	
yycrank+667,	0,		0,	
yycrank+664,	0,		0,	
yycrank+677,	0,		0,	
yycrank+0,	0,		yyvstop+106,
yycrank+640,	0,		0,	
yycrank+644,	0,		0,	
yycrank+639,	0,		0,	
yycrank+637,	0,		0,	
yycrank+0,	0,		yyvstop+108,
yycrank+637,	0,		0,	
yycrank+653,	0,		0,	
yycrank+633,	0,		0,	
yycrank+640,	0,		0,	
yycrank+652,	0,		0,	
yycrank+653,	0,		0,	
yycrank+645,	0,		0,	
yycrank+0,	0,		yyvstop+110,
yycrank+0,	0,		yyvstop+112,
yycrank+0,	0,		yyvstop+114,
yycrank+659,	0,		0,	
yycrank+660,	0,		0,	
yycrank+640,	0,		0,	
yycrank+658,	0,		0,	
yycrank+665,	0,		0,	
yycrank+666,	0,		0,	
yycrank+669,	0,		0,	
yycrank+670,	0,		0,	
yycrank+665,	0,		0,	
yycrank+670,	0,		0,	
yycrank+0,	0,		yyvstop+116,
yycrank+658,	0,		0,	
yycrank+659,	0,		0,	
yycrank+0,	0,		yyvstop+118,
yycrank+673,	0,		0,	
yycrank+0,	yysvec+288,	yyvstop+120,
yycrank+692,	0,		0,	
yycrank+697,	0,		0,	
yycrank+707,	0,		0,	
yycrank+708,	0,		0,	
yycrank+0,	yysvec+257,	yyvstop+122,
yycrank+713,	0,		0,	
yycrank+713,	0,		0,	
yycrank+706,	0,		0,	
yycrank+717,	0,		0,	
yycrank+708,	0,		0,	
yycrank+710,	0,		0,	
yycrank+714,	0,		0,	
yycrank+722,	0,		0,	
yycrank+722,	0,		0,	
yycrank+708,	0,		0,	
yycrank+724,	0,		0,	
yycrank+728,	0,		0,	
yycrank+730,	0,		0,	
yycrank+721,	0,		0,	
yycrank+713,	0,		0,	
yycrank+729,	0,		0,	
yycrank+731,	0,		0,	
yycrank+724,	0,		0,	
yycrank+722,	0,		0,	
yycrank+724,	0,		0,	
yycrank+730,	0,		0,	
yycrank+725,	0,		0,	
yycrank+727,	0,		0,	
yycrank+736,	0,		yyvstop+124,
yycrank+733,	0,		0,	
yycrank+731,	0,		0,	
yycrank+725,	0,		0,	
yycrank+739,	0,		0,	
yycrank+772,	0,		0,	
yycrank+756,	0,		0,	
yycrank+766,	0,		0,	
yycrank+772,	0,		0,	
yycrank+763,	0,		0,	
yycrank+762,	0,		0,	
yycrank+749,	0,		0,	
yycrank+743,	0,		0,	
yycrank+742,	0,		0,	
yycrank+742,	0,		0,	
yycrank+0,	0,		yyvstop+126,
yycrank+745,	0,		0,	
yycrank+744,	0,		0,	
yycrank+751,	0,		0,	
yycrank+758,	0,		0,	
yycrank+756,	0,		0,	
yycrank+0,	0,		yyvstop+128,
yycrank+751,	0,		yyvstop+130,
yycrank+745,	0,		0,	
yycrank+760,	0,		0,	
yycrank+763,	0,		0,	
yycrank+762,	0,		0,	
yycrank+0,	0,		yyvstop+132,
yycrank+0,	0,		yyvstop+134,
yycrank+747,	0,		0,	
yycrank+754,	0,		0,	
yycrank+764,	0,		0,	
yycrank+0,	0,		yyvstop+136,
yycrank+0,	0,		yyvstop+138,
yycrank+0,	0,		yyvstop+140,
yycrank+798,	0,		0,	
yycrank+792,	0,		0,	
yycrank+793,	0,		0,	
yycrank+802,	0,		0,	
yycrank+789,	0,		0,	
yycrank+789,	0,		0,	
yycrank+802,	0,		0,	
yycrank+802,	0,		0,	
yycrank+804,	0,		0,	
yycrank+0,	0,		yyvstop+142,
yycrank+812,	0,		0,	
yycrank+815,	0,		0,	
yycrank+818,	0,		0,	
yycrank+0,	0,		yyvstop+144,
yycrank+815,	0,		0,	
yycrank+798,	0,		0,	
yycrank+817,	0,		0,	
yycrank+818,	0,		0,	
yycrank+0,	0,		yyvstop+146,
yycrank+819,	0,		0,	
yycrank+812,	0,		0,	
yycrank+823,	0,		0,	
yycrank+816,	0,		0,	
yycrank+823,	0,		0,	
yycrank+824,	0,		0,	
yycrank+818,	0,		0,	
yycrank+829,	0,		0,	
yycrank+819,	0,		0,	
yycrank+838,	0,		0,	
yycrank+826,	0,		0,	
yycrank+835,	0,		0,	
yycrank+832,	0,		0,	
yycrank+835,	0,		0,	
yycrank+827,	0,		0,	
yycrank+828,	0,		0,	
yycrank+862,	0,		0,	
yycrank+865,	0,		0,	
yycrank+854,	0,		0,	
yycrank+856,	0,		0,	
yycrank+837,	0,		0,	
yycrank+837,	0,		0,	
yycrank+834,	0,		0,	
yycrank+824,	0,		0,	
yycrank+835,	0,		0,	
yycrank+836,	0,		0,	
yycrank+837,	0,		0,	
yycrank+838,	0,		0,	
yycrank+829,	0,		0,	
yycrank+840,	0,		0,	
yycrank+848,	0,		0,	
yycrank+0,	0,		yyvstop+148,
yycrank+842,	0,		0,	
yycrank+0,	0,		yyvstop+150,
yycrank+840,	0,		0,	
yycrank+846,	0,		0,	
yycrank+843,	0,		0,	
yycrank+0,	0,		yyvstop+152,
yycrank+879,	0,		0,	
yycrank+890,	0,		0,	
yycrank+876,	0,		0,	
yycrank+879,	0,		0,	
yycrank+884,	0,		0,	
yycrank+897,	0,		0,	
yycrank+898,	0,		0,	
yycrank+886,	0,		0,	
yycrank+888,	0,		0,	
yycrank+889,	0,		0,	
yycrank+888,	0,		0,	
yycrank+891,	0,		0,	
yycrank+889,	0,		0,	
yycrank+906,	0,		0,	
yycrank+894,	0,		0,	
yycrank+895,	0,		0,	
yycrank+891,	0,		0,	
yycrank+913,	0,		0,	
yycrank+911,	0,		0,	
yycrank+898,	0,		0,	
yycrank+910,	0,		0,	
yycrank+948,	0,		0,	
yycrank+916,	0,		0,	
yycrank+919,	0,		0,	
yycrank+920,	0,		0,	
yycrank+904,	0,		0,	
yycrank+921,	0,		0,	
yycrank+930,	0,		0,	
yycrank+925,	0,		0,	
yycrank+918,	0,		0,	
yycrank+0,	0,		yyvstop+154,
yycrank+951,	0,		0,	
yycrank+944,	0,		0,	
yycrank+942,	0,		0,	
yycrank+959,	0,		0,	
yycrank+873,	0,		0,	
yycrank+886,	0,		0,	
yycrank+0,	0,		yyvstop+156,
yycrank+929,	0,		0,	
yycrank+0,	0,		yyvstop+158,
yycrank+914,	0,		0,	
yycrank+924,	0,		0,	
yycrank+924,	0,		0,	
yycrank+925,	0,		0,	
yycrank+0,	0,		yyvstop+160,
yycrank+917,	0,		0,	
yycrank+0,	0,		yyvstop+162,
yycrank+927,	0,		0,	
yycrank+0,	0,		yyvstop+164,
yycrank+0,	0,		yyvstop+166,
yycrank+937,	0,		0,	
yycrank+957,	0,		0,	
yycrank+974,	0,		0,	
yycrank+969,	0,		0,	
yycrank+977,	0,		0,	
yycrank+976,	0,		0,	
yycrank+956,	0,		0,	
yycrank+976,	0,		0,	
yycrank+0,	0,		yyvstop+168,
yycrank+968,	0,		0,	
yycrank+982,	0,		0,	
yycrank+971,	0,		0,	
yycrank+972,	0,		0,	
yycrank+974,	0,		0,	
yycrank+971,	0,		0,	
yycrank+980,	0,		0,	
yycrank+981,	0,		0,	
yycrank+994,	0,		0,	
yycrank+998,	0,		0,	
yycrank+985,	0,		0,	
yycrank+0,	0,		yyvstop+170,
yycrank+981,	0,		0,	
yycrank+982,	0,		0,	
yycrank+998,	0,		0,	
yycrank+989,	0,		0,	
yycrank+1000,	0,		0,	
yycrank+988,	0,		0,	
yycrank+995,	0,		0,	
yycrank+1017,	0,		0,	
yycrank+0,	0,		yyvstop+172,
yycrank+1018,	0,		0,	
yycrank+1010,	0,		0,	
yycrank+1007,	0,		0,	
yycrank+1012,	0,		0,	
yycrank+1012,	0,		0,	
yycrank+1025,	0,		0,	
yycrank+0,	0,		yyvstop+174,
yycrank+1020,	0,		0,	
yycrank+986,	0,		0,	
yycrank+0,	0,		yyvstop+176,
yycrank+985,	0,		0,	
yycrank+1006,	0,		0,	
yycrank+0,	0,		yyvstop+178,
yycrank+0,	0,		yyvstop+180,
yycrank+999,	0,		0,	
yycrank+1008,	0,		0,	
yycrank+1001,	0,		0,	
yycrank+996,	0,		0,	
yycrank+0,	0,		yyvstop+182,
yycrank+1048,	0,		0,	
yycrank+1035,	0,		0,	
yycrank+0,	0,		yyvstop+184,
yycrank+1037,	0,		0,	
yycrank+1032,	0,		0,	
yycrank+1051,	0,		0,	
yycrank+0,	0,		yyvstop+186,
yycrank+1038,	0,		0,	
yycrank+1045,	0,		0,	
yycrank+1043,	0,		0,	
yycrank+1042,	0,		0,	
yycrank+1051,	0,		0,	
yycrank+1063,	0,		0,	
yycrank+1045,	0,		0,	
yycrank+1047,	0,		0,	
yycrank+1058,	0,		0,	
yycrank+1071,	0,		0,	
yycrank+1057,	0,		0,	
yycrank+1061,	0,		0,	
yycrank+0,	0,		yyvstop+188,
yycrank+1068,	0,		0,	
yycrank+1056,	0,		0,	
yycrank+1060,	0,		0,	
yycrank+0,	0,		yyvstop+190,
yycrank+1061,	0,		0,	
yycrank+1073,	0,		0,	
yycrank+1072,	0,		0,	
yycrank+1087,	0,		0,	
yycrank+1074,	0,		0,	
yycrank+1138,	0,		0,	
yycrank+1088,	0,		0,	
yycrank+0,	0,		yyvstop+192,
yycrank+1095,	0,		0,	
yycrank+1044,	0,		0,	
yycrank+0,	0,		yyvstop+194,
yycrank+0,	0,		yyvstop+196,
yycrank+1055,	0,		0,	
yycrank+1063,	0,		0,	
yycrank+1075,	0,		0,	
yycrank+1075,	0,		0,	
yycrank+1113,	0,		0,	
yycrank+1099,	0,		0,	
yycrank+1113,	0,		0,	
yycrank+1124,	0,		0,	
yycrank+1109,	0,		0,	
yycrank+1123,	0,		0,	
yycrank+1126,	0,		0,	
yycrank+1114,	0,		0,	
yycrank+1126,	0,		0,	
yycrank+1140,	0,		0,	
yycrank+1141,	0,		0,	
yycrank+1128,	0,		0,	
yycrank+1129,	0,		0,	
yycrank+1140,	0,		0,	
yycrank+1132,	0,		0,	
yycrank+1133,	0,		0,	
yycrank+1138,	0,		0,	
yycrank+1140,	0,		0,	
yycrank+1147,	0,		0,	
yycrank+1135,	0,		0,	
yycrank+1151,	0,		0,	
yycrank+1150,	0,		0,	
yycrank+1147,	0,		0,	
yycrank+0,	0,		yyvstop+198,
yycrank+1152,	0,		0,	
yycrank+0,	0,		yyvstop+200,
yycrank+1151,	0,		0,	
yycrank+1138,	0,		0,	
yycrank+0,	yysvec+569,	yyvstop+202,
yycrank+1139,	0,		0,	
yycrank+1146,	0,		0,	
yycrank+0,	0,		yyvstop+204,
yycrank+1112,	0,		0,	
yycrank+0,	0,		yyvstop+206,
yycrank+1113,	0,		0,	
yycrank+0,	0,		yyvstop+208,
yycrank+1156,	0,		0,	
yycrank+1163,	0,		0,	
yycrank+1171,	0,		0,	
yycrank+1166,	0,		0,	
yycrank+1173,	0,		0,	
yycrank+1191,	0,		0,	
yycrank+1181,	0,		0,	
yycrank+0,	0,		yyvstop+210,
yycrank+1193,	0,		0,	
yycrank+1182,	0,		0,	
yycrank+1198,	0,		0,	
yycrank+1188,	0,		0,	
yycrank+1189,	0,		0,	
yycrank+1189,	0,		0,	
yycrank+1201,	0,		0,	
yycrank+1202,	0,		0,	
yycrank+1193,	0,		0,	
yycrank+1202,	0,		0,	
yycrank+1203,	0,		0,	
yycrank+1206,	0,		0,	
yycrank+1199,	0,		0,	
yycrank+0,	0,		yyvstop+212,
yycrank+1189,	0,		0,	
yycrank+1202,	0,		0,	
yycrank+1212,	0,		0,	
yycrank+1204,	0,		0,	
yycrank+1205,	0,		0,	
yycrank+1206,	0,		0,	
yycrank+0,	0,		yyvstop+214,
yycrank+0,	0,		yyvstop+216,
yycrank+1214,	0,		0,	
yycrank+1215,	0,		0,	
yycrank+1218,	0,		0,	
yycrank+1210,	0,		0,	
yycrank+1211,	0,		0,	
yycrank+0,	0,		yyvstop+218,
yycrank+1213,	0,		0,	
yycrank+0,	0,		yyvstop+220,
yycrank+1216,	0,		0,	
yycrank+1233,	0,		0,	
yycrank+1225,	0,		0,	
yycrank+1238,	0,		0,	
yycrank+1254,	0,		0,	
yycrank+1247,	0,		0,	
yycrank+0,	0,		yyvstop+222,
yycrank+0,	0,		yyvstop+224,
yycrank+1243,	0,		0,	
yycrank+1244,	0,		0,	
yycrank+1247,	0,		0,	
yycrank+0,	0,		yyvstop+226,
yycrank+1252,	0,		0,	
yycrank+1262,	0,		0,	
yycrank+1248,	0,		0,	
yycrank+1251,	0,		0,	
yycrank+1266,	0,		0,	
yycrank+1267,	0,		0,	
yycrank+0,	0,		yyvstop+228,
yycrank+1254,	0,		0,	
yycrank+1255,	0,		0,	
yycrank+1260,	0,		0,	
yycrank+0,	0,		yyvstop+230,
yycrank+1262,	0,		0,	
yycrank+0,	0,		yyvstop+232,
yycrank+1269,	0,		0,	
yycrank+1272,	0,		0,	
yycrank+1261,	0,		0,	
yycrank+0,	0,		yyvstop+234,
yycrank+1274,	0,		0,	
yycrank+1277,	0,		0,	
yycrank+0,	0,		yyvstop+236,
yycrank+1268,	0,		0,	
yycrank+1269,	0,		0,	
yycrank+1276,	0,		0,	
yycrank+0,	0,		yyvstop+238,
yycrank+0,	0,		yyvstop+240,
yycrank+0,	0,		yyvstop+242,
yycrank+0,	0,		yyvstop+244,
yycrank+0,	0,		yyvstop+246,
yycrank+1271,	0,		0,	
yycrank+1272,	0,		0,	
yycrank+1268,	0,		0,	
yycrank+1288,	0,		0,	
yycrank+1281,	0,		0,	
yycrank+1278,	0,		0,	
yycrank+1300,	0,		0,	
yycrank+1291,	0,		0,	
yycrank+1302,	0,		0,	
yycrank+1302,	0,		0,	
yycrank+1303,	0,		0,	
yycrank+1319,	0,		0,	
yycrank+1305,	0,		0,	
yycrank+1308,	0,		0,	
yycrank+1311,	0,		0,	
yycrank+1315,	0,		0,	
yycrank+1325,	0,		0,	
yycrank+1318,	0,		0,	
yycrank+1319,	0,		0,	
yycrank+1320,	0,		0,	
yycrank+1318,	0,		0,	
yycrank+1323,	0,		0,	
yycrank+1324,	0,		0,	
yycrank+1314,	0,		0,	
yycrank+1328,	0,		0,	
yycrank+1329,	0,		0,	
yycrank+0,	0,		yyvstop+248,
yycrank+1328,	0,		0,	
yycrank+0,	0,		yyvstop+250,
yycrank+1324,	0,		0,	
yycrank+1323,	0,		0,	
yycrank+1326,	0,		0,	
yycrank+1323,	0,		0,	
yycrank+1345,	0,		0,	
yycrank+1346,	0,		0,	
yycrank+0,	0,		yyvstop+252,
yycrank+1347,	0,		0,	
yycrank+1348,	0,		0,	
yycrank+1344,	0,		0,	
yycrank+1345,	0,		0,	
yycrank+0,	0,		yyvstop+254,
yycrank+1346,	0,		0,	
yycrank+0,	0,		yyvstop+256,
yycrank+0,	0,		yyvstop+258,
yycrank+0,	0,		yyvstop+260,
yycrank+0,	0,		yyvstop+262,
yycrank+0,	0,		yyvstop+264,
yycrank+1358,	0,		0,	
yycrank+1369,	0,		0,	
yycrank+1382,	0,		0,	
yycrank+1380,	0,		0,	
yycrank+0,	0,		yyvstop+266,
yycrank+0,	0,		yyvstop+268,
yycrank+0,	0,		yyvstop+270,
0,	0,	0};
struct yywork *yytop = yycrank+1483;
struct yysvf *yybgin = yysvec+1;
char yymatch[] ={
00  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,011 ,012 ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
011 ,01  ,'"' ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,
'0' ,'0' ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,'A' ,'B' ,'C' ,'D' ,'E' ,'F' ,'G' ,
'H' ,'I' ,01  ,'K' ,'L' ,'M' ,'N' ,'O' ,
'P' ,01  ,'R' ,'S' ,'T' ,'U' ,'V' ,'W' ,
01  ,'Y' ,'Z' ,01  ,01  ,01  ,01  ,01  ,
01  ,'A' ,'B' ,'C' ,'D' ,'E' ,'F' ,'G' ,
'H' ,'I' ,01  ,'K' ,'L' ,'M' ,'N' ,'O' ,
'P' ,01  ,'R' ,'S' ,'T' ,'U' ,'V' ,'W' ,
01  ,'Y' ,'Z' ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
0};
char yyextra[] ={
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0};
/*	ncform	4.1	83/08/11	*/

int yylineno =1;
# define YYU(x) x
# define NLSTATE yyprevious=YYNEWLINE
char yytext[YYLMAX];
struct yysvf *yylstate [YYLMAX], **yylsp, **yyolsp;
char yysbuf[YYLMAX];
char *yysptr = yysbuf;
int *yyfnd;
extern struct yysvf *yyestate;
int yyprevious = YYNEWLINE;
yylook(){
	register struct yysvf *yystate, **lsp;
	register struct yywork *yyt;
	struct yysvf *yyz;
	int yych;
	struct yywork *yyr;
# ifdef LEXDEBUG
	int debug;
# endif
	char *yylastch;
	/* start off machines */
# ifdef LEXDEBUG
	debug = 0;
# endif
	if (!yymorfg)
		yylastch = yytext;
	else {
		yymorfg=0;
		yylastch = yytext+yyleng;
		}
	for(;;){
		lsp = yylstate;
		yyestate = yystate = yybgin;
		if (yyprevious==YYNEWLINE) yystate++;
		for (;;){
# ifdef LEXDEBUG
			if(debug)fprintf(yyout,"state %d\n",yystate-yysvec-1);
# endif
			yyt = yystate->yystoff;
			if(yyt == yycrank){		/* may not be any transitions */
				yyz = yystate->yyother;
				if(yyz == 0)break;
				if(yyz->yystoff == yycrank)break;
				}
			*yylastch++ = yych = input();
		tryagain:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"unsigned char ");
				allprint(yych);
				putchar('\n');
				}
# endif
			yyr = yyt;
			if ( (int)yyt > (int)yycrank){
				yyt = yyr + yych;
				if (yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				}
# ifdef YYOPTIM
			else if((int)yyt < (int)yycrank) {		/* r < yycrank */
				yyt = yyr = yycrank+(yycrank-yyt);
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"compressed state\n");
# endif
				yyt = yyt + yych;
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				yyt = yyr + YYU(yymatch[yych]);
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"try fall back character ");
					allprint(YYU(yymatch[yych]));
					putchar('\n');
					}
# endif
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transition */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				}
			if ((yystate = yystate->yyother) && (yyt= yystate->yystoff) != yycrank){
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"fall back to state %d\n",yystate-yysvec-1);
# endif
				goto tryagain;
				}
# endif
			else
				{unput(*--yylastch);break;}
		contin:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"state %d char ",yystate-yysvec-1);
				allprint(yych);
				putchar('\n');
				}
# endif
			;
			}
# ifdef LEXDEBUG
		if(debug){
			fprintf(yyout,"stopped at %d with ",*(lsp-1)-yysvec-1);
			allprint(yych);
			putchar('\n');
			}
# endif
		while (lsp-- > yylstate){
			*yylastch-- = 0;
			if (*lsp != 0 && (yyfnd= (*lsp)->yystops) && *yyfnd > 0){
				yyolsp = lsp;
				if(yyextra[*yyfnd]){		/* must backup */
					while(yyback((*lsp)->yystops,-*yyfnd) != 1 && lsp > yylstate){
						lsp--;
						unput(*yylastch--);
						}
					}
				yyprevious = YYU(*yylastch);
				yylsp = lsp;
				yyleng = yylastch-yytext+1;
				yytext[yyleng] = 0;
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"\nmatch ");
					sprint(yytext);
					fprintf(yyout," action %d\n",*yyfnd);
					}
# endif
				return(*yyfnd++);
				}
			unput(*yylastch);
			}
		if (yytext[0] == 0  /* && feof(yyin) */)
			{
			yysptr=yysbuf;
			return(0);
			}
		yyprevious = yytext[0] = input();
		if (yyprevious>0)
			output(yyprevious);
		yylastch=yytext;
# ifdef LEXDEBUG
		if(debug)putchar('\n');
# endif
		}
	}
yyback(p, m)
	int *p;
{
if (p==0) return(0);
while (*p)
	{
	if (*p++ == m)
		return(1);
	}
return(0);
}
	/* the following are only used in the lex library */
yyinput(){
	return(input());
	}
yyoutput(c)
  int c; {
	output(c);
	}
yyunput(c)
   int c; {
	unput(c);
	}
