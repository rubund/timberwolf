#include "copyright.h"
#include "yacr.h"

/*********************************************************************
 *
 *  This routine allocates space for an array of NETS.  The array contains
 *  'size' elements.  Each element has its pointers set to NULL, its
 *  level_from_top and level_from_bottom set to 0, its row set to 0,
 *  and its name set to its position in the array.
 *
 *  Author: Jim Reed
 *
 *  Date: 3-18-84
 *  Modified: 9-24-84	pin_placement added
 *
 *********************************************************************/

NETPTR allocate_nets (size)
IN int size;			/* Size of array to be allocated and
				   initialized, 0 element is a dummy */
{
    int i;			/* loop counter */
    NETPTR array;		/* the array being allocated */

    array = ALLOC(NET, size);

    /*
     *  initialize storage just allocated
     */

    for (i = 0; i < size; i++)
    {
	array[i].name = i;
	array[i].level_from_top = 0;
	array[i].level_from_bottom = 0;
	array[i].pin_placement = 0;
	array[i].num_bot = 0;
	array[i].num_top = 0;
	array[i].row = 0;
	array[i].leftmost = NULL;
	array[i].rightmost = NULL;
	array[i].parents = NULL;
	array[i].children = NULL;
    }
    return (array);
}



/******************************************************************
 *
 *  allocate_channel returns a pointer to an initialized CHANNEL structure.
 *
 *  Author: Jim Reed
 *
 *  Date: 3-23-84
 *
 *  Fixed bug 3-26-85 D. Braun to fill row 0 with -1's.
 *
 *****************************************************************/

CHANNELPTR allocate_channel (num_rows, num_cols)
IN int num_rows,		/* number of rows to be in the channel */
       num_cols;		/* number of columns to be in the channel */
{
    int i, j;			/* loop counters */
    CHANNELPTR channel;		/* used to allocate the channel */
    unsigned rows,		/* num_rows + 1 */
	     cols;		/* num_cols + 1 */

    rows = (unsigned) num_rows + 2;
    cols = (unsigned) num_cols + 1;

    /*
     *  Allocate space for the channel
     */

    channel = ALLOC(CHANNEL, 1);
    channel->vert_layer = ALLOC(int *, rows);
    channel->horiz_layer = ALLOC(int *, rows);
    for (i = 0; i < rows; i++)
    {
	channel->vert_layer[i] = ALLOC(int, cols + 1);
	channel->horiz_layer[i] = ALLOC(int, cols + 1);
    }

    /*
     *  Initialize values
     */

    channel->left_column = 0;

    for (i = 0; i <= num_rows; i++)
    {
	for (j = 0; j < num_cols + 2; j++)
	{
	    channel->vert_layer[i][j] = 0;
	    channel->horiz_layer[i][j] = 0;
	}
    }

    /*
     *  make dummy top and bottom row that can be looked at but will never be
     *  be changed
     */
    i = num_rows + 1;
    for (j = 0; j < num_cols + 2; j++)
    {
	channel->vert_layer[0][j] = BORDER;
	channel->horiz_layer[0][j] = BORDER;
	channel->vert_layer[i][j] = BORDER;
	channel->horiz_layer[i][j] = BORDER;
    }
    return (channel);
}

/*ARGSUSED*/
deallocate_channel (channel, num_rows, num_cols)
IN int num_rows,		/* number of rows to be in the channel */
       num_cols;		/* number of columns to be in the channel */
CHANNELPTR channel;		/* used to allocate the channel */
{
    int i;			/* loop counters */
    unsigned rows;		/* num_rows + 1 */


    rows = (unsigned) num_rows + 2;

    /*
     *  deAllocate space for the channel
     */

    for (i = 0; i < rows; i++)
      {
	FREE(channel->vert_layer[i]);
	FREE(channel->horiz_layer[i]);
      }
    FREE(channel->vert_layer);
    FREE(channel->horiz_layer);
    FREE(channel);
}



/*****************************************************************
 *
 *  allocate_cost returns a pointer to a matrix of int.  The matrix
 *  has dimension [num_rows][num_nets + 1].
 *
 *  Author: Jim Reed
 *
 *  Date: 3-26-84
 *
 *******************************************************************/

int **allocate_cost (num_rows, num_nets)
IN int num_rows;		/* number of rows in the matrix */
IN int num_nets;		/* number of nets the matrix must be able
				   to handle */
{
    int **mat;		/* the matrix being allocated */
    int i, j;			/* loop counters */

    mat = ALLOC(int *, num_rows + 1);

    for (i = 0; i <= num_rows; i++)
    {
	mat[i] = ALLOC(int, num_nets + 1);
	for (j = 0; j <= num_nets; j++)
	    mat[i][j] = INFINITY;
    }

    return (mat);
}



/*****************************************************************
 *
 *  allocate_matrix returns a pointer to a matrix of int.  The matrix
 *  has dimension [n][n].
 *
 *  Author: Jim Reed
 *
 *  Date: 10-28-84
 *
 *******************************************************************/

int **allocate_matrix (n)
IN int n;			/* number of rows in the matrix */
{
    int **mat;			/* the matrix being allocated */
    register int i, j;		/* loop counters */

    mat = ALLOC(int *, n + 1);

    for (i = 0; i <= n; i++)
    {
	mat[i] = ALLOC(int, n + 1);
	for (j = 0; j <= n; j++)
	    mat[i][j] = 0;
    }

    return (mat);
}


/* beards - sept 87 - added these memory savers because of memory overflow
 	     on some channels with lots oc VCV's  */

free_path_list(path_l)
PATH_LIST path_l;
{
PATHPTR path,path2;

for(; path_l != NULL;path_l = path_l->next)
  for(path = path_l->path;path != NULL;path = path2)
    {
      path2 = path->next;
      delete_path(path);
    }
}

static PATHPTR old_paths = NULL;

PATHPTR new_path()
{
    PATHPTR p;

    if(old_paths == NULL)
        return(ALLOC(PATH, 1));

    p = old_paths;
    old_paths = old_paths->next;
    return(p);
}
	 
delete_path(path)
PATHPTR path;
{
    path->next = old_paths;
    old_paths = path;
}

