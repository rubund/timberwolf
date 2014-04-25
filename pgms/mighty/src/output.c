#ifndef lint
static char SccsId[] = "@(#) output.c version 6.3 12/27/90" ;
#endif

#include "mighty.h"
#include <yalecad/message.h>

extern int xshift, yshift;

/*****************************************************************
 *
 *  print_channel prints out the contents of the horizontal and vertical
 *  route layers of the channel.  One column is included for each (left
 *  and right) edge.
 *
 *
 *  Date: 3-30-86
 *
 ****************************************************************/

void print_channel (channel, num_rowsG, num_colsG, num_netsG)
CHANNELPTR channel;		/* the channel to be printed */
int num_rowsG;		/* number of rows in the channel */
int num_colsG;		/* number of columns in the channel */
int num_netsG;		/* number of nets in the channel */
{
    register int i, j;		/* loop counters */
    register int num, l;	/* used to convert integers to characters */
    char temp[20];		/* the caracter representation of a number */

#ifdef ONLYIFNEEDED
    {
	fprintf (output_fileG, "\nThe horizontal layer (turned sideways):\n");
	fprintf (output_fileG, " Top -------------------------> Bottom\n");
	fprintf (output_fileG, "     ");
	fprintf (output_fileG, "\n");
	for (j = 1; j <= num_colsG; j++)
	{
	    putc(' ', output_fileG);
	    for (i = num_rowsG; i >= 1; i--)
	    {
		num = channel->horiz_layer[i][j];

		if (num > num_netsG)
		{
		    putc(' ',output_fileG);
		    putc('X',output_fileG);
		    putc(' ',output_fileG);
		}
		else
		{
		    num = number_to_name(num);

		    /* Generate digits (reverse order) */
		    l = 0; do temp[l++] = num % 10 + '0'; while ((num /= 10) > 0);

		    /* right justify the number in a two digit field */
		    if (l == 1)
		        putc(' ', output_fileG);
    
		    /* Copy them back in correct order */
		    do putc(temp[--l], output_fileG); while (l > 0);

		    /* insert a space to separate the numbers */
		    putc(' ', output_fileG);
	        }
	    }
	    fprintf (output_fileG, " col = %3d\n", j );
	}
	fprintf(output_fileG, "     ");
	fprintf(output_fileG, "\n");

	fprintf (output_fileG, "\nThe vertical layer (turned sideways):\n");
	fprintf (output_fileG, " Top -----------------------> Bottom\n");
	fprintf (output_fileG, "     ");
	fprintf (output_fileG, "\n");
	for (j = 1; j <= num_colsG; j++)
	{
	    putc(' ', output_fileG);
	    for (i = num_rowsG; i >= 1; i--)
	    {
		num = channel->vert_layer[i][j];
		if (num > num_netsG)
		{
		    putc(' ',output_fileG);
		    putc('X',output_fileG);
		    putc(' ',output_fileG);
		}
		else
		{
		    num = number_to_name(num);

		    /* Generate digits (reverse order) */
		    l = 0; do temp[l++] = num % 10 + '0'; while ((num /= 10) > 0);

		    /* right justify the number in a 2 digit field */
		    if (l == 1)
		        putc(' ', output_fileG);

		    /* Copy them back in correct order */
		    do putc(temp[--l], output_fileG); while (l > 0);

		    /* insert a space to separate the numbers */
		    putc(' ', output_fileG);
	        }
	    }
	    fprintf (output_fileG, "  col = %3d\n", j );
	}
	fprintf(output_fileG, "     ");
	fprintf(output_fileG, "\n");
    }
#endif
}



/*****************************************************************
 *
 *  print_channel prints out the contents of the horizontal and vertical
 *  route layers of the channel.  One column is included for each (left
 *  and right) edge.
 *
 ****************************************************************/

