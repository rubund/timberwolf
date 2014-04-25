/* ----------------------------------------------------------------- 
FILE:	    output.c                                       
DESCRIPTION:output the placement information.
CONTENTS:   output()
	    final_free_up()
	    create_cel_file()
	    elim_unused_feeds()
DATE:	    Mar 27, 1989 
REVISIONS:  July 15, 1989
----------------------------------------------------------------- */
#ifndef lint
static char SccsId[] = "@(#) output.c (Yale) version 1.12 2/23/91" ;
#endif

/* #define DEC  */
/* added on 06/01/90 Sury */
/* #define NSC */

#include <string.h>
#include "standard.h"
#include "parser.h"
#include <yalecad/string.h>
#include <yalecad/file.h>
#include <yalecad/rbtree.h>
#include <yalecad/message.h>
#include <yalecad/colors.h>
#include <yalecad/draw.h>
#include <yalecad/yreadpar.h>

#define GREATER 1
#define LESS -1
#define EQUAL 0
#define GENROWPROG      "genrows"
#define GENPART         "DO YOU WISH TO RECONFIGURE ANY PARTITION ROWS?"

typedef struct row{
	int x1;
	int x2;
	int y1;
	int y2;
}
*ROWPTR,ROW;

typedef struct part_row{
        int numrows;
	ROWPTR *rowarray;
	BOOL  processed ;
}
*PARTROW,PROW;
PARTROW *partrows;

typedef struct padgroup{
	SHORT id;
	SHORT padside;
}
*PADGPTR,PADGP;

extern BOOL doGraphicsG;
int rowG;
static int part;
static PARTNPTR partptr;
FILE *fpmver,*fpcel;
YTREEPTR Padtree,Padgptree;
BOOL drawRow,output_timeG;

#ifdef OLDCODE

assigncells_to_parts()
{
static int tile,cell;
static PTILEPTR tileptr;

for (tile = 1; tile <= num_ptileG; tile++) {
    tileptr = tarrayG[tile];
    if (tileptr->legal || tileptr->capacity == 0) continue;
    part = tileptr->partition_id;
    partptr = partarrayG[part];
    if (!partptr->carray){
	     partptr->carray =  (CBOXPTR *)  Ysafe_malloc(
			(tileptr->cells +1)  * sizeof( CBOXPTR ) ) ;
    } else {
	     partptr->carray =  (CBOXPTR *) Ysafe_realloc(partptr->carray,
	       (partptr->cells + tileptr->cells +1) *sizeof( CBOXPTR ) ) ;
    }

    for (cell = 1; cell <= tileptr->cells; cell++) {
 	partptr->cells++;
 	partptr->carray[partptr->cells] = (CBOXPTR) Ysafe_malloc( 
							sizeof(CBOX) );
 	partptr->carray[partptr->cells] = tileptr->carray[cell];
    }
	partptr->celllen += tileptr->celllen;
}
}

#endif /* OLDCODE */

create_par_file(partptr)
PARTNPTR partptr;
{
    FILE *fppar;
    FILE *fin ;
    char filename[LRECL] ;
    char buffer[LRECL] ;
    char *bufferptr ;
    char **tokens ;
    char *lineptr ;
    INT  line ;
    INT  numtokens ;
    BOOL onNotOff ;
    BOOL wildcard ;


    /**** create :x.par file by reading .par file ****/
    sprintf( filename,"%s:%d.par", cktNameG, partptr->id ) ;
    fppar = TWOPEN( filename,"w",ABORT ) ;

    /* read user par file for RULES */
    sprintf( filename,"%s.par", cktNameG ) ;
    fin = TWOPEN( filename,"r",ABORT ) ;
    while( bufferptr = fgets( buffer, LRECL,fin) ) {
	bufferptr = Yremove_lblanks( bufferptr ) ;
	if( strncmp( bufferptr, "RULES", 5 ) == STRINGEQ ){
	    onNotOff = TRUE ;
	} else if( strncmp( bufferptr, "ENDRULES", 8 ) == STRINGEQ ){
	    fprintf( fppar, "%s", bufferptr ) ;
	    onNotOff = FALSE ;
	}
	if( onNotOff ){
	    fprintf( fppar, "%s", bufferptr ) ;
	}
    }
    TWCLOSE( fin ) ;

    Yreadpar_init( cktNameG, USER, TWSC, TRUE ) ;
    while( tokens = Yreadpar_next( &lineptr, &line, &numtokens, &onNotOff,
	&wildcard )){

	if( numtokens == 0 ){
	    /* skip over empty lines */
	    continue ;

	} else if( strcmp( tokens[0],"padspacing") == STRINGEQ ){
	    continue ;
	} else if( strcmp( tokens[0],"minimum_pad_space") == STRINGEQ ){
	} else {
	    /* we copy to output file */
	    fprintf(fppar,"%s", lineptr ) ;
	}
    } /* end while loop */
    /**** add pad spacing ***/
    fprintf(fppar,"TWSC*minimum_pad_space: %f\n", ceil(track_pitch));
    fprintf(fppar,"TWSC*padspacing : variable\n");

}

