#ifndef lint
static char SccsId[] = "@(#)init_info.c	Yale Version 2.6 5/16/91";
#endif
/* -----------------------------------------------------------------

	FILE:		init_info.c
	AUTHOR:		Dahe Chen
	DATE:		Wed Dec 13 2:47:32 EDT 1989
	CONTENTS:	init_info ()
	REVISION:
		Wed Aug 15 16:45:14 PDT 1990
	    Change and add parameter for the random interchange
	    algorithm.
		Fri Aug 17 17:03:14 PDT 1990
	    Remove one parameter no_change_limit for the random
	    interchange.
		Tue Oct  9 12:17:27 EDT 1990
	    Change version number.
		Mon Oct 22 16:37:38 EDT 1990
	    Add the include file yalecad/string.h
		Wed Oct 31 15:38:43 EST 1990
	    Change the length of LEN from 128 to LRECL. And add
	    the code reading the sheet capacitance and resistance.
		Mon Nov 12 11:11:43 EST 1990
	    Add a parameter to control graphics.
		Thu Nov 15 19:13:49 EST 1990
	    Add the code reading the parameters C_TOLERANCE and
	    R_TOLERANCE.
		Tue Nov 20 17:58:18 EST 1990
	    Remove #define LEN and parameter for external storage.
	    Modify the code to my new style.
		Mon Dec  3 15:02:01 EST 1990
	    Replace sscanf by Ystrparser.
		Tue Dec  4 16:09:58 EST 1990
	    Change the input format of the specifications objective
	    and iteration_limit. Also, add the specification for
	    the number of routes generated.
		Wed Dec  5 13:25:09 EST 1990
	    Remove h_width and v_width.
		Tue Dec 11 15:31:24 EST 1990
	    Set a default value for the parameter iteration_limit.
		Tue Feb  5 12:04:57 EST 1991
	    Reformat error message output.
		Fri Feb  8 13:54:11 EST 1991
	    Change the error messages to be more informative.
		Tue Mar  5 11:00:06 EST 1991
	    Change fopen and fclose to TWOPEN and TWCLOSE, respectively.

----------------------------------------------------------------- */

#include <yalecad/string.h>
#include <define.h>
#include <gg_router.h>
#include <dgraph.h>
#include <macros.h>
#include <analog.h>
#include <yalecad/file.h>

#define VERSION	"v2.0 "

BOOL verboseG;

extern int iteration_limit;
extern int *Apins;
extern int *routes;