void print_debug (msg, name, layer, num_rowsG, num_colsG, num_netsG)
char *msg;
char *name;
int **layer;		/* the layer to be printed */
int num_rowsG;		/* number of rows in the channel */
int num_colsG;		/* number of columns in the channel */
int num_netsG;		/* number of nets in the channel */
{
    register int i, j;		/* loop counters */
    register int num, l;	/* used to convert integers to characters */
    char temp[20];		/* the caracter representation of a number */

    static int dumpNetNames = 1 ;
    {

	if( dumpNetNames ){
	    fprintf( output_fileG," Net number to net name table \n" ) ;
	    fprintf( output_fileG," net number : net name\n" ) ;
	    for( i=1;i<=num_netsG;i++ ){
		fprintf( output_fileG, " %4d : %4d \n", i,
		number_to_name(i) );
	    }
	    dumpNetNames = 0 ;
	}
#ifdef ONLYIFNEEDED

	fprintf (output_fileG, "\nThe %s layer (%s):\n", name, msg);
	fprintf (output_fileG, "     ");
	fprintf (output_fileG, "\n");
	for (j = 0; j <= num_colsG+1; j++) {
	    putc(' ', output_fileG);
	    for (i = num_rowsG; i >= 0; i--) {
		num = layer[i][j];
		if (num < 0) {
		    num = -num;
		    if( num < 99 )
		        putc('-', output_fileG);
		    else {
			num = num % 100;
		        putc('*', output_fileG);
		    }
		} else {
		    /* insert a space to separate the numbers */
		    putc(' ', output_fileG);
		}
		if( layer[i][j] > num_netsG ) {
		    putc(' ', output_fileG);
		    putc('X', output_fileG);
		} else {
		    /* Generate digits (reverse order) */
		    l = 0; do temp[l++] = num % 10 + '0'; while ((num /= 10) > 0);

		    /* right justify the number in a 2 digit field */
		    if (l == 1)
		        putc(' ', output_fileG);

		    /* Copy them back in correct order */
		    do putc(temp[--l], output_fileG); while (l > 0);

	        }
	    }
	    fprintf (output_fileG, "  col = %2d\n", j);
	}
	fprintf(output_fileG, "     ");
	fprintf(output_fileG, "\n");
#endif
    }
}



int pitch = 7*20;
int npitch = - 7*20;
/*
int npitch = 7*20;
*/
int instnum = 0;