create_mver_file(partptr)
PARTNPTR partptr;
{
char filename[LRECL] ;
static int tile,macro,mac,*macro_array, cor;
static PADBOXPTR padptr ;
static CBOXPTR macroptr;

	 sprintf( filename , "%s:%d.mver" , cktNameG,partptr->id ) ;
	 fpmver = TWOPEN( filename, "w" , ABORT ) ;
	 fprintf(fpmver,"total_row_length %d\n", partptr->celllen);
	 fprintf(fpmver,"actual_row_height %d\n", rowHeight);
	 fprintf(fpmver,"channel_separation %d\n", rowHeight);
	 fprintf(fpmver,"min_length %d\n", (int)(0.2 *
	 	(partptr->lower_right_x - partptr->upper_left_x)));
	 fprintf(fpmver,"core %d %d %d %d\n", partptr->upper_left_x,partptr->lower_right_y,partptr->lower_right_x,partptr->upper_left_y);
	 fprintf(fpmver,"grid %d %d\n",(int)track_pitch,(int)track_pitch);
if (numMacroG == 0) {
	 fprintf(fpmver,"num_macros 0\n");
	 TWCLOSE(fpmver);
	 return;
}
macro_array = (int*) Ysafe_calloc((numMacroG+1),sizeof(int));
macro = 0;
for (mac = 1; mac <= numMacroG; mac++){
  tile = search_macro_tile(carrayG[numcellsG + mac]->cxcenter,carrayG[numcellsG + mac]->cycenter);
  part = tarrayG[tile]->partition_id;
  carrayG[numcellsG + mac]->tile = part;
  if (part == partptr->id){
        macro++;
	macro_array[macro] = mac;
  }
}
	 fprintf(fpmver,"num_macros %d\n",macro);
	 if (macro == 1) {
		macroptr = carrayG[numcellsG + macro_array[1]];
		fprintf(fpmver,"macro orient 0 4 vertices ");
		padptr = macroptr->padptr;
		for ( cor = 1 ; cor <= padptr->corners ; cor++){
			fprintf(fpmver,"%d %d ",
				padptr->xpoints[cor],padptr->ypoints[cor]);
		}
		fprintf(fpmver,"\n");
	 } else if ( macro > 1 ){
	 for (mac = 1; mac <= macro; mac++){
		macroptr = carrayG[numcellsG + macro_array[mac]];
		fprintf(fpmver,"macro orient 0 4 vertices ");
		padptr = macroptr->padptr;
		fprintf(fpmver,"%d %d ",
			padptr->xpoints[1]+1,padptr->ypoints[1]+1);
		fprintf(fpmver,"%d %d ",
			padptr->xpoints[2]+1,padptr->ypoints[2]-1);
		fprintf(fpmver,"%d %d ",
			padptr->xpoints[3]-1,padptr->ypoints[3]-1);
		fprintf(fpmver,"%d %d ",
			padptr->xpoints[4]-1,padptr->ypoints[4]+1);
	 }
	 }
	 TWCLOSE(fpmver);
}

output()
{
int part;

for (part =1 ; part <=num_partnsG; part++){
	if (partarrayG[part]->capacity == 0) continue;
        create_mver_file(partarrayG[part]);
	create_par_file(partarrayG[part]);
	if (partarrayG[part]->capacity == 0) continue;
}
    drawRow = TRUE;
    output_timeG = TRUE;
    sprintf(YmsgG,"Creating Inputs for TimberWolfSC.\n");
    printf("Ready to Create Inputs for TimberWolfSC.\n");
    create_cel_files() ;
    printf("Creating Inputs for TimberWolfSC before exiting.\n");
    call_gen_rows() ;
#ifndef NOGRAPHICS

    if (doGraphicsG) main_draw("Ready to Create Inputs for TimberWolfSC");
#endif /* NOGRAPHICS */

    final_free_up() ;
}

INT comparepads(p1,p2)
PADPTR p1,p2;
{
if (p1->x == p2->x && p1->y == p2->y) return (EQUAL);
else if (p1->y > p2->y) return (GREATER);
else if (p1->x > p2->x && p1->y == p2->y) return (GREATER);
else return (LESS);
}

INT comparepadgps(p1,p2)
PADGPTR p1,p2;
{
if (p1->padside > p2->padside)  return (GREATER);
if (p1->padside < p2->padside)  return (LESS);
else return (EQUAL);
}


