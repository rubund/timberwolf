/* ----------------------------------------------------------------- 
FILE:	    build_menu.c                                       
DESCRIPTION:Program for building the menus.h file.
CONTENTS:   main()
DATE:	    Oct 14, 1990 
REVISIONS:  Tue Mar  5 10:44:04 EST 1991 - modified for library rename.
----------------------------------------------------------------- */
#ifndef lint
static char SccsId[] = "@(#) build_menu.c version 1.3 4/7/92" ;
#endif

#include <yalecad/base.h>
#include <yalecad/file.h>
#include <yalecad/message.h>
#include <yalecad/debug.h>
#include <yalecad/draw.h>
#include <yalecad/dialog.h>
#include <yalecad/colors.h>
#include <yalecad/cleanup.h>

main(argc,argv)
int argc;
char *argv[];
{

    Yinit_memsize( 64 * 1024 ) ;
    YINITCLEANUP( argv[0], NULL, MAYBEDUMP ) ;

    if( argc != 2 ){
	fprintf( stderr,"ERROR:syntax - build_menu menuName\n\n\n" ) ;
    }
    /* set library debug on */
    YsetDebug( FALSE ) ;
    Ymessage_mode( TRUE  ) ;
    fprintf( stderr, "%s\n\n" ,
	YinitProgram( "build_menu", "v1.0", NULL ) );

#ifndef NOGRAPHICS
    TWinitGraphics( argc,argv,TWnumcolors(),TWstdcolors(),FALSE,
	    TWread_menus( argv[1] ), NULL ) ;
#else /* NOGRAPHICS */
    fprintf( stderr, "This program is worthless without graphics!\n" ) ;
    fprintf( stderr, "This program was compiled with -DNOGRAPHICS defined.\n\n") ;
#endif /* NOGRAPHICS */
    YexitPgm( PGMOK ) ;

} /* end main program */