void S_printsq()
/*
 *  print statistics - number of vias, total line length,
 *                     number of rows and columns.
 *  Mirror the whole layout upside down when print out
 */
{
    LINKPTR tlink;
    LINKLISTPTR list;
    PINPTR cpin;
    int i;  /* counter */
    int x,
	y;
    int hlink,
        vlink; 		/* To mark the existence of the links */
    int nvia = 0;
    int numlink = 0;
    int width;


    /*
     *  Initial SQUID format
     */
    initformat();

    /*  instnum must be bigger than netnum  */
    instnum += num_netsG;

    /*
     *  find the wire length
     */
    for( i = 1; i <= num_netsG; i++ )
    {
	for( tlink = net_arrayG[i].path; tlink != (LINKPTR)NULL;
	     tlink = tlink->netnext )
	{
	    numlink++;
	}
    }
    fprintf(output_fileG, "SUBNET %d\n", numlink );
    /*
     *  print the wires
     */
    for( i = 1; i <= num_netsG; i++ )
    {
	for( tlink = net_arrayG[i].path; tlink != (LINKPTR)NULL;
	     tlink = tlink->netnext )
	{
	    /*
	    fprintf(output_fileG, "%d %d %d %d %d %d\n",
	     number_to_name(i), tlink->layer,
	     tlink->x1, tlink->y1, tlink->x2, tlink->y2 );
	     */
	if( tlink->layer == HORIZ )
	{
	    width = 60;
	    if( tlink->x1 == tlink->x2 )
	    {
		fprintf(output_fileG, "MK INST %d INST_NAME \"60by60mterm\" MASTER \"60by60mterm\" \"layout\" MAT 1 0 0 1 %d %d\n",
		++instnum, pitch*tlink->x1, npitch*tlink->y1 );
		/*
		fprintf(output_fileG, "MK TERM \"i\" NET_ID %d INST_ID %d\n",
		hlayerG[tlink->y1][tlink->x1], instnum );
		*/

		fprintf(output_fileG, "MK INST %d INST_NAME \"60by60mterm\" MASTER \"60by60mterm\" \"layout\" MAT 1 0 0 1 %d %d\n",
		++instnum, pitch*tlink->x2, npitch*tlink->y2 );
		/*
		fprintf(output_fileG, "MK TERM \"i\" NET_ID %d INST_ID %d\n",
		hlayerG[tlink->y2][tlink->x2], instnum );
		*/
	    }
	}
	else
	{
	    width = 40;
	    if( tlink->y1 == tlink->y2 )
	    {
		fprintf(output_fileG, "MK INST %d INST_NAME \"40by40pterm\" MASTER \"40by40pterm\" \"layout\" MAT 1 0 0 1 %d %d\n",
		++instnum, pitch*tlink->x1, npitch*tlink->y1 );
		/*
		fprintf(output_fileG, "MK TERM \"i\" NET_ID %d INST_ID %d\n",
		vlayerG[tlink->y1][tlink->x1], instnum );
		*/

		fprintf(output_fileG, "MK INST %d INST_NAME \"40by40pterm\" MASTER \"40by40pterm\" \"layout\" MAT 1 0 0 1 %d %d\n",
		++instnum, pitch*tlink->x2, npitch*tlink->y2 );
		/*
		fprintf(output_fileG, "MK TERM \"i\" NET_ID %d INST_ID %d\n",
		vlayerG[tlink->y2][tlink->x2], instnum );
		*/
	    }
	}
	writeline(pitch*tlink->x1, npitch*tlink->y1, pitch*tlink->x2,
		  npitch*tlink->y2, width, i);

	}
    }

    /*
     *  count the vias
     */
    for( y = 1; y <= num_rowsG; y++ )
    {
	for( x = 1; x <= num_colsG; x++ )
	{
	    if( hlayerG[y][x] == vlayerG[y][x] && hlayerG[y][x] != 0 &&
		hlayerG[y][x] <= num_netsG )
	    {
		hlink = vlink = NO;
		for( list = linklayerG[y][x]; list != (LINKLISTPTR)NULL;
			list = list->next )
		{
		    tlink = list->link;
		    if( tlink->layer == HORIZ )
			hlink = YES;
		    else
			vlink = YES;

		}

		/*
		 *  To include vias on the boundary
		 */
		if( playerhG[y][x] > 0 )
		    hlink = YES;
		if( playervG[y][x] > 0 )
		    vlink = YES;

		if( hlink == YES && vlink == YES )
		{
		    nvia++;
		}
	    }
	}
    }
    /*
    fprintf(output_fileG, "VIA %d\n", nvia );
    */
    /*
     *  print the vias
     */
    for( y = 1; y <= num_rowsG; y++ )
    {
	for( x = 1; x <= num_colsG; x++ )
	{
	    if( hlayerG[y][x] == vlayerG[y][x] && hlayerG[y][x] != 0 &&
		hlayerG[y][x] <= num_netsG )
	    {
		hlink = vlink = NO;
		for( list = linklayerG[y][x]; list != (LINKLISTPTR)NULL;
			list = list->next )
		{
		    tlink = list->link;
		    if( tlink->layer == HORIZ )
			hlink = YES;
		    else
			vlink = YES;

		}

		/*
		 *  To include vias on the boundary
		 */
		if( playerhG[y][x] > 0 )
		    hlink = YES;
		if( playervG[y][x] > 0 )
		    vlink = YES;

		if( hlink == YES && vlink == YES )
		{
		    nvia++;
		    /*
		    fprintf(output_fileG, "%d %d %d %d\n", hlayerG[y][x],
					     1, x, y );
		    */
	      fprintf(output_fileG, "MK INST %d INST_NAME \"80by80pmc\" MASTER \"80by80pmc\" \"layout\" MAT 1 0 0 1 %d %d\n",
	      ++instnum, pitch*x, npitch*y);
	      /*
	      fprintf(output_fileG, "MK TERM \"i\" NET_ID %d INST_ID %d\n",
	      hlayerG[y][x], instnum );
	      */
		}
	    }
	}
    }
    printf(" There are %d vias\n", nvia );
    /*
    printf(" The total net_length is %d\n", hlength + vlength );
    printf(" ( hlength = %d,  vlength = %d )\n", hlength, vlength );
    */
}