create_cel_files()
{

FILE **fpoL , *fp ;
char **filename, finame[LRECL] ;
char cell_name[LRECL],padside,netname[LRECL] ;
static INT x,y ,padgroup, test , tok, delx, dely ;
static INT carray_index,tile,part ,pad, howmany;
static INT lx , ly , part_ht, part_wd ;
char input[LRECL]       ;
char copy_buffer[LRECL] ;
char **tokens           ;
char *bufferptr         ;
INT     numtokens ;
int macroLineC          ; /*** the line number of the hardcell
				 section of .cel file starting with 1 on
				hardcell line **/
double sidespace_lo,sidespace_hi;
BOOL    cellFound ,macroFound      ;
PADPTR padptr,getpadptr ;
PADGPTR padgpptr,getpadgptr ;


fpoL = (FILE**) Ysafe_malloc ((num_partnsG +1)* sizeof(FILE*));
filename = (char**) Ysafe_malloc ((num_partnsG +1)* sizeof(char*));

sprintf( finame , "%s.pcel" , cktNameG ) ;
fp = TWOPEN( finame, "r" , ABORT ) ;

carray_index = 0 ;
for (part =1 ; part <=num_partnsG; part++){
if (partarrayG[part]->capacity > 0){
filename[part] = (char*) Ysafe_malloc (LRECL * sizeof(char));
	sprintf( filename[part] , "%s:%d.scel" ,cktNameG, part ) ;
    	fpoL[part] = TWOPEN( filename[part], "w" , ABORT ) ;
}
}

while(  bufferptr = fgets( input, LRECL,fp) ) {

    strcpy( copy_buffer, bufferptr ) ;
    tokens = Ystrparser( bufferptr, " \t\n", &numtokens ) ;

    if( numtokens == 0 ){
	 cellFound = FALSE;
	 macroFound = FALSE;
	 macroLineC = 0;
   	 continue ;
    }
    if (macroFound) macroLineC++; 
    if( strcmp( tokens[0] , "cell" ) == 0 ) {

            cellFound = TRUE;
	    if( numtokens == 3 ){
	       strcpy( cell_name , tokens[2] ) ;
	       do {
	        	test = strcmp( carrayG[ ++carray_index ]->cname,
					cell_name ) ;
               } while( test != 0 ) ;
	       tile = carrayG[carray_index ]->tile;
	       part = tarrayG[tile]->partition_id;
	       fprintf(fpoL[part], "\n") ;
	       fprintf(fpoL[part], "%s ", copy_buffer) ;
	       fflush(fpoL[part]);
	    }
    } else if ( strcmp( tokens[0] , "hardcell" ) ==0 ){
	       macroFound = TRUE;
	       macroLineC = 1;
	       if( numtokens == 4 ){
	       strcpy( cell_name , tokens[3] ) ;
	       do {
	        	test = strcmp( carrayG[ ++carray_index ]->cname,
					cell_name ) ;
               } while( test != 0 ) ;
                part = carrayG[carray_index]->tile;
		if (!part || !partarrayG[part]->capacity) continue;
	        fprintf(fpoL[part], "\n") ;
	        fprintf(fpoL[part], "%s", copy_buffer) ; /** print first line 
                and then compute the pin positions and then print the rest **/
	        fflush(fpoL[part]);
                /******* print macros in the .scel files *****/
		print_macro(fpoL[part],carray_index);

	        fflush(fpoL[part]);
	       }
    } else if ( strcmp( tokens[0] , "legal_block_classes" ) ==0 ){
		continue;
    } else if ( strcmp( tokens[0] , "legal_part_classes" ) ==0 ){
		continue;
    } else {
	    if (!part || !partarrayG[part]->capacity) continue;
	    if ( cellFound ) { 
	       fprintf(fpoL[part], "%s", copy_buffer) ;
	       fflush(fpoL[part]);
	    } else if ( macroFound ) {
		/* introduce the patch up for equiv pins */
		if (strcmp( tokens[0] , "corners") == 0) {
		/* do nothing */
		} else if (numtokens == 8) { /* corner coord line */
		/* do nothing */
		} else if (numtokens == 2 && 
			(strcmp (tokens[0], "orient")) ) { /* not the orient
line */
		/* do nothing */
		} else if (numtokens == 9) { /* "pin" line */
			for (tok = 0 ; tok <= 6 ; tok ++) {
	       			fprintf(fpoL[part], "%s ", tokens[tok]) ;
			}
			delx = carrayG[carray_index]->padptr->xpoints[0];
			delx += atoi( tokens[7]);
			dely = carrayG[carray_index]->padptr->ypoints[0];
			dely += atoi( tokens[8]);
	       		fprintf(fpoL[part], "%d %d\n",delx , dely); 
		} else if (numtokens == 7) { /* "equiv pin" line */ 
			for (tok = 0 ; tok <= 4 ; tok ++) {
	       			fprintf(fpoL[part], "%s ", tokens[tok]) ;
			}
			delx = carrayG[carray_index]->padptr->xpoints[0];
			delx += atoi( tokens[5]);
			dely = carrayG[carray_index]->padptr->ypoints[0];
			dely += atoi( tokens[6]);
	       		fprintf(fpoL[part], "%d %d\n",delx , dely); 
		} else {
	       		fprintf(fpoL[part], "%s", copy_buffer) ;
	       		fflush(fpoL[part]);
		} 
	    } 
    }
}

/*** put pads on .scel files ****/

for (part =1 ; part <=num_partnsG; part++){
	if (partarrayG[part]->capacity == 0) continue;
	Padtree = Yrbtree_init(comparepads);
	for (pad =1 ; pad <=partarrayG[part]->numpads; pad++){
		padptr = partarrayG[part]->padlist[pad];
		Yrbtree_insert(Padtree, (char*)padptr);
	}

	for (pad =1 ; pad <=partarrayG[part]->numpads; pad++){
		padptr = partarrayG[part]->padlist[pad];
		howmany = howmany_same_pads(padptr);
		switch (padptr->padside){
		case 1:
                     padside = 'L';
		     break;
		case 2:
                     padside = 'T';
		     break;
		case 3:
                     padside = 'R';
		     break;
		case 4:
                     padside = 'B';
		     break;
                default:
		     break;	
		}
		strcpy(netname,netarrayG[padptr->net]->name); 
	        fprintf(fpoL[part], "\n") ;
                fprintf(fpoL[part],"pad %d name pad%d\n",pad,padptr->id); 
                fprintf(fpoL[part],"corners 4 -1 -1 -1 1 1 1 1 -1\n");
                fprintf(fpoL[part],"restrict side %c\n",padside);
		if (howmany==1) { /*** single pads not included in the
			padgroups and hence need sidespace right now ***/
			Yrbtree_delete(Padtree, (char*)padptr,0);
switch (padptr->padside){
	case 1:
	   sidespace_lo = (double)(padptr->tileptr->lower_right_y - partarrayG[part]->lower_right_y)/ (double)(partarrayG[part]->upper_left_y -
	   partarrayG[part]->lower_right_y);
	   sidespace_hi = (double)(padptr->tileptr->upper_left_y - partarrayG[part]->lower_right_y)/ (double)(partarrayG[part]->upper_left_y -
	   partarrayG[part]->lower_right_y);
           break;
	case 2:
	   sidespace_lo = (double)(padptr->tileptr->upper_left_x - partarrayG[part]->upper_left_x)/ (double)(partarrayG[part]->lower_right_x -
	   partarrayG[part]->upper_left_x);
	   sidespace_hi = (double)(padptr->tileptr->lower_right_x - partarrayG[part]->upper_left_x)/ (double)(partarrayG[part]->lower_right_x -
	   partarrayG[part]->upper_left_x);
           break;
	case 3:
	   sidespace_lo = (double)(padptr->tileptr->lower_right_y - partarrayG[part]->lower_right_y)/ (double)(partarrayG[part]->upper_left_y -
	   partarrayG[part]->lower_right_y);
	   sidespace_hi = (double)(padptr->tileptr->upper_left_y - partarrayG[part]->lower_right_y)/ (double)(partarrayG[part]->upper_left_y -
	   partarrayG[part]->lower_right_y);
	   break;
	case 4:
	   sidespace_lo = (double)(padptr->tileptr->upper_left_x - partarrayG[part]->upper_left_x)/ (double)(partarrayG[part]->lower_right_x -
	   partarrayG[part]->upper_left_x);
	   sidespace_hi = (double)(padptr->tileptr->lower_right_x - partarrayG[part]->upper_left_x)/ (double)(partarrayG[part]->lower_right_x -
	   partarrayG[part]->upper_left_x);
	   break;
        default:
           break;	
}

fprintf(fpoL[part],"sidespace %f	%f\n",sidespace_lo,sidespace_hi);
		}
                fprintf(fpoL[part],"pin name 1 signal %s layer 1 0 1\n",netname);
	        fflush(fpoL[part]);
	}

/* form the padgroups from the padtree and print  **/

fprintf(fpoL[part], "\n") ;
Padgptree = Yrbtree_init(comparepadgps);

padptr = (PADPTR) Yrbtree_enumerate(Padtree,TRUE);
x = padptr->x;
y = padptr->y;
padgroup = 1;
fprintf(fpoL[part],"padgroup padgroup%d permute\n",padgroup);
fprintf(fpoL[part],"pad%d nonfixed\n",padptr->id);
	        fflush(fpoL[part]);

padgpptr = (PADGPTR) Ysafe_calloc (1, sizeof(PADGP));
padgpptr->id = padgroup;
	part_ht = partarrayG[part]->upper_left_y -
					partarrayG[part]->lower_right_y;
	part_wd = partarrayG[part]->lower_right_x -
					partarrayG[part]->upper_left_x;
	lx = partarrayG[part]->upper_left_x ;
	ly = partarrayG[part]->lower_right_y ;
switch (padptr->padside){

	case 1:
           padgpptr->padside = 1;
	   sidespace_lo = (double)(padptr->tileptr->lower_right_y - ly)/ (double)(part_ht) ;
	   sidespace_hi = (double)(padptr->tileptr->upper_left_y - ly)/ (double)(part_ht);
           break;

	case 2:
           padgpptr->padside = 2;
	   sidespace_lo = (double)(padptr->tileptr->upper_left_x - lx)/ (double)(part_wd);
	   sidespace_hi = (double)(padptr->tileptr->lower_right_x - lx)/ (double)(part_wd);
           break;

	case 3:
           padgpptr->padside = 3;
	   sidespace_lo = (double)(padptr->tileptr->lower_right_y - ly)/ (double)(part_ht);
	   sidespace_hi = (double)(padptr->tileptr->upper_left_y - ly)/ (double)(part_ht );
	   break;

	case 4:
           padgpptr->padside = 4;
	   sidespace_lo = (double)(padptr->tileptr->upper_left_x - lx)/ (double)(part_wd);
	   sidespace_hi = (double)(padptr->tileptr->lower_right_x - lx)/ (double)(part_wd);
	   break;

        default:
           break;	

}
Yrbtree_insert(Padgptree, (char*)padgpptr);

for (getpadptr = (PADPTR) Yrbtree_interval(Padtree,(char*)padptr,(char*)padptr,TRUE);
	getpadptr; getpadptr = 
	(PADPTR) Yrbtree_interval(Padtree,(char*)padptr,(char*)padptr,FALSE)){
  if (padptr != getpadptr){ 
    fprintf(fpoL[part],"pad%d nonfixed\n",getpadptr->id);
    fflush(fpoL[part]);
  }
}
switch (padptr->padside){
	case 1:
           fprintf(fpoL[part],"restrict side L\n");
           break;
	case 2:
           fprintf(fpoL[part],"restrict side T\n");
           break;
	case 3:
           fprintf(fpoL[part],"restrict side R\n");
	   break;
	case 4:
           fprintf(fpoL[part],"restrict side B\n");
	   break;
        default:
           break;	
}
fprintf(fpoL[part],"sidespace %f	%f\n",sidespace_lo,sidespace_hi);

Yrbtree_interval_free(Padtree,(char*)padptr,(char*)padptr,NULL);
/*printf("%d\n",Yrbtree_size(Padtree)); */

for (padptr= (PADPTR) Yrbtree_enumerate(Padtree,TRUE)
;padptr; padptr= (PADPTR) Yrbtree_enumerate(Padtree,TRUE)){

   if (padptr->x == x && padptr->y == y) continue; 

   x = padptr->x;
   y = padptr->y;
   fprintf(fpoL[part], "\n") ;
   padgroup++;  

padgpptr = (PADGPTR) Ysafe_calloc (1, sizeof(PADGP));
padgpptr->id = padgroup;
	part_ht = partarrayG[part]->upper_left_y -
					partarrayG[part]->lower_right_y;
	part_wd = partarrayG[part]->lower_right_x -
					partarrayG[part]->upper_left_x;
	lx = partarrayG[part]->upper_left_x ;
	ly = partarrayG[part]->lower_right_y ;
switch (padptr->padside){

	case 1:
           padgpptr->padside = 1;
	   sidespace_lo = (double)(padptr->tileptr->lower_right_y - ly)/ (double)(part_ht);
	   sidespace_hi = (double)(padptr->tileptr->upper_left_y - ly)/ (double)(part_ht);
           break;

	case 2:
           padgpptr->padside = 2;
	   sidespace_lo = (double)(padptr->tileptr->upper_left_x - lx)/ (double)(part_wd);
	   sidespace_hi = (double)(padptr->tileptr->lower_right_x - lx)/ (double)(part_wd);
           break;

	case 3:
           padgpptr->padside = 3;
	   sidespace_lo = (double)(padptr->tileptr->lower_right_y - ly)/ (double)(part_ht);
	   sidespace_hi = (double)(padptr->tileptr->upper_left_y - ly)/ (double)(part_ht);
	   break;

	case 4:
           padgpptr->padside = 4;
	   sidespace_lo = (double)(padptr->tileptr->upper_left_x - lx)/ (double)(part_wd);
	   sidespace_hi = (double)(padptr->tileptr->lower_right_x - lx)/ (double)(part_wd);
	   break;

        default:
           break;	

}
Yrbtree_insert(Padgptree, (char*)padgpptr);

   fprintf(fpoL[part],"padgroup padgroup%d permute\n",padgroup);
   fprintf(fpoL[part],"pad%d nonfixed\n",padptr->id);
	        fflush(fpoL[part]);
   for (getpadptr = (PADPTR) Yrbtree_interval(Padtree,(char*)padptr,
						(char*)padptr,TRUE);
	getpadptr; getpadptr = 
	(PADPTR) Yrbtree_interval(Padtree,(char*)padptr,
						(char*)padptr,FALSE)){
     if (padptr != getpadptr){ 
        fprintf(fpoL[part],"pad%d nonfixed\n",getpadptr->id);
	        fflush(fpoL[part]);
     }
   }
switch (padptr->padside){
	case 1:
           fprintf(fpoL[part],"restrict side L\n");
           break;
	case 2:
           fprintf(fpoL[part],"restrict side T\n");
           break;
	case 3:
           fprintf(fpoL[part],"restrict side R\n");
	   break;
	case 4:
           fprintf(fpoL[part],"restrict side B\n");
	   break;
        default:
           break;	
}
fprintf(fpoL[part],"sidespace %f	%f\n",sidespace_lo,sidespace_hi);
fflush(fpoL[part]);
Yrbtree_interval_free(Padtree,(char*)padptr,(char*)padptr,NULL);
/**printf("%d\n",Yrbtree_size(Padtree)); **/
}

/********* print padgroup padgroup : not reqd any more *****

for (padgpptr= (PADGPTR) Yrbtree_enumerate(Padgptree,TRUE)
;padgpptr; padgpptr= (PADGPTR) Yrbtree_enumerate(Padgptree,TRUE)){

   fprintf(fpoL[part], "\n") ;
   fprintf(fpoL[part],"padgroup padgroup%d nopermute\n",++padgroup);
   fflush(fpoL[part]);

   for (getpadgptr = (PADGPTR) Yrbtree_interval(Padgptree,(char*)padgpptr,
						(char*)padgpptr,TRUE);
	getpadgptr; getpadgptr = 
	(PADGPTR) Yrbtree_interval(Padgptree,(char*)padgpptr,
						(char*)padgpptr,FALSE)){
        fprintf(fpoL[part],"padgroup%d fixed\n",getpadgptr->id);
        fflush(fpoL[part]);
   }
switch (padgpptr->padside){
	case 1:
           fprintf(fpoL[part],"restrict side L\n");
           break;
	case 2:
           fprintf(fpoL[part],"restrict side T\n");
           break;
	case 3:
           fprintf(fpoL[part],"restrict side R\n");
	   break;
	case 4:
           fprintf(fpoL[part],"restrict side B\n");
	   break;
        default:
           break;	
}
Yrbtree_interval_free(Padgptree,(char*)padgpptr,(char*)padgpptr,NULL);
}   ******/

TWCLOSE(fpoL[part]) ;
}
TWCLOSE(fp) ;
}

