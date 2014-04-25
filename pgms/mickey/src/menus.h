
/* TWmenu definitions */  
#define CANCEL			0
#define REDRAW			1
#define ZOOM			2
#define FULLVIEW		3
#define CONTINUE_PROG		4
#define AUTO_REDRAW_ON		5
#define AUTO_REDRAW_OFF		6
#define DUMP_GRAPHICS		7
#define CLOSE_GRAPHICS		8
#define DRAW_LABELS		20
#define IGNORE_LABELS		21
#define	DRAW_ROUTE		22
#define	IGNORE_ROUTE		23
#define	ALL_ROUTES		24
#define	IGNORE_ALL_ROUTES	25
#define	NET_ROUTE		26
#define	IGNORE_NET_ROUTE	27

static TWMENUBOX menuS[16] = {
    "CONTROL",0,0,1,0,0,
    "Redraw",0,0,0,1,0,
    "Zoom",0,0,0,2,0,
    "FullView",0,0,0,3,0,
    "Continue Prog.",0,0,0,4,0,
    "Auto Redraw On","Auto Redraw Off",1,0,5,6,
    "Dump Graphics",0,0,0,7,0,
    "Close Graphics",0,0,0,8,0,
    "Cancel",0,0,0,0,0,
    "DRAW ",0,0,1,0,0,
    "Draw Labels","Ignore Labels",1,0,20,21,
    "Draw Route","Ignore Route",1,0,22,23,
    "All Routes (Manual)","Ignore All Routes",1,0,24,25,
    "Draw Net And Route","Ignore Net And Route",1,0,26,27,
    "Cancel",0,0,0,0,0,
    0,0,0,0,0,0
} ;

