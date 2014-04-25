#ifndef lint
static char SccsId[] = "@(#) density.c version 6.1 6/19/90" ;
#endif

#include "mighty.h"

/*********************************************************************
 *
 *  find_density returns an array containing the density of each column.
 *  A net occupies all columns between its rightmost->col and its
 *  leftmost->col (inclusive).  rightmost and leftmost are set during
 *  the input routine, when the net data structures are being constructed.
 *
 **********************************************************************/

int * S_finddensity()
{
    int *density;		/* array that will contain the density
				   of each column */
    PINPTR cpin;
    int i,j;			/* loop counters */
    int xmin,
	xmax;
    int maxdensity = 0;
    int *S_allocatevector();

    /*
     *  allocate space for the density array
     */

    density = S_allocatevector( num_colsG+1 );

    /*
     *  find range of each net
     */
    for (i = 1; i <= num_netsG; i++) {
	if( (cpin = net_arrayG[i].pin) == (PINPTR)NULL ){
	    continue;
	}

	xmin = net_arrayG[i].colleft;
	xmax = net_arrayG[i].colright;

        /*
         *  find densities
	 *  if unit length, do not count ( we can use vert layer )
         */
	if( xmax - xmin > 1 )
	    for(j = xmin; j <= xmax; j++)
	        (density[j])++;
    }

    /*
     *  return result
     */
    for( j = 1; j <= num_colsG; j++ )
    {
	maxdensity = MAX( density[j], maxdensity );
	/*
	printf("%3d %d\n", j, density[j]);
	*/
    }
    printf("modified maxdensity = %d\n", maxdensity );

    return (density);
}


int S_maxdencol( density, fromcol, tocol )
int *density;
int fromcol,
    tocol;
/*
 *  return the column number of max density
 */
{
    int i, j;
    int maxcol;
    int count;
    int limit;
    int maxden = 0;

    maxcol = tocol ;
    limit = MIN( tocol+5, num_colsG );
    for( i = fromcol; i <= tocol; i++ )
    {
	if( maxden < density[i] )
	{
	    maxden = density[i];
	    for( count = 1; (density[i+count] == maxden) &&
		(i+count < limit); )
		count++;
	    maxcol = i + count/2;
	}
	if( maxden == density[i] && i > maxcol + count )
	{
	    for( j = 1; (density[i+j] == maxden) && (i+j < limit); )
		j++;
	    if( j > count )
	    {
	        maxcol = i + j/2;
		count = j;
	    }
	}
    }

    return( maxcol );
}

void S_retdensity()
{
    int *density;		/* array that will contain the density
				   of each column */
    int *lowtr;			/* lower boundary */
    int *hightr;		/* higher boundary */
    PINPTR cpin;
    LINKPTR link;
    int i,j;			/* loop counters */
    int xmin,
	xmax;
    int ntrack,
	tmprow;
    int maxdensity = MINFINITY;
    int *S_allocatevector();
    int S_findtracks();

    /*
     *  allocate space for the density array
     */

    density = S_allocatevector( num_colsG+1 );
    lowtr = S_allocatevector( num_colsG+1 );
    hightr = S_allocatevector( num_colsG+1 );
    for( j = 1; j <= num_colsG; j++ )
    {
	lowtr[j] = 0;
	hightr[j] = INFINITY;
    }

    /*
     *  find range of each net
     */
    for (i = 1; i <= num_netsG; i++)
    {
	if( (cpin = net_arrayG[i].pin) == (PINPTR)NULL )
    continue;

	xmin = net_arrayG[i].colleft;
	xmax = net_arrayG[i].colright;

        /*
         *  find densities
	 *  if unit length, do not count ( we can use vert layer )
         */
	if( xmax - xmin > 1 )
	    for(j = xmin; j <= xmax; j++)
	        (density[j])++;
    }

    for( link = bounding_boxG; link != (LINKPTR)NULL; link = link->netnext )
    {
	/* if vertical, continue */
	if( link->x1 < link->x2 )
	    for( j = link->x1; j <= link->x2; j++ )
		lowtr[j] = MAX( lowtr[j], link->y1);
	if( link->x2 < link->x1 )
	    for( j = link->x2; j <= link->x1; j++ )
		hightr[j] = MIN( hightr[j], link->y1);
    }
    /*
     *  return result
     */
    for( j = 1; j <= num_colsG; j++ )
    {
	density[j] = density[j] - hightr[j] + lowtr[j];
	/*
	printf("%d %d %d\n", hightr[j], lowtr[j], density[j]);
	*/
	maxdensity = MAX( density[j] , maxdensity );
    }
    /* add 1 since boundary can not be used */
    maxdensity++;
    fprintf(output_fileG, "%d (incremental density)\n", maxdensity );

    return (maxdensity);
}