print_macro(filep,cell)
FILE *filep;
int cell;
{
static CBOXPTR macroptr;
static PADBOXPTR padptr;
int i;

    macroptr = carrayG[cell];
    padptr = macroptr->padptr ;

    fprintf(filep,"corners %d\n", padptr->corners);
    fflush(filep);
    for ( i = 1; i <= padptr->corners ; i++ ) {
    	fprintf(filep,"%d %d\n",padptr->xpoints[i], padptr->ypoints[i] );
    }
    fflush(filep);

}

print_macro_pins(filep,cell)
FILE *filep;
int cell;
{
static CBOXPTR macroptr;
static PINBOXPTR pinptr;

    macroptr = carrayG[cell];
    for (pinptr = macroptr->pins; pinptr; pinptr = pinptr->nextpin){
    fprintf(filep,"pin name %s signal %s layer %d",pinptr->pinname,netarrayG[pinptr->net]->name, pinptr->layer);
    fprintf(filep," %d  %d\n",pinptr->absx ,pinptr->absy);
    }
    fflush(filep);
}

howmany_same_pads(padptrS)
PADPTR padptrS;
{
static int countS;
static PADPTR getpadptrS;

   countS = 0;
   for (getpadptrS = (PADPTR) Yrbtree_interval(Padtree,(char*)padptrS,
						(char*)padptrS,TRUE);
	getpadptrS; getpadptrS = 
	(PADPTR) Yrbtree_interval(Padtree,(char*)padptrS,
						(char*)padptrS,FALSE)){
        countS++;
   }
return(countS);
}