void initformat()
/*
 *  write the initialization part in SQUID format
 */
{
    int i;

    fprintf(output_fileG, "SQUID\n");
    fprintf(output_fileG, "PUT VIEW \"%dby%dchannel\" \"layout\" \"w\" \"squidNextObjectID\" INT 777\n",num_rowsG, num_colsG);
    for( i = num_netsG; i >= 1; i-- )
    {
	fprintf(output_fileG, "MK NET %d NET_NAME \"\"\n", i );
    }
}



int numline = 0;

void writeline(x1, y1, x2, y2, width, net)
int x1, y1, x2, y2;
int width, net;
/*
 *  write lines in SQUID format
 */
{
    numline++;
    fprintf(output_fileG, "MK LINE %d NET %d LAYER \"%s\" FILL WIDTH %d PATH %d %d %d %d\n",
        INFINITY - numline, net, (width == 40 ? "NP" : "NM"),
	width, x1, y1, x2, y2);
    fprintf(output_fileG, "PUT LINE %d \"ishorizontal\" BOOL %s\n", INFINITY - numline,
	(y1 == y2 ? "TRUE" : "FALSE"));
}



void S_printstandard()
/*
 *  print statistics - number of vias, total line length,
 *                     number of rows and columns.
 *  Mirror the whole layout upside down when print out
 */
{
    LINKPTR tlink;
    LINKLISTPTR list;
    PINPTR cpin;
    int i;  /* counter */
    int x,
	y;
    int hlink,
        vlink; 		/* To mark the existence of the links */
    int nvia = 0;
    int numlink = 0;
    int width;
    PIN_LISTPTR p;


    /*
     *  Initial format
     */
    fprintf(output_fileG, "channelwiring\n" );


    /*
     *  count number of links
     */
    for( i = 1; i <= num_netsG; i++ )
    {
	for( tlink = net_arrayG[i].path; tlink != (LINKPTR)NULL;
	     tlink = tlink->netnext )
	{
	    numlink++;
	}
    }
    fprintf(output_fileG, "wires %d\n", numlink );

    /*
     *  print the wires
     */
    for( i = 1; i <= num_netsG; i++ )
    {
	for( tlink = net_arrayG[i].path; tlink != (LINKPTR)NULL;
	     tlink = tlink->netnext )
	{
	    if( tlink->p.user_given == USERGIVEN ){
		fprintf(output_fileG, "%d %d %d %d %d %d\n",
		 number_to_name(i),
		 tlink->x1, 
		 tlink->y1,
		 tlink->x2, 
		 tlink->y2, 
		 tlink->layer );
	    } else if( tlink->p.user_given == 0 ){
		fprintf(output_fileG, "%d %d %d %d %d %d\n",
		 number_to_name(i),
		 (tlink->x1 - 1) * xgridG + xshift, 
		 (tlink->y1 - 1) * ygridG + yshift,
		 (tlink->x2 - 1) * xgridG + xshift, 
		 (tlink->y2 - 1) * ygridG + yshift, 
		 tlink->layer );
	    } else {
		M( ERRMSG, "output","logic problem\n" ) ;
	    }
	}
    }

    /*
     *  count the vias
     */
    for( y = 1; y <= num_rowsG; y++ ){
	for( x = 1; x <= num_colsG; x++ ) {
	    if( hlayerG[y][x] != 0 && hlayerG[y][x] <= num_netsG ) {
		if( hlayerG[y][x] == vlayerG[y][x] ){
		    hlink = vlink = NO;
		    for( list = linklayerG[y][x]; list ; list = list->next ) {
			tlink = list->link;
			if( tlink->layer == HORIZ ){
			    hlink = YES;
			} else if( tlink->layer == VERT ){
			    vlink = YES;
			}

		    }

		    /*
		     *  To include vias on the boundary
		     */
		    if( playerhG[y][x] > 0 )
			hlink = YES;
		    if( playervG[y][x] > 0 )
			vlink = YES;


		    if( hlink == YES && vlink == YES ) {
			/* Make sure it wasn't a 3rd layer pin */
			for(p=layer3G[x]; p != (PIN_LISTPTR)NULL ; p=p->next ) {
			  if( p->pin->y == y )	/* no vias allowed on .5 layer pins */
				break; 
			  }
			if ( p == (PIN_LISTPTR)NULL ) /* p=NULL means ok to passthru */
			  nvia++;
		    }
		}
		/* now check for vias between layers 2 & 3 */
		for( list = linklayerG[y][x]; list ; list = list->next ) {
		    tlink = list->link;
		    if( tlink->layer == THREE ){
			nvia++;
		    }
		}
	    }
	}
    }
    fprintf(output_fileG, "vias %d\n", nvia );
    /*
     *  print the vias
     */
    for( y = 1; y <= num_rowsG; y++ ) {
	for( x = 1; x <= num_colsG; x++ ) {
	    if( hlayerG[y][x] != 0 && hlayerG[y][x] <= num_netsG ) {
		if( hlayerG[y][x] == vlayerG[y][x] ){
		    hlink = vlink = NO;
		    for( list = linklayerG[y][x]; list ; list = list->next ) {
			tlink = list->link;
			if( tlink->layer == HORIZ ){
			    hlink = YES;
			} else if( tlink->layer == VERT ){
			    vlink = YES;
			} 
		    }

		    /*
		     *  To include vias on the boundary
		     */
		    if( playerhG[y][x] > 0 )
			hlink = YES;
		    if( playervG[y][x] > 0 )
			vlink = YES;

		    if( hlink == YES && vlink == YES ) {
			/* we perform inverse operation of that */
			/* performed in input.c - that is we return */
			/* to (0,0) multiply by grid and shift to original */
			/* Make sure it wasn't a 3rd layer pin */
			for(p=layer3G[x]; p != (PIN_LISTPTR)NULL ; p=p->next ) {
			  if( p->pin->y == y )	/* no vias allowed on .5 layer pins */
				break; 
			  }
			if ( p == (PIN_LISTPTR)NULL ) {	/* p=NULL means ok to passthru */
			  fprintf(output_fileG, "%d %d %d %d %d\n",
			    number_to_name(hlayerG[y][x]),
			    (x - 1) * xgridG + xshift, 
			    (y - 1) * ygridG + yshift, 1, 2 );
			  }
		    }
		}

		/* now output vias between layer 2 and 3 */
		for( list = linklayerG[y][x]; list ; list = list->next ) {
		    tlink = list->link;
		    if( tlink->layer == THREE ){
			/* we perform inverse operation of that */
			/* performed in input.c - that is we return */
			/* to (0,0) multiply by grid and shift to original */
			fprintf(output_fileG, "%d %d %d %d %d\n",
			    number_to_name(hlayerG[y][x]),
			    (x - 1) * xgridG + xshift, 
			    (y - 1) * ygridG + yshift, HORIZ, THREE );
		    }
		}
	    }
	} /* end for loop */
    }
    fprintf(output_fileG, ".end\n");
}
