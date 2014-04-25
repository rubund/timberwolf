/* globals.h - global insert file for drawTW */ 
/* static char SccsId[] = "@(#) globals.h version 3.4 8/13/91" ; */

#ifndef GLOBALS_H
#define GLOBALS_H

#include <yalecad/base.h>
#include <yalecad/program.h>
#include <yalecad/string.h>
#include <yalecad/message.h>
#include <yalecad/wgraphics.h>
#include <yalecad/colors.h>
#include <yalecad/debug.h>

#define ROWCOLOR     TWGREEN
#define ROWCOLOR2    TWMEDAQUA
#define FEEDCOLOR    TWYELLOW
#define NETCOLOR     TWRED
#define PINCOLOR     TWBLACK
#define PSEUDOCOLOR  TWORANGE

#define EXPECTEDNUMSEG  20

#define SORTBYGROUP  1
#define SORTBYX      2

typedef struct route {
    int   x0;
    int   y0;
    int   pinloc;
    int   groupNo;
    int   pseudoFlag;
    struct route *next ;
}
*routeBoxPtr ,
routeBox ;

#endif /* GLOBALS_H */