call_gen_rows()
{
char *twdir ;
char *Ygetenv() ;
char filename[LRECL],command[LRECL] ;
char *Yrelpath() ;
static int i,part;
BOOL stateSaved = FALSE ;
BOOL work_needed ;

partrows = (PARTROW*) Ysafe_calloc (num_partnsG+1,sizeof(PARTROW));
for (i = 1; i <= num_partnsG; i++){
    if (!partarrayG[i]->capacity) continue;
    partrows[i] = (PARTROW) Ysafe_calloc (1,sizeof(PROW));
}

if (!doGraphicsG) {
	for (part = 1; part <= num_partnsG; part++){
    		if( twdir = Ygetenv( "TWDIR" ) ){
			sprintf( filename, "%s/bin/%s", twdir, GENROWPROG ) ;
    		}

    		/* Ysystem will not kill program if catastrophe occurred */
    		Ysystem( GENROWPROG, NOABORT, YmsgG, NULL ) ;
		
    		read_blk_file(part) ;
	}
	return;
}

#ifndef NOGRAPHICS

work_needed = TRUE ;
while( work_needed ){
    part = pick_partition() ;
    if (!(part)){
	continue ;
    }
    if (!partarrayG[part]->capacity){
	draw_the_data("Illegal Partition");
	continue ;
    }
    /* if we get to here we have a valid partition */
    if( twdir = Ygetenv( "TWDIR" ) ){
	sprintf( filename, "%s/bin/%s", twdir, GENROWPROG ) ;
    }

    sprintf( YmsgG, "%s -wf %s:%d %d",filename, cktNameG,
	part, TWsaveState()) ;
    stateSaved = TRUE ;
    M( MSG, NULL, YmsgG ) ;
    M( MSG, NULL, "\n" ) ;

    /* Ysystem will not kill program if catastrophe occurred */
    Ysystem( GENROWPROG, NOABORT, YmsgG, NULL ) ;
    if( stateSaved ){
	/* if we save the graphics state we need to restore it */
	TWrestoreState() ;
    }
    /* ############# end of genrows execution ############ */
    printf ("Genrows just created rows in Partition # %d.\n\n",part);
    read_blk_file(part) ;
    /*read_gen_file(part) ; */
    partrows[part]->processed = TRUE ;

    /* check to see if we are done */
    work_needed = FALSE ;
    for (i = 1; i <= num_partnsG; i++){
	if (!partarrayG[i]->capacity) continue;
	if(!(partrows[i]->processed )){
	    work_needed = TRUE ;
	}
    }

    /* if we are done - not_processed = FALSE - ask for more */
    if( work_needed == FALSE ){
	if( query_dialog( GENPART )){
	    work_needed = TRUE ;
	} else {
	    printf ("You have called Genrows in all the Partitions.\n\n");
	    break ; /* get out of the loop */
	}
    }
printf("\nClick in the middle of another partition to configure rows\n");
} /* end while loop */

#endif /* NOGRAPHICS */

} /* end call_gen_rows */



    
read_blk_file(part)
int part;
{
    char filename[LRECL] ,msg[LRECL];
    char buffer[LRECL], *bufferptr ;
    char **tokens ;     /* for parsing file */
    INT  numtokens, line ;
    BOOL abort ; /* whether to abort program */
    FILE *fp ;
    PARTROW prtptr;

    prtptr = partrows[part];
    if (prtptr->rowarray) Ysafe_free(prtptr->rowarray);
    prtptr->numrows = rowG = 0;
    /* **************** READ RESULTS of genrows ************/
    /* open block file for reading */
    sprintf(msg, "Reading results of genrows for Partition %d...\n",part ) ;
    M( MSG, NULL, msg) ;
    sprintf(filename, "%s:%d.blk" , cktNameG,part ) ;
    fp = TWOPEN( filename , "r", NOABORT ) ;

    /* parse file */
    line = 0 ;
    abort = FALSE ;
    while( bufferptr=fgets(buffer,LRECL,fp )){
	/* parse file */
	line ++ ; /* increment line number */
	tokens = Ystrparser( bufferptr, " \t\n", &numtokens );

	if( numtokens == 0 ){
	    /* skip over empty lines */
	    continue ;
	} else if( strcmp( tokens[0], "rows" ) == STRINGEQ){
	    /* look at first field for keyword */
	    /* ie. rows 3 */
	    if( numtokens != 2 ){
		sprintf( YmsgG, "Syntax error on line:%d\n", line ) ;
		M(ERRMSG, "read_blk_file", YmsgG ) ;
		abort = TRUE ;
		continue ;
	    } else{
		prtptr = partrows[part];
		if (prtptr->numrows == 0){
		prtptr->numrows += atoi(tokens[1]);
		prtptr->rowarray = (ROWPTR*) Ysafe_calloc (prtptr->numrows+1,sizeof(ROWPTR));
		} else {
		prtptr->numrows += atoi(tokens[1]);
		prtptr->rowarray = (ROWPTR*) Ysafe_realloc (prtptr->rowarray,(prtptr->numrows+1)*sizeof(ROWPTR));
		}
	    }
	    if( abort ) break ; /* no sense in reading any longer */
	} else if( strcmp( tokens[0], "row" ) == STRINGEQ ){
		/* row 23 12 218 38 except ... */
	    /* look at first field for keyword */
	    if( numtokens < 5 ){
		sprintf( YmsgG, "Syntax error on line:%d\n", line ) ;
		M(ERRMSG, "read_blk_file", YmsgG ) ;
		abort = TRUE ;
		continue ;
            } else if (numtokens > 5) { /* except case **/
		prtptr->numrows++;
		prtptr->rowarray = (ROWPTR*) Ysafe_realloc (prtptr->rowarray,(prtptr->numrows+1)*sizeof(ROWPTR));
		rowG++;
		prtptr->rowarray[rowG] = (ROWPTR) Ysafe_calloc (1,sizeof(ROW));
		prtptr->rowarray[rowG]->x1 = atoi(tokens[1]);
		prtptr->rowarray[rowG]->y1 = atoi(tokens[2]);
		prtptr->rowarray[rowG]->x2 = atoi(tokens[6]);
		prtptr->rowarray[rowG]->y2 = atoi(tokens[4]);
		rowG++;
		prtptr->rowarray[rowG] = (ROWPTR) Ysafe_calloc (1,sizeof(ROW));
		prtptr->rowarray[rowG]->x1 = atoi(tokens[7]);
		prtptr->rowarray[rowG]->y1 = atoi(tokens[2]);
		prtptr->rowarray[rowG]->x2 = atoi(tokens[3]);
		prtptr->rowarray[rowG]->y2 = atoi(tokens[4]);
	    } else {
		rowG++;
		prtptr->rowarray[rowG] = (ROWPTR) Ysafe_calloc (1,sizeof(ROW));
		prtptr->rowarray[rowG]->x1 = atoi(tokens[1]);
		prtptr->rowarray[rowG]->y1 = atoi(tokens[2]);
		prtptr->rowarray[rowG]->x2 = atoi(tokens[3]);
		prtptr->rowarray[rowG]->y2 = atoi(tokens[4]);
	    }
	} else {
	    continue ;
	}
    }
    TWCLOSE( fp ) ;

    if( abort ){
	M(ERRMSG, "read_blk_file", "Problem with genrows. Must abort\n" ) ;
#ifndef NOGRAPHICS

	TWcloseGraphics() ;

#endif /* NOGRAPHICS */
	YexitPgm( PGMFAIL ) ;
    }
    /* ************ END READ RESULTS of genrows ************/

} /* end read_blk_file() */

