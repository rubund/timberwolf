#ifndef lint
static char SccsId[] = "@(#) allocate.c version 6.1 6/19/90" ;
#endif

#include "mighty.h"

/*********************************************************************
 *
 *  This routine allocates space for an array of NETS.  The array contains
 *  'size' elements.  Each element has its pointers set to NULL, its
 *  and its name set to its position in the array.
 *
 *
 *
 *********************************************************************/

NETPTR allocate_nets (size)
int size;			/* Size of array to be allocated and
				   initialized, 0 element is a dummy */
{
    int i;			/* loop counter */
    NETPTR array;		/* the array being allocated */

    array = (NETPTR) alloc((unsigned) size, sizeof (NET));

    /*
     *  initialize storage just allocated
     */

    for (i = 0; i < size; i++)
    {
	array[i].name = i;

    }
    return (array);
}



/******************************************************************
 *
 *  allocate_channel returns a pointer to an initialized CHANNEL structure.
 *
 *
 *****************************************************************/

CHANNELPTR allocate_channel (num_rows, num_cols)
int num_rows,		/* number of rows to be in the channel */
    num_cols;		/* number of columns to be in the channel */
{
    int i, j;			/* loop counters */
    CHANNELPTR channel;		/* used to allocate the channel */
    int rows,		/* num_rows + 1 */
        cols;		/* num_cols + 1 */

    rows = (unsigned) num_rows + 2;
    cols = (unsigned) num_cols + 2;

    /*
     *  Allocate space for the channel
     */

    channel = (CHANNELPTR) alloc (1 , sizeof (CHANNEL));
    channel->vert_layer = (int **) alloc (rows, sizeof (int *));
    channel->horiz_layer = (int **) alloc (rows, sizeof (int *));
    channel->pin_layerh = (int **) alloc (rows, sizeof (int *));
    channel->pin_layerv = (int **) alloc (rows, sizeof (int *));
    channel->hcomp = (int **) alloc (rows, sizeof (int *));
    channel->vcomp = (int **) alloc (rows, sizeof (int *));
    for (i = 0; i < rows; i++)
    {
	channel->vert_layer[i] = (int *) alloc (cols, sizeof (int));
	channel->horiz_layer[i] = (int *) alloc (cols, sizeof (int));
	channel->pin_layerh[i] = (int *) alloc (cols, sizeof (int));
	channel->pin_layerv[i] = (int *) alloc (cols, sizeof (int));
	channel->vcomp[i] = (int *) alloc (cols, sizeof (int));
	channel->hcomp[i] = (int *) alloc (cols, sizeof (int));
    }

    /*
     *  Initialize values
     */

    for (i = 0; i < rows; i++)
    {
	for (j = 0; j < cols; j++)
	{
	    channel->vert_layer[i][j] = 0;
	    channel->horiz_layer[i][j] = 0;
	    channel->pin_layerh[i][j] = 0;
	    channel->pin_layerv[i][j] = 0;
	    channel->vcomp[i][j] = 0;
	    channel->hcomp[i][j] = 0;
	}
    }

    channel->vert_layer[0][0] = VERT;
    channel->horiz_layer[0][0] = HORIZ;
    return (channel);
}





LINKLISTPTR ** allocate_linklayer (num_rows, num_cols)
int num_rows,		/* number of rows to be in the channel */
    num_cols;		/* number of columns to be in the channel */
{
    int i, j;			/* loop counters */
    LINKLISTPTR ** linklayer;		/* used to allocate the linklayer */
    unsigned rows,		/* num_rows + 1 */
	     cols;		/* num_cols + 1 */

    rows = (unsigned) num_rows + 2;
    cols = (unsigned) num_cols + 2;

    /*
     *  Allocate space for the linklayer
     */

    linklayer = (LINKLISTPTR **) alloc (rows , sizeof (LINKLISTPTR *));
    for (i = 0; i < rows; i++)
    {
	linklayer[i] = (LINKLISTPTR *) alloc (cols, sizeof( LINKLISTPTR ));
    }

    /*
     *  Initialize values
     */


    for (i = 0; i < rows; i++)
    {
	for (j = 0; j < cols; j++)
	{
	    linklayer[i][j] = (LINKLISTPTR)NULL;
	}
    }
    return (linklayer);
}

SEARCHPTR * allocate_searchq( size )
int size;
{
    SEARCHPTR *searchq;
    int i;

    searchq = (SEARCHPTR *) alloc (size , sizeof (SEARCHPTR));
    /*
     *  initialize the values
     */
    for( i = 0; i < size; i++ )
    {
	searchq[i] = (SEARCHPTR)NULL;
    }
    return( searchq );
}


int ** allocate_hist (num_nets)
int num_nets;
/*
 *  allocate num_nets by num_nets matrix
 */
{
    int i, j;			/* loop counters */
    int ** hist;		/* used to allocate the history */
    int nnets;

    nnets = num_nets + 2;
    /*
     *  Allocate space for the linklayer
     */

    hist = (int **) alloc (nnets , sizeof (int *));
    for (i = 0; i < nnets; i++)
    {
	hist[i] = (int *) alloc (nnets, sizeof( int ));
    }

    /*
     * Initialize to zero
     */
    for( i = 0; i < nnets; i++ )
	for( j = 0; j < nnets; j++ )
	    hist[i][j] = 0;
    return( hist );
}

int ** S_allocatematrix ( rows, cols)
int rows,		/* number of rows */
    cols;		/* number of columns */
{
    int i, j;			/* loop counters */
    int ** matrix;		/* used to allocate the channel */

    rows++;
    cols++;

    /*
     *  Allocate space for the matrix
     */

    matrix = (int **) alloc (rows, sizeof (int *));
    for (i = 0; i < rows; i++)
    {
	matrix[i] = (int *) alloc (cols, sizeof (int));
    }

    /*
     *  Initialize values
     */

    for (i = 0; i < rows; i++)
    {
	for (j = 0; j < cols; j++)
	{
	    matrix[i][j] = 0;
	}
    }
    return( matrix );
}


int * S_allocatevector( cols )
int cols;		/* number of columns */
{
    int j;			/* loop counters */
    int * vector;		/* used to allocate the vector */

    cols++;

    /*
     *  Allocate space for the vector
     */

    vector = (int *) alloc (cols, sizeof (int));

    /*
     *  Initialize values
     */

    for (j = 0; j < cols; j++)
	vector[j] = 0;

    return( vector );
}



NETPTR * S_allocatenetptr( n )
int n;
{
    NETPTR *stack;
    int i;

    stack = (NETPTR *) alloc ((unsigned) n+1, sizeof (NETPTR));

    /*
     *  Initialize values
     */

    for( i = 1; i <= n; i++ )
	stack[i] = (NETPTR)NULL;

    return( stack );
}