BOOLEAN
init_info(argc, argv)
    int argc;
    char **argv;
{

    char input[LRECL];
    char *ptr;
    char **tokens;
    INT numtokens;
    int status;
    int intro();
    BOOL debug;	
    FILE *fpar;

    /***********************************************************
    * At least a program name and a circuit name must be present
    ***********************************************************/
    if (argc < 2 || argc > 3)
    {
	syntax();
    }
    else
    {
	debug     = FALSE;
	verboseG  = FALSE;
	graphicsG = FALSE;
	if (*argv[1] == '-')
	{
	    for (ptr = ++argv[1]; *ptr; ptr++)
	    {
		switch (*ptr)
		{
		    case 'd':
			debug = TRUE;
			break;

		    case 'g':
			graphicsG = TRUE;
			break;

		    case 'v':
			verboseG = TRUE;
			break;

		    default:
			ERROR2 ("\n\nUnknown option:%c\n", *ptr);
			syntax ();
		}
	    }
	    YdebugMemory(debug);

	    sprintf(cktName, "%s", argv[2]);
	    YinitProgram("Mickey", VERSION, intro);

	    /***********************************************************
	    * Now tell the user what he picked
	    ***********************************************************/
	    OUT1("\n\nMickey switches:\n");
	    if (debug)
	    {
		YsetDebug(TRUE);
		OUT1("\tdebug on\n");
	    } 
	    if (verboseG )
	    {
		OUT1("\tMessages will be redirected to screen\n");
	    }
	    OUT1("\n");
	}
	else if (argc == 2)
	{
	    /***********************************************************
	    * order is important here
	    ***********************************************************/
	    YdebugMemory(FALSE);

	    sprintf(cktName, "%s", argv[1]);
	    YinitProgram("Mickey", VERSION, intro);

	}
	else
	{
	    syntax();
	}
    }

    status = TRUE;

    /***********************************************************
    * Set default value for the parameters:		      */

	    DIGITAL  = TRUE;
	    CASE     = 1;
	    C_SHEET  = 1.0;
	    R_SHEET  = 1.0;
	    NUMTREES = 20;
	    iteration_limit = INT_MAX;

    /**********************************************************/

    /***********************************************************
    * Retrieve all parameters and circuit name specified by the
    * user. Parameters can be either saved in file cktName.gpar
    * or specified on the command line.
    ***********************************************************/
    sprintf(input, "%s.gpar", cktName);

    if ((fpar = TWOPEN(input, "r", ABORT)) != NULL)
    {
	while (fgets(input, LRECL, fpar))
	{
	    tokens = Ystrparser(input, " \t\n", &numtokens);
	    if (numtokens == 0)
	    {
		continue;
	    }

	    switch(input[0])
	    {
		case 'a' :
		    /*****************************************************
		    * The circuit is an analog circuit.
		    *****************************************************/
		    if (strncmp(tokens[0], "analog.circuit", 14)
		     == STRINGEQ)
		    {
			if (numtokens != 1)
			{
			    ERROR2("\n\n%s.gpar:WARNING: ", cktName);
			    ERROR2("Anything after %s is discarded.\n",
				tokens[0]);
			}
			DIGITAL = FALSE;
		    }
		    else
		    {
			ERROR2("\n\n%s.gpar:ERROR: ", cktName);
			ERROR2("Unknown keyword %s.\n", tokens[0]);
			status = FALSE;
		    }
		    break;

		case 'c' :
		    /*****************************************************
		    * The sheet capacitance.
		    *****************************************************/
		    if (numtokens != 2)
		    {
			ERROR2("\n\n%s.gpar:ERROR: ", cktName);
			ERROR2("Incorrect number of fields %d\n",
			    numtokens);
			ERROR1("\tCorrect format: capacitance FLOAT\n");
			ERROR1("\t\tor\n\t");
			ERROR1("\t\tcap_tolerance FLOAT\n");
			status = FALSE;
		    }
		    else
		    {
			if (strncmp(tokens[0], "capacitance", 11)
			 == STRINGEQ)
			{
			    C_SHEET = atof(tokens[1]);
			}
			else if (strncmp(tokens[0], "cap_tolerance", 13)
			      == STRINGEQ)
			{
			    C_TOLERANCE = atof(tokens[1]);
			}
			else
			{
			    ERROR2("\n\n%s.gpar:ERROR: ", cktName);
			    ERROR2("Unknown keyword %s.\n", tokens[0]);
			    status = FALSE;
			}
		    }
		    break;

		case 'd' :
		    /*****************************************************
		    * The circuit is a digital circuit.
		    *****************************************************/
		    if (numtokens != 1)
		    {
			ERROR2("\n\n%s.gpar:WARNING: ", cktName);
			ERROR2("Anything after %s is discarded.\n",
			    tokens[0]);
		    }
		    if (strncmp(tokens[0], "digital.circuit", 15)
		     != STRINGEQ)
		    {
			ERROR2("\n\n%s.gpar:ERROR: ", cktName);
			ERROR2("Unknown keyword %s\n", tokens[0]);
			status = FALSE;
		    }
		    break;

		case 'l' :
		    /*****************************************************
		    * The limit for the number of iteration in the random
		    * interchange algorithm.
		    *****************************************************/
		    if (strncmp(tokens[0], "limit_iteration", 15)
		     == STRINGEQ)
		    {
			if (numtokens != 2)
			{
			    ERROR2("\n\n%s.gpar:ERROR: ", cktName);
			    ERROR2("Incorrect number of fields %d\n",
				numtokens);
			    ERROR1("\tCorrect format: limit_iteration INT\n");
			    status = FALSE;
			}
			else
			{
			    iteration_limit = atoi(tokens[1]);
			}
		    }
		    else
		    {
			ERROR2("\n\n%s.gpar:ERROR: ", cktName);
			ERROR2("Unknown keyword %s.\n", tokens[0]);
			status = FALSE;
		    }
		    break;

		case 'm' :
		    /*****************************************************
		    * The circuit is a mixed circuit.
		    *****************************************************/
		    if (strncmp(tokens[0], "mixed.circuit", 13)
		     == STRINGEQ)
		    {
			if (numtokens != 1)
			{
			    ERROR2("\n\n%s.gpar:WARNING: ", cktName);
			    ERROR2("Anything after %s is discarded.\n",
				tokens[0]);
			}
			DIGITAL = FALSE;
		    }
		    else
		    {
			ERROR2("\n\n%s.gpar:ERROR: ", cktName);
			ERROR2("Unknown keyword %s.\n", tokens[0]);
			status = FALSE;
		    }
		    break;

		case 'n' :
		    /*****************************************************
		    * The number of routes to be generated for a net.
		    *****************************************************/
		    if (strncmp(tokens[0], "number.routes", 13)
		     == STRINGEQ)
		    {
			if (numtokens != 2)
			{
			    ERROR2("\n\n%s.gpar:ERROR: ", cktName);
			    ERROR2("Incorrect number of fields %d\n",
				numtokens);
			    ERROR1("\tCorrect format: number.routes INT\n");
			    status = FALSE;
			}
			else
			{
			    NUMTREES = atoi(tokens[1]);
			    if (NUMTREES < 1 || NUMTREES > 32)
			    {
				ERROR2("\n\n%s.gpar:WARNING: ", cktName);
				ERROR2("Incorrect number of routes: %d\n",
				    NUMTREES);
				ERROR2("\tSet to default value: %d\n",
				    NUMTREES = 20);
			    }
			}
		    }
		    else
		    {
			ERROR2("\n\n%s.gpar:ERROR: ", cktName);
			ERROR2("Unknown keyword %s\n", tokens[0]);
			status = FALSE;
		    }
		    break;

		case 'o' :
		    /*****************************************************
		    * The objective function specification. The spec CASE
		    * must be equal to 1 or 2.
		    *****************************************************/
		    if (strncmp(tokens[0], "objective", 9) == STRINGEQ)
		    {
			if (numtokens != 2)
			{
			    ERROR2("\n\n%s.gpar:ERROR: ", cktName);
			    ERROR2("Incorrect number of fields %d\n",
				numtokens);
			    ERROR2("\tCorrect format: %s [1|2]\n",
				tokens[0]);
			    status = FALSE;
			}
			else
			{
			    CASE = atoi(tokens[1]);
			    if (!(CASE == 1 || CASE == 2))
			    {
				ERROR2("\n\n%s.gpar:ERROR: ", cktName);
				ERROR2("Incorrect objective spec %d\n",
				    CASE);
				ERROR2("\tCorrect format: %s [1|2]\n",
				    tokens[0]);
				status = FALSE;
			    }
			}
		    }
		    else
		    {
			status = FALSE;
		    }
		    break;

		case 'r' :
		    /*****************************************************
		    * The sheet resistance.
		    *****************************************************/
		    if (numtokens != 2)
		    {
			ERROR2("\n\n%s.gpar:ERROR: ", cktName);
			ERROR2("Incorrect number of fields %d\n",
			    numtokens);
			ERROR1("\tCorrect format: resistance FLOAT\n");
			ERROR1("\t\tor\n\t");
			ERROR1("\t\tres_tolerance FLOAT\n");
			status = FALSE;
		    }
		    else
		    {
			if (strncmp(tokens[0], "resistance", 10)
			 == STRINGEQ)
			{
			    R_SHEET = atof(tokens[1]);
			}
			else if (strncmp(tokens[0], "res_tolerance", 13)
			      == STRINGEQ)
			{
			    R_TOLERANCE = atof(tokens[1]);
			}
			else
			{
			    ERROR2("\n\n%s.gpar:ERROR: ", cktName);
			    ERROR2("Unknown keyword %s\n", tokens[0]);
			    status = FALSE;
			}
		    }
		    break;

		case 's' :
		    /*****************************************************
		    * No output to the terminal is requested.
		    *****************************************************/
		    if (strncmp(tokens[0], "silent", 6) == STRINGEQ)
		    {
			if (numtokens != 1)
			{
			    ERROR2("\n\n%s.gpar:WARNING: ", cktName);
			    ERROR2("Anythings after %s are discarded\n",
				tokens[0]);
			}
			verboseG = FALSE;
		    }
		    else
		    {
			ERROR2("\n\n%s.gpar:ERROR: ", cktName);
			ERROR2("Unknown keyword %s\n", tokens[0]);
			status = FALSE;
		    }
		    break;

		default :
		    ERROR2("\n\n%s.gpar:ERROR: ", cktName);
		    ERROR2("Unknown keyword %s\n", tokens[0]);
		    status = FALSE;
		    break;
	    }
	}
	TWCLOSE(fpar);
    }
    else
    {
	PRINT(stdout, "\n\n");
	PRINT(stdout, "The file %s.gpar does not exist.\n", cktName);
	PRINT(stdout, "Default values are used for the parameters:\n");
	PRINT(stdout, "\tDigital circuit\n");
	PRINT(stdout, "\tFirst objective function\n");
	PRINT(stdout, "\tNumber of routes: %d\n", NUMTREES);
	PRINT(stdout, "\tMaximum number of iterations: %d\n",
			iteration_limit);
	PRINT(stdout, "\n\n");
    }

    fprintf(stderr, "Opening .gout file for writing\n");
    fdat = FOPEN("gout","w");
    fprintf(stderr, "Done.\n");

    fprintf(fdat, "\tMickey: A Graph_Based Global Routing Program\n\n");
    fprintf(fdat, "          Electrical Engineering Department\n");
    fprintf(fdat, "                  Yale University\n\n\n");
    fprintf(fdat, "Circuit name: <%s>\n\n", cktName);

    fin = FOPEN("mrte","r");

    if (fgets(input, LRECL, fin))
    {
	tokens = Ystrparser(input, " :\n\t", &numtokens);
	if (numtokens != 4)
	{
	    ERROR2("\n\n%s.gpar:ERROR: ", cktName);
	    ERROR2("Incorrect number of fields %d\n", numtokens);
	    ERROR1("\tCorrect format: numnodes:INT numedges:INT\n");
	    status = FALSE;
	}
	else
	{
	    numnodes = atoi(tokens[1]);
	    numedges = atoi(tokens[3]);
	}
    }

    maxpins = 0;
    totroutes = 0;
    THRESHOLD = numpins / 2;

    routes = (int *) Ysafe_calloc((NUMTREES+1), sizeof(int));
    Apins = (int *) Ysafe_calloc(51, sizeof(int));

    netlist = NIL(NETDR);

    OUT1("The channel graph:\n");
    OUT2("    number of nodes: %d\n", numnodes);
    OUT2("    number of edges: %d\n\n", numedges);
    OUT1("net                    pins     routes     m_len     M_len     ave_len\n");
    OUT1("======================================================================\n");
    fflush(stdout);

    fprintf(fdat, "The channel graph:\n");
    fprintf(fdat, "    number of nodes: %d\n", numnodes);
    fprintf(fdat, "    number of edges: %d\n\n", numedges);
    fprintf(fdat, "net                    pins     routes     m_len     M_len     ave_len\n");
    fprintf(fdat, "======================================================================\n");
    fflush(fdat);

    return(status);

}

