#ifndef lint
static char SccsId[] = "@(#) misc.c version 6.1 6/19/90" ;
#endif

#include "mighty.h"
#include <yalecad/message.h>
int Densityonly;

/******************************************************************
 *
 *  command_line processes all the information on the command line.
 *  Global flags are set from this, and input and output files are opened.
 *  If no input and output files are specified, stdin and stdout are
 *  assumed.
 *
 *
 *****************************************************************/

void command_line (argc, argv)
int argc;			/* argc and argv are used to get information
				   from the command line */
char *argv[];
{
    int i;			/* loop counter */

    /* set defaults */
    debugG = NO;
    riverG = NO;
    input_fileG = stdin;
    result_fileG = stdin;
    output_fileG = stdout;
    ioformG = HUMAN;
    outformG = HUMAN;
    stats_onlyG = NO;
    maximize_metalG = YES;
    Densityonly = NO;
    mazeOnlyG = NO;
    xgridG = 1 ;
    ygridG = 1 ;

    for (i = 1; i < argc; i++)
    {
	if (strcmp (argv[i], "-H") == 0)
	    ioformG = MACHINE;
	else if (strcmp (argv[i], "-O") == 0)
	{
	    outformG = MACHINE;
	    if (i < argc-1) result_fileG = fopen(argv[++i], "w");
	    else outformG = HUMAN;
	}
	else if (strcmp (argv[i], "-d") == 0)
	    debugG = YES;
	else if (strcmp (argv[i], "-s") == 0)
	    stats_onlyG = YES;
	else if (strcmp (argv[i], "-r") == 0)
	    riverG = YES;
	else if (strcmp (argv[i], "-m") == 0)
	    maximize_metalG = NO;
	else if (strcmp (argv[i], "-e") == 0)
	    Densityonly = YES;
	else if (strcmp (argv[i], "-maze") == 0)
	    mazeOnlyG = YES;
	else if (strcmp (argv[i], "-xgrid") == 0)
	{
	    i++;
	    if (i < argc) sscanf (argv[i], "%d", &xgridG);
	    if( xgridG <= 0 ){
		sprintf( YmsgG, "ERROR xgrid:%d is <= 0\n", xgridG ) ;
		M( ERRMSG, "command_line", YmsgG ) ; 
		xgridG = 1 ;
	    }
	    sprintf( YmsgG, "xgrid set to %d\n", xgridG ) ;
	    M( MSG, NULL, YmsgG ) ; 
	}
	else if (strcmp (argv[i], "-ygrid") == 0)
	{
	    i++;
	    if (i < argc) sscanf (argv[i], "%d", &ygridG);
	    if( ygridG <= 0 ){
		sprintf( YmsgG, "ERROR ygrid:%d is <= 0\n", ygridG ) ;
		M( ERRMSG, "command_line", YmsgG ) ; 
		ygridG = 1 ;
	    }
	    sprintf( YmsgG, "ygrid set to %d\n", ygridG ) ;
	    M( MSG, NULL, YmsgG ) ; 
	}
/*
	else if (strcmp (argv[i], "-z") == 0)
	{
	    i++;
	    if (i < argc)
		sscanf (argv[i], "%d", &cut_column);
	}
	else if (strcmp (argv[i], "-c") == 0)
	{
	    i++;
	    if (i < argc)
		sscanf (argv[i], "%d", &initial_column);
	}
*/
	else
	{
	    if (ioformG == HUMAN)
	    {
		input_fileG = fopen (argv[i], "r");
		if (i + 1 < argc)
		    output_fileG = fopen (argv[i + 1], "w");
		fprintf (output_fileG, "\nInput file: %s\n\n", argv[i]);
		return;
	    }
	}
    }
}


/*****************************************************
 *
 *  name_to_number and number_to_name handle the translation from the
 *  external (input) to the internal numbers used for the various nets
 *  being routed.  init_name_translation is called to set up the static
 *  variables declared below that are used in the translation.
 *  Since this name_to_number is called only once per pin on the channel
 *  it is not done in a very efficient way.  number_to_name is called
 *  (at least) once for every piece of metal or poly in the final routed
 *  channel, so it is very efficient.
 *  
 ******************************************************/

static int max_net_number;	/* largest net number used so far */

void init_name_translation (num_nets)
int num_nets;		/* number of nets that will be in the channel
				   */
{
    int i;			/* loop counter */
    int *S_allocatevector();

    /* allocate the name_array */
    name_arrayG = S_allocatevector( num_nets );

    /* empty the array */
    for (i = 0; i <= num_nets; name_arrayG[i++] = 0);

    /* set max_net_number */
    max_net_number = 0;
}

/* number_to_name has been changed to a macro.  It (and name_array) would
 * have to be moved to "mighty.h"
 */
/* int number_to_name (number)
int number;			* the net number whose name is desired *
{
    return (name_arrayG[number]);
} */

int correct_num_nets ()
{
    return (max_net_number);
}

int name_to_number (name)
int name;			/* the external name of a net */
{
    int i;			/* loop counter */

/*     name_array[name] = name;
    return(name);
 */

    /* if "name" has already been assigned a number, return that number */
    for (i = 0; i <= max_net_number; i++)
	if (name_arrayG[i] == name)
	    return (i);

    /* assign max_net_number+1 to be name */
    max_net_number++;
    name_arrayG[max_net_number] = name;
    return (max_net_number);
}

