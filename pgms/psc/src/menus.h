
/* TWmenu definitions */  
#define TWNUMMENUS		16
#define AUTO_REDRAW_ON		1
#define AUTO_REDRAW_OFF		2
#define CLOSE_GRAPHICS		3
#define COLORS		4
#define EXIT_PROGRAM		5
#define DUMP_GRAPHICS		6
#define FULLVIEW		7
#define REDRAW		8
#define TELL_POINT		9
#define TRANSLATE		10
#define ZOOM		11
#define CANCEL		0
#define EXECUTE_PGMS		12
#define REMOTE_GRAPHICS_ON		13
#define REMOTE_GRAPHICS_OFF		14
#define CANCEL		0


static TWMENUBOX menuS[17] = {
    "CONTROL",0,0,1,0,0,
    "Auto Redraw On","Auto Redraw Off",1,0,1,2,
    "Close Graphics",0,0,0,3,0,
    "Colors",0,0,0,4,0,
    "Exit Program",0,0,0,5,0,
    "Dump Graphics",0,0,0,6,0,
    "FullView",0,0,0,7,0,
    "Redraw",0,0,0,8,0,
    "Tell Point",0,0,0,9,0,
    "Translate",0,0,0,10,0,
    "Zoom",0,0,0,11,0,
    "Cancel",0,0,0,0,0,
    "PGMS ",0,0,1,0,0,
    "Execute Pgms",0,0,0,12,0,
    "Remote Graphics On","Remote Graphics Off",0,0,13,14,
    "Cancel",0,0,0,0,0,
    0,0,0,0,0,0
} ;