intro()
{

    extern char *YmsgG;

    PRINT(stdout, "\n\n%s\n\n", YmsgG);
    PRINT(stdout, "        A Graph_Based Global Routing Program\n\n");
    PRINT(stdout, "          Electrical Engineering Department\n");
    PRINT(stdout, "                  Yale University\n\n\n");
    PRINT(stdout, "Circuit name: <%s>\n\n", cktName);

}

/*=====================================================================
*   Give the user correct syntax.
=====================================================================*/
syntax()
{

    Ysystem("Mickey", 0, "echo ", NIL (char));
    Ysystem("Mickey", 0, "echo ", NIL (char));
    ERROR1( "\n\nIncorrect syntax.  Correct syntax:\n");
    ERROR1("\nMickey [-dgv] designName\n");
    ERROR1("\twhose options is zero or more of the following:\n");
    ERROR1("\t\td - prints debug info and performs extensive\n");
    ERROR1("\t\t    error checking\n");
    ERROR1("\t\tg - turn on graphics - default no graphics\n");
    ERROR1("\t\tv - verbose mode - default silent writes to screen\n");
    YexitPgm(PGMFAIL);

} /* end syntax */

/*=====================================================================
 *  FOPEN definition (formerly a macro)
 *=====================================================================*/

FILE *FOPEN (const char *sfx, const char *op)
{
    FILE *fp;
    char fname[256];

    sprintf(fname, "%s.%s", cktName, sfx);

/* Diagnostic */
/*
    fprintf(stderr, "cktName is %s\n", fname);
    fprintf(stderr, "sfx is %s\n", sfx);
    fprintf(stderr, "fname is %s\n", fname);
    fprintf(stderr, "op is %s\n", op);
*/

    if ((fp = TWOPEN(fname, (char *)op, ABORT)) == NULL)
    {
	PRINT(stderr, "Can't open file %s\n", fname);
	exit(1);
    }
    return fp;
}       