#ifdef OLDCODE

read_gen_file(part)
int part;
{
    char filename[LRECL] ;
    char buffer[LRECL], *bufferptr ;
    char **tokens ;     /* for parsing file */
    INT  numtokens, line ,tile,macro,mac,*macro_array,cur_part,i;
    INT incrx,incry;
    CBOXPTR macroptr ; /* current cell */
    PINBOXPTR pinptr ; /* current cell */
    BOOL abort ; /* whether to abort program */
    FILE *fp ;

    if( numMacroG == 0 ){
	return ;
    }
    /* **************** READ RESULTS of genrows ************/
    sprintf(filename, "%s:%d.gen" , cktNameG ,part) ;
    fp = TWOPEN( filename , "r", NOABORT ) ;

    /* parse file */
    line = 0 ;
    abort = FALSE ;
    macro_array = (INT*) Ysafe_calloc((numMacroG+1),sizeof(INT));
    macro = 0;
  for (mac = 1; mac <= numMacroG; mac++){
      macroptr = carrayG[numcellsG + mac];
    cur_part =	macroptr->tile;
    partptr = partarrayG[cur_part];
    if (part == partptr->id){
       macro++;
       macro_array[macro] = mac;
    }
  }
    for (mac = 1; mac <= macro; mac++){
        macroptr = carrayG[numcellsG + macro_array[mac]];

	while( bufferptr=fgets(buffer,LRECL,fp )){
	    /* parse file */
	    line++ ; /* increment line number */
	    tokens = Ystrparser( bufferptr, " \t\n", &numtokens );
	    if( numtokens == 0 ){
		/* skip over empty lines */
		continue ;
	    } else if( numtokens == 3 ){
		/*incrx = macroptr->cxcenter - atoi( tokens[0] ) ;*/
		macroptr->cxcenter = atoi( tokens[0] ) ;
		/*incry = macroptr->cycenter - atoi( tokens[1] ) ;*/
		macroptr->cycenter = atoi( tokens[1] ) ;
		for (i = 1; i<= 4; i++) {
			macroptr->cor_array[i]->x_coord -= incrx; 
			macroptr->cor_array[i]->y_coord -= incry; 
		}
		for (pinptr = macroptr->pins; pinptr; pinptr = pinptr->nextpin){
			pinptr->absx -= incrx;
			pinptr->absy -= incry;
			if (pinptr->absx  ==
			macroptr->cor_array[1]->x_coord){
				pinptr->xpos = point_xloc(macroptr->cxcenter);
				pinptr->ypos = point_yloc(pinptr->absy);
			} else if (pinptr->absx  ==  macroptr->cor_array[3]->x_coord){
				pinptr->xpos = point_xloc(macroptr->cxcenter);
				pinptr->ypos = point_yloc(pinptr->absy);
			} else {
			if (pinptr->absy  ==
			macroptr->cor_array[1]->y_coord){
				pinptr->ypos = point_yloc(macroptr->cycenter);
				pinptr->xpos = point_xloc(pinptr->absx);
			} else if (pinptr->absy  ==  macroptr->cor_array[3]->y_coord){
				pinptr->ypos = point_yloc(macroptr->cycenter);
				pinptr->xpos = point_xloc(pinptr->absx);
			} 
			}
                }
		break ; /* go on to the next cell */
	    } else {
		sprintf( YmsgG, "Problem reading .gen file on line:%d\n",line ) ;
		M( ERRMSG, "read_gen_file", YmsgG ) ;
		abort = TRUE ;
	    }
	}
    }

    TWCLOSE( fp ) ;

    if( abort ){
	M(ERRMSG, "read_gen_file", "Problem with genrows. Must abort\n" ) ;
#ifndef NOGRAPHICS
	TWcloseGraphics() ;
#endif /* NOGRAPHICS */

	YexitPgm( PGMFAIL ) ;
    }
    /* ************ END READ RESULTS of genrows ************/

} /* end read_gen_file() */

