/* ----------------------------------------------------------------- 
FILE:	    mergetile.c                                       
DESCRIPTION: mergetile()
CONTENTS:   
	  
	
DATE:	  February 7th, 1990 
REVISIONS: February 14th, 1990:  Interactive tile merge 
	   Feb. 28 : New penalty Global penalty: partition penalty   
----------------------------------------------------------------- */
#ifndef VMS
#ifndef lint
static char SccsId[] = "@(#) mergetile.c (Yale) version 1.17 5/3/92" ;
#endif
#endif

#include <string.h>
#include <yalecad/base.h>
#include <yalecad/rbtree.h>
#include <yalecad/file.h>
#include <yalecad/string.h>
#include <yalecad/message.h>
#include "standard.h"
#include "parser.h"
#define NUMPARTS 5 

#define PART_FILE  "DO YOU WANT TO READ PARTITIONS FROM FILE?"
#define GROUP      "DO YOU WANT ANOTHER GROUP?"
#define MOREPARTS  "DO YOU WANT ANOTHER PARTITION?"

static INT ux, uy,i ;
static INT lx, ly ;
static INT t[20],num;
static INT tileS ,partAlloc;
extern BOOL drawPartition, doGraphicsG;
extern YTREEPTR Tiletree,Tilealltree,Tilemacro1tree,Tilemacro2tree;
extern YTREEPTR XCornerTree, YCornerTree, XIntervalTree,YIntervalTree;

YTREEPTR legal_part_tree; /* hold the legal partitions to check as entered and
				in uloop */ 
INT partitions;
FILE *fpparti,*fpparto;
char filename[LRECL],command[LRECL];

read_partitions()
{
static int number,j;
char buffer[LRECL] , copy_buffer[LRECL];
char *bufferptr , *class;
char **tokens ;
INT  numtokens , count_part = 0;
INT  xcheck1,ycheck1,xcheck2,ycheck2;

sprintf( filename , "%s.part" , cktNameG ) ;
fpparti = TWOPEN( filename , "r" , ABORT ) ;
while( bufferptr = fgets( buffer, LRECL,fpparti) ) {
	strcpy( copy_buffer, bufferptr ) ;
        tokens = Ystrparser( bufferptr, " \t\n", &numtokens ) ;
		xcheck1 = atoi(tokens[0]);
		ycheck1 = atoi(tokens[1]);
		xcheck2 = atoi(tokens[2]);
		ycheck2 = atoi(tokens[3]);
	if ( numtokens == 5 ) {
		class = (char*)Ysafe_calloc(strlen(tokens[4]),sizeof(char));
		strcpy(class , tokens[4]);
	} else {
		class = (char*)Ysafe_calloc(4,sizeof(char));
		strcpy(class , "none");
	}	
	printf ("Checking partition %d\n", ++count_part);
	add_partition_corners(xcheck1,ycheck1,xcheck2,ycheck2);
	check_partition(class,xcheck1,ycheck1,xcheck2,ycheck2);
	make_partition(class,xcheck1,ycheck1,xcheck2,ycheck2);
}
TWCLOSE( fpparti ) ;
return;
}

check_partition(class,x1,y1,x2,y2)
int x1,y1,x2,y2 ;
char *class ;
{
/*** is not doing what I want : tobe fixed 
	if (! Yrbtree_search( legal_part_tree , class ) ){
		M(WARNMSG,"check_partition","Invalid partition class\n") ;
		printf ("I would think you want this partition free \n") ;
		printf("of any stdcells\n");
	}
	*/

	if (y1 >= y2) {
		/* invalid quit*/
		M(ERRMSG,"check_partition","Invalid partition \"y\" dimensions\n Aborting program.");
		YexitPgm(PGMFAIL) ;
	}
	if (x1 >= x2) {
		/* invalid quit*/
		M(ERRMSG,"check_partition","Invalid partition \"x\" dimensions\n Aborting program.");
		YexitPgm(PGMFAIL) ;
	}
}

newmerge()
{
BOOL more_partition;

partitions = 0;
partAlloc =  NUMPARTS;
partarrayG = (PARTNPTR *) Ysafe_calloc (partAlloc , sizeof(PARTNPTR));
make_corner_and_intervaltrees();
if (!doGraphicsG){
	read_partitions();
	return;
}
#ifndef NOGRAPHICS

more_partition = TRUE;
while (more_partition){
	init_draw2();
	drawPartition = TRUE ;
	draw_the_data2("Click at diagonal points for a partition");
	get_partitions();
	more_partition = query_dialog( MOREPARTS ) ;
}
#endif /* NOGRAPHICS */
}

