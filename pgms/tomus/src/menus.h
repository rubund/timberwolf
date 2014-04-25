
/* TWmenu definitions */  
#define TWNUMMENUS		19
#define AUTO_REDRAW_ON		1
#define AUTO_REDRAW_OFF		2
#define COLORS		4
#define CONTINUE_PROGRAM		5
#define DUMP_GRAPHICS		6
#define FULLVIEW		8
#define GRAPHICS_UPDATE_ON		9
#define GRAPHICS_UPDATE_OFF		10
#define REDRAW		11
#define TELL_POINT		12
#define TRANSLATE		13
#define ZOOM		14
#define CANCEL		0
#define IGNORE_PARTITIONS		20
#define DRAWPARTITIONS		21
#define DRAWLINES		22
#define IGNORE_LINES		23
#define DRAWNETS		24
#define IGNORENETS		25
#define DRAWMACROS		26
#define IGNOREMACROS		27
#define DRAWSTDCELLS		28
#define IGNORESTDCELLS		29
#define CANCEL		0


static TWMENUBOX menuS[20] = {
    "CONTROL",0,0,1,0,0,
    "Auto Redraw On","Auto Redraw Off",1,0,1,2,
    "Colors",0,0,0,4,0,
    "Continue Program",0,0,0,5,0,
    "Dump Graphics",0,0,0,6,0,
    "FullView",0,0,0,8,0,
    "Graphics Update On","Graphics Update Off",1,0,9,10,
    "Redraw",0,0,0,11,0,
    "Tell Point",0,0,0,12,0,
    "Translate",0,0,0,13,0,
    "Zoom",0,0,0,14,0,
    "Cancel",0,0,0,0,0,
    "DRAW ",0,0,1,0,0,
    "Ignore Partitions","DrawPartitions",1,0,20,21,
    "DrawLines","Ignore Lines",1,0,22,23,
    "DrawNets","IgnoreNets",0,0,24,25,
    "DrawMacros","IgnoreMacros",1,0,26,27,
    "DrawStdCells","IgnoreStdCells",0,0,28,29,
    "Cancel",0,0,0,0,0,
    0,0,0,0,0,0
} ;