#endif /* OLDCODE */

#ifndef NOGRAPHICS
drawrow()
{
static int xr,yr,lx,ly,row,p;
PARTROW prtptr;

for (p = 1; p <= num_partnsG; p++){
 if (!partarrayG[p]->capacity) continue;
 prtptr = partrows[p];
 for( row = 1 ; row <= prtptr->numrows; row++ ){
        xr = prtptr->rowarray[row]->x1;
        yr = prtptr->rowarray[row]->y1;
        lx = prtptr->rowarray[row]->x2;
        ly = prtptr->rowarray[row]->y2;
        TWdrawCell(1,xr,yr,lx,ly,TWLIGHTGREEN,NULL) ;
 }
}
}
#endif /* NOGRAPHICS */

final_free_up()
{
    char filename[LRECL] ;

    /* clean out temporary files */

    sprintf( filename, "%s.pcel", cktNameG ) ;
    Yrm_files( filename ) ;
    sprintf( filename, "%s.gpar", cktNameG ) ;
    Yrm_files( filename ) ;
    sprintf( filename, "%s.mtwf", cktNameG ) ;
    Yrm_files( filename ) ;
    sprintf( filename, "%s.mgph", cktNameG ) ;
    Yrm_files( filename ) ;
    sprintf( filename, "%s.mrte", cktNameG ) ;
    Yrm_files( filename ) ;
    sprintf( filename, "%s.gout", cktNameG ) ;
    Yrm_files( filename ) ;
    sprintf( filename, "%s.gout", cktNameG ) ;
    Yrm_files( filename ) ;
    sprintf( filename, "%s.gpyt", cktNameG ) ;
    Yrm_files( filename ) ;
 /*   more things to be added to this */

}