make_partition(class,a,b,c,d)
INT a,b,c,d;
char *class;
{
static PARTNPTR partptr;
/*** a,b : lower left
c,d : upper right ***/

  if (++partitions>=partAlloc) { /* here is where partitions is
incremented*/
       partAlloc += NUMPARTS;
       partarrayG =  (PARTNPTR *) Ysafe_realloc(  partarrayG,
                  partAlloc * sizeof( PARTNPTR ) ) ;
   }
partptr = partarrayG[partitions]= (PARTNPTR)Ysafe_calloc(1,sizeof(PARTNBOX));
	 partptr->id = partitions; 
 /* as entered by the user */
	 if (class) strcpy (partptr->class , class );
	 else strcpy (partptr->class , "none");
	 partptr->upper_left_x = a;
	 partptr->upper_left_y = d;
	 partptr->lower_right_x = c;
	 partptr->lower_right_y = b;
	 partptr->area = (c-a)*(d-b);
         part_capacity(partptr); 
       	 num_partnsG = partitions;
}

int search_all_tile_list(x,y) 
int x,y;
{
static PTILEPTR tptr,dummyptr;

dummyptr = (PTILEPTR) Ysafe_calloc(1, sizeof(PTBOX) );
dummyptr->upper_left_x = x;
dummyptr->upper_left_y = y;
dummyptr->lower_right_x = x;
dummyptr->lower_right_y = y;
tptr = (PTILEPTR) Yrbtree_search(Tilealltree, (char*)dummyptr);
Ysafe_free(dummyptr);
if (tptr) {
	return(tptr->id);
} else return (0);
}

int search_legal_tile(x,y)
int x,y;
{
static PTILEPTR dummyptr,tptr;

dummyptr = (PTILEPTR) Ysafe_calloc(1, sizeof(PTBOX) );
dummyptr->upper_left_x = x;
dummyptr->upper_left_y = y;
dummyptr->lower_right_x = x;
dummyptr->lower_right_y = y;
tptr = (PTILEPTR) Yrbtree_search(Tiletree, (char*)dummyptr);
Ysafe_free(dummyptr);
if (tptr) 
return(tptr->id);
else return(0);
}


int search_macro_tile(x,y)
int x,y;
{
static PTILEPTR dummyptr,tptr;

dummyptr = (PTILEPTR) Ysafe_calloc(1, sizeof(PTBOX) );
dummyptr->upper_left_x = x;
dummyptr->upper_left_y = y;
dummyptr->lower_right_x = x;
dummyptr->lower_right_y = y;
tptr = (PTILEPTR) Yrbtree_search(Tilemacro2tree, (char*)dummyptr);
Ysafe_free(dummyptr);
if (tptr) 
return(tptr->id);
else return(0);
}



int search_tile_list3(x,y) /* will give the tile_id
                              whose upper left corner
                              coord.s are fed in */
int x,y;
{
 static PTILEPTR tptr;
 static int i,func_val,rx,ry;
 for (i = 1; i<=num_ptileG; i++){
   tptr = tarrayG[i];
   rx = tptr->upper_left_x ;
   ry = tptr->upper_left_y ;
   if ( x == rx  &&  y == ry ){
         func_val = tptr->id;
	 break;
   }
   else  func_val = 0;
 }
 return func_val;
 }



int search_tile_list4(x,y) /* will give the tile_id
                              whose lower right corner
                              coord.s are fed in */
int x,y;
{
 static PTILEPTR tptr;
 static int i,func_val,rx,ry;
 for (i = 1; i<=num_ptileG; i++){
   tptr = tarrayG[i];
   rx = tptr->lower_right_x ;
   ry = tptr->upper_left_y ;
   if ( x == rx  &&  y == ry ){
         func_val = tptr->id;
	 break;
   }
   else  func_val = 0;
 }
 return func_val;
 }


free_parts()
{
int partL,tileL;

for (partL = 1; partL <= num_partnsG; partL++){
	Ysafe_free(partarrayG[partL]);
}
num_partnsG = 0;
Yrbtree_empty(XCornerTree,0);
Yrbtree_empty(YCornerTree,0);
Yrbtree_empty(XIntervalTree,Ysafe_free);
Yrbtree_empty(YIntervalTree,Ysafe_free);
/**for (tileL = 1; tileL <= num_ptileG; tileL++){
	tarrayG[tileL]->partition_id = 0;
	tarrayG[tileL]->mg_flag = 0;
} **/
}
